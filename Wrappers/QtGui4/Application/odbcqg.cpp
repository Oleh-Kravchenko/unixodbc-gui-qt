/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "odbcqg.h"

#include "Execute16.xpm"
#include "Connected16.xpm"
#include "Disconnected16.xpm"
#include "ODBC64.xpm"


odbcqg::odbcqg()
    : QMainWindow( 0 /*, WDestructiveClose */ )
{
    // init our gui elements...
    setWindowTitle( "odbcqg" );
    setWindowIcon( QIcon( xpmODBC64 ) );
    createHandles();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createClientArea();

    // message passing is all connected now so lets make some ODBC calls...
    pEnvironment->doAlloc();
    pConnection->doAlloc();

}

odbcqg::~odbcqg()
{
    // we could just delete pSystem and let QObject destructor cleanup but lets do it explicitly
    if ( pStatement ) delete pStatement;
    if ( pConnection ) delete pConnection;
    if ( pEnvironment ) delete pEnvironment;
    if ( pSystem  ) delete pSystem;
}

void odbcqg::createHandles()
{
    pSystem         = new ODBCQGSystem();
//    connect( pSystem, SIGNAL(signalMessage(ODBCMessage)), this, SLOT(slotMessage(ODBCMessage)) );

    pEnvironment    = new ODBCQGEnvironment( pSystem );
    connect( pEnvironment, SIGNAL(signalMessage(ODBCMessage)), this, SLOT(slotMessage(ODBCMessage)) );

    pConnection     = new ODBCQGConnection( pEnvironment );
    connect( pConnection, SIGNAL(signalConnected()), this, SLOT(slotConnected()) );
    connect( pConnection, SIGNAL(signalDisconnected()), this, SLOT(slotDisconnected()) );
    
    pStatement      = new ODBCQGStatement( pConnection );
    connect( pStatement, SIGNAL(signalResults(ODBCQStatement*)), this, SLOT(slotResults(ODBCQStatement*)) );
}

void odbcqg::createActions()
{
    pactionExecute = new QAction( QIcon( xpmExecute16 ), "&Execute", this );
    pactionExecute->setShortcut( tr( "Ctrl+E" ) );
    pactionExecute->setStatusTip( tr( "Submit the text to the data source for execution" ) );
    connect( pactionExecute, SIGNAL(triggered()), this, SLOT(slotExecute()) );

    pactionQuit = new QAction( tr( "&Quit" ), this );
    pactionQuit->setShortcut( tr( "Ctrl+Q" ) );
    pactionQuit->setStatusTip( tr( "Quit this application" ) );
    connect( pactionQuit, SIGNAL(triggered()), this, SLOT(close()) );

    pactionConnect = new QAction( QIcon( xpmDisconnected16 ), "&Connect", this );
    pactionConnect->setStatusTip( tr( "Connect to a Data Source or Disconnect from current." ) );
    connect( pactionConnect, SIGNAL(triggered()), this, SLOT(slotConnectToggle()) );

    pactionAbout = new QAction( tr( "&About" ), this );
    pactionAbout->setStatusTip( tr( "Show this application's About box" ) );
    connect( pactionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()) );
}

void odbcqg::createMenus()
{
    pmenuFile = menuBar()->addMenu( tr( "&File" ) );
    pmenuFile->addAction( pactionExecute );
    pmenuFile->addAction( pactionQuit );

    pmenuDataSource = menuBar()->addMenu( tr( "&Data Source" ) );
    pmenuDataSource->addAction( pactionConnect );

    menuBar()->addSeparator();

    pmenuHelp = menuBar()->addMenu( tr( "&Help" ) );
    pmenuHelp->addAction( pactionAbout );
}

void odbcqg::createToolBars()
{
    ptoolbarFile = addToolBar(tr("File"));
    ptoolbarFile->addAction( pactionExecute );

    ptoolbarDataSource = addToolBar(tr("Data Source"));
    ptoolbarDataSource->addAction( pactionConnect );
}

void odbcqg::createStatusBar()
{
    statusBar()->showMessage( tr( "Ready" ) );
}

void odbcqg::createClientArea()
{
    pSplitter           = new QSplitter( Qt::Vertical, this );          
    ptexteditSQL        = new QTextEdit( pSplitter );
    ptablewidgetResults       = new QTableWidget( pSplitter );
    ptexteditMessages   = new QTextEdit( pSplitter );

    setCentralWidget( pSplitter );
    resize( 450, 600 );
}

void odbcqg::slotConnectToggle()
{
    if ( pConnection->isConnected() )
        pConnection->doDisconnect();
    else
        pConnection->doConnect( this );
}

void odbcqg::slotConnected()
{
    pactionConnect->setIcon( QIcon( xpmConnected16 ) );
}

void odbcqg::slotDisconnected()
{
    pactionConnect->setIcon( QIcon( xpmDisconnected16 ) );
}

void odbcqg::slotExecute() 
{
    // remove table items...
    ptablewidgetResults->clear();
    // remove table cells...
    ptablewidgetResults->setColumnCount( 0 );
    ptablewidgetResults->setRowCount( 0 );

    //
    pStatement->slotExecute( ptexteditSQL->toPlainText() );
}

void odbcqg::slotResults( ODBCQStatement * ) 
{
    doResultGUIGrid();
}

void odbcqg::slotMessage( ODBCMessage Message ) 
{
    ptexteditMessages->append( ODBCQToQString( Message.getText() ) );
}

void odbcqg::doResultGUIGrid()
{
    SWORD       nCols;

    // GET NUMBER OF COLUMNS RETURNED
    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nCols )) )
        nCols = 0;

    if ( nCols < 0 ) nCols = 0;

    ptablewidgetResults->setRowCount( 0 );
    ptablewidgetResults->setColumnCount( nCols );

    // GET A RESULTS HEADER (column headers)
    doResultGUIGridHeader( nCols );

    // GET A RESULTS BODY (data)
    if ( nCols > 0 )
        doResultGUIGridBody( nCols );
}

void odbcqg::doResultGUIGridHeader( SWORD nColumns )
{
	int			nCol;
	SQLCHAR		szColumnName[101]	= "";	
    QStringList stringlistHeaderLabels;

	for( nCol = 0; nCol < nColumns; nCol++ )
	{
        *szColumnName = '\0';
		pStatement->doColAttribute( nCol + 1, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), 0, 0 );
        stringlistHeaderLabels << (const char*)szColumnName;
	}
    ptablewidgetResults->setHorizontalHeaderLabels( stringlistHeaderLabels );
}

void odbcqg::doResultGUIGridBody( SWORD nColumns )
{
    SQLRETURN      	nReturn             = 0;
    SQLINTEGER      nRow                = 0;
    SQLUSMALLINT    nCol            	= 0;
	SQLLEN          nIndicator;
	char			szColumn[300];

    // for each result record...
    while( SQL_SUCCEEDED( (nReturn = pStatement->doFetch()) ) )
    {
        nRow++;
        // SOME DRIVERS DO NOT RETURN THE ROW COUNT PROPERLY SO EXPAND IF NEED BE 
        if ( ptablewidgetResults->rowCount() < nRow )
            ptablewidgetResults->setRowCount( nRow );

        // PROCESS ALL COLUMNS
        for( nCol = 0; nCol < nColumns; nCol++ )
        {
            nReturn = pStatement->doData( nCol+1, SQL_C_CHAR, (SQLPOINTER)szColumn, sizeof(szColumn)-1, &nIndicator );
            if ( nReturn == SQL_ERROR )
                break;

            if ( SQL_SUCCEEDED( nReturn ) && nIndicator != SQL_NULL_DATA )
            {
                QTableWidgetItem *ptablewidgetitem = new QTableWidgetItem( szColumn );
                ptablewidgetitem->setFlags( Qt::ItemIsSelectable );
                ptablewidgetResults->setItem( nRow - 1, nCol, ptablewidgetitem );
            }
            else
            {
                QTableWidgetItem *ptablewidgetitem = new QTableWidgetItem( "" );
                ptablewidgetitem->setFlags( Qt::ItemIsSelectable );
                ptablewidgetResults->setItem( nRow - 1, nCol, ptablewidgetitem );
            }
        }

    } // while rows
}



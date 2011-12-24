/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DDataManager.h"

#include "DBrowser.h"
#include "DPropWidget.h"
#include "DOutputMessages.h"
#include "DOutputLog.h"
#include "DEdit.h"

#include "ODBCDataManager64.xpm"
#include "Run48.xpm"

DDataManager::DDataManager()
{
    pEdit       = 0;
    pMdiArea    = new QMdiArea( this );
    setCentralWidget( pMdiArea );

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    connect( pMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), SLOT(slotSubWindowActivated(QMdiSubWindow*)) );

    setWindowTitle( tr( "ODBC Data Manager" ) );
    setWindowIcon( QIcon( xpmODBCDataManager64 ) );
}

DDataManager::~DDataManager()
{
    delete ptableviewProperties;
    delete pViewBrowser;
    delete pModelBrowser;
    delete pModelSystem;
    delete pSystem;

    delete pactionQuit;
    delete pactionAbout;
    delete pactionSubmit;
}

void DDataManager::slotSubWindowActivated( QMdiSubWindow *pSubWindow )
{
    if ( pEdit )
    {
        // disconnect it
        disconnect( pactionSubmit, 0, 0, 0 );
        pactionSubmit->setEnabled( false );
        pEdit = 0;
    }

    if ( pSubWindow )
    {
        pEdit = (DEdit*)pSubWindow->widget();
        pEdit->setActionSubmit( pactionSubmit );
    }
}

void DDataManager::slotSelected( const QModelIndex &index )
{
    if ( !pModelBrowser )
        return;
    ODBCModel *pModel = pModelBrowser->getModel( index );

    if ( !pModel )
        return;

    ptableviewProperties->setModel( pModel );
}
void DDataManager::createActions()
{
     pactionQuit = new QAction( tr( "&Quit" ), this );
     pactionQuit->setShortcut( tr( "Ctrl+Q" ) );
     pactionQuit->setStatusTip( tr( "Quit this application" ) );
     connect( pactionQuit, SIGNAL(triggered()), this, SLOT(close()) );

     pactionAbout = new QAction( tr( "&About" ), this );
     pactionAbout->setStatusTip( tr( "Show this application's About box" ) );
     connect( pactionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()) );

     // editor actions...
     pactionSubmit = new QAction( QIcon( xpmRun48 ), tr( "Submit" ), this );
     pactionSubmit->setStatusTip( tr( "submit text to the data source for processing - show any results" ) );
     pactionSubmit->setEnabled( false );
}

void DDataManager::createMenus()
{
    pmenuFile = menuBar()->addMenu( tr( "&File" ) );
    pmenuFile->addAction( pactionQuit );
    
    menuBar()->addSeparator();
    
    pmenuHelp = menuBar()->addMenu( tr( "&Help" ) );
    pmenuHelp->addAction( pactionAbout );
}

void DDataManager::createToolBars()
{
    ptoolbarEditor = addToolBar( tr("Editor") );
    ptoolbarEditor->addAction( pactionSubmit );
}

void DDataManager::createStatusBar()
{
    statusBar()->showMessage( tr( "Ready" ) );
}

void DDataManager::createDockWindows()
{
    QDockWidget *pDockWindow;

    // output dock...
    pDockWindow = new QDockWidget( tr("Output"), this );
    pDockWindow->setAllowedAreas( Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea );
    QTabWidget *pTabWidget = new QTabWidget( pDockWindow );
    pOutputMessages = new DOutputMessages( pTabWidget );
    pOutputLog = new DOutputLog( pTabWidget );
    pTabWidget->addTab( pOutputMessages, "Diagnostic Messages" );
    pTabWidget->addTab( pOutputLog, "Trace" );
    pDockWindow->setWidget( pTabWidget );
    addDockWidget( Qt::BottomDockWidgetArea, pDockWindow );

    // 
    pDockWindow = new QDockWidget( tr("Browser"), this  );
    pDockWindow->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    pViewBrowser        = new ODBCViewBrowser( pDockWindow );
    pSystem             = new ODBCQGSystem();
    pModelSystem        = new ODBCModelSystem( pSystem );
    pModelBrowser       = new ODBCModelBrowser( pModelSystem );

    pViewBrowser->setModel( pModelBrowser );
    pDockWindow->setWidget( pViewBrowser );
    addDockWidget( Qt::LeftDockWidgetArea, pDockWindow );
    connect( pViewBrowser, SIGNAL(clicked( const QModelIndex &)), this, SLOT(slotSelected( const QModelIndex &)) );

    pDockWindow = new QDockWidget( tr("Properties"), this );
    pDockWindow->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    ptableviewProperties = new QTableView( pDockWindow );
    pDelegateCell = new ODBCDelegateCell( this );
    ptableviewProperties->setItemDelegateForColumn ( 1, pDelegateCell );
    ptableviewProperties->setAlternatingRowColors( true );
    pDockWindow->setWidget( ptableviewProperties );
    addDockWidget( Qt::RightDockWidgetArea, pDockWindow );

}



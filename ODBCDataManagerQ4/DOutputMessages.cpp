#include "DOutputMessages.h"

#include "Error48.xpm"
#include "Warning48.xpm"
#include "Information48.xpm"

DOutputMessages::DOutputMessages( QWidget *pwidgetParent )
    : QWidget( pwidgetParent )
{
    playoutMain = new QVBoxLayout;
    playoutMain->setSpacing( 0 );

    // tool bar on top...
    pToolBar = new QToolBar( this );
    playoutMain->addWidget( pToolBar );

    // browser below...
    pTreeWidget = new QTreeWidget( this );
    pTreeWidget->setRootIsDecorated( true );
    QStringList stringlistLabels;
    stringlistLabels << tr("Return Code") << tr("Cursor Row Count") << tr("Dynamic Function") << tr("Dyanmic Function Code") << tr("Number") << tr("Row Count") << tr("Class Origin") << tr("Column Number") << tr("Connection Name") << tr("Message Text") << tr("Native") << tr("Row Number") << tr("Server Name") << tr("SQL State") << tr("Sub Class Origin");
    pTreeWidget->setHeaderLabels( stringlistLabels );
    playoutMain->addWidget( pTreeWidget );

    //
    setLayout( playoutMain );
}

DOutputMessages::~DOutputMessages()
{
}

void DOutputMessages::slotDiagnosticClear()
{
    pTreeWidget->clear();
}

void DOutputMessages::slotDiagnostic( DDiagnostic diagnostic )
{
    if ( diagnostic.bNull )
        return;

    QTreeWidgetItem *pitemParent = new QTreeWidgetItem( pTreeWidget );

    if ( !diagnostic.stringReturnCode.isEmpty() )
    {
        SQLRETURN n = diagnostic.stringReturnCode.toInt();

        if ( n == SQL_ERROR )
            pitemParent->setIcon( 0, QIcon( xpmError48 ) );
        else if ( n == SQL_SUCCESS_WITH_INFO )
            pitemParent->setIcon( 0, QIcon( xpmWarning48 ) );
        else
            pitemParent->setIcon( 0, QIcon( xpmInformation48 ) );
    }

    pitemParent->setText( 0, ODBCStringReturn( diagnostic.stringReturnCode.toInt() ) );
    pitemParent->setText( 2, diagnostic.stringCursorRowCount );
    pitemParent->setText( 3, diagnostic.stringDynamicFunction );
    pitemParent->setText( 4, diagnostic.stringDynamicFunctionCode );
    pitemParent->setText( 5, diagnostic.stringNumber );
    pitemParent->setText( 6, diagnostic.stringRowCount );

    for ( int i = 0; i < diagnostic.listRecords.size(); ++i ) 
    {
        DDiagnosticRecord   record      = diagnostic.listRecords.at( i );
        QTreeWidgetItem *   pitemChild  = new QTreeWidgetItem( pitemParent );

        pitemChild->setText( 1, record.stringMessageText );
        pitemChild->setText( 7, record.stringClassOrigin );
        pitemChild->setText( 8, record.stringColumnNumber );
        pitemChild->setText( 9, record.stringConnectionName );
        pitemChild->setText( 10, record.stringNative );
        pitemChild->setText( 11, record.stringRowNumber );
        pitemChild->setText( 12, record.stringServerName );
        pitemChild->setText( 13, record.stringSQLState );
        pitemChild->setText( 14, record.stringSubClassOrigin );
    }

    pitemParent->setExpanded( true );
}

void DOutputMessages::slotClear()
{
    pTreeWidget->clear();
}



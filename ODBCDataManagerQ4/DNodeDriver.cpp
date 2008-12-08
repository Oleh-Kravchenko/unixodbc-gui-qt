#include "DNodeDriver.h"

#include "DNodeConnection.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Connected48.xpm"
#include "Remove32.xpm"
#include "Driver48.xpm"

DNodeDriver::DNodeDriver( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringDriver )
    : DNode( pNodeWidget, pNode )
{
    this->stringDriver = stringDriver;
    setIcon( 0, QIcon( xpmDriver48 ) );
    setText( 0, stringDriver );

    pactionConnect = new QAction( QIcon( xpmConnected48 ), "Connect", 0 );
    connect( pactionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()) );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );

    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
}

DNodeDriver::~DNodeDriver()
{
    delete pactionConnect;
    delete pactionRemove;
}

void DNodeDriver::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionConnect );
    pToolBar->addAction( pactionRemove );
}

void DNodeDriver::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionConnect );
    pToolBar->removeAction( pactionRemove );
}

void DNodeDriver::slotConnect()
{
    DNodeConnection *pConnection = new DNodeConnection( pNodeWidget, this );
    setExpanded( true );
}

void DNodeDriver::slotRemove()
{
    delete this;
}

void DNodeDriver::doLoadProperties( DPropWidget *pPropWidget )
{
    char    szError[FILENAME_MAX+1];
    DWORD   nError;
    char    szResults[4048];
    char    szValue[501];
    char *  pszKey;
    char *  pszDriver;

    QByteArray bytearray = stringDriver.toLatin1().data();
    pszDriver = bytearray.data();

    if ( SQLGetPrivateProfileString( pszDriver, NULL, NULL, szResults, sizeof( szResults ) - 1, "ODBCINST.INI" ) < 1 )
    {
        SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
        printf( "DNodeDriver: SQLGetPrivateProfileString failed with %s.\n", szError );
        return;
    }
    pszKey = szResults;
    while ( *pszKey )
    {
        SQLGetPrivateProfileString( pszDriver, pszKey, "", szValue, sizeof( szValue ) - 1, "ODBCINST.INI" );

        DNodeAttribute *p = new DNodeAttribute( pPropWidget->getNodeWidget(), pszKey, szValue );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
        pszKey += strlen( pszKey ) + 1;
    }
}

void DNodeDriver::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}



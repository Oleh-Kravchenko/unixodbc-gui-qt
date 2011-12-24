/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeDataSourceNameSystem.h"

#include "DNodeAttribute.h"

#include "DNodeConnection.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Connected48.xpm"
#include "Remove32.xpm"
#include "DataSourceNameSystem48.xpm"

DNodeDataSourceNameSystem::DNodeDataSourceNameSystem( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName )
    : DNode( pNodeWidget, pNode )
{
    this->stringName = stringName;
    setIcon( 0, QIcon( xpmDataSourceNameSystem48 ) );
    setText( 0, stringName );

    pactionConnect = new QAction( QIcon( xpmConnected48 ), "Connect", 0 );
    connect( pactionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()) );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );

    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
}

DNodeDataSourceNameSystem::~DNodeDataSourceNameSystem()
{
    delete pactionConnect;
    delete pactionRemove;
}

void DNodeDataSourceNameSystem::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionConnect );
    pToolBar->addAction( pactionRemove );
}

void DNodeDataSourceNameSystem::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionConnect );
    pToolBar->removeAction( pactionRemove );
}

void DNodeDataSourceNameSystem::slotConnect()
{
    DNodeConnection *pConnection = new DNodeConnection( pNodeWidget, this );

    setExpanded( true );
}

void DNodeDataSourceNameSystem::slotRemove()
{
    delete this;
}

void DNodeDataSourceNameSystem::doLoadProperties( DPropWidget *pPropWidget )
{
    char    szError[FILENAME_MAX+1];
    DWORD   nError;
    char    szResults[4048];
    char    szValue[501];
    char *  pszKey;
    char *  pszName;
    UWORD   nConfigMode;

    QByteArray bytearray = stringName.toLatin1().data();
    pszName = bytearray.data();

    SQLGetConfigMode( &nConfigMode );
    SQLSetConfigMode( ODBC_SYSTEM_DSN );

    if ( SQLGetPrivateProfileString( pszName, NULL, NULL, szResults, sizeof( szResults ) - 1, "ODBC.INI" ) < 1 )
    {
        SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
        printf( "DNodeDataSourceNameSystem: SQLGetPrivateProfileString failed with %s.\n", szError );
        SQLSetConfigMode( nConfigMode );
        return;
    }
    pszKey = szResults;
    while ( *pszKey )
    {
        SQLGetPrivateProfileString( pszName, pszKey, "", szValue, sizeof( szValue ) - 1, "ODBC.INI" );

        DNodeAttribute *p = new DNodeAttribute( pPropWidget->getNodeWidget(), pszKey, szValue );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
        pszKey += strlen( pszKey ) + 1;
    }
    SQLSetConfigMode( nConfigMode );
}

void DNodeDataSourceNameSystem::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}




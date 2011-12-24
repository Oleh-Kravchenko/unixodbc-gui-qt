/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeDataSourceNameUser.h"

#include "DNodeConnection.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Connected48.xpm"
#include "Remove32.xpm"
#include "DataSourceNameUser48.xpm"

DNodeDataSourceNameUser::DNodeDataSourceNameUser( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName )
    : DNode( pNodeWidget, pNode )
{
    this->stringName = stringName;
    setIcon( 0, QIcon( xpmDataSourceNameUser48 ) );
    setText( 0, stringName );

    pactionConnect = new QAction( QIcon( xpmConnected48 ), "Connect", 0 );
    connect( pactionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()) );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );

    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
}

DNodeDataSourceNameUser::~DNodeDataSourceNameUser()
{
    delete pactionConnect;
    delete pactionRemove;
}

void DNodeDataSourceNameUser::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionConnect );
    pToolBar->addAction( pactionRemove );
}

void DNodeDataSourceNameUser::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionConnect );
    pToolBar->removeAction( pactionRemove );
}

void DNodeDataSourceNameUser::slotConnect()
{
    // prompt here...

    // create connect node...
    {
        DNodeConnection *pConnection = new DNodeConnection( pNodeWidget, this );
    }
/*
    QWidget *pwidgetEditorParent = getEditorParent();
    if ( pwidgetEditorParent && pwidgetEditorParent->inherits( "QMdiArea" ) )
    {
        QLabel *p = new QLabel( stringName, pwidgetEditorParent );
        ((QMdiArea*)pwidgetEditorParent)->addSubWindow( p );
        p->show();
    }
    else
    {
        QLabel *p = new QLabel( stringName, pwidgetEditorParent );
        p->show();
    }
*/

    setExpanded( true );
}

void DNodeDataSourceNameUser::slotRemove()
{
    delete this;
}

void DNodeDataSourceNameUser::doLoadProperties( DPropWidget *pPropWidget )
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
    SQLSetConfigMode( ODBC_USER_DSN );

    if ( SQLGetPrivateProfileString( pszName, NULL, NULL, szResults, sizeof( szResults ) - 1, "ODBC.INI" ) < 1 )
    {
        SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
        printf( "DNodeDataSourceNameUser: SQLGetPrivateProfileString failed with %s.\n", szError );
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

void DNodeDataSourceNameUser::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}



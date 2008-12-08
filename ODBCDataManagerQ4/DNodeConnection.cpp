#include "DNodeConnection.h"

#include "DNodeStatement.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Connected48.xpm"
#include "Disconnected48.xpm"
#include "SQL48.xpm"

DNodeConnection::DNodeConnection( DNodeWidget *pNodeWidget, DNodeDriver *pNode )
    : DNode( pNodeWidget, pNode )
{
    doInit();
}

DNodeConnection::DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameFile *pNode )
    : DNode( pNodeWidget, pNode )
{
    doInit();
}

DNodeConnection::DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameSystem *pNode )
    : DNode( pNodeWidget, pNode )
{
    doInit();
}

DNodeConnection::DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameUser *pNode )
    : DNode( pNodeWidget, pNode )
{
    doInit();
}

DNodeConnection::~DNodeConnection()
{
    if ( hDbc )
        SQLFreeHandle( SQL_HANDLE_DBC, hDbc );
    delete pactionConnectToggle;
    delete pactionNewStatement;
}

SQLHDBC DNodeConnection::getConnection()
{
    isAllocated( true );
    return hDbc;
}

void DNodeConnection::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionConnectToggle );
    pToolBar->addAction( pactionNewStatement );
}

void DNodeConnection::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionConnectToggle );
    pToolBar->removeAction( pactionNewStatement );
}

void DNodeConnection::doLoadProperties( DPropWidget *pPropWidget )
{
    doDiagnosticClearSignal();

    if ( !isAllocated( true ) )
        return;

    DNode *pParent = (DNode*)(((QObject*)this)->parent());

    if ( QString( pParent->metaObject()->className() ) == "DNodeDriver" )
    {
        // for SQLDriverConnect...
        DNodeAttribute *p;

        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "Connection String", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
    }
    else
    {
        // for SQLConnect...
        DNodeAttribute *p;

        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "User Name", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "Authentication", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
    }

    // dbc attributes...
    {
        SQLRETURN       nReturn;
        DNodeAttribute *p;
        SQLUINTEGER     nUnsignedInteger;
        SQLINTEGER      nInteger;
        char            sz[256];
        SQLHWND         hWnd;

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_ACCESS_MODE, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ACCESS_MODE", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ACCESS_MODE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_ASYNC_ENABLE, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ASYNC_ENABLE", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ASYNC_ENABLE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_AUTO_IPD, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_AUTO_IPD", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_AUTO_IPD", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_AUTOCOMMIT, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_OUTPUT_NTS", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_OUTPUT_NTS", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        if ( isConnected() )
        {
            nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_CONNECTION_DEAD, &nUnsignedInteger, 0, 0 ); 
            if ( nReturn == SQL_SUCCESS ) 
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_DEAD", QString::number( nUnsignedInteger ) );
            }
            else
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_DEAD", "<unknown>" );
                if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
            }
        }
        else
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_DEAD", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_CONNECTION_TIMEOUT, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_TIMEOUT", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_TIMEOUT", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        if ( isConnected() )
        {
            nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_CURRENT_CATALOG, sz, sizeof( sz ), 0 ); 
            if ( nReturn == SQL_SUCCESS ) 
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURRENT_CATALOG", ( nReturn == SQL_SUCCESS ? sz : "" ) );
            }
            else
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURRENT_CATALOG", "<unknown>" );
                if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
            }
        }
        else
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURRENT_CATALOG", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_LOGIN_TIMEOUT, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_LOGIN_TIMEOUT", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_LOGIN_TIMEOUT", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_METADATA_ID, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_METADATA_ID", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_METADATA_ID", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_ODBC_CURSORS, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ODBC_CURSORS", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ODBC_CURSORS", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_PACKET_SIZE, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PACKET_SIZE", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PACKET_SIZE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_QUIET_MODE, &hWnd, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_QUIET_MODE", QString::number( (long)hWnd ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_QUIET_MODE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_TRACE, &nUnsignedInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRACE", QString::number( nUnsignedInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRACE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_TRACEFILE, sz, sizeof( sz ), 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRACEFILE", sz );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRACEFILE", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        if ( isConnected() )
        {
            nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_TRANSLATE_LIB, sz, sizeof( sz ), 0 ); 
            if ( nReturn == SQL_SUCCESS ) 
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_LIB", sz );
            }
            else
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_LIB", "<unknown>" );
                if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
            }
        }
        else
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_LIB", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        if ( isConnected() )
        {
            nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_TRANSLATE_OPTION, &nInteger, 0, 0 ); 
            if ( nReturn == SQL_SUCCESS ) 
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_OPTION", QString::number( nInteger ) );
            }
            else
            {
                p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_OPTION", "<unknown>" );
                if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
            }
        }
        else
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TRANSLATE_OPTION", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_TXN_ISOLATION, &nInteger, 0, 0 ); 
        if ( nReturn == SQL_SUCCESS ) 
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TXN_ISOLATION", QString::number( nInteger ) );
        }
        else
        {
            p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_TXN_ISOLATION", "<unknown>" );
            if ( nReturn != SQL_NO_DATA ) doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        }
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
    }
}

void DNodeConnection::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}

bool DNodeConnection::isAllocated( bool bEnsure )
{
    if ( hDbc )
        return true;

    if ( bEnsure )
    {
        SQLRETURN nReturn = SQLAllocHandle( SQL_HANDLE_DBC, getEnvironment(), &hDbc );
        if ( nReturn != SQL_SUCCESS )
            doDiagnosticSignal( DDiagnostic( SQL_HANDLE_ENV, getEnvironment() ) );
        if ( SQL_SUCCEEDED( nReturn ) )
            return true;
    }

    return false;
}

bool DNodeConnection::isConnected( bool bEnsure )
{
    if ( !isAllocated( bEnsure ) )
        return false;

    if ( bConnected && bEnsure )
    {
        SQLUINTEGER n;
        SQLRETURN   nReturn = SQLGetConnectAttr( hDbc, SQL_ATTR_CONNECTION_DEAD, &n, 0, 0 );
        if ( nReturn != SQL_SUCCESS )
            doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );
        if ( SQL_SUCCEEDED( nReturn ) && n == SQL_CD_FALSE )
            return true;
        SQLDisconnect( hDbc );
    }

    pactionConnectToggle->setText( "Connect" );
    pactionConnectToggle->setIcon( QIcon( xpmConnected48 ) );
    setIcon( 0, QIcon( xpmDisconnected48 ) );

    return false;
}

void DNodeConnection::slotConnectToggle()
{
    if ( !isAllocated( true ) )
        return;

    if ( isConnected( true ) )
    {
        // disconnect...
        SQLRETURN nReturn = SQLDisconnect( hDbc );
        if ( nReturn != SQL_SUCCESS )
            doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );

        if ( !SQL_SUCCEEDED( nReturn ) )
            return;

        pactionConnectToggle->setText( "Connect" );
        pactionConnectToggle->setIcon( QIcon( xpmConnected48 ) );
        setIcon( 0, QIcon( xpmDisconnected48 ) );
    }

    {
        // connect...
        DNode *pParent = (DNode*)(((QObject*)this)->parent());

        if ( QString( pParent->metaObject()->className() ) == "DNodeDriver" )
        {
            if ( !doConnect( (DNodeDriver*)pParent ) )
                return;
        }
        else if ( QString( pParent->metaObject()->className() ) == "DNodeDataSourceNameFile" )
        {
            if ( !doConnect( (DNodeDataSourceNameFile*)pParent ) )
                return;
        }
        else if ( QString( pParent->metaObject()->className() ) == "DNodeDataSourceNameSystem" )
        {
            if ( !doConnect( (DNodeDataSourceNameSystem*)pParent ) )
                return;
        }        
        else if ( QString( pParent->metaObject()->className() ) == "DNodeDataSourceNameUser" )
        {
            if ( !doConnect( (DNodeDataSourceNameUser*)pParent ) )
                return;
        }

        pactionConnectToggle->setText( "Disconnect" );
        pactionConnectToggle->setIcon( QIcon( xpmDisconnected48 ) );
        setIcon( 0, QIcon( xpmConnected48 ) );
        return;
    }

}

void DNodeConnection::slotNewStatement()
{
    if ( !isConnected( true ) )
        return;

    DNodeStatement *pStatement = new DNodeStatement( pNodeWidget, this );
    setExpanded( true );
}

void DNodeConnection::doInit()
{
    hDbc        = NULL;
    bConnected  = false;
    setIcon( 0, QIcon( xpmDisconnected48 ) );
    setText( 0, tr( "Connection" ) );
    pactionConnectToggle = new QAction( QIcon( xpmConnected48 ), "Connect", 0 );
    connect( pactionConnectToggle, SIGNAL(triggered()), this, SLOT(slotConnectToggle()) );
    pactionNewStatement = new QAction( QIcon( xpmSQL48 ), "New Statment", 0 );
    connect( pactionNewStatement, SIGNAL(triggered()), this, SLOT(slotNewStatement()) );
}

bool DNodeConnection::doConnect( DNodeDriver *pNode )
{
    /*
    SQLCHAR szIn[1024];
    SQLCHAR szOut[1024];

    SQLSMALLINT  nConnStrOut;
    SQLUSMALLINT nDriverCompletion = SQL_DRIVER_PROMPT;

    "DRIVER=" + pNode->name();
    SQLDriverConnect( hDbc, 0, szIn, nIn, szOut, nOut, &nOutLen, nDriverCompletion );
    */
    return false;
}

bool DNodeConnection::doConnect( DNodeDataSourceNameFile *pNode )
{
    
    /*
    "FILEDSN=" + pNode->name();
    SQLDriverConnect( hDbc, 0, szIn, nIn, szOut, nOut, &nOutLen, nDriverCompletion );
    */

    return false;
}

bool DNodeConnection::doConnect( DNodeDataSourceNameSystem *pNode )
{
    UWORD nConfigMode = ODBC_BOTH_DSN;

    if ( !isAllocated( true ) )
        return false;

    if ( isConnected( true ) )
        return true;

    SQLGetConfigMode( &nConfigMode );
    SQLSetConfigMode( ODBC_SYSTEM_DSN );

#ifdef UNICODE
    SQLRETURN nReturn = SQLConnect( hDbc, (SQLWCHAR*)pNode->getName().unicode(), pNode->getName().length(), NULL, 0, NULL, 0 );
#else
    SQLRETURN nReturn = SQLConnect( hDbc, (SQLCHAR*)pNode->getName().toLatin1().constData(), pNode->getName().length(), NULL, 0, NULL, 0 );
#endif

    if ( nReturn != SQL_SUCCESS )
        doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );

    bConnected = SQL_SUCCEEDED( nReturn );

    SQLSetConfigMode( nConfigMode );

    return bConnected;
}

bool DNodeConnection::doConnect( DNodeDataSourceNameUser *pNode )
{
    UWORD nConfigMode = ODBC_BOTH_DSN;

    if ( !isAllocated( true ) )
        return false;

    if ( isConnected( true ) )
        return true;

    SQLGetConfigMode( &nConfigMode );
    SQLSetConfigMode( ODBC_USER_DSN );

#ifdef UNICODE
    SQLRETURN nReturn = SQLConnect( hDbc, (SQLWCHAR*)pNode->getName().unicode(), pNode->getName().length(), NULL, 0, NULL, 0 );
#else
    SQLRETURN nReturn = SQLConnect( hDbc, (SQLCHAR*)pNode->getName().toLatin1().constData(), pNode->getName().length(), NULL, 0, NULL, 0 );
#endif

    if ( nReturn != SQL_SUCCESS )
        doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, hDbc ) );

    bConnected = SQL_SUCCEEDED( nReturn );

    SQLSetConfigMode( nConfigMode );

    return bConnected;
}


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "OQEnvironment.h"
#include "OQConnection.h"
#include "OQStatement.h"

OQConnection::OQConnection( OQEnvironment *penvironment )
    : OQHandle( Dbc, penvironment )
{
    setObjectName( "OQConnection" );

    bPromptDriver           = true;
    bPromptDataSourceName   = true;
    bPromptUserID           = true;
    bPromptPassword         = true;
    bConnected              = false;

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(OQMessage)), penvironment, SIGNAL(signalMessage(OQMessage)) );
    connect( this, SIGNAL(signalDiagnostic(OQDiagnostic)), penvironment, SIGNAL(signalDiagnostic(OQDiagnostic)) );
}

OQConnection::~OQConnection()
{
    // increase the chances that cleanup will complete fully
    if ( isConnected() )
        doDisconnect();
}

SQLRETURN OQConnection::setAttrAccessMode( AttrAccessModeTypes nAttrAccessMode )
{
    return setConnectAttr( SQL_ATTR_ACCESS_MODE, (SQLPOINTER)nAttrAccessMode );
}

SQLRETURN OQConnection::setAttrAsyncEnable( AttrAsyncEnableTypes nAttrAsyncEnable )
{
    return setConnectAttr( SQL_ATTR_ASYNC_ENABLE, (SQLPOINTER)nAttrAsyncEnable );
}

SQLRETURN OQConnection::setAttrAutocommit( AttrAutocommitTypes nAttrAutocommit )
{
    return setConnectAttr( SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)nAttrAutocommit );
}

SQLRETURN OQConnection::setAttrConnectionTimeout( SQLUINTEGER nAttrConnectionTimeout )
{
    return setConnectAttr( SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)nAttrConnectionTimeout );
}

SQLRETURN OQConnection::setAttrCurrentCatalog( const QString &stringAttrCurrentCatalog )
{
    return setConnectAttr( SQL_ATTR_CURRENT_CATALOG, stringAttrCurrentCatalog );
}

SQLRETURN OQConnection::setAttrLoginTimeout( SQLUINTEGER nAttrLoginTimeout )
{
    return setConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)nAttrLoginTimeout );
}

SQLRETURN OQConnection::setAttrMetadataId( bool bAttrMetadataId )
{
    return setConnectAttr( SQL_ATTR_METADATA_ID, (SQLPOINTER)bAttrMetadataId );
}

SQLRETURN OQConnection::setAttrOdbcCursors( AttrOdbcCursorsTypes nAttrOdbcCursors )
{
    return setConnectAttr( SQL_ATTR_ODBC_CURSORS, (SQLPOINTER)nAttrOdbcCursors );
}

SQLRETURN OQConnection::setAttrPacketSize( SQLUINTEGER nAttrPacketSize )
{
    return setConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)nAttrPacketSize );
}

SQLRETURN OQConnection::setAttrQuietMode( SQLHWND hWnd )
{
    return setConnectAttr( SQL_ATTR_QUIET_MODE, (SQLPOINTER)hWnd );
}

SQLRETURN OQConnection::setAttrTrace( AttrTraceTypes nAttrTrace )
{
    return setConnectAttr( SQL_ATTR_TRACE, (SQLPOINTER)nAttrTrace );
}

SQLRETURN OQConnection::setAttrTracefile( const QString &stringAttrTracefile )
{
    return setConnectAttr( SQL_ATTR_TRACEFILE, stringAttrTracefile );
}

SQLRETURN OQConnection::setAttrTranslateLib( const QString &stringAttrTranslateLib )
{
    return setConnectAttr( SQL_ATTR_TRANSLATE_LIB, stringAttrTranslateLib );
}

SQLRETURN OQConnection::setAttrTranslateOption( SQLUINTEGER nAttrTranslateOption )
{
    return setConnectAttr( SQL_ATTR_TRANSLATE_OPTION, (SQLPOINTER)nAttrTranslateOption );
}

SQLRETURN OQConnection::setAttrTxnIsolation( SQLUINTEGER nAttrTxnIsolation )
{
    return setConnectAttr( SQL_ATTR_TXN_ISOLATION, (SQLPOINTER)nAttrTxnIsolation );
}

OQConnection::AttrAccessModeTypes OQConnection::getAttrAccessMode( SQLRETURN *pn )
{
    AttrAccessModeTypes nAttrAccessMode = ModeReadWrite;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ACCESS_MODE, &nAttrAccessMode );
    if ( pn ) *pn = nReturn;
    return nAttrAccessMode;
}

OQConnection::AttrAsyncEnableTypes OQConnection::getAttrAsyncEnable( SQLRETURN *pn ) 
{
    AttrAsyncEnableTypes nAttrAsyncEnable = AsyncEnableOff;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ASYNC_ENABLE, &nAttrAsyncEnable );
    if ( pn ) *pn = nReturn;
    return nAttrAsyncEnable;
}

bool OQConnection::getAttrAutoIpd( SQLRETURN *pn )
{
    bool bAttrAutoIpd = false;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_AUTO_IPD, &bAttrAutoIpd );
    if ( pn ) *pn = nReturn;
    return bAttrAutoIpd;
}

OQConnection::AttrAutocommitTypes OQConnection::getAttrAutocommit( SQLRETURN *pn )
{
    AttrAutocommitTypes nAttrAutocommit = AutocommitOn;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_AUTOCOMMIT, &nAttrAutocommit );
    if ( pn ) *pn = nReturn;
    return nAttrAutocommit;
}

bool OQConnection::getAttrConnectionDead( SQLRETURN *pn )
{
    bool bAttrConnectionDead = true;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_CONNECTION_DEAD, &bAttrConnectionDead );
    if ( pn ) *pn = nReturn;
    return bAttrConnectionDead;
}

SQLUINTEGER OQConnection::getAttrConnectionTimeout( SQLRETURN *pn )
{
    SQLUINTEGER nAttrConnectionTimeout = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_CONNECTION_DEAD, &nAttrConnectionTimeout );
    if ( pn ) *pn = nReturn;
    return nAttrConnectionTimeout;
}

QString OQConnection::getAttrCurrentCatalog( SQLRETURN *pn )
{
    QString     stringValue;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_CURRENT_CATALOG, &stringValue );

    if ( pn ) *pn = nReturn;

    return stringValue;
}

SQLUINTEGER OQConnection::getAttrLoginTimeout( SQLRETURN *pn )
{
    SQLUINTEGER nAttrLoginTimeout = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, &nAttrLoginTimeout );
    if ( pn ) *pn = nReturn;
    return nAttrLoginTimeout;
}

bool OQConnection::getAttrMetadataId( SQLRETURN *pn )
{
    bool bAttrMetadataId = true;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_METADATA_ID, &bAttrMetadataId );
    if ( pn ) *pn = nReturn;
    return bAttrMetadataId;
}

OQConnection::AttrOdbcCursorsTypes OQConnection::getAttrOdbcCursors( SQLRETURN *pn )
{
    AttrOdbcCursorsTypes nAttrOdbcCursors = CurUseDriver;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ODBC_CURSORS, &nAttrOdbcCursors );
    if ( pn ) *pn = nReturn;
    return nAttrOdbcCursors;
}

SQLUINTEGER OQConnection::getAttrPacketSize( SQLRETURN *pn )
{
    SQLUINTEGER nAttrPacketSize = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_PACKET_SIZE, &nAttrPacketSize );
    if ( pn ) *pn = nReturn;
    return nAttrPacketSize;
}

SQLHWND OQConnection::getAttrQuietMode( SQLRETURN *pn )
{
    SQLHWND hWnd = NULL;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_QUIET_MODE, &hWnd );
    if ( pn ) *pn = nReturn;
    return hWnd;
}

OQConnection::AttrTraceTypes OQConnection::getAttrTrace( SQLRETURN *pn )
{
    AttrTraceTypes nAttrTrace = OptTraceOff;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TRACE, &nAttrTrace );
    if ( pn ) *pn = nReturn;
    return nAttrTrace;
}

QString OQConnection::getAttrTracefile( SQLRETURN *pn )
{
    QString     stringValue;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_TRACEFILE, &stringValue );

    if ( pn ) *pn = nReturn;

    return stringValue;
}

QString OQConnection::getAttrTranslateLib( SQLRETURN *pn )
{
    QString     stringValue;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_TRANSLATE_LIB, &stringValue );

    if ( pn ) *pn = nReturn;

    return stringValue;
}

SQLUINTEGER OQConnection::getAttrTranslateOption( SQLRETURN *pn )
{
    SQLUINTEGER nAttrTranslateOption = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TRANSLATE_OPTION, &nAttrTranslateOption );
    if ( pn ) *pn = nReturn;
    return nAttrTranslateOption;
}

SQLUINTEGER OQConnection::getAttrTxnIsolation( SQLRETURN *pn )
{
    SQLUINTEGER nAttrTxnIsolation = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TXN_ISOLATION, &nAttrTxnIsolation );
    if ( pn ) *pn = nReturn;
    return nAttrTxnIsolation;
}

/*!
    getExecute
    
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getExecute( const QString &stringStatement )
{
    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    OQStatement *   pStatement  = new OQStatement( this );
    SQLRETURN       nReturn     = pStatement->slotExecDirect( stringStatement );

    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getCatalogs
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getCatalogs()
{
    OQStatement *    pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doTables( SQL_ALL_CATALOGS, QString::null, QString::null );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getSchemas
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getSchemas( const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doTables( stringCatalog, SQL_ALL_SCHEMAS, QString::null );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getTables
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getTables( const QString &stringSchema, const QString &stringCatalog, const QString &stringType )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doTables( stringCatalog, stringSchema, SQL_ALL_SCHEMAS, stringType );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getViews
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getViews( const QString &stringSchema, const QString &stringCatalog, const QString &stringType )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doTables( stringCatalog, stringSchema, SQL_ALL_SCHEMAS, stringType );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getColumns
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getColumns.
*/
OQStatement *OQConnection::getColumns( const QString &stringTable, const QString &stringSchema, const QString &stringCatalog, const QString &stringType )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doColumns( stringCatalog, stringSchema, stringTable, stringType );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getIndexs
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getStatistics.
*/
OQStatement *OQConnection::getIndexs( const QString &stringTable, const QString &stringSchema, const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doStatistics( stringCatalog, stringSchema, stringTable );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getPrimaryKey
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getPrimaryKey.
*/
OQStatement *OQConnection::getPrimaryKeys( const QString &stringTable, const QString &stringSchema, const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doPrimaryKeys( stringCatalog, stringSchema, stringTable );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getForeignKeys
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getForeignKeys.
*/
OQStatement *OQConnection::getForeignKeys( const QString &stringTable, const QString &stringSchema, const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doForeignKeys( stringCatalog, stringSchema, stringTable );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getSpecialColumns
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getSpecialColumns.
*/
OQStatement *OQConnection::getSpecialColumns( const QString &stringTable, const QString &stringSchema, const QString &stringCatalog )
{
    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    OQStatement *   pStatement      = new OQStatement( this );
    SQLSMALLINT     nIdentifierType = SQL_BEST_ROWID;
    SQLRETURN       nReturn         = pStatement->doSpecialColumns( nIdentifierType, stringCatalog, stringSchema, stringTable );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getProcedures
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getProcedures.
*/
OQStatement *OQConnection::getProcedures( const QString &stringSchema, const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doProcedures( stringCatalog, stringSchema );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getProcedureColumns
        
    Creates a result set (or NULL if there was an error).
    See OQStatement::getProcedureColumns.
*/
OQStatement *OQConnection::getProcedureColumns( const QString &stringProcedure, const QString &stringSchema, const QString &stringCatalog )
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doProcedureColumns( stringCatalog, stringSchema, stringProcedure );
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    getDataTypes
        
    Creates a result set (or NULL if there was an error).
    See ODBCStatement::getypeInfo.
*/
OQStatement *OQConnection::getDataTypes()
{
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, QString( __FUNCTION__ ), "Not connected." ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doTypeInfo();
    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        delete pStatement;
        pStatement = 0;
    }

    return pStatement;
}

/*!
    doBrowseConnect
    
    Connects to the data source. emits signalConnected() if things work out.
*/
SQLRETURN OQConnection::doBrowseConnect( const QString &stringIn, QString *pstringOut )
{
    SQLTCHAR        szOut[4096];
    SQLSMALLINT     nCharsIn        = SQL_NTS;
    SQLSMALLINT     nCharsOutMax    = 4096;
    SQLSMALLINT     nCharsAvailable = 0;
    SQLRETURN       nReturn         = doBrowseConnect( OQFromQString( stringIn ), nCharsIn, szOut, nCharsOutMax, &nCharsAvailable );

    if ( SQL_SUCCEEDED( nReturn ) || nReturn == SQL_NEED_DATA )
        *pstringOut = OQToQString( szOut );

    return nReturn;
}

/*!
    doConnect
    
    Connects to the data source. emits signalConnected() if things work out.
*/
SQLRETURN OQConnection::doConnect( const QString &stringServerName, const QString &stringUserName, const QString &stringAuthentication )
{
    return doConnect( OQFromQString( stringServerName ), SQL_NTS, OQFromQString( stringUserName ), SQL_NTS, OQFromQString( stringAuthentication ), SQL_NTS );
}

/*!
    doDriverConnect
    
    Connects to the data source. emits signalConnected() if things work out.
*/
SQLRETURN OQConnection::doDriverConnect( SQLHWND hWnd, const QString &stringIn, QString *pstringOut, SQLUSMALLINT nPrompt )
{
    SQLTCHAR        szOut[4096];
    SQLSMALLINT     nCharsIn        = SQL_NTS;
    SQLSMALLINT     nCharsOutMax    = 4096;
    SQLSMALLINT     nCharsAvailable = 0;
    SQLRETURN       nReturn         = doDriverConnect( hWnd, OQFromQString( stringIn ), nCharsIn, szOut, nCharsOutMax, &nCharsAvailable, nPrompt );

    if ( SQL_SUCCEEDED( nReturn ) )
        *pstringOut = OQToQString( szOut );

    return nReturn;
}

/*!
    doDisconnect
    
    Disconnects from data source.
*/
SQLRETURN OQConnection::doDisconnect()
{
    if ( !isAlloc( false ) )
    {
        eventMessage( OQMessage( OQMessage::Error, __FUNCTION__, "Not allocated." ) );
        return SQL_ERROR;
    }
    if ( !isConnected() )
    {
        eventMessage( OQMessage( OQMessage::Error, __FUNCTION__, "Not connected." ) );
        return SQL_ERROR;
    }

    SQLRETURN nReturn = SQLDisconnect( hHandle );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            bConnected = false;
            break;
        case SQL_SUCCESS_WITH_INFO:
            bConnected = false;
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, __FUNCTION__, "SQL_INVALID_HANDLE" ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, __FUNCTION__, "Unexpected SQLRETURN value.", nReturn ) );
            break;
    }

    if ( !isConnected() )
    {
        stringDSN           = QString::null;
        stringUID           = QString::null;
        stringPWD           = QString::null;
        stringConnectString = QString::null;
        emit signalDisconnected();
    }

    return nReturn;
}

bool OQConnection::isConnected()
{
/*
    // SANITY CHECKS
    if ( hHandle == SQL_NULL_HDBC )
        return false;

    // DO IT
    SQLRETURN   nReturn;
    SQLUINTEGER nValue;
    SQLINTEGER  nRetSize;

    nReturn = SQLGetConnectAttr( hHandle, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)(&nValue), SQL_IS_UINTEGER, &nRetSize  );
    if ( nReturn == SQL_SUCCESS )
    {
    }
    else if ( nReturn == SQL_SUCCESS_WITH_INFO )
    {
        doErrors();
    }
    else
    {
        // Lets not echo out the errors here and instead assume its because the
        // hHandle was never connected or because this feature has not been implemented
        // by the driver.
        // doErrors();
        return bConnected; // just use our state
    }

    // synch our connect state with the driver state
    if ( nValue == SQL_CD_TRUE )
    {
        if ( !bConnected )
            bConnected = true;
    }
    else
    {
        if ( bConnected )
            bConnected = false;
    }
*/
    return bConnected;
}

SQLRETURN OQConnection::setConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLSetConnectAttr( hHandle, nAttribute, pValue, 0 );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN OQConnection::setConnectAttr( SQLINTEGER nAttribute, const QString &stringValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLSetConnectAttr( hHandle, nAttribute, OQFromQString( stringValue ), SQL_NTS );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN OQConnection::getConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetConnectAttr( hHandle, nAttribute, pValue, 0, NULL  );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN OQConnection::getConnectAttr( SQLINTEGER nAttribute, QString *pValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLTCHAR    szValue[256];
    SQLINTEGER  nLength = 256;
    SQLINTEGER  nRetSize;
    SQLRETURN   nReturn = SQLGetConnectAttr( hHandle, nAttribute, szValue, nLength, &nRetSize  );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            *pValue = OQToQString( szValue );
            break;
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            *pValue = OQToQString( szValue );
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN OQConnection::doBrowseConnect( SQLTCHAR *pszInConnectionString, SQLSMALLINT nStringLength1, SQLTCHAR *pszOutConnectionString, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength2Ptr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLBrowseConnect( hHandle, pszInConnectionString, nStringLength1, pszOutConnectionString, nBufferLength, pnStringLength2Ptr );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            bConnected = true;
            break;
        case SQL_SUCCESS_WITH_INFO:
            bConnected = true;
            eventDiagnostic();
            break;
        case SQL_NEED_DATA:
            return nReturn;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    if ( isConnected() )
        emit signalConnected();

    return nReturn;
}

SQLRETURN OQConnection::doConnect( const SQLTCHAR *pszDSN, SQLSMALLINT nLength1, const SQLTCHAR *pszUID, SQLSMALLINT nLength2, const SQLTCHAR *pszPWD, SQLSMALLINT nLength3 )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    // DO IT
    SQLRETURN nReturn = SQLConnect( hHandle, (SQLTCHAR*)pszDSN, nLength1, (SQLTCHAR*)pszUID, nLength2, (SQLTCHAR*)pszPWD, nLength3 );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            bConnected = true;
            break;
        case SQL_SUCCESS_WITH_INFO:
            bConnected = true;
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    if ( isConnected() )
    {
        stringDSN = OQToQString( pszDSN );
        stringUID = OQToQString( pszUID );
        stringPWD = OQToQString( pszPWD );
        emit signalConnected();
    }

    return nReturn;
}

SQLRETURN OQConnection::doDriverConnect( SQLHWND hWnd, SQLTCHAR *pszIn, SQLSMALLINT nLengthIn, SQLTCHAR *pszOut, SQLSMALLINT nLengthOut, SQLSMALLINT *pnLengthOut, SQLUSMALLINT nPrompt )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLDriverConnect( hHandle, hWnd, pszIn, nLengthIn, pszOut, nLengthOut, pnLengthOut, nPrompt );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            bConnected = true;
            break;
        case SQL_SUCCESS_WITH_INFO:
            bConnected = true;
            eventDiagnostic();
            break;
        case SQL_NEED_DATA:
            return nReturn;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    if ( isConnected() )
        emit signalConnected();

    return nReturn;
}

SQLRETURN OQConnection::doGetInfo( SQLUSMALLINT nInfoType, SQLPOINTER pInfoValue, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetInfo( hHandle, nInfoType, pInfoValue, nBufferLength, pnStringLength );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}



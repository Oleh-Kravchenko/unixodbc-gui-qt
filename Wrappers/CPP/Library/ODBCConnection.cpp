/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCConnection.h"
#include "ODBCEnvironment.h"

ODBCConnection::ODBCConnection( ODBCEnvironment *pEnvironment )
    : ODBCHandle( ODBCHandle::Dbc, pEnvironment )
{
    bConnected = false;
}

ODBCConnection::~ODBCConnection()
{
    // increase the chances that cleanup will complete fully
    if ( isConnected() )
        doDisconnect();
}

SQLRETURN ODBCConnection::setAttrAccessMode( AttrAccessModeTypes nAttrAccessMode )
{
    return setConnectAttr( SQL_ATTR_ACCESS_MODE, (SQLPOINTER)nAttrAccessMode, 0 );
}

SQLRETURN ODBCConnection::setAttrAsyncEnable( AttrAsyncEnableTypes nAttrAsyncEnable )
{
    return setConnectAttr( SQL_ATTR_ASYNC_ENABLE, (SQLPOINTER)nAttrAsyncEnable, 0 );
}

SQLRETURN ODBCConnection::setAttrAutocommit( AttrAutocommitTypes nAttrAutocommit )
{
    return setConnectAttr( SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)nAttrAutocommit, 0 );
}

SQLRETURN ODBCConnection::setAttrConnectionTimeout( SQLUINTEGER nAttrConnectionTimeout )
{
    return setConnectAttr( SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)nAttrConnectionTimeout, 0 );
}

SQLRETURN ODBCConnection::setAttrCurrentCatalog( ODBCCHAR *pszAttrCurrentCatalog )
{
    return setConnectAttr( SQL_ATTR_CURRENT_CATALOG, (SQLPOINTER)pszAttrCurrentCatalog, SQL_NTS );
}

SQLRETURN ODBCConnection::setAttrLoginTimeout( SQLUINTEGER nAttrLoginTimeout )
{
    return setConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)nAttrLoginTimeout, 0 );
}

SQLRETURN ODBCConnection::setAttrMetadataId( bool bAttrMetadataId )
{
    return setConnectAttr( SQL_ATTR_METADATA_ID, (SQLPOINTER)bAttrMetadataId, 0 );
}

SQLRETURN ODBCConnection::setAttrOdbcCursors( AttrOdbcCursorsTypes nAttrOdbcCursors )
{
    return setConnectAttr( SQL_ATTR_ODBC_CURSORS, (SQLPOINTER)nAttrOdbcCursors, 0 );
}

SQLRETURN ODBCConnection::setAttrPacketSize( SQLUINTEGER nAttrPacketSize )
{
    return setConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)nAttrPacketSize, 0 );
}

SQLRETURN ODBCConnection::setAttrQuietMode( SQLHWND hWnd )
{
    return setConnectAttr( SQL_ATTR_QUIET_MODE, (SQLPOINTER)hWnd, 0 );
}

SQLRETURN ODBCConnection::setAttrTrace( AttrTraceTypes nAttrTrace )
{
    return setConnectAttr( SQL_ATTR_TRACE, (SQLPOINTER)nAttrTrace, 0 );
}

SQLRETURN ODBCConnection::setAttrTracefile( ODBCCHAR *pszAttrTracefile )
{
    return setConnectAttr( SQL_ATTR_TRACEFILE, (SQLPOINTER)pszAttrTracefile, SQL_NTS );
}

SQLRETURN ODBCConnection::setAttrTranslateLib( ODBCCHAR *pszAttrTranslateLib )
{
    return setConnectAttr( SQL_ATTR_TRANSLATE_LIB, (SQLPOINTER)pszAttrTranslateLib, SQL_NTS );
}

SQLRETURN ODBCConnection::setAttrTranslateOption( SQLUINTEGER nAttrTranslateOption )
{
    return setConnectAttr( SQL_ATTR_TRANSLATE_OPTION, (SQLPOINTER)nAttrTranslateOption, 0 );
}

SQLRETURN ODBCConnection::setAttrTxnIsolation( SQLUINTEGER nAttrTxnIsolation )
{
    return setConnectAttr( SQL_ATTR_TXN_ISOLATION, (SQLPOINTER)nAttrTxnIsolation, 0 );
}

SQLRETURN ODBCConnection::setConnectAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    return setConnectAttr( nAttribute, pValue, nStringLength );
}

SQLRETURN ODBCConnection::setConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLSetConnectAttr( getHandle(), nAttribute, pValue, nStringLength );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

ODBCConnection::AttrAccessModeTypes ODBCConnection::getAttrAccessMode( SQLRETURN *pn )
{
    AttrAccessModeTypes nAttrAccessMode = ModeReadWrite;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ACCESS_MODE, &nAttrAccessMode, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrAccessMode;
}

ODBCConnection::AttrAsyncEnableTypes ODBCConnection::getAttrAsyncEnable( SQLRETURN *pn ) 
{
    AttrAsyncEnableTypes nAttrAsyncEnable = AsyncEnableOff;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ASYNC_ENABLE, &nAttrAsyncEnable, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrAsyncEnable;
}

bool ODBCConnection::getAttrAutoIpd( SQLRETURN *pn )
{
    bool bAttrAutoIpd = false;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_AUTO_IPD, &bAttrAutoIpd, 0, NULL );
    if ( pn ) *pn = nReturn;
    return bAttrAutoIpd;
}

ODBCConnection::AttrAutocommitTypes ODBCConnection::getAttrAutocommit( SQLRETURN *pn )
{
    AttrAutocommitTypes nAttrAutocommit = AutocommitOn;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_AUTOCOMMIT, &nAttrAutocommit, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrAutocommit;
}

bool ODBCConnection::getAttrConnectionDead( SQLRETURN *pn )
{
    bool bAttrConnectionDead = true;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_CONNECTION_DEAD, &bAttrConnectionDead, 0, NULL );
    if ( pn ) *pn = nReturn;
    return bAttrConnectionDead;
}

SQLUINTEGER ODBCConnection::getAttrConnectionTimeout( SQLRETURN *pn )
{
    SQLUINTEGER nAttrConnectionTimeout = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_CONNECTION_DEAD, &nAttrConnectionTimeout, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrConnectionTimeout;
}

ODBCCHAR *ODBCConnection::getAttrCurrentCatalog( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn )
{
    SQLINTEGER  nCharsAvailable;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_CURRENT_CATALOG, psz, nCharsMax, &nCharsAvailable );
    if ( pn ) *pn = nReturn;
    return psz;
}

SQLUINTEGER ODBCConnection::getAttrLoginTimeout( SQLRETURN *pn )
{
    SQLUINTEGER nAttrLoginTimeout = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, &nAttrLoginTimeout, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrLoginTimeout;
}

bool ODBCConnection::getAttrMetadataId( SQLRETURN *pn )
{
    bool bAttrMetadataId = true;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_METADATA_ID, &bAttrMetadataId, 0, NULL );
    if ( pn ) *pn = nReturn;
    return bAttrMetadataId;
}

ODBCConnection::AttrOdbcCursorsTypes ODBCConnection::getAttrOdbcCursors( SQLRETURN *pn )
{
    AttrOdbcCursorsTypes nAttrOdbcCursors = CurUseDriver;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_ODBC_CURSORS, &nAttrOdbcCursors, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrOdbcCursors;
}

SQLUINTEGER ODBCConnection::getAttrPacketSize( SQLRETURN *pn )
{
    SQLUINTEGER nAttrPacketSize = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_PACKET_SIZE, &nAttrPacketSize, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrPacketSize;
}

SQLHWND ODBCConnection::getAttrQuietMode( SQLRETURN *pn )
{
    SQLHWND hWnd = NULL;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_QUIET_MODE, &hWnd, 0, NULL );
    if ( pn ) *pn = nReturn;
    return hWnd;
}

ODBCConnection::AttrTraceTypes ODBCConnection::getAttrTrace( SQLRETURN *pn )
{
    AttrTraceTypes nAttrTrace = OptTraceOff;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TRACE, &nAttrTrace, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrTrace;
}

ODBCCHAR *ODBCConnection::getAttrTracefile( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn )
{
    SQLINTEGER  nCharsAvailable;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_TRACEFILE, (SQLPOINTER)psz, nCharsMax, &nCharsAvailable );
    if ( pn ) *pn = nReturn;
    return psz;
}

ODBCCHAR *ODBCConnection::getAttrTranslateLib( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn )
{
    SQLINTEGER  nCharsAvailable;
    SQLRETURN   nReturn = getConnectAttr( SQL_ATTR_TRANSLATE_LIB, psz, nCharsMax, &nCharsAvailable );
    if ( pn ) *pn = nReturn;
    return psz;
}

SQLUINTEGER ODBCConnection::getAttrTranslateOption( SQLRETURN *pn )
{
    SQLUINTEGER nAttrTranslateOption = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TRANSLATE_OPTION, &nAttrTranslateOption, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrTranslateOption;
}

SQLUINTEGER ODBCConnection::getAttrTxnIsolation( SQLRETURN *pn )
{
    SQLUINTEGER nAttrTxnIsolation = 0;
    SQLRETURN nReturn = getConnectAttr( SQL_ATTR_TXN_ISOLATION, &nAttrTxnIsolation, 0, NULL );
    if ( pn ) *pn = nReturn;
    return nAttrTxnIsolation;
}

SQLRETURN ODBCConnection::getAttrAccessMode( AttrAccessModeTypes *pn )
{
    return getConnectAttr( SQL_ATTR_ACCESS_MODE, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrAsyncEnable( AttrAsyncEnableTypes *pn )
{
    return getConnectAttr( SQL_ATTR_ASYNC_ENABLE, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getgetAttrAutoIpd( bool *pb )
{
    return getConnectAttr( SQL_ATTR_AUTO_IPD, pb, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrAutocommit( AttrAutocommitTypes *pn )
{
    return getConnectAttr( SQL_ATTR_AUTOCOMMIT, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrConnectionDead( bool *pb )
{
    return getConnectAttr( SQL_ATTR_CONNECTION_DEAD, pb, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrConnectionTimeout( SQLUINTEGER *pn )
{
    return getConnectAttr( SQL_ATTR_CONNECTION_DEAD, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrCurrentCatalog( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn )
{
    return getConnectAttr( SQL_ATTR_CURRENT_CATALOG, psz, nCharsMax, pnCharsToReturn );
}

SQLRETURN ODBCConnection::getAttrLoginTimeout( SQLUINTEGER *pn )
{
    return getConnectAttr( SQL_ATTR_LOGIN_TIMEOUT, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrMetadataId( bool *pb )
{
    return getConnectAttr( SQL_ATTR_METADATA_ID, pb, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrOdbcCursors( AttrOdbcCursorsTypes *pn )
{
    return getConnectAttr( SQL_ATTR_ODBC_CURSORS, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrPacketSize( SQLUINTEGER *pn )
{
    return getConnectAttr( SQL_ATTR_PACKET_SIZE, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrQuietMode( SQLHWND *ph )
{
    return getConnectAttr( SQL_ATTR_QUIET_MODE, ph, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrTrace( AttrTraceTypes *pn )
{
    return getConnectAttr( SQL_ATTR_TRACE, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrTracefile( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn )
{
    return getConnectAttr( SQL_ATTR_TRACEFILE, psz, nCharsMax, pnCharsToReturn );
}

SQLRETURN ODBCConnection::getAttrTranslateLib( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn )
{
    return getConnectAttr( SQL_ATTR_TRANSLATE_LIB, psz, nCharsMax, pnCharsToReturn );
}

SQLRETURN ODBCConnection::getAttrTranslateOption( SQLUINTEGER *pn )
{
    return getConnectAttr( SQL_ATTR_TRANSLATE_OPTION, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getAttrTxnIsolation( SQLUINTEGER *pn )
{
    return getConnectAttr( SQL_ATTR_TXN_ISOLATION, pn, 0, NULL );
}

SQLRETURN ODBCConnection::getConnectAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nLength, SQLINTEGER *pnRetSize )
{
    return getConnectAttr( nAttribute, pValue, nLength, pnRetSize );
}

SQLRETURN ODBCConnection::getConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nLength, SQLINTEGER *pnRetSize  )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetConnectAttr( getHandle(), nAttribute, pValue, nLength, pnRetSize  );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

ODBCEnvironment *ODBCConnection::getEnvironment() 
{ 
    return (ODBCEnvironment*)phandleParent;
}

SQLRETURN ODBCConnection::doConnect( const ODBCCHAR *pszDSN, SQLSMALLINT nLength1, const ODBCCHAR *pszUID, SQLSMALLINT nLength2, const ODBCCHAR *pszPWD, SQLSMALLINT nLength3 )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    // DO IT
    SQLRETURN nReturn = SQLConnect( getHandle(), (SQLTCHAR*)pszDSN, nLength1, (SQLTCHAR*)pszUID, nLength2, (SQLTCHAR*)pszPWD, nLength3 );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN ODBCConnection::doDriverConnect( SQLHWND hWnd, ODBCCHAR *pszIn, SQLSMALLINT nLengthIn, ODBCCHAR *pszOut, SQLSMALLINT nLengthOut, SQLSMALLINT *pnLengthOut, SQLUSMALLINT nPrompt )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLDriverConnect( getHandle(), hWnd, pszIn, nLengthIn, pszOut, nLengthOut, pnLengthOut, nPrompt );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN ODBCConnection::doBrowseConnect( ODBCCHAR *pszInConnectionString, SQLSMALLINT nStringLength1, ODBCCHAR *pszOutConnectionString, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength2Ptr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLBrowseConnect( getHandle(), pszInConnectionString, nStringLength1, pszOutConnectionString, nBufferLength, pnStringLength2Ptr );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN ODBCConnection::doDisconnect()
{
    if ( !isAlloc( false ) )
    {
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not allocated.") ) );
        return SQL_ERROR;
    }
    if ( !isConnected() )
    {
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
        return SQL_ERROR;
    }

    SQLRETURN nReturn = SQLDisconnect( getHandle() );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

SQLRETURN ODBCConnection::doGetInfo( SQLUSMALLINT nInfoType, SQLPOINTER pInfoValue, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetInfo( getHandle(), nInfoType, pInfoValue, nBufferLength, pnStringLength );
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
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

bool ODBCConnection::isConnected()
{
/*
    // SANITY CHECKS
    if ( getHandle() == SQL_NULL_HDBC )
        return false;

    // DO IT
    SQLRETURN   nReturn;
    SQLUINTEGER nValue;
    SQLINTEGER  nRetSize;

    nReturn = SQLGetConnectAttr( getHandle(), SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)(&nValue), SQL_IS_UINTEGER, &nRetSize  );
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
        // getHandle() was never connected or because this feature has not been implemented
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



/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCCONNECTION_H
#define ODBCCONNECTION_H

#include "ODBCHandle.h"
#include "ODBCStatement.h"

class ODBCEnvironment;

/*! 
 * \brief   An ODBC connection.
 *
 *          This class provides a very thin wrapper to SQLHDBC. Using this class is
 *          more convenient for C++ developers (and those with modern code editors) than using 
 *          the SQLHDBC directly. 
 * 
 * \sa      ODBCEnvironment
 *          ODBCStatement
 */
class ODBCConnection : public ODBCHandle
{
    friend class ODBCStatement;
public:
    enum AttributeTypes
    {
        AttrAccessMode          = SQL_ATTR_ACCESS_MODE,         /*!< This can be used to optimize locking strategies, transaction management, or other areas as appropriate to the driver or data source.   */
        AttrAsyncEnable         = SQL_ATTR_ASYNC_ENABLE,        /*!< Specifies whether a function called with a statement on the specified connection is executed asynchronously.                           */
        AttrAutoIpd             = SQL_ATTR_AUTO_IPD,            /*!< ReadOnly. Specifies whether automatic population of the parameter descriptions after a call to prepare statement is supported.         */
        AttrAutocommit          = SQL_ATTR_AUTOCOMMIT,          /*!< Specifies whether to use autocommit or manual-commit mode.                                                                             */
        AttrConnectionDead      = SQL_ATTR_CONNECTION_DEAD,     /*!< ReadOnly. Indicates the state of the connection (or at least the connect/disconnect part of state).                                    */
        AttrConnectionTimeout   = SQL_ATTR_CONNECTION_TIMEOUT,  /*!< The number of seconds to wait for any request on the connection to complete before returning to the application.                       */
        AttrCurrentCatalog      = SQL_ATTR_CURRENT_CATALOG,     /*!< A character string containing the name of the catalog to be used by the data source.                                                   */
        AttrLoginTimeout        = SQL_ATTR_LOGIN_TIMEOUT,       /*!< The number of seconds to wait for a login request to complete before returning to the application.                                     */
        AttrMetadataId          = SQL_ATTR_METADATA_ID,         /*!< Determines how the string arguments of catalog functions are treated.                                                                  */
        AttrOdbcCursors         = SQL_ATTR_ODBC_CURSORS,        /*!< Specifies how the Driver Manager uses the ODBC cursor library.                                                                         */
        AttrPacketSize          = SQL_ATTR_PACKET_SIZE,         /*!< Specifying the network packet size in bytes.                                                                                           */
        AttrQuietMode           = SQL_ATTR_QUIET_MODE,          /*!< The driver uses this handle to display dialog boxes.                                                                                   */
        AttrTrace               = SQL_ATTR_TRACE,               /*!< Tells the Driver Manager whether to perform tracing.                                                                                   */
        AttrTracefile           = SQL_ATTR_TRACEFILE,           /*!< String containing the name of the trace file.                                                                                          */
        AttrTranslateLib        = SQL_ATTR_TRANSLATE_LIB,       /*!< String containing the name of a lib containing the functions that the driver accesses to perform tasks such as char set translation.   */
        AttrTranslateOption     = SQL_ATTR_TRANSLATE_OPTION,    /*!< Value that is passed to the translation DLL.                                                                                           */
        AttrTxnIsolation        = SQL_ATTR_TXN_ISOLATION        /*!< Sets the transaction isolation level for the current connection.                                                                       */
    };

    enum AttrAccessModeTypes
    {
        ModeReadOnly        = SQL_MODE_READ_ONLY,               /*!< Used by the driver/data source as an indicator that the connection is not required to support SQL that cause updates to occur.         */
        ModeReadWrite       = SQL_MODE_READ_WRITE               /*!< Default. Driver/Data Source should support SQL which cause updates to occur.                                                           */
    };

    enum AttrAsyncEnableTypes
    {
        AsyncEnableOff      = SQL_ASYNC_ENABLE_OFF,             /*!< Default. All calls are synchronous.                                                                                                    */
        AsyncEnableOn       = SQL_ASYNC_ENABLE_ON               /*!< Enables asynchronous execution for all future statement handles allocated on this connection.                                          */
    };

    enum AttrAutocommitTypes
    {
        AutocommitOff   = SQL_AUTOCOMMIT_OFF,                   /*!< Driver uses manual-commit mode, and the application must explicitly commit or roll back transactions with SQLEndTran.                  */
        AutocommitOn    = SQL_AUTOCOMMIT_ON                     /*!< Default. Driver uses autocommit mode. Each statement is committed immediately after it is executed.                                    */
    };

    enum AttrOdbcCursorsTypes
    {
        CurUseIfNeeded      = SQL_CUR_USE_IF_NEEDED,            /*!< Driver Manager uses the ODBC cursor library only if it is needed.                                                                      */
        CurUseOdbc          = SQL_CUR_USE_ODBC,                 /*!< Driver Manager uses the ODBC cursor library.                                                                                           */
        CurUseDriver        = SQL_CUR_USE_DRIVER                /*!< Default. Driver Manager uses the scrolling capabilities of the driver.                                                                 */
    };

    enum AttrTraceTypes
    {
        OptTraceOff = SQL_OPT_TRACE_OFF,                        /*!< Default. Tracing off.                                                                                                                  */
        OptTraceOn  = SQL_OPT_TRACE_ON                          /*!< Tracing on. When tracing is on, the Driver Manager writes each ODBC function call to the trace file.                                   */
    };

    explicit ODBCConnection( ODBCEnvironment *pEnvironment );
    virtual ~ODBCConnection();

    virtual SQLRETURN setAttrAccessMode( AttrAccessModeTypes nAttrAccessMode = ModeReadWrite );
    virtual SQLRETURN setAttrAsyncEnable( AttrAsyncEnableTypes nAttrAsyncEnable = AsyncEnableOff ); 
    virtual SQLRETURN setAttrAutocommit( AttrAutocommitTypes nAttrAutocommit = AutocommitOn );
    virtual SQLRETURN setAttrConnectionTimeout( SQLUINTEGER nAttrConnectionTimeout = 0 );
    virtual SQLRETURN setAttrCurrentCatalog( ODBCCHAR *pszAttrCurrentCatalog );
    virtual SQLRETURN setAttrLoginTimeout( SQLUINTEGER nAttrLoginTimeout = 0 );
    virtual SQLRETURN setAttrMetadataId( bool bAttrMetadataId = false );
    virtual SQLRETURN setAttrOdbcCursors( AttrOdbcCursorsTypes nAttrOdbcCursors = CurUseDriver );
    virtual SQLRETURN setAttrPacketSize( SQLUINTEGER nAttrPacketSize = 1024 );
    virtual SQLRETURN setAttrQuietMode( SQLHWND hWnd );
    virtual SQLRETURN setAttrTrace( AttrTraceTypes nAttrTrace = OptTraceOff );
    virtual SQLRETURN setAttrTracefile( ODBCCHAR *pszAttrTracefile );
    virtual SQLRETURN setAttrTranslateLib( ODBCCHAR *pszAttrTranslateLib );
    virtual SQLRETURN setAttrTranslateOption( SQLUINTEGER nAttrTranslateOption );
    virtual SQLRETURN setAttrTxnIsolation( SQLUINTEGER nAttrTxnIsolation );
    virtual SQLRETURN setConnectAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );
    virtual SQLRETURN setConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );

    virtual AttrAccessModeTypes     getAttrAccessMode( SQLRETURN *pn = NULL );
    virtual AttrAsyncEnableTypes    getAttrAsyncEnable( SQLRETURN *pn = NULL ); 
    virtual bool                    getAttrAutoIpd( SQLRETURN *pn = NULL );
    virtual AttrAutocommitTypes     getAttrAutocommit( SQLRETURN *pn = NULL );
    virtual bool                    getAttrConnectionDead( SQLRETURN *pn = NULL );
    virtual SQLUINTEGER             getAttrConnectionTimeout( SQLRETURN *pn = NULL );
    virtual ODBCCHAR *              getAttrCurrentCatalog( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn = NULL );
    virtual SQLUINTEGER             getAttrLoginTimeout( SQLRETURN *pn = NULL );
    virtual bool                    getAttrMetadataId( SQLRETURN *pn = NULL );
    virtual AttrOdbcCursorsTypes    getAttrOdbcCursors( SQLRETURN *pn = NULL );
    virtual SQLUINTEGER             getAttrPacketSize( SQLRETURN *pn = NULL );
    virtual SQLHWND                 getAttrQuietMode( SQLRETURN *pn = NULL );
    virtual AttrTraceTypes          getAttrTrace( SQLRETURN *pn = NULL );
    virtual ODBCCHAR *              getAttrTracefile( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn = NULL );
    virtual ODBCCHAR *              getAttrTranslateLib( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLRETURN *pn = NULL );
    virtual SQLUINTEGER             getAttrTranslateOption( SQLRETURN *pn = NULL );
    virtual SQLUINTEGER             getAttrTxnIsolation( SQLRETURN *pn = NULL );
    virtual SQLRETURN               getAttrAccessMode( AttrAccessModeTypes *pn );
    virtual SQLRETURN               getAttrAsyncEnable( AttrAsyncEnableTypes *pn );
    virtual SQLRETURN               getgetAttrAutoIpd( bool *pb );
    virtual SQLRETURN               getAttrAutocommit( AttrAutocommitTypes *pn );
    virtual SQLRETURN               getAttrConnectionDead( bool *pb );
    virtual SQLRETURN               getAttrConnectionTimeout( SQLUINTEGER *pn );
    virtual SQLRETURN               getAttrCurrentCatalog( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn );
    virtual SQLRETURN               getAttrLoginTimeout( SQLUINTEGER *pn );
    virtual SQLRETURN               getAttrMetadataId( bool *pb );
    virtual SQLRETURN               getAttrOdbcCursors( AttrOdbcCursorsTypes *pn );
    virtual SQLRETURN               getAttrPacketSize( SQLUINTEGER *pn );
    virtual SQLRETURN               getAttrQuietMode( SQLHWND *ph );
    virtual SQLRETURN               getAttrTrace( AttrTraceTypes *pn );
    virtual SQLRETURN               getAttrTracefile( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn );
    virtual SQLRETURN               getAttrTranslateLib( ODBCCHAR *psz, SQLINTEGER nCharsMax, SQLINTEGER *pnCharsToReturn );
    virtual SQLRETURN               getAttrTranslateOption( SQLUINTEGER *pn );
    virtual SQLRETURN               getAttrTxnIsolation( SQLUINTEGER *pn );
    virtual SQLRETURN               getConnectAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nLength, SQLINTEGER *pnRetSize );
    virtual SQLRETURN               getConnectAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nLength, SQLINTEGER *pnRetSize );
    virtual ODBCEnvironment *       getEnvironment();
    
    virtual SQLRETURN doConnect( const ODBCCHAR *pszServerName = NULL, SQLSMALLINT nLength1 = SQL_NTS, const ODBCCHAR *pszUserName = NULL, SQLSMALLINT nLength2 = SQL_NTS, const ODBCCHAR *pszAuthentication = NULL, SQLSMALLINT nLength3 = SQL_NTS );
    virtual SQLRETURN doDriverConnect( SQLHWND hWnd, ODBCCHAR *pszIn, SQLSMALLINT nLengthIn, ODBCCHAR *pszOut, SQLSMALLINT nLengthOut, SQLSMALLINT *pnLengthOut, SQLUSMALLINT nPrompt );
    virtual SQLRETURN doBrowseConnect( ODBCCHAR *szInConnectionString, SQLSMALLINT nStringLength1, ODBCCHAR *szOutConnectionString, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength2Ptr );
    virtual SQLRETURN doDisconnect();
    virtual SQLRETURN doGetInfo( SQLUSMALLINT nInfoType, SQLPOINTER pInfoValue, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength );

    virtual bool isConnected();

protected:
    bool bConnected;             /*!< cached connect state - need to see if this is needed                   */
};

#endif


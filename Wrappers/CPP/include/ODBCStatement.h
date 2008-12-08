/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCSTATEMENT_H
#define ODBCSTATEMENT_H

#include "ODBCHandle.h"
#include "ODBCVariant.h"

#include <time.h>

class ODBCConnection;

/*! 
 * \brief   An ODBC statement.
 *
 *          This class provides a very thin wrapper to SQLHSTMT. Using this class is
 *          more convenient for C++ developers (and those with modern code editors) 
 *          than using the SQLHSTMT directly. 
 * 
 * \sa      ODBCEnvironment
 *          ODBCConnection
 */
class ODBCStatement : public ODBCHandle
{
public:
    enum AttributeTypes
    {
        AttrAppParamDesc                = SQL_ATTR_APP_PARAM_DESC,
        AttrAppRowDesc                  = SQL_ATTR_APP_ROW_DESC,
        AttrAsyncEnable                 = SQL_ATTR_ASYNC_ENABLE,
        AttrConcurrency                 = SQL_ATTR_CONCURRENCY,
        AttrCursorScrollable            = SQL_ATTR_CURSOR_SCROLLABLE,
        AttrCursorSensitivity           = SQL_ATTR_CURSOR_SENSITIVITY,
        AttrCursorType                  = SQL_ATTR_CURSOR_TYPE,
        AttrEnableAuotIpd               = SQL_ATTR_ENABLE_AUTO_IPD,
        AttrFetchBookmarkPtr            = SQL_ATTR_FETCH_BOOKMARK_PTR,
        AttrImpParamDesc                = SQL_ATTR_IMP_PARAM_DESC,
        AttrImpRowDesc                  = SQL_ATTR_IMP_ROW_DESC,
        AttrKeysetSize                  = SQL_ATTR_KEYSET_SIZE,
        AttrMaxLength                   = SQL_ATTR_MAX_LENGTH,
        AttrMaxRows                     = SQL_ATTR_MAX_ROWS,
        AttrMetadataId                  = SQL_ATTR_METADATA_ID,
        AttrNoscan                      = SQL_ATTR_NOSCAN,
        AttrParamBindOffsetPtr          = SQL_ATTR_PARAM_BIND_OFFSET_PTR,
        AttrParamBindType               = SQL_ATTR_PARAM_BIND_TYPE,
        AttrParamOperationPtr           = SQL_ATTR_PARAM_OPERATION_PTR,
        AttrParamStatusPtr              = SQL_ATTR_PARAM_STATUS_PTR,
        AttrParamsProcessedPtr          = SQL_ATTR_PARAMS_PROCESSED_PTR,
        AttrParamsetSize                = SQL_ATTR_PARAMSET_SIZE,
        AttrQueryTimeout                = SQL_ATTR_QUERY_TIMEOUT,
        AttrRetrieveData                = SQL_ATTR_RETRIEVE_DATA,
        AttrRowArraySize                = SQL_ATTR_ROW_ARRAY_SIZE,
        AttrRowBindOffsetPtr            = SQL_ATTR_ROW_BIND_OFFSET_PTR,
        AttrRowBindType                 = SQL_ATTR_ROW_BIND_TYPE,
        AttrRowNumber                   = SQL_ATTR_ROW_NUMBER,
        AttrRowOperationPtr             = SQL_ATTR_ROW_OPERATION_PTR,
        AttrRowStatusPtr                = SQL_ATTR_ROW_STATUS_PTR,
        AttrRowsFetchedPtr              = SQL_ATTR_ROWS_FETCHED_PTR,
        AttrSimulateCursor              = SQL_ATTR_SIMULATE_CURSOR,
        AttrUseBookmarks                = SQL_ATTR_USE_BOOKMARKS
    };

    enum AttrAsyncEnableTypes
    {
        AsyncEnableOff          = SQL_ASYNC_ENABLE_OFF,
        AsyncEnableOn           = SQL_ASYNC_ENABLE_ON
    };

    enum AttrConcurrencyTypes
    {
        ConcurReadOnly      = SQL_CONCUR_READ_ONLY,
        ConcurLock          = SQL_CONCUR_LOCK,
        ConcurRowver        = SQL_CONCUR_ROWVER,
        ConcurValues        = SQL_CONCUR_VALUES
    };

    enum AttrCursorScrollableTypes
    {
        Nonscrollable   = SQL_NONSCROLLABLE,
        Scrollable      = SQL_SCROLLABLE
    };

    enum AttrCursorSensitivityTypes
    {
        Unspecified     = SQL_UNSPECIFIED,
        Insensitive     = SQL_INSENSITIVE,
        Sensitive       = SQL_SENSITIVE
    };

    enum AttrCursorTypes
    {
        CursorForwardOnly   = SQL_CURSOR_FORWARD_ONLY,
        CursorStatic        = SQL_CURSOR_STATIC,
        CursorKeysetDriven  = SQL_CURSOR_KEYSET_DRIVEN,
        CursorDynamic       = SQL_CURSOR_DYNAMIC
    };

    enum AttrNoscanTypes
    {
        NoscanOff   = SQL_NOSCAN_OFF,
        NoscanOn    = SQL_NOSCAN_ON
    };

    enum AttrRetrieveDataTypes
    {
        RdOn    = SQL_RD_ON,
        RdOff   = SQL_RD_OFF
    };

    enum AttrSimulateCursorTypes
    {
        ScNonUnique = SQL_SC_NON_UNIQUE,
        ScTryUnique = SQL_SC_TRY_UNIQUE,
        ScUnique    = SQL_SC_UNIQUE
    };

    enum AttrUseBookmarksTypes
    {
        UbOff   = SQL_UB_OFF,
        UbOn    = SQL_UB_ON
    };

    explicit ODBCStatement( ODBCConnection *pconnection );
    virtual ~ODBCStatement();

    virtual SQLRETURN setAttrAsyncEnable( AttrAsyncEnableTypes n );
    virtual SQLRETURN setAttrConcurrency( AttrConcurrencyTypes n );
    virtual SQLRETURN setStmtAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );
    virtual SQLRETURN setStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );

    virtual SQLRETURN getAttrAsyncEnable( AttrAsyncEnableTypes *pn );
    virtual SQLRETURN getAttrConcurrency( AttrConcurrencyTypes *pn );
    virtual SQLRETURN getStmtAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength );
    virtual SQLRETURN getStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength );
                            
    virtual ODBCConnection *getConnection();
    virtual double          getElapsedSeconds();

    virtual SQLRETURN doExecute();
    virtual SQLRETURN doExecDirect( ODBCCHAR *pszStatement, SQLINTEGER nLength = SQL_NTS );
    virtual SQLRETURN doTables( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszTableType = NULL, SQLSMALLINT nLength4 = 0 );
    virtual SQLRETURN doColumns( const ODBCCHAR *pszCatalogName = TEXT(""), SQLSMALLINT nLength1 = SQL_NTS, const ODBCCHAR *pszSchemaName = TEXT(SQL_ALL_SCHEMAS), SQLSMALLINT nLength2 = SQL_NTS, const ODBCCHAR *pszTableName = TEXT("%"), SQLSMALLINT nLength3 = SQL_NTS, const ODBCCHAR *pszColumnName = TEXT("%"), SQLSMALLINT nLength4 = SQL_NTS );
    virtual SQLRETURN doStatistics( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doSpecialColumns( SQLSMALLINT nIdentifierType = SQL_BEST_ROWID, ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doPrimaryKeys( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0 );
    virtual SQLRETURN doForeignKeys( ODBCCHAR *pszPKCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszPKSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszPKTableName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszFKCatalogName = NULL, SQLSMALLINT nLength4 = 0, ODBCCHAR *pszFKSchemaName = NULL, SQLSMALLINT nLength5 = 0, ODBCCHAR *pszFKTableName = NULL, SQLSMALLINT nLength6 = 0 );
    virtual SQLRETURN doProcedures( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszProcName = NULL, SQLSMALLINT nLength3 = 0 );
    virtual SQLRETURN doProcedureColumns( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszProcName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszColumnName = NULL, SQLSMALLINT nLength4 = 0 );
    virtual SQLRETURN doTypeInfo( SQLSMALLINT nDataType = SQL_ALL_TYPES );
    virtual SQLRETURN doFetch();
    virtual SQLRETURN doData( SQLUSMALLINT nColumnNumber, SQLSMALLINT nTargetType, SQLPOINTER pTargetValuePtr, SQLLEN nBufferLength, SQLLEN *pnStrLenOrIndPtr );
    virtual SQLRETURN doData( SQLUSMALLINT nColumnNumber, ODBCVariant *p, bool bExpand = false );
    virtual SQLRETURN doColAttribute( SQLUSMALLINT nColumnNumber, SQLUSMALLINT nFieldIdentifier, SQLPOINTER nCharacterAttributePtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr, SQLLEN *pnNumericAttributePtr );
    virtual SQLRETURN doNumResultCols( SQLSMALLINT *pnColumnCountPtr );
    virtual SQLRETURN doRowCount( SQLLEN *pnRowCountPtr );
    virtual SQLRETURN doCloseCursor();
    virtual SQLRETURN doPrepare( ODBCCHAR *pszStatementText, SQLINTEGER nTextLength );
    virtual SQLRETURN doBindCol( SQLUSMALLINT nColumnNumber, SQLSMALLINT nTargetType, SQLPOINTER pTargetValuePtr, SQLLEN nBufferLength, SQLLEN *pnStrLen_or_Ind );
    virtual SQLRETURN doCancel();
    virtual bool      doWaiting();
    virtual SQLRETURN doAlloc();
    virtual SQLRETURN doFree( SQLUSMALLINT n );
    virtual SQLRETURN doFree() { return ODBCHandle::doFree(); }

    virtual bool      isCursor();

protected:
    double nElapsedSeconds;    /*!< seconds it took for request to complete                                */
};


#endif


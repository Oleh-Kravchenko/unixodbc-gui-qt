/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#pragma once

#include "OQHandle.h"

class OQConnection;

class OQFilter : public QString
{
public:
    OQFilter( const QString &string )
        : QString( string )
    {
    }

};

/*! 
 * \class   OQStatement
 * \brief   An ODBC statement.
 *
 *          This class wraps an ODBC Statement handle.
 *
 *          \li uses Qt data types where possible
 *          \li provides several Qt signals
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 *          \li use of Qt threads 
 * 
 */
class OQStatement : public OQHandle
{
    Q_OBJECT
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

    OQStatement( OQConnection *pconnection );
    virtual ~OQStatement();

    // SETTERS
    virtual SQLRETURN setAttrAsyncEnable( AttrAsyncEnableTypes n );
    virtual SQLRETURN setAttrConcurrency( AttrConcurrencyTypes n );
    virtual SQLRETURN setAttrMaxLength( SQLUINTEGER n );

    // GETTERS
    virtual SQLRETURN   getAttrAsyncEnable( AttrAsyncEnableTypes *pn );
    virtual SQLRETURN   getAttrConcurrency( AttrConcurrencyTypes *pn );
    virtual QVariant    getData( SQLUSMALLINT nColumnNumber, SQLRETURN *pnReturn = 0 );
    virtual double      getElapsedSeconds();

    // DOERS
    virtual SQLRETURN doBindCol( SQLUSMALLINT nColumnNumber, QVariant *pv );
    virtual SQLRETURN doCancel();
    virtual SQLRETURN doCatalogs( const QString &stringCatalogName );
    virtual SQLRETURN doCloseCursor();
    virtual SQLRETURN doColAttribute( SQLUSMALLINT nColumnNumber, SQLUSMALLINT nFieldIdentifier, SQLPOINTER nCharacterAttributePtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr, SQLLEN *pnNumericAttributePtr );
    virtual SQLRETURN doColumns( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, const QString &stringColumnName = QString::null );
    virtual SQLRETURN doExecute();
    virtual SQLRETURN doExecDirect( const QString &stringStatement );
    virtual SQLRETURN doFetch();
    virtual SQLRETURN doForeignKeys( const QString &stringPKCatalogName, const QString &stringPKSchemaName = QString::null, const QString &stringPKTableName = QString::null, const QString &stringFKCatalogName = QString::null, const QString &stringFKSchemaName = QString::null, const QString &stringFKTableName = QString::null );
    virtual SQLRETURN doNumResultCols( SQLSMALLINT *pnColumnCountPtr );
    virtual SQLRETURN doPrepare( const QString &stringStatementText );
    virtual SQLRETURN doPrimaryKeys( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null );
    virtual SQLRETURN doProcedureColumns( const QString &stringCatalogName = QString::null, const QString &stringSchemaName = QString::null, const QString &stringProcName = QString::null, const QString &stringColumnName = QString::null );
    virtual SQLRETURN doProcedures( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringProcName = QString::null );
    virtual SQLRETURN doRowCount( SQLLEN *pnRowCountPtr );
    virtual SQLRETURN doSchemas( const QString &stringCatalogName, const QString &stringSchemaName = QString::null );
    virtual SQLRETURN doSpecialColumns( SQLSMALLINT nIdentifierType = SQL_BEST_ROWID, const QString &stringCatalogName = QString::null, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doStatistics( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doTables( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, const QString &stringTableType = QString::null );
    virtual SQLRETURN doTypeInfo( SQLSMALLINT nDataType = SQL_ALL_TYPES );
    virtual bool      doWaiting();
    // to support a filter string
    virtual SQLRETURN doColumns( const OQFilter &stringFilter );
    virtual SQLRETURN doForeignKeys( const OQFilter &stringFilter );
    virtual SQLRETURN doPrimaryKeys( const OQFilter &stringFilter );
    virtual SQLRETURN doProcedureColumns( const OQFilter &stringFilter );
    virtual SQLRETURN doProcedures( const OQFilter &stringFilter );
    virtual SQLRETURN doSpecialColumns( const OQFilter &stringFilter, SQLSMALLINT nIdentifierType = SQL_BEST_ROWID, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doStatistics( const OQFilter &stringFilter, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doTables( const OQFilter &stringFilter, const QString &stringTableType = QString::null );

    virtual bool      isCursor();

signals:
    virtual void signalElapsedSeconds( double nElapsedSeconds );
    virtual void signalResults( OQStatement *pstatement );

public slots:
    SQLRETURN slotExecDirect( const QString &stringStatement );
    SQLRETURN slotExecute();

protected:
    double nElapsedSeconds;    /*!< seconds it took for request to complete                                */

    virtual SQLRETURN setStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue );

    virtual SQLRETURN getStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue );

    static void getParsedFilter( const OQFilter &stringFilter, QString *pstringCatalog, QString *pstringSchema, QString *pstringObject );
};



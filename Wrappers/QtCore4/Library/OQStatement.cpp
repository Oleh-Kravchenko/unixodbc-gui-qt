/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "OQConnection.h"
#include "OQStatement.h"

OQStatement::OQStatement( OQConnection *pconnection )
    : QObject( 0 ), ODBCStatement( pconnection )
{
    setObjectName( "OQStatement" );

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(ODBCMessage Message)), pconnection, SIGNAL(signalMessage(ODBCMessage Message)) );
    connect( this, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)), pconnection, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)) );
}

OQStatement::~OQStatement()
{
}

/*!
    getExecute
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doExecute()
{
    SQLRETURN nReturn = ODBCStatement::doExecute();
    if ( SQL_SUCCEEDED( nReturn ) && isCursor() )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getExecDirect
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doExecDirect( ODBCCHAR *pszStatement, SQLINTEGER nLength )
{
    SQLRETURN nReturn = ODBCStatement::doExecDirect( pszStatement, nLength );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getCatalogs
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doCatalogs( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1 )
{
    SQLRETURN nReturn = ODBCStatement::doTables( pszCatalogName, nLength1, (ODBCCHAR*)"", SQL_NTS, (ODBCCHAR*)"", SQL_NTS, (ODBCCHAR*)"", SQL_NTS );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getSchemas
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doSchemas( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2 )
{
    SQLRETURN nReturn = ODBCStatement::doTables( pszCatalogName, nLength1, pszSchemaName, nLength2, (ODBCCHAR*)"", SQL_NTS, (ODBCCHAR*)"", SQL_NTS );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getTables
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doTables( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, ODBCCHAR *pszTableType, SQLSMALLINT nLength4 )
{
    SQLRETURN nReturn = ODBCStatement::doTables( pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, pszTableType, nLength4 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getColumns
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doColumns( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
{
    SQLRETURN nReturn = ODBCStatement::doColumns( pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, pszColumnName, nLength4 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getStatistics
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doStatistics( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
{
    SQLRETURN nReturn = ODBCStatement::doStatistics( pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, nUnique, nReserved );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getSpecialColumns
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doSpecialColumns( SQLSMALLINT nIdentifierType, ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLSMALLINT nScope, SQLSMALLINT nNullable )
{
    SQLRETURN nReturn = ODBCStatement::doSpecialColumns( nIdentifierType, pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, nScope, nNullable );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getPrimaryKeys
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doPrimaryKeys( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3 )
{
    SQLRETURN nReturn = ODBCStatement::doPrimaryKeys( pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getForeignKeys
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doForeignKeys( ODBCCHAR *pszPKCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszPKSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszPKTableName, SQLSMALLINT nLength3, ODBCCHAR *pszFKCatalogName, SQLSMALLINT nLength4, ODBCCHAR *pszFKSchemaName, SQLSMALLINT nLength5, ODBCCHAR *pszFKTableName, SQLSMALLINT nLength6 )
{
    SQLRETURN nReturn = ODBCStatement::doForeignKeys( pszPKCatalogName, nLength1, pszPKSchemaName, nLength2, pszPKTableName, nLength3, pszFKCatalogName, nLength4, pszFKSchemaName, nLength5, pszFKTableName, nLength6 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getProcedures
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doProcedures( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3 )
{
    SQLRETURN nReturn = ODBCStatement::doProcedures( pszCatalogName, nLength1, pszSchemaName, nLength2, pszProcName, nLength3 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getProcedureColumns
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doProcedureColumns( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3, ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
{
    SQLRETURN nReturn = ODBCStatement::doProcedureColumns( pszCatalogName, nLength1, pszSchemaName, nLength2, pszProcName, nLength3, pszColumnName, nLength4 );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getTypeInfo
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN OQStatement::doTypeInfo( SQLSMALLINT nDataType )
{
    SQLRETURN nReturn = ODBCStatement::doTypeInfo( nDataType );
    if ( SQL_SUCCEEDED( nReturn ) )
    {
        emit signalElapsedSeconds( nElapsedSeconds );
        emit signalResults( this );
    }

    return nReturn;
}

/*!
    getExecDirect
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doExecDirect( const QString &stringStatement )
{
    ODBCCHAR *pszStatement  = OQFromQString(stringStatement);
    int nStatement          = pszStatement ? SQL_NTS : 0;

    return doExecDirect( pszStatement, nStatement );
}

/*!
    doCatalogs
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doCatalogs( const QString &stringCatalog )
{
    ODBCCHAR *  pszCatalog = OQFromQString(stringCatalog);
    int         nCatalog   = pszCatalog ? SQL_NTS : 0;

    return doCatalogs( pszCatalog, nCatalog );
}

/*!
    doSchemas
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doSchemas( const QString &stringCatalog, const QString &stringSchema )
{
    ODBCCHAR *  pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *  pszSchema  = OQFromQString(stringSchema);
    int         nCatalog   = pszCatalog ? SQL_NTS : 0;
    int         nSchema    = pszSchema ? SQL_NTS : 0; 

    return doSchemas( pszCatalog, nCatalog, pszSchema, nSchema );
}

/*!
    doTables
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doTables( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, const QString &stringType )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszTable   = OQFromQString(stringTable);
    ODBCCHAR *pszType    = OQFromQString(stringType);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nTable          = pszTable ? SQL_NTS : 0;
    int nType           = pszType ? SQL_NTS : 0; 

    return doTables( pszCatalog, nCatalog, pszSchema, nSchema, pszTable, nTable, pszType, nType );
}

/*!
    doColumns
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doColumns( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, const QString &stringColumn )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszTable   = OQFromQString(stringTable);
    ODBCCHAR *pszColumn  = OQFromQString(stringColumn);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nTable          = pszTable ? SQL_NTS : 0;
    int nColumn         = pszColumn ? SQL_NTS : 0; 

    return doColumns( pszCatalog, nCatalog, pszSchema, nSchema, pszTable, nTable, pszColumn, nColumn );
}

/*!
    doStatistics
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doStatistics( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszTable   = OQFromQString(stringTable);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nTable          = pszTable ? SQL_NTS : 0;

    return doStatistics( pszCatalog, nCatalog, pszSchema, nSchema, pszTable, nTable, nUnique, nReserved );
}

/*!
    doSpecialColumns
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doSpecialColumns( SQLSMALLINT nIdentifierType, const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, SQLSMALLINT nScope, SQLSMALLINT nNullable )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszTable   = OQFromQString(stringTable);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nTable          = pszTable ? SQL_NTS : 0;

    return doSpecialColumns( nIdentifierType, pszCatalog, nCatalog, pszSchema, nSchema, pszTable, nTable, nScope, nNullable );
}

/*!
    doPrimaryKeys
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doPrimaryKeys( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszTable   = OQFromQString(stringTable);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nTable          = pszTable ? SQL_NTS : 0;

    return doPrimaryKeys( pszCatalog, nCatalog, pszSchema, nSchema, pszTable, nTable );
}


/*!
    doForeignKeys
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doForeignKeys( const QString &stringPKCatalogName, const QString &stringPKSchemaName, const QString &stringPKTableName, const QString &stringFKCatalogName, const QString &stringFKSchemaName, const QString &stringFKTableName )
{
    ODBCCHAR *pszPKCatalogName = OQFromQString(stringPKCatalogName);
    ODBCCHAR *pszPKSchemaName  = OQFromQString(stringPKSchemaName);
    ODBCCHAR *pszPKTableName   = OQFromQString(stringPKTableName);

    ODBCCHAR *pszFKCatalogName = OQFromQString(stringFKCatalogName);
    ODBCCHAR *pszFKSchemaName  = OQFromQString(stringFKSchemaName);
    ODBCCHAR *pszFKTableName   = OQFromQString(stringFKTableName);

    int nPKCatalogName = pszPKCatalogName ? SQL_NTS : 0;
    int nPKSchemaName  = pszPKSchemaName ? SQL_NTS : 0;
    int nPKTableName   = pszPKTableName ? SQL_NTS : 0;

    int nFKCatalogName = pszFKCatalogName ? SQL_NTS : 0;
    int nFKSchemaName  = pszFKSchemaName ? SQL_NTS : 0;
    int nFKTableName   = pszFKTableName ? SQL_NTS : 0;

    return doForeignKeys( pszPKCatalogName, nPKCatalogName, pszPKSchemaName, nPKSchemaName, pszPKTableName, nPKTableName, pszFKCatalogName, nFKCatalogName, pszFKSchemaName, nFKSchemaName, pszFKTableName, nFKTableName );
}

/*!
    doProcedures
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doProcedures( const QString &stringCatalog, const QString &stringSchema, const QString &stringProc )
{
    ODBCCHAR *pszCatalog = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = OQFromQString(stringSchema);
    ODBCCHAR *pszProc    = OQFromQString(stringProc);
    int nCatalog        = pszCatalog ? SQL_NTS : 0;
    int nSchema         = pszSchema ? SQL_NTS : 0; 
    int nProc           = pszProc ? SQL_NTS : 0;

    return doProcedures( pszCatalog, nCatalog, pszSchema, nSchema, pszProc, nProc );
}

/*!
    doProcedureColumns
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN OQStatement::doProcedureColumns( const QString &stringCatalog, const QString &stringSchema, const QString &stringProcedure, const QString &stringColumn )
{
    ODBCCHAR *pszCatalog     = OQFromQString(stringCatalog);
    ODBCCHAR *pszSchema      = OQFromQString(stringSchema);
    ODBCCHAR *pszProcedure   = OQFromQString(stringProcedure);
    ODBCCHAR *pszColumn      = OQFromQString(stringColumn);
    int nCatalog            = pszCatalog ? SQL_NTS : 0;
    int nSchema             = pszSchema ? SQL_NTS : 0; 
    int nProcedure          = pszProcedure ? SQL_NTS : 0;
    int nColumn             = pszColumn ? SQL_NTS : 0; 

    return doProcedureColumns( pszCatalog, nCatalog, pszSchema, nSchema, pszProcedure, nProcedure, pszColumn, nColumn );
}

/*!
    getTables
    
    Query based upon a filter where filter may be of the form;
    
    [[CATALOG.]SCHEMA]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doTables( const OQFilter &stringFilter, const QString &stringTableType )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringDummy;

    getParsedFilter( stringFilter, &stringDummy, &stringCatalog, &stringSchema );

    return doTables( stringCatalog, stringSchema, QString::null, stringTableType );
}

/*!
    doColumns
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]TABLE | VIEW]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doColumns( const OQFilter &stringFilter )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringTable;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringTable );

    return doColumns( stringCatalog, stringSchema, stringTable );
}

/*!
    doStatistics
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]TABLE]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doStatistics( const OQFilter &stringFilter, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringTable;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringTable );

    return doStatistics( stringCatalog, stringSchema, stringTable, nUnique, nReserved );
}

/*!
    doSpecialColumns
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]TABLE]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doSpecialColumns( const OQFilter &stringFilter, SQLSMALLINT nIdentifierType, SQLSMALLINT nScope, SQLSMALLINT nNullable )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringTable;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringTable );

    return doSpecialColumns( nIdentifierType, stringCatalog, stringSchema, stringTable, nScope, nNullable );
}

/*!
    doPrimaryKeys
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]TABLE]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doPrimaryKeys( const OQFilter &stringFilter )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringTable;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringTable );

    return doPrimaryKeys( stringCatalog, stringSchema, stringTable );
}

/*!
    doForeignKeys
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]TABLE]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doForeignKeys( const OQFilter &stringFilter )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringTable;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringTable );

    return doForeignKeys( stringCatalog, stringSchema, stringTable );
}

/*!
    doProcedures
    
    Query based upon a filter where filter may be of the form;
    
    [[CATALOG.]SCHEMA]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doProcedures( const OQFilter &stringFilter )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringDummy;

    getParsedFilter( stringFilter, &stringDummy, &stringCatalog, &stringSchema );

    return doProcedures( stringCatalog, stringSchema );
}

/*!
    doProcedureColumns
    
    Query based upon a filter where filter may be of the form;
    
    [[[CATALOG.]SCHEMA.]PROCEDURE]
    
    The filter is expanded and the query is executed.
*/
SQLRETURN OQStatement::doProcedureColumns( const OQFilter &stringFilter )
{
    QString stringCatalog;
    QString stringSchema;
    QString stringProcedure;

    getParsedFilter( stringFilter, &stringCatalog, &stringSchema, &stringProcedure );

    return doProcedureColumns( stringCatalog, stringSchema, stringProcedure );
}

/*!
    getParsedFilter

    Will seperate a stringFilter which is expected to be of the form;
    
    [[[CATALOG.]SCHEMA.]OBJECT]
*/
void OQStatement::getParsedFilter(  const OQFilter &stringFilter, QString *pstringCatalog, QString *pstringSchema, QString *pstringObject )
{
    *pstringCatalog = QString::null;
    *pstringSchema  = QString::null;
    *pstringObject  = QString::null;

    QStringList stringlist = stringFilter.split( '.' );
    if ( stringlist.count() > 0 )
        *pstringObject = stringlist[stringlist.count() - 1];

    if ( stringlist.count() > 1 )
        *pstringSchema = stringlist[stringlist.count() - 2];

    if ( stringlist.count() > 2 )
        *pstringCatalog = stringlist[stringlist.count() - 3];
}

/*!
    doWaiting
    
    Replaces ODBCStatement::doWaiting. 
    
    This will give time to the main Qt event loop during any asynch operation such
    that the application gets some time to do things like; repaint the screen or update
    a progress dialog.
*/
bool OQStatement::doWaiting()
{
//    qApp->processEvents();

    ODBCStatement::doWaiting();

    return true;
}

/*!
    slotExecute
    
    Executes the given statement.
*/
SQLRETURN OQStatement::slotExecute( const QString &stringSQL )
{
    SQLRETURN nReturn;
     
    // Use doPrepare or call doExecDirect ???? There would seem to be diff parse logic in some drivers (i.e. DB2) re. multi-statements and comments

    nReturn = doPrepare( OQFromQString(stringSQL), SQL_NTS );

    if ( !SQL_SUCCEEDED( nReturn ) )
        return nReturn;

    nReturn = doExecute();

    return nReturn;
}

void OQStatement::eventMessage( ODBCMessage Message )
{
    emit signalMessage( Message );
}

void OQStatement::eventDiagnostic()
{
    emit signalDiagnostic( ODBCDiagnostic( this ) );
}



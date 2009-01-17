/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCQConnection.h"
#include "ODBCQStatement.h"

ODBCQStatement::ODBCQStatement( ODBCQConnection *pconnection )
    : QObject( 0 ), ODBCStatement( pconnection )
{
    setObjectName( "ODBCQStatement" );

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(ODBCMessage Message)), pconnection, SIGNAL(signalMessage(ODBCMessage Message)) );
    connect( this, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)), pconnection, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)) );
}

ODBCQStatement::~ODBCQStatement()
{
}

/*!
    getExecute
    
    Replaces ODBCStatement version so as to emit signals.
*/
SQLRETURN ODBCQStatement::doExecute()
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
SQLRETURN ODBCQStatement::doExecDirect( ODBCCHAR *pszStatement, SQLINTEGER nLength )
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
SQLRETURN ODBCQStatement::doCatalogs( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1 )
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
SQLRETURN ODBCQStatement::doSchemas( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2 )
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
SQLRETURN ODBCQStatement::doTables( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, ODBCCHAR *pszTableType, SQLSMALLINT nLength4 )
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
SQLRETURN ODBCQStatement::doColumns( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
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
SQLRETURN ODBCQStatement::doStatistics( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
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
SQLRETURN ODBCQStatement::doSpecialColumns( SQLSMALLINT nIdentifierType, ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLSMALLINT nScope, SQLSMALLINT nNullable )
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
SQLRETURN ODBCQStatement::doPrimaryKeys( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3 )
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
SQLRETURN ODBCQStatement::doForeignKeys( ODBCCHAR *pszPKCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszPKSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszPKTableName, SQLSMALLINT nLength3, ODBCCHAR *pszFKCatalogName, SQLSMALLINT nLength4, ODBCCHAR *pszFKSchemaName, SQLSMALLINT nLength5, ODBCCHAR *pszFKTableName, SQLSMALLINT nLength6 )
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
SQLRETURN ODBCQStatement::doProcedures( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3 )
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
SQLRETURN ODBCQStatement::doProcedureColumns( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3, ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
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
SQLRETURN ODBCQStatement::doTypeInfo( SQLSMALLINT nDataType )
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
SQLRETURN ODBCQStatement::doExecDirect( const QString &stringStatement )
{
    ODBCCHAR *pszStatement  = ODBCQFromQString(stringStatement);
    int nStatement          = pszStatement ? SQL_NTS : 0;

    return doExecDirect( pszStatement, nStatement );
}

/*!
    doCatalogs
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN ODBCQStatement::doCatalogs( const QString &stringCatalog )
{
    ODBCCHAR *  pszCatalog = ODBCQFromQString(stringCatalog);
    int         nCatalog   = pszCatalog ? SQL_NTS : 0;

    return doCatalogs( pszCatalog, nCatalog );
}

/*!
    doSchemas
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN ODBCQStatement::doSchemas( const QString &stringCatalog, const QString &stringSchema )
{
    ODBCCHAR *  pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *  pszSchema  = ODBCQFromQString(stringSchema);
    int         nCatalog   = pszCatalog ? SQL_NTS : 0;
    int         nSchema    = pszSchema ? SQL_NTS : 0; 

    return doSchemas( pszCatalog, nCatalog, pszSchema, nSchema );
}

/*!
    doTables
    
    Allows the use of QString instead of ODBCCHAR* but otherwise simply
    calls the ODBCStatement equivalent.
*/
SQLRETURN ODBCQStatement::doTables( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, const QString &stringType )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszTable   = ODBCQFromQString(stringTable);
    ODBCCHAR *pszType    = ODBCQFromQString(stringType);
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
SQLRETURN ODBCQStatement::doColumns( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, const QString &stringColumn )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszTable   = ODBCQFromQString(stringTable);
    ODBCCHAR *pszColumn  = ODBCQFromQString(stringColumn);
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
SQLRETURN ODBCQStatement::doStatistics( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszTable   = ODBCQFromQString(stringTable);
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
SQLRETURN ODBCQStatement::doSpecialColumns( SQLSMALLINT nIdentifierType, const QString &stringCatalog, const QString &stringSchema, const QString &stringTable, SQLSMALLINT nScope, SQLSMALLINT nNullable )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszTable   = ODBCQFromQString(stringTable);
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
SQLRETURN ODBCQStatement::doPrimaryKeys( const QString &stringCatalog, const QString &stringSchema, const QString &stringTable )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszTable   = ODBCQFromQString(stringTable);
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
SQLRETURN ODBCQStatement::doForeignKeys( const QString &stringPKCatalogName, const QString &stringPKSchemaName, const QString &stringPKTableName, const QString &stringFKCatalogName, const QString &stringFKSchemaName, const QString &stringFKTableName )
{
    ODBCCHAR *pszPKCatalogName = ODBCQFromQString(stringPKCatalogName);
    ODBCCHAR *pszPKSchemaName  = ODBCQFromQString(stringPKSchemaName);
    ODBCCHAR *pszPKTableName   = ODBCQFromQString(stringPKTableName);

    ODBCCHAR *pszFKCatalogName = ODBCQFromQString(stringFKCatalogName);
    ODBCCHAR *pszFKSchemaName  = ODBCQFromQString(stringFKSchemaName);
    ODBCCHAR *pszFKTableName   = ODBCQFromQString(stringFKTableName);

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
SQLRETURN ODBCQStatement::doProcedures( const QString &stringCatalog, const QString &stringSchema, const QString &stringProc )
{
    ODBCCHAR *pszCatalog = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema  = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszProc    = ODBCQFromQString(stringProc);
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
SQLRETURN ODBCQStatement::doProcedureColumns( const QString &stringCatalog, const QString &stringSchema, const QString &stringProcedure, const QString &stringColumn )
{
    ODBCCHAR *pszCatalog     = ODBCQFromQString(stringCatalog);
    ODBCCHAR *pszSchema      = ODBCQFromQString(stringSchema);
    ODBCCHAR *pszProcedure   = ODBCQFromQString(stringProcedure);
    ODBCCHAR *pszColumn      = ODBCQFromQString(stringColumn);
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
SQLRETURN ODBCQStatement::doTables( const ODBCQFilter &stringFilter, const QString &stringTableType )
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
SQLRETURN ODBCQStatement::doColumns( const ODBCQFilter &stringFilter )
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
SQLRETURN ODBCQStatement::doStatistics( const ODBCQFilter &stringFilter, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
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
SQLRETURN ODBCQStatement::doSpecialColumns( const ODBCQFilter &stringFilter, SQLSMALLINT nIdentifierType, SQLSMALLINT nScope, SQLSMALLINT nNullable )
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
SQLRETURN ODBCQStatement::doPrimaryKeys( const ODBCQFilter &stringFilter )
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
SQLRETURN ODBCQStatement::doForeignKeys( const ODBCQFilter &stringFilter )
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
SQLRETURN ODBCQStatement::doProcedures( const ODBCQFilter &stringFilter )
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
SQLRETURN ODBCQStatement::doProcedureColumns( const ODBCQFilter &stringFilter )
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
void ODBCQStatement::getParsedFilter(  const ODBCQFilter &stringFilter, QString *pstringCatalog, QString *pstringSchema, QString *pstringObject )
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
bool ODBCQStatement::doWaiting()
{
//    qApp->processEvents();

    ODBCStatement::doWaiting();

    return true;
}

/*!
    slotExecute
    
    Executes the given statement.
*/
SQLRETURN ODBCQStatement::slotExecute( const QString &stringSQL )
{
    SQLRETURN nReturn;
     
    // Use doPrepare or call doExecDirect ???? There would seem to be diff parse logic in some drivers (i.e. DB2) re. multi-statements and comments

    nReturn = doPrepare( ODBCQFromQString(stringSQL), SQL_NTS );

    if ( !SQL_SUCCEEDED( nReturn ) )
        return nReturn;

    nReturn = doExecute();

    return nReturn;
}

void ODBCQStatement::eventMessage( ODBCMessage Message )
{
    emit signalMessage( Message );
}

void ODBCQStatement::eventDiagnostic()
{
    emit signalDiagnostic( ODBCDiagnostic( this ) );
}



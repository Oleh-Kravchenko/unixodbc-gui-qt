/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQSTATEMENT_H
#define OQSTATEMENT_H

// libqt
#include <QtCore>

// libodbcplus
#include <ODBCStatement.h>
#include <ODBCDiagnostic.h>

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
 *          This class extends ODBCStatement by providing a more Qt friendly interface. For
 *          example;
 *
 *          \li uses Qt data types where possible
 *          \li provides several Qt signals
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 *          \li use of Qt threads 
 * 
 */
class OQStatement : public QObject, public ODBCStatement
{
    Q_OBJECT
public:
    OQStatement( OQConnection *pconnection );
    virtual ~OQStatement();

    // SETTERS

    // GETTERS
    // to ensure Qt signals emitted
    virtual SQLRETURN doExecute();
    virtual SQLRETURN doExecDirect( ODBCCHAR *pszStatement, SQLINTEGER nLength = SQL_NTS );
    virtual SQLRETURN doCatalogs( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0 );
    virtual SQLRETURN doSchemas( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0 );
    virtual SQLRETURN doTables( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszTableType = NULL, SQLSMALLINT nLength4 = 0 );
    virtual SQLRETURN doColumns( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszColumnName = NULL, SQLSMALLINT nLength4 = 0 );
    virtual SQLRETURN doStatistics( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doSpecialColumns( SQLSMALLINT nIdentifierType = SQL_BEST_ROWID, ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doPrimaryKeys( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszTableName = NULL, SQLSMALLINT nLength3 = 0 );
    virtual SQLRETURN doForeignKeys( ODBCCHAR *pszPKCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszPKSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszPKTableName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszFKCatalogName = NULL, SQLSMALLINT nLength4 = 0, ODBCCHAR *pszFKSchemaName = NULL, SQLSMALLINT nLength5 = 0, ODBCCHAR *pszFKTableName = NULL, SQLSMALLINT nLength6 = 0 );
    virtual SQLRETURN doProcedures( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszProcName = NULL, SQLSMALLINT nLength3 = 0 );
    virtual SQLRETURN doProcedureColumns( ODBCCHAR *pszCatalogName = NULL, SQLSMALLINT nLength1 = 0, ODBCCHAR *pszSchemaName = NULL, SQLSMALLINT nLength2 = 0, ODBCCHAR *pszProcName = NULL, SQLSMALLINT nLength3 = 0, ODBCCHAR *pszColumnName = NULL, SQLSMALLINT nLength4 = 0 );
    virtual SQLRETURN doTypeInfo( SQLSMALLINT nDataType = SQL_ALL_TYPES );

    // to support QString
    virtual SQLRETURN doExecDirect( const QString &stringStatement );
    virtual SQLRETURN doCatalogs( const QString &stringCatalogName );
    virtual SQLRETURN doSchemas( const QString &stringCatalogName, const QString &stringSchemaName = QString::null );
    virtual SQLRETURN doTables( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, const QString &stringTableType = QString::null );
    virtual SQLRETURN doColumns(  const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, const QString &stringColumnName = QString::null );
    virtual SQLRETURN doStatistics( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doSpecialColumns( SQLSMALLINT nIdentifierType, const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doPrimaryKeys( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringTableName = QString::null );
    virtual SQLRETURN doForeignKeys( const QString &stringPKCatalogName, const QString &stringPKSchemaName = QString::null, const QString &stringPKTableName = QString::null, const QString &stringFKCatalogName = QString::null, const QString &stringFKSchemaName = QString::null, const QString &stringFKTableName = QString::null );
    virtual SQLRETURN doProcedures( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringProcName = QString::null );
    virtual SQLRETURN doProcedureColumns( const QString &stringCatalogName, const QString &stringSchemaName = QString::null, const QString &stringProcName = QString::null, const QString &stringColumnName = QString::null );

    // to support a filter string
    virtual SQLRETURN doTables( const OQFilter &stringFilter, const QString &stringTableType = QString::null );
    virtual SQLRETURN doColumns( const OQFilter &stringFilter );
    virtual SQLRETURN doStatistics( const OQFilter &stringFilter, SQLUSMALLINT nUnique = SQL_INDEX_ALL, SQLUSMALLINT nReserved = SQL_QUICK );
    virtual SQLRETURN doSpecialColumns( const OQFilter &stringFilter, SQLSMALLINT nIdentifierType = SQL_BEST_ROWID, SQLSMALLINT nScope = SQL_SCOPE_CURROW, SQLSMALLINT nNullable = SQL_NULLABLE );
    virtual SQLRETURN doPrimaryKeys( const OQFilter &stringFilter );
    virtual SQLRETURN doForeignKeys( const OQFilter &stringFilter );
    virtual SQLRETURN doProcedures( const OQFilter &stringFilter );
    virtual SQLRETURN doProcedureColumns( const OQFilter &stringFilter );

    //
    static void getParsedFilter( const OQFilter &stringFilter, QString *pstringCatalog, QString *pstringSchema, QString *pstringObject );

    // DOERS
    virtual bool doWaiting();

signals:
    void signalMessage( ODBCMessage Message );
    void signalDiagnostic( ODBCDiagnostic Diagnostic );
    void signalElapsedSeconds( double nElapsedSeconds );
    void signalResults( OQStatement *pstatement );

public slots:
    SQLRETURN slotExecute( const QString &stringSQL );

protected:
    virtual void eventMessage( ODBCMessage Message );
    virtual void eventDiagnostic();
};

#endif


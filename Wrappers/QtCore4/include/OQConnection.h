/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef OQCONNECTION_H
#define OQCONNECTION_H

// libqt
#include <QtCore>

// libodbcplus
#include <ODBCConnection.h>

//
#include "OQEnvironment.h"

class OQStatement;

/*! 
 * \class   OQConnection
 * \brief   An ODBC connection.
 *
 *          This class extends ODBCConnection by providing a more Qt friendly interface. For
 *          example;
 *
 *          \li uses Qt data types where possible
 *          \li provides several Qt signals
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 *
 *          This class does not provide any User Interface code - see QtGui4 layer for those bits.
 */
class OQConnection : public QObject, public ODBCConnection
{
    Q_OBJECT
public:
    OQConnection( OQEnvironment *penvironment );
    virtual ~OQConnection();

    // SETTERS
    virtual void setPromptDriver( bool bPrompt ) { bPromptDriver = bPrompt; }
    virtual void setPromptDataSourceName( bool bPrompt ) { bPromptDataSourceName = bPrompt; }
    virtual void setPromptUserID( bool bPrompt ) { bPromptUserID = bPrompt; }
    virtual void setPromptPassword( bool bPrompt ) { bPromptPassword = bPrompt; }

    // GETTERS
    virtual OQStatement *getExecute( const QString &stringSQL );
    virtual OQStatement *getCatalogs();
    virtual OQStatement *getSchemas( const QString &stringCatalog = QString::null );
    virtual OQStatement *getTables( const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null, const QString &stringType = "TABLE" );
    virtual OQStatement *getViews( const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null, const QString &stringType = "VIEW" );
    virtual OQStatement *getColumns( const QString &stringTable = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null, const QString &stringType = "TABLE" );
    virtual OQStatement *getIndexs( const QString &stringTable = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getPrimaryKeys( const QString &stringTable = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getForeignKeys( const QString &stringTable = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getSpecialColumns( const QString &stringTable = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getProcedures( const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getProcedureColumns( const QString &stringProcedure = QString::null, const QString &stringSchema = QString::null, const QString &stringCatalog = QString::null );
    virtual OQStatement *getDataTypes();

    virtual bool        getPromptDriver() { return bPromptDriver; }
    virtual bool        getPromptDataSourceName() { return bPromptDataSourceName; }
    virtual bool        getPromptUserID() { return bPromptUserID; }
    virtual bool        getPromptPassword() { return bPromptPassword; }

    virtual QString getDSN() { return stringDSN; }
    virtual QString getUID() { return stringUID; }
    virtual QString getPWD() { return stringPWD; }

    // DOERS
    // we replace ODBCConnection versions of these so as to emit connect/disconnect signals
    virtual SQLRETURN doConnect( ODBCCHAR *pszServerName = NULL, SQLSMALLINT nLength1 = SQL_NTS, ODBCCHAR *pszUserName = NULL, SQLSMALLINT nLength2 = SQL_NTS, ODBCCHAR *pszAuthentication = NULL, SQLSMALLINT nLength3 = SQL_NTS );
    virtual SQLRETURN doBrowseConnect( ODBCCHAR *szInConnectionString, SQLSMALLINT nStringLength1, ODBCCHAR *szOutConnectionString, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength2Ptr );
    virtual SQLRETURN doDriverConnect( SQLHWND hWnd, ODBCCHAR *pszIn, SQLSMALLINT nLengthIn, ODBCCHAR *pszOut, SQLSMALLINT nLengthOut, SQLSMALLINT *pnLengthOut, SQLUSMALLINT nPrompt );
    virtual SQLRETURN doDisconnect();
    // we layer these on top of the above to support QString
    virtual SQLRETURN doConnect( const QString &stringServerName = QString::null, const QString &stringUserName = QString::null, const QString &stringAuthentication = QString::null );
    virtual SQLRETURN doBrowseConnect( const QString &stringIn, QString *pstringOut );
    virtual SQLRETURN doDriverConnect( SQLHWND hWnd, const QString &stringIn, QString *pstringOut, SQLUSMALLINT nPrompt );

signals:
    void signalMessage( ODBCMessage Message );
    void signalDiagnostic( ODBCDiagnostic Diagnostic );
    void signalConnected();
    void signalDisconnected();

protected:
    // Used by doConnect() and doBrowseConnect()
    bool                bPromptDriver;
    bool                bPromptDataSourceName;
    // Used by doConnect()
    bool                bPromptUserID;
    bool                bPromptPassword;
    // These reflect the current connection. null if no connection.
    QString             stringDSN;
    QString             stringUID;
    QString             stringPWD;
    QString             stringConnectString;

    virtual void eventMessage( ODBCMessage Message );
    virtual void eventDiagnostic();
};

#endif


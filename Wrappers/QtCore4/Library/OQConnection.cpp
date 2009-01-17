/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "OQEnvironment.h"
#include "OQConnection.h"
#include "OQStatement.h"

OQConnection::OQConnection( OQEnvironment *penvironment )
    : QObject( 0 ), ODBCConnection( penvironment )
{
    setObjectName( "OQConnection" );

    bPromptDriver           = true;
    bPromptDataSourceName   = true;
    bPromptUserID           = true;
    bPromptPassword         = true;

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(ODBCMessage Message)), penvironment, SIGNAL(signalMessage(ODBCMessage Message)) );
    connect( this, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)), penvironment, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)) );
}

OQConnection::~OQConnection()
{
}

/*!
    getExecute
    
    Creates a result set (or NULL if there was an error).
    See OQStatement::getTables.
*/
OQStatement *OQConnection::getExecute( const QString &stringSQL )
{
    OQStatement *    pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->slotExecute( stringSQL );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
    OQStatement *   pStatement = 0;
    SQLRETURN           nReturn;

    if ( !isConnected() )
    {
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
        return 0;
    }

    pStatement = new OQStatement( this );
    nReturn = pStatement->doSpecialColumns( SQL_BEST_ROWID, stringCatalog, stringSchema, stringTable );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Not connected.") ) );
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
    doConnect
    
    This replaces ODBCConnection::doConnect but does the same thing. This
    method also emits signalConnected() if things worked out.
*/
SQLRETURN OQConnection::doConnect( ODBCCHAR *pszServerName, SQLSMALLINT nLength1, ODBCCHAR *pszUserName, SQLSMALLINT nLength2, ODBCCHAR *pszAuthentication, SQLSMALLINT nLength3 )
{
    SQLRETURN nReturn = ODBCConnection::doConnect( pszServerName, nLength1, pszUserName, nLength2, pszAuthentication, nLength3 );

    if ( isConnected() )
    {
        stringDSN = OQToQString( pszServerName );
        stringUID = OQToQString( pszUserName );
        stringPWD = OQToQString( pszAuthentication );
        emit signalConnected();
    }

    return nReturn;
}

/*!
    doBrowseConnect
    
    This replaces ODBCConnection::doBrowseConnect but does the same thing. This
    method also emits signalConnected() if things worked out.
*/
SQLRETURN OQConnection::doBrowseConnect( ODBCCHAR *szInConnectionString, SQLSMALLINT nStringLength1, ODBCCHAR *szOutConnectionString, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLength2Ptr )
{
    SQLRETURN nReturn = ODBCConnection::doBrowseConnect( szInConnectionString, nStringLength1, szOutConnectionString, nBufferLength, pnStringLength2Ptr );

    if ( isConnected() )
    {
        stringConnectString = OQToQString( szOutConnectionString );
        emit signalConnected();
    }

    return nReturn;
}

/*!
    doDriverConnect
    
    This replaces ODBCConnection::doDriverConnect but does the same thing. This
    method also emits signalConnected() if things worked out.
*/
SQLRETURN OQConnection::doDriverConnect( SQLHWND hWnd, ODBCCHAR *pszIn, SQLSMALLINT nLengthIn, ODBCCHAR *pszOut, SQLSMALLINT nLengthOut, SQLSMALLINT *pnLengthOut, SQLUSMALLINT nPrompt )
{
    SQLRETURN nReturn = ODBCConnection::doDriverConnect( hWnd, pszIn, nLengthIn, pszOut, nLengthOut, pnLengthOut, nPrompt );

    if ( isConnected() )
        emit signalConnected();

    return nReturn;
}

/*!
    doDisconnect
    
    This replaces ODBCCOnnection::doDisconnect but does the same thing. This
    method also emits signalDisconnected() if things worked out.
*/
SQLRETURN OQConnection::doDisconnect()
{
    SQLRETURN nReturn = ODBCConnection::doDisconnect();

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

/*!
    doConnect

    Allows the use of QString instead of ODBCCHAR* but otherwise does
    same thing.
*/
SQLRETURN OQConnection::doConnect( const QString &stringDSN, const QString &stringUID, const QString &stringPWD )
{
    ODBCCHAR *pszDSN = (ODBCCHAR*)TEXT("");
    ODBCCHAR *pszUID = (ODBCCHAR*)TEXT("");
    ODBCCHAR *pszPWD = (ODBCCHAR*)TEXT("");

    if ( !stringDSN.isEmpty() )
        pszDSN = OQFromQString(stringDSN);
    if ( !stringUID.isEmpty() )
        pszUID = OQFromQString(stringUID);
    if ( !stringPWD.isEmpty() )
        pszPWD = OQFromQString(stringPWD);

    return doConnect( pszDSN, SQL_NTS, pszUID, SQL_NTS, pszPWD, SQL_NTS );
}

/*!
    doBrowseConnect
    
    Allows the use of QString instead of ODBCCHAR* but otherwise does
    same thing.
*/
SQLRETURN OQConnection::doBrowseConnect( const QString &stringIn, QString *pstringOut )
{
    ODBCCHAR *      pszIn       = (ODBCCHAR*)TEXT("");
    ODBCCHAR        szOut[4096];
    SQLSMALLINT     nLengthIn   = 0;
    SQLSMALLINT     nLengthOut;

    *szOut = '\0';

    if ( !stringIn.isEmpty() )
    {
        pszIn       = OQFromQString(stringIn);
        nLengthIn   = stringIn.length();
    }

    SQLRETURN nReturn = doBrowseConnect( pszIn, nLengthIn, szOut, sizeof(szOut), &nLengthOut ); 
    if ( nReturn == SQL_NEED_DATA )
    {
        *pstringOut = OQToQString(szOut);
    }

    return nReturn;
}

/*!
    doDriverConnect

    Allows the use of QString instead of ODBCCHAR* but otherwise does
    same thing.
    
    NOTE: We do not have OQ++ based prompting for Driver Connect because 
          the whole reason for using it is to have the Driver do the 
          prompting. The exception to this is that the Driver Manager will
          prompt for DSN, DRV, or FILEDSN if the stringIn is empty. In anycase;
          OQ++ probably should NOT do any prompting.
          
          The down side of this is that applications calling a Driver Connect
          method are unlikley to be portable without the application taking
          further measures. This is because the Driver Manager and the Driver
          may not support any kind of prompting - often the case on UNIX.
*/
SQLRETURN OQConnection::doDriverConnect( SQLHWND hWnd, const QString &stringIn, QString *pstringOut, SQLUSMALLINT nPrompt )
{
    ODBCCHAR *      pszIn       = (ODBCCHAR*)TEXT("");
    ODBCCHAR        szOut[4096];
    SQLSMALLINT     nLengthIn   = 0;
    SQLSMALLINT     nLengthOut;

    if ( !stringIn.isEmpty() )
    {
        pszIn       = OQFromQString(stringIn);
        nLengthIn   = stringIn.length();
    }

    SQLRETURN nReturn = doDriverConnect( hWnd, pszIn, nLengthIn, szOut, sizeof(szOut), &nLengthOut, nPrompt ); 
    if ( nReturn == SQL_NEED_DATA )
    {
        *pstringOut = OQToQString(szOut);
    }

    return nReturn;
}

void OQConnection::eventMessage( ODBCMessage Message )
{
    emit signalMessage( Message );
}

void OQConnection::eventDiagnostic()
{
    emit signalDiagnostic( ODBCDiagnostic( this ) );
}



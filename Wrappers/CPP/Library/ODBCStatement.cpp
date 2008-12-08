/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */

#include "ODBCStatement.h"
#include "ODBCEnvironment.h"
#include "ODBCConnection.h"

#ifndef WIN32
    #include <unistd.h>
#endif

/*! 
 * \brief   Constructs an ODBCStatement.
 * 
 *          The underlying statement is not allocated until needed or until
 *          an explicit call to \sa doAlloc. An explicit call is not usually
 *          needed.
 *
 * \sa      doAlloc
 */
ODBCStatement::ODBCStatement( ODBCConnection *pConnection )
    : ODBCHandle( ODBCHandle::Stm, pConnection )
{
    nElapsedSeconds = 0;
}

ODBCStatement::~ODBCStatement()
{
}

SQLRETURN ODBCStatement::setAttrAsyncEnable( AttrAsyncEnableTypes n )
{
    return setStmtAttr( SQL_ATTR_ASYNC_ENABLE, (SQLPOINTER)n, 0 );
}

SQLRETURN ODBCStatement::setAttrConcurrency( AttrConcurrencyTypes n )
{
    return setStmtAttr( SQL_ATTR_CONCURRENCY, (SQLPOINTER)n, 0 );
}


SQLRETURN ODBCStatement::setStmtAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    return setStmtAttr( (SQLINTEGER)nAttribute, pValue, nStringLength );
}

SQLRETURN ODBCStatement::setStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLSetStmtAttr( getHandle(), nAttribute, pValue, nStringLength );
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

SQLRETURN ODBCStatement::getAttrAsyncEnable( AttrAsyncEnableTypes *pn )
{
    return getStmtAttr( SQL_ATTR_ASYNC_ENABLE, pn, 0, NULL );
}

SQLRETURN ODBCStatement::getAttrConcurrency( AttrConcurrencyTypes *pn )
{
    return getStmtAttr( SQL_ATTR_CONCURRENCY, pn, 0, NULL );
}

SQLRETURN ODBCStatement::getStmtAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength )
{
    return getStmtAttr( (SQLINTEGER)nAttribute, pValue, nBufferLength, pnStringLength );
}

SQLRETURN ODBCStatement::getStmtAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetStmtAttr( getHandle(), nAttribute, pValue, nBufferLength, pnStringLength );
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

ODBCConnection *ODBCStatement::getConnection()
{ 
    return (ODBCConnection*)phandleParent;
}

double ODBCStatement::getElapsedSeconds() 
{
    return nElapsedSeconds; 
}

SQLRETURN ODBCStatement::doExecute()
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;

    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLExecute( getHandle() );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
                break;
            case SQL_NEED_DATA:
            case SQL_NO_DATA:
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
    } // while

    return nReturn;
}

SQLRETURN ODBCStatement::doExecDirect( ODBCCHAR *pszStatement, SQLINTEGER nLength )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLExecDirect( getHandle(), pszStatement, nLength );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
                break;
            case SQL_NO_DATA:
            case SQL_NEED_DATA:
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doTables( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, ODBCCHAR *pszTableType, SQLSMALLINT nLength4 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;

    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLTables( getHandle(), pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, pszTableType, nLength4 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doColumns( const ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, const ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, const ODBCCHAR *pszTableName, SQLSMALLINT nLength3, const ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLColumns( getHandle(), (ODBCCHAR*)pszCatalogName, nLength1, (ODBCCHAR*)pszSchemaName, nLength2, (ODBCCHAR*)pszTableName, nLength3, (ODBCCHAR*)pszColumnName, nLength4 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doStatistics( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLUSMALLINT nUnique, SQLUSMALLINT nReserved )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLStatistics( getHandle(), pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, nUnique, nReserved );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doSpecialColumns( SQLSMALLINT nIdentifierType, ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3, SQLSMALLINT nScope, SQLSMALLINT nNullable )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLSpecialColumns( getHandle(), nIdentifierType, pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3, nScope, nNullable );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doPrimaryKeys( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszTableName, SQLSMALLINT nLength3 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLPrimaryKeys( getHandle(), pszCatalogName, nLength1, pszSchemaName, nLength2, pszTableName, nLength3 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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

    } // while

    return nReturn;
}

SQLRETURN ODBCStatement::doForeignKeys( ODBCCHAR *pszPKCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszPKSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszPKTableName, SQLSMALLINT nLength3, ODBCCHAR *pszFKCatalogName, SQLSMALLINT nLength4, ODBCCHAR *pszFKSchemaName, SQLSMALLINT nLength5, ODBCCHAR *pszFKTableName, SQLSMALLINT nLength6 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLForeignKeys( getHandle(), pszPKCatalogName, nLength1, pszPKSchemaName, nLength2, pszPKTableName, nLength3, pszFKCatalogName, nLength4, pszFKSchemaName, nLength5, pszFKTableName, nLength6 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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

    } // while

    return nReturn;
}

SQLRETURN ODBCStatement::doProcedures( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLProcedures( getHandle(), pszCatalogName, nLength1, pszSchemaName, nLength2, pszProcName, nLength3 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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

    } // while

    return nReturn;
}

SQLRETURN ODBCStatement::doProcedureColumns( ODBCCHAR *pszCatalogName, SQLSMALLINT nLength1, ODBCCHAR *pszSchemaName, SQLSMALLINT nLength2, ODBCCHAR *pszProcName, SQLSMALLINT nLength3, ODBCCHAR *pszColumnName, SQLSMALLINT nLength4 )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLProcedureColumns( getHandle(), pszCatalogName, nLength1, pszSchemaName, nLength2, pszProcName, nLength3, pszColumnName, nLength4 );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doTypeInfo( SQLSMALLINT nDataType )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    time_t      timeStart;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    time( &timeStart );
    nElapsedSeconds = 0;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLGetTypeInfo( getHandle(), nDataType );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                break;
            case SQL_SUCCESS_WITH_INFO:
                nElapsedSeconds = difftime( time( NULL ), timeStart );
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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

    } // while

    return nReturn;
}

SQLRETURN ODBCStatement::doFetch()
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLFetch( getHandle() );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
                break;
            case SQL_NO_DATA:
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doData( SQLUSMALLINT nColumnNumber, SQLSMALLINT nTargetType, SQLPOINTER pTargetValuePtr, SQLLEN nBufferLength, SQLLEN *pnStrLenOrIndPtr )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLGetData( getHandle(), nColumnNumber, nTargetType, pTargetValuePtr, nBufferLength, pnStrLenOrIndPtr );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
                break;
            case SQL_NO_DATA:
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doData( SQLUSMALLINT nCol, ODBCVariant *p, bool bExpand )
{
    SQLRETURN   nReturn = SQL_SUCCESS;
    SQLLEN      nIndicator;

    if ( bExpand )
    {
        /*! \todo chunk data - expand buffer as needed */
    }
    else
    {
        nReturn = doData( nCol, p->getType(), p->getBuffer(), p->getElementsMax() * p->getElementBytes( p->getType() ), &nIndicator );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
            case SQL_SUCCESS_WITH_INFO:
                // no data
                if ( nIndicator == SQL_NULL_DATA )
                    p->clear();
                // filled our buffer and there is more data...
                else if ( nIndicator == SQL_NO_TOTAL )
                    p->setElements( p->getElementsMax() );
                // filled (or partially filled) our buffer and no more data...
                else
                    p->setElements( nIndicator );
                break;
            case SQL_ERROR:
            case SQL_INVALID_HANDLE:
            case SQL_NO_DATA:
            default:
                p->clear();
                break;
        }
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doColAttribute( SQLUSMALLINT nColumnNumber, SQLUSMALLINT nFieldIdentifier, SQLPOINTER nCharacterAttributePtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr, SQLLEN *pnNumericAttributePtr )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLColAttribute( getHandle(), nColumnNumber, nFieldIdentifier, nCharacterAttributePtr, nBufferLength, pnStringLengthPtr, pnNumericAttributePtr );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doNumResultCols( SQLSMALLINT *pnColumnCountPtr )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLNumResultCols( getHandle(), pnColumnCountPtr );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doRowCount( SQLLEN *pnRowCountPtr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLRowCount( getHandle(), pnRowCountPtr );
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

SQLRETURN ODBCStatement::doCloseCursor()
{
    if ( !isAlloc() )
        return SQL_ERROR;

    // DO IT
    SQLRETURN nReturn;

    nReturn = SQLCloseCursor( getHandle() );
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

SQLRETURN ODBCStatement::doPrepare( ODBCCHAR *pszStatementText, SQLINTEGER nTextLength )
{
    bool        bCancelled  = false;
    SQLRETURN   nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    // do it
    nReturn = SQL_STILL_EXECUTING;
    while ( nReturn == SQL_STILL_EXECUTING )
    {
        nReturn = SQLPrepare( getHandle(), pszStatementText, nTextLength );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                eventDiagnostic();
                break;
            case SQL_STILL_EXECUTING:
                if ( !bCancelled && !doWaiting() )
                {
                    if ( SQL_SUCCEEDED( doCancel() ) )
                        bCancelled = true;  // Cancelled! We still need to loop to give the driver time to cleanup.
                }
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
    }

    return nReturn;
}

SQLRETURN ODBCStatement::doBindCol( SQLUSMALLINT nColumnNumber, SQLSMALLINT nTargetType, SQLPOINTER pTargetValuePtr, SQLLEN nBufferLength, SQLLEN *pnStrLen_or_Ind )
{
    SQLRETURN nReturn;
    
    if ( !isAlloc() )
        return SQL_ERROR;

    nReturn = SQLBindCol( getHandle(), nColumnNumber, nTargetType, pTargetValuePtr, nBufferLength, pnStrLen_or_Ind );
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

SQLRETURN ODBCStatement::doCancel()
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLCancel( getHandle() );
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

SQLRETURN ODBCStatement::doAlloc()
{
    SQLRETURN nReturn = ODBCHandle::doAlloc();
    if ( !SQL_SUCCEEDED( nReturn ) )
        return nReturn;

    // PAH - temp to get MS SQL Server to allow multiple active statements
    // SQL_CONCUR_READ_ONLY, SQL_CONCUR_ROWVER, SQL_CONCUR_VALUES, or SQL_CONCUR_LOCK.
    SQLSetStmtAttr( getHandle(), SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC, 0 );
    SQLSetStmtAttr( getHandle(), SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, 0 );

    return nReturn;
}

SQLRETURN ODBCStatement::doFree( SQLUSMALLINT n )
{
    if ( !isAlloc( false ) )
    {
        eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Handle not allocated.") ) );
        return SQL_ERROR;
    }

    SQLRETURN nReturn = SQLFreeStmt( getHandle(), n ); 
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

bool ODBCStatement::isCursor()
{
    SQLSMALLINT nColumns    = -1;
    SQLRETURN   nReturn     = doNumResultCols( &nColumns );

    if ( SQL_SUCCEEDED( nReturn ) && nColumns > 0 )
        return true;

    return false;
}

/*!
    Do something between asynch calls.
    
    This gets called each iteration through a polling loop when the
    ODBC asynch option is turned on and the driver supports asynch calls.
    
    So one could derive a new class from here and replace doWaiting()
    with something more useful.
    
    Whatever is done in here should not take more than a moment to process
    because we want to check out the progress of our asynch call fairly
    frequently... perhaps every second or so.
    
    Return false to cancel asynch operation.
*/
bool ODBCStatement::doWaiting()
{
    // i want to know if a driver actually supports asynch these days...
    printf( "[PAH][%s][%d] Looks like asynch option supported by this driver.\n", __FILE__, __LINE__ );
    // just slow the polling down a bit
#ifdef _WINDOWS_
    Sleep( 1000 );
#else
    sleep( 1000 ); 
#endif
    return true;
}



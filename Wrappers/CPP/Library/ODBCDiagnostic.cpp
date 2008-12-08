/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \version 1
 * \date    2008
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCDiagnostic.h"

ODBCDiagnosticRecord::ODBCDiagnosticRecord( ODBCDiagnostic *pDiagnostic, SQLINTEGER nRecord )
{
    this->pDiagnostic   = pDiagnostic;
    this->nRecord       = nRecord;
}

ODBCCHAR *ODBCDiagnosticRecord::getClassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ClassOrigin, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER ODBCDiagnosticRecord::getColumnNumber( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( ColumnNumber, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *ODBCDiagnosticRecord::getConnectionName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ConnectionName, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCCHAR *ODBCDiagnosticRecord::getMessageText( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( MessageText, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER ODBCDiagnosticRecord::getNative( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( Native, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLLEN ODBCDiagnosticRecord::getRowNumber( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( RowNumber, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *ODBCDiagnosticRecord::getServerName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ServerName, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCCHAR *ODBCDiagnosticRecord::getSqlstate( ODBCCHAR *psz /* better be 5 chars */, SQLRETURN *pnReturn )
{
    if ( psz )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( Sqlstate, psz, 5, NULL );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCString  ODBCDiagnosticRecord::getSqlstate( SQLRETURN *pnReturn )
{
    ODBCString s;

    s.resize( 6, '\0' );
    SQLRETURN nReturn = getDiagField( Sqlstate, (ODBCCPTR)s.c_str(), 5, NULL );

    if ( pnReturn )
        *pnReturn = nReturn;

    return s;
}

ODBCCHAR *ODBCDiagnosticRecord::getSubclassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( SubclassOrigin, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLRETURN ODBCDiagnosticRecord::getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    return getDiagField( (SQLSMALLINT)nField, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
}

SQLRETURN ODBCDiagnosticRecord::getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    if ( !pDiagnostic->pHandle->isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetDiagField( (SQLSMALLINT)pDiagnostic->pHandle->getType(), pDiagnostic->pHandle->getHandle(), nRecord, nDiagIdentifier, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            pDiagnostic->pHandle->eventMessage( ODBCMessage( ODBCMessage::Warning, TEXT(__FUNCTION__), TEXT("SQL_SUCCESS_WITH_INFO") ) );
            break;
        case SQL_ERROR:
            pDiagnostic->pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_ERROR") ) );
            break;
        case SQL_INVALID_HANDLE:
            pDiagnostic->pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            pDiagnostic->pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

ODBCDiagnostic::ODBCDiagnostic( ODBCHandle *pHandle )
{
    this->pHandle = pHandle;
}

SQLLEN ODBCDiagnostic::getCursorRowCount( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( CursorRowCount, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *ODBCDiagnostic::getDynamicFunction( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( DynamicFunction, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER ODBCDiagnostic::getDynamicFunctionCode( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( DynamicFunctionCode, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLINTEGER ODBCDiagnostic::getNumber( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( Number, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLRETURN ODBCDiagnostic::getReturncode( SQLRETURN *pn )
{
    SQLRETURN   n       = SQL_SUCCESS;
    SQLRETURN   nReturn = getDiagField( Returncode, &n, SQL_IS_INTEGER /* no SQL_IS_RETURNCODE! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLLEN ODBCDiagnostic::getRowCount( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( RowCount, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLRETURN ODBCDiagnostic::getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    return getDiagField( (SQLSMALLINT)nField, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
}

SQLRETURN ODBCDiagnostic::getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    if ( !pHandle->isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetDiagField( pHandle->getType(), pHandle->getHandle(), 0, nDiagIdentifier, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            pHandle->eventMessage( ODBCMessage( ODBCMessage::Warning, TEXT(__FUNCTION__), TEXT("SQL_SUCCESS_WITH_INFO") ) );
            break;
        case SQL_ERROR:
            pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_ERROR") ) );
            break;
        case SQL_INVALID_HANDLE:
            pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            pHandle->eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}




/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \version 1
 * \date    2008
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#include "OQDiagnostic.h"

OQDiagnosticRecord::OQDiagnosticRecord( OQDiagnostic *pDiagnostic, SQLINTEGER nRecord )
{
    this->pDiagnostic   = pDiagnostic;
    this->nRecord       = nRecord;
}

ODBCCHAR *OQDiagnosticRecord::getClassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ClassOrigin, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER OQDiagnosticRecord::getColumnNumber( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( ColumnNumber, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *OQDiagnosticRecord::getConnectionName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ConnectionName, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCCHAR *OQDiagnosticRecord::getMessageText( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( MessageText, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER OQDiagnosticRecord::getNative( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( Native, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLLEN OQDiagnosticRecord::getRowNumber( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( RowNumber, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *OQDiagnosticRecord::getServerName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( ServerName, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCCHAR *OQDiagnosticRecord::getSqlstate( ODBCCHAR *psz /* better be 5 chars */, SQLRETURN *pnReturn )
{
    if ( psz )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( Sqlstate, psz, 5, NULL );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

ODBCString  OQDiagnosticRecord::getSqlstate( SQLRETURN *pnReturn )
{
    ODBCString s;

    s.resize( 6, '\0' );
    SQLRETURN nReturn = getDiagField( Sqlstate, (ODBCCPTR)s.c_str(), 5, NULL );

    if ( pnReturn )
        *pnReturn = nReturn;

    return s;
}

ODBCCHAR *OQDiagnosticRecord::getSubclassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( SubclassOrigin, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLRETURN OQDiagnosticRecord::getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    return getDiagField( (SQLSMALLINT)nField, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
}

SQLRETURN OQDiagnosticRecord::getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
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
            pDiagnostic->pHandle->eventMessage( OQMessage( OQMessage::Warning, TEXT(__FUNCTION__), TEXT("SQL_SUCCESS_WITH_INFO") ) );
            break;
        case SQL_ERROR:
            pDiagnostic->pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_ERROR") ) );
            break;
        case SQL_INVALID_HANDLE:
            pDiagnostic->pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            pDiagnostic->pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

OQDiagnostic::OQDiagnostic( OQHandle *pHandle )
{
    this->pHandle = pHandle;
}

SQLLEN OQDiagnostic::getCursorRowCount( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( CursorRowCount, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

ODBCCHAR *OQDiagnostic::getDynamicFunction( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes, SQLRETURN *pnReturn )
{
    if ( psz && nMaxBytes >= sizeof(ODBCCHAR) )
        *psz = '\0';

    SQLRETURN nReturn = getDiagField( DynamicFunction, psz, nMaxBytes, pnRequiredBytes );

    if ( pnReturn )
        *pnReturn = nReturn;

    return psz;
}

SQLINTEGER OQDiagnostic::getDynamicFunctionCode( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( DynamicFunctionCode, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLINTEGER OQDiagnostic::getNumber( SQLRETURN *pn )
{
    SQLINTEGER  n       = 0;
    SQLRETURN   nReturn = getDiagField( Number, &n, SQL_IS_INTEGER, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLRETURN OQDiagnostic::getReturncode( SQLRETURN *pn )
{
    SQLRETURN   n       = SQL_SUCCESS;
    SQLRETURN   nReturn = getDiagField( Returncode, &n, SQL_IS_INTEGER /* no SQL_IS_RETURNCODE! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLLEN OQDiagnostic::getRowCount( SQLRETURN *pn )
{
    SQLLEN      n       = 0;
    SQLRETURN   nReturn = getDiagField( RowCount, &n, SQL_IS_INTEGER /* no SQL_IS_LEN! */, NULL );

    if ( pn )
        *pn = nReturn;

    return n;
}

SQLRETURN OQDiagnostic::getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
{
    return getDiagField( (SQLSMALLINT)nField, pnDiagInfoPtr, nBufferLength, pnStringLengthPtr );
}

SQLRETURN OQDiagnostic::getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr )
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
            pHandle->eventMessage( OQMessage( OQMessage::Warning, TEXT(__FUNCTION__), TEXT("SQL_SUCCESS_WITH_INFO") ) );
            break;
        case SQL_ERROR:
            pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_ERROR") ) );
            break;
        case SQL_INVALID_HANDLE:
            pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            pHandle->eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}




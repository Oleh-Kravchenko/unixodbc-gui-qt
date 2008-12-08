/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \version 1
 * \date    2008
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCDIAGNOSTIC_H
#define ODBCDIAGNOSTIC_H

#include "ODBCHandle.h"

class ODBCDiagnostic;

/*! 
 * \class   ODBCDiagnosticRecord
 * \brief   An ODBC diagnostic record.
 *
 *          This class is an interface to the ODBC diagnostic record information. The data is 'lazy loaded'
 *          or in other words - loaded only as requested. This means that this class should not be
 *          used if the parent \sa ODBCDiagnostic becomes invalid.
 *
 * \sa      ODBCDiagnostic
 */
class ODBCDiagnosticRecord
{
public:
    enum Fields
    {
        ClassOrigin     = SQL_DIAG_CLASS_ORIGIN,
        ColumnNumber    = SQL_DIAG_COLUMN_NUMBER,
        ConnectionName  = SQL_DIAG_CONNECTION_NAME,
        MessageText     = SQL_DIAG_MESSAGE_TEXT,
        Native          = SQL_DIAG_NATIVE,
        RowNumber       = SQL_DIAG_ROW_NUMBER,
        ServerName      = SQL_DIAG_SERVER_NAME,
        Sqlstate        = SQL_DIAG_SQLSTATE,
        SubclassOrigin  = SQL_DIAG_SUBCLASS_ORIGIN
    };

    explicit ODBCDiagnosticRecord( ODBCDiagnostic *pDiagnostic, SQLINTEGER nRecord );

    ODBCCHAR *  getClassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    SQLINTEGER  getColumnNumber( SQLRETURN *pn = NULL );
    ODBCCHAR *  getConnectionName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    ODBCCHAR *  getMessageText( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    SQLINTEGER  getNative( SQLRETURN *pn = NULL );
    SQLLEN      getRowNumber( SQLRETURN *pn = NULL );
    ODBCCHAR *  getServerName( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    ODBCCHAR *  getSqlstate( ODBCCHAR *psz /* better be 5 chars */, SQLRETURN *pnReturn = NULL );
    ODBCString  getSqlstate( SQLRETURN *pnReturn = NULL );
    ODBCCHAR *  getSubclassOrigin( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    SQLRETURN   getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr );
    SQLRETURN   getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr );

protected:
    ODBCDiagnostic *pDiagnostic;
    SQLINTEGER      nRecord;
};

/*! 
 * \class   ODBCDiagnostic
 * \brief   ODBC diagnostic information.
 *
 *          This class is an interface to the ODBC diagnostic information usually requested upon
 *          receiving a SQL_ERROR or SQL_SUCCESS_WITH_INFO return code. The data is 'lazy loaded'
 *          or in other words - loaded only as requested. This means that this class should not be
 *          used if the parent (Environemment/Connection/Statement) becomes invalid.
 * 
 * \sa      ODBCDiagnosticRecord
 * 
 * \author  pharvey (8/15/2008)
 */
class ODBCDiagnostic
{
    friend class ODBCDiagnosticRecord;
public:
    enum Fields
    {
        CursorRowCount      = SQL_DIAG_CURSOR_ROW_COUNT,
        DynamicFunction     = SQL_DIAG_DYNAMIC_FUNCTION,
        DynamicFunctionCode = SQL_DIAG_DYNAMIC_FUNCTION_CODE,
        Number              = SQL_DIAG_NUMBER,
        Returncode          = SQL_DIAG_RETURNCODE,
        RowCount            = SQL_DIAG_ROW_COUNT
    };

    explicit ODBCDiagnostic( ODBCHandle *pHandle );

    SQLLEN      getCursorRowCount( SQLRETURN *pn = NULL );
    ODBCCHAR *  getDynamicFunction( ODBCCHAR *psz, SQLSMALLINT nMaxBytes, SQLSMALLINT *pnRequiredBytes = NULL, SQLRETURN *pnReturn = NULL );
    SQLINTEGER  getDynamicFunctionCode( SQLRETURN *pn = NULL );
    SQLINTEGER  getNumber( SQLRETURN *pn = NULL );
    SQLRETURN   getReturncode( SQLRETURN *pn = NULL );
    SQLLEN      getRowCount( SQLRETURN *pn = NULL );
    SQLRETURN   getDiagField( Fields nField, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr );
    SQLRETURN   getDiagField( SQLSMALLINT nDiagIdentifier, SQLPOINTER pnDiagInfoPtr, SQLSMALLINT nBufferLength, SQLSMALLINT *pnStringLengthPtr );

protected:
    ODBCHandle *pHandle;
};

#endif




#include "DDiagnostic.h"

#ifdef UNICODE
    #define DTCHAR( a, b ) QString( (const QChar*)a, b );
#else
    #define DTCHAR( a, b ) QString::fromLocal8Bit( (const char*)a );
#endif

DDiagnostic::DDiagnostic( SQLSMALLINT nHandleType, SQLHANDLE hHandle )
{
    SQLRETURN   n;
    SQLINTEGER  nInteger;
    SQLLEN      nLen;
    SQLRETURN   nReturn;
    SQLCHAR     sz[SQL_MAX_MESSAGE_LENGTH + 2];
    SQLSMALLINT nStringLength; // \todo Use this later to avoid text truncation
    SQLINTEGER  nNumber = 0;

    // header fields...
    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_NUMBER, &nNumber, SQL_IS_INTEGER, 0 );
    if ( n != SQL_SUCCESS )
    {
        bNull = true;
        return;
    }

    stringNumber = QString::number( nNumber );
    bNull = false;

    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_CURSOR_ROW_COUNT, &nLen, SQL_IS_INTEGER, 0 );
    if ( n == SQL_SUCCESS ) stringCursorRowCount = QString::number( nLen );

    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_DYNAMIC_FUNCTION, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
    if ( n == SQL_SUCCESS ) { stringDynamicFunction = DTCHAR( sz, nStringLength ); }
    else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; stringDynamicFunction = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }

    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_DYNAMIC_FUNCTION_CODE, &nInteger, SQL_IS_INTEGER, 0 );
    if ( n == SQL_SUCCESS ) stringDynamicFunctionCode = QString::number( nInteger );

    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_RETURNCODE, &nReturn, SQL_IS_SMALLINT, 0 );
    if ( n == SQL_SUCCESS ) stringReturnCode = QString::number( nReturn );

    n = SQLGetDiagField( nHandleType, hHandle, 0, SQL_DIAG_ROW_COUNT, &nLen, SQL_IS_SMALLINT, 0 );
    if ( n == SQL_SUCCESS ) stringRowCount = QString::number( nLen );

    // records...
    for ( SQLSMALLINT nRecord = 1; nRecord <= nNumber; nRecord++ )
//    for ( SQLSMALLINT nRecord = 0; nRecord < 101; nRecord++ )
    {
        DDiagnosticRecord record;

        // record fields...
        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_CLASS_ORIGIN, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringClassOrigin = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringClassOrigin = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }
        else if ( n == SQL_NO_DATA )
            break;

        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_COLUMN_NUMBER, &nInteger, SQL_IS_INTEGER, 0 );
        if ( n == SQL_SUCCESS ) record.stringColumnNumber = QString::number( nInteger );

        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_CONNECTION_NAME, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringConnectionName = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringConnectionName = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }
    
        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_MESSAGE_TEXT, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringMessageText = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringMessageText = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }
    
        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_NATIVE, &nInteger, SQL_IS_INTEGER, 0 );
        if ( n == SQL_SUCCESS ) record.stringNative = QString::number( nInteger );

        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_ROW_NUMBER, &nLen, SQL_IS_INTEGER, 0 );
        if ( n == SQL_SUCCESS ) record.stringRowNumber = QString::number( nLen );

        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_SERVER_NAME, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringServerName = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringServerName = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }
    
        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_SQLSTATE, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringSQLState = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringSQLState = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }
    
        n = SQLGetDiagField( nHandleType, hHandle, nRecord, SQL_DIAG_SUBCLASS_ORIGIN, sz, SQL_MAX_MESSAGE_LENGTH, &nStringLength );
        if ( n == SQL_SUCCESS ) { record.stringSubClassOrigin = DTCHAR( sz, nStringLength ); }
        else if ( n == SQL_SUCCESS_WITH_INFO ) { sz[SQL_MAX_MESSAGE_LENGTH] = '\0'; record.stringSubClassOrigin = DTCHAR( sz, SQL_MAX_MESSAGE_LENGTH ); }

        if ( record.stringSQLState.isEmpty() && record.stringMessageText.isEmpty() )
            continue;

        listRecords.append( record );
    }
}



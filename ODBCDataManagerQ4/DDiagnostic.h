#ifndef DDIAGNOSTIC_H
#define DDIAGNOSTIC_H

#include <QtGui>

#include <sqlext.h>
#include <odbcinstext.h>

#include <ODBCString.h>

class DDiagnosticRecord
{
public:
    QString     stringClassOrigin;
    QString     stringColumnNumber;     // SQLINTEGER
    QString     stringConnectionName;
    QString     stringMessageText;
    QString     stringNative;           // SQLINTEGER
    QString     stringRowNumber;        // SQLLEN
    QString     stringServerName;
    QString     stringSQLState;
    QString     stringSubClassOrigin;
};


class DDiagnostic 
{
public:
    DDiagnostic( SQLSMALLINT nHandleType, SQLHANDLE hHandle );

    bool        bNull;

    QString     stringCursorRowCount;       // SQLLEN
    QString     stringDynamicFunction;
    QString     stringDynamicFunctionCode;  // SQLINTEGER
    QString     stringNumber;               // SQLINTEGER
    QString     stringReturnCode;           // SQLRETURN
    QString     stringRowCount;             // SQLLEN

    QList<DDiagnosticRecord> listRecords;
};

#endif


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

OQEnvironment::OQEnvironment( OQSystem *pSystem )
    : QObject( pSystem ), ODBCEnvironment()
{
    setObjectName( "OQEnvironment" );

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(ODBCMessage Message)), pSystem, SIGNAL(signalMessage(ODBCMessage Message)) );
    connect( this, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)), pSystem, SIGNAL(signalDiagnostic(ODBCDiagnostic Diagnostic)) );
}

OQEnvironment::~OQEnvironment()
{
}

QStringList OQEnvironment::getDrivers( SQLRETURN *pnReturn )
{
    QStringList     stringlistDrivers;
    SQLRETURN       nReturn;
    ODBCCHAR        szDRV[101];
    SQLSMALLINT     nLength1;
    ODBCCHAR        szAttribute[301];
    SQLSMALLINT     nLength2;

    nReturn = ODBCEnvironment::doDrivers( SQL_FETCH_FIRST, szDRV, sizeof(szDRV) - 1, &nLength1, szAttribute, sizeof(szAttribute) - 1, &nLength2 );
    while ( SQL_SUCCEEDED( nReturn ) )
    {
        stringlistDrivers.append( OQToQString( szDRV ) );
        nReturn = ODBCEnvironment::doDrivers( SQL_FETCH_NEXT, szDRV, sizeof(szDRV) - 1, &nLength1, szAttribute, sizeof(szAttribute) - 1, &nLength2 );
    }

    if ( pnReturn )
        *pnReturn = nReturn;

    return stringlistDrivers;
}

/*!
    Qt friendly way to get a list of DSN's. 
*/
QStringList OQEnvironment::getDataSources( bool bUser, bool bSystem, SQLRETURN *pnReturn )
{
    QStringList     stringlistDataSources;
    SQLRETURN       nReturn;
    SQLUSMALLINT    nDirection  =   SQL_FETCH_FIRST;
    ODBCCHAR        szDSN[101];
    SQLSMALLINT     nLength1;
    ODBCCHAR        szDescription[101];
    SQLSMALLINT     nLength2;

    if ( bUser || bSystem )
    {
#ifndef Q_WS_MACX
        if ( !bUser && bSystem )
            nDirection = SQL_FETCH_FIRST_SYSTEM;
        else if ( bUser && !bSystem )
            nDirection = SQL_FETCH_FIRST_USER;
#endif

        nReturn = ODBCEnvironment::doDataSources( nDirection, szDSN, sizeof(szDSN) - 1, &nLength1, szDescription, sizeof(szDescription) - 1, &nLength2 );
        while ( SQL_SUCCEEDED( nReturn ) )
        {
            stringlistDataSources += OQToQString(szDSN);
            nReturn = ODBCEnvironment::doDataSources( SQL_FETCH_NEXT, szDSN, sizeof(szDSN) - 1, &nLength1, szDescription, sizeof(szDescription) - 1, &nLength2 );
        }
    }
    else
        nReturn = SQL_NO_DATA;

    if ( pnReturn )
        *pnReturn = nReturn;

    return stringlistDataSources;
}

void OQEnvironment::eventMessage( ODBCMessage Message )
{
    emit signalMessage( Message );
}

void OQEnvironment::eventDiagnostic()
{
    emit signalDiagnostic( ODBCDiagnostic( this ) );
}



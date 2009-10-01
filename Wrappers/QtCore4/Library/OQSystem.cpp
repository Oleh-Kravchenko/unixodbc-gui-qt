/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "OQSystem.h"
#include <odbcinst.h>

OQSystem::OQSystem()
    : OQHandle( Sys )
{
    setObjectName( "OQSystem" );
}

OQSystem::~OQSystem()
{
}

SQLRETURN OQSystem::setDriverAttribute( const QString &stringDriver, const QString &stringKey, const QString &stringValue )
{
    if ( stringValue.isNull() )
    {
        // \todo delete key/value
    }

    // update/add key/value...
    QString stringFile( "ODBCINST.INI" );

    if ( SQLWritePrivateProfileString( (LPTSTR)OQFromQString(stringDriver), (LPTSTR)OQFromQString(stringKey), (LPTSTR)OQFromQString(stringValue), (LPTSTR)OQFromQString(stringFile) ) )
        return SQL_SUCCESS;

    eventDiagnostic();

    return SQL_ERROR;
}

QMap<QString,QString> OQSystem::getDriverAttributes( const QString &stringDriver, SQLRETURN *pnReturn )
{
    QMap<QString,QString>   mapAttributes;
    TCHAR                   szResults[4000];
    TCHAR                   szValue[500];
    TCHAR *                 pszKey;

    QString                 stringFileName( "ODBCINST.INI" );
    QString                 stringDefault( "" );
    LPTSTR                  pszSection  = (LPTSTR)OQFromQString(stringDriver);
    LPTSTR                  pszFileName = (LPTSTR)OQFromQString(stringFileName);
    LPTSTR                  pszDefault  = (LPTSTR)OQFromQString(stringDefault);

    if ( SQLGetPrivateProfileString( pszSection, NULL, NULL, (LPTSTR)szResults, sizeof( szResults ) / sizeof( TCHAR ), pszFileName ) < 1 )
    {
        if ( pnReturn ) *pnReturn = SQL_ERROR;
        eventDiagnostic();
        return mapAttributes;
    }
    pszKey = szResults;
    while ( *pszKey )
    {
        if ( SQLGetPrivateProfileString( pszSection, (LPTSTR)pszKey, pszDefault, (LPTSTR)szValue, sizeof( szValue ) / sizeof( TCHAR ), pszFileName ) < 1 )
        {
            if ( pnReturn ) *pnReturn = SQL_ERROR;
            eventDiagnostic();
            return mapAttributes;
        }
        QString stringKey = OQToQString(pszKey);
        mapAttributes[ stringKey ] = OQToQString( szValue );
        pszKey += stringKey.length() + 1;
    }

    if ( pnReturn ) *pnReturn = SQL_SUCCESS;

    return mapAttributes;
}

QMap<QString,QString> OQSystem::getAttributes( SQLRETURN *pnReturn )
{
    vector<ODBCKeyValue>    vectorProperties;
    ODBCCHAR                szResults[4096];

    szResults[0] = '\0';

    /*
     * - This works fine for UNIX'ism.
     * - This does not work on MS'ism. I can SQLWritePrivateProfileString key/values to "ODBC" and get it back but
     *   this does not pickup the Trace, Polling, etc settings?
     */
    if ( SQLGetPrivateProfileString( (ODBCCPTR)TEXT("ODBC"), NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") ) > 0 )
    {
        ODBCCHAR    szValue[512];
        ODBCCHAR *  p = szResults;

        while ( *p )
        {
            if ( SQLGetPrivateProfileString( (ODBCCPTR)TEXT("ODBC"), (ODBCCPTR)p, (ODBCCPTR)TEXT(""), (ODBCCPTR)szValue, sizeof(szValue) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") ) > 0 )
                vectorProperties.push_back( ODBCKeyValue( p, szValue ) );
            p += ODBCStrLen( p ) + 1;
        }
    }

    if ( pnReturn )
        *pnReturn = SQL_SUCCESS;

    return vectorProperties;
}

/*! 
 *  \f$     doManageDataSources
 *  \brief  Invoke a GUI (an ODBC Administrator).
 *  
 *          On MS Windows or when working with a recent unixODBC - we can simply pass this
 *          request on via SQLManageDataSources().
 *  
 *          On OSX we exec a program since SQLManageDataSources() is not likely to be supported.
 *  
 *  \note   HWND should be a viable ODBCINSTWND when using unixODBC. The app can call SQLGetInfo()
 *          to determine if unixODBC is in use.
 *          
 */
#ifdef Q_WS_MACX
BOOL OQSystem::doManageDataSources( HWND )
{
    QProcess  * pprocess = new QProcess( this );

    pprocess->addArgument( "open" );
    pprocess->addArgument( "/Applications/Utilities/ODBC Administrator.app" ); // OSX Jaguar now has a standard ODBC Administrator :)
    if ( pprocess->start() ) 
    {
        return true;
    }
    
    delete pprocess;

    return false;
}
#else
BOOL OQSystem::doManageDataSources( HWND hWnd )
{
	return SQLManageDataSources( hWnd );
}
#endif



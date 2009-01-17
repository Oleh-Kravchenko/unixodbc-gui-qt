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
    : QObject(), ODBCSystem()
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

    if ( SQLWritePrivateProfileString( (ODBCCPTR)OQFromQString(stringDriver), (ODBCCPTR)OQFromQString(stringKey), (ODBCCPTR)OQFromQString(stringValue), (ODBCCPTR)OQFromQString(stringFile) ) )
        return SQL_SUCCESS;

    return SQL_ERROR;
}

QMap<QString,QString> OQSystem::getDriverAttributes( const QString &stringName, SQLRETURN *pnReturn )
{
    QMap<QString,QString> mapAttributes;
    SQLTCHAR    szResults[4000];
    SQLTCHAR    szValue[500];
    SQLTCHAR *  pszKey;

    if ( SQLGetPrivateProfileString( (ODBCCPTR)OQFromQString(stringName), NULL, NULL, (ODBCCPTR)szResults, sizeof( szResults ) - 1, (ODBCCPTR)TEXT("ODBCINST.INI") ) < 1 )
    {
        if ( pnReturn ) *pnReturn = SQL_ERROR;
        return mapAttributes;
    }
    pszKey = szResults;
    while ( *pszKey )
    {
        if ( SQLGetPrivateProfileString( (ODBCCPTR)OQFromQString(stringName), (ODBCCPTR)pszKey, (ODBCCPTR)TEXT(""), (ODBCCPTR)szValue, sizeof( szValue ) - 1, (ODBCCPTR)TEXT("ODBCINST.INI") ) < 1 )
        {
            if ( pnReturn ) *pnReturn = SQL_ERROR;
            return mapAttributes;
        }
        mapAttributes[ OQToQString(pszKey) ] = OQToQString( szValue );
        pszKey += ODBCStrLen( pszKey ) + 1;
    }
    if ( pnReturn ) *pnReturn = SQL_SUCCESS;
    return mapAttributes;
}

/*! 
 *  \f$     doManageDataSources
 *  \brief  Invoke a GUI (an ODBC Administrator).
 *  
 *          This provides an alternative to calling SQLManageDataSources by attempting to
 *          exec a program. This will work better than SQLManageDataSources in some cases such
 *          as with iODBC on OSX.
 *  
 *          For MS'ism this may still invoke SQLManageDataSources since that is known to always
 *          work.
 */
#ifdef WIN32
BOOL OQSystem::doManageDataSources( HWND hWnd )
{
/* PAH - SQLManageDataSources() is a much better solution on MS Windows than this...
    QProcess  * pprocess = new QProcess( this );

    pprocess->addArgument( "ODBCAD32.exe" );
    if ( pprocess->start() ) 
        return;

    delete pprocess;
    pprocess = new QProcess( this );

    pprocess->addArgument( "c:\\windows\\system\\ODBCAD32.exe" );
    if ( pprocess->start() ) 
        return;

    delete pprocess;
    pprocess = new QProcess( this );

    pprocess->addArgument( "c:\\windows\\system32\\ODBCAD32.exe" );
    if ( pprocess->start() ) 
        return;

    delete pprocess;
    pprocess = new QProcess( this );

    pprocess->addArgument( "c:\\winnt\\system32\\ODBCAD32.exe" );
    if ( pprocess->start() ) 
        return;

    delete pprocess;
*/
	return SQLManageDataSources( hWnd );
}
#else
#ifdef Q_WS_MACX
BOOL OQSystem::doManageDataSources( HWND )
{
    QProcess  * pprocess = new QProcess( this );

    pprocess->addArgument( "open" );
    pprocess->addArgument( "/Applications/Utilities/ODBC Administrator.app" ); // OSX Jaguar now has a standard ODBC Administrator
    if ( pprocess->start() ) 
    {
        return true;
    }
    
    delete pprocess;

    return false;
}
#else
BOOL OQSystem::doManageDataSources( HWND )
{
    /*
     * Method 1 
     *
     * Execute a seperate process.
     *
     */
    if ( QProcess::startDetached( "ODBCManageDataSourcesQ4" ) )
        return true;
    if ( QProcess::startDetached( "ODBCConfig" ) )
        return true;
    if ( QProcess::startDetached( "gODBCConfig" ) )
        return true;

    /*
     * Method 2
     *
     * Invoke using a Qt dialog.
     *
     * 1. Assumes we are using unixODBC.
     * 2. Assumes that unixODBC was built with GUI support.
     * 3. Assumes that there are no conflicts between the Qt lib used here
     *    and the one used to build unixODBC.
     */
/*
    ODBCINSTWND odbcinstwnd;
    
    strcpy( odbcinstwnd.szUI, "odbcinstQ4" );
    odbcinstwnd.hWnd = pwidget;

	return SQLManageDataSources( (HWND)(&odbcinstwnd) );
*/

	return false;
}
#endif
#endif

/*!
 * \brief   Intercept the Error event so we can emit signalInstallerError for each error
 *          we may find.
 * 
 * \author  pharvey (8/31/2008)
 */
void OQSystem::eventError()
{
    // max is supposed to be 8 but lets allow for up to 100
    for ( WORD nIndex = 1; nIndex < 100; nIndex++ )
    {
        ODBCSystemError SystemError = getError( nIndex );
        if ( !SQL_SUCCEEDED( SystemError.nRetCode ) )
            break;
        emit signalInstallerError( SystemError );
    }
}



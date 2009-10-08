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
    : OQHandle( TypeSys )
{
    setObjectName( "OQSystem" );
}

OQSystem::~OQSystem()
{
}

/*!
 * \brief   Get ODBC system-wide attributes. 
 *  
 *          These attributes are system-wide and include such things as connection pooling
 *          and DM tracing. 
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   pnReturn 
 * 
 * \return  OQAttributes 
 */
OQAttributes OQSystem::getAttributes( SQLRETURN *pnReturn )
{
    SQLRETURN       nReturn;
    OQAttributes    Attributes = getAttributes( "ODBCINST.INI", "ODBC", &nReturn );

    if ( pnReturn ) *pnReturn = nReturn;

    return Attributes;
}

/*!
 * \brief   Get driver attributes. 
 *  
 *          This gets the driver attributes from ODBCINST.INI. 
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   stringDriver 
 * \param   pnReturn 
 * 
 * \return  OQDriver 
 */
OQDriver OQSystem::getDriver( const QString &stringDriver, SQLRETURN *pnReturn )
{
    SQLRETURN   nReturn;
    OQDriver    Driver = getAttributes( "ODBCINST.INI", stringDriver, &nReturn );

    if ( pnReturn ) *pnReturn = nReturn;

    return Driver;
}

/*!
 * \brief   Get a list of registered drivers.  
 *  
 *          The list comes from doGetInstalledDrivers().
 *  
 * \author  pharvey (10/6/2009)
 * 
 * \param   pnReturn 
 * 
 * \return  QVector<QString> 
 */
QVector<QString> OQSystem::getDriverNames( SQLRETURN *pnReturn )
{
    QVector<QString> vectorDriverNames;

    BOOL b = doGetInstalledDrivers( &vectorDriverNames );

    if ( pnReturn )
        *pnReturn = (  b ? SQL_SUCCESS : SQL_ERROR );

    return vectorDriverNames;
}

/*!
 * \brief   Get driver information for all registered drivers.
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   pnReturn 
 * 
 * \return  QVector<OQDriver> 
 */
QVector<OQDriver> OQSystem::getDrivers( SQLRETURN *pnReturn )
{
    SQLRETURN           nReturn;
    QVector<OQDriver>   vectorDrivers;

    // get a list of driver names...
    QVector<QString> vectorDriverNames = getDriverNames( &nReturn );

    if ( !SQL_SUCCEEDED( nReturn ) )
    {
        if ( pnReturn ) *pnReturn = nReturn;
        return vectorDrivers;
    }

    // get & store details...
    for ( int n = 0; n < vectorDriverNames.size(); n++ )
    {
        OQDriver Driver = getDriver( vectorDriverNames[n], &nReturn );
        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            if ( pnReturn ) *pnReturn = nReturn;
            return vectorDrivers;
        }
        vectorDrivers.append( Driver );
    }

    return vectorDrivers;
}

/*!
 * \brief   Get data source information.
 *  
 *          Gets data source information using the given scope.
 *  
 * \author  pharvey (10/6/2009)
 * 
 * \param   stringDataSourceName 
 * \param   nScope 
 * \param   pnReturn 
 * 
 * \return  OQDataSourceName 
 */
OQDataSourceName OQSystem::getDataSource( const QString &stringDataSourceName, OQDataSourceName::Scopes nScope, SQLRETURN *pnReturn )
{
    OQDataSourceName::Scopes nScopeOrig = OQDataSourceName::ScopeBoth;

    doGetConfigMode( &nScopeOrig );
    doSetConfigMode( nScope );

    SQLRETURN           nReturn;
    OQDataSourceName    DataSourceName = getAttributes( "ODBC.INI", stringDataSourceName, &nReturn );

    if ( pnReturn ) *pnReturn = nReturn;

    SQLSetConfigMode( nScopeOrig );

    DataSourceName.nScope           = nScope;
    DataSourceName.stringFilename   = "ODBC.INI";

    return DataSourceName;
}

/*!
 * \brief   Get data source information. 
 *  
 *          Gets data source information using the given file name. 
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   stringDataSourceName 
 * \param   stringFilename 
 * \param   pnReturn 
 * 
 * \return  OQDataSourceName 
 */
OQDataSourceName OQSystem::getDataSource( const QString &stringDataSourceName, const QString &stringFilename, SQLRETURN *pnReturn )
{
    OQDataSourceName::Scopes nScope = OQDataSourceName::ScopeBoth;

    doGetConfigMode( &nScope );

    if ( stringFilename.upper() == "ODBC.INI" )
        return getDataSource( stringDataSourceName, nScope, pnReturn );

    SQLRETURN           nReturn;
    OQDataSourceName    DataSourceName = getAttributes( stringFilename, stringDataSourceName, &nReturn );

    if ( pnReturn ) *pnReturn = nReturn;

    DataSourceName.nScope           = nScope;
    DataSourceName.stringFilename   = stringFilename;

    return DataSourceName;
}

/*!
 * \brief   Get a list of data sources.
 *  
 *          Gets a list of data sources (DSN's) from system information using
 *          the given scope. This does NOT include file DSN's.
 *  
 * \author  pharvey (10/6/2009)
 * 
 * \param   nScope 
 * \param   pnReturn 
 * 
 * \return  QVector<QString> 
 */
QVector<QString> OQSystem::getDataSourceNames( OQDataSourceName::Scopes nScope, SQLRETURN *pnReturn )
{
    QVector<QString>            vectorDataSourceNames;
    OQDataSourceName::Scopes    nScopeOrig = OQDataSourceName::ScopeBoth;

    doGetConfigMode( &nScopeOrig );
    doSetConfigMode( nScope );

    BOOL b = doGetPrivateProfileString( QString::null, &vectorDataSourceNames, "ODBC.INI" );
    if ( pnReturn ) *pnReturn = ( b ? SQL_SUCCESS : SQL_ERROR );

    SQLSetConfigMode( nScopeOrig );

    DataSourceName.nScope           = nScope;
    DataSourceName.stringFilename   = "ODBC.INI";

    return DataSourceName;
}

/*!
 * \brief   Get information on all data sources (DSN's).
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   nScope 
 * \param   pnReturn 
 * 
 * \return  QVector<OQDataSourceName> 
 */
QVector<OQDataSourceName> OQSystem::getDataSources( OQDataSourceName::Scopes nScope, SQLRETURN *pnReturn )
{
    QVector<OQDataSourceName>   vectorDataSources;
    SQLRETURN                   nReturn;
    QVector<QString>            vectorDataSourceNames;
    SQLRETURN                   nReturn;
    SQLRETURN *                 pn = &nReturn;

    if ( pnReturn ) pn = pnReturn;

    // get a list data source names...
    vectorDataSourceNames = getDataSourceNames( nScope, pn );
    if ( !SQL_SUCCEEDED(*pn) )
        return vectorDataSources;

    // get data source objects..
    for ( int n = 0; n <  vectorDataSourceNames.size(); n++ )
    {
        OQDataSource DataSource = getDataSource( vectorDataSourceNames[n], nScope, pn ); 
        if ( !SQL_SUCCEEDED(*pn) )
            return vectorDataSources;

        vectorDataSources.append( DataSource );
    }

    return vectorDataSources;
}

/*!
 * \brief   Get the system error at the given index.
 *  
 *          The system error is usually an ODBC installer error.
 *  
 * \author  pharvey (10/6/2009)
 * 
 * \param   nIndex The spec says 1-8 is valid but more are often supported.
 * \param   pnRetCode 
 * 
 * \return  OQSystemError 
 */
OQSystemError OQSystem::getSystemError( WORD nIndex /* 1 - 8 */, RETCODE *pnRetCode = NULL )
{
    OQSystemError SystemError;

    RETCODE nRetCode = doInstallerError( nIndex, &(SystemError.nErrorCode), &(SystemError.stringErrorMsg) );

    if ( pnRetCode ) *pnRetCode = nRetCode;

    return SystemError;
}

/*!
 * \brief   Get all system erros currently available.
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \return  QVector<OQSystemError> 
 */
QVector<OQSystemError> OQSystem::getSystemErrors()
{
    QVector<OQSystemError>  vectorSystemErrors;
    RETCODE                 nRetCode = SQL_SUCCESS;

    for ( WORD n = 0; SQL_SUCCEEDED( nRetCode ); n++ )
    {
        OQSystemError SystemError = getSystemError( n, &nRetCode );
        if ( SQL_SUCCEEDED( nRetCode )  )
            vectorSystemErrors.append( SystemError );
    }

    return vectorSystemErrors;
}

/*! 
 *  \f$     doManageDataSources
 *  \brief  Wrapper for SQLManageDataSources. Invoke a GUI (an ODBC Administrator).
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

/*!
 * \brief   Gets all key/values for the given 'section'. 
 *  
 *          The 'section' is usually a driver or a dsn. 
 * 
 * \author  pharvey (10/6/2009)
 * 
 * \param   stringFilename 
 * \param   stringSection 
 * \param   pnReturn 
 * 
 * \return  OQAttributes 
 */
OQAttributes OQSystem::getAttributes( const QString &stringFilename, const QString &stringSection, SQLRETURN *pnReturn )
{
    OQAttributes        Attributes;
    QVector<QString>    vectorKeys;

    doGetPrivateProfileString( stringSection, &vectorKeys, stringFilename );

    for ( int n = 0; n < vectorKeys.size(); n++ )
    {
        QString stringValue;
        doGetPrivateProfileString( stringSection, vectorKeys[n], &stringValue, stringFilename );
        Attributes.mapAttributes.insert( vectorKeys[n], stringValue );
    }

    Attributes.stringName = stringSection;

    return Attributes;
}

/* 
BOOL OQSystem::doConfigDataSource( HWND hwndParent, enumConfigDataSourceRequest nRequest, const QString &stringDriver, const QMap<Qstring,QString> &mapAttributes )
{
    LPTSTR  pszDriver       = (LPTSTR)OQFromQString(stringDriver);
    LPTSTR  pszAttributes   = getAttributes( mapAttributes );

    BOOL b = SQLConfigDataSource( hwndParent, (WORD)nRequest, pszDriver, pszAttributes );

    free( pszAttributes );

    return b;
}
*/

/*
BOOL OQSystem::doConfigDriver( HWND hwndParent, enumConfigDriverRequest nRequest, const QString &stringDriver, const QString &stringArgs, QString *pstringMsg )
{
    BOOL    b;
    LPTSTR  pszDriver   = (LPTSTR)OQFromQString(stringDriver);
    LPTSTR  pszArgs     = (LPTSTR)OQFromQString(stringArgs);
    WORD    nMsgMax     = 512;
    TCHAR   szMsg[nMsgMax];
    WORD    nMsgMaxOut  = 0;

    b = SQLConfigDriver( hwndParent, (WORD)nRequest, pszDriver, pszArgs, szMsg, nMsgMax, &nMsgMaxOut );
    if ( nMsgMaxOut <= nMsgMax )
    {
        nMsgMax = (nMsgMaxOut + 2);
        {
            TCHAR szMsg[nMsgMax];

            b = SQLConfigDriver( hwndParent, (WORD)nRequest, pszDriver, pszArgs, szMsg, nMsgMax, &nMsgMaxOut );
            if ( b && pstringMsg )
                *pstringMsg = OQToQString( pszMsg );
        }
    }
    else if ( b && pstringMsg )
        *pstringMsg = OQToQString( pszMsg );

    return b;
}
*/

/*
BOOL OQSystem::doCreateDataSource( HWND hwnd, const QString &stringDS )
{
    return SQLCreateDataSource( hwnd, OQFromQString( stringDS ) ); 
}
*/

/*!
 * \brief   Wrapper for SQLGetConfigMode.
 * 
 * \author pharvey (10/6/2009)
 * 
 * \param pnConfigMode 
 * 
 * \return BOOL 
 */
BOOL OQSystem::doGetConfigMode( enumConfigMode *pnConfigMode )
{
    return SQLGetConfigMode( (UWORD)pnConfigMode );
}

/*!
 * \brief   Wrapper for SQLGetInstalledDrivers.
 * 
 * \author pharvey (10/6/2009)
 * 
 * \param pvectorDrivers 
 * 
 * \return BOOL 
 */
BOOL OQSystem::doGetInstalledDrivers( QVector<QString> *pvectorDrivers )
{
    BOOL    b;
    WORD    nBufMax = 1024;
    TCHAR   szBuf[nBufMax];
    WORD    nBufOut = 0;

    b = SQLGetInstalledDrivers( szBuf, nBufMax, &nBufOut );
    if ( nBufOut <= nBufMax )
    {
        nBufMax = (nBufOut + 2);
        {
            TCHAR szBuf[nBufMax];

            b = SQLGetInstalledDrivers( szBuf, nBufMax, &nBufOut );
            if ( b && pvectorDrivers )
                *pvectorDrivers = getVector( pszBuf );
        }
    }
    else if ( b && pvectorDrivers )
        *pvectorDrivers = getVector( pszBuf );

    return b;
}

/*!
 * \brief   Wrapper for SQLGetPrivateProfileString. 
 *  
 *          Get ODBC system information from INI files and/or registry. Use this when the
 *          result is expected to be a single string.
 * 
 * \author  pharvey (10/5/2009)  
 * 
 * \param   stringSection 
 * \param   stringEntry 
 * \param   stringDefault 
 * \param   pstring 
 * \param   stringFilename 
 * 
 * \return  BOOL 
 */
BOOL OQSystem::doGetPrivateProfileString( const QString &stringSection, const QString &stringEntry, const QString &stringDefault, QString *pstring, const QString &stringFilename )
{
    if ( !pstring )
    {
        // post an error
        return false;
    }

    pstring->clear();

    LPTSTR  pszSection = (LPTSTR)OQFromQString(stringSection);
    LPTSTR  pszEntry   = (LPTSTR)OQFromQString(stringEntry);
    LPTSTR  pszDefault = (LPTSTR)OQFromQString(stringDefault);
    LPTSTR  pszFilename= (LPTSTR)OQFromQString(stringFilename);

    int     nCharsMax = 1024;
    TCHAR   szChars[nCharsMax] = { '\0' };

    int nCharsRead = SQLGetPrivateProfileString( pszSection, pszEntry, pszDefault, szChars, nCharsMax, pszFilename );

    if ( nCharsRead < 1 )
        return true;

    if ( pstring )
        *pstring = OQToQString( szChars );

    return true;
}

/*!
 * \brief   Wrapper for SQLGetPrivateProfileString. 
 *  
 *          Get ODBC system information from INI files and/or registry. Use this when
 *          the result is expected to be a string list - when getting all sections or
 *          all keys for a specified section.
 * 
 * \author  pharvey (10/5/2009)
 * 
 * \param   stringSection 
 * \param   stringEntry 
 * \param   pvectorStrings 
 * \param   stringFilename 
 * 
 * \return  BOOL 
 */
BOOL OQSystem::doGetPrivateProfileString( const QString &stringSection, QVector<QString> *pvectorStrings, const QString &stringFilename )
{
    if ( !pvectorStrings )
    {
        // post an error
        return false;
    }

    pvectorStrings->clear();

    LPTSTR  pszSection      = (LPTSTR)OQFromQString(stringSection);
    LPTSTR  pszFilename     = (LPTSTR)OQFromQString(stringFilename);

    int     nCharsMax = 4096;
    TCHAR   szChars[nCharsMax] = { '\0' };

    int nCharsRead = SQLGetPrivateProfileString( pszSection, NULL, NULL, szChars, nCharsMax, pszFilename );

    if ( nCharsRead < 1 )
        return true;

    // decode result
    pvectorStrings->clear();
    for ( TCHAR *pszCursor = szChars; pszCursor[1] != '\0'; )
    {
        // grab the string
        pvectorStrings->append( OQToQString( pszCursor ) );
        // scan until next string
        while ( *pszCursor != '\0' )
            pszCursor++;
        pszCursor++;
    }

    return true;
}

/*!
 * \brief   Wrapper for SQLInstallerError.
 * 
 * \author pharvey (10/6/2009)
 * 
 * \param nError 
 * \param pnErrorCode 
 * \param pstringMsg 
 * 
 * \return RETCODE 
 */
RETCODE OQSystem::doInstallerError( WORD nError, DWORD *pnErrorCode, QString *pstringMsg )
{
    WORD    nErrorMsgMaxChars               = 512;
    WORD    nErrorMsgChars                  = 0;
    TCHAR   szErrorMsg[nErrorMsgMaxChars]   = { '\0' };
    RETCODE nRetCode;

    nRetCode = SQLInstallerError( nError, pnErrorCode, szErrorMsg, nErrorMsgMaxChars, &nErrorMsgChars );
    if ( nErrorMsgChars >= nErrorMsgMaxChars  )
    {
        nErrorMsgMaxChars = nErrorMsgChars + 1;
        {
            TCHAR szErrorMsg[nErrorMsgMaxChars]   = { '\0' };
            nRetCode = SQLInstallerError( nError, pnErrorCode, szErrorMsg, nErrorMsgMaxChars, &nErrorMsgChars );
        }
    }

    if ( SQL_SUCCEEDED(nRetCode) && pstringMsg )
        *pstringMsg = OQToQString( szErrorMsg );

    return nRetCode;
}

/*
RETCODE OQSystem::doPostInstallerError( DWORD nErrorCode, const QString &stringErrorMsg )
{
    return SQLPostInstallerError( nErrorCode, (LPTSTR)OQFromQString(stringErrorMsg); );
}
*/

/*!
 * \brief   Wrapper for SQLSetConfigMode.
 * 
 * \author pharvey (10/6/2009)
 * 
 * \param nConfigMode 
 * 
 * \return BOOL 
 */
BOOL OQSystem::doSetConfigMode( enumConfigMode nConfigMode )
{
    return SQLSetConfigMode( (UWORD)nConfigMode );
}



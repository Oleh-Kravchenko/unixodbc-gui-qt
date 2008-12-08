#include "ODBCSystem.h"

#include <odbcinst.h>

ODBCSystemError::ODBCSystemError()
{
    nRetCode    = SQL_ERROR;
    nErrorCode  = 0;
    *szErrorMsg = '\0';
}

ODBCKeyValue::ODBCKeyValue()
{
    *szKey      = '\0';
    *szValue    = '\0';
}

ODBCKeyValue::ODBCKeyValue( const ODBCKeyValue &KeyValue )
{
    *szKey      = '\0';
    *szValue    = '\0';

    ODBCStrNCpy( szKey, sizeof(szKey) / sizeof(ODBCCHAR), KeyValue.szKey, _TRUNCATE );
    ODBCStrNCpy( szValue, sizeof(szValue) / sizeof(ODBCCHAR), KeyValue.szValue, _TRUNCATE );
}

ODBCKeyValue::ODBCKeyValue( ODBCCHAR *pszKey, ODBCCHAR *pszValue )
{
    *szKey      = '\0';
    *szValue    = '\0';

    if ( pszKey )
        ODBCStrNCpy( szKey, sizeof(szKey) / sizeof(ODBCCHAR), pszKey, _TRUNCATE );

    if ( pszValue )
        ODBCStrNCpy( szValue, sizeof(szValue) / sizeof(ODBCCHAR), pszValue, _TRUNCATE );
}

ODBCDriver::ODBCDriver()
{
    *szName = '\0';
}

ODBCDataSourceName::ODBCDataSourceName()
{
    *szName = '\0';
    *szFile = '\0';
}

ODBCSystem::ODBCSystem()
{
}

ODBCSystem::~ODBCSystem()
{
}

ODBCDriver ODBCSystem::getDriver( const ODBCCHAR *pszDriver, SQLRETURN *pnReturn )
{
    ODBCDriver Driver;
    ODBCCHAR   szResults[4096];

    if ( pnReturn )
        *pnReturn = SQL_ERROR;

    if ( !pszDriver )
        return Driver;

    szResults[0] = '\0';
    ODBCStrNCpy( Driver.szName, sizeof(Driver.szName) / sizeof(ODBCCHAR), pszDriver, _TRUNCATE );

    // load properties...
    if ( SQLGetPrivateProfileString( (ODBCCPTR)pszDriver, NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") ) > 0 )
    {
        ODBCCHAR    szValue[512];
        ODBCCHAR *  p = szResults;

        while ( *p )
        {
            *szValue = '\0';
            SQLGetPrivateProfileString( (ODBCCPTR)pszDriver, (ODBCCPTR)p, (ODBCCPTR)TEXT(""), (ODBCCPTR)szValue, sizeof(szValue) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") );
            Driver.vectorProperties.push_back( ODBCKeyValue( p, szValue ) );
            p += ODBCStrLen( p ) + 1;
        }
    }

    if ( pnReturn )
        *pnReturn = SQL_SUCCESS;

    return Driver;
}

vector<ODBCDriver> ODBCSystem::getDrivers( SQLRETURN *pnReturn )
{
    vector<ODBCDriver>  vectorDrivers;
    ODBCCHAR            szResults[4096];
    SQLRETURN           nReturn = SQL_SUCCESS;

    szResults[0] = '\0';

    /*
     * METHOD 1 
     *  
     * - requesting "ODBC Drivers" section works ok on MS Windows 
     * - this section may not exist for other ODBC implementations 
     */
#ifdef WIN32
    {
        if ( SQLGetPrivateProfileString( (ODBCCPTR)TEXT("ODBC Drivers"), NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") ) > 0 )
        {
            ODBCCHAR *p = szResults;
    
            while ( *p )
            {
                ODBCDriver Driver = getDriver( p, &nReturn );
                if ( !SQL_SUCCEEDED( nReturn ) )
                    break;
                vectorDrivers.push_back( Driver );
                p += ODBCStrLen( p ) + 1;
            }
        } 
    }
#endif

    /*
     * METHOD 2
     *  
     * - this works well on UNIX'ism
     * - passing NULL as first arg to SQLGetPrivateProfileString() should get us a list 
     *   of all section names but this is not always the case - we get nothing on MS Windows
     */
#ifndef WIN32
    {
        if ( SQLGetPrivateProfileString( NULL, NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBCINST.INI") ) > 0 )
        {
            ODBCCHAR *p = szResults;
    
            while ( *p )
            {
                ODBCDriver Driver = getDriver( p, &nReturn );
                if ( !SQL_SUCCEEDED( nReturn ) )
                    break;
                vectorDrivers.push_back( Driver );
                p += ODBCStrLen( p ) + 1;
            }
        } 
    }
#endif

    /*
     * METHOD 3
     */
    {
        // SQLDrivers
    }

    // fini
    if ( pnReturn )
        *pnReturn = nReturn;

    return vectorDrivers;
}

ODBCDataSourceName ODBCSystem::getDataSourceName( const ODBCCHAR *pszDataSourceName, ODBCDataSourceName::Types nType, SQLRETURN *pnReturn )
{
    ODBCDataSourceName  DataSourceName;
    UWORD               nScopeOriginal;
    ODBCCHAR            szResults[4096];
    
    if ( pnReturn )
        *pnReturn = SQL_ERROR;

    if ( !pszDataSourceName )
    {
        // \todo handle this as a request for DEFAULT 
        return (const ODBCDataSourceName &)DataSourceName;
    }

    szResults[0] = '\0';
    ODBCStrNCpy( DataSourceName.szName, sizeof(DataSourceName.szName) / sizeof(ODBCCHAR), pszDataSourceName, _TRUNCATE );
    
    SQLGetConfigMode( &nScopeOriginal );

    // set scope...
    switch ( nType )
    {
        case ODBCDataSourceName::User:
            SQLSetConfigMode( ODBC_USER_DSN );
            break;
        case ODBCDataSourceName::System:
            SQLSetConfigMode( ODBC_SYSTEM_DSN );
            break;
        case ODBCDataSourceName::Both:
            SQLSetConfigMode( ODBC_BOTH_DSN );
            break;
        case ODBCDataSourceName::File:
            break;
        default:
            return DataSourceName;
    }

    // load properties...
    if ( SQLGetPrivateProfileString( (ODBCCPTR)pszDataSourceName, NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBC.INI") ) >= 1 )
    {
        ODBCCHAR    szValue[512];
        ODBCCHAR *  p = szResults;

        while ( *p )
        {
            *szValue = '\0';
            SQLGetPrivateProfileString( (ODBCCPTR)pszDataSourceName, (ODBCCPTR)p, (ODBCCPTR)TEXT(""), (ODBCCPTR)szValue, sizeof(szValue) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBC.INI") );
            DataSourceName.vectorProperties.push_back( ODBCKeyValue( p, szValue ) );
            p += ODBCStrLen( p ) + 1;
        }
    }

    if ( pnReturn )
        *pnReturn = SQL_SUCCESS;

    // reset scope...
    SQLSetConfigMode( nScopeOriginal );

    return DataSourceName;
}

vector<ODBCDataSourceName> ODBCSystem::getDataSourceNames( ODBCDataSourceName::Types nType, SQLRETURN *pnReturn )
{
    vector<ODBCDataSourceName>  vectorDataSourceNames;
    UWORD                       nScopeOriginal;
    ODBCCHAR                    szResults[4096];
    SQLRETURN                   nReturn = SQL_SUCCESS;

    szResults[0] = '\0';

    SQLGetConfigMode( &nScopeOriginal );

    // set scope...
    switch ( nType )
    {
        case ODBCDataSourceName::User:
            SQLSetConfigMode( ODBC_USER_DSN );
            break;
        case ODBCDataSourceName::System:
            SQLSetConfigMode( ODBC_SYSTEM_DSN );
            break;
        case ODBCDataSourceName::Both:
            SQLSetConfigMode( ODBC_BOTH_DSN );
            break;
        case ODBCDataSourceName::File:
            break;
        default:
            return vectorDataSourceNames;
    }
    /*
     * METHOD 1 
     *  
     * - requesting "ODBC Data Sources" section works ok on MS Windows 
     * - this section may not exist for other ODBC implementations 
     */
#ifdef WIN32
    {
        if ( SQLGetPrivateProfileString( (ODBCCPTR)TEXT("ODBC Data Sources"), NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBC.INI") ) >= 1 )
        {
            ODBCCHAR *  p = szResults;
    
            while ( *p )
            {
                ODBCDataSourceName DataSourceName = getDataSourceName( p, nType, &nReturn );
                if ( !SQL_SUCCEEDED( nReturn ) )
                    break;
                vectorDataSourceNames.push_back( DataSourceName );
                p += ODBCStrLen( p ) + 1;
            }
        }
    }
#endif

    /*
     * METHOD 2
     *  
     * - this works well on UNIX'ism
     * - passing NULL as first arg to SQLGetPrivateProfileString() should get us a list 
     *   of all section names but this is not the case - we get nothing on MS Windows as of
     *   this writing
     */
#ifndef WIN32
    {
        if ( SQLGetPrivateProfileString( NULL, NULL, NULL, (ODBCCPTR)szResults, sizeof(szResults) / sizeof(ODBCCHAR), (ODBCCPTR)TEXT("ODBC.INI") ) >= 1 )
        {
            ODBCCHAR *  p = szResults;
    
            while ( *p )
            {
                ODBCDataSourceName DataSourceName = getDataSourceName( p, nType, &nReturn );
                if ( !SQL_SUCCEEDED( nReturn ) )
                    break;
                vectorDataSourceNames.push_back( DataSourceName );
                p += ODBCStrLen( p ) + 1;
            }
        } 
    }
#endif

    /*
     * METHOD 3 
     */
    {
        // SQLDataSources
    }

    if ( pnReturn )
        *pnReturn = nReturn;

    // reset scope...
    SQLSetConfigMode( nScopeOriginal );

    return vectorDataSourceNames;
}

/*!
 * \brief   Lookup the given key and return a reference to the corresponding Value.
 * 
 *          This is a simple helper method.
 * 
 * \param   vectorKeyValues 
 * \param   pszKey 
 * 
 * \return  const ODBCCHAR* 
 *
 * \author  pharvey (8/31/2008)
 */
const ODBCCHAR *ODBCSystem::getValue( const vector<ODBCKeyValue> &vectorKeyValues, const ODBCCHAR *pszKey )
{
    for ( unsigned int n = 0; n < vectorKeyValues.size(); n++ )
    {
        if ( ODBCStrCaseCmp( vectorKeyValues.at( n ).szKey, pszKey ) == 0 )
            return vectorKeyValues.at( n ).szValue;
    }

    return NULL;
}

/*!
 * \brief   Use this to get the Key/Value pairs representing the ODBC System properties.
 * 
 *          These properties exist at the ODBC System level/scope and include such things as;
 * 
 *          \li trace
 *          \li pooling
 * 
 *          Only properties which are well known will exist without existing in the ODBC System information
 *          (ie because they are not set).
 * 
 * \param   pnReturn 
 * 
 * \return  vector<ODBCKeyValue> 
 *
 * \author  pharvey (8/31/2008)
 */
vector<ODBCKeyValue> ODBCSystem::getProperties( SQLRETURN *pnReturn )
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

ODBCSystemError ODBCSystem::getError( WORD nIndex )
{
    ODBCSystemError SystemError;

    SystemError.nRetCode = SQLInstallerError( nIndex, &SystemError.nErrorCode, SystemError.szErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL );  

    return SystemError;
}

vector<ODBCSystemError> ODBCSystem::getErrors()
{
    vector<ODBCSystemError> vectorErrors;

    for ( WORD nIndex = 1; nIndex <= 8; nIndex++ )
    {
        ODBCSystemError SystemError = getError( nIndex );
        if ( !SQL_SUCCEEDED( SystemError.nRetCode ) )
            break;
        vectorErrors.push_back( SystemError );
    }

    return vectorErrors;
}

/*! 
 * \brief   Invoke user interface to manage data sources.
 * 
 *          This maps to SQLManageDataSources. On Microsoft Windows platforms
 *          this will invoke a small GUI application which allows one to
 *          manage data sources (and more). On other platforms this may invoke
 *          a user interface based upon a plugin system or may simply return an
 *          error.
 *
 *          The caller must pass a viable HWND or a NULL. On MS Windows this is
 *          straight forward since HWND is a MS'ism. For unixODBC based platforms
 *          (most Linux platforms for example) a viable HWND can be initialized as
 *          follows;
 * \code 
ODBCINSTWND odbcinstwnd;

odbcinstwnd.hWnd = 0;
strcpy( odbcinstwnd.szUI, "odbcinstQ4" );

if ( SQLManageDataSources( (HWND)&(odbcinstwnd) ) == FALSE )
    return 1;

return 0;
   \endcode
 *
 *          This explicitly requests that the odbcinstQ4 plugin be used to provide
 *          the user interface. At this time there are two plugins for this... the
 *          other is odbcinstQ (Qt3) based user interface. See unixODBC doc on
 *          ODBCINSTWND for details.
 *
 * \param   hWnd
 * 
 * \return  BOOL
 */
BOOL ODBCSystem::doManageDataSources( HWND hWnd )
{
    return SQLManageDataSources( hWnd );
}

void ODBCSystem::eventError()
{
    // derived classes can catch error events using this
}



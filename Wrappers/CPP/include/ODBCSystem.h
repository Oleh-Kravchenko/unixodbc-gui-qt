/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2008
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCSYSTEM_H
#define ODBCSYSTEM_H

#include "ODBC.h"

#include <vector>

using namespace std;

/*!
 * \class   ODBCSystemError 
 * \brief   An ODBC system/installer error. 
 *  
 *          This is error information collected by calling \sa getError()
 *          or \sa getErrors().
 *  
 * \sa      getError 
 *          getErrors
 *  
 * \author  pharvey (8/15/2008)
 */
class ODBCSystemError
{
public:
    ODBCSystemError();

    RETCODE nRetCode;                               /*!< RetCode for call to get error: SQL_SUCCESS, SQL_SUCCESS_WITH_INFO, SQL_NO_DATA, or SQL_ERROR   */
    DWORD   nErrorCode;                             /*!< Installer error code.                                                                          */
    TCHAR   szErrorMsg[SQL_MAX_MESSAGE_LENGTH + 1]; /*!< Installer error text.                                                                          */
};

/*!
 * \class   ODBCKeyValue
 * \brief   This class binds a key and a value together. 
 *  
 *          Driver and Data Source Name properties are stored in Key/Value pairs.
 *  
 * \author  pharvey (8/15/2008)
 */
class ODBCKeyValue
{
public:
    ODBCKeyValue();
    ODBCKeyValue( const ODBCKeyValue &KeyValue );
    ODBCKeyValue( ODBCCHAR *pszKey, ODBCCHAR *pszValue );

    ODBCCHAR szKey[100];        /*!< a key - restrictions apply - see ODBC spec.*/
    ODBCCHAR szValue[1024];     /*!< a value                                    */
};

/*!
 * \class   ODBCDriver 
 * \brief   This class binds a Driver name with its properties. 
 *  
 *          Everthing one may need to know about an ODBC driver. 
 * 
 * \sa      ODBCDataSourceName 
 *          ODBCKeyValue 
 *  
 * \author  pharvey (8/15/2008)
 */
class ODBCDriver
{
public:
    ODBCDriver();

    ODBCCHAR                szName[100];        /*!< driver name                */
    vector<ODBCKeyValue>    vectorProperties;   /*!< config details             */
};

/*!
 * \class   ODBCDataSourceName
 * \brief   This class binds a Data Source Name with its properties. 
 *  
 *          Everthing one may need to know about an ODBC Data Source Name.
 *  
 * \sa      ODBCDriver 
 *          ODBCKeyValue 
 *  
 * \author  pharvey (8/15/2008)
 */
class ODBCDataSourceName
{
public:
    enum Types
    {
        User,       /*!< User scope. DSN's which are for use for a specific User account.   */
        System,     /*!< System scope. DSN's which apply to the entire system/machine.      */
        Both,       /*!< User and System scope combined.                                    */
        File        /*!< DSN is stored in its own file.                                     */
    };

    ODBCDataSourceName();
    ODBCDataSourceName( const ODBCDataSourceName &DataSourceName )
    {
        *szName = '\0';
        *szFile = '\0';
    
        if ( DataSourceName.szName )
            ODBCStrCpy( szName, DataSourceName.szName );
        if ( DataSourceName.szFile )
            ODBCStrCpy( szFile, DataSourceName.szFile );
    
        vectorProperties = DataSourceName.vectorProperties;
    }

    ODBCCHAR                szName[100];            /*!< DSN name                           */
    ODBCCHAR                szFile[FILENAME_MAX];   /*!< path + szName + ext of file DSN    */
    vector<ODBCKeyValue>    vectorProperties;       /*!< config details                     */

    ODBCDataSourceName &operator=(const ODBCDataSourceName &DataSourceName )
    {
        *szName = '\0';
        *szFile = '\0';
        if ( DataSourceName.szName )
            ODBCStrCpy( szName, DataSourceName.szName );
        if ( DataSourceName.szFile )
            ODBCStrCpy( szFile, DataSourceName.szFile );

        vectorProperties = DataSourceName.vectorProperties;

        return *this;
    }

};

/*! 
 * \class   ODBCSystem 
 * \brief   Interface to ODBC system information.
 *
 *          This class provides access to ODBC system information which does not require
 *          an ODBCEnvironment. Most of this functionality can be categorized as 'installer'
 *          functionality.
 * 
 * \sa      ODBCDataSourceName
 *          ODBCDriver
 * 
 * \author  pharvey (8/15/2008)
 */
class ODBCSystem
{
public:
    explicit ODBCSystem();
    virtual ~ODBCSystem();

    virtual ODBCDriver                   getDriver( const ODBCCHAR *pszDriver, SQLRETURN *pnReturn = NULL );
    virtual vector<ODBCDriver>           getDrivers( SQLRETURN *pnReturn = NULL);
    virtual ODBCDataSourceName           getDataSourceName( const ODBCCHAR *pszDataSourceName, ODBCDataSourceName::Types nType = ODBCDataSourceName::Both, SQLRETURN *pnReturn = NULL );
    virtual vector<ODBCDataSourceName>   getDataSourceNames( ODBCDataSourceName::Types nType = ODBCDataSourceName::Both, SQLRETURN *pnReturn = NULL );
    virtual const ODBCCHAR *             getValue( const vector<ODBCKeyValue> &vectorKeyValues, const ODBCCHAR *pszKey );

    virtual vector<ODBCKeyValue>         getProperties( SQLRETURN *pnReturn = NULL);
    virtual ODBCSystemError              getError( WORD nIndex /* 1 - 8 */ );
    virtual vector<ODBCSystemError>      getErrors();
    
    virtual BOOL doManageDataSources( HWND hWnd );

protected:
    virtual void eventError();
};

#endif




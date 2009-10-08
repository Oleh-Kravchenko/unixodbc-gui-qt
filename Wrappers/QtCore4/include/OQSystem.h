/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#pragma once

#include "OQHandle.h"

/*!
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
class OQSystemError
{
public:
    OQSystemError()
    {
        nErrorCode  = 0;
    }

    DWORD   nErrorCode;     /*!< Installer error code.                                                                          */
    QString stringErrorMsg; /*!< Installer error text.                                                                          */
};

/*!
 * \brief   A set of attributes from system information. 
 *  
 *          Think of this as an INI section.
 * 
 * \author  pharvey (10/2/2009)
 */
class OQAttributes
{
public:
    QString                 stringName;     // section
    QMap<QString,QString>   mapAttributes;  // key/value pairs
};

/*! 
 * \brief   Driver system information. 
 *  
 * \author  pharvey (10/2/2009)
 */
typedef OQAttributes OQDriver;

/*!
 * \brief   Data Source Name (DSN) system information.
 * 
 * \author  pharvey (10/2/2009)
 */
class OQDataSourceName : public OQAttributes
{
public:
    enum Scopes
    {
        ScopeUser       = ODBC_USER_DSN,       /*!< User scope. DSN's which are for use for a specific User account.   */
        ScopeSystem     = ODBC_SYSTEM_DSN,     /*!< System scope. DSN's which apply to the entire system/machine.      */
        ScopeBoth       = ODBC_BOTH_DSN        /*!< User and System scope combined.                                    */
    };

    OQDataSourceName()
    {
        nScope = ScopeBoth;
    }

    Scopes  nScope;
    QString stringFilename; // filename or default (default="ODBC.INI"/null/empty)
};

/*! 
 * \class   OQSystem
 * \brief   An ODBC system.
 *
 *          This class wraps some ODBC setup & installer functionality.
 *
 *          \li uses Qt data types where possible
 *          \li will emit signal when new messages become available
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 * 
 */
class OQSystem : public OQHandle
{
    Q_OBJECT
public:
    explicit OQSystem();
    virtual ~OQSystem();

    enum enumConfigDataSourceRequest
    {
        AddDsn              = ODBC_ADD_DSN,
        ConfigDsn           = ODBC_CONFIG_DSN,
        RemoveDsn           = ODBC_REMOVE_DSN,
        AddSysDsn           = ODBC_ADD_SYS_DSN,
        ConfigSysDsn        = ODBC_CONFIG_SYS_DSN,
        RemoveSysDsn        = ODBC_REMOVE_SYS_DSN,
        RemoveDefaultDsn    = ODBC_REMOVE_DEFAULT_DSN
    };

    enum enumConfigDriverRequest
    {
        ConfigDriver    = ODBC_CONFIG_DRIVER,
        InstallDriver   = ODBC_INSTALL_DRIVER,
        RemoveDriver    = ODBC_REMOVE_DRIVER
    };

    enum enumConfigMode
    {
        UserDsn     = ODBC_USER_DSN,
        SystemDsn   = ODBC_SYSTEM_DSN,
        BothDsn     = ODBC_BOTH_DSN
    };

    enum enumInstallDriverExRequest
    {
        InstallInquiry  = ODBC_INSTALL_INQUIRY,
        InstallComplete = ODBC_INSTALL_COMPLETE
    };

    // getters
    virtual OQAttributes               getAttributes( SQLRETURN *pnReturn = NULL);
    virtual OQDriver                   getDriver( const QString &stringDriver, SQLRETURN *pnReturn = NULL );
    virtual QVector<QString>           getDriverNames( SQLRETURN *pnReturn = NULL );
    virtual QVector<OQDriver>          getDrivers( SQLRETURN *pnReturn = NULL);
    virtual OQDataSourceName           getDataSource( const QString &stringDataSourceName, OQDataSourceName::Scopes nScope = OQDataSourceName::ScopeBoth, SQLRETURN *pnReturn = NULL );
    virtual OQDataSourceName           getDataSource( const QString &stringDataSourceName, const QString &stringLocation, SQLRETURN *pnReturn = NULL );
    virtual QVector<QString>           getDataSourceNames( OQDataSourceName::Scopes nScope = OQDataSourceName::ScopeBoth, SQLRETURN *pnReturn = NULL );
    virtual QVector<OQDataSourceName>  getDataSources( OQDataSourceName::Scopes nScope = OQDataSourceName::ScopeBoth, SQLRETURN *pnReturn = NULL );
    virtual OQSystemError              getSystemError( WORD nIndex /* 1 - 8 */, RETCODE *pnRetCode = NULL );
    virtual QVector<OQSystemError>     getSystemErrors();

    // doers
    virtual BOOL    doManageDataSources( HWND hWnd );    

signals:
    virtual void signalSystemError( OQSystemError SystemError );

protected:
    virtual void eventSystemError();

    virtual OQAttributes getAttributes( const QString &stringFilename, const QString &stringSection, SQLRETURN *pnReturn );

//    virtual BOOL    doConfigDataSource( HWND hwndParent, enumConfigDataSourceRequest nRequest, const QString &stringDriver, const QMap<Qstring,QString> &mapAttributes );
//    virtual BOOL    doConfigDriver( HWND hwndParent, enumConfigDriverRequest nRequest, const QString &stringDriver, const QString &stringArgs, QString *pstringMsg ); 
//    virtual BOOL    doCreateDataSource( HWND hwnd, const QString &stringDS );
    virtual BOOL    doGetConfigMode( enumConfigMode *pnConfigMode );
    virtual BOOL    doGetInstalledDrivers( QVector<QString> *pvectorDrivers );
    virtual BOOL    doGetPrivateProfileString( const QString &stringSection, const QString &stringEntry, const QString &stringDefault, QString *pstring, const QString &stringFilename );
    virtual BOOL    doGetPrivateProfileString( const QString &stringSection, QVector<QString> pvectorStrings, const QString &stringFilename );
//    virtual BOOL    doInstallDriverEx( const OQDriver &Driver, const QString &stringPathIn, QString *pstringPathOut, enumInstallDriverExRequest nRequest, LPDWORD pnUsageCount );
    virtual RETCODE doInstallerError( WORD nError, DWORD *pnErrorCode, QString *pstringMsg );
//    virtual RETCODE doPostInstallerError( DWORD nErrorCode, const QString &stringErrorMsg );
//    virtual BOOL    doReadFileDSN( const QString &stringFilename, const QString &stringAppName, const QString &stringKeyName, QString *pstring );
//    virtual BOOL    doRemoveDriver( const QString &stringDriver, bool bRemoveDSN, LPDWORD pnUsageCount );
//    virtual BOOL    doRemoveDSNFromIni( const QString &stringDSN );
    virtual BOOL    doSetConfigMode( enumConfigMode nConfigMode );
//    virtual BOOL    doWriteFileDSN( const QString &stringFileName, const QString &stringAppName, const QString &stringKeyName, const QString stringValue );
//    virtual BOOL    doWritePrivateProfileString( const QString &stringSection, const QString &stringEntry, const QString &stringValue, const QString &stringFilename );

};


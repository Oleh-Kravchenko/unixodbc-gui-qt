/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2008
 * \license Copyright unixODBC-GUI-Qt Project 2009-2010, LGPL
 */
#include <odbcinstext.h>

#include <QApplication>

#include "CDriverConnectPrompt.h"

/*! 
 * \brief   Manage Data Sources
 * 
 *          SQLManageDataSources done using Qt4. Here is where we enter into Qt4 'world'.
 * 
 * \param   hWnd
 * 
 * \return  BOOL
 */
static BOOL QT4DriverConnectPrompt( HWND hWnd, SQLCHAR *pszDataSourceName, SQLSMALLINT nMaxChars )
{
    /*
     * Here, we handle case where a non QT app has called us. Our approach here is a bit different 
     * than what we used for Qt3 because we were getting segfault upon app exit. Here; we instantiate
     * with a 'new' and NOT 'delete' it. Its a work around.
     */ 
    if ( !qApp )
    {
        int argc = 1;
        char *argv[] = { "odbcinstQ4", NULL };

        QApplication *pApplication = new QApplication( argc, argv );
        QCoreApplication::setOrganizationName("unixODBC");
        QCoreApplication::setOrganizationDomain("unixodbc.org");
        QCoreApplication::setApplicationName("ODBC Driver Connect Prompt");
    }

    // missing parent widget? Use desktop...
    QWidget *pWidget = (QWidget*)hWnd;
    if ( !pWidget )
        pWidget = qApp->desktop();

    // sanity check...
    if ( !pszDataSourceName  )
    {
        QMessageBox::critical( pWidget, "Select Data Source...", "Invalid buffer for data source name!" );
        return false;
    }

    if ( nMaxChars <= 1 )
    {
        QMessageBox::critical( pWidget, "Select Data Source...", "Invalid max char value for data source name!" );
        return false;
    }

    // show dialog...
    CDriverConnectPrompt o( pszDataSourceName, nMaxChars, pWidget );
    if ( o.exec() == QDialog::Accepted )
        return true;

    return false;
}

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief   Plugin in entry point.
 *
 *          This entry point is called to implement the SQLDriverConnectPrompt call.
 * 
 *          This plugin does it using Qt4.
 * 
 *          The typical way to get to here is to call into odbcinst via SQLDriverConnectPrompt. 
 * 
 * \return  BOOL
 * \retval  TRUE    pszDataSourceName contains a viable data source name.
 * \retval  FALSE   User cancelled or something went wrong.
 * 
 * \sa      CDriverConnectPrompt
 *          unixODBC::DriverManager::SQLDriverConnect
 *          unixODBC::DriverManager::SQLDriverConnectPrompt
 */
BOOL ODBCDriverConnectPrompt( HWND hWnd, SQLCHAR *pszDataSourceName, SQLSMALLINT nMaxChars )
{
    return QT4DriverConnectPrompt( hWnd, pszDataSourceName, nMaxChars );
}

#ifdef __cplusplus
};
#endif


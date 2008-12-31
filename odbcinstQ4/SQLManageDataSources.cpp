/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#include <odbcinstext.h>
#include <autotest.h>

#include <QApplication>

#include "CODBCConfig.h"
#include "CDSNWizard.h"

/*! 
 * \brief   Manage Data Sources
 * 
 *          SQLManageDataSources done using Qt4. Here is where we enter into Qt4 'world'.
 * 
 * \param   hWnd
 * 
 * \return  BOOL
 */
static BOOL QT4ManageDataSources( HWND hWnd )
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
        QCoreApplication::setApplicationName("ODBC Administrator");
    }

    // missing parent widget? Use desktop...
    QWidget *pWidget = (QWidget*)hWnd;
    if ( !pWidget )
        pWidget = qApp->desktop();

    // show dialog...
	CODBCConfig odbcconfig( pWidget );
	if ( odbcconfig.exec() == QDialog::Accepted )
        return true;

    return false;
}

/*! 
 * \brief   Create Data Source
 * 
 *          SQLCreateDataSource done using Qt4. Here is where we enter into Qt4 'world'.
 * 
 * \param   hWnd
 * 
 * \return  BOOL
 */
static BOOL QT4CreateDataSource( HWND hWnd, LPCSTR pszDataSourceName )
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
        QCoreApplication::setApplicationName("ODBC Administrator");
    }

    // missing parent widget? Use desktop...
    QWidget *pWidget = (QWidget*)hWnd;
    if ( !pWidget )
        pWidget = qApp->desktop();

    // show dialog...
    CDSNWizardData  WizardData( pszDataSourceName );
    CDSNWizard      odbccreate( &WizardData, pWidget );
	int nReturn = odbccreate.exec();

    //  sucks to have to do this after wizard is on its way out - no fail and Back :(
    if ( nReturn == QDialog::Accepted )
        return CODBCInst::saveDataSourceName( pWidget, WizardData.hFirstProperty, WizardData.nType );

    return false;
}

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief   Plugin in entry point.
 *
 *          This entry point is called to implement the SQLManageDataSources call.
 * 
 *          This plugin does it using Qt4.
 * 
 *          The typical way to get to here is to call into odbcinst via SQLManageDataSource. 
 */
BOOL ODBCManageDataSources( HWND hWnd )
{
    return QT4ManageDataSources( hWnd );
}

/*!
 * \brief   Plugin in entry point.
 *
 *          This entry point is called to implement the SQLCreateDataSource call.
 * 
 *          This plugin does it using Qt4.
 * 
 *          The typical way to get to here is to call into odbcinst via SQLCreateDataSource. 
 */
BOOL ODBCCreateDataSource( HWND hWnd, LPCSTR lpszDS )
{
    return QT4CreateDataSource( hWnd, lpszDS );
}

/*!
 * \brief   Plugin in entry point.
 *
 *          This entry point is called to implement the szLogPrintf call used by auto tests managed/run
 *          by ODBCTestQ4.
 * 
 *          This plugin does it using Qt4.
 * 
 *          The typical way to get to here is to call into odbcinst via szLogPrintf. 
 */
BOOL EXTFUNCDECL FAR ODBCLogPrintf( lpSERVERINFO pServerInfo )
{
    // ensure text is terminated...
    pServerInfo -> szBuff[ pServerInfo -> cBuff ] = '\0';

    // to GUI...
    if ( pServerInfo -> fScreen && pServerInfo->hwnd )
    {
        // the app (ie ODBCTestQ4) should have provided a generic window handle...
        ODBCINSTWND *hWnd = (ODBCINSTWND*)pServerInfo->hwnd;

        if ( hWnd )
            ((QTextEdit*)hWnd)->append( pServerInfo -> szBuff );
    }

    // to file...
    if ( pServerInfo -> fLog )
    {
        FILE *fp = fopen( pServerInfo -> szLogFile, "a+" );
        if ( fp )
        {
            fputs( pServerInfo -> szBuff, fp );
            fputs( "\n", fp );
            fclose( fp );
        }
    }

    // reset...
    pServerInfo -> cBuff = 0;

    return true;
}

/*!
 * \brief   Plugin in entry point.
 *
 *          This entry point is called to implement the szMessageBox call used by auto tests managed/run
 *          by ODBCTestQ4.
 * 
 *          This plugin does it using Qt4.
 * 
 *          The typical way to get to here is to call into odbcinst via szMessageBox. 
 */
int EXTFUNCDECL FAR ODBCMessageBox( HWND hwnd, UINT nStyle, LPTSTR szTitle, LPTSTR szFormat, ... )
{
    // ok - you can call here with a null hwnd - but that is reason to question your code...
    if ( !hwnd )
        return 0;

    // the app (ie ODBCTestQ4) should have provided a generic window handle...
    // ODBCINSTWND *hWnd = (ODBCINSTWND*)hwnd;

    // format the message...
    va_list ap;
    char szFormatted[ 1024 ];

    va_start(ap, szFormat);
    vsprintf (szFormatted, szFormat, ap);
    va_end(ap);

    // activate buttons...
    int button0, button1, button2 = 0;

    button0 = QMessageBox::NoButton;
    button1 = QMessageBox::NoButton;
    button2 = QMessageBox::NoButton;

    switch ( nStyle & (MB_OK | MB_ABORTRETRYIGNORE | MB_OKCANCEL | MB_RETRYCANCEL | MB_YESNO | MB_YESNOCANCEL) )
    {
      case MB_ABORTRETRYIGNORE:
        button0 = QMessageBox::Abort;
        button1 = QMessageBox::Retry;
        button2 = QMessageBox::Ignore;
        break;
      case MB_OKCANCEL:
        button0 = QMessageBox::Ok;
        button1 = QMessageBox::Cancel;
        break;
      case MB_RETRYCANCEL:
        button0 = QMessageBox::Retry;
        button1 = QMessageBox::Cancel;
        break;
      case MB_YESNO:
        button0 = QMessageBox::Yes;
        button1 = QMessageBox::No;
        break;
      case MB_YESNOCANCEL:
        button0 = QMessageBox::Yes;
        button1 = QMessageBox::No;
        button2 = QMessageBox::Cancel;
        break;
      default:
        button0 = QMessageBox::Ok;
        break;
    }

    // set default button...
    switch ( nStyle & (MB_DEFBUTTON1 | MB_DEFBUTTON2 | MB_DEFBUTTON3 ) )
    {
      case MB_DEFBUTTON1:
      default:
        button0 |= QMessageBox::Default;
        break;
      case MB_DEFBUTTON2:
        button1 |= QMessageBox::Default;
        break;
      case MB_DEFBUTTON3:
        button2 |= QMessageBox::Default;
        break;
    }

    // icon...
    QMessageBox::Icon icon = QMessageBox::NoIcon;
    switch ( nStyle & (MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP ) )
    {
      case MB_ICONINFORMATION :
        icon = QMessageBox::Information;
        break;
      case MB_ICONQUESTION:
        icon = QMessageBox::Warning;
        break;
      case MB_ICONSTOP:
        icon = QMessageBox::Critical;
        break;
      default:
        icon = QMessageBox::NoIcon;
        break;
    }

    QMessageBox MessageBox( szTitle, szFormatted, icon, button0, button1, button2 );

    return MessageBox.exec();
}

#ifdef __cplusplus
};
#endif


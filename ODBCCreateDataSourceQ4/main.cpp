/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#include <odbcinst.h>
#include <odbcinstext.h>

#include <QApplication>
#include <QMessageBox>

/*! 
 * \brief   Invokes a UI to walk caller through creating a new Data Source Name.
 * 
 *          This wraps SQLCreateDataSource to get a simple executable. We are a
 *          Qt4 based app so we explicitly request the Qt4 based UI ("odbcinstQ4"). 
 *
 *          This app can be complimented with other apps which use a different
 *          toolkit (ie GTK). Presumably those other apps will also use a file name
 *          for the executable which follows a similar convention as this..
 *
 *          \li ODBCCreateDataSource<Toolkit>
 *
 *          We can then designate a default, to assist desktop environment developers, 
 *          using a symlink in the file system.
 *
 * \todo    Accept a DSN on the command-line.
 *
 * \param   argc
 * \param   argv
 * 
 * \return  int
 * \retval  0   Success
 * \retval  1   Error
 */
int main( int argc, char **argv )
{
    // init a Qt application...
    QApplication oApplication( argc, argv );
    QCoreApplication::setOrganizationName("unixODBC-GUI-Qt");
    QCoreApplication::setOrganizationDomain("unixodbc-gui-qt.sourceforge.net");
    QCoreApplication::setApplicationName("ODBC Create Data Source");

    // specify Qt4 UI plugin explicitly...
    ODBCINSTWND odbcinstwnd;
    strcpy( odbcinstwnd.szUI, "odbcinstQ4" );
    odbcinstwnd.hWnd = qApp->desktop();

    // call odbcinst library (which will map to odbcinstQ4 UI plugin)...
    if ( SQLCreateDataSource( (HWND)(&odbcinstwnd), NULL ) == TRUE )
        return 0;

    // oops - report any errors we can dig up...
    for ( WORD nError = 1; nError < 10; nError++ )
    {
        DWORD   nErrorCode;
        char    szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
        RETCODE nRetCode = SQLInstallerError( nError, &nErrorCode, szErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL );
        if ( !SQL_SUCCEEDED( nRetCode ) )
        {
            QMessageBox::critical( 0, QObject::tr( "ODBC Create Data Source" ),  QObject::tr( "failed: no more errors to report" ) );
            break;
        }
        QMessageBox::critical( 0, QObject::tr( "ODBC Create Data Source" ),  szErrorMsg );
    }

    // exit with error
    return 1;
}


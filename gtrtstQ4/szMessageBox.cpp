/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2009
 * \license Copyright unixODBC-GUI-Qt Project 2009-2010, LGPL
 */
#include <autotest.h>

#include <QtGui>

/*!
 * \brief   szMessageBox.
 *
 *          This is a Qt specific implementation of szMessageBox. This call
 *          is declared in unixODBC::autotest.h.
 * 
 *          AutoTest libraries link to this when they want to be run from
 *          ODBCTestQ4.
 */
int EXTFUNCDECL FAR szMessageBox( HWND hwnd, UINT nStyle, LPTSTR szTitle, LPTSTR szFormat, ... )
{
    // ok - you can call here with a null hwnd - but that is reason to question your code...
    if ( !hwnd )
        return 0;

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


#include "tools.h"

// storage for our global...
OdbcTools *gOdbcTools;

OdbcTools::OdbcTools( OdbcTest *pOdbcTest )
{
    this->pOdbcTest = pOdbcTest;

    pSettings = new QSettings( QDir::homePath() + "Gator.ini", QSettings::IniFormat );
}

OdbcTools::~OdbcTools()
{
    delete pSettings;
}

void OdbcTools::post_to_odbctest( lpSERVERINFO lps )
{
    lps -> szBuff[ lps -> cBuff ] = '\0';

    if ( lps -> fScreen )
    {
        gOdbcTools->pOdbcTest-> out_win -> insertLineLimited( lps -> szBuff );
    }
    if ( lps -> fLog )
    {
        FILE *fp = fopen( lps -> szLogFile, "a+" );
        if ( fp )
        {
            fputs( lps -> szBuff, fp );
            fputs( "\n", fp );
            fclose( fp );
        }
    }

    lps -> cBuff = 0;
}

void OdbcTools::print_to_odbctest( lpSERVERINFO lps, char *str, int log )
{
    gOdbcTools->pOdbcTest-> out_win -> insertLineLimited( str );

    if ( log && lps -> fLog )
    {
        FILE *fp = fopen( lps -> szLogFile, "a+" );
        if ( fp )
        {
            fputs( str, fp );
            fputs( "\n", fp );
            fclose( fp );
        }
    }
}

int OdbcTools::show_message_box( int style, const char *title, const char *msg )
{
    int button0, button1, button2;

    button0 = QMessageBox::NoButton;
    button1 = QMessageBox::NoButton;
    button2 = QMessageBox::NoButton;

    switch ( style & (MB_OK | MB_ABORTRETRYIGNORE | MB_OKCANCEL | MB_RETRYCANCEL | MB_YESNO | MB_YESNOCANCEL) )
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

    switch ( style & (MB_DEFBUTTON1 | MB_DEFBUTTON2 | MB_DEFBUTTON3 ) )
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

    QMessageBox::Icon icon = QMessageBox::NoIcon ;
    switch ( style & (MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP ) )
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

    QMessageBox mb( title,
                    msg,
                    icon,
                    button0,
                    button1,
                    button2 );

    return mb.exec();
}

void OdbcTools::fill_dsn_list( QComboBox *box )
{
    SQLHANDLE henv;
    SQLRETURN ret;
    SQLCHAR dsn_txt[ 128 ];

    box -> clear();

    /*
     * allocate a handle if required
     */

    ret = SQLAllocEnv( &henv );

    if ( !SQL_SUCCEEDED( ret ))
    {
        pOdbcTest -> out_win -> insertLineLimited( "SQLAllocHandle fails allocating a environment handle" );
        return;
    }

    ret = SQLDataSources( henv, 
                          SQL_FETCH_FIRST,
                          dsn_txt,
                          sizeof( dsn_txt ),
                          NULL,
                          NULL,
                          0,
                          NULL );

    while ( SQL_SUCCEEDED( ret ))
    {
        box -> addItem( (char*)dsn_txt );
        ret = SQLDataSources( henv, 
                              SQL_FETCH_NEXT,
                              dsn_txt,
                              sizeof( dsn_txt ),
                              NULL,
                              NULL,
                              0,
                              NULL );
    }

    /*
     * remove the temp henv
     */

    SQLFreeEnv( henv );
}

void OdbcTools::set_dsn_list( QComboBox *box, const QString &str )
{
    int index;
    QString qstr;

    for ( index = 0; index < box->count(); index ++ )
    {
        qstr = box->itemText( index );
        if ( qstr == str )
        {
            box->setCurrentIndex( index );
            break;
        }
    }
}


//
// callback function
//

extern "C" 
{

static int callback_function( lpSERVERINFO lps, BOOL fForce, BOOL fMsgBox, UINT style, LPTSTR szTitle, const char *msg )
{
    if ( fMsgBox )
    {
        return gOdbcTools->show_message_box( style, szTitle, msg );
    }
    else
    {
//        int line_out = 0;
        /*
         * copy from msg to szBuff, looking for \n
         */

        while ( *msg )
        {
            if ( *msg == '\n' )
            {
                gOdbcTools->post_to_odbctest( lps );
            }
            else if ( isprint( *msg ))
            {
                if ( lps -> cBuff < sizeof( lps -> szBuff ) - 1 )
                {
                    lps -> szBuff[ lps -> cBuff ] = *msg;
                    lps -> cBuff ++;
                }
            }
            msg ++;
        }

        if ( fForce && lps -> cBuff > 0 )
        {
            gOdbcTools->post_to_odbctest( lps );
        }
    }

    return 0;
}

}





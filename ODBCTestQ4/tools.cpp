/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 **********************************************************************
 *
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 * $Id: tools.cpp,v 1.8 2007/02/12 11:49:37 lurcher Exp $
 *
 * $Log: tools.cpp,v $
 * Revision 1.8  2007/02/12 11:49:37  lurcher
 * Add QT4 support to existing GUI parts
 *
 * Revision 1.7  2005/04/05 09:11:32  lurcher
 * The config string being passed into ConfigDsn was wrong, removed semicolon, and added terminating double null
 *
 * Revision 1.6  2003/12/01 16:37:17  lurcher
 *
 * Fix a bug in SQLWritePrivateProfileString
 *
 * Revision 1.5  2003/11/13 15:12:54  lurcher
 *
 * small change to ODBCConfig to have the password field in the driver
 * properties hide the password
 * Make both # and ; comments in ini files
 *
 * Revision 1.4  2003/09/29 08:56:10  lurcher
 *
 * Fix warning dialogs
 * Check for headers before using them
 *
 * Revision 1.3  2002/01/21 18:00:51  lurcher
 *
 * Assorted fixed and changes, mainly UNICODE/bug fixes
 *
 * Revision 1.2  2001/12/04 16:46:19  lurcher
 *
 * Allow the Unix Domain Socket to be set from the ini file (DSN)
 * Make the DataManager browser work with drivers that don't support
 * SQLRowCount
 * Make the directory selection from odbctest work simplier
 *
 * Revision 1.1.1.1  2001/10/17 16:40:31  lurcher
 *
 * First upload to SourceForge
 *
 * Revision 1.11  2001/10/01 17:24:53  nick
 *
 * Assorted fixes
 *
 * Revision 1.10  2001/05/31 16:05:55  nick
 *
 * Fix problems with postgres closing local sockets
 * Make odbctest build with QT 3 (it doesn't work due to what I think are bugs
 * in QT 3)
 * Fix a couple of problems in the cursor lib
 *
 * Revision 1.9  2001/05/09 11:56:47  nick
 *
 * Add support for libtool 1.4
 *
 * Revision 1.8  2001/04/17 16:29:39  nick
 *
 * More checks and autotest fixes
 *
 * Revision 1.7  2001/04/17 12:57:11  nick
 *
 * Extra for AutoTest
 *
 * Revision 1.6  2001/04/16 22:35:10  nick
 *
 * More tweeks to the AutoTest code
 *
 * Revision 1.5  2001/04/16 15:41:24  nick
 *
 * Fix some problems calling non existing error funcs
 *
 * Revision 1.4  2001/04/14 19:00:34  nick
 *
 * Add support for ODBC Test handles, and catch a few problems with
 * empty Gator.ini
 *
 * Revision 1.3  2001/04/14 10:42:03  nick
 *
 * Extra work on the autotest feature of odbctest
 *
 * Revision 1.2  2001/04/12 17:43:36  nick
 *
 * Change logging and added autotest to odbctest
 *
 * Revision 1.1.1.1  2000/09/04 16:42:53  nick
 * Imported Sources
 *
 * Revision 1.1  2000/05/04 17:04:48  ngorham
 *
 * Initial commit
 *
 *
 **********************************************************************/

#include "tools.h"

//
// time func
// 

const char *get_time_str( void )
{
    static char str[ 128 ];
    time_t tim;
    struct tm *tm;

    tim = time( NULL );

    tm = localtime( &tim ); 

    sprintf( str, "%02d:%02d:%02d", tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    return str;
}

//
// callback function
//

static OdbcTest *static_odbctest;

static void post_to_odbctest( lpSERVERINFO lps )
{
    lps -> szBuff[ lps -> cBuff ] = '\0';

    if ( lps -> fScreen )
    {
        static_odbctest -> out_win -> insertLineLimited( lps -> szBuff );
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

static void print_to_odbctest( lpSERVERINFO lps, char *str, int log )
{
    static_odbctest -> out_win -> insertLineLimited( str );
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

static int show_message_box( int style, const char *title, const char *msg )
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

extern "C" {
static int callback_function( lpSERVERINFO lps, BOOL fForce,
        BOOL fMsgBox, UINT style, LPTSTR szTitle, const char *msg )
{
    if ( fMsgBox )
    {
        return show_message_box( style, szTitle, msg );
    }
    else
    {
//        int line_out = 0;
        /*
         * copy from msg to szBuff, looking for \n
         */

        while( *msg )
        {
            if ( *msg == '\n' )
            {
                post_to_odbctest( lps );
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
            post_to_odbctest( lps );
        }
    }

    return 0;
}
}

//
// Put information back into ini file
//

void replace_ini_list( OdbcTest *parent )
{
	HINI hIni;
//	char szPropertyValue[INI_MAX_PROPERTY_VALUE+1];
    char szINI[ODBC_FILENAME_MAX+1];

    sprintf( szINI, "%s/%s", SYSTEM_FILE_PATH, "Gator.ini" ); 
	if ( iniOpen( &hIni, szINI, "#;", '[', ']', '=', TRUE ) != INI_ERROR )
	{
        QListIterator<section*> i( ini_list );

        while ( i.hasNext() )
        {
            section *s = i.next();
            if ( !s )
                break;
            iniObjectSeekSure( hIni, (char*)s -> get_section());
            iniObjectDelete( hIni );

            iniObjectSeekSure( hIni, (char*)s -> get_section());

            for ( prop *prop = s->first(); prop != 0; prop = s -> next())
            {
                iniPropertyInsert( hIni, (char*)prop -> name(), (char*)prop -> value());
            }

            iniCommit( hIni );
        }
	}
    else
    {
        char msg[ 256 ];

        sprintf( msg, "Unable to open INI file (%s)", szINI );
        QMessageBox::critical( parent, "OdbcTest", msg );
    }

    ini_list.clear();
}

void remove_section( OdbcTest *parent, section *section )
{
	HINI hIni;
//	char szPropertyValue[INI_MAX_PROPERTY_VALUE+1];
    char szINI[ODBC_FILENAME_MAX+1];

    sprintf( szINI, "%s/%s", SYSTEM_FILE_PATH, "Gator.ini" ); 
	if ( iniOpen( &hIni, szINI, "#;", '[', ']', '=', TRUE ) != INI_ERROR )
	{
        iniObjectSeekSure( hIni, (char*)section -> get_section());
        iniObjectDelete( hIni );
        iniCommit( hIni );
	}
    else
    {
        char msg[ 256 ];

        sprintf( msg, "Unable to open INI file (%s)", szINI );
        QMessageBox::critical( parent, "OdbcTest", msg );
    }


}

//
// extract the information from the ini file
//

void init_ini_list( OdbcTest *parent )
{
	HINI hIni;
	char szObject[INI_MAX_OBJECT_NAME+1];
	char szPropertyName[INI_MAX_PROPERTY_NAME+1];
	char szPropertyValue[INI_MAX_PROPERTY_VALUE+1];
    char szINI[ODBC_FILENAME_MAX+1];

    ini_list.clear();

    sprintf( szINI, "%s/%s", SYSTEM_FILE_PATH, "Gator.ini" ); 
	if ( iniOpen( &hIni, szINI, "#;", '[', ']', '=', TRUE ) != INI_ERROR )
	{
		iniObjectFirst( hIni );
		while ( iniObjectEOL( hIni ) == FALSE )
		{
			szObject[0]         = '\0';
			szPropertyName[0] 	= '\0';
			szPropertyValue[0] 	= '\0';
			iniObject( hIni, szObject );
			iniPropertyFirst( hIni );

            section *s = new section( szObject );

            ini_list.append( s );

            while ( iniPropertyEOL( hIni ) == FALSE )
            {
                iniProperty( hIni, szPropertyName );
                iniValue( hIni, szPropertyValue );

                prop *p = new prop( szPropertyName, szPropertyValue );

                s -> append( p );

                iniPropertyNext( hIni );
            }
			iniObjectNext( hIni );
		}
	}
	else
	{
        FILE *fp;

        //
        // empty list
        //
        sprintf( szINI, "%s/%s", SYSTEM_FILE_PATH, "Gator.ini" ); 
        fp = fopen( szINI, "w+" );
        if ( fp )
        {
            //
            // Create the sections
            //
            fprintf( fp, "[SQL_DRIVERS]\n\n[GROUPS]\n\n" );
            fclose( fp );
        }
        else
        {
            char msg[ 256 ];

            sprintf( msg, "Unable to open INI file (%s)", szINI );
            QMessageBox::critical( parent, "OdbcTest", msg );
        }
	}

    //
    // if empty create base groups
    //

    if ( !ini.contains( "SQL_DRIVERS" ) )
    {
        QMap<QString,QString> a;
        ini["SQL_DRIVERS"] = a;
    }

    if ( !ini.contains( "GROUPS" ) )
    {
        QMap<QString,QString> a;
        ini["GROUPS"] = a;
    }

    if ( !ini.contains( "Auto Tests" ) )
    {
        QMap<QString,QString> a;
        ini["Auto Tests"] = a;
    }

}

void fill_dsn_list( OdbcTest *parent, QComboBox *box )
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
        parent -> out_win -> insertLineLimited( "SQLAllocHandle fails allocating a environment handle" );
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
		box -> insertItem( QString( dsn_txt ) );
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

void set_dsn_list( QComboBox *box, const char *str )
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



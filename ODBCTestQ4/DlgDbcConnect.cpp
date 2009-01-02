/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 **********************************************************************
 *
 * 2009-01-02   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "DlgDbcConnect.h"
#include "OdbcTest.h"

DlgDbcConnect::DlgDbcConnect( OdbcTest *pOdbcTest, QString stringTitle )
: QDialog( pOdbcTest )
{
    setWindowTitle( stringTitle );

    this->pOdbcTest = pOdbcTest;

    //
    QDialogButtonBox *pDialogButtonBox = new QDialogButtonBox( this );
    pDialogButtonBox->setStandardButtons( QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help );

    // connection handles...
    pcomboboxHandles = new QComboBox( this );
    pOdbcTest->fill_handle_list( SQL_HANDLE_DBC, pcomboboxHandles );

    // servers...
    pcomboboxServers = new QComboBox( this );
    pcomboboxServers->setEditable( true );
    pcomboboxServers->insertItem( 0, "<null ptr>" );
    pcomboboxServers->insertItem( 1, "<empty string>" );
    pcomboboxServerLengths = new QComboBox( this );
    pcomboboxServerLengths->setEditable( true );
    pcomboboxServerLengths->insertItem( 0, "SQL_NTS=-3" );
    pcomboboxServerLengths->insertItem( 1, "0" );

    {
        // get last environment handle...
        SQLHANDLE hEnvironment = SQL_NULL_HANDLE;
        {
            QListIterator<OdbcHandle*> i( pOdbcTest->listHandle );
    
            while ( i.hasNext() )
            {
                OdbcHandle *pOdbcHandle = i.next();
                if ( pOdbcHandle && pOdbcHandle->getType() == SQL_HANDLE_ENV )
                {
                    hEnvironment = pOdbcHandle->getHandle();
                }
            }
        }
    
        // use last environment handle to get list of servers (Data Source Names)...    
        if ( hEnvironment )
        {
            SQLRETURN   nReturn;
            SQLCHAR     szDataSourceName[ 128 ];
            int         nIndex = 2;
    
            nReturn = SQLDataSources( hEnvironment, SQL_FETCH_FIRST, szDataSourceName, sizeof( szDataSourceName ), NULL, NULL, 0, NULL );
            while ( SQL_SUCCEEDED( nReturn ) )
            {
                pcomboboxServers->insertItem( nIndex ++, ( char * )szDataSourceName );
                nReturn = SQLDataSources( hEnvironment, SQL_FETCH_NEXT, szDataSourceName, sizeof( szDataSourceName ), NULL, NULL, 0, NULL );
            }
        }
    }

    // users...
    pcomboboxUsers = new QComboBox( this );
    pcomboboxUsers->setEditable( true );
    pcomboboxUsers->insertItem( 0, "<null ptr>" );
    pcomboboxUsers->insertItem( 1, "<empty string>" );
    pcomboboxUserLengths = new QComboBox( this );
    pcomboboxUserLengths->setEditable( true );
    pcomboboxUserLengths->insertItem( 0, "SQL_NTS=-3" );
    pcomboboxUserLengths->insertItem( 1, "0" );

    // authorizations...
    pcomboboxAuthentications = new QComboBox( this );
    pcomboboxAuthentications->setEditable( true );
    pcomboboxAuthentications->insertItem( 0, "<null ptr>" );
    pcomboboxAuthentications->insertItem( 1, "<empty string>" );
    pcomboboxAuthenticationLengths = new QComboBox( this );
    pcomboboxAuthenticationLengths->setEditable( true );
    pcomboboxAuthenticationLengths->insertItem( 0, "SQL_NTS=-3" );
    pcomboboxAuthenticationLengths->insertItem( 1, "0" );

    // layout...
    QVBoxLayout *pLayoutTop = new QVBoxLayout( this );

    QGridLayout *pLayout = new QGridLayout();
    pLayoutTop->addLayout( pLayout );
    pLayoutTop->addWidget( pDialogButtonBox );

    pLayout->addWidget( new QLabel( "Handle:", this ), 0, 0 );
    pLayout->addWidget( pcomboboxHandles, 0, 1 );

    pLayout->addWidget( new QLabel( "Server:", this ), 1, 0 );
    pLayout->addWidget( pcomboboxServers, 1, 1 );

    pLayout->addWidget( new QLabel( "String Length:", this ), 1, 2 );
    pLayout->addWidget( pcomboboxServerLengths, 1, 3 );

    pLayout->addWidget( new QLabel( "User:", this ), 2, 0 );
    pLayout->addWidget( pcomboboxUsers, 2, 1 );

    pLayout->addWidget( new QLabel( "String Length:", this ), 2, 2 );
    pLayout->addWidget( pcomboboxUserLengths, 2, 3 );

    pLayout->addWidget( new QLabel( "Authentication:", this ), 3, 0 );
    pLayout->addWidget( pcomboboxAuthentications, 3, 1 );

    pLayout->addWidget( new QLabel( "String Length:", this ), 3, 2 );
    pLayout->addWidget( pcomboboxAuthenticationLengths, 3, 3 );

    // connect signals...
    connect( pDialogButtonBox, SIGNAL(accepted()), this, SLOT(slotOk()) );
    connect( pDialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()) );
    connect( pDialogButtonBox, SIGNAL(helpRequested()), this, SLOT(slotHelp()) );
}

DlgDbcConnect::~DlgDbcConnect()
{
}

void DlgDbcConnect::slotOk()
{
    OdbcHandle *pOdbcHandle                 = pOdbcTest->extract_handle_list( SQL_HANDLE_DBC, pcomboboxHandles );
    SQLHANDLE   hConnection                 = SQL_NULL_HANDLE;
    QString     stringServer                = pcomboboxServers->currentText();
    QString     stringUser                  = pcomboboxUsers->currentText();
    QString     stringAuthentication        = pcomboboxAuthentications->currentText();
    QString     stringServerLength          = pcomboboxServerLengths->currentText();
    QString     stringUserLength            = pcomboboxUserLengths->currentText();
    QString     stringAuthenticationLength  = pcomboboxAuthenticationLengths->currentText();

    if ( pOdbcHandle )
        hConnection = pOdbcHandle->getHandle();

    pOdbcTest->out_win->append( "SQLConnect():" );
    pOdbcTest->out_win->append( "  In:" );

    // connection handle...
    if ( hConnection )
        pOdbcTest->out_win->append( QString( tr("    Connection Handle: %1") ).arg( (ulong)hConnection ) );
    else
        pOdbcTest->out_win->append( tr("    Connection Handle: SQL_NULL_HDBC") );

    // server string...
    if ( stringServer == "<null ptr>" )
    {
        stringServer = QString();
        pOdbcTest->out_win->append( tr("    Server: <null ptr>" ) );
    }
    else if ( stringServer == "<empty string>" )
    {
        stringServer = "";
        pOdbcTest->out_win->append( tr("    Server: <empty string>" ) );
    }
    else
        pOdbcTest->out_win->append( tr("    Server: ") + stringServer );

    // server string length...
    if ( stringServerLength.left( 7 ) == "SQL_NTS" )
    {
        stringServerLength = QString::number( SQL_NTS );
        pOdbcTest->out_win->append( tr("    Server Len: SQL_NTS=-3" ) );
    }
    else
        pOdbcTest->out_win->append( QString( tr("    Server Len: %1") ).arg( stringServerLength.toInt() ) );

    // user string...
    if ( stringUser == "<null ptr>" )
    {
        stringUser = QString();
        pOdbcTest->out_win->append( tr("    User: <null ptr>") );
    }
    else if ( stringUser == "<empty string>" )
    {
        stringUser = "";
        pOdbcTest->out_win->append( tr("    User: <empty string>") );
    }
    else
        pOdbcTest->out_win->append( QString( tr("    User: ") + stringUser ) );

    // user string length...
    if ( stringUserLength.left( 7 ) == "SQL_NTS" )
    {
        stringUserLength = QString::number( SQL_NTS );
        pOdbcTest->out_win->append( tr("    User Len: SQL_NTS=-3") );
    }
    else
        pOdbcTest->out_win->append( QString( tr("    User Len: %1") ).arg( stringUserLength.toInt() ) );

    // authorization string...
    if ( stringAuthentication == "<null ptr>" )
    {
        stringAuthentication = QString();
        pOdbcTest->out_win->append( tr("    Auth: <null ptr>") );
    }
    else if ( stringAuthentication == "<empty string>" )
    {
        stringAuthentication = "";
        pOdbcTest->out_win->append( tr("    Auth: <empty string>") );
    }
    else
        pOdbcTest->out_win->append( QString( tr("    Auth: ") + stringAuthentication ) );

    // authorization string length...
    if ( stringAuthenticationLength.left( 7 ) == "SQL_NTS" )
    {
        stringAuthenticationLength = QString::number( SQL_NTS );
        pOdbcTest->out_win->append( tr("    Auth Len: SQL_NTS=-3" ) );
    }
    else
        pOdbcTest->out_win->append( QString( tr("    Auth Len: %1") ).arg( stringAuthenticationLength.toInt() ) );

/* printf( "[PAH][%s][%d][%s] [%s][%d][%s][%d][%s][%d]\n", __FILE__, __LINE__, __FUNCTION__,
                                    (SQLCHAR*)stringServer.toAscii().data(), stringServerLength.toInt(),
                                    (SQLCHAR*)stringUser.toAscii().data(), stringUserLength.toInt(), 
                                    (SQLCHAR*)stringAuthentication.toAscii().data(), stringAuthenticationLength.toInt() ); */
    // do it...
    SQLRETURN nReturn = SQLConnect( hConnection, 
                                    (SQLCHAR*)stringServer.toAscii().data(), stringServerLength.toInt(),
                                    (SQLCHAR*)stringUser.toAscii().data(), stringUserLength.toInt(), 
                                    (SQLCHAR*)stringAuthentication.toAscii().data(), stringAuthenticationLength.toInt() );

    // return value...
    pOdbcTest->out_win->append( "  Return:" );
    pOdbcTest->out_win->append( QString( tr("    %1=%2") ).arg( pOdbcTest->return_as_text( nReturn ) ).arg( nReturn ) );
    pOdbcTest->out_win->append( "" );

    accept();
}

void DlgDbcConnect::slotHelp()
{
}

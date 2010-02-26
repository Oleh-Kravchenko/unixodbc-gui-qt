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
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "DlgEnvFreeEnv.h"
#include "OdbcTest.h"

void DlgEnvFreeEnv::Ok()
{
    OdbcHandle *env = pOdbcTest->extract_handle_list( SQL_HANDLE_ENV, handles );
	SQLHANDLE in_handle = SQL_NULL_HANDLE;
    
	if ( env )
		in_handle = env->getHandle();

	pOdbcTest->out_win->append( "SQLFreeEnv():" );
	pOdbcTest->out_win->append( "  In:" );

	if ( in_handle )
		txt.sprintf( "    henv: %p", in_handle );
	else
		txt.sprintf( "    henv: SQL_NULL_HENV" );
	pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLFreeEnv( in_handle );

	pOdbcTest->out_win->append( "  Return:" );
	txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
	pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ) && in_handle )
    {
		pOdbcTest->listHandle.removeAll( env );
        delete env;
    }

	pOdbcTest->out_win->append( "" );
}

DlgEnvFreeEnv::DlgEnvFreeEnv( OdbcTest *pOdbcTest, QString name )
        : QDialog( pOdbcTest )
{
	setWindowTitle( name );

	this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 90,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 170,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 250,10, 70,25 );

	handles = new QComboBox( this );
	handles->setGeometry( 120, 50, 200, 20 );
	pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, handles );

	l_handles = new QLabel( "henv:", this );
	l_handles->setGeometry( 10, 50, 100, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

DlgEnvFreeEnv::~DlgEnvFreeEnv()
{
	delete ok;
	delete cancel;
	delete help;
	delete handles;
	delete l_handles;
}



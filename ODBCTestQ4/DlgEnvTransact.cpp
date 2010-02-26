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

#include "DlgEnvTransact.h"
#include "OdbcTest.h"

void DlgEnvTransact::Ok()
{
    OdbcHandle *ehand = pOdbcTest->extract_handle_list( SQL_HANDLE_ENV, ehandles );
    OdbcHandle *chand = pOdbcTest->extract_handle_list( SQL_HANDLE_DBC, chandles );
	SQLHANDLE ein_handle = SQL_NULL_HANDLE;
	SQLHANDLE cin_handle = SQL_NULL_HANDLE;
    SQLSMALLINT completion;

	if ( ehand  )
		ein_handle = ehand->getHandle();
	if ( chand  )
		cin_handle = chand->getHandle();

	pOdbcTest->out_win->append( "SQLTransact():" );
	pOdbcTest->out_win->append( "  In:" );

	if ( ein_handle )
		txt.sprintf( "    henv: %p", ein_handle );
	else
		txt.sprintf( "    henv: SQL_NULL_HENV" );
	pOdbcTest->out_win->append( txt );

	if ( cin_handle )
		txt.sprintf( "    hdbc: %p", cin_handle );
	else
		txt.sprintf( "    hdbc: SQL_NULL_HDBC" );
	pOdbcTest->out_win->append( txt );

    completion = pEnvCompletionTypes[ completion_type->currentIndex() ].value;

    SQLRETURN ret = SQLTransact( ein_handle, cin_handle, completion );

	pOdbcTest->out_win->append( "  Return:" );
	txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
	pOdbcTest->out_win->append( txt );

	pOdbcTest->out_win->append( "" );
}

DlgEnvTransact::DlgEnvTransact( OdbcTest *pOdbcTest, QString name )
        : QDialog( pOdbcTest )
{
	setWindowTitle( name );
    setModal( true );
	this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 110,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 190,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 270,10, 70,25 );

	ehandles = new QComboBox( this );
	ehandles->setGeometry( 130, 50, 200, 20 );
	pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, ehandles );

	l_ehandles = new QLabel( "henv:", this );
	l_ehandles->setGeometry( 10, 50, 120, 20 );

	chandles = new QComboBox( this );
	chandles->setGeometry( 130, 80, 200, 20 );
	pOdbcTest->fill_handle_list( SQL_HANDLE_DBC, chandles );

	l_chandles = new QLabel( "hdbc:", this );
	l_chandles->setGeometry( 10, 80, 120, 20 );

	completion_type = new QComboBox( this );
	completion_type->setGeometry( 130, 110, 200, 20 );
	pOdbcTest->fill_list_box( pEnvCompletionTypes, completion_type );

	l_completion_type = new QLabel( "fType Type:", this );
	l_completion_type->setGeometry( 10, 110, 120, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

DlgEnvTransact::~DlgEnvTransact()
{
	delete ok;
	delete cancel;
	delete help;
	delete ehandles;
	delete l_ehandles;
	delete chandles;
	delete l_chandles;
    delete completion_type;
    delete l_completion_type;
}



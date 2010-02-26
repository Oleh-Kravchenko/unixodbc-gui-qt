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

#include "DlgEnvEndTran.h"
#include "OdbcTest.h"

void DlgEnvEndTran::sel_handle( int /* index */ )
{
    int handle_t;

	handles->clear();
	handle_t = pEnvHandleTypes[ handle_type->currentIndex() ].value;

	pOdbcTest->fill_handle_list( handle_t, handles );
}

void DlgEnvEndTran::Ok()
{
    int htype = pEnvHandleTypes[ handle_type->currentIndex() ].value;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( htype, handles );
	SQLHANDLE in_handle = SQL_NULL_HANDLE;
    SQLSMALLINT completion;

	if ( hand  )
		in_handle = hand->getHandle();

	pOdbcTest->out_win->append( "SQLEndTran():" );
	pOdbcTest->out_win->append( "  In:" );

    txt.sprintf( "    Handle Type: %s", pEnvHandleTypes[ handle_type->currentIndex() ].text );
	pOdbcTest->out_win->append( txt );

	if ( in_handle )
		txt.sprintf( "    Handle: %p", in_handle );
	else
		txt.sprintf( "    Handle: SQL_NULL_HANDLE" );
	pOdbcTest->out_win->append( txt );

    completion = pEnvCompletionTypes[ completion_type->currentIndex() ].value;

    SQLRETURN ret = SQLEndTran( htype, in_handle, completion );

	pOdbcTest->out_win->append( "  Return:" );
	txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
	pOdbcTest->out_win->append( txt );

	pOdbcTest->out_win->append( "" );
}

DlgEnvEndTran::DlgEnvEndTran( OdbcTest *pOdbcTest, QString name )
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

	handle_type = new QComboBox( this );
	handle_type->setGeometry( 130, 50, 200, 20 );
	pOdbcTest->fill_list_box( pEnvHandleTypes, handle_type );

	l_handle_type = new QLabel( "Handle Type:", this );
	l_handle_type->setGeometry( 10, 50, 120, 20 );

	handles = new QComboBox( this );
	handles->setGeometry( 130, 80, 200, 20 );
	pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, handles );

	l_handles = new QLabel( "Handle:", this );
	l_handles->setGeometry( 10, 80, 120, 20 );

	completion_type = new QComboBox( this );
	completion_type->setGeometry( 130, 110, 200, 20 );
	pOdbcTest->fill_list_box( pEnvCompletionTypes, completion_type );

	l_completion_type = new QLabel( "Completion Type:", this );
	l_completion_type->setGeometry( 10, 110, 120, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

	connect( handle_type, SIGNAL(activated(int)), this, SLOT( sel_handle(int)));
}

DlgEnvEndTran::~DlgEnvEndTran()
{
	delete ok;
	delete cancel;
	delete help;
	delete handles;
	delete l_handles;
	delete handle_type;
	delete l_handle_type;
    delete completion_type;
    delete l_completion_type;
}



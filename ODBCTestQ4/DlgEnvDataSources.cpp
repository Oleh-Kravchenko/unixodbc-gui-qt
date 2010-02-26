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

#include "DlgEnvDataSources.h"
#include "OdbcTest.h"

void DlgEnvDataSources::server_clkd()
{
	if ( server_valid->isChecked() )
	    server_valid->setText( "ServerName: SQL_NULL_POINTER" );
	else
	    server_valid->setText( "ServerName: VALID" );
}

void DlgEnvDataSources::description_clkd()
{
	if ( description_valid->isChecked() )
	    description_valid->setText( "Description: SQL_NULL_POINTER" );
	else
	    description_valid->setText( "Description: VALID" );
}

void DlgEnvDataSources::nlp1_clkd()
{
	if ( nlp1_valid->isChecked() )
	    nlp1_valid->setText( "NameLengthPtr1: SQL_NULL_POINTER" );
	else
	    nlp1_valid->setText( "NameLengthPtr1: VALID" );
}

void DlgEnvDataSources::nlp2_clkd()
{
	if ( nlp2_valid->isChecked() )
	    nlp2_valid->setText( "NameLengthPtr2: SQL_NULL_POINTER" );
	else
	    nlp2_valid->setText( "NameLengthPtr2: VALID" );
}

void DlgEnvDataSources::Ok()
{
    OdbcHandle *env = pOdbcTest->extract_handle_list( SQL_HANDLE_ENV, handles );
	SQLHANDLE in_handle = SQL_NULL_HANDLE;
    SQLCHAR *server_name, *description;
    SQLSMALLINT bl1, bl2, *nlp1, *nlp2, nl1, nl2;
    SQLUSMALLINT direc;
    
	if ( env )
		in_handle = env->getHandle();

	pOdbcTest->out_win->append( "SQLDataSources():" );
	pOdbcTest->out_win->append( "  In:" );

	if ( in_handle )
		txt.sprintf( "    Environment Handle: %p", in_handle );
	else
		txt.sprintf( "    Environment Handle: SQL_NULL_HENV" );
	pOdbcTest->out_win->append( txt );

	direc = pEnvDataSourcesDirections[ direction->currentIndex() ].value;
	txt.sprintf( "    Direction: %s=%d", 
		pEnvDataSourcesDirections[ direction->currentIndex() ].text,
		pEnvDataSourcesDirections[ direction->currentIndex() ].value );

    bl1 = server_len->text().toInt();
	if ( server_valid->isChecked() )
    {
        server_name = NULL;
	    txt.sprintf( "    ServerName: <null pointer>" );
    }
	else
    {
        if ( bl1 < 0 )
            bl1 = 300;

        server_name = new SQLCHAR[ bl1 ];

		txt.sprintf( "    ServerName: %p", bl1 );
    }
	pOdbcTest->out_win->append( txt );

	if ( nlp1_valid->isChecked() )
    {
        nlp1 = NULL;
	    txt.sprintf( "    NameLengthPtr 1: <null pointer>" );
    }
    else
    {
        nl1 = -9999;
        nlp1 = &nl1;
	    txt.sprintf( "    NameLengthPtr 1: %p", nlp1 );
    }
	pOdbcTest->out_win->append( txt );

    bl2 = description_len->text().toInt();
	if ( description_valid->isChecked() )
    {
        description = NULL;
	    txt.sprintf( "    Description: <null pointer>" );
    }
	else
    {
        if ( bl1 < 0 )
            bl1 = 300;

        description = new SQLCHAR[ bl1 ];

		txt.sprintf( "    Description: %p", bl1 );
    }
	pOdbcTest->out_win->append( txt );

	if ( nlp2_valid->isChecked() )
    {
        nlp2 = NULL;
	    txt.sprintf( "    NameLengthPtr 2: <null pointer>" );
    }
    else
    {
        nl2 = -9999;
        nlp2 = &nl2;
	    txt.sprintf( "    NameLengthPtr 2: %p", nlp2 );
    }
	pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLDataSources( in_handle, direc, server_name, bl1, nlp1,
            description, bl2, nlp2 );

	pOdbcTest->out_win->append( "  Return:" );
	txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
	pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        pOdbcTest->out_win->append( "  Out:" );
        if ( server_name )
        {
	        txt.sprintf( "    ServerName: %s", server_name );
            pOdbcTest->out_win->append( txt );
        }
        if ( nlp1 )
        {
            if ( nl1 == 9999 )
            {
                txt.sprintf( "    *NameLengthPtr 1: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *NameLengthPtr 1: %d", nl1 );
            }
            pOdbcTest->out_win->append( txt );
        }
        if ( description )
        {
	        txt.sprintf( "    Description: %s", description );
            pOdbcTest->out_win->append( txt );
        }
        if ( nlp2 )
        {
            if ( nl2 == 9999 )
            {
                txt.sprintf( "    *NameLengthPtr 2: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *NameLengthPtr 2: %d", nl2 );
            }
            pOdbcTest->out_win->append( txt );
        }
    }

    pOdbcTest->out_win->append( "" );

    if ( server_name )
        delete server_name;
    if ( description )
        delete description;
}

DlgEnvDataSources::DlgEnvDataSources( OdbcTest *pOdbcTest, QString name )
        : QDialog( pOdbcTest )
{
	setWindowTitle( name );
    setModal( true );

	this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 190,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 270,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 350,10, 70,25 );

	handles = new QComboBox( this );
	handles->setGeometry( 130, 50, 200, 20 );
	pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, handles );

	l_handles = new QLabel( "Environment Handle:", this );
	l_handles->setGeometry( 10, 50, 120, 20 );

	direction = new QComboBox( this );
	direction->setGeometry( 130, 80, 200, 20 );
	pOdbcTest->fill_list_box( pEnvDataSourcesDirections, direction );

	l_direction = new QLabel( "Direction:", this );
	l_direction->setGeometry( 10, 80, 120, 20 );

	server_valid = new QCheckBox( "ServerName: VALID", this );
	server_valid->setGeometry( 10, 110, 300, 15 );

	server_len = new QLineEdit( this );
    server_len->setGeometry( 350, 110, 70, 20 );
	server_len->setMaxLength( 6 );
	server_len->setText( "300" );

	l_server_len = new QLabel( "BufferLength 1:", this );
    l_server_len->setGeometry( 240, 110, 100, 20 );

	nlp1_valid = new QCheckBox( "Name Length Ptr 1: VALID", this );
	nlp1_valid->setGeometry( 10, 140, 300, 15 );

	description_valid = new QCheckBox( "Description: VALID", this );
	description_valid->setGeometry( 10, 170, 300, 15 );

	description_len = new QLineEdit( this );
    description_len->setGeometry( 350, 170, 70, 20 );
	description_len->setMaxLength( 6 );
	description_len->setText( "300" );

	l_description_len = new QLabel( "BufferLength 2:", this );
    l_description_len->setGeometry( 240, 170, 100, 20 );

	nlp2_valid = new QCheckBox( "Name Length Ptr 2: VALID", this );
	nlp2_valid->setGeometry( 10, 200, 300, 15 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

	connect( server_valid, SIGNAL( clicked()), this, SLOT( server_clkd()));
	connect( nlp1_valid, SIGNAL( clicked()), this, SLOT( nlp1_clkd()));
	connect( description_valid, SIGNAL( clicked()), this, SLOT( description_clkd()));
	connect( nlp2_valid, SIGNAL( clicked()), this, SLOT( nlp2_clkd()));
}

DlgEnvDataSources::~DlgEnvDataSources()
{
	delete ok;
	delete cancel;
	delete help;
	delete handles;
	delete l_handles;
    delete direction;
    delete l_direction;
    delete server_valid;
    delete server_len;
    delete l_server_len;
    delete nlp1_valid;
    delete description_valid;
    delete description_len;
    delete l_description_len;
    delete nlp2_valid;
}



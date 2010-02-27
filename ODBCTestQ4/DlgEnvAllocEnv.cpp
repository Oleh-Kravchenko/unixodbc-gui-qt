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

#include "DlgEnvAllocEnv.h"
#include "OdbcTest.h"

void DlgEnvAllocEnv::handle_clkd()
{
    if ( handle_valid->isChecked() )
        handle_valid->setText( "phenv: SQL_NULL_POINTER" );
    else
        handle_valid->setText( "phenv: VALID" );
}

void DlgEnvAllocEnv::slotDone()
{
    SQLHENV henv, *henv_ptr;

    pOdbcTest->out_win->append( "SQLAllocEnv():" );
    pOdbcTest->out_win->append( "  In:" );

    if ( handle_valid->isChecked()) {
        henv_ptr = NULL;
        txt.sprintf( "    phenv: SQL_NULL_HANDLE" );
    } else {
        henv_ptr = &henv;
        txt.sprintf( "    phenv: %p", henv_ptr );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLAllocEnv( henv_ptr );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ) && henv_ptr ) {
        txt.sprintf( "    *phenv: %p", henv );
        pOdbcTest->out_win->append( txt );

        pOdbcTest->listHandle.append( new OdbcHandle( SQL_HANDLE_ENV, henv ) );
    }

    pOdbcTest->out_win->append( "" );

    accept();
}

DlgEnvAllocEnv::DlgEnvAllocEnv( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    QVBoxLayout *playoutTop = new QVBoxLayout( this );

    handle_valid = new QCheckBox( "phenv: VALID", this );
    playoutTop->addWidget( handle_valid );

    pDialogButtonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help, Qt::Horizontal, this );
    playoutTop->addWidget( pDialogButtonBox );

    connect( handle_valid, SIGNAL( clicked()), this, SLOT( handle_clkd()));
    connect( pDialogButtonBox, SIGNAL(accepted()), this, SLOT(slotDone()) );
    connect( pDialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()) );
    //	connect( pDialogButtonBox, SIGNAL(helpRequested()), this, SLOT(slotHelp()) );
}

DlgEnvAllocEnv::~DlgEnvAllocEnv()
{
    delete handle_valid;
}



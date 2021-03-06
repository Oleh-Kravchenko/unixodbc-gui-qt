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
 **********************************************************************/

#include "DlgToolsNewSource.h"
#include "DlgToolsManageTest.h"
#include "OdbcTest.h"

DlgToolsNewSource::DlgToolsNewSource( OdbcTest *pOdbcTest, QString name, DlgToolsManageTest *ptest )
    : QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;
    parent_test = ptest;

    cancel = new QPushButton( "Close", this );
    cancel->setGeometry( 200,50, 70,25 );

    ok = new QPushButton( "Ok", this );
    ok->setGeometry( 110,50, 70,25 );

    source = new QLineEdit( this );
    source->setGeometry( 100, 20, 250, 20 );
    source->setMaxLength( 128 );

    l_dsn = new QLabel( "Test Source:", this );
    l_dsn->setGeometry( 10, 20, 90, 20 );

    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
}

DlgToolsNewSource::~DlgToolsNewSource()
{
    delete cancel;
    delete ok;
    delete source;
    delete l_dsn;
}

void DlgToolsNewSource::Ok()
{
    // sanity check...
    QString stringSource = source->text();
    if ( stringSource.isEmpty() )
        return;

    // add it (if it does not already exist)...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    if ( pOdbcTest->pSettings->contains( stringSource ) )
    {
        QMessageBox::critical( this, "OdbcTest", QString( tr( "Source (%1) already defined") ).arg( stringSource ) );
        pOdbcTest->pSettings->endGroup();
        return;
    }
    pOdbcTest->pSettings->setValue( stringSource, "Installed" );
    pOdbcTest->pSettings->endGroup();

    // update UI...
    parent_test->test_source->addItem( stringSource );
    parent_test->Activated( stringSource );
}



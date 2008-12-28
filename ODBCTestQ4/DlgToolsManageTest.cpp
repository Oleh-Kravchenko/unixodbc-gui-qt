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

#include "DlgToolsManageTest.h"
#include "DlgToolsNewSource.h"
#include "OdbcTest.h"

DlgToolsManageTest::DlgToolsManageTest( OdbcTest *pOdbcTest, QString name )
    : QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    close = new QPushButton( "Close", this );
    close->setGeometry( 270,80, 70,25 );

    nw = new QPushButton( "New", this );
    nw->setGeometry( 270,110, 70,25 );

    del = new QPushButton( "Delete", this );
    del->setGeometry( 270,140, 70,25 );

    test_source = new QComboBox( this );
    test_source->setGeometry( 100, 20, 250, 20 );

    l_ts = new QLabel( "Test Source:", this );
    l_ts->setGeometry( 10, 20, 80, 20 );

    param = new QGroupBox( "Connect Parameters", this );
    param->setGeometry( 10, 60, 240, 125 );

    dsn = new QComboBox( this );
    dsn->setGeometry( 80, 90, 150, 20 );

    l_dsn = new QLabel( "DSN:", this );
    l_dsn->setGeometry( 20, 90, 60, 20 );

    uid = new QLineEdit( this );
    uid->setGeometry( 80, 120, 150, 20 );
    uid->setMaxLength( 128 );

    l_uid = new QLabel( "UID:", this );
    l_uid->setGeometry( 20, 120, 60, 20 );

    pwd = new QLineEdit( this );
    pwd->setGeometry( 80, 150, 150, 20 );
    pwd->setMaxLength( 128 );

    l_pwd = new QLabel( "PWD:", this );
    l_pwd->setGeometry( 20, 150, 60, 20 );

    kw = new QLineEdit( this );
    kw->setGeometry( 80, 200, 250, 20 );
    kw->setMaxLength( 128 );

    l_kw = new QLabel( "Keywords:", this );
    l_kw->setGeometry( 10, 200, 60, 20 );

    connect( close, SIGNAL(clicked()), SLOT(Ok()) );
    connect( close, SIGNAL(clicked()), SLOT(accept()) );

    connect( nw, SIGNAL(clicked()), SLOT(NewSource()) );

    connect( del, SIGNAL(clicked()), SLOT(DelSource()) );

    // load driver list...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    test_source->addItems( pOdbcTest->pSettings->allKeys() );
    pOdbcTest->pSettings->endGroup();

    // load dsn list...
    pOdbcTest->fill_dsn_list( dsn );

    //
    // set up other fields
    //
    Activated( 0 );
    connect( test_source, SIGNAL(activated(const QString &)), this, SLOT( Activated(const QString &)));
}

DlgToolsManageTest::~DlgToolsManageTest()
{
    // sync settings with disk (mostly means 'save changes')
    {
        pOdbcTest->pSettings->sync();
        QSettings::Status nStatus = pOdbcTest->pSettings->status();
        switch ( nStatus )
        {
            case QSettings::AccessError:
                QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("AccessError when sync() settings to %1") ).arg( pOdbcTest->pSettings->fileName() ) );
                break;
            case QSettings::FormatError:
                QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("FormatError when sync() settings to %1") ).arg( pOdbcTest->pSettings->fileName() ) );
                break;
            case QSettings::NoError:
            default:
                break;
        }
    }

    delete close;
    delete nw;
    delete del;
    delete test_source;
    delete dsn;
    delete l_dsn;
    delete l_ts;
    delete pwd;
    delete l_pwd;
    delete kw;
    delete l_kw;
    delete param;
}

void DlgToolsManageTest::Activated( const QString &str )
{
    // did we find section...
    if ( pOdbcTest->pSettings->contains( str ) )
    {
        uid->clear();
        pwd->clear();
        kw->clear();
        return;
    }

    // load dsn details...
    pOdbcTest->pSettings->beginGroup( str );
    foreach ( QString stringKey, pOdbcTest->pSettings->allKeys() ) 
    {
        if ( stringKey == "SERVER0" )
        {
            pOdbcTest->set_dsn_list( dsn, pOdbcTest->pSettings->value( stringKey ).toString() );
        }
        else if ( stringKey == "LOGIN0" )
        {
            uid->setText( pOdbcTest->pSettings->value( stringKey ).toString() );
        }
        else if ( stringKey == "PASSWORD0" )
        {
            pwd->setText( pOdbcTest->pSettings->value( stringKey ).toString() );
        }
        else if ( stringKey == "KEYWORDS" )
        {
            kw->setText( pOdbcTest->pSettings->value( stringKey ).toString() );
        }
    }
    pOdbcTest->pSettings->endGroup();
}

void DlgToolsManageTest::Activated( int val )
{
    if ( test_source->count() > 0 )
    {
        Activated( test_source->itemText( val ) );
    }
}

void DlgToolsManageTest::Ok()
{
    // find driver name...
    QString driver = test_source->currentText();

    if ( driver.isEmpty() )
        return;

    // apply...
    pOdbcTest->pSettings->beginGroup( driver );
    pOdbcTest->pSettings->remove( "" ); // removes all key/values within group
    pOdbcTest->pSettings->setValue( "SERVER0", dsn->currentText() );
    pOdbcTest->pSettings->setValue( "LOGIN0", uid->text() );
    pOdbcTest->pSettings->setValue( "PASSWORD0", pwd->text() );
    pOdbcTest->pSettings->setValue( "KEYWORDS", kw->text() );
    pOdbcTest->pSettings->endGroup();
}

void DlgToolsManageTest::NewSource()
{
    DlgToolsNewSource *dlg = new DlgToolsNewSource( pOdbcTest, "New Test Sources", this );

    dlg->exec();

    delete dlg;

    // reload list...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    test_source->clear();
    test_source->addItems( pOdbcTest->pSettings->allKeys() );
    pOdbcTest->pSettings->endGroup();

    // make last (new one) the current one...
    Activated( test_source->count() - 1 );
    test_source->setCurrentIndex( test_source->count() - 1 );
}

void DlgToolsManageTest::DelSource()
{
    if ( test_source->count() == 0 )
        return;

    // which driver is current...
    QString driver = test_source->currentText();
    if ( driver.isEmpty() )
        return;

    // do we really want to do this...
    if ( QMessageBox::information( this, "OdbcTest",
                                   QString( "Delete the test source %1?" ).arg( driver ),
                                   "&Delete", "&Cancel", 0,
                                   0, 1 ) != 0 )

    {
        return;
    }

    // remove from master list...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    pOdbcTest->pSettings->remove( driver );
    pOdbcTest->pSettings->endGroup();

    // remove section...
    pOdbcTest->pSettings->remove( driver );

    // reload list...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    test_source->clear();
    test_source->addItems( pOdbcTest->pSettings->allKeys() );
    pOdbcTest->pSettings->endGroup();

    // make first the current one...
    Activated( 0 );
    test_source->setCurrentIndex( 0 );
}



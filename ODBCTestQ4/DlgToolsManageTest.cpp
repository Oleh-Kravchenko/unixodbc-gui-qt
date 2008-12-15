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

DlgToolsManageTest::DlgToolsManageTest( OdbcTest *parent, QString name )
: QDialog( parent, name, TRUE )
{
    setWindowTitle( name );

    odbctest = parent;

    init_ini_list( parent );

    close = new QPushButton( "Close", this );
    close->setGeometry( 270,80, 70,25 );

    nw = new QPushButton( "New", this );
    nw->setGeometry( 270,110, 70,25 );

    del = new QPushButton( "Delete", this );
    del->setGeometry( 270,140, 70,25 );

    test_source = new QComboBox( FALSE, this, "test Source" );
    test_source -> setGeometry( 100, 20, 250, 20 );

    l_ts = new QLabel( "Test Source:", this );
    l_ts -> setGeometry( 10, 20, 80, 20 );

    param = new QButtonGroup( "Connect Parameters", this );
    param -> setGeometry( 10, 60, 240, 125 );

    dsn = new QComboBox( FALSE, this, "dsn" );
    dsn -> setGeometry( 80, 90, 150, 20 );

    l_dsn = new QLabel( "DSN:", this );
    l_dsn -> setGeometry( 20, 90, 60, 20 );

    uid = new QLineEdit( this, "uid" );
    uid -> setGeometry( 80, 120, 150, 20 );
    uid -> setMaxLength( 128 );

    l_uid = new QLabel( "UID:", this );
    l_uid -> setGeometry( 20, 120, 60, 20 );

    pwd = new QLineEdit( this, "pwd" );
    pwd -> setGeometry( 80, 150, 150, 20 );
    pwd -> setMaxLength( 128 );

    l_pwd = new QLabel( "PWD:", this );
    l_pwd -> setGeometry( 20, 150, 60, 20 );

    kw = new QLineEdit( this, "Keywords" );
    kw -> setGeometry( 80, 200, 250, 20 );
    kw -> setMaxLength( 128 );

    l_kw = new QLabel( "Keywords:", this );
    l_kw -> setGeometry( 10, 200, 60, 20 );

    connect( close, SIGNAL(clicked()), SLOT(Ok()) );
    connect( close, SIGNAL(clicked()), SLOT(accept()) );

    connect( nw, SIGNAL(clicked()), SLOT(NewSource()) );

    connect( del, SIGNAL(clicked()), SLOT(DelSource()) );

    //
    // fill up combo box
    //

    section *s = find_section( "SQL_DRIVERS" );

    if ( s )
    {
        prop *p;

        for ( p = s -> first(); 
            p != 0; 
            p = s -> next())
        {
            test_source -> insertItem( p -> name());
        }
    }

    //
    // fill the list of DSN's
    //

    fill_dsn_list( odbctest, dsn );

    //
    // set up other fields
    //
    Activated( 0 );
    connect( test_source, SIGNAL(activated(const QString &)), 
             this, SLOT( Activated(const QString &)));
}

DlgToolsManageTest::~DlgToolsManageTest()
{
    replace_ini_list( odbctest );
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
    section *s = find_section( str.toAscii().constData() );

    if ( s )
    {
        for ( prop *prop = s->first(); prop != 0; prop = s -> next())
        {
            if ( strcmp( prop -> name(), "SERVER0" ) == 0 )
            {
                set_dsn_list( dsn, prop->value());
            }
            else if ( strcmp( prop -> name(), "LOGIN0" ) == 0 )
            {
                uid -> setText( prop -> value());
            }
            else if ( strcmp( prop -> name(), "PASSWORD0" ) == 0 )
            {
                pwd -> setText( prop -> value());
            }
            else if ( strcmp( prop -> name(), "KEYWORDS" ) == 0 )
            {
                kw -> setText( prop -> value());
            }
        }
    }
    else
    {
        uid -> clear();
        pwd -> clear();
        kw -> clear();
    }
}

void DlgToolsManageTest::Activated( int val )
{
    if ( test_source -> count() > 0 )
    {
        Activated( test_source -> text( val ));
    }
}

void DlgToolsManageTest::Ok()
{
    //
    // find driver name
    // 
    QString driver = test_source -> currentText();

    if ( driver.isNull() )
    {
        return;
    }

    //
    // Get section
    // 

    section *s = find_section( driver.toAscii().constData());
    if ( s )
    {
        //
        // remove all its entries
        //
        s -> clear();
    }
    else
    {
        s = new section( driver.toAscii().constData());
        ini_list.append( s );
    }

    //
    // Add the entries
    //

    prop *p = new prop( "SERVER0", dsn -> currentText());
    s -> append( p );
    p = new prop( "LOGIN0", uid -> text());
    s -> append( p );
    p = new prop( "PASSWORD0", pwd -> text());
    s -> append( p );
    p = new prop( "KEYWORDS", kw -> text());
    s -> append( p );
}

void DlgToolsManageTest::NewSource()
{
    dNewSource *dlg = new dNewSource( this -> odbctest, "New Test Sources", this );

    dlg -> exec();

    delete dlg;

    //
    // fill up combo box
    //

    test_source -> clear();

    section *s = find_section( "SQL_DRIVERS" );
    int last = 0;

    if ( s )
    {
        prop *p;

        for ( p = s -> first(); 
            p != 0; 
            p = s -> next())
        {
            test_source -> insertItem( p -> name());
            last ++;
        }
    }
    Activated( last - 1 );
    test_source -> setCurrentItem( last - 1 );
}

void DlgToolsManageTest::DelSource()
{
    if ( test_source -> count() == 0 )
    {
        return;
    }

    QString driver = test_source -> currentText();

    char msg [128];

    sprintf( msg, "Delete the test source %s ?", driver.toAscii().constData());

    if ( QMessageBox::information( this, "OdbcTest",
                                   msg,
                                   "&Delete", "&Cancel", 0,
                                   0, 1 ) == 0 )
    {
        //
        // Remove it from the SQL_DRIVERS section
        //
        section *s = find_section( "SQL_DRIVERS" );

        if ( s )
        {
            prop *p;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                if ( strcmp( p -> name(), driver.toAscii().constData()) == 0 )
                {
                    s -> remove( p );
                    break;
                }
            }
        }

        //
        // remove the section
        //
        s = find_section( driver.toAscii().constData());
        if ( s )
        {
            ini_list.removeRef( s );
            remove_section( odbctest, s );
        }

        //
        // fill up combo box
        //

        test_source -> clear();

        s = find_section( "SQL_DRIVERS" );

        if ( s )
        {
            prop *p;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                test_source -> insertItem( p -> name());
            }
        }
        Activated( 0 );
        test_source -> setCurrentItem( 0 );
    }
}



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

#include "DlgToolsManageAutoTest.h"

DlgToolsManageAutoTest::DlgToolsManageAutoTest( OdbcTest *parent, QString name )
: QDialog( parent, name, TRUE )
{
    setWindowTitle( name );

    odbctest = parent;

    init_ini_list( parent );

    from = new QPushButton( "From", this );
    from->setGeometry( 10,18, 70,25 );

    s_from = new QLabel( "Path", this );
    s_from -> setGeometry( 100, 20, 300, 20 );

    add = new QPushButton( "Add >", this );
    add->setGeometry( 180,90, 70,25 );

    remove = new QPushButton( "< Remove", this );
    remove->setGeometry( 180,130, 70,25 );

    close = new QPushButton( "Close", this );
    close->setGeometry( 180,200, 70,25 );

    lib_list = new QListBox( this, "Lib List" );
    lib_list -> setGeometry( 10, 80, 150, 160 );

    test_list = new QListBox( this, "Test List" );
    test_list -> setGeometry( 270, 80, 250, 160 );

    l_avail = new QLabel( "Available Test Libs:", this );
    l_avail -> setGeometry( 10, 55, 200, 20 );

    l_lib = new QLabel( "Installed Auto Tests:", this );
    l_lib -> setGeometry( 270, 55, 200, 20 );

    l_name = new QLabel( "Name:", this );
    l_name -> setGeometry( 10, 255, 200, 20 );

    l_so = new QLabel( "Lib:", this );
    l_so -> setGeometry( 10, 280, 200, 20 );

    s_name = new QLabel( "NAME", this );
    s_name -> setGeometry( 70, 255, 200, 20 );

    s_lib = new QLabel( "LIB", this );
    s_lib -> setGeometry( 70, 280, 300, 20 );

    connect( close, SIGNAL(clicked()), SLOT(Ok()) );
    connect( close, SIGNAL(clicked()), SLOT(accept()) );
    connect( from, SIGNAL(clicked()), SLOT(From()) );
    connect( add,  SIGNAL(clicked()), SLOT(Add()) );
    connect( remove,  SIGNAL(clicked()), SLOT(Remove()) );

    //
    // fill up combo box
    //

    section *s = find_section( "Auto Tests" );

    if ( s )
    {
        prop *p;

        for ( p = s -> first(); 
            p != 0; 
            p = s -> next())
        {
            test_list -> insertItem( p -> name());
        }
    }

    //
    // Setup the path, initially to the current directory
    //

    getcwd( curr_dir, sizeof( curr_dir ));
    SetPath( curr_dir );

    connect( test_list,  SIGNAL(highlighted( const QString &)), SLOT(ListSelect(const QString &)) );

    test_list -> setCurrentItem( 0 );
}

DlgToolsManageAutoTest::~DlgToolsManageAutoTest()
{
    replace_ini_list( odbctest );
    delete close;
    delete add;
    delete remove;
    delete from;
    delete s_from;
    delete lib_list;
    delete test_list;
    delete l_avail;
    delete l_lib;
    delete l_name;
    delete l_so;
    delete s_name;
    delete s_lib;
}

void DlgToolsManageAutoTest::Ok()
{
}

void DlgToolsManageAutoTest::SetPath( QString &qs )
{
    SetPath( qs.toAscii().constData());
}

void DlgToolsManageAutoTest::SetPath( const char *path )
{
    s_from -> setText( path );

    //
    // extract any libs from the path
    //

    lib_list -> clear();

    QDir q_d( path );
    if ( q_d.exists())
    {
        q_d.setFilter( QDir::Files | QDir::Hidden );
        for ( int i=0; i < q_d.count(); i++ )
        {
            lib_list -> insertItem( q_d[i] );
        }
    }
}

void DlgToolsManageAutoTest::Add()
{
    int index = lib_list -> currentItem();

    if ( index >= 0 )
    {
        QListBoxItem *lbi = lib_list -> item( index );
        const char *name = lbi -> text();

        QDir q_d( s_from->text());

        QString path = q_d.filePath ( lbi->text());

        /*
         * initialize libtool
         */

        lt_dlinit();

        lt_dlhandle handle = lt_dlopen( path.toAscii().constData());

        if ( !handle )
        {
            char msg[ 256 ];

            sprintf( msg, "Unable to open file %s", lt_dlerror());
            QMessageBox::critical( odbctest, "OdbcTest", msg );
        }
        else
        {
            //
            // Try and extract the symbols
            //
            void *pfAutoTestDesc, *pfAutoTestFunc;
            BOOL (*pfAutoTestName)(LPSTR,UINT*);

            pfAutoTestName = (BOOL(*)(LPSTR,UINT*))lt_dlsym( handle, "AutoTestName" );
            pfAutoTestDesc = lt_dlsym( handle, "AutoTestDesc" );
            pfAutoTestFunc = lt_dlsym( handle, "AutoTestFunc" );

            if ( !pfAutoTestName &&
                 !pfAutoTestDesc && 
                 !pfAutoTestFunc )
            {
                char msg[ 256 ];

                sprintf( msg, "Could not find one or more of AutoTestName, AutoTestDesc, or AutoTestFunc in auto test\n%s", path.toAscii().constData());

                QMessageBox::critical( odbctest, "OdbcTest", msg );
                lt_dlclose( handle );
                return;
            }

            char test_name[ AUTO_MAX_TEST_NAME + 1 ];
            UINT count;

            if ( pfAutoTestName )
            {
                //
                // get the test name
                //
                if ( !pfAutoTestName( test_name, &count ))
                {
                    char msg[ 256 ];

                    sprintf( msg, "AutoTestName returned FALSE in %s", path.toAscii().constData());

                    QMessageBox::critical( odbctest, "OdbcTest", msg );
                    lt_dlclose( handle );
                    return;
                }
            }
            else
            {
                char msg[ 256 ];

                sprintf( msg, "AutoTestName not exported from %s", path.toAscii().constData());

                QMessageBox::critical( odbctest, "OdbcTest", msg );
                lt_dlclose( handle );
                return;
            }

            //
            // if we are here, we can add it
            //
            //
            section *s = find_section( test_name );

            if ( s )
            {
                char msg[ 256 ];

                sprintf( msg, "Auto test '%s'already installed", test_name );

                QMessageBox::information( odbctest, "OdbcTest", msg );
                lt_dlclose( handle );
                return;
            }

            char number[ 64 ];
            s = find_section( "Auto Tests" );

            sprintf( number, "%d", count );
            prop *p = new prop( test_name, number );
            s -> append( p );

            s = new section( test_name );
            ini_list.append( s );

            p = new prop( "DLL", path.toAscii().constData());
            s -> append( p );

            lt_dlclose( handle );

            s = find_section( "Auto Tests" );

            test_list -> clear();

            if ( s )
            {
                prop *p;

                for ( p = s -> first(); 
                    p != 0; 
                    p = s -> next())
                {
                    test_list -> insertItem( p -> name());
                }
            }
            test_list -> setCurrentItem( 0 );

            ListSelect( test_name );
        }
    }
}

void DlgToolsManageAutoTest::From()
{
    QFileDialog *dlg = new QFileDialog( this, "fred", TRUE );

    dlg -> setMode( QFileDialog::Directory );

    if ( dlg -> exec() == QDialog::Accepted )
    {
        QString result = dlg -> selectedFile();
        SetPath( result );
    }

    delete dlg;
}

void DlgToolsManageAutoTest::ListSelect( const QString &name )
{
    section *s = find_section( name.toAscii().constData());

    if ( s )
    {
        s_name -> setText( name.toAscii().constData());
        s_lib -> setText( "" );

        for ( prop *prop = s->first(); prop != 0; prop = s -> next())
        {
            if ( strcmp( prop -> name(), "DLL" ) == 0 )
            {
                s_lib -> setText( prop->value());
            }
        }
    }
    else
    {
        s_name -> setText( "" );
        s_lib -> setText( "" );
    }
}

void DlgToolsManageAutoTest::Remove()
{
    int index = test_list -> currentItem();

    if ( index >= 0 )
    {
        QString autotest = test_list->text(index);

        //
        // remove it from the Auto Test section
        //

        section *s = find_section( "Auto Tests" );

        if ( s )
        {
            prop *p;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                if ( strcmp( p -> name(), autotest.toAscii().constData()) == 0 )
                {
                    s -> remove( p );
                    break;
                }
            }
        }

        //
        // remove the section
        //

        s = find_section( autotest );
        if ( s )
        {
            ini_list.removeOne( s );
            remove_section( odbctest, s );
        }

        //
        // update combo box
        //

        s = find_section( "Auto Tests" );

        s_name -> setText( "" );
        s_lib -> setText( "" );

        test_list -> clear();

        if ( s )
        {
            prop *p;
            int first = 1;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                test_list -> insertItem( p -> name());
                if ( first )
                {
                    ListSelect( p -> name());
                    first = 0;
                }
            }
        }
        test_list -> setCurrentItem( 0 );
    }
}



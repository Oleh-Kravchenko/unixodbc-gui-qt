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

#include "DlgToolsRunAutoTests.h"
#include "OdbcTest.h"

#define setqbit(lpa, pos)	\
	(lpa[((pos) / CQBITS)] |= (1 << ((pos) - (CQBITS * ((pos) / CQBITS)))))
#define SETBIT(p1,p2) setqbit(p1,(p2)-1)

DlgToolsRunAutoTests::DlgToolsRunAutoTests( OdbcTest *pOdbcTest, QString name )
    : QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    init_ini_list( parent );

    l_tests = new QLabel( "Auto Tests:", this );
    l_tests->setGeometry( 10, 15, 60, 20 );

    tests = new QTreeWidget( this );

    tests->setGeometry( 10, 40, 300, 150 );
//    tests->addColumn( "Tests", -1 );
    tests->setRootIsDecorated( TRUE );
    tests->setSelectionMode( QAbstractItemView::MultiSelection );
//    tests->setSorting( -1 );
    tests->header()->hide();

    l_sources = new QLabel( "Test Sources:", this );
    l_sources->setGeometry( 320, 15, 80, 20 );

    sources = new QListWidget( this );
    sources->setSelectionMode( QListWidget::MultiSelection );

    sources->setGeometry( 320, 40, 150, 220 );

    output = new QGroupBox( "Output", this );

    output->setGeometry( 10, 200, 90, 80 );

    b_log_file = new QCheckBox( "Log File", output );
    b_log_file->setGeometry( 10, 20, 70, 20 );

    b_screen = new QCheckBox( "Screen", output );
    b_screen->setGeometry( 10, 50, 70, 20 );
    b_screen->setChecked( TRUE );

    options = new QGroupBox( "Options", this );

    options->setGeometry( 110, 200, 200, 80 );

    b_debug = new QCheckBox( "Debug", options );
    b_debug->setGeometry( 10, 20, 80, 20 );

    b_isolate = new QCheckBox( "Isolate tests", options );
    b_isolate->setGeometry( 10, 50, 100, 20 );

    b_cursor = new QCheckBox( "Cursor Library", options );
    b_cursor->setGeometry( 90, 20, 100, 20 );
    b_cursor->setTristate( TRUE );

    run_list = new QPushButton( "Run List...", this );
    run_list->setGeometry( 10, 290, 70, 25 );
    run_list->setEnabled( FALSE );

    rlist = new QComboBox( this );
    rlist->setGeometry( 100, 290, 150, 20 );
    rlist->insertItem( 0, "<Default>" );
    rlist->setEnabled( FALSE );

    ok = new QPushButton( "Ok", this );
    ok->setGeometry( 320, 290, 70, 25 );
    ok->setEnabled( FALSE );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 400, 290, 70, 25 );

    log_file = new QPushButton( "Log File...", this );
    log_file->setGeometry( 10, 320, 70, 25 );
    log_file->setEnabled( FALSE );

    l_log = new QLabel( "auto.log", this );
    l_log->setGeometry( 89, 320, 380, 20 );
    l_log->setEnabled( FALSE );

    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );

    connect( log_file, SIGNAL(clicked()), SLOT(Log()) );

    connect( b_log_file, SIGNAL(stateChanged(int)), SLOT(LogChanged(int)));

    cursor_state = SQL_CUR_USE_DRIVER;
    connect( b_cursor, SIGNAL(stateChanged(int)), SLOT(CursorChanged(int)));

    connect( sources, SIGNAL(selectionChanged()), SLOT(TestsChanged()));
    connect( tests, SIGNAL(selectionChanged()), SLOT(TestsChanged()));

    //
    // Fill test sources
    //
    section *s = find_section( "SQL_DRIVERS" );
    if ( s )
    {
        prop *p;

        for ( p = s->first(); 
            p != 0; 
            p = s->next())
        {
            sources->addItem( p->name() );
        }
    }
    sources->addItem( "ODBC Test Handles" );


    MYQListViewItem *top = NULL;  
    MYQListViewItem *last_test = NULL;  

    //
    // fill auto tests
    //

    s = find_section( "Auto Tests" );

    if ( s )
    {
        prop *p;

        top = new MYQListViewItem( tests, top, "All" );  
        last_test = NULL ;
        for ( p = s->first(); 
            p != 0; 
            p = s->next())
        {
            add_auto_test( p->name(), top, &last_test );
        }
    }

    //
    // fill individual tests
    //
    s = find_section( "GROUPS" );
    if ( s )
    {
        prop *p, *p1;

        for ( p = s->first(); 
            p != 0; 
            p = s->next())
        {
            section *s1 = find_section( p->name() );
            if ( s1 )
            {
                top = new MYQListViewItem( tests, top, p->name());  
                last_test = NULL ;
                for ( p1 = s1->first(); 
                    p1 != 0; 
                    p1 = s1->next())
                {
                    add_auto_test( p1->name(), top, &last_test );
                }
            }
        }
    }
}

DlgToolsRunAutoTests::~DlgToolsRunAutoTests()
{
    replace_ini_list( odbctest );
    delete l_tests;
    delete tests;
    delete l_sources;
    delete sources;
    delete output;
    delete options;
    delete run_list;
    delete rlist;
    delete ok;
    delete cancel;
    delete log_file;
    delete l_log;
}

void DlgToolsRunAutoTests::Ok()
{
    //
    // use each selected source with all selected tests
    //
    int i;
    QString group_name;
    SERVERINFO server_info;
    char msg[ 1024 ];

    //
    // set up callback, handle
    // (callback activity will need our main window)
    //
    static_odbctest = pOdbcTest;

    for ( i = 0; i < sources->count(); i ++ )
    {
        if ( sources->isSelected( i ))
        {
            MYQListViewItem *group;

            QString src = sources->text( i );

            // walk tree

            group = (MYQListViewItem *) tests->firstChild();
            while ( group )
            {
                if ( group->isSelected())
                {
                    sprintf( msg, "Now executing Group %s on source %s",
                             group->group().toAscii().constData(), src.toAscii().constData());
                    print_to_odbctest( &server_info, msg, 0 );

                    section *src_section;

                    if ( src == "ODBC Test Handles" )
                    {
                        src_section = NULL;
                        server_info.henv = pOdbcTest->get_handle( SQL_HANDLE_ENV );
                        server_info.hdbc = pOdbcTest->get_handle( SQL_HANDLE_DBC );
                        server_info.hstmt = pOdbcTest->get_handle( SQL_HANDLE_STMT );

                    }
                    else
                    {
                        src_section = find_section( src.toAscii().constData() );
                        server_info.henv = NULL;
                        server_info.hdbc = NULL;
                        server_info.hstmt = NULL;
                    }

                    server_info.szSource[ 0 ] = '\0';
                    server_info.szValidServer0[ 0 ] = '\0';
                    server_info.szValidLogin0[ 0 ] = '\0';
                    server_info.szValidPassword0[ 0 ] = '\0';
                    server_info.szKeywords[ 0 ] = '\0';
                    server_info.cErrors = 0;

                    if ( b_debug->isChecked())
                        server_info.fDebug = 1;
                    else
                        server_info.fDebug = 0;

                    if ( b_isolate->isChecked())
                        server_info.fIsolate = 1;
                    else
                        server_info.fIsolate = 0;

                    if ( b_screen->isChecked())
                        server_info.fScreen = 1;
                    else
                        server_info.fScreen = 0;

                    server_info.vCursorLib = cursor_state;

                    if ( b_log_file->isChecked())
                    {
                        strcpy( server_info.szLogFile, l_log->text().toAscii().constData() );
                        server_info.fLog = 1;
                    }
                    else
                    {
                        server_info.szLogFile[ 0 ] = '\0';
                        server_info.fLog = 0;
                    }

                    server_info.hLoadedInst = NULL;

                    if ( src_section )
                    {
                        for ( prop *prop = src_section->first(); prop != 0; prop = src_section->next())
                        {
                            if ( strcmp( prop->name(), "SERVER0" ) == 0 )
                            {
                                strcpy( server_info.szValidServer0, prop->value());
                            }
                            else if ( strcmp( prop->name(), "LOGIN0" ) == 0 )
                            {
                                strcpy( server_info.szValidLogin0, prop->value());
                            }
                            else if ( strcmp( prop->name(), "PASSWORD0" ) == 0 )
                            {
                                strcpy( server_info.szValidPassword0, prop->value());
                            }
                            else if ( strcmp( prop->name(), "KEYWORDS" ) == 0 )
                            {
                                strcpy( server_info.szKeywords, prop->value());
                            }
                        }
                    }

                    strcpy( server_info.szSource, src.toAscii().constData());
                    server_info.cBuff = 0;

                    sprintf( msg, "Keywords: %s", server_info.szKeywords );
                    print_to_odbctest( &server_info, msg, 0 );

                    MYQListViewItem *sect = group->firstChild();

                    while ( sect )
                    {
                        if ( sect->isSelected())
                        {
                            sprintf( msg, "Now Executing Auto Test: %s", sect->name().toAscii().constData());
                            print_to_odbctest( &server_info, msg, 1 );
                            sprintf( msg, "Source: %s", src.toAscii().constData());
                            print_to_odbctest( &server_info, msg, 1 );
                            sprintf( msg, "Time started %s", QTime::currentTime().toString().toAscii().constData() );
                            print_to_odbctest( &server_info, msg, 1 );

                            // run tests
                            // open driver

                            section *s = find_section( sect->name().toAscii().constData() );

                            /*
                             * initialize libtool
                             */

                            lt_dlinit();

                            if ( s )
                            {
                                for ( prop *prop = s->first(); prop != 0; prop = s->next())
                                {
                                    if ( strcmp( prop->name(), "DLL" ) == 0 )
                                    {
                                        lt_dlhandle handle = lt_dlopen( prop->value());
                                        //
                                        // open the lib
                                        //
                                        if ( handle )
                                        {
                                            void (*pfAutoTestFunc)(lpSERVERINFO);
                                            BOOL (*pfAutoTestName)(LPSTR,UINT*);

                                            pfAutoTestFunc = (void(*)(lpSERVERINFO))lt_dlsym( handle, "AutoTestFunc" );
                                            pfAutoTestName = (BOOL(*)(LPSTR,UINT*))lt_dlsym( handle, "AutoTestName" );

                                            if ( !pfAutoTestFunc )
                                            {
                                                sprintf( msg, "Can't Find AutoTestFunc in %s", prop->value());
                                                print_to_odbctest( &server_info, msg, 1 );
                                            }
                                            else if ( !pfAutoTestName )
                                            {
                                                sprintf( msg, "Can't Find AutoTestName in %s", prop->value());
                                                print_to_odbctest( &server_info, msg, 1 );
                                            }
                                            else
                                            {
                                                char test_name[ AUTO_MAX_TEST_NAME + 1 ];
                                                UINT count;

                                                if ( !pfAutoTestName( test_name, &count ))
                                                {
                                                    sprintf( msg, "AutoTestName returns FALSE" );
                                                    print_to_odbctest( &server_info, msg, 1 );
                                                }
                                                else
                                                {
                                                    int size;

                                                    size = count / (sizeof(unsigned int)*8);
                                                    size ++;

                                                    server_info.rglMask = (UINT FAR *)calloc( sizeof(unsigned int), size );

                                                    server_info.hwnd = (void*)callback_function;

                                                    // now we are ready
                                                    if ( b_isolate->isChecked())
                                                    {
                                                        MYQListViewItem *test = sect->firstChild();

                                                        while ( test )
                                                        {
                                                            if ( test->isSelected())
                                                            {
                                                                SETBIT(server_info.rglMask, test->index());
                                                                pfAutoTestFunc(&server_info);
                                                            }
                                                            test = test->nextSibling();
                                                        }
                                                    }
                                                    else
                                                    {
                                                        MYQListViewItem *test = sect->firstChild();

                                                        memset( server_info.rglMask, 0, sizeof(unsigned int) * size );
                                                        while ( test )
                                                        {
                                                            if ( test->isSelected())
                                                            {
                                                                SETBIT(server_info.rglMask, test->index());
                                                            }
                                                            test = test->nextSibling();
                                                        }
                                                        pfAutoTestFunc(&server_info);
                                                    }
                                                    sprintf( msg, "Error Count: %d", server_info.cErrors);
                                                    print_to_odbctest( &server_info, msg, 1 );

                                                    free( server_info.rglMask );
                                                }
                                            }
                                            lt_dlclose( handle );
                                        }
                                        else
                                        {
                                            sprintf( msg, "Can't open %s", prop->value());
                                            print_to_odbctest( &server_info, msg, 1 );
                                        }
                                    }
                                }
                            }

                            sprintf( msg, "Time finished %s", QTime::currentTime().toString().toAscii().constData() );
                            print_to_odbctest( &server_info, msg, 1 );
                        }
                        sect = sect->nextSibling();
                    }
                }
                group = group->nextSibling();
            }
        }
    }
}

void DlgToolsRunAutoTests::Log()
{
    // allow User to select a file...
    QFileDialog dlg( this );

    dlg.setFileMode( QFileDialog::AnyFile );
    dlg.selectFile( l_log->text() );

    if ( dlg.exec() == QDialog::Accepted )
    {
        QString result = dlg.selectedFiles().at( 0 );
        l_log->setText( result );
    }
} 

void DlgToolsRunAutoTests::LogChanged( int state )
{
    if ( state )
    {
        log_file->setEnabled( TRUE );
        l_log->setEnabled( TRUE );
    }
    else
    {
        log_file->setEnabled( FALSE );
        l_log->setEnabled( FALSE );
    }
}

void DlgToolsRunAutoTests::CursorChanged( int state )
{
    if ( state == 0 )
    {
        cursor_state = SQL_CUR_USE_DRIVER;
    }
    else if ( state == 1 )
    {
        cursor_state = SQL_CUR_USE_IF_NEEDED;
    }
    else if ( state == 1 )
    {
        cursor_state = SQL_CUR_USE_ODBC;
    }
}

void DlgToolsRunAutoTests::add_auto_test( const char * test_name, MYQListViewItem *top, MYQListViewItem **item )
{
    section *s = find_section( test_name );

    if ( s )
    {
        for ( prop *prop = s->first(); prop != 0; prop = s->next())
        {
            if ( strcmp( prop->name(), "DLL" ) == 0 )
            {
                /*
                 * initialize libtool
                 */
                lt_dlinit();

                //
                // open the lib
                //
                lt_dlhandle handle = lt_dlopen( prop->value());
                if ( handle )
                {
                    void *pfAutoTestFunc;
                    BOOL (*pfAutoTestName)(LPSTR,UINT*);
                    BOOL (*pfAutoTestDesc)(UWORD,LPSTR,LPSTR);

                    pfAutoTestName = (BOOL(*)(LPSTR,UINT*))lt_dlsym( handle, "AutoTestName" );
                    pfAutoTestDesc = (BOOL(*)(UWORD,LPSTR,LPSTR))lt_dlsym( handle, "AutoTestDesc" );
                    pfAutoTestFunc = lt_dlsym( handle, "AutoTestFunc" );


                    if ( !pfAutoTestName ||
                         !pfAutoTestDesc ||
                         !pfAutoTestFunc )
                    {
                        lt_dlclose( handle );
                        return;
                    }

                    char test_name[ AUTO_MAX_TEST_NAME + 1 ];
                    char func_name[ AUTO_MAX_TESTCASE_NAME + 1 ];
                    char test_desc[ AUTO_MAX_TESTDESC_NAME + 1 ];
                    UINT count;

                    //
                    // get the test name
                    //
                    if ( !pfAutoTestName( test_name, &count ))
                    {
                        lt_dlclose( handle );
                        return;
                    }

                    *item = new MYQListViewItem( top, *item, test_name );  

                    MYQListViewItem *after = NULL;

                    for ( UWORD i = 1; i <= count; i ++ )
                    {
                        if ( pfAutoTestDesc( i, func_name, test_desc ))
                        {
                            if ( after )
                            {
                                MYQListViewItem *test = new MYQListViewItem( *item, after, func_name, test_desc, i, test_name );  
                                after = test;
                            }
                            else
                            {
                                MYQListViewItem *test = new MYQListViewItem( *item, func_name, test_desc, i, test_name );  
                                after = test;
                            }
                        }
                    }

                    lt_dlclose( handle );
                }
            }
        }
    }
}

void DlgToolsRunAutoTests::TestsChanged()
{
    int ok1 = 0, ok2 = 0;

    // are any of the sources selected?
    {
        /* 
            for ( int i = 0; i < sources->count(); i ++ )
            {
                if ( sources->isSelected( i ) )
                {
                    ok1 = 1;
                    break;
                }
            }
        */
        if ( sources->selectedItems().count() )
            ok1 = 1;
    }

    // are any of the tests selected?
    {
        /*
        MYQListViewItem *group = (MYQListViewItem*) tests->firstChild();
        while( group )
        {
            if ( group->isSelected())
            {
                ok2 = 1;
                break;
            }
            group = group->nextSibling();
        }
        */
        if ( tests->selectedItems().count() )
            ok2 = 1;
    }

    // 
    if ( ok1 && ok2 )
    {
        ok->setEnabled( TRUE );
    }
    else
    {
        ok->setEnabled( FALSE );
    }
}

void OdbcTest::options()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

void OdbcTest::trace()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

void OdbcTest::manage_test()
{
    dManageTest *dlg = new dManageTest( this, "Manage Test Sources" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::manage_auto_test()
{
    dManageAutoTest *dlg = new dManageAutoTest( this, "Manage Auto Test" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::manage_test_groups()
{
    dManageTestGroup *dlg = new dManageTestGroup( this, "Manage Test Groups" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::run_auto_tests()
{
    DlgToolsRunAutoTests *dlg = new DlgToolsRunAutoTests( this, "Run Auto Tests" );

    dlg->exec();

    delete dlg;
}


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
#include "OdbcTest.h"

DlgToolsManageAutoTest::DlgToolsManageAutoTest( OdbcTest *pOdbcTest, QString name )
    : QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    from = new QPushButton( "From", this );
    from->setGeometry( 10,18, 70,25 );

    s_from = new QLabel( "Path", this );
    s_from->setGeometry( 100, 20, 300, 20 );

    add = new QPushButton( "Add >", this );
    add->setGeometry( 180,90, 70,25 );

    remove = new QPushButton( "< Remove", this );
    remove->setGeometry( 180,130, 70,25 );

    close = new QPushButton( "Close", this );
    close->setGeometry( 180,200, 70,25 );

    lib_list = new QListWidget( this );
    lib_list->setGeometry( 10, 80, 150, 160 );

    test_list = new QListWidget( this );
    test_list->setGeometry( 270, 80, 250, 160 );

    l_avail = new QLabel( "Available Test Libs:", this );
    l_avail->setGeometry( 10, 55, 200, 20 );

    l_lib = new QLabel( "Installed Auto Tests:", this );
    l_lib->setGeometry( 270, 55, 200, 20 );

    l_name = new QLabel( "Name:", this );
    l_name->setGeometry( 10, 255, 200, 20 );

    l_so = new QLabel( "Lib:", this );
    l_so->setGeometry( 10, 280, 200, 20 );

    s_name = new QLabel( "NAME", this );
    s_name->setGeometry( 70, 255, 200, 20 );

    s_lib = new QLabel( "LIB", this );
    s_lib->setGeometry( 70, 280, 300, 20 );

    connect( close, SIGNAL(clicked()), SLOT(Ok()) );
    connect( close, SIGNAL(clicked()), SLOT(accept()) );
    connect( from, SIGNAL(clicked()), SLOT(From()) );
    connect( add,  SIGNAL(clicked()), SLOT(Add()) );
    connect( remove,  SIGNAL(clicked()), SLOT(Remove()) );

    // load test list...
    int nSection = gOdbcTools->ini.indexSection( "Auto Tests" );
    if ( nSection >= 0 )
    {
        for ( int nEntry = 0; nEntry < gOdbcTools->ini.vectorSectionEntries[nSection].size(); nEntry++ )
        {
            test_list->addItem( gOdbcTools->ini.vectorSectionEntries[nSection][nEntry].at( 0 ) );
        }
    }

    //
    // Setup the path, initially to the current directory
    //

    getcwd( curr_dir, sizeof( curr_dir ));
    SetPath( curr_dir );

    connect( test_list,  SIGNAL(highlighted( const QString &)), SLOT(ListSelect(const QString &)) );

    test_list->setCurrentItem( 0 );
}

DlgToolsManageAutoTest::~DlgToolsManageAutoTest()
{
    if ( !gOdbcTools->ini.write() )
        QMessageBox::critical( odbctest, "OdbcTest", QString( tr("Failed to write %1") ).arg( gOdbcTools->ini.fileIni.fileName() ) );

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
    s_from->setText( path );

    //
    // extract any libs from the path
    //

    lib_list->clear();

    QDir q_d( path );
    if ( q_d.exists())
    {
        q_d.setFilter( QDir::Files | QDir::Hidden );
        for ( uint i=0; i < q_d.count(); i++ )
        {
            lib_list ->addItem( q_d[i] );
        }
    }
}

void DlgToolsManageAutoTest::Add()
{
    int index = lib_list ->currentRow();

    if ( index >= 0 )
    {
        QListWidgetItem *lbi = lib_list->item( index );
//        const char *name = lbi->text().toAscii().constData();

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

            // does test already exist...
            {
                int nSection = gOdbcTools->ini.vectorSections.indexOf( test_name );
    
                if ( nSection >= 0 )
                {
                    QMessageBox::information( odbctest, "OdbcTest", QString( tr("Auto test '%1'already installed") ).arg( test_name ) );
                    lt_dlclose( handle );
                    return;
                }
    
            }

            // add test to master list...
            {
                char number[ 64 ];
                sprintf( number, "%d", count );
    
                int nSection = gOdbcTools->ini.vectorSections.indexOf( "Auto Tests" );
                gOdbcTools->ini.appendEntry( nSection, test_name, number );
            }

            // add test section & entries...
            {
                int nSection = gOdbcTools->ini.appendSection( test_name );
                gOdbcTools->ini.appendEntry( nSection, "DLL", path );
            }

            lt_dlclose( handle );

            // reload list...
            {
                int nSection = gOdbcTools->ini.vectorSections.indexOf( "Auto Tests" );
    
                test_list->clear();
    
                if ( nSection >= 0 )
                {
                    for ( int nEntry = 0; nEntry < gOdbcTools->ini.vectorSectionEntries[nSection].size(); nEntry++ )
                    {
                        test_list->addItem( gOdbcTools->ini.vectorSectionEntries[nSection][nEntry].at( 0 ) );
                    }
                }
                test_list->setCurrentItem( 0 );
    
                ListSelect( test_name );
            }
        }
    }
}

void DlgToolsManageAutoTest::From()
{
    QFileDialog *dlg = new QFileDialog( this, "fred" );

    dlg->setFileMode( QFileDialog::Directory );

    if ( dlg->exec() == QDialog::Accepted )
    {
        QString result = dlg->directory().absolutePath();
        SetPath( result );
    }

    delete dlg;
}

void DlgToolsManageAutoTest::ListSelect( const QString &name )
{
    int nSection = gOdbcTools->ini.vectorSections.indexOf( name );

    if ( nSection >= 0 )
    {
        s_name->setText( name );
        s_lib->setText( "" );

        // get the DLL name...
        for ( int nEntry = 0; nEntry < gOdbcTools->ini.vectorSectionEntries[nSection].size(); nEntry++ )
        {
            if ( gOdbcTools->ini.vectorSectionEntries[nSection][nEntry].at( 0 ) == "DLL" )
            {
                s_lib->setText( gOdbcTools->ini.vectorSectionEntries[nSection][nEntry].at( 1 ) );
                break;
            }
        }
    }
    else
    {
        s_name->setText( "" );
        s_lib->setText( "" );
    }
}

void DlgToolsManageAutoTest::Remove()
{
    int nSection = test_list->currentRow();

    if ( nSection >= 0 )
    {
        // remove from master list...
        gOdbcTools->ini.removeEntry( "Auto Tests", gOdbcTools->ini.vectorSections[nSection] );
        
        // remove section & entries...
        gOdbcTools->ini.removeSection( nSection );

        // reload list...
        {
            int nSection = gOdbcTools->ini.vectorSections.indexOf( "Auto Tests" );

            test_list->clear();

            if ( nSection >= 0 )
            {
                for ( int nEntry = 0; nEntry < gOdbcTools->ini.vectorSectionEntries[nSection].size(); nEntry++ )
                {
                    test_list->addItem( gOdbcTools->ini.vectorSectionEntries[nSection][nEntry].at( 0 ) );
                }
            }

            // select first item...
            if ( test_list->count() )
            {
                test_list->setCurrentItem( 0 );
                ListSelect( test_list->currentItem()->text() );
            }

        }
    }
}



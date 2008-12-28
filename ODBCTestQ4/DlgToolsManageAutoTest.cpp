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
    pOdbcTest->pSettings->beginGroup( "Auto Tests" );
    test_list->addItems( pOdbcTest->pSettings->allKeys() );
    pOdbcTest->pSettings->endGroup();

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

    if ( index < 0 )
        return;

    QListWidgetItem *lbi = lib_list->item( index );
    QDir q_d( s_from->text());
    QString path = q_d.filePath ( lbi->text() );
    QLibrary l( path );

    if ( !l.isLoaded() )
    {
        QMessageBox::critical( pOdbcTest, "OdbcTest", l.errorString() );
        return;
    }
    
    //
    // Try and extract the symbols
    //
    void *pfAutoTestDesc, *pfAutoTestFunc;
    BOOL (*pfAutoTestName)(LPSTR,UINT*);

    pfAutoTestName = (BOOL(*)(LPSTR,UINT*))l.resolve( "AutoTestName" );
    pfAutoTestDesc = l.resolve( "AutoTestDesc" );
    pfAutoTestFunc = l.resolve( "AutoTestFunc" );

    if ( !pfAutoTestName &&
         !pfAutoTestDesc && 
         !pfAutoTestFunc )
    {
        QMessageBox::critical( pOdbcTest, "OdbcTest", l.errorString() );
        QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("Could not find one or more of AutoTestName, AutoTestDesc, or AutoTestFunc in auto test\n%1") ).arg( path ) );
        return;
    }

    char szAutoTestName[ AUTO_MAX_TEST_NAME + 1 ];  // name of test as provided by test library
    UINT nTestCases = 0;                            // each test library may have 0-n test cases

    if ( pfAutoTestName )
    {
        // get the test name...
        if ( !pfAutoTestName( szAutoTestName, &nTestCases ) )
        {
            QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("AutoTestName returned FALSE in %1") ).arg( path ) );
            return;
        }
    }
    else
    {
        QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("AutoTestName not exported from %1") ).arg( path ) );
        return;
    }

    // does test already exist...
    if ( pOdbcTest->pSettings->contains( szAutoTestName ) )
    {
        QMessageBox::information( pOdbcTest, "OdbcTest", QString( tr("Auto test '%1'already installed") ).arg( szAutoTestName ) );
        return;
    }

    // add test to master list...
    pOdbcTest->pSettings->beginGroup( "Auto Tests" );
    pOdbcTest->pSettings->setValue( szAutoTestName, nTestCases );
    pOdbcTest->pSettings->endGroup();

    // add test section & entries...
    pOdbcTest->pSettings->beginGroup( szAutoTestName );
    pOdbcTest->pSettings->setValue( "DLL", path ); /*! \todo escape slashs */
    pOdbcTest->pSettings->endGroup();

    // reload list...
    pOdbcTest->pSettings->beginGroup( "Auto Tests" );
    test_list->clear();
    test_list->addItems( pOdbcTest->pSettings->allKeys() );
    pOdbcTest->pSettings->endGroup();
    test_list->setCurrentItem( 0 );
    ListSelect( szAutoTestName );
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

    if ( pOdbcTest->pSettings->contains( name ) )
    {
        s_name->setText( name );
        s_lib->setText( "" );

        // get the DLL name...
        pOdbcTest->pSettings->beginGroup( name );
        s_lib->setText( pOdbcTest->pSettings->value( "DLL" ).toString() );
        pOdbcTest->pSettings->endGroup();
    }
    else
    {
        s_name->setText( "" );
        s_lib->setText( "" );
    }
}

void DlgToolsManageAutoTest::Remove()
{
    QListWidgetItem *pListWidgetItem = test_list->currentItem();

    if ( !pListWidgetItem )
        return;

    // remove from master list...
    pOdbcTest->pSettings->beginGroup( "Auto Tests" );
    pOdbcTest->pSettings->remove( pListWidgetItem->text() );
    pOdbcTest->pSettings->endGroup();

    // remove section & entries...
    pOdbcTest->pSettings->remove( pListWidgetItem->text() );

    // reload list...
    {
        pOdbcTest->pSettings->beginGroup( "Auto Tests" );
        test_list->clear();
        test_list->addItems( pOdbcTest->pSettings->allKeys() );
        pOdbcTest->pSettings->endGroup();

        // select first item...
        if ( test_list->count() )
        {
            test_list->setCurrentItem( 0 );
            ListSelect( test_list->currentItem()->text() );
        }
    }
}



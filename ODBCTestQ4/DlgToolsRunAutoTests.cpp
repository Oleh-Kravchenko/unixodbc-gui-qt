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
#include "DlgToolsManageAutoTest.h"
#include "DlgToolsManageTestGroup.h"
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

    // load list...
    pOdbcTest->pSettings->beginGroup( "SQL_DRIVERS" );
    sources->addItems( pOdbcTest->pSettings->allKeys() );
    sources->addItem( "ODBC Test Handles" );
    pOdbcTest->pSettings->endGroup();

    // load treeview...
    {
        QTreeWidgetItem *top = NULL;  
        QTreeWidgetItem *last_test = NULL;  
    
        // load treeview with all "Auto Tests"...    
        {
            // get all "Auto Tests"...
            pOdbcTest->pSettings->beginGroup( "Auto Tests" );
            QStringList stringlistAutoTests = pOdbcTest->pSettings->allKeys();
            pOdbcTest->pSettings->endGroup();
                
            top = new QTreeWidgetItem( tests, top );  
            top->setText( 0, "All" );
            last_test = NULL ;
                
            // load treeview with all tests...
            foreach( QString stringAutoTest, stringlistAutoTests )
            {
                add_auto_test( stringAutoTest, top, &last_test );
            }
        }
    
        // load treeview with all "GROUPS"...
        {
            // get all "GROUPS"...
            pOdbcTest->pSettings->beginGroup( "GROUPS" );
            QStringList stringlistGroups = pOdbcTest->pSettings->allKeys();
            pOdbcTest->pSettings->endGroup();

            foreach( QString stringGroup, stringlistGroups )
            {
                // get all tests in group...
                pOdbcTest->pSettings->beginGroup( stringGroup );
                QStringList stringlistTests = pOdbcTest->pSettings->allKeys();
                pOdbcTest->pSettings->endGroup();

                top = new QTreeWidgetItem( tests, top );  
                top->setText( 0, stringGroup );
                last_test = NULL ;

                // load treeview with all tests in group...
                foreach( QString stringTest, stringlistTests )
                {
                    add_auto_test( stringTest, top, &last_test );
                }
            }
        }
    }
}

DlgToolsRunAutoTests::~DlgToolsRunAutoTests()
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

/*!
 * \brief   Run the tests. 
 *  
 *          For each selected Source (SQL_DRIVER) run selected Tests (Auto Tests). The
 *          Sources are processed in the order found in the UI. The Tests are also
 *          processed in the order found in the UI. The Groups (of tests) are processed
 *          last. One should find that the order reflects the order of things in the
 *          settings file.
 * 
 */
void DlgToolsRunAutoTests::Ok()
{
    SQLHWND hWnd = NULL;

#ifdef WIN32
    hWnd = (SQLHWND)pOdbcTest->out_win;
#else

    /* 
     * Init a ODBCINSTWND 
     * --- 
     *  
     * This is for SERVERINFO::hwnd.
     *  
     * We use a generic handle (ODBCINSTWND) and specify a Qt4 graphical user interface (odbcinstQ4). 
     *  
     * The odbcinstQ4 library provides the Qt4 graphical user interface for things like SQLCreateDataSource
     * and provides szLogPrintf/szMessageBox. The odbcinstQ4 library is a plugin which is loaded by the
     * odbcinst library (and some others) as needed - it should NOT be used directly by this application 
     * or by any of the test libraries. The test libraries should never need to interpret SERVERINFO::hwnd - 
     * they should simply pass it on wherever needed. 
     *  
     * This application and test libraries should link to the odbcinst library to get szLogPrintf and 
     * szMessageBox. 
     *  
     * NOTE 
     *  
     * It is bad form to have auto tests rely upon any user interaction so a test library which needs 
     * a viable hwnd should not really happen (not even for SQLDriverConnect). However; szLogPrintf and 
     * szMessageBox will use it internally.  
     *  
     * On MS'sm the szLogPrintf and szMessageBox are found in the gtrtst (gator test) library. Here; we 
     * get it via the odbcinst library. 
     *  
     */
    ODBCINSTWND Wnd;

    strcpy( Wnd.szUI, "odbcinstQ4" );   // UI plugin to use (Qt4).
    Wnd.hWnd = pOdbcTest->out_win;      // Output window for szLogPrintf and szMessageBox.
    hWnd = (SQLHWND)(&Wnd);
#endif

    /* 
     * Init a SERVERINFO
     * ---
     *
     * More refinements are done as we process.
     *
     */
    SERVERINFO ServerInfo;

    ServerInfo.cBuff                = 0;
    ServerInfo.cErrors              = 0;
    ServerInfo.failed               = 0;
    ServerInfo.fDebug               = ( b_debug->isChecked() ? true : false );
    ServerInfo.fIsolate             = ( b_isolate->isChecked() ? true : false );
    ServerInfo.fLog                 = ( b_log_file->isChecked() ? true : false );
    ServerInfo.fScreen              = ( b_screen->isChecked() ? true : false );
    ServerInfo.hdbc                 = SQL_NULL_HANDLE;
    ServerInfo.henv                 = SQL_NULL_HANDLE;
    ServerInfo.hLoadedInst          = NULL;
    ServerInfo.hstmt                = SQL_NULL_HANDLE;
    ServerInfo.hwnd                 = hWnd;
    ServerInfo.rglMask              = NULL;
    *(ServerInfo.szBuff)            = '\0';
    *(ServerInfo.szKeywords)        = '\0';
    *(ServerInfo.szLogFile)         = '\0';
    *(ServerInfo.szSource)          = '\0';
    *(ServerInfo.szValidLogin0)     = '\0';
    *(ServerInfo.szValidPassword0)  = '\0';
    *(ServerInfo.szValidServer0)    = '\0';
    ServerInfo.vCursorLib           = cursor_state; 

    if ( b_log_file->isChecked() ) strcpy( ServerInfo.szLogFile, l_log->text().toAscii().constData() );

    // do it
    runSources( &ServerInfo );
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

void DlgToolsRunAutoTests::add_auto_test( const QString &stringTest, QTreeWidgetItem *top, QTreeWidgetItem **item )
{
    // get test library file name...
    pOdbcTest->pSettings->beginGroup( stringTest );
    QString stringTestFileName = pOdbcTest->pSettings->value( "DLL" ).toString();
    pOdbcTest->pSettings->endGroup();

    if ( stringTestFileName.isEmpty() )
        return;

    // load test library...
    QLibrary libraryTest( stringTestFileName );

    if ( !libraryTest.isLoaded() )
        return;

    // get our entry points...
    AUTOTESTNAME pAutoTestName = (AUTOTESTNAME)libraryTest.resolve( "AutoTestName" );
    AUTOTESTDESC pAutoTestDesc = (AUTOTESTDESC)libraryTest.resolve( "AutoTestDesc" );
    AUTOTESTFUNC pAutoTestFunc = (AUTOTESTFUNC)libraryTest.resolve( "AutoTestFunc" );

    if ( !pAutoTestName || !pAutoTestDesc || !pAutoTestFunc )
        return;

    // get test name, number of test cases...
    char szTest[ AUTO_MAX_TEST_NAME + 1 ];
    UINT nTestCases;

    if ( !pAutoTestName( szTest, &nTestCases ) )
        return;

    // add test...
    QTreeWidgetItem *ptreewidgetitemTest = *item = new QTreeWidgetItem( top, *item );  
    ptreewidgetitemTest->setText( 0, szTest );

    // add test cases...
    QTreeWidgetItem *ptreewidgetitemTestCase = NULL;

    for ( UWORD i = 1; i <= nTestCases; i ++ )
    {
        // get test case details...
        char szTestCase[ AUTO_MAX_TESTCASE_NAME + 1 ];
        char szTestCaseDesc[ AUTO_MAX_TESTDESC_NAME + 1 ];

        if ( !pAutoTestDesc( i, szTestCase, szTestCaseDesc ) )
            continue;

        // create test case tree widget item...
        if ( ptreewidgetitemTestCase )
            ptreewidgetitemTestCase = new QTreeWidgetItem( ptreewidgetitemTest, ptreewidgetitemTestCase );
        else
            ptreewidgetitemTestCase = new QTreeWidgetItem( ptreewidgetitemTest );  

        ptreewidgetitemTestCase->setText( 0, szTestCase );
        ptreewidgetitemTestCase->setText( 1, szTestCaseDesc );
    }
}

void DlgToolsRunAutoTests::runSources( SERVERINFO *pServerInfo )
{
    // for each selected source (SQL_DRIVER)...
    foreach( QListWidgetItem *pListWidgetItem, sources->selectedItems() )
    {
        QString stringSource = pListWidgetItem->text();

        // init some SERVERINFO stuff...
        strcpy( pServerInfo->szSource, stringSource.toAscii().constData() );

        pOdbcTest->pSettings->beginGroup( stringSource );
        strcpy( pServerInfo->szValidServer0, pOdbcTest->pSettings->value( "SERVER0" ).toString().toAscii().constData() );
        strcpy( pServerInfo->szValidLogin0, pOdbcTest->pSettings->value( "LOGIN0" ).toString().toAscii().constData() );
        strcpy( pServerInfo->szValidPassword0, pOdbcTest->pSettings->value( "PASSWORD0" ).toString().toAscii().constData() );
        strcpy( pServerInfo->szKeywords, pOdbcTest->pSettings->value( "KEYWORDS" ).toString().toAscii().constData() );
        pOdbcTest->pSettings->endGroup();

        // do it...
        runGroups( pServerInfo, stringSource );
    }
}

void DlgToolsRunAutoTests::runGroups( SERVERINFO *pServerInfo, const QString &stringSource )
{
    // process groups (1st level in tree)...
    QTreeWidgetItem *ptreewidgetitemGroup = NULL;

    for ( int n = 0; (ptreewidgetitemGroup = tests->topLevelItem( n )); n++ )
    {
        if ( !ptreewidgetitemGroup->isSelected() )
            continue;

        // init/reinit some SERVERINFO stuff (reinit in case test messed with it)...
        if ( stringSource == "ODBC Test Handles" )
        {
            pServerInfo->henv = pOdbcTest->get_handle( SQL_HANDLE_ENV );
            pServerInfo->hdbc = pOdbcTest->get_handle( SQL_HANDLE_DBC );
            pServerInfo->hstmt = pOdbcTest->get_handle( SQL_HANDLE_STMT );

        }
        else
        {
            pServerInfo->henv = NULL;
            pServerInfo->hdbc = NULL;
            pServerInfo->hstmt = NULL;
        }

        // kick out some progress info...
        QString stringGroup = ptreewidgetitemGroup->text( 0 );            
        QString stringMessage;

        stringMessage = QString( tr("Now executing Group %1 on source %2") ).arg( stringGroup ).arg( stringSource ); // we format the message here so we can use tr()
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        stringMessage = QString( tr("Keywords: %1") ).arg( pServerInfo->szKeywords );
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );

        // do it...
        runTests( pServerInfo, ptreewidgetitemGroup );
    }
}

void DlgToolsRunAutoTests::runTests( SERVERINFO *pServerInfo, QTreeWidgetItem *ptreewidgetitemGroup )
{
    // process tests (2nd level in tree)...
    QTreeWidgetItem *ptreewidgetitemTest = NULL;

    for ( int n = 0; (ptreewidgetitemTest = ptreewidgetitemGroup->child( n )); n++ )
    {
        if ( !ptreewidgetitemTest->isSelected() )
            continue;

        // dot it...        
        runTest( pServerInfo, ptreewidgetitemTest );
    }
}

void DlgToolsRunAutoTests::runTest( SERVERINFO *pServerInfo, QTreeWidgetItem *ptreewidgetitemTest )
{
    QString stringTest = ptreewidgetitemTest->text( 0 );            
    QString stringMessage;

    // get test library file name...
    pOdbcTest->pSettings->beginGroup( stringTest );
    QString stringTestFileName = pOdbcTest->pSettings->value( "DLL" ).toString();
    pOdbcTest->pSettings->endGroup();

    if ( stringTestFileName.isEmpty() )
    {
        stringMessage = QString( tr("Failed to find library name (DLL) in settings for %1 test.") ).arg( stringTest );
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        return;
    }

    // kick out some progress info...
    stringMessage = QString( tr("Now Executing Auto Test: %1") ).arg( stringTest );
    szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
    stringMessage = QString( tr("Time started %1") ).arg( QTime::currentTime().toString() );
    szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );

    // load test library...
    QLibrary libraryTest( stringTestFileName );
    
    if ( !libraryTest.isLoaded() )
    {
        stringMessage = QString( tr("Failed to load test library %1") ).arg( stringTestFileName );
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        return;
    }

    // get our entry points...
    AUTOTESTNAME pAutoTestName = (AUTOTESTNAME)libraryTest.resolve( "AutoTestName" );
    AUTOTESTFUNC pAutoTestFunc = (AUTOTESTFUNC)libraryTest.resolve( "AutoTestFunc" );

    if ( !pAutoTestFunc )
    {
        stringMessage = QString( tr("Failed to resolve AutoTestFunc in library %1") ).arg( stringTestFileName );
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        return;
    }

    if ( !pAutoTestName )
    {
        stringMessage = QString( tr("Failed to resolve AutoTestName in library %1") ).arg( stringTestFileName );
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        return;
    }

    // get test name and number of test cases...
    char szTest[ AUTO_MAX_TEST_NAME + 1 ];
    UINT nTestCases;

    if ( !pAutoTestName( szTest, &nTestCases ) )
    {
        stringMessage = tr("AutoTestName returns FALSE");
        szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
        return;
    }

    // do it...
    runTestCases( pServerInfo, ptreewidgetitemTest, pAutoTestFunc, nTestCases );

    //
    stringMessage = QString( tr("Time finished %s") ).arg( QTime::currentTime().toString() );
    szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );
}

void DlgToolsRunAutoTests::runTestCases( SERVERINFO *pServerInfo, QTreeWidgetItem *ptreewidgetitemTest, AUTOTESTFUNC pAutoTestFunc, UINT nTestCases )
{
    QString stringMessage;
    int     size;

    size = nTestCases / (sizeof(unsigned int)*8);
    size ++;

    // init mask...
    pServerInfo->rglMask = (UINT FAR *)calloc( sizeof(unsigned int), size );

    // for each test case call into test library... 
    if ( b_isolate->isChecked())
    {
        QTreeWidgetItem *ptreewidgetitemTestCase = NULL;

        for ( int n = 0; (ptreewidgetitemTestCase = ptreewidgetitemTest->child( n )); n++ )
        {
            if ( ptreewidgetitemTestCase->isSelected())
            {
                SETBIT( pServerInfo->rglMask, ptreewidgetitemTest->indexOfChild( ptreewidgetitemTestCase ) );
                pAutoTestFunc( pServerInfo );
            }
        }
    }
    // call into test library once... 
    else
    {
        QTreeWidgetItem *ptreewidgetitemTestCase = NULL;

        memset( pServerInfo->rglMask, 0, sizeof(unsigned int) * size );

        for ( int n = 0; (ptreewidgetitemTestCase = ptreewidgetitemTest->child( n )); n++ )
        {
            if ( ptreewidgetitemTestCase->isSelected())
            {
                SETBIT(pServerInfo->rglMask, ptreewidgetitemTest->indexOfChild( ptreewidgetitemTestCase ) );
            }
        }
        pAutoTestFunc( pServerInfo );
    }

    // errors?
    stringMessage = QString( tr("Error Count: %1") ).arg( pServerInfo->cErrors );
    szLogPrintf( pServerInfo, false, stringMessage.toLatin1().data() );

    // fini mask...
    free( pServerInfo->rglMask );
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
        QTreeWidgetItem *group = (QTreeWidgetItem*) tests->firstChild();
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

void OdbcTest::slotOptions()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

void OdbcTest::slotTrace()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

void OdbcTest::slotManageTestSources()
{
    DlgToolsManageTest *dlg = new DlgToolsManageTest( this, "Manage Test Sources" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotManageAutoTests()
{
    DlgToolsManageAutoTest *dlg = new DlgToolsManageAutoTest( this, "Manage Auto Test" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotManageTestGroups()
{
    DlgToolsManageTestGroup *dlg = new DlgToolsManageTestGroup( this, "Manage Test Groups" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotRunAutoTests()
{
    DlgToolsRunAutoTests *dlg = new DlgToolsRunAutoTests( this, "Run Auto Tests" );

    dlg->exec();

    delete dlg;
}


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

#include "OdbcTest.h"

OdbcTest::OdbcTest( QWidget *parent )
    : QMainWindow( parent )
{
    /*! 
     *  Open the test configuration file once and allow all supporting code to use it. Let Qt
     *  delete the object when this (its parent) deconstructs. The settings will automatically
     *  sync to disk at that time.
     *  
     *  \note   Using QSettings to read/write ini files imposes some limitations. The main
     *          one is that slashs in directory names need to be escaped.
     */
    pSettings = new QSettings( QDir::homePath() + "Gator.ini", QSettings::IniFormat, this );

/*
    QPopupMenu *file = new QPopupMenu( this );
	int id;

    file->insertItem( "E&xit", qApp, SLOT(quit()), CTRL+Key_Q );

    QPopupMenu* diag = new QPopupMenu( this );
    diag->insertItem( "SQLGetDiag&Rec...", this, SLOT(sqlgetdiagrec()) );
    diag->insertItem( "SQLGetDiag&Field...", this, SLOT(sqlgetdiagfield()) );
    diag->insertItem( "SQL&Error...", this, SLOT(sqlerror()) );
    diag->insertSeparator();
    id = diag->insertItem( "Errors &All", this, SLOT(errorall()) );
	diag->setItemEnabled( id, FALSE );

    QPopupMenu* env = new QPopupMenu( this );
    env->insertItem( "SQL&AllocEnv...", this, SLOT(sqlallocenv()) );
    env->insertItem( "SQL&AllocHandle...", this, SLOT(sqlallochandle()) );
    env->insertItem( "SQLDataS&ources...", this, SLOT(sqldatasources()) );
    env->insertItem( "S&QLDrivers...", this, SLOT(sqldrivers()) );
    env->insertItem( "SQL&FreeEnv...", this, SLOT(sqlfreeenv()) );
    env->insertItem( "SQLF&reeHandle...", this, SLOT(sqlfreehandle()) );
    env->insertItem( "SQLE&ndTran...", this, SLOT(sqlendtran()) );
    env->insertItem( "SQL&Transact...", this, SLOT(sqltransact()) );
    env->insertSeparator();
    id = env->insertItem( "Data &Sources All", this, SLOT(datasourcesall()) );
	env->setItemEnabled( id, FALSE );
    id = env->insertItem( "Dri&vers All", this, SLOT(driversall()) );
	env->setItemEnabled( id, FALSE );

    QPopupMenu* conn = new QPopupMenu( this );
    conn->insertItem( "SQL&AllocConnect...", this, SLOT(sqlallocconnect()) );
    conn->insertItem( "SQL&BrowseConnect...", this, SLOT(sqlbrowseconnect()) );
    conn->insertItem( "SQL&Connect...", this, SLOT(sqlconnect()) );
    conn->insertItem( "SQLD&riverConnect...", this, SLOT(sqldriverconnect()) );
    conn->insertItem( "SQL&Disconnect...", this, SLOT(sqldisconnect()) );
    conn->insertItem( "SQL&FreeConnect...", this, SLOT(sqlfreeconnect()) );
    conn->insertItem( "S&QLGetFunctions...", this, SLOT(sqlgetfunctions()) );
    conn->insertItem( "SQLGet&Info...", this, SLOT(sqlgetinfo()) );
    conn->insertItem( "SQLN&ativeSQL...", this, SLOT(sqlnativesql()) );
	conn->setItemEnabled( id, FALSE );
    conn->insertSeparator();
    conn->insertItem( "F&ull Connect...", this, SLOT(fullconnect()), Qt::CTRL+Qt::Key_F );
    id = conn->insertItem( "Fu&ll Disconnect", this, SLOT(fulldisconnect()), Qt::CTRL+Qt::Key_D );
	conn->setItemEnabled( id, FALSE );
    conn->insertItem( "G&et Info All", this, SLOT(getinfoall()) );
    id = conn->insertItem( "Get &Functions All", this, SLOT(getfunctionsall()) );
	conn->setItemEnabled( id, FALSE );

    QPopupMenu* desc = new QPopupMenu( this );
    desc->insertItem( "SQLCop&yDesc...", this, SLOT(sqlcopydesc()) );
    desc->insertItem( "SQLGetDesc&Field...", this, SLOT(sqlgetdescfield()) );
    desc->insertItem( "SQLG&etDescRec...", this, SLOT(sqlgetdescrec()) );
    id = desc->insertItem( "SQLSetDescF&ield...", this, SLOT(sqlsetdescfield()) );
	desc->setItemEnabled( id, FALSE );
    id = desc->insertItem( "SQLS&etDescRec...", this, SLOT(sqlsetdescrec()) );
	desc->setItemEnabled( id, FALSE );
    desc->insertSeparator();
    id = desc->insertItem( "Get Descriptors All", this, SLOT(getdescriptorsall()) );
	desc->setItemEnabled( id, FALSE );

    QPopupMenu* stmt = new QPopupMenu( this );
    stmt->insertItem( "SQL&AllocStmt...", this, SLOT(sqlallocstmt()) );
    id = stmt->insertItem( "S&QLBindParam...", this, SLOT(sqlbindparam()) );
	stmt->setItemEnabled( id, FALSE );
    id = stmt->insertItem( "SQL&BindParameter...", this, SLOT(sqlbindparameter()) );
	stmt->setItemEnabled( id, FALSE );
    stmt->insertItem( "SQL&Cancel...", this, SLOT(sqlcancel()) );
    stmt->insertItem( "SQLCl&oseCursor...", this, SLOT(sqlclosecursor()) );
    stmt->insertItem( "SQLDe&scribeParam...", this, SLOT(sqldescribeparam()) );
    stmt->insertItem( "SQL&Execute...", this, SLOT(sqlexecute()) );
    stmt->insertItem( "SQLExec&Direct...", this, SLOT(sqlexecdirect()) );
    stmt->insertItem( "SQL&FreeStmt...", this, SLOT(sqlfreestmt()) );
    stmt->insertItem( "SQL&GetCursorName...", this, SLOT(sqlgetcursorname()) );
    stmt->insertItem( "SQL&NumParams...", this, SLOT(sqlnumparams()) );
    stmt->insertItem( "SQLPara&mData...", this, SLOT(sqlparamdata()) );
    stmt->insertItem( "SQLPa&ramOptions...", this, SLOT(sqlparamoptions()) );
    stmt->insertItem( "SQL&Prepare...", this, SLOT(sqlprepare()) );
    stmt->insertItem( "SQLP&utData...", this, SLOT(sqlputdata()) );
    stmt->insertItem( "SQ&LSetCursorName...", this, SLOT(sqlsetcursorname()) );
    stmt->insertSeparator();
    id = stmt->insertItem( "F&ill Param...", this, SLOT(fillparam()) );
	stmt->setItemEnabled( id, FALSE );
    id = stmt->insertItem( "Sho&w Param...", this, SLOT(showparam()) );
	stmt->setItemEnabled( id, FALSE );
    id = stmt->insertItem( "S&how Cursor Settings...", this, SLOT(showcursorsettings()) );
	stmt->setItemEnabled( id, FALSE );

    QPopupMenu* attr = new QPopupMenu( this );
    attr->insertItem( "SQLSet&StmtAttr...", this, SLOT(sqlsetstmtattr()) );
    attr->insertItem( "SQLGetS&tmtAttr...", this, SLOT(sqlgetstmtattr()) );
    attr->insertItem( "SQLSetStmt&Option...", this, SLOT(sqlsetstmtoption()) );
    attr->insertItem( "SQLGetStmtOpt&ion...", this, SLOT(sqlgetstmtoption()) );
    attr->insertSeparator();
    attr->insertItem( "SQLSetConnect&Attr...", this, SLOT(sqlsetconnectattr()) );
    attr->insertItem( "SQLGetC&onnectAttr...", this, SLOT(sqlgetconnectattr()) );
    attr->insertItem( "SQLSetConnectO&ption...", this, SLOT(sqlsetconnectoption()) );
    attr->insertItem( "SQLGetC&onnectOp&tion...", this, SLOT(sqlgetconnectoption()) );
    attr->insertSeparator();
    attr->insertItem( "SQLSet&EnvAttr...", this, SLOT(sqlsetenvattr()) );
    attr->insertItem( "SQLGetE&nvAttr...", this, SLOT(sqlgetenvattr()) );
    attr->insertSeparator();
    id = attr->insertItem( "Set &Cursor Attributes...", this, SLOT(setcursoratributes()) );
	attr->setItemEnabled( id, FALSE );

    QPopupMenu* results = new QPopupMenu( this );
    id = results->insertItem( "SQL&BindCol...", this, SLOT(sqlbindcol()) );
	results->setItemEnabled( id, FALSE );
    results->insertItem( "SQLBul&kOperations...", this, SLOT(sqlbulkoperations()) );
    results->insertItem( "S&QLColAttributes...", this, SLOT(sqlcolattributes()) );
    results->insertItem( "SQLColAttribute...", this, SLOT(sqlcolattribute()) );
    results->insertItem( "SQL&DescribeCol...", this, SLOT(sqldescribecol()) );
    results->insertItem( "SQLE&xtendedFetch...", this, SLOT(sqlextendedfetch()) );
    results->insertItem( "SQL&Fetch...", this, SLOT(sqlfetch()) );
    results->insertItem( "SQLFetc&hScroll...", this, SLOT(sqlfetchscroll()) );
    results->insertItem( "SQL&GetData...", this, SLOT(sqlgetdata()) );
    results->insertItem( "SQL&MoreResults...", this, SLOT(sqlmoreresults()) );
    results->insertItem( "SQL&NumResultsCols...", this, SLOT(sqlnumresultscols()) );
    results->insertItem( "SQL&RowCount...", this, SLOT(sqlrowcount()) );
    results->insertItem( "SQL&SetPos...", this, SLOT(sqlsetpos()) );
    results->insertItem( "SQLS&etScrollOptions...", this, SLOT(sqlsetscrolloptions()) );

	results->insertSeparator();
    id = results->insertItem( "B&ind Col All", this, SLOT(bindcolall()) );
	results->setItemEnabled( id, FALSE );
    id = results->insertItem( "Describe C&ol All", this, SLOT(describecolall()) );
	results->setItemEnabled( id, FALSE );
    id = results->insertItem( "Fetch &All", this, SLOT(fetchall()) );
	results->setItemEnabled( id, FALSE );
    results->insertItem( "Get Data A&ll", this, SLOT(getdataall()) );
    id = results->insertItem( "Sho&w Bound Cols", this, SLOT(showboundcols()) );
	results->setItemEnabled( id, FALSE );
    id = results->insertItem( "Display Rowset", this, SLOT(displayrowset()) );
	results->setItemEnabled( id, FALSE );

    QPopupMenu* catalog = new QPopupMenu( this );
    catalog->insertItem( "SQL&Columns...", this, SLOT(sqlcolumns()) );
    catalog->insertItem( "SQL&ColumnPrivileges...", this, SLOT(sqlcolumnprivileges()) );
    catalog->insertItem( "SQL&GetTypeInfo...", this, SLOT(sqlgettypeinfo()) );
    catalog->insertItem( "SQL&ForeignKeys...", this, SLOT(sqlforeignkeys()) );
    catalog->insertItem( "SQL&PrimaryKeys...", this, SLOT(sqlprimarykeys()) );
    catalog->insertItem( "SQLP&rocedures...", this, SLOT(sqlprocedures()) );
    catalog->insertItem( "SQLProc&edureColumns...", this, SLOT(sqlprocedurecolumns()) );
    catalog->insertItem( "SQLSpecia&lColumns...", this, SLOT(sqlspecialcolumns()) );
    catalog->insertItem( "SQL&Statistics...", this, SLOT(sqlstatistics()) );
    catalog->insertItem( "SQL&Tables...", this, SLOT(sqltables()) );
    catalog->insertItem( "SQLT&ablePrivileges...", this, SLOT(sqltableprivileges()) );

    QPopupMenu* datasources = new QPopupMenu( this );
    datasources->insertItem( "SQL&ManageDataSources...", this, SLOT(sqlmanagedatasources()) );
    datasources->insertItem( "SQL&RemoveDefaultDataSource...", this, SLOT(sqlremovedefaultdatasource()) );
    datasources->insertItem( "SQL&ConfigDataSource...", this, SLOT(sqlconfigdatasource()) );
    datasources->insertItem( "SQ&LCreatDataSource...", this, SLOT(sqlcreatedatasource()) );
    datasources->insertItem( "SQL&ValidDSN...", this, SLOT(sqlvaliddsn()) );
    datasources->insertItem( "SQLR&emoveDSNFromIni...", this, SLOT(sqlremovedsnfromini()) );
    datasources->insertItem( "SQLWriteDSNTo&Ini...", this, SLOT(sqlwritedsntoini()) );

    QPopupMenu* drivers = new QPopupMenu( this );
    id = drivers->insertItem( "SQLRemo&veDrivers...", this, SLOT(sqlremovedrivers()) );
	drivers->setItemEnabled( id, FALSE );
    id = drivers->insertItem( "S&QLConfigDrivers...", this, SLOT(sqlconfigdrivers()) );
	drivers->setItemEnabled( id, FALSE );
    id = drivers->insertItem( "SQLI&nstallDriver...", this, SLOT(sqlinstalldriver()) );
	drivers->setItemEnabled( id, FALSE );
    id = drivers->insertItem( "SQLI&nstallDriverEx...", this, SLOT(sqlinstalldriverex()) );
	drivers->setItemEnabled( id, FALSE );
    id = drivers->insertItem( "SQLGetInstalledDrivers...", this, SLOT(sqlgetinstalleddrivers()) );
	drivers->setItemEnabled( id, FALSE );

    QPopupMenu* drivermanager = new QPopupMenu( this );
    id = drivermanager->insertItem( "SQL&RemoveDriverManager...", this, SLOT(sqlremovedrivermanager()) );
	drivermanager->setItemEnabled( id, FALSE );
    id = drivermanager->insertItem( "SQL&InstallDriverManager...", this, SLOT(sqlinstalldrivermanager()) );
	drivermanager->setItemEnabled( id, FALSE );

    QPopupMenu* filedsn = new QPopupMenu( this );
    id = filedsn->insertItem( "SQL&ReadFileDSN...", this, SLOT(sqlreadfiledsn()) );
	filedsn->setItemEnabled( id, FALSE );
    id = filedsn->insertItem( "SQL&WriteFileDSN...", this, SLOT(sqlwritefiledsn()) );
	filedsn->setItemEnabled( id, FALSE );

    QPopupMenu* profilestrings = new QPopupMenu( this );
    id = profilestrings->insertItem( "SQL&WritePrivateProfileString...", 
		this, SLOT(sqlwriteprivateprofilestring()) );
	profilestrings->setItemEnabled( id, FALSE );
    id = profilestrings->insertItem( "SQL&GetPrivateProfileString...", 
		this, SLOT(sqlgetprivateprofilestring()) );
	profilestrings->setItemEnabled( id, FALSE );

    QPopupMenu* translator = new QPopupMenu( this );
    id = translator->insertItem( "SQL&InstallTranslator...", 
		this, SLOT(sqlinstalltranslator()) );
	translator->setItemEnabled( id, FALSE );
    id = translator->insertItem( "SQLI&nstallTranslatorEx...", 
		this, SLOT(sqlinstalltranslatorex()) );
	translator->setItemEnabled( id, FALSE );
    id = translator->insertItem( "SQL&RemoveTranslator...", 
		this, SLOT(sqlremovetranslator()) );
	translator->setItemEnabled( id, FALSE );
    id = translator->insertItem( "SQL&GetTranslator...", 
		this, SLOT(sqlgettranslator()) );
	translator->setItemEnabled( id, FALSE );

    QPopupMenu* configmode = new QPopupMenu( this );
    id = configmode->insertItem( "SQL&SetConfigMode...", 
		this, SLOT(sqlsetconfigmode()) );
	configmode->setItemEnabled( id, FALSE );
    id = configmode->insertItem( "SQL&GetConfigMode...", 
		this, SLOT(sqlgetconfigmode()) );
	configmode->setItemEnabled( id, FALSE );

    QPopupMenu* installer = new QPopupMenu( this );
    id = installer->insertItem( "&Data Sources...", datasources );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "Dri&vers...", drivers );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "Driver&Manager...", drivermanager );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "&File DSN...", filedsn );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "&Profile Strings...", profilestrings );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "&Translator...", translator );
	installer->setItemEnabled( id, FALSE );
    id = installer->insertItem( "C&onfig Mode...", configmode );
	installer->setItemEnabled( id, FALSE );

    QPopupMenu* tools = new QPopupMenu( this );
    id = tools->insertItem( "&Options..", this, SLOT(options()) );
	tools->setItemEnabled( id, FALSE );
    id = tools->insertItem( "T&race..", this, SLOT(trace()) );
	tools->setItemEnabled( id, FALSE );
    tools->insertSeparator();
    tools->insertItem( "Manage Test &Sources...", this, SLOT(manage_test()) );
    tools->insertItem( "&Manage Auto Tests...", this, SLOT(manage_auto_test()) );
    tools->insertItem( "&Manage Test &Groups...", this, SLOT(manage_test_groups()) );
    tools->insertItem( "Run Auto &Tests...", this, SLOT(run_auto_tests()) );

    QPopupMenu *help = new QPopupMenu( this );
    id = help->insertItem( "ODBC Test &Help", this, SLOT(testhelp()) );
	help->setItemEnabled( id, FALSE );
    id = help->insertItem( "API A&PI Help", this, SLOT(apihelp()) );
	help->setItemEnabled( id, FALSE );
    help->insertItem( "About ODBC Test...", this, SLOT(about()) );

    menu = new QMenuBar( this );

    menu->insertItem( "&File", file );
    menu->insertItem( "Dia&g", diag );
    menu->insertItem( "E&nv", env );
    menu->insertItem( "&Conn", conn );
    menu->insertItem( "&Desc", desc );
    menu->insertItem( "&Stmt", stmt );
    menu->insertItem( "&Attr", attr );
    menu->insertItem( "&Results", results );
    menu->insertItem( "Cata&log", catalog );
    menu->insertItem( "&Installer", installer );
    menu->insertItem( "&Tools", tools );
    menu->insertSeparator();
    menu->insertItem( "&Help", help );
    menu->setSeparator( QMenuBar::InWindowsStyle );
*/
	createActions();
	createMenus();

    this->setGeometry( 0, 0, 500, 250 );

	split = new QSplitter( Qt::Vertical, this );
	split -> setOpaqueResize( FALSE );
	setCentralWidget( split );
    in_win 	= new QTextEdit( split );
    out_win = new QTextEdit( split );
	out_win -> setReadOnly( TRUE );
	out_win -> setMaxLines( 1000 );
}

OdbcTest::~OdbcTest()
{
	// delete all handles
	while ( !listHandle.isEmpty() )
		delete listHandle.takeFirst();
}

const char * OdbcTest::return_as_text( int ret )
{
	switch( ret )
	{
		case SQL_SUCCESS:
			return "SQL_SUCCESS";

		case SQL_SUCCESS_WITH_INFO:
			return "SQL_SUCCESS_WITH_INFO";

		case SQL_ERROR:
			return "SQL_ERROR";

		case SQL_INVALID_HANDLE:
			return "SQL_INVALID_HANDLE";

		case SQL_STILL_EXECUTING:
			return "SQL_STILL_EXECUTING";

		case SQL_NEED_DATA:
			return "SQL_NEED_DATA";

		case SQL_NO_DATA:
			return "SQL_NO_DATA";

		default:
			return "Unknown Return ?";
	}
}

void OdbcTest::fill_list_box( attr_value *attr, QComboBox *lst )
{
	char txt[ 128 ];

	for ( int i = 0; attr[ i ].text; i ++ )
	{
		if ( strlen( attr[ i ].text ) > 0 )
		{
			if ( attr[ i ].version )
			{
				sprintf( txt, "%s=%d (%s)", attr[ i ].text, 
					attr[ i ].value, attr[ i ].version );
			}
			else
			{
				sprintf( txt, "%s=%d", attr[ i ].text, 
					attr[ i ].value );
			}
		}
		else
		{
			sprintf( txt, "%d", attr[ i ].value );
		}
		lst -> insertItem( i, txt );
	}
}

void OdbcTest::fill_list_box( attr_options *attr, QComboBox *lst )
{
	char txt[ 128 ];

	for ( int i = 0; attr[ i ].text; i ++ )
	{
		if ( strlen( attr[ i ].text ) > 0 )
		{
			if ( attr[ i ].version )
			{
				sprintf( txt, "%s=%d (%s)", attr[ i ].text, 
					attr[ i ].attr, attr[ i ].version );
			}
			else
			{
				sprintf( txt, "%s=%d", attr[ i ].text, 
					attr[ i ].attr );
			}
		}
		else
		{
			sprintf( txt, "%d", attr[ i ].attr );
		}
		lst -> insertItem( i, txt );
	}
}

SQLHANDLE OdbcTest::get_handle( int type )
{
	QListIterator<OdbcHandle*> it( listHandle );

	while ( it.hasNext() )
	{
		OdbcHandle *hand = it.next();
		if ( hand && hand->getType() == type )
		{
			return hand->getHandle();
		}
	}

	return SQL_NULL_HANDLE;
}

OdbcHandle * OdbcTest::fill_handle_list( int type, QComboBox *lst )
{
	QListIterator<OdbcHandle*> 	it( listHandle );
	OdbcHandle *				match 	= NULL;
	int 					i 		= 0;
	char 					txt[128];

	while ( it.hasNext() )
	{
		OdbcHandle *hand = it.next();
		if ( !hand  )
			break;

		hand->toStr( txt );
		if ( type < 0 )
		{
			lst->insertItem( i++, txt );
			match = hand;
		}
		else if ( hand->getType() == type )
		{
			lst->insertItem( i++, txt );
			match = hand;
		}
	}

	lst->insertItem( i, "SQL_NULL_HANDLE" );

	return match;
}

OdbcHandle *OdbcTest::extract_handle_list( int type, QComboBox *lst )
{
	QListIterator<OdbcHandle*> 	it( listHandle );
	int 					index = lst -> currentIndex(); 
	int 					i = 0;
	OdbcHandle *				hand = NULL;

	while ( it.hasNext() )
	{
		hand = it.next();
		if ( !hand  )
			break;
		if ( type < 0 || hand->getType() == type )
		{
			if ( i == index )
			{
				break;
			}
			i++;
		}
	}

	return hand;
}

void OdbcTest::dumpError( int type, SQLHANDLE hnd )
{
	SQLRETURN ret;
	SQLINTEGER count, i;
	char handle[ 30 ];

	switch( type )
	{
		case SQL_HANDLE_ENV:
			sprintf( handle, "henv %p", hnd );
			break;

		case SQL_HANDLE_DBC:
			sprintf( handle, "hdbc %p", hnd );
			break;

		case SQL_HANDLE_STMT:
			sprintf( handle, "hstmt %p", hnd );
			break;

		case SQL_HANDLE_DESC:
			sprintf( handle, "hdesc %p", hnd );
			break;

		default:
			strcpy( handle, "unknown handle" );
			break;
	}

	ret = SQLGetDiagField( type, hnd, 0, SQL_DIAG_NUMBER,
		&count, 0, NULL );

	if ( !SQL_SUCCEEDED( ret ))
	{
		out_win->insertLineLimited( "SQLGetDiagField( SQL_DIAG_NUMBER ) failed" );
		return;
	}

	for ( i = 1; i <= count; i ++ )
	{
		SQLCHAR sqlstate[ 6 ];
		SQLINTEGER native;
		SQLCHAR message_text[ SQL_MAX_MESSAGE_LENGTH ];
		char txt[ SQL_MAX_MESSAGE_LENGTH + 50 ];

		ret = SQLGetDiagRec( type, hnd, i, sqlstate,
			&native, message_text, sizeof( message_text ),
			NULL );

		if ( !SQL_SUCCEEDED( ret ))
	    {
			out_win->insertLineLimited( "SQLGetDiagRec() failed" );
			return;
		}

		sprintf( txt, "Diag(%s):%s:%d:%s",
			handle, sqlstate, native, message_text );

		out_win->insertLineLimited( txt );
	}
}

void OdbcTest::apihelp()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::testhelp()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::about()
{
    QMessageBox::about( this, "ODBC Test",
			"This program is part of the unixODBC SDK.\n"
			"It can be used to test the ODBC API.\n"
			"Based on the ODBC test program supplied by Microsoft.\n"
			"Written by Nick Gorham." );
}

void OdbcTest::resizeEvent( QResizeEvent * )
{
    // label->setGeometry( 20, rect().center().y()-20, width()-40, 40 );
}

const char *OdbcTest::int_type_as_string( SQLINTERVAL itype )
{
	switch ( itype )
	{
   		case SQL_IS_YEAR:
			return "SQL_IS_YEAR";

    	case SQL_IS_MONTH:
			return "SQL_IS_MONTH";

    	case SQL_IS_DAY:
			return "SQL_IS_DAY";

    	case SQL_IS_HOUR:
			return "SQL_IS_HOUR";

    	case SQL_IS_MINUTE:
			return "SQL_IS_MINUTE";

    	case SQL_IS_SECOND:
			return "SQL_IS_SECOND";

    	case SQL_IS_YEAR_TO_MONTH:
			return "SQL_IS_YEAR_TO_MONTH";

    	case SQL_IS_DAY_TO_HOUR :
			return "SQL_IS_DAY_TO_HOUR";

    	case SQL_IS_DAY_TO_MINUTE:
			return "SQL_IS_DAY_TO_MINUTE";

    	case SQL_IS_DAY_TO_SECOND:
			return "SQL_IS_DAY_TO_SECOND";

    	case SQL_IS_HOUR_TO_MINUTE:
			return "SQL_IS_HOUR_TO_MINUTE";

    	case SQL_IS_HOUR_TO_SECOND:
			return "SQL_IS_HOUR_TO_SECOND";

    	case SQL_IS_MINUTE_TO_SECOND:
			return "SQL_IS_MINUTE_TO_SECOND";
	}

    return "Unknown Type";
}	

void OdbcTest::createActions()
{
	pactionExit							    = new QAction( tr("Exit"), this );    
	pactionGetDiagRec                       = new QAction( tr("GetDiagRec"), this );    
	pactionGetDiagField                     = new QAction( tr("GetDiagField"), this );    
	pactionError                            = new QAction( tr("Error"), this );    
	pactionErrorsAll                        = new QAction( tr("ErrorsAll"), this );    
	pactionAllocEnv                         = new QAction( tr("AllocEnv"), this );    
	pactionAllocHandle                      = new QAction( tr("AllocHandle"), this );    
	pactionDataSources                      = new QAction( tr("DataSources"), this );    
	pactionDrivers                          = new QAction( tr("Drivers"), this );    
	pactionFreeEnv                          = new QAction( tr("FreeEnv"), this );    
	pactionFreeHandle                       = new QAction( tr("FreeHandle"), this );    
	pactionEndTran                          = new QAction( tr("EndTran"), this );    
	pactionTransact                         = new QAction( tr("Transact"), this );    
	pactionDataSourcesAll                   = new QAction( tr("DataSourcesAll"), this );    
	pactionDriversAll                       = new QAction( tr("DriversAll"), this );    
	pactionAllocConnect                     = new QAction( tr("AllocConnect"), this );    
	pactionBrowseConnect                    = new QAction( tr("BrowseConnect"), this );    
	pactionConnect                          = new QAction( tr("Connect"), this );    
	pactionDriverConnect                    = new QAction( tr("DriverConnect"), this );    
	pactionDisconnect                       = new QAction( tr("Disconnect"), this );    
	pactionFreeConnect                      = new QAction( tr("FreeConnect"), this );    
	pactionGetFunctions                     = new QAction( tr("GetFunctions"), this );    
	pactionGetInfo                          = new QAction( tr("GetInfo"), this );    
	pactionNativeSQL                        = new QAction( tr("NativeSQL"), this );    
	pactionFullConnect                      = new QAction( tr("FullConnect"), this );    
	pactionFullDisconnect                   = new QAction( tr("FullDisconnect"), this );    
	pactionGetInfoAll                       = new QAction( tr("GetInfoAll"), this );    
	pactionGetFunctionsAll                  = new QAction( tr("GetFunctionsAll"), this );    
	pactionCopyDesc                         = new QAction( tr("CopyDesc"), this );    
	pactionGetDescField                     = new QAction( tr("GetDescField"), this );    
	pactionGetDescRec                       = new QAction( tr("GetDescRec"), this );    
	pactionSetDescField                     = new QAction( tr("SetDescField"), this );    
	pactionSetDescRec                       = new QAction( tr("SetDescRec"), this );    
	pactionGetDescAll                       = new QAction( tr("GetDescAll"), this );    
	pactionAllocStmt                        = new QAction( tr("AllocStmt"), this );    
	pactionBindParam                        = new QAction( tr("BindParam,"), this );    
	pactionBindParameter                    = new QAction( tr("BindParameter"), this );    
	pactionCancel                           = new QAction( tr("Cancel"), this );    
	pactionCloseCursor                      = new QAction( tr("CloseCursor"), this );    
	pactionDescribeParam                    = new QAction( tr("DescribeParam"), this );    
	pactionExecute                          = new QAction( tr("Execute"), this );    
	pactionExecDirect                       = new QAction( tr("ExecDirect"), this );    
	pactionFreeStmt                         = new QAction( tr("FreeStmt"), this );    
	pactionGetCursorName                    = new QAction( tr("GetCursorName"), this );    
	pactionNumParams                        = new QAction( tr("NumParams"), this );    
	pactionParamData                        = new QAction( tr("ParamData"), this );    
	pactionParamOptions                     = new QAction( tr("ParamOptions"), this );    
	pactionPrepare                          = new QAction( tr("Prepare"), this );    
	pactionPutData                          = new QAction( tr("PutData"), this );    
	pactionSetCursorName                    = new QAction( tr("SetCursorName"), this );    
	pactionFillParam                        = new QAction( tr("FillParam"), this );    
	pactionShowParam                        = new QAction( tr("ShowParam"), this );    
	pactionShowCursorSettings               = new QAction( tr("ShowCursorSettings"), this );    
	pactionSetStmtAttr                      = new QAction( tr("SetStmtAttr"), this );    
	pactionGetStmtAttr                      = new QAction( tr("GetStmtAttr"), this );    
	pactionSetStmtOption                    = new QAction( tr("SetStmtOption"), this );    
	pactionGetStmtOption                    = new QAction( tr("GetStmtOption"), this );    
	pactionSetConnectAttr                   = new QAction( tr("SetConnectAttr"), this );    
	pactionGetConnectAttr                   = new QAction( tr("GetConnectAttr"), this );    
	pactionSetConnectOption                 = new QAction( tr("SetConnectOption"), this );    
	pactionGetConnectOption                 = new QAction( tr("GetConnectOption"), this );    
	pactionSetEnvAttr                       = new QAction( tr("SetEnvAttr"), this );    
	pactionGetEnvAttr                       = new QAction( tr("GetEnvAttr"), this );    
	pactionSetCursorAttributes              = new QAction( tr("SetCursorAttributes"), this );    
	pactionBindCol                          = new QAction( tr("BindCol"), this );    
	pactionBulkOperations                   = new QAction( tr("BulkOperations"), this );    
	pactionColAttributes                    = new QAction( tr("ColAttributes"), this );    
	pactionColAttribute                     = new QAction( tr("ColAttribute"), this );    
	pactionDescribeCol                      = new QAction( tr("DescribeCol"), this );    
	pactionExtendedFetch                    = new QAction( tr("ExtendedFetch"), this );    
	pactionFetch                            = new QAction( tr("Fetch"), this );    
	pactionFetchScroll                      = new QAction( tr("FetchScroll"), this );    
	pactionGetData                          = new QAction( tr("GetData"), this );    
	pactionMoreResults                      = new QAction( tr("MoreResults"), this );    
	pactionNumResultCols                    = new QAction( tr("NumResultCols"), this );    
	pactionRowCount                         = new QAction( tr("RowCount"), this );    
	pactionSetPos                           = new QAction( tr("SetPos"), this );    
	pactionSetScrollOptions                 = new QAction( tr("SetScrollOptions"), this );    
	pactionBindColAll                       = new QAction( tr("BindColAll"), this );    
	pactionDescribeColAll                   = new QAction( tr("DescribeColAll"), this );    
	pactionFetchAll                         = new QAction( tr("FetchAll"), this );    
	pactionGetDataAll                       = new QAction( tr("GetDataAll"), this );    
	pactionShowBoundCols                    = new QAction( tr("ShowBoundCols"), this );    
	pactionDisplayRowset                    = new QAction( tr("DisplayRowset"), this );    
	pactionColumns                          = new QAction( tr("Columns"), this );    
	pactionColumnPrivileges                 = new QAction( tr("ColumnPrivileges"), this );    
	pactionGetTypeInfo                      = new QAction( tr("GetTypeInfo"), this );    
	pactionForeignKeys                      = new QAction( tr("ForeignKeys"), this );    
	pactionPrimaryKeys                      = new QAction( tr("PrimaryKeys"), this );    
	pactionProcedures                       = new QAction( tr("Procedures"), this );    
	pactionProcedureColumns                 = new QAction( tr("ProcedureColumns"), this );    
	pactionSpecialColumns                   = new QAction( tr("SpecialColumns"), this );    
	pactionStatistics                       = new QAction( tr("Statistics"), this );    
	pactionTables                           = new QAction( tr("Tables"), this );    
	pactionTablePrivileges                  = new QAction( tr("TablePrivileges"), this );    
	pactionManageDataSources                = new QAction( tr("ManageDataSources"), this );    
	pactionRemoveDefaultDataSource          = new QAction( tr("RemoveDefaultDataSource"), this );    
	pactionConfigDataSource                 = new QAction( tr("ConfigDataSource"), this );    
	pactionCreateDataSource                 = new QAction( tr("CreateDataSource"), this );    
	pactionValidDSN                         = new QAction( tr("ValidDSN"), this );    
	pactionRemoveDSNFromIni                 = new QAction( tr("RemoveDSNFromIni"), this );    
	pactionWriteDSNToIni                    = new QAction( tr("WriteDSNToIni"), this );    
	pactionRemoveDrivers                    = new QAction( tr("RemoveDrivers"), this );    
	pactionConfigDrivers                    = new QAction( tr("ConfigDrivers"), this );    
	pactionInstallDriver                    = new QAction( tr("InstallDriver"), this );    
	pactionInstallDriverEx                  = new QAction( tr("InstallDriverEx"), this );    
	pactionGetInstalledDrivers              = new QAction( tr("GetInstalledDrivers"), this );    
	pactionRemoveDriverManager              = new QAction( tr("RemoveDriverManager"), this );    
	pactionInstallDriverManager             = new QAction( tr("InstallDriverManager"), this );    
	pactionReadFileDSN                      = new QAction( tr("ReadFileDSN"), this );    
	pactionWriteFileDSN                     = new QAction( tr("WriteFileDSN"), this );    
	pactionWritePrivateProfileString	    = new QAction( tr("WritePrivateProfileString"), this );    
	pactionGetPrivateProfileString          = new QAction( tr("GetPrivateProfileString"), this );    
	pactionInstallTranslator                = new QAction( tr("InstallTranslator"), this );    
	pactionInstallTranslatorEx              = new QAction( tr("InstallTranslatorEx"), this );    
	pactionRemoveTranslator                 = new QAction( tr("RemoveTranslator"), this );    
	pactionGetTranslator                    = new QAction( tr("GetTranslator"), this );    
	pactionSetConfigMode                    = new QAction( tr("SetConfigMode"), this );    
	pactionGetConfigMode                    = new QAction( tr("GetConfigMode"), this );    
	pactionOptions                          = new QAction( tr("Options"), this );    
	pactionTrace                            = new QAction( tr("Trace"), this );    
	pactionManageTestSources                = new QAction( tr("ManageTestSources"), this );    
	pactionManageAutoTests                  = new QAction( tr("ManageAutoTests"), this );    
	pactionManageTestGroups                 = new QAction( tr("ManageTestGroups"), this );    
	pactionRunAutoTests                     = new QAction( tr("RunAutoTests"), this );    
	pactionHelpTest                         = new QAction( tr("HelpTest"), this );    
	pactionHelpApi                          = new QAction( tr("HelpApi"), this );    
	pactionHelpAbout                        = new QAction( tr("HelpAbout"), this );    

	connect( pactionExit                     , SIGNAL(triggered()), this, SLOT(slotExit                     ()) );
	connect( pactionGetDiagRec               , SIGNAL(triggered()), this, SLOT(slotGetDiagRec               ()) );
	connect( pactionGetDiagField             , SIGNAL(triggered()), this, SLOT(slotGetDiagField             ()) );
	connect( pactionError                    , SIGNAL(triggered()), this, SLOT(slotError                    ()) );
	connect( pactionErrorsAll                , SIGNAL(triggered()), this, SLOT(slotErrorsAll                ()) );
	connect( pactionAllocEnv                 , SIGNAL(triggered()), this, SLOT(slotAllocEnv                 ()) );
	connect( pactionAllocHandle              , SIGNAL(triggered()), this, SLOT(slotAllocHandle              ()) );
	connect( pactionDataSources              , SIGNAL(triggered()), this, SLOT(slotDataSources              ()) );
	connect( pactionDrivers                  , SIGNAL(triggered()), this, SLOT(slotDrivers                  ()) );
	connect( pactionFreeEnv                  , SIGNAL(triggered()), this, SLOT(slotFreeEnv                  ()) );
	connect( pactionFreeHandle               , SIGNAL(triggered()), this, SLOT(slotFreeHandle               ()) );
	connect( pactionEndTran                  , SIGNAL(triggered()), this, SLOT(slotEndTran                  ()) );
	connect( pactionTransact                 , SIGNAL(triggered()), this, SLOT(slotTransact                 ()) );
	connect( pactionDataSourcesAll           , SIGNAL(triggered()), this, SLOT(slotDataSourcesAll           ()) );
	connect( pactionDriversAll               , SIGNAL(triggered()), this, SLOT(slotDriversAll               ()) );
	connect( pactionAllocConnect             , SIGNAL(triggered()), this, SLOT(slotAllocConnect             ()) );
	connect( pactionBrowseConnect            , SIGNAL(triggered()), this, SLOT(slotBrowseConnect            ()) );
	connect( pactionConnect                  , SIGNAL(triggered()), this, SLOT(slotConnect                  ()) );
	connect( pactionDriverConnect            , SIGNAL(triggered()), this, SLOT(slotDriverConnect            ()) );
	connect( pactionDisconnect               , SIGNAL(triggered()), this, SLOT(slotDisconnect               ()) );
	connect( pactionFreeConnect              , SIGNAL(triggered()), this, SLOT(slotFreeConnect              ()) );
	connect( pactionGetFunctions             , SIGNAL(triggered()), this, SLOT(slotGetFunctions             ()) );
	connect( pactionGetInfo                  , SIGNAL(triggered()), this, SLOT(slotGetInfo                  ()) );
	connect( pactionNativeSQL                , SIGNAL(triggered()), this, SLOT(slotNativeSQL                ()) );
	connect( pactionFullConnect              , SIGNAL(triggered()), this, SLOT(slotFullConnect              ()) );
	connect( pactionFullDisconnect           , SIGNAL(triggered()), this, SLOT(slotFullDisconnect           ()) );
	connect( pactionGetInfoAll               , SIGNAL(triggered()), this, SLOT(slotGetInfoAll               ()) );
	connect( pactionGetFunctionsAll          , SIGNAL(triggered()), this, SLOT(slotGetFunctionsAll          ()) );
	connect( pactionCopyDesc                 , SIGNAL(triggered()), this, SLOT(slotCopyDesc                 ()) );
	connect( pactionGetDescField             , SIGNAL(triggered()), this, SLOT(slotGetDescField             ()) );
	connect( pactionGetDescRec               , SIGNAL(triggered()), this, SLOT(slotGetDescRec               ()) );
	connect( pactionSetDescField             , SIGNAL(triggered()), this, SLOT(slotSetDescField             ()) );
	connect( pactionSetDescRec               , SIGNAL(triggered()), this, SLOT(slotSetDescRec               ()) );
	connect( pactionGetDescAll               , SIGNAL(triggered()), this, SLOT(slotGetDescAll               ()) );
	connect( pactionAllocStmt                , SIGNAL(triggered()), this, SLOT(slotAllocStmt                ()) );
	connect( pactionBindParam                , SIGNAL(triggered()), this, SLOT(slotBindParam                ()) );
	connect( pactionBindParameter            , SIGNAL(triggered()), this, SLOT(slotBindParameter            ()) );
	connect( pactionCancel                   , SIGNAL(triggered()), this, SLOT(slotCancel                   ()) );
	connect( pactionCloseCursor              , SIGNAL(triggered()), this, SLOT(slotCloseCursor              ()) );
	connect( pactionDescribeParam            , SIGNAL(triggered()), this, SLOT(slotDescribeParam            ()) );
	connect( pactionExecute                  , SIGNAL(triggered()), this, SLOT(slotExecute                  ()) );
	connect( pactionExecDirect               , SIGNAL(triggered()), this, SLOT(slotExecDirect               ()) );
	connect( pactionFreeStmt                 , SIGNAL(triggered()), this, SLOT(slotFreeStmt                 ()) );
	connect( pactionGetCursorName            , SIGNAL(triggered()), this, SLOT(slotGetCursorName            ()) );
	connect( pactionNumParams                , SIGNAL(triggered()), this, SLOT(slotNumParams                ()) );
	connect( pactionParamData                , SIGNAL(triggered()), this, SLOT(slotParamData                ()) );
	connect( pactionParamOptions             , SIGNAL(triggered()), this, SLOT(slotParamOptions             ()) );
	connect( pactionPrepare                  , SIGNAL(triggered()), this, SLOT(slotPrepare                  ()) );
	connect( pactionPutData                  , SIGNAL(triggered()), this, SLOT(slotPutData                  ()) );
	connect( pactionSetCursorName            , SIGNAL(triggered()), this, SLOT(slotSetCursorName            ()) );
	connect( pactionFillParam                , SIGNAL(triggered()), this, SLOT(slotFillParam                ()) );
	connect( pactionShowParam                , SIGNAL(triggered()), this, SLOT(slotShowParam                ()) );
	connect( pactionShowCursorSettings       , SIGNAL(triggered()), this, SLOT(slotShowCursorSettings       ()) );
	connect( pactionSetStmtAttr              , SIGNAL(triggered()), this, SLOT(slotSetStmtAttr              ()) );
	connect( pactionGetStmtAttr              , SIGNAL(triggered()), this, SLOT(slotGetStmtAttr              ()) );
	connect( pactionSetStmtOption            , SIGNAL(triggered()), this, SLOT(slotSetStmtOption            ()) );
	connect( pactionGetStmtOption            , SIGNAL(triggered()), this, SLOT(slotGetStmtOption            ()) );
	connect( pactionSetConnectAttr           , SIGNAL(triggered()), this, SLOT(slotSetConnectAttr           ()) );
	connect( pactionGetConnectAttr           , SIGNAL(triggered()), this, SLOT(slotGetConnectAttr           ()) );
	connect( pactionSetConnectOption         , SIGNAL(triggered()), this, SLOT(slotSetConnectOption         ()) );
	connect( pactionGetConnectOption         , SIGNAL(triggered()), this, SLOT(slotGetConnectOption         ()) );
	connect( pactionSetEnvAttr               , SIGNAL(triggered()), this, SLOT(slotSetEnvAttr               ()) );
	connect( pactionGetEnvAttr               , SIGNAL(triggered()), this, SLOT(slotGetEnvAttr               ()) );
	connect( pactionSetCursorAttributes      , SIGNAL(triggered()), this, SLOT(slotSetCursorAttributes      ()) );
	connect( pactionBindCol                  , SIGNAL(triggered()), this, SLOT(slotBindCol                  ()) );
	connect( pactionBulkOperations           , SIGNAL(triggered()), this, SLOT(slotBulkOperations           ()) );
	connect( pactionColAttributes            , SIGNAL(triggered()), this, SLOT(slotColAttributes            ()) );
	connect( pactionColAttribute             , SIGNAL(triggered()), this, SLOT(slotColAttribute             ()) );
	connect( pactionDescribeCol              , SIGNAL(triggered()), this, SLOT(slotDescribeCol              ()) );
	connect( pactionExtendedFetch            , SIGNAL(triggered()), this, SLOT(slotExtendedFetch            ()) );
	connect( pactionFetch                    , SIGNAL(triggered()), this, SLOT(slotFetch                    ()) );
	connect( pactionFetchScroll              , SIGNAL(triggered()), this, SLOT(slotFetchScroll              ()) );
	connect( pactionGetData                  , SIGNAL(triggered()), this, SLOT(slotGetData                  ()) );
	connect( pactionMoreResults              , SIGNAL(triggered()), this, SLOT(slotMoreResults              ()) );
	connect( pactionNumResultCols            , SIGNAL(triggered()), this, SLOT(slotNumResultCols            ()) );
	connect( pactionRowCount                 , SIGNAL(triggered()), this, SLOT(slotRowCount                 ()) );
	connect( pactionSetPos                   , SIGNAL(triggered()), this, SLOT(slotSetPos                   ()) );
	connect( pactionSetScrollOptions         , SIGNAL(triggered()), this, SLOT(slotSetScrollOptions         ()) );
	connect( pactionBindColAll               , SIGNAL(triggered()), this, SLOT(slotBindColAll               ()) );
	connect( pactionDescribeColAll           , SIGNAL(triggered()), this, SLOT(slotDescribeColAll           ()) );
	connect( pactionFetchAll                 , SIGNAL(triggered()), this, SLOT(slotFetchAll                 ()) );
	connect( pactionGetDataAll               , SIGNAL(triggered()), this, SLOT(slotGetDataAll               ()) );
	connect( pactionShowBoundCols            , SIGNAL(triggered()), this, SLOT(slotShowBoundCols            ()) );
	connect( pactionDisplayRowset            , SIGNAL(triggered()), this, SLOT(slotDisplayRowset            ()) );
	connect( pactionColumns                  , SIGNAL(triggered()), this, SLOT(slotColumns                  ()) );
	connect( pactionColumnPrivileges         , SIGNAL(triggered()), this, SLOT(slotColumnPrivileges         ()) );
	connect( pactionGetTypeInfo              , SIGNAL(triggered()), this, SLOT(slotGetTypeInfo              ()) );
	connect( pactionForeignKeys              , SIGNAL(triggered()), this, SLOT(slotForeignKeys              ()) );
	connect( pactionPrimaryKeys              , SIGNAL(triggered()), this, SLOT(slotPrimaryKeys              ()) );
	connect( pactionProcedures               , SIGNAL(triggered()), this, SLOT(slotProcedures               ()) );
	connect( pactionProcedureColumns         , SIGNAL(triggered()), this, SLOT(slotProcedureColumns         ()) );
	connect( pactionSpecialColumns           , SIGNAL(triggered()), this, SLOT(slotSpecialColumns           ()) );
	connect( pactionStatistics               , SIGNAL(triggered()), this, SLOT(slotStatistics               ()) );
	connect( pactionTables                   , SIGNAL(triggered()), this, SLOT(slotTables                   ()) );
	connect( pactionTablePrivileges          , SIGNAL(triggered()), this, SLOT(slotTablePrivileges          ()) );
	connect( pactionManageDataSources        , SIGNAL(triggered()), this, SLOT(slotManageDataSources        ()) );
	connect( pactionRemoveDefaultDataSource  , SIGNAL(triggered()), this, SLOT(slotRemoveDefaultDataSource  ()) );
	connect( pactionConfigDataSource         , SIGNAL(triggered()), this, SLOT(slotConfigDataSource         ()) );
	connect( pactionCreateDataSource         , SIGNAL(triggered()), this, SLOT(slotCreateDataSource         ()) );
	connect( pactionValidDSN                 , SIGNAL(triggered()), this, SLOT(slotValidDSN                 ()) );
	connect( pactionRemoveDSNFromIni         , SIGNAL(triggered()), this, SLOT(slotRemoveDSNFromIni         ()) );
	connect( pactionWriteDSNToIni            , SIGNAL(triggered()), this, SLOT(slotWriteDSNToIni            ()) );
	connect( pactionRemoveDrivers            , SIGNAL(triggered()), this, SLOT(slotRemoveDrivers            ()) );
	connect( pactionConfigDrivers            , SIGNAL(triggered()), this, SLOT(slotConfigDrivers            ()) );
	connect( pactionInstallDriver            , SIGNAL(triggered()), this, SLOT(slotInstallDriver            ()) );
	connect( pactionInstallDriverEx          , SIGNAL(triggered()), this, SLOT(slotInstallDriverEx          ()) );
	connect( pactionGetInstalledDrivers      , SIGNAL(triggered()), this, SLOT(slotGetInstalledDrivers      ()) );
	connect( pactionRemoveDriverManager      , SIGNAL(triggered()), this, SLOT(slotRemoveDriverManager      ()) );
	connect( pactionInstallDriverManager     , SIGNAL(triggered()), this, SLOT(slotInstallDriverManager     ()) );
	connect( pactionReadFileDSN              , SIGNAL(triggered()), this, SLOT(slotReadFileDSN              ()) );
	connect( pactionWriteFileDSN             , SIGNAL(triggered()), this, SLOT(slotWriteFileDSN             ()) );
	connect( pactionWritePrivateProfileString, SIGNAL(triggered()), this, SLOT(slotWritePrivateProfileString()) );
	connect( pactionGetPrivateProfileString  , SIGNAL(triggered()), this, SLOT(slotGetPrivateProfileString  ()) );
	connect( pactionInstallTranslator        , SIGNAL(triggered()), this, SLOT(slotInstallTranslator        ()) );
	connect( pactionInstallTranslatorEx      , SIGNAL(triggered()), this, SLOT(slotInstallTranslatorEx      ()) );
	connect( pactionRemoveTranslator         , SIGNAL(triggered()), this, SLOT(slotRemoveTranslator         ()) );
	connect( pactionGetTranslator            , SIGNAL(triggered()), this, SLOT(slotGetTranslator            ()) );
	connect( pactionSetConfigMode            , SIGNAL(triggered()), this, SLOT(slotSetConfigMode            ()) );
	connect( pactionGetConfigMode            , SIGNAL(triggered()), this, SLOT(slotGetConfigMode            ()) );
	connect( pactionOptions                  , SIGNAL(triggered()), this, SLOT(slotOptions                  ()) );
	connect( pactionTrace                    , SIGNAL(triggered()), this, SLOT(slotTrace                    ()) );
	connect( pactionManageTestSources        , SIGNAL(triggered()), this, SLOT(slotManageTestSources        ()) );
	connect( pactionManageAutoTests          , SIGNAL(triggered()), this, SLOT(slotManageAutoTests          ()) );
	connect( pactionManageTestGroups         , SIGNAL(triggered()), this, SLOT(slotManageTestGroups         ()) );
	connect( pactionRunAutoTests             , SIGNAL(triggered()), this, SLOT(slotRunAutoTests             ()) );
	connect( pactionHelpTest                 , SIGNAL(triggered()), this, SLOT(slotHelpTest                 ()) );
	connect( pactionHelpApi                  , SIGNAL(triggered()), this, SLOT(slotHelpApi                  ()) );
	connect( pactionHelpAbout                , SIGNAL(triggered()), this, SLOT(slotHelpAbout                ()) );

}

void OdbcTest::createMenus()
{
	// File...
	pmenuFile				= menuBar()->addMenu( tr("&File") );
	pmenuFile->addAction( pactionExit );
	
	// Diagnostic...	
	pmenuDiagnostic         = menuBar()->addMenu( tr("Dia&gnostic") );
	pmenuDiagnostic->addAction( pactionGetDiagRec 	);
	pmenuDiagnostic->addAction( pactionGetDiagField );
	pmenuDiagnostic->addAction( pactionError 		);
	pmenuDiagnostic->addSeparator();
	pmenuDiagnostic->addAction( pactionErrorsAll 	);

	// Environment...	
	pmenuEnvironment        = menuBar()->addMenu( tr("E&nvironment") );
	pmenuEnvironment->addAction( pactionAllocEnv       );
	pmenuEnvironment->addAction( pactionAllocHandle    );
	pmenuEnvironment->addAction( pactionDataSources    );
	pmenuEnvironment->addAction( pactionDrivers        );
	pmenuEnvironment->addAction( pactionFreeEnv        );
	pmenuEnvironment->addAction( pactionFreeHandle     );
	pmenuEnvironment->addAction( pactionEndTran        );
	pmenuEnvironment->addAction( pactionTransact       );
	pmenuEnvironment->addSeparator();
	pmenuEnvironment->addAction( pactionDataSourcesAll );
	pmenuEnvironment->addAction( pactionDriversAll     );

	// Connection...
	pmenuConnection         = menuBar()->addMenu( tr("&Connection") );
	pmenuConnection->addAction( pactionAllocConnect    );
	pmenuConnection->addAction( pactionBrowseConnect   );
	pmenuConnection->addAction( pactionConnect         );
	pmenuConnection->addAction( pactionDriverConnect   );
	pmenuConnection->addAction( pactionDisconnect      );
	pmenuConnection->addAction( pactionFreeConnect     );
	pmenuConnection->addAction( pactionGetFunctions    );
	pmenuConnection->addAction( pactionGetInfo         );
	pmenuConnection->addAction( pactionNativeSQL       );
	pmenuConnection->addSeparator();
	pmenuConnection->addAction( pactionFullConnect     );
	pmenuConnection->addAction( pactionFullDisconnect  );
	pmenuConnection->addAction( pactionGetInfoAll      );
	pmenuConnection->addAction( pactionGetFunctionsAll );

	// Descriptor...
	pmenuDescriptor         = menuBar()->addMenu( tr("&Descriptor") );
	pmenuDescriptor->addAction( pactionCopyDesc     );
	pmenuDescriptor->addAction( pactionGetDescField );
	pmenuDescriptor->addAction( pactionGetDescRec   );
	pmenuDescriptor->addAction( pactionSetDescField );
	pmenuDescriptor->addAction( pactionSetDescRec   );
	pmenuDescriptor->addSeparator();
	pmenuDescriptor->addAction( pactionGetDescAll   );

	// Statement...
	pmenuStatement          = menuBar()->addMenu( tr("&Statement") );
	pmenuStatement->addAction( pactionAllocStmt          );
	pmenuStatement->addAction( pactionBindParam          );
	pmenuStatement->addAction( pactionBindParameter      );
	pmenuStatement->addAction( pactionCancel             );
	pmenuStatement->addAction( pactionCloseCursor        );
	pmenuStatement->addAction( pactionDescribeParam      );
	pmenuStatement->addAction( pactionExecute            );
	pmenuStatement->addAction( pactionExecDirect         );
	pmenuStatement->addAction( pactionFreeStmt           );
	pmenuStatement->addAction( pactionGetCursorName      );
	pmenuStatement->addAction( pactionNumParams          );
	pmenuStatement->addAction( pactionParamData          );
	pmenuStatement->addAction( pactionParamOptions       );
	pmenuStatement->addAction( pactionPrepare            );
	pmenuStatement->addAction( pactionPutData            );
	pmenuStatement->addAction( pactionSetCursorName      );
	pmenuStatement->addSeparator();
	pmenuStatement->addAction( pactionFillParam          );
	pmenuStatement->addAction( pactionShowParam          );
	pmenuStatement->addAction( pactionShowCursorSettings );

	// Attributes...
	pmenuAttributes         = menuBar()->addMenu( tr("&Attributes") );
	pmenuAttributes->addAction( pactionSetStmtAttr         );
	pmenuAttributes->addAction( pactionGetStmtAttr         );
	pmenuAttributes->addAction( pactionSetStmtOption       );
	pmenuAttributes->addAction( pactionGetStmtOption       );
	pmenuAttributes->addSeparator();
	pmenuAttributes->addAction( pactionSetConnectAttr      );
	pmenuAttributes->addAction( pactionGetConnectAttr      );
	pmenuAttributes->addAction( pactionSetConnectOption    );
	pmenuAttributes->addAction( pactionGetConnectOption    );
	pmenuAttributes->addSeparator();
	pmenuAttributes->addAction( pactionSetEnvAttr          );
	pmenuAttributes->addAction( pactionGetEnvAttr          );
	pmenuAttributes->addAction( pactionSetCursorAttributes );

	// Results...
	pmenuResults            = menuBar()->addMenu( tr("&Results") );
	pmenuResults->addAction( pactionBindCol          );
	pmenuResults->addAction( pactionBulkOperations   );
	pmenuResults->addAction( pactionColAttributes    );
	pmenuResults->addAction( pactionColAttribute     );
	pmenuResults->addAction( pactionDescribeCol      );
	pmenuResults->addAction( pactionExtendedFetch    );
	pmenuResults->addAction( pactionFetch            );
	pmenuResults->addAction( pactionFetchScroll      );
	pmenuResults->addAction( pactionGetData          );
	pmenuResults->addAction( pactionMoreResults      );
	pmenuResults->addAction( pactionNumResultCols    );
	pmenuResults->addAction( pactionRowCount         );
	pmenuResults->addAction( pactionSetPos           );
	pmenuResults->addAction( pactionSetScrollOptions );
	pmenuResults->addSeparator();
	pmenuResults->addAction( pactionBindColAll       );
	pmenuResults->addAction( pactionDescribeColAll   );
	pmenuResults->addAction( pactionFetchAll         );
	pmenuResults->addAction( pactionGetDataAll       );
	pmenuResults->addAction( pactionShowBoundCols    );
	pmenuResults->addAction( pactionDisplayRowset    );

	// Catalog...
	pmenuCatalog            = menuBar()->addMenu( tr("Cata&log") );
	pmenuCatalog->addAction( pactionColumns          );
	pmenuCatalog->addAction( pactionColumnPrivileges );
	pmenuCatalog->addAction( pactionGetTypeInfo      );
	pmenuCatalog->addAction( pactionForeignKeys      );
	pmenuCatalog->addAction( pactionPrimaryKeys      );
	pmenuCatalog->addAction( pactionProcedures       );
	pmenuCatalog->addAction( pactionProcedureColumns );
	pmenuCatalog->addAction( pactionSpecialColumns   );
	pmenuCatalog->addAction( pactionStatistics       );
	pmenuCatalog->addAction( pactionTables           );
	pmenuCatalog->addAction( pactionTablePrivileges  );

	// Installer...
	pmenuInstaller          = menuBar()->addMenu( tr("&Installer") );

	// Installer -> Data Sources...
	pmenuDataSources        = pmenuInstaller->addMenu( tr("DataSources") );
	pmenuDataSources->addAction( pactionManageDataSources       );
	pmenuDataSources->addAction( pactionRemoveDefaultDataSource );
	pmenuDataSources->addAction( pactionConfigDataSource        );
	pmenuDataSources->addAction( pactionCreateDataSource        );
	pmenuDataSources->addAction( pactionValidDSN                );
	pmenuDataSources->addAction( pactionRemoveDSNFromIni        );
	pmenuDataSources->addAction( pactionWriteDSNToIni           );

	// Installer -> Drivers...
	pmenuDrivers            = pmenuInstaller->addMenu( tr("Drivers") );
	pmenuDrivers->addAction( pactionRemoveDrivers       );
	pmenuDrivers->addAction( pactionConfigDrivers       );
	pmenuDrivers->addAction( pactionInstallDriver       );
	pmenuDrivers->addAction( pactionInstallDriverEx     );
	pmenuDrivers->addAction( pactionGetInstalledDrivers );

	// Installer -> DriverManager...
	pmenuDriverManager      = pmenuInstaller->addMenu( tr("DriverManager") );
	pmenuDriverManager->addAction( pactionRemoveDriverManager  );
	pmenuDriverManager->addAction( pactionInstallDriverManager );

	// Installer -> DataSourceName...
	pmenuFileDataSourceName	= pmenuInstaller->addMenu( tr("FileDataSourceName") );
	pmenuFileDataSourceName->addAction( pactionReadFileDSN  );
	pmenuFileDataSourceName->addAction( pactionWriteFileDSN );

	// Installer -> ProfileStrings...
	pmenuProfileStrings     = pmenuInstaller->addMenu( tr("ProfileStrings") );
	pmenuProfileStrings->addAction( pactionWritePrivateProfileString  );
	pmenuProfileStrings->addAction( pactionGetPrivateProfileString );

	// Installer -> Translator...
	pmenuTranslator         = pmenuInstaller->addMenu( tr("Translator") );
	pmenuTranslator->addAction( pactionInstallTranslator   );
	pmenuTranslator->addAction( pactionInstallTranslatorEx );
	pmenuTranslator->addAction( pactionRemoveTranslator    );
	pmenuTranslator->addAction( pactionGetTranslator       );

	// Installer -> ConfigMode...
	pmenuConfigMode         = pmenuInstaller->addMenu( tr("ConfigMode") );
	pmenuConfigMode->addAction( pactionSetConfigMode );
	pmenuConfigMode->addAction( pactionGetConfigMode );

	// Tools...
	pmenuTools              = menuBar()->addMenu( tr("&Tools") );
	pmenuTools->addAction( pactionOptions           );
	pmenuTools->addAction( pactionTrace             );
	pmenuTools->addSeparator();
	pmenuTools->addAction( pactionManageTestSources );
	pmenuTools->addAction( pactionManageAutoTests   );
	pmenuTools->addAction( pactionManageTestGroups  );
	pmenuTools->addAction( pactionRunAutoTests      );

	// Help...
	pmenuHelp               = menuBar()->addMenu( tr("&Help") );
	pmenuHelp->addAction( pactionHelpTest );
	pmenuHelp->addAction( pactionHelpApi );
	pmenuHelp->addAction( pactionHelpAbout );
}



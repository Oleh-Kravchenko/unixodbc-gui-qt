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

#pragma once

#include "OdbcHandle.h"

/*!
 * \brief   Main application class for ODBCTestQ4. 
 *  
 *          This contains or invokes all of our functionality. This is
 *          instantiated in main().
 * 
 */
class OdbcTest : public QMainWindow
{
    Q_OBJECT
public:
    OdbcTest( QWidget *parent=0 );
    ~OdbcTest();

    QSettings * pSettings;      // an ini file usually called Gator.ini where we store configuration for our tests

	QSplitter *split;
	QTextEdit *in_win;
	QTextEdit *out_win;

    QList<OdbcHandle*> listHandle; // \todo free these up in a destructor
	const char *return_as_text( int ret );
	void fill_list_box( attr_value *attr, QComboBox *lst );
	void fill_list_box( attr_options *attr, QComboBox *lst );
    void fill_dsn_list( QComboBox *box );
    void set_dsn_list( QComboBox *box, const QString &stringItem );
	void dumpError( int type, SQLHANDLE );
	OdbcHandle *fill_handle_list( int type, QComboBox *lst );
	OdbcHandle *extract_handle_list( int type, QComboBox *lst );
	const char *int_type_as_string( SQLINTERVAL );
	SQLHANDLE get_handle( int type );
   
public slots:
    void about();
	void testhelp();
	void apihelp();
	void open();
	void saveas();
	void saveopt();
	void undo();
	void cut();
	void copy();
	void paste();
	void del();
	void clearow();
	void selectall();
	void wrap();
	void sqlgetdiagrec();
	void sqlgetdiagfield();
	void sqlerror();
	void errorall();
	void sqlallochandle();
	void sqldatasources();
	void sqldrivers();
	void sqlendtran();
	void sqlfreehandle();
	void datasourcesall();
	void driversall();
	void sqlbrowseconnect();
	void sqlconnect();
	void sqldriverconnect();
	void sqldisconnect();
	void sqlgetinfo();
	void getinfodbc( SQLHANDLE dbc = SQL_NULL_HANDLE );
	void sqlgetfunctions();
	void sqlnativesql();
	void fullconnect();
	void fulldisconnect();
	void getinfoall();
	void getfunctionsall();
	void sqlcopydesc();
	void sqlgetdescfield();
	void sqlgetdescrec();
	void sqlsetdescfield();
	void sqlsetdescrec();
	void getdescriptorsall();
	void sqlbindparameter();
	void sqlcancel();
	void sqlclosecursor();
	void sqldescribeparam();
	void sqlexecute();
	void sqlexecdirect();
	void sqlfreestmt();
	void sqlgetcursorname();
	void sqlnumparams();
	void sqlparamdata();
	void sqlparamoptions();
	void sqlprepare();
	void sqlputdata();
	void sqlsetcursorname();
	void fillparam();
	void showparam();
	void showcursorsettings();
	void sqlsetstmtattr();
	void sqlgetstmtattr();
	void sqlsetconnectattr();
	void sqlgetconnectattr();
	void sqlsetenvattr();
	void sqlgetenvattr();
	void setcursoratributes();
	void sqlbindcol();
	void sqlbulkoperations();
	void sqlcolattributes();
	void sqlcolattribute();
	void sqldescribecol();
	void sqlextendedfetch();
	void sqlfetch();
	void sqlfetchscroll();
	void sqlgetdata();
	void sqlmoreresults();
	void sqlnumresultscols();
	void sqlrowcount();
	void sqlsetpos();
	void sqlsetscrolloptions();
	void bindcolall();
	void describecolall();
	void fetchall();
	void getdataall();
	void getdatastmt( SQLHANDLE hstmt = SQL_NULL_HANDLE );
	void showboundcols();
	void displayrowset();
	void sqlcolumns();
	void sqlcolumnprivileges();
	void sqlgettypeinfo();
	void sqlforeignkeys();
	void sqlprimarykeys();
	void sqlprocedures();
	void sqlprocedurecolumns();
	void sqlspecialcolumns();
	void sqlstatistics();
	void sqltables();
	void sqltableprivileges();
	void sqlmanagedatasources();
	void sqlremovedefaultdatasource();
	void sqlconfigdatasource();
	void sqlcreatedatasource();
	void sqlvaliddsn();
	void sqlremovedsnfromini();
	void sqlwritedsntoini();
	void sqlremovedrivers();
	void sqlconfigdrivers();
	void sqlinstalldriver();
	void sqlinstalldriverex();
	void sqlgetinstalleddrivers();
	void sqlremovedrivermanager();
	void sqlinstalldrivermanager();
	void sqlreadfiledsn();
	void sqlwritefiledsn();
	void sqlwriteprivateprofilestring();
	void sqlgetprivateprofilestring();
	void sqlinstalltranslator();
	void sqlinstalltranslatorex();
	void sqlremovetranslator();
	void sqlgettranslator();
	void sqlsetconfigmode();
	void sqlgetconfigmode();
	void options();
	void trace();
    void sqlallocenv();
    void sqlfreeenv();
    void sqltransact();
    void sqlallocconnect();
    void sqlfreeconnect();
    void sqlallocstmt();
    void sqlbindparam();
    void sqlsetstmtoption();
    void sqlgetstmtoption();
    void sqlsetconnectoption();
    void sqlgetconnectoption();
    void manage_test();
    void manage_auto_test();
    void manage_test_groups();
    void run_auto_tests();

protected:
    void    resizeEvent( QResizeEvent * );

signals:
    void    explain( const QString& );

private:
    QLabel   *label;

    QMenu*      pmenuFile;
    QMenu*      pmenuDiagnostic;
    QMenu*      pmenuEnvironment;
    QMenu*      pmenuConnection;
    QMenu*      pmenuDescriptor;
    QMenu*      pmenuStatement;
    QMenu*      pmenuAttributes;
    QMenu*      pmenuResults;
    QMenu*      pmenuCatalog;
    QMenu*      pmenuDataSources;
    QMenu*      pmenuDrivers;
    QMenu*      pmenuDriverManager;
    QMenu*      pmenuFileDataSourceName;
    QMenu*      pmenuProfileStrings;
    QMenu*      pmenuTranslator;
    QMenu*      pmenuConfigMode;
    QMenu*      pmenuInstaller;
    QMenu*      pmenuTools;
    QMenu*      pmenuHelp;

    QAction*    pactionExit;
    QAction*    pactionGetDiagRec;
    QAction*    pactionGetDiagField;
    QAction*    pactionError;
    QAction*    pactionErrorsAll;
    QAction*    pactionAllocEnv;
    QAction*    pactionAllocHandle;
    QAction*    pactionDataSources;
    QAction*    pactionDrivers;
    QAction*    pactionFreeEnv;
    QAction*    pactionFreeHandle;
    QAction*    pactionEndTran;
    QAction*    pactionTransact;
    QAction*    pactionDataSourcesAll;
    QAction*    pactionDriversAll;
    QAction*    pactionAllocConnect;
    QAction*    pactionBrowseConnect;
    QAction*    pactionConnect;
    QAction*    pactionDriverConnect;
    QAction*    pactionDisconnect;
    QAction*    pactionFreeConnect;
    QAction*    pactionGetFunctions;
    QAction*    pactionGetInfo;
    QAction*    pactionNativeSQL;
    QAction*    pactionFullConnect;
    QAction*    pactionFullDisconnect;
    QAction*    pactionGetInfoAll;
    QAction*    pactionGetFunctionsAll;
    QAction*    pactionCopyDesc;
    QAction*    pactionGetDescField;
    QAction*    pactionGetDescRec;
    QAction*    pactionSetDescField;
    QAction*    pactionSetDescRec;
    QAction*    pactionGetDescAll;
    QAction*    pactionAllocStmt;
    QAction*    pactionBindParam;
    QAction*    pactionBindParameter;
    QAction*    pactionCancel;
    QAction*    pactionCloseCursor;
    QAction*    pactionDescribeParam;
    QAction*    pactionExecute;
    QAction*    pactionExecDirect;
    QAction*    pactionFreeStmt;
    QAction*    pactionGetCursorName;
    QAction*    pactionNumParams;
    QAction*    pactionParamData;
    QAction*    pactionParamOptions;
    QAction*    pactionPrepare;
    QAction*    pactionPutData;
    QAction*    pactionSetCursorName;
    QAction*    pactionFillParam;
    QAction*    pactionShowParam;
    QAction*    pactionShowCursorSettings;
    QAction*    pactionSetStmtAttr;
    QAction*    pactionGetStmtAttr;
    QAction*    pactionSetStmtOption;
    QAction*    pactionGetStmtOption;
    QAction*    pactionSetConnectAttr;
    QAction*    pactionGetConnectAttr;
    QAction*    pactionSetConnectOption;
    QAction*    pactionGetConnectOption;
    QAction*    pactionSetEnvAttr;
    QAction*    pactionGetEnvAttr;
    QAction*    pactionSetCursorAttributes;
    QAction*    pactionBindCol;
    QAction*    pactionBulkOperations;
    QAction*    pactionColAttributes;
    QAction*    pactionColAttribute;
    QAction*    pactionDescribeCol;
    QAction*    pactionExtendedFetch;
    QAction*    pactionFetch;
    QAction*    pactionFetchScroll;
    QAction*    pactionGetData;
    QAction*    pactionMoreResults;
    QAction*    pactionNumResultCols;
    QAction*    pactionRowCount;
    QAction*    pactionSetPos;
    QAction*    pactionSetScrollOptions;
    QAction*    pactionBindColAll;
    QAction*    pactionDescribeColAll;
    QAction*    pactionFetchAll;
    QAction*    pactionGetDataAll;
    QAction*    pactionShowBoundCols;
    QAction*    pactionDisplayRowset;
    QAction*    pactionColumns;
    QAction*    pactionColumnPrivileges;
    QAction*    pactionGetTypeInfo;
    QAction*    pactionForeignKeys;
    QAction*    pactionPrimaryKeys;
    QAction*    pactionProcedures;
    QAction*    pactionProcedureColumns;
    QAction*    pactionSpecialColumns;
    QAction*    pactionStatistics;
    QAction*    pactionTables;
    QAction*    pactionTablePrivileges;
    QAction*    pactionManageDataSources;
    QAction*    pactionRemoveDefaultDataSource;
    QAction*    pactionConfigDataSource;
    QAction*    pactionCreateDataSource;
    QAction*    pactionValidDSN;
    QAction*    pactionRemoveDSNFromIni;
    QAction*    pactionWriteDSNToIni;
    QAction*    pactionRemoveDrivers;
    QAction*    pactionConfigDrivers;
    QAction*    pactionInstallDriver;
    QAction*    pactionInstallDriverEx;
    QAction*    pactionGetInstalledDrivers;
    QAction*    pactionRemoveDriverManager;
    QAction*    pactionInstallDriverManager;
    QAction*    pactionReadFileDSN;
    QAction*    pactionWriteFileDSN;
    QAction*    pactionWritePrivateProfileString;
    QAction*    pactionGetPrivateProfileString;
    QAction*    pactionInstallTranslator;
    QAction*    pactionInstallTranslatorEx;
    QAction*    pactionRemoveTranslator;
    QAction*    pactionGetTranslator;
    QAction*    pactionSetConfigMode;
    QAction*    pactionGetConfigMode;
    QAction*    pactionOptions;
    QAction*    pactionTrace;
    QAction*    pactionManageTestSources;
    QAction*    pactionManageAutoTests;
    QAction*    pactionManageTestGroups;
    QAction*    pactionRunAutoTests;
    QAction*    pactionHelpTest;
    QAction*    pactionHelpApi;
    QAction*    pactionHelpAbout;

    void createActions();
    void createMenus();
};



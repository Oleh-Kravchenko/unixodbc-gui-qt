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
    void getInfoOdbc( SQLHANDLE dbc = SQL_NULL_HANDLE );
    void getDataStmt( SQLHANDLE hstmt = SQL_NULL_HANDLE );
   
public slots:
    // slots for our actions...
    void slotExit();
    void slotGetDiagRec();
    void slotGetDiagField();
    void slotError();
    void slotErrorsAll();
    void slotAllocEnv();
    void slotAllocHandle();
    void slotDataSources();
    void slotDrivers();
    void slotFreeEnv();
    void slotFreeHandle();
    void slotEndTran();
    void slotTransact();
    void slotDataSourcesAll();
    void slotDriversAll();
    void slotAllocConnect();
    void slotBrowseConnect();
    void slotConnect();
    void slotDriverConnect();
    void slotDisconnect();
    void slotFreeConnect();
    void slotGetFunctions();
    void slotGetInfo();
    void slotNativeSql();
    void slotFullConnect();
    void slotFullDisconnect();
    void slotGetInfoAll();
    void slotGetFunctionsAll();
    void slotCopyDesc();
    void slotGetDescField();
    void slotGetDescRec();
    void slotSetDescField();
    void slotSetDescRec();
    void slotGetDescAll();
    void slotAllocStmt();
    void slotBindParam();
    void slotBindParameter();
    void slotCancel();
    void slotCloseCursor();
    void slotDescribeParam();
    void slotExecute();
    void slotExecDirect();
    void slotFreeStmt();
    void slotGetCursorName();
    void slotNumParams();
    void slotParamData();
    void slotParamOptions();
    void slotPrepare();
    void slotPutData();
    void slotSetCursorName();
    void slotFillParam();
    void slotShowParam();
    void slotShowCursorSettings();
    void slotSetStmtAttr();
    void slotGetStmtAttr();
    void slotSetStmtOption();
    void slotGetStmtOption();
    void slotSetConnectAttr();
    void slotGetConnectAttr();
    void slotSetConnectOption();
    void slotGetConnectOption();
    void slotSetEnvAttr();
    void slotGetEnvAttr();
    void slotSetCursorAttributes();
    void slotBindCol();
    void slotBulkOperations();
    void slotColAttributes();
    void slotColAttribute();
    void slotDescribeCol();
    void slotExtendedFetch();
    void slotFetch();
    void slotFetchScroll();
    void slotGetData();
    void slotMoreResults();
    void slotNumResultCols();
    void slotRowCount();
    void slotSetPos();
    void slotSetScrollOptions();
    void slotBindColAll();
    void slotDescribeColAll();
    void slotFetchAll();
    void slotGetDataAll();
    void slotShowBoundCols();
    void slotDisplayRowSet();
    void slotColumns();
    void slotColumnPrivileges();
    void slotGetTypeInfo();
    void slotForeignKeys();
    void slotPrimaryKeys();
    void slotProcedures();
    void slotProcedureColumns();
    void slotSpecialColumns();
    void slotStatistics();
    void slotTables();
    void slotTablePrivileges();
    void slotManageDataSources();
    void slotRemoveDefaultDataSource();
    void slotConfigDataSource();
    void slotCreateDataSource();
    void slotValidDSN();
    void slotRemoveDSNFromIni();
    void slotWriteDSNToIni();
    void slotRemoveDrivers();
    void slotConfigDrivers();
    void slotInstallDriver();
    void slotInstallDriverEx();
    void slotGetInstalledDrivers();
    void slotRemoveDriverManager();
    void slotInstallDriverManager();
    void slotReadFileDSN();
    void slotWriteFileDSN();
    void slotWritePrivateProfileString();
    void slotGetPrivateProfileString();
    void slotInstallTranslator();
    void slotInstallTranslatorEx();
    void slotRemoveTranslator();
    void slotGetTranslator();
    void slotSetConfigMode();
    void slotGetConfigMode();
    void slotOptions();
    void slotTrace();
    void slotManageTestSources();
    void slotManageAutoTests();
    void slotManageTestGroups();
    void slotRunAutoTests();
    void slotHelpTest();
    void slotHelpApi();
    void slotHelpAbout();

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
    QAction*    pactionNativeSql;
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
    QAction*    pactionDisplayRowSet;
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
    void readApplicationState();
    void writeApplicationState();
};



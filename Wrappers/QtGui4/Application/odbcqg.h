/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQG_H
#define ODBCQG_H


// qt
#include <QtGui>

// odbcplus
#include <ODBCMessage.h>

// odbcqg
#include <ODBCQGSystem.h>
#include <ODBCQGEnvironment.h>
#include <ODBCQGConnection.h>
#include <ODBCQGStatement.h>

class odbcqg : public QMainWindow
{ 
    Q_OBJECT
public:
	explicit odbcqg();
	~odbcqg();

protected:
    ODBCQGSystem *      pSystem;
    ODBCQGEnvironment * pEnvironment;
    ODBCQGConnection *  pConnection;
    ODBCQGStatement *   pStatement;

    QMenu * pmenuFile;
    QMenu * pmenuDataSource;
    QMenu * pmenuHelp;

    QToolBar *  ptoolbarFile;
    QToolBar *  ptoolbarDataSource;

    QAction *   pactionExecute;
    QAction *   pactionQuit;
    QAction *   pactionConnect;
    QAction *   pactionAbout;

    QSplitter *     pSplitter;
    QTextEdit *     ptexteditSQL;
    QTableWidget *  ptablewidgetResults;
    QTextEdit *     ptexteditMessages;

    void createHandles();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createClientArea();

    void doResultGUIGrid();
    void doResultGUIGridHeader( SWORD nColumns );
    void doResultGUIGridBody( SWORD nColumns );

protected slots:
    void slotConnectToggle();
    void slotConnected();
    void slotDisconnected();
    void slotExecute();
    void slotResults( ODBCQStatement *pStatement );
    void slotMessage( ODBCMessage Message );
};

#endif


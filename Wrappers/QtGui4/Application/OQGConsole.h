/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQG_H
#define OQG_H


// qt
#include <QtGui>

// odbc_CPP
#include <ODBCMessage.h>

// odbcqg
#include <OQGSystem.h>
#include <OQGEnvironment.h>
#include <OQGConnection.h>
#include <OQGStatement.h>

class odbcqg : public QMainWindow
{ 
    Q_OBJECT
public:
	explicit odbcqg();
	~odbcqg();

protected:
    OQGSystem *      pSystem;
    OQGEnvironment * pEnvironment;
    OQGConnection *  pConnection;
    OQGStatement *   pStatement;

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
    void slotResults( OQStatement *pStatement );
    void slotMessage( ODBCMessage Message );
};

#endif


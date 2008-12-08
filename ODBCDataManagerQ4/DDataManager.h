#ifndef DDATAMANAGER_H
#define DDATAMANAGER_H

#include <QtGui>

#include "ODBCQGEnvironment.h"
#include "ODBCModelSystem.h"
#include "ODBCModelBrowser.h"
#include "ODBCViewBrowser.h"
#include "ODBCDelegateCell.h"

class DBrowser;
class DPropWidget;
class DOutputMessages;
class DOutputLog;
class DEdit;

class DDataManager : public QMainWindow
{
    Q_OBJECT
public:
    DDataManager();
    virtual ~DDataManager();

protected slots:
    void slotSubWindowActivated( QMdiSubWindow *pSubWindow );
    void slotSelected( const QModelIndex &index );

protected:
    ODBCViewBrowser *       pViewBrowser;
    ODBCQGSystem *          pSystem;
    ODBCModelSystem *       pModelSystem;
    ODBCModelBrowser *      pModelBrowser;
    QTableView *            ptableviewProperties; // properties
    ODBCDelegateCell *      pDelegateCell;

    QToolBar *          ptoolbarEditor;
    QMdiArea *          pMdiArea;
    DOutputMessages *   pOutputMessages;
    DOutputLog *        pOutputLog;

    DEdit *             pEdit; // current editor or NULL

    QMenu * pmenuFile;
    QMenu * pmenuHelp;

    QAction *   pactionQuit;
    QAction *   pactionAbout;

    QAction *   pactionSubmit;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
};

#endif


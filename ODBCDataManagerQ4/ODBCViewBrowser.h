#ifndef ODBCVIEWBROWSER_H
#define ODBCVIEWBROWSER_H

#include <QtGui>

#include "ODBCModel.h"

class ODBCViewBrowser : public QTreeView
{
    Q_OBJECT
public:
    explicit ODBCViewBrowser( QWidget *pwidgetParent = 0 );
    ~ODBCViewBrowser();

protected:
    void contextMenuEvent( QContextMenuEvent *pEvent );

private:
    void readSettings();
    void writeSettings();
};


#endif



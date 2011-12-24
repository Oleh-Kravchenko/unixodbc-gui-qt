/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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



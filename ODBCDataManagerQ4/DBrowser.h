/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DBROWSER_H
#define DBROWSER_H

#include <QtGui>

#include "DNode.h"

class DNodeWidget;
class DPropWidget;

class DBrowser : public QDockWidget
{
    Q_OBJECT
public:
    explicit DBrowser( const QString &stringTitle, QWidget *pwidgetParent, QWidget *pwidgetEditorParent, DPropWidget *pPropWidget );
    ~DBrowser();

signals:
    void signalDiagnosticClear();
    void signalDiagnostic( DDiagnostic d );

public slots:
    void slotCurrentItemChanged( QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious );

private:
    QWidget *       pwidgetMain;
    QVBoxLayout *   playoutMain;
    QToolBar *      pToolBar;
    DNodeWidget *   pNodeWidget;
    DPropWidget *   pPropWidget;

    void readSettings();
    void writeSettings();
};

#endif



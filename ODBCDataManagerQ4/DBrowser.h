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



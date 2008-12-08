#ifndef DPROPWIDGET_H
#define DPROPWIDGET_H

#include <QtGui>

class DNodeWidget;

class DPropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DPropWidget( QWidget *pwidgetParent );
    virtual ~DPropWidget();

    DNodeWidget *getNodeWidget() { return pNodeWidget; }

public slots:
    void slotCurrentItemChanged( QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious );

private:
    QVBoxLayout *   playoutMain;
    QToolBar *      pToolBar;
    DNodeWidget *   pNodeWidget;

    void readSettings();
    void writeSettings();
};

#endif



/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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



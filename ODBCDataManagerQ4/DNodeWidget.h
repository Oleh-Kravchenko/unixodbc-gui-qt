/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEWIDGET_H
#define DNODEWIDGET_H

#include <QtGui>

#include "DNode.h"

class DNodeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DNodeWidget( const QString &stringName, QWidget *pwidgetParent, QWidget *pwidgetEditorParent );
    ~DNodeWidget();

    void setEditorParent( QWidget *pWidget ) { pwidgetEditorParent = pWidget; }

    QWidget *getEditorParent() { return pwidgetEditorParent; }

protected slots:
    void slotExpanded( QTreeWidgetItem *pItem );
    void slotCollapsed( QTreeWidgetItem *pItem );

protected:
    void contextMenuEvent( QContextMenuEvent * );

private:
    QWidget *       pwidgetEditorParent;

    void readSettings();
    void writeSettings();
};

#endif



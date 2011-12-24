/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DOUTPUTMESSAGES_H
#define DOUTPUTMESSAGES_H

#include <QtGui>

#include "DNode.h"

class DOutputMessages : public QWidget
{
    Q_OBJECT
public: 
    DOutputMessages( QWidget *pwidgetParent );
    ~DOutputMessages();

public slots:
    void slotDiagnosticClear();
    void slotDiagnostic( DDiagnostic d );
    void slotClear();

private:
    QVBoxLayout *   playoutMain;
    QToolBar *      pToolBar;
    QTreeWidget *   pTreeWidget;
};

#endif


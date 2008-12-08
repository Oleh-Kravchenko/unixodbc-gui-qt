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


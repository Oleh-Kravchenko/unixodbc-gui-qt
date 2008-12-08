#ifndef DNODEDRIVERS_H
#define DNODEDRIVERS_H

#include "DNode.h"
#include "DNodeDriver.h"

class DNodeDrivers : public DNode
{
    Q_OBJECT
public:
    DNodeDrivers( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNodeDrivers();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoad();
    void doClear() {}

protected slots:
    void slotAdd();

protected:
    QAction *pactionAdd; 
};

#endif


#ifndef DNODEDRIVER_H
#define DNODEDRIVER_H

#include "DNode.h"

class DNodeDriver : public DNode
{
    Q_OBJECT
public:
    DNodeDriver( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringDriver );
    virtual ~DNodeDriver();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoadProperties( DPropWidget *pPropWidget );
    void doClearProperties( DPropWidget *pPropWidget );
    void doLoad() {}
    void doClear() {}

protected slots:
    void slotConnect();
    void slotRemove();

protected:
    QAction *pactionConnect; 
    QAction *pactionRemove;

private:
    QString stringDriver;
};

#endif


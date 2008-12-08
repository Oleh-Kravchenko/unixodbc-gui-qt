#ifndef DNODEATTRIBUTE_H
#define DNODEATTRIBUTE_H

#include "DNode.h"

class DNodeAttribute : public DNode
{
    Q_OBJECT
public:
    DNodeAttribute( DNodeWidget *pNodeWidget, const QString &stringName, const QString &stringValue );
    DNodeAttribute( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName, const QString &stringValue );
    virtual ~DNodeAttribute();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoad();
    void doClear();

protected slots:
    void slotAdd();
    void slotRemove();

protected:
    QAction *pactionAdd; 
    QAction *pactionRemove;

};

#endif


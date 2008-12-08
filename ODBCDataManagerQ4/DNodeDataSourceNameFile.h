#ifndef DNODEDATASOURCENAMEFILE_H
#define DNODEDATASOURCENAMEFILE_H

#include "DNode.h"

class DNodeDataSourceNameFile : public DNode
{
    Q_OBJECT
public:
    DNodeDataSourceNameFile( DNodeWidget *pNodeWidget, DNode *pNode, const QFileInfo &f );
    virtual ~DNodeDataSourceNameFile();

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
    QAction *   pactionConnect; 
    QAction *   pactionRemove; 
    QFileInfo   f;
};

#endif


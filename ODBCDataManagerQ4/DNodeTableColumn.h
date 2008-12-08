#ifndef DNODEDATASOURCENAMEUSER_H
#define DNODEDATASOURCENAMEUSER_H

#include "DNode.h"

class DNodeTableColumn : public DNode
{
public:
    DNodeTableColumn( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName );
    virtual ~DNodeTableColumn();

    void doLoad() {}
    void doClear() {}
};

#endif


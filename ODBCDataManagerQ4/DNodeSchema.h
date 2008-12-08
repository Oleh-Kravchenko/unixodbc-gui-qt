#ifndef DNODESCHEMA_H
#define DNODESCHEMA_H

#include "DNode.h"
// #include "DNodeTableTypes.h"

class DNodeSchema : public DNode
{
public:
    DNodeSchema( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema );
    virtual ~DNodeSchema();

    void doLoad() {}
    void doClear() {}
};

#endif


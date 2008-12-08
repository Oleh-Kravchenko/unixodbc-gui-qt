#ifndef DNODESCHEMAS_H
#define DNODESCHEMAS_H

#include "DNode.h"
#include "DNodeSchema.h"

class DNodeSchemas : public DNode
{
public:
    DNodeSchemas( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNodeSchemas();

    void doLoad() {}
    void doClear() {}
};

#endif


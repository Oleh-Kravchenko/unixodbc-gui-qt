#ifndef DNODETABLE_H
#define DNODETABLE_H

#include "DNode.h"

class DNodeTable : public DNode
{
public:
    DNodeTable( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema, const QString &stringTable );
    virtual ~DNodeTable();

    void doLoad() {}
    void doClear() {}

protected:
    QString stringSchema;
};

#endif


#ifndef DNODETABLES_H
#define DNODETABLES_H

#include "DNode.h"

class DNodeTables : public DNode
{
public:
    DNodeTables( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema );
    virtual ~DNodeTables();

    void doLoad() {}
    void doClear() {}

protected:
    QString stringSchema;
};

#endif


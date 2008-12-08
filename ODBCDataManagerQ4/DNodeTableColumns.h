#ifndef DNODETABLECOLUMNS_H
#define DNODETABLECOLUMNS_H

#include "DNode.h"

class DNodeTableColumns : public DNode
{
public:
    DNodeTableColumns( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema, const QString &stringTable );
    virtual ~DNodeTableColumns();

    void doLoad() {}
    void doClear() {}

private:
    QString stringSchema;
    QString stringTable;
};

#endif


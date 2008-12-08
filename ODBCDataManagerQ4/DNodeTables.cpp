#include "DNodeTables.h"

#include "DNodeTable.h"

#include "DataSourceNames48.xpm"

DNodeTables::DNodeTables( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema )
    : DNode( pNodeWidget, pNode )
{
    this->stringSchema = stringSchema;
}

DNodeTables::~DNodeTables()
{
}



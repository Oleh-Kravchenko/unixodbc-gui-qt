#include "DNodeTable.h"

#include "DNodeTableColumn.h"

#include "DataSourceNameUser48.xpm"

DNodeTable::DNodeTable( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema, const QString &stringTable )
    : DNode( pNodeWidget, pNode )
{
    this->stringSchema = stringSchema;
}

DNodeTable::~DNodeTable()
{
}



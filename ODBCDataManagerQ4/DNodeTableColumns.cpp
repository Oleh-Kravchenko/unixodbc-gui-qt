#include "DNodeTableColumns.h"

#include "DNodeTableColumn.h"

#include "DataSourceNameUser48.xpm"

DNodeTableColumns::DNodeTableColumns( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema, const QString &stringTable )
    : DNode( pNodeWidget, pNode )
{
    this->stringSchema  = stringSchema;
    this->stringTable   = stringTable;

}

DNodeTableColumns::~DNodeTableColumns()
{
}



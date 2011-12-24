/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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



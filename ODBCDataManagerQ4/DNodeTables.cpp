/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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



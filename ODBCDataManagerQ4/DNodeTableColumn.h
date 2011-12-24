/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEDATASOURCENAMEUSER_H
#define DNODEDATASOURCENAMEUSER_H

#include "DNode.h"

class DNodeTableColumn : public DNode
{
public:
    DNodeTableColumn( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName );
    virtual ~DNodeTableColumn();

    void doLoad() {}
    void doClear() {}
};

#endif


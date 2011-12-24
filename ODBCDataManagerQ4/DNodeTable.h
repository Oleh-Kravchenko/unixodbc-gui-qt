/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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


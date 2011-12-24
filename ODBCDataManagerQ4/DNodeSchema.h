/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODESCHEMA_H
#define DNODESCHEMA_H

#include "DNode.h"
// #include "DNodeTableTypes.h"

class DNodeSchema : public DNode
{
public:
    DNodeSchema( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringSchema );
    virtual ~DNodeSchema();

    void doLoad() {}
    void doClear() {}
};

#endif


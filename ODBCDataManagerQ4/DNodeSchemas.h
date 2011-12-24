/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODESCHEMAS_H
#define DNODESCHEMAS_H

#include "DNode.h"
#include "DNodeSchema.h"

class DNodeSchemas : public DNode
{
public:
    DNodeSchemas( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNodeSchemas();

    void doLoad() {}
    void doClear() {}
};

#endif


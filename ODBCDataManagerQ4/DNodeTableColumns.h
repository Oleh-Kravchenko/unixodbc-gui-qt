/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
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


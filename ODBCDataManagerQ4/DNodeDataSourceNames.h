/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEDATASOURCENAMES_H
#define DNODEDATASOURCENAMES_H

#include "DNode.h"

class DNodeDataSourceNames : public DNode
{
    Q_OBJECT
public:
    DNodeDataSourceNames( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNodeDataSourceNames();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoad();
    void doClear() {}

protected slots:
    void slotAdd();

protected:
    QAction *pactionAdd; 
};

#endif


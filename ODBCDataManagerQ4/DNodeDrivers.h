/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEDRIVERS_H
#define DNODEDRIVERS_H

#include "DNode.h"
#include "DNodeDriver.h"

class DNodeDrivers : public DNode
{
    Q_OBJECT
public:
    DNodeDrivers( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNodeDrivers();

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


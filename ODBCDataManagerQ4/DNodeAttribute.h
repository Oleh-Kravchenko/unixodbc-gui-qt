/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEATTRIBUTE_H
#define DNODEATTRIBUTE_H

#include "DNode.h"

class DNodeAttribute : public DNode
{
    Q_OBJECT
public:
    DNodeAttribute( DNodeWidget *pNodeWidget, const QString &stringName, const QString &stringValue );
    DNodeAttribute( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName, const QString &stringValue );
    virtual ~DNodeAttribute();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoad();
    void doClear();

protected slots:
    void slotAdd();
    void slotRemove();

protected:
    QAction *pactionAdd; 
    QAction *pactionRemove;

};

#endif


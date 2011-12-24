/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODESTATEMENT_H
#define DNODESTATEMENT_H

#include "DNodeConnection.h"

class DEditStatement;

class DNodeStatement : public DNode
{
    Q_OBJECT
public:
    DNodeStatement( DNodeWidget *pNodeWidget, DNodeConnection *pNode );
    virtual ~DNodeStatement();

    SQLHSTMT getStatement();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoadProperties( DPropWidget *pPropWidget );
    void doClearProperties( DPropWidget *pPropWidget );
    void doLoad() {}
    void doClear() {}

    bool isAllocated( bool bEnsure = false );

protected slots:
    void slotRemove();

protected:
    QAction *       pactionRemove;
    SQLHSTMT        hStmt;
    DEditStatement *pEditStatement;
};

#endif


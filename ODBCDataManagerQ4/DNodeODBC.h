/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODEODBC_H
#define DNODEODBC_H

#include "DNode.h"

class DNodeODBC : public DNode
{
    Q_OBJECT
public:
    DNodeODBC( DNodeWidget *pNodeWidget );
    virtual ~DNodeODBC();

    SQLHENV getEnvironment();

    void doLoadProperties( DPropWidget *pPropWidget );
    void doClearProperties( DPropWidget *pPropWidget );
    void doLoad() {}
    void doClear() {}

private:
    SQLHENV hEnv;
};

#endif


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


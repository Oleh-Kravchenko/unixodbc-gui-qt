#ifndef DNODECONNECTION_H
#define DNODECONNECTION_H

#include "DNode.h"
#include "DNodeDriver.h"
#include "DNodeDataSourceNameFile.h"
#include "DNodeDataSourceNameSystem.h"
#include "DNodeDataSourceNameUser.h"

class DNodeConnection : public DNode
{
    Q_OBJECT
public:
    DNodeConnection( DNodeWidget *pNodeWidget, DNodeDriver *pNode );
    DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameFile *pNode );
    DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameSystem *pNode );
    DNodeConnection( DNodeWidget *pNodeWidget, DNodeDataSourceNameUser *pNode );
    virtual ~DNodeConnection();

    SQLHDBC getConnection();

    void doLoadToolBar( QToolBar *pToolBar );
    void doClearToolBar( QToolBar *pToolBar );
    void doLoadProperties( DPropWidget *pPropWidget );
    void doClearProperties( DPropWidget *pPropWidget );
    void doLoad() {}
    void doClear() {}

    bool isAllocated( bool bEnsure = false );
    bool isConnected( bool bEnsure = false );

protected slots:
    void slotConnectToggle();
    void slotNewStatement();

protected:
    SQLHDBC     hDbc;
    bool        bConnected;
    QAction *   pactionConnectToggle; 
    QAction *   pactionNewStatement; 

    bool doConnect( DNodeDriver *pNode );              
    bool doConnect( DNodeDataSourceNameFile *pNode );  
    bool doConnect( DNodeDataSourceNameSystem *pNode );
    bool doConnect( DNodeDataSourceNameUser *pNode );  
    void doInit();
};

#endif


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeConnection.h"
#include "DNodeODBC.h"
#include "DNode.h"

#include "DNodeWidget.h"

DNode::DNode( DNodeWidget *pNodeWidget )
    : QTreeWidgetItem( (QTreeWidget*)pNodeWidget )
{
    this->pNodeWidget = pNodeWidget;
    setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
}

DNode::DNode( DNodeWidget *pNodeWidget, DNode *pNode )
    : QObject( pNode ), QTreeWidgetItem( pNode )
{
    this->pNodeWidget = pNodeWidget;
    setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
}

DNode::~DNode()
{
}

SQLHENV DNode::getEnvironment()
{
    DNode *pNode = this;

    while ( pNode )
    {
        if ( QString( pNode->metaObject()->className() ) == "DNodeODBC" )
        {
            return ((DNodeODBC*)pNode)->getEnvironment();
        }
        pNode = (DNode*)(((QObject*)pNode)->parent());
    }

    return NULL;
}

SQLHDBC DNode::getConnection()
{
    DNode *pNode = this;

    while ( pNode )
    {
        if ( QString( pNode->metaObject()->className() ) == "DNodeConnection" )
        {
            return ((DNodeConnection*)pNode)->getConnection();
        }
        pNode = (DNode*)(((QObject*)pNode)->parent());
    }

    return NULL;
}

void DNode::doDiagnosticClearSignal()
{
    // for those connected to us...
    emit signalDiagnosticClear();

    // for those aggregating at some parent...
    QObject *pObject = (QObject*)((QObject*)this)->parent();
    if ( !pObject )
        return;

    if ( pObject->inherits( "DNode" ) )
    {
        DNode *pNode = (DNode*)pObject;
        pNode->doDiagnosticClearSignal();
    }
}

void DNode::doDiagnosticSignal( DDiagnostic d )
{
    // for those connected to us...
    emit signalDiagnostic( d );

    // for those aggregating at some parent...
    QObject *pObject = (QObject*)((QObject*)this)->parent();
    if ( !pObject )
        return;

    if ( pObject->inherits( "DNode" ) )
    {
        DNode *pNode = (DNode*)pObject;
        pNode->doDiagnosticSignal( d );
    }
}

QWidget *DNode::getEditorParent()
{
    if ( !pNodeWidget )
        return 0;

    return pNodeWidget->getEditorParent();
}



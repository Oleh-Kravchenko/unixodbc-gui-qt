/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeAttribute.h"

#include "Attribute48.xpm"
#include "Add32.xpm"
#include "Remove32.xpm"

DNodeAttribute::DNodeAttribute( DNodeWidget *pNodeWidget, const QString &stringName, const QString &stringValue )
    : DNode( pNodeWidget )
{
    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
//    setIcon( 0, QIcon( xpmAttribute48 ) );
    setText( 0, stringName );
    setText( 1, stringValue );

    pactionAdd = new QAction( QIcon( xpmAdd32 ), "Add", 0 );
    connect( pactionAdd, SIGNAL(triggered()), this, SLOT(slotAdd()) );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );
}

DNodeAttribute::DNodeAttribute( DNodeWidget *pNodeWidget, DNode *pNode, const QString &stringName, const QString &stringValue )
    : DNode( pNodeWidget, pNode )
{
    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
//    setIcon( 0, QIcon( xpmAttribute48 ) );
    setText( 0, stringName );
    setText( 1, stringValue );
}

DNodeAttribute::~DNodeAttribute()
{
    delete pactionAdd;
    delete pactionRemove;
}

void DNodeAttribute::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionAdd );
    pToolBar->addAction( pactionRemove );
}

void DNodeAttribute::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionAdd );
    pToolBar->removeAction( pactionRemove );
}

void DNodeAttribute::doLoad()
{
}

void DNodeAttribute::doClear()
{
}

void DNodeAttribute::slotAdd()
{
    DNodeAttribute *p = new DNodeAttribute( pNodeWidget, "?", "" );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
}

void DNodeAttribute::slotRemove()
{
    delete this;
}


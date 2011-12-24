/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DPropWidget.h"
#include "DNodeWidget.h"

DPropWidget::DPropWidget( QWidget *pwidgetParent )
    : QWidget( pwidgetParent )
{
    playoutMain = new QVBoxLayout;

    playoutMain->setSpacing( 0 );

    // tool bar on top...
    pToolBar = new QToolBar( this );
    playoutMain->addWidget( pToolBar );

    // browser below...
    pNodeWidget = new DNodeWidget( "Properties", this, 0 );
    pNodeWidget->setRootIsDecorated( false );
    playoutMain->addWidget( pNodeWidget );
    connect( pNodeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)) );

    //
    setLayout( playoutMain );
    readSettings();
}

DPropWidget::~DPropWidget()
{
    writeSettings();
}

void DPropWidget::slotCurrentItemChanged( QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious )
{
    if ( pPrevious )
    {
        DNode *pNode = (DNode*)pPrevious;
        pNode->doClearToolBar( pToolBar );
    }

    if ( pCurrent )
    {
        DNode *pNode = (DNode*)pCurrent;
        pNode->doLoadToolBar( pToolBar );
    }
}

void DPropWidget::readSettings()
{
    QSettings settings;
    resize( settings.value( "DPropWidget/width", width() ).toInt(), height() );
}

void DPropWidget::writeSettings()
{
    QSettings settings;
    settings.setValue( "DPropWidget/width", width() );
}


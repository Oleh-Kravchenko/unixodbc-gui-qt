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


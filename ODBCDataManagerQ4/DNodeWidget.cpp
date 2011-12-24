/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeWidget.h"

/*! 
 * \brief   Constructs a DNodeWidget.
 * 
 * \param   pwidgetParent
 */
DNodeWidget::DNodeWidget( const QString &stringName, QWidget *pwidgetParent, QWidget *pwidgetEditorParent )
    : QTreeWidget( pwidgetParent )
{
    setObjectName( stringName );

    this->pwidgetEditorParent   = pwidgetEditorParent;
    setRootIsDecorated( true );

    QStringList stringlistLabels;
    stringlistLabels << tr("Name") << tr("Value") << tr("Description");
    setHeaderLabels( stringlistLabels );

    connect( this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(slotExpanded(QTreeWidgetItem*)) );
    connect( this, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(slotCollapsed(QTreeWidgetItem*)) );

    readSettings();
}

/*! 
 * \brief   Destructs DNodeWidget.
 * 
 */
DNodeWidget::~DNodeWidget()
{
    writeSettings();
}

void DNodeWidget::slotExpanded( QTreeWidgetItem *pItem )
{
    ((DNode*)pItem)->doLoad();
}

void DNodeWidget::slotCollapsed( QTreeWidgetItem *pItem )
{
    ((DNode*)pItem)->doClear();
}

void DNodeWidget::contextMenuEvent( QContextMenuEvent *pContextMenuEvent )
{
    QTreeWidgetItem *pTreeWidgetItem = itemAt( pContextMenuEvent->pos() );

    if ( !pTreeWidgetItem )
        return;
    DNode *pNode = (DNode*)pTreeWidgetItem;

printf( "[PAH][%s][%d] %s\n", __FILE__, __LINE__, pNode->metaObject()->className() );
}

void DNodeWidget::readSettings()
{
    QSettings settings;
    setColumnWidth( 0, settings.value( objectName() + "/col0", columnWidth( 0 ) ).toInt() );
    setColumnWidth( 1, settings.value( objectName() + "/col1", columnWidth( 1 ) ).toInt() );
    setColumnWidth( 2, settings.value( objectName() + "/col2", columnWidth( 2 ) ).toInt() );
}

void DNodeWidget::writeSettings()
{
    QSettings settings;
    settings.setValue( objectName() + "/col0", columnWidth( 0 ) );
    settings.setValue( objectName() + "/col1", columnWidth( 1 ) );
    settings.setValue( objectName() + "/col2", columnWidth( 2 ) );
}


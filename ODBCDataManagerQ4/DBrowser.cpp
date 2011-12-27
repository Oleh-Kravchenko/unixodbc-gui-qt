/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DBrowser.h"
#include "DNodeWidget.h"
#include "DPropWidget.h"
#include "DNodeOQ.h"

DBrowser::DBrowser( const QString &stringTitle, QWidget *pwidgetParent, QWidget *pwidgetEditorParent, DPropWidget *pPropWidget )
    : QDockWidget( stringTitle, pwidgetParent )
{
    this->pPropWidget = pPropWidget;

    playoutMain = new QVBoxLayout;
    pwidgetMain = new QWidget( this );

    playoutMain->setSpacing( 0 );

    // tool bar on top...
    pToolBar = new QToolBar( pwidgetMain );
    playoutMain->addWidget( pToolBar );

    // browser below...
    pNodeWidget = new DNodeWidget( "Objects", pwidgetMain, pwidgetEditorParent );
    DNode *pNode = new DNodeODBC( pNodeWidget );
    playoutMain->addWidget( pNodeWidget );
    connect( pNode, SIGNAL(signalDiagnosticClear()), this, SIGNAL(signalDiagnosticClear()) );
    connect( pNode, SIGNAL(signalDiagnostic(DDiagnostic)), this, SIGNAL(signalDiagnostic(DDiagnostic)) );
    connect( pNodeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)) );

    //
    pwidgetMain->setLayout( playoutMain );
    setWidget( pwidgetMain );
    readSettings();
}

DBrowser::~DBrowser()
{
    writeSettings();
}

void DBrowser::slotCurrentItemChanged( QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious )
{
    if ( pPrevious )
    {
        DNode *pNode = (DNode*)pPrevious;
        pNode->doClearToolBar( pToolBar );
        pNode->doClearProperties( pPropWidget );
    }

    if ( pCurrent )
    {
        DNode *pNode = (DNode*)pCurrent;
        pNode->doLoadToolBar( pToolBar );
        pNode->doLoadProperties( pPropWidget );
    }
}

void DBrowser::readSettings()
{
    QSettings settings;
    resize( settings.value( "DBrowser/width", width() ).toInt(), height() );
}

void DBrowser::writeSettings()
{
    QSettings settings;
    settings.setValue( "DBrowser/width", width() );
}


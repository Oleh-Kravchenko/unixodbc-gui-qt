/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeDataSourceNameFile.h"

#include "DNodeConnection.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Connected48.xpm"
#include "Remove32.xpm"
#include "DataSourceNameFile48.xpm"

DNodeDataSourceNameFile::DNodeDataSourceNameFile( DNodeWidget *pNodeWidget, DNode *pNode, const QFileInfo &f )
    : DNode( pNodeWidget, pNode )
{
    this->f = f;
    setIcon( 0, QIcon( xpmDataSourceNameFile48 ) );
    setText( 0, f.baseName() );

    pactionConnect = new QAction( QIcon( xpmConnected48 ), "Connect", 0 );
    connect( pactionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()) );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );

    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );
}

DNodeDataSourceNameFile::~DNodeDataSourceNameFile()
{
    delete pactionConnect;
    delete pactionRemove;
}

void DNodeDataSourceNameFile::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionConnect );
    pToolBar->addAction( pactionRemove );
}

void DNodeDataSourceNameFile::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionConnect );
    pToolBar->removeAction( pactionRemove );
}

void DNodeDataSourceNameFile::slotConnect()
{
    DNodeConnection *pConnection = new DNodeConnection( pNodeWidget, this );

    setExpanded( true );
}

void DNodeDataSourceNameFile::slotRemove()
{
    delete this;
}

void DNodeDataSourceNameFile::doLoadProperties( DPropWidget *pPropWidget )
{
    char    szError[FILENAME_MAX+1];
    DWORD   nError;
    char    szKeyValues[4048];

    if ( !SQLReadFileDSN( f.absoluteFilePath().toAscii().data(), "ODBC", NULL, szKeyValues, sizeof( szKeyValues ), NULL ) )
    {
        SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
        printf( "DNodeDataSourceNameFile: SQLReadFileDSN failed with %s for %s.\n", szError, f.absoluteFilePath().toAscii().data() );
        return;
    }

    if ( strlen( szKeyValues ) < 1 )
    {
        printf( "DNodeDataSourceNameFile: SQLReadFileDSN failed to return any keys for %s.\n", f.absoluteFilePath().toAscii().data() );
        return;
    }

    QString     stringKeyValues( szKeyValues );
    QStringList stringlistKeyValues = stringKeyValues.split( ';' );

    for ( int nKeyValues = 0; nKeyValues < stringlistKeyValues.size(); ++nKeyValues )
    {
        QString     stringKeyValue      = stringlistKeyValues.at( nKeyValues );
        QStringList stringlistKeyValue  = stringKeyValue.split( '=' );
        if ( stringlistKeyValue.count() > 1 )
        {
            DNodeAttribute *p = new DNodeAttribute( pPropWidget->getNodeWidget(), stringlistKeyValue.at( 0 ).toLocal8Bit().constData(), stringlistKeyValue.at( 1 ).toLocal8Bit().constData() );
            p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
        }
        else if ( stringlistKeyValue.count() > 0 )
        {
            DNodeAttribute *p = new DNodeAttribute( pPropWidget->getNodeWidget(), stringlistKeyValue.at( 0 ).toLocal8Bit().constData(), "" );
            p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
        }
    }
}

void DNodeDataSourceNameFile::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}




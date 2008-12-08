#include "ODBCViewBrowser.h"
#include "ODBCModelBrowser.h"

ODBCViewBrowser::ODBCViewBrowser( QWidget *pwidgetParent )
    : QTreeView( pwidgetParent )
{
    setObjectName( metaObject()->className() );
    setRootIsDecorated( true );

    readSettings();
}

ODBCViewBrowser::~ODBCViewBrowser()
{
    writeSettings();
}

void ODBCViewBrowser::contextMenuEvent( QContextMenuEvent *pEvent )
{
    QModelIndex index = indexAt( pEvent->pos() );

    ODBCModelBrowser *pModelBrowser = (ODBCModelBrowser*)model();
    if ( !pModelBrowser )
        return;

    pModelBrowser->doContextMenu( index, this, mapToGlobal( pEvent->pos() ) );
}

void ODBCViewBrowser::readSettings()
{
    QSettings settings;
    setColumnWidth( 0, settings.value( objectName() + "/col0", columnWidth( 0 ) ).toInt() );
    setColumnWidth( 1, settings.value( objectName() + "/col1", columnWidth( 1 ) ).toInt() );
    setColumnWidth( 2, settings.value( objectName() + "/col2", columnWidth( 2 ) ).toInt() );
}

void ODBCViewBrowser::writeSettings()
{
    QSettings settings;
    settings.setValue( objectName() + "/col0", columnWidth( 0 ) );
    settings.setValue( objectName() + "/col1", columnWidth( 1 ) );
    settings.setValue( objectName() + "/col2", columnWidth( 2 ) );
}


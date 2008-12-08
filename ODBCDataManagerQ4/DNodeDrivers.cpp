#include "DNodeDrivers.h"

#include "Add32.xpm"
#include "Drivers48.xpm"

DNodeDrivers::DNodeDrivers(  DNodeWidget *pNodeWidget, DNode *pNode )
    : DNode( pNodeWidget, pNode )
{
    setIcon( 0, QIcon( xpmDrivers48 ) );
    setText( 0, QObject::tr( "Drivers" ) );

    pactionAdd = new QAction( QIcon( xpmAdd32 ), "Add", 0 );
    connect( pactionAdd, SIGNAL(triggered()), this, SLOT(slotAdd()) );
}

DNodeDrivers::~DNodeDrivers()
{
    delete pactionAdd;
}

void DNodeDrivers::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionAdd );
}

void DNodeDrivers::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionAdd );
}

void DNodeDrivers::doLoad()
{
    // load children...
    char    szError[FILENAME_MAX+1];
    DWORD   nError;
    char    szResults[4048];
    char    szValue[501];
    char *  ptr;

    /* list Drivers */
    if ( SQLGetPrivateProfileString( NULL, NULL, NULL, szResults, sizeof( szResults ) - 1, "ODBCINST.INI" ) < 1 )
    {
        SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
        printf( "DNodeDrivers: SQLGetPrivateProfileString failed with %s.\n", szError );
        return;
    }
    ptr = szResults;
    while ( *ptr )
    {
        new DNodeDriver( pNodeWidget, this, ptr );
        ptr += strlen( ptr ) + 1;
    }
}

void DNodeDrivers::slotAdd()
{
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
}


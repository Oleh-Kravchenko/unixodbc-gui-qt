/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeDataSourceNames.h"

#include "DNodeDataSourceNameUser.h"
#include "DNodeDataSourceNameSystem.h"
#include "DNodeDataSourceNameFile.h"

#include "Add32.xpm"
#include "DataSourceNames48.xpm"

DNodeDataSourceNames::DNodeDataSourceNames( DNodeWidget *pNodeWidget, DNode *pNode )
    : DNode( pNodeWidget, pNode )
{
    setIcon( 0, QIcon( xpmDataSourceNames48 ) );
    setText( 0, QObject::tr( "Data Source Names" ) );
    setText( 2, QObject::tr( "preconfigured connection profiles" ) );

    pactionAdd = new QAction( QIcon( xpmAdd32 ), "Add", 0 );
    connect( pactionAdd, SIGNAL(triggered()), this, SLOT(slotAdd()) );
}

DNodeDataSourceNames::~DNodeDataSourceNames()
{
    delete pactionAdd;
}

void DNodeDataSourceNames::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionAdd );
}

void DNodeDataSourceNames::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionAdd );
}

void DNodeDataSourceNames::doLoad()
{
    // load User Data Source Names...
    {
        char    szError[FILENAME_MAX+1];
        DWORD   nError;
        char    szSectionNames[4096];
        char    szSectionName[INI_MAX_OBJECT_NAME+1];
        int     nElement;

        // GET SECTION NAMES (Data Sources)
        memset( szSectionNames, 0, sizeof(szSectionNames) );
        SQLSetConfigMode( ODBC_USER_DSN );
        if ( SQLGetPrivateProfileString( NULL, NULL, NULL, szSectionNames, 4090, "odbc.ini" ) >= 0 )
        {
            for ( nElement = 0; iniElement( szSectionNames, '\0', '\0', nElement, szSectionName, INI_MAX_OBJECT_NAME ) == INI_SUCCESS ; nElement++ )
            {
                new DNodeDataSourceNameUser( pNodeWidget, this, szSectionName );
            }
        }
        else
        {
            SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
            printf( "DNodeDataSourceNames: SQLGetPrivateProfileString failed with %s.\n", szError );
        }
    }
    SQLSetConfigMode( ODBC_BOTH_DSN );

    // load System Data Source Names...
    {
        char    szError[FILENAME_MAX+1];
        DWORD   nError;
        char    szSectionNames[4096];
        char    szSectionName[INI_MAX_OBJECT_NAME+1];
        int     nElement;

        // GET SECTION NAMES (Data Sources)
        memset( szSectionNames, 0, sizeof(szSectionNames) );
        SQLSetConfigMode( ODBC_SYSTEM_DSN );
        if ( SQLGetPrivateProfileString( NULL, NULL, NULL, szSectionNames, 4090, "odbc.ini" ) >= 0 )
        {
            for ( nElement = 0; iniElement( szSectionNames, '\0', '\0', nElement, szSectionName, INI_MAX_OBJECT_NAME ) == INI_SUCCESS ; nElement++ )
            {
                new DNodeDataSourceNameSystem( pNodeWidget, this, szSectionName );
            }
        }
        else
        {
            SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
            printf( "DNodeDataSourceNames: SQLGetPrivateProfileString failed with %s.\n", szError );
        }
    }
    SQLSetConfigMode( ODBC_BOTH_DSN );

    // load File Data Source Names...
    {
        char szDirectory[FILENAME_MAX];

        *szDirectory = '\0';
        _odbcinst_FileINI( szDirectory );

        QDir            d( szDirectory, "*.dsn" );
        QFileInfoList   l = d.entryInfoList();
        for ( int i = 0; i < l.size(); ++i )
        {
            new DNodeDataSourceNameFile( pNodeWidget, this, l.at( i ) );
        }
    }
}

void DNodeDataSourceNames::slotAdd()
{
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
}


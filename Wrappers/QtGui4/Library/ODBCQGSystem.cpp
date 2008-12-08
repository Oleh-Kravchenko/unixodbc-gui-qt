/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCQGSystem.h"

ODBCQGSystem::ODBCQGSystem()
    : ODBCQSystem()
{
    setObjectName( "ODBCQGSystem" );
}

ODBCQGSystem::~ODBCQGSystem()
{
}

#ifdef WIN32
bool ODBCQGSystem::doManageDataSources( QWidget *pwidget )
{
    HWND hWnd = ( pwidget ? (HWND)(pwidget->winId()) : NULL );

    if ( !ODBCQSystem::doManageDataSources( hWnd ) )
    {
        QMessageBox::warning( 0, metaObject()->className(),  tr( "Call to SQLManageDataSources returned false." ), QMessageBox::Ok );
        return false;
    }

    return true;
}
#else
#ifdef Q_WS_MACX
bool ODBCQGSystem::doManageDataSources( QWidget * )
{
    if ( !ODBCQSystem::doManageDataSources( NULL ) )
    {
        QMessageBox::warning( 0, metaObject()->className(),  tr( "Failed to execute the ODBC Administrator.\nIt should have been in /Applications/Utilities." ), QMessageBox::Ok );
        return false;
    }

	return true;
}
#else
bool ODBCQGSystem::doManageDataSources( QWidget *pwidgetParent )
{
    if ( !ODBCQSystem::doManageDataSources( (HWND)pwidgetParent ) )
    {
        QMessageBox::warning( pwidgetParent, metaObject()->className(),  tr( "Failed to execute an ODBC Config tool - this sucks but it can easily be corrected.\nSimply ensure that ODBCConfig or gODBCConfig is in your path.\nThese programs are availible on www.sourceforge.com (search for unixODBC)." ), QMessageBox::Ok );
        return false;
    }

    return true;
}
#endif
#endif



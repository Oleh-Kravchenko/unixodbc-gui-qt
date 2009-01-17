/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "OQGSystem.h"

OQGSystem::OQGSystem()
    : OQSystem()
{
    setObjectName( "OQGSystem" );
}

OQGSystem::~OQGSystem()
{
}

#ifdef WIN32
bool OQGSystem::doManageDataSources( QWidget *pwidget )
{
    HWND hWnd = ( pwidget ? (HWND)(pwidget->winId()) : NULL );

    if ( !OQSystem::doManageDataSources( hWnd ) )
    {
        QMessageBox::warning( 0, metaObject()->className(),  tr( "Call to SQLManageDataSources returned false." ), QMessageBox::Ok );
        return false;
    }

    return true;
}
#else
#ifdef Q_WS_MACX
bool OQGSystem::doManageDataSources( QWidget * )
{
    if ( !OQSystem::doManageDataSources( NULL ) )
    {
        QMessageBox::warning( 0, metaObject()->className(),  tr( "Failed to execute the ODBC Administrator.\nIt should have been in /Applications/Utilities." ), QMessageBox::Ok );
        return false;
    }

	return true;
}
#else
bool OQGSystem::doManageDataSources( QWidget *pwidgetParent )
{
    if ( !OQSystem::doManageDataSources( (HWND)pwidgetParent ) )
    {
        QMessageBox::warning( pwidgetParent, metaObject()->className(),  tr( "Failed to execute an ODBC Config tool - this sucks but it can easily be corrected.\nSimply ensure that ODBCConfig or gODBCConfig is in your path.\nThese programs are availible on www.sourceforge.com (search for unixODBC)." ), QMessageBox::Ok );
        return false;
    }

    return true;
}
#endif
#endif



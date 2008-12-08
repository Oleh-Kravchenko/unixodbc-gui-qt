/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGSYSTEM_H
#define ODBCQGSYSTEM_H

#include <QtGui>
#include <ODBCQSystem.h>

/*! 
 * \class   ODBCQGSystem
 * \brief   An ODBC system. 
 *
 *          This extends \sa ODBCQSystem by adding some QtGui based support.
 *          The additional support is very modest but that is all that seems to be needed here.
 */
class ODBCQGSystem : public ODBCQSystem
{
    Q_OBJECT
public:
    explicit ODBCQGSystem();
    virtual ~ODBCQGSystem();

    // DO'rs
    virtual bool doManageDataSources( QWidget *pwidgetParent );    
};

#endif


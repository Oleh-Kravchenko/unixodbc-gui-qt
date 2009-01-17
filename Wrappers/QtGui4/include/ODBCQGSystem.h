/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGSYSTEM_H
#define OQGSYSTEM_H

#include <QtGui>
#include <OQSystem.h>

/*! 
 * \class   OQGSystem
 * \brief   An ODBC system. 
 *
 *          This extends \sa OQSystem by adding some QtGui based support.
 *          The additional support is very modest but that is all that seems to be needed here.
 */
class OQGSystem : public OQSystem
{
    Q_OBJECT
public:
    explicit OQGSystem();
    virtual ~OQGSystem();

    // DO'rs
    virtual bool doManageDataSources( QWidget *pwidgetParent );    
};

#endif


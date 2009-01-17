/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGENVIRONMENT_H
#define OQGENVIRONMENT_H

#include <QtGui>
#include <OQEnvironment.h>

#include "OQGSystem.h"

/*! 
 * \class   OQGEnvironment
 * \brief   An ODBC environment. 
 *
 *          This extends \sa OQEnvironment by adding some QtGui based support.
 *          The additional support is very modest but that is all that seems to be needed here.
 */
class OQGEnvironment : public OQEnvironment
{
    Q_OBJECT
public:
    OQGEnvironment( OQGSystem *pSystem );

};

#endif


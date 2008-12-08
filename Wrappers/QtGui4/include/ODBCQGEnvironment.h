/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGENVIRONMENT_H
#define ODBCQGENVIRONMENT_H

#include <QtGui>
#include <ODBCQEnvironment.h>

#include "ODBCQGSystem.h"

/*! 
 * \class   ODBCQGEnvironment
 * \brief   An ODBC environment. 
 *
 *          This extends \sa ODBCQEnvironment by adding some QtGui based support.
 *          The additional support is very modest but that is all that seems to be needed here.
 */
class ODBCQGEnvironment : public ODBCQEnvironment
{
    Q_OBJECT
public:
    ODBCQGEnvironment( ODBCQGSystem *pSystem );

};

#endif


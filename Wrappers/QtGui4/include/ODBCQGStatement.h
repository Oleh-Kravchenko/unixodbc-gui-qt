/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGSTATEMENT_h
#define ODBCQGSTATEMENT_h

// libqt
#include <QtGui>

#include "../include/ODBCQGConnection.h"
#include <ODBCQStatement.h>

/*! 
 * \class   ODBCQGStatement
 * \brief   An ODBC statement.
 * 
 *          This class extends ODBCQStatement by adding QtGui based features.
 *          A statement does not require any Qt beyond what QtCore offers so this class
 *          exists simply to complete the set of ODBCQG classes. This class does not, at
 *          this time, extend ODBCQStatement in any functional way - but this may change.
 */
class ODBCQGStatement : public ODBCQStatement
{
    Q_OBJECT
public:
    ODBCQGStatement( ODBCQGConnection *pconnection );
};

#endif


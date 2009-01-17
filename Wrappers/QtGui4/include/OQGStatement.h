/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGSTATEMENT_h
#define OQGSTATEMENT_h

// libqt
#include <QtGui>

#include "../include/OQGConnection.h"
#include <OQStatement.h>

/*! 
 * \class   OQGStatement
 * \brief   An ODBC statement.
 * 
 *          This class extends OQStatement by adding QtGui based features.
 *          A statement does not require any Qt beyond what QtCore offers so this class
 *          exists simply to complete the set of OQG classes. This class does not, at
 *          this time, extend OQStatement in any functional way - but this may change.
 */
class OQGStatement : public OQStatement
{
    Q_OBJECT
public:
    OQGStatement( OQGConnection *pconnection );
};

#endif


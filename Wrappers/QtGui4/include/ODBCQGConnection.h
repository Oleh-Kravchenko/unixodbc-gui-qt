/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGCONNECTION_H
#define OQGCONNECTION_H

#include <QtGui>
#include <OQConnection.h>
#include "../include/OQGEnvironment.h"

class OQGProperty;

/*! 
 * \class   OQGConnection
 * \brief   ODBC Connection.
 *
 *          This extends \sa OQConnection by adding QtGui based features.
 * 
 */
class OQGConnection : public OQConnection
{
    Q_OBJECT
public:
    OQGConnection( OQGEnvironment *penvironment );

    // SETTERS

    // GETTERS

    // DOERS
    // we layer these on to provide OQG based prompting
    virtual bool doConnect( QWidget *pwidgetParent, const QString &stringServerName = QString::null, const QString &stringUserName = QString::null, const QString &stringAuthentication = QString::null );
    virtual bool doBrowseConnect( QWidget *pwidgetParent, const QString &stringConnect );
    virtual bool doBrowseConnect( QWidget *pwidgetParent );

protected:

    // Used by doBrowseConnect
    virtual QString getString( QVector<OQGProperty> vectorProperties );
    virtual QVector<OQGProperty> getProperties( const QString &string );
};

#endif


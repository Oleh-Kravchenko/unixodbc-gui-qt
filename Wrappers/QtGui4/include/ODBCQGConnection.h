/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGCONNECTION_H
#define ODBCQGCONNECTION_H

#include <QtGui>
#include <ODBCQConnection.h>
#include "../include/ODBCQGEnvironment.h"

class ODBCQGProperty;

/*! 
 * \class   ODBCQGConnection
 * \brief   ODBC Connection.
 *
 *          This extends \sa ODBCQConnection by adding QtGui based features.
 * 
 */
class ODBCQGConnection : public ODBCQConnection
{
    Q_OBJECT
public:
    ODBCQGConnection( ODBCQGEnvironment *penvironment );

    // SETTERS

    // GETTERS

    // DOERS
    // we layer these on to provide ODBCQG based prompting
    virtual bool doConnect( QWidget *pwidgetParent, const QString &stringServerName = QString::null, const QString &stringUserName = QString::null, const QString &stringAuthentication = QString::null );
    virtual bool doBrowseConnect( QWidget *pwidgetParent, const QString &stringConnect );
    virtual bool doBrowseConnect( QWidget *pwidgetParent );

protected:

    // Used by doBrowseConnect
    virtual QString getString( QVector<ODBCQGProperty> vectorProperties );
    virtual QVector<ODBCQGProperty> getProperties( const QString &string );
};

#endif


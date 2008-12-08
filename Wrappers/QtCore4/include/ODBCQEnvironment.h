/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQENVIRONMENT_H
#define ODBCQENVIRONMENT_H

// libqt
#include <QtCore>

// libodbcplus
#include <ODBCEnvironment.h>
#include <ODBCDiagnostic.h>

//
#include "ODBCQSystem.h"

/*! 
 * \class   ODBCQEnvironment
 * \brief   An ODBC environment.
 *
 *          This class extends ODBCEnvironment by providing a more Qt friendly interface. For
 *          example;
 *
 *          \li uses Qt data types where possible
 *          \li will emit signal when new messages become available
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 * 
 */
class ODBCQEnvironment : public QObject, public ODBCEnvironment
{
    Q_OBJECT
public:
    ODBCQEnvironment( ODBCQSystem *pSystem );
    virtual ~ODBCQEnvironment();

    virtual QStringList getDrivers( SQLRETURN *pnReturn = NULL );
    virtual QStringList getDataSources( bool bUser = true, bool bSystem = true, SQLRETURN *pnReturn = NULL );

signals:
    void signalMessage( ODBCMessage Message );
    void signalDiagnostic( ODBCDiagnostic Diagnostic );

protected:
    virtual void eventMessage( ODBCMessage Message );
    virtual void eventDiagnostic();
};

#endif


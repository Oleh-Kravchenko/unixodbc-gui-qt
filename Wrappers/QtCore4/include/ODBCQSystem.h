/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQSYSTEM_H
#define ODBCQSYSTEM_H

// libqt
#include <QtCore>

// libodbcplus
#include <ODBCSystem.h>
#include <ODBCDiagnostic.h>

/*! 
 *  \def    ODBCQToQString
 *  \brief  This macro is used wherever we need to create a QString from a SQLTCHAR.
 *  
 *          The string data is copied.
 */
/*! 
 *  \def    ODBCQFromQString
 *  \brief  This macro is used wherever we need to get a reference to a QString's data.
 *  
 *          The string data is not copied so the reference is only valid as long as the
 *          QString is not modified. The string data must not be altered.
 */
#ifdef UNICODE
    #define ODBCQToQString( a ) QString::fromWCharArray( (SQLWCHAR*)a )
    #define ODBCQFromQString( a ) (SQLWCHAR*)a.unicode()
#else
    #define ODBCQToQString( a ) QString::fromLocal8Bit( (const char*)a )
    #define ODBCQFromQString( a )(SQLCHAR*)a.toLatin1().constData()
#endif

/*! 
 * \class   ODBCQSystem
 * \brief   An ODBC system.
 *
 *          This class extends ODBCSystem by providing a more Qt friendly interface. For
 *          example;
 *
 *          \li uses Qt data types where possible
 *          \li will emit signal when new messages become available
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 * 
 */
class ODBCQSystem : public QObject, public ODBCSystem
{
    Q_OBJECT
public:
    explicit ODBCQSystem();
    virtual ~ODBCQSystem();

    virtual SQLRETURN setDriverAttribute( const QString &stringDriver, const QString &stringKey, const QString &stringValue );

    virtual QMap<QString,QString> getDriverAttributes( const QString &stringName, SQLRETURN *pnReturn = NULL );

    virtual BOOL doManageDataSources( HWND hWnd );    

signals:
    void signalMessage( ODBCMessage Message );
    void signalDiagnostic( ODBCDiagnostic Diagnostic );
    void signalInstallerError( ODBCSystemError SystemError );

protected:
    void eventError();
};

#endif


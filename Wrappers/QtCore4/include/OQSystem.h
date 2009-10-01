/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#pragma once

#include "OQHandle.h"

/*! 
 * \class   OQSystem
 * \brief   An ODBC system.
 *
 *          This class wraps some ODBC setup & installer functionality.
 *
 *          \li uses Qt data types where possible
 *          \li will emit signal when new messages become available
 *          \li inherits QObject to assist in parent/child relationships using rtti and using signals/slots
 * 
 */
class OQSystem : public OQHandle
{
    Q_OBJECT
public:
    explicit OQSystem();
    virtual ~OQSystem();

    // setters
    virtual SQLRETURN setDriverAttribute( const QString &stringDriver, const QString &stringKey, const QString &stringValue );

    // getters
    virtual QMap<QString,QString> getAttributesDataSource( const QString &stringName, SQLRETURN *pnReturn = NULL );
    virtual QMap<QString,QString> getAttributesInstaller( const QString &stringName, SQLRETURN *pnReturn = NULL );

    virtual QMap<QString,QString> getAttributeDataSource( const QString &stringName, SQLRETURN *pnReturn = NULL );
    virtual QMap<QString,QString> getAttributeInstaller( const QString &stringName, SQLRETURN *pnReturn = NULL );

    // doers
    virtual BOOL doManageDataSources( HWND hWnd );    

protected:
    virtual bool setValue( const QString &stringLocation, const QString &stringSection, const QString &stringKey, const QString &stringValue );

    virtual QStringList getSections( const QString &stringLocation, BOOL *pb );
    virtual QStringList getKeys( const QString &stringLocation, const QString &stringSection, BOOL *pb );
    virtual QString     getValue( const QString &stringSection, const QString &stringKey, BOOL *pb );

};


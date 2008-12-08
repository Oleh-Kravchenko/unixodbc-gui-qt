/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCHANDLE_H
#define ODBCHANDLE_H

#include "ODBC.h"
#include "ODBCMessage.h"

/*! 
 * \brief   An ODBC handle.
 *
 *          This is the base class for key classes in this library. Specifically;
 *
 *          \li ODBCEnvironment
 *          \li ODBCConnection
 *          \li ODBCStatement
 *
 * \sa ODBCEnvironment
 *     ODBCConnection
 *     ODBCStatement
 */
class ODBCHandle
{
public:
    enum Types
    {
        Env = SQL_HANDLE_ENV,
        Dbc = SQL_HANDLE_DBC,
        Stm = SQL_HANDLE_STMT
    };

    explicit ODBCHandle( Types nType, ODBCHandle *phandleParent = NULL );
    virtual ~ODBCHandle();

    Types       getType();
    SQLHANDLE   getHandle();

    virtual SQLRETURN doAlloc();        
    virtual SQLRETURN doFree();         

    bool isAlloc( bool bAlloc = true );

    virtual void eventMessage( ODBCMessage Message );
    virtual void eventDiagnostic();

protected:
    ODBCHandle *phandleParent;
    Types       nType;
    SQLHANDLE   hHandle;
};

#endif


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#pragma once

#include "OQ.h"
#include "OQMessage.h"

/*! 
 * \brief   An ODBC handle.
 *
 *          This is the base class for key classes in this library. Specifically;
 *
 *          \li OQEnvironment
 *          \li OQConnection
 *          \li OQStatement
 *
 * \sa OQEnvironment
 *     OQConnection
 *     OQStatement
 */
class OQHandle
{
public:
    enum Types
    {
        Env = SQL_HANDLE_ENV,
        Dbc = SQL_HANDLE_DBC,
        Stm = SQL_HANDLE_STMT
    };

    explicit OQHandle( Types nType, OQHandle *phandleParent = NULL );
    virtual ~OQHandle();

    Types       getType();
    SQLHANDLE   getHandle();

    virtual SQLRETURN doAlloc();        
    virtual SQLRETURN doFree();         

    bool isAlloc( bool bAlloc = true );

    virtual void eventMessage( OQMessage Message );
    virtual void eventDiagnostic();

protected:
    OQHandle *  phandleParent;
    Types       nType;
    SQLHANDLE   hHandle;
};


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#include "OQHandle.h"

OQHandle::OQHandle( Types nType, OQHandle *phandleParent )
{
    this->nType         = nType;
    this->phandleParent = phandleParent;
    hHandle             = NULL;
}

OQHandle::~OQHandle()
{
    if ( isAlloc( false ) )
        doFree();
}

OQHandle::Types OQHandle::getType()
{
    return nType;
}

SQLHANDLE OQHandle::getHandle()
{
    return hHandle;
}

/*! 
 * \brief   Allocate underlying ODBC handle.
 *
 *          This method is not usually called explicitly from an application since 
 *          it will be silently called via \sa isAlloc as needed.
 *
 *          This method is public to handle any exceptional cases such as when
 *          an app wants to regularly \sa doAlloc and \sa doFree to handle unstable
 *          drivers.
 * 
 * \return  SQLRETURN
 *
 * \sa      doFree
 *          isAlloc
 */
SQLRETURN OQHandle::doAlloc()
{
    if ( isAlloc( false ) )
    {
        eventMessage( OQMessage( OQMessage::Warning, TEXT(__FUNCTION__), TEXT("Already allocated.") ) );
        return SQL_ERROR;
    }

    SQLRETURN nReturn = SQLAllocHandle( nType, ( phandleParent ? phandleParent->getHandle() : SQL_NULL_HANDLE ), &hHandle );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_ERROR") ) );
            hHandle = NULL;
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            hHandle = NULL;
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            hHandle = NULL;
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Free underlying ODBC handle.
 *
 *          Frees resources used to maintain the underlying ODBC handle. Upon success - this will
 *          invalidate any child handles but will not notify them! Errors will be caught but the 
 *          proper way to free a handle is to first ensure that any/all child handles have been
 *          freed.
 *
 *          This method will be silently called in the destructor as needed.
 *
 *          This method is public to handle any exceptional cases such as when
 *          an app wants to regularly \sa doAlloc and \sa doFree to handle unstable
 *          drivers.
 * 
 * \return  SQLRETURN
 *
 * \sa      doAlloc
 *          isAlloc
 */
SQLRETURN OQHandle::doFree()
{
    if ( !isAlloc( false ) )
    {
        eventMessage( OQMessage( OQMessage::Warning, TEXT(__FUNCTION__), TEXT("Already free.") ) );
        return SQL_ERROR;
    }

    SQLRETURN nReturn = SQLFreeHandle( nType, hHandle );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            hHandle = NULL;
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventMessage( OQMessage( OQMessage::Warning, TEXT(__FUNCTION__), TEXT("SQL_SUCCESS_WITH_INFO") ) );
            hHandle = NULL;
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Ensure underlying environment handle is allocated.
 *
 *          We call this at the start of most methods to ensure that we have an allocated
 *          handle to work with.
 * 
 * \param   bAlloc  True if we want to silently allocate it as needed. Default is true.
 *
 * \return  bool
 * \retval  false   Handle was not allocated AND we failed to allocate it.
 * \retval  true    Handle was either allocated OR we succeeded in doing so.
 *
 * \sa      doAlloc
 *          doFree
 */
bool OQHandle::isAlloc( bool bAlloc )
{
    if ( hHandle == NULL )
    {
        if ( !bAlloc )
            return false;
        SQLRETURN nReturn = doAlloc();
        if ( !SQL_SUCCEEDED( nReturn ) )
            return false;
    }

    return true;
}

void OQHandle::eventMessage( OQMessage )
{
    /* do nothing - let derived class decide what to do */
}

void OQHandle::eventDiagnostic()
{
    /* do nothing - let derived class decide what to do */
}



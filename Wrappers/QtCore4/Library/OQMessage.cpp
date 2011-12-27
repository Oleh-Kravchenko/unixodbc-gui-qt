
/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#include "OQMessage.h"

/*! 
 * \brief   Constructs an OQMessage.
 *
 *          This copies and stores the given message information.
 *  
 * \param   nType       Input. One of OQMessage::MessageTypes.
 * \param   pszRequest  Input. Usually function ie "SQLAllocHandle".
 * \param   pszText     Input. Message text. Can be NULL - pref. not.
 * \param   nNumeric    Input. Numeric value dependent upon message.
 *
 */
OQMessage::OQMessage( Types nType, const ODBCCHAR *pszRequest, const ODBCCHAR *pszText, SQLINTEGER nNumeric )
{
    //
    this->nType = nType;

    //
    if ( pszRequest )
    {
        this->pszRequest = (ODBCCHAR*)ODBCStrDup( pszRequest );
    }
    else
        this->pszRequest = 0;

    //
    if ( pszText )
    {
        this->pszText = (ODBCCHAR*)ODBCStrDup( pszText );
    }
    else
        this->pszText = 0;

    //
    this->nNumeric = nNumeric;
}

OQMessage::OQMessage( const OQMessage &Message )
{
    nType = Message.nType;
    if ( Message.pszRequest )
        pszRequest = (ODBCCHAR*)ODBCStrDup( Message.pszRequest );
    else
        pszRequest = NULL;
    if ( Message.pszText )
        pszText = (ODBCCHAR*)ODBCStrDup( Message.pszText );
    else
        pszText = NULL;
    nNumeric = Message.nNumeric;
}

OQMessage::~OQMessage()
{
    if ( pszRequest )
        free( pszRequest );
    if ( pszText )
        free( pszText );
}

/*! 
 * \brief   Message type.
 * 
 *          This can viewed as the message severity if you want.
 * 
 * \return  Types
 *
 * \sa      getTypeText
 */
OQMessage::Types OQMessage::getType() 
{ 
    return nType; 
}

/*! 
 * \brief   Message type text.
 * 
 *          This can be used to format a nicer message.
 * 
 * \return  const ODBCCHAR*
 *
 * \sa      getType
 */
const ODBCCHAR * OQMessage::getTypeText()
{
    switch( nType )
    {
        case Info:
            return TEXT("INFO");
        case Warning:
            return TEXT("WARNING");
        case Error:
            return TEXT("ERROR");
    }

    return TEXT("UNKNOWN");
}

/*! 
 * \brief   Message request.
 * 
 *          The request which generated this message. This is usually a function or method name.
 * 
 * \return  const ODBCCHAR*
 */
const ODBCCHAR *OQMessage::getRequest() 
{ 
    return pszRequest; 
}

/*! 
 * \brief   Message text.
 * 
 *          The message text. This can usually be presented, as is, but
 *          one may want to enhance it using other bits of info from 
 *          OQMessage.
 * 
 * \return  const ODBCCHAR*
 */
const ODBCCHAR *OQMessage::getText() 
{ 
    return pszText; 
}

/*! 
 * \brief   Numeric information.
 * 
 *          The value of this is dependent upon the message context.
 * 
 * \return  SQLINTEGER
 * \retval  -1          Usually (but not always) means null.
 */
SQLINTEGER OQMessage::getNumeric() 
{
    return nNumeric; 
}



/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCMESSAGE_H
#define ODBCMESSAGE_H

#include "ODBC.h"

/*! 
 * \brief   An ODBC message.
 * 
 *          An ODBC message is created by the class library and is provided to the application via
 *          the \sa eventMessage() method. This class compliments \sa ODBCDiagnostic (and the eventDiagnostic()
 *          method) by providing additional diagnostic information. For example; when a request fails due to 
 *          an invalid handle - in such a case no diagnostic information can be found using ODBCDiagnostic. 
 *
 * \sa      ODBCEnvironment
 *          ODBCConnection
 *          ODBCStatement
 */
class ODBCMessage
{
public:
    enum Types 
    { 
        Info = 0,   /*!< the application may ignore this message                    */
        Warning,    /*!< the application may want to pay attention to this message  */ 
        Error       /*!< the application should pay attention to this message       */ 
    };

    ODBCMessage( Types nType, const ODBCCHAR *pszRequest = 0, const ODBCCHAR *pszText = 0, SQLINTEGER nNumeric = 0 );
    ODBCMessage( const ODBCMessage &Message );
    ~ODBCMessage();

    Types               getType();
    const ODBCCHAR *    getRequest();
    const ODBCCHAR *    getText();
    SQLINTEGER          getNumeric();
    const ODBCCHAR *    getTypeText();

protected:
    Types       nType;       /*!< message type \sa Types                                */
    ODBCCHAR *  pszRequest;  /*!< usually function ie SQLAllocHandle                    */
    ODBCCHAR *  pszText;     /*!< message text                                          */
    SQLINTEGER  nNumeric;    /*!< numeric value dependent upon message                  */
};

#endif


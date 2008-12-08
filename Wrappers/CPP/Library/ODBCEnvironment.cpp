/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCEnvironment.h"

/*! 
 * \brief   Constructs an ODBCEnvironment.
 * 
 *          The underlying environment is not allocated until needed or until
 *          an explicit call to \sa doAlloc. An explicit call is not usually
 *          needed.
 *
 * \sa      doAlloc
 */
ODBCEnvironment::ODBCEnvironment()
    : ODBCHandle( ODBCHandle::Env )
{
}

/*! 
 * \brief   Destructs the ODBCEnvironment object.
 * 
 *          The underlying environment is automatically deallocated as needed.
 */
ODBCEnvironment::~ODBCEnvironment()
{
}

/*! 
 * \brief   Sets SQL_ATTR_CONNECTION_POOLING attribute.
 * 
 *          See \sa getAttrConnectionPooling for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \note    Connection pooling not fully implemented here - yet. This does does set
 *          this attribute but does not follow up with the remaining, internal, bits 
 *          we need to do.
 *
 * \param   n   Input. One of \sa ODBCEnvironment::AttrConnectionPoolingTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrConnectionPooling
 */
SQLRETURN ODBCEnvironment::setAttrConnectionPooling( AttrConnectionPoolingTypes n )
{
    return setEnvAttr( SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)n, 0 );
}

/*! 
 * \brief   Sets SQL_ATTR_CP_MATCH attribute.
 * 
 *          See \sa getAttrCPMatch for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \param   n   Input. One of \sa ODBCEnvironment::AttrCPMatchTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrCPMatch
 */
SQLRETURN ODBCEnvironment::setAttrCPMatch( AttrCPMatchTypes n )
{
    return setEnvAttr( SQL_ATTR_CP_MATCH, (SQLPOINTER)n, 0 );
}

/*! 
 * \brief   Sets SQL_ATTR_ODBC_VERSION attribute.
 * 
 *          See \sa getAttrODBCVersion for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \param   n   Input. One of \sa ODBCEnvironment::AttrODBCVersionTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrODBCVersion
 */
SQLRETURN ODBCEnvironment::setAttrODBCVersion( AttrODBCVersionTypes n )
{
    return setEnvAttr( SQL_ATTR_ODBC_VERSION, (SQLPOINTER)n, 0 );
}

/*! 
 * \brief   Sets SQL_ATTR_OUTPUT_NTS attribute.
 * 
 *          See \sa getAttrOutputNTS for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \param   b   Input. Either true or false.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::setAttrOutputNTS( bool b )
{
    return setEnvAttr( SQL_ATTR_OUTPUT_NTS, (SQLPOINTER)b, 0 );
}

/*! 
 * \brief   Set an environment attribute.
 *
 *          Use of this method of setting an attribute guides the coder to using the desired
 *          nAttribute but is not as good as using the more convenient methods such as 
 *          \sa setAttrConnectionPooling etc. 
 * 
 *          This is a convenience method which maps to a call to SQLSetEnvAttr. Using
 *          convenience methods is preferrable to calling other methods since it helps to enforce
 *          valid values. A bonus is that most modern editors will present valid options 
 *          as part of 'code completion' and code comments may also be presented to further
 *          guide coder.
 *
 * \param   nAttribute      Input. One of the \sa ODBCEnvironment::AttributeTypes.
 * \param   pValue          Input. The value (pointer *is* the value for numerics).
 * \param   nStringLength   Input. Number of chars at pValue in case where pValue points to a string.
 * 
 * \return  SQLRETURN
 *
 * \sa      setAttrConnectionPooling
 *          setAttrCPMatch
 *          setAttrODBCVersion
 *          setAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::setEnvAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    return setEnvAttr( (SQLINTEGER)nAttribute, pValue, nStringLength );
}

/*! 
 * \brief   Set an environment attribute.
 *
 *          Use of this method of setting an attribute is discouraged. Please consider using
 *          the more convenient methods such as \sa setAttrConnectionPooling etc. This method
 *          can be used to set non-standard environment attributes.
 * 
 * \param   nAttribute      Input. A viable environment attribute such as; SQL_ATTR_CONNECTION_POOLING.
 * \param   pValue          Input. The value (pointer *is* the value for numerics).
 * \param   nStringLength   Input. Number of chars at pValue in case where pValue points to a string.
 * 
 * \return  SQLRETURN
 * 
 * \sa      setAttrConnectionPooling
 *          setAttrCPMatch
 *          setAttrODBCVersion
 *          setAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::setEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLSetEnvAttr( getHandle(), nAttribute, pValue, nStringLength );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Get SQL_ATTR_CONNECTION_POOLING attribute.
 * 
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 *          Any error messages generated during this call will be captured to
 *          the message list.
 *
 *          A default value will be returned in the event of an error. The default value
 *          will often be a valid representation of the facts - but not always. The caller
 *          is relying more on the extreme likelihood that no error will occur for this call.
 * 
 * \param   pnReturn    Input. Pointer to mem to return SQLRETURN value. Ignored if NULL.
 *
 * \return  ODBCEnvironment::AttrConnectionPoolingTypes
 *
 * \sa      setAttrConnectionPooling
 */
ODBCEnvironment::AttrConnectionPoolingTypes ODBCEnvironment::getAttrConnectionPooling( SQLRETURN *pnReturn )
{
    AttrConnectionPoolingTypes n = CPOff;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_CONNECTION_POOLING, &n, 0, NULL );
    if ( pnReturn ) *pnReturn = nReturn;

    return n;
}

/*! 
 * \brief   Get SQL_ATTR_CP_MATCH attribute.
 * 
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 *          Any error messages generated during this call will be captured to
 *          the message list.
 *
 *          A default value will be returned in the event of an error. The default value
 *          will often be a valid representation of the facts - but not always. The caller
 *          is relying more on the extreme likelihood that no error will occur for this call.
 * 
 * \param   pnReturn    Input. Pointer to mem to return SQLRETURN value. Ignored if NULL.
 *
 * \return  ODBCEnvironment::AttrCPMatchTypes
 *
 * \sa      setAttrCPMatch
 */
ODBCEnvironment::AttrCPMatchTypes ODBCEnvironment::getAttrCPMatch( SQLRETURN *pnReturn )
{
    AttrCPMatchTypes n = CPStrictMatch;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_CP_MATCH, &n, 0, NULL );
    if ( pnReturn ) *pnReturn = nReturn;

    return n;
}

/*! 
 * \brief   Get SQL_ATTR_ODBC_VERSION attribute.
 * 
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 *          Any error messages generated during this call will be captured to
 *          the message list.
 *
 *          A default value will be returned in the event of an error. The default value
 *          will often be a valid representation of the facts - but not always. The caller
 *          is relying more on the extreme likelihood that no error will occur for this call.
 * 
 * \param   pnReturn    Input. Pointer to mem to return SQLRETURN value. Ignored if NULL.
 *
 * \return  ODBCEnvironment::AttrODBCVersionTypes
 *
 * \sa      setAttrODBCVersion
 */
ODBCEnvironment::AttrODBCVersionTypes ODBCEnvironment::getAttrODBCVersion( SQLRETURN *pnReturn )
{
    AttrODBCVersionTypes n = OVOdbc3;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_ODBC_VERSION, &n, 0, NULL );
    if ( pnReturn ) *pnReturn = nReturn;

    return n;
}

/*! 
 * \brief   Get SQL_ATTR_OUTPUT_NTS attribute.
 * 
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 *          Any error messages generated during this call will be captured to
 *          the message list.
 *
 *          A default value will be returned in the event of an error. The default value
 *          will often be a valid representation of the facts - but not always. The caller
 *          is relying more on the extreme likelihood that no error will occur for this call.
 * 
 * \param   pnReturn    Input. Pointer to mem to return SQLRETURN value. Ignored if NULL.
 *
 * \return  bool
 *
 * \sa      setAttrOutputNTS
 */
bool ODBCEnvironment::getAttrOutputNTS( SQLRETURN *pnReturn )
{
    bool b = true;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_OUTPUT_NTS, &b, 0, NULL );
    if ( pnReturn ) *pnReturn = nReturn;

    return b;
}

/*! 
 * \brief   Get SQL_ATTR_CONNECTION_POOLING attribute.
 *
 *          Determines if connection pooling is enabled and if so - how it is to be done.
 *
 *          \li \c CPOff Default. Connection pooling is turned off.
 *          \li \c CPOnePerDriver A single connection pool is supported for each driver. Every connection in a pool is associated with one driver.
 *          \li \c CPOnePerHenv A single connection pool is supported for each environment. Every connection in a pool is associated with one environment.
 *
 *          This is the recommended method to get this attribute.
 *
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 * \param   pb  Output. Pointer to space to return attribute value.
 * 
 * \return  SQLRETURN
 *
 * \sa      setAttrConnectionPooling
 */
SQLRETURN ODBCEnvironment::getAttrConnectionPooling( AttrConnectionPoolingTypes *pn )
{
    return getEnvAttr( SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)pn, 0, NULL );
}

/*! 
 * \brief   Get SQL_ATTR_CP_MATCH attribute.
 *
 *          Determines how a connection is chosen from a connection pool. When connect is called, the Driver 
 *          Manager determines which connection is reused from the pool. The Driver Manager tries to match 
 *          the connection options in the call and the connection attributes set by the application to the 
 *          keywords and connection attributes of the connections in the pool. The value of this attribute 
 *          determines the level of precision of the matching criteria.
 *
 *          \li \c CPStrictMatch Default. Only connections that exactly match the connection options in the call and the connection attributes set by the application are reused.
 *          \li \c CPRelaxedMatch Connections with matching connection string keywords can be used. Keywords must match, but not all connection attributes must match.
 *
 *          This is the recommended method to get this attribute.
 *
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 * \param   pb  Output. Pointer to space to return attribute value.
 * 
 * \return  SQLRETURN
 *
 * \sa      setAttrCPMatch
 */
SQLRETURN ODBCEnvironment::getAttrCPMatch( AttrCPMatchTypes *pn )
{
    return getEnvAttr( SQL_ATTR_CP_MATCH, (SQLPOINTER)pn, 0, NULL );
}

/*! 
 * \brief   Get SQL_ATTR_ODBC_VERSION attribute.
 *
 *          Determines whether certain functionality exhibits ODBC 2.x behavior or ODBC 3.x behavior. 
 *
 *          \li \c OVOdbc3 Default. The Driver Manager and driver exhibit some ODBC 3.x behavior.
 *          \li \c OVOdbc2 The Driver Manager and driver exhibit some ODBC 2.x behavior.
 *
 * \note    The ODBC specification says that any ODBC3 code needs to set this attribute after the 
 *          environment is allocated. We, silently, do this on behalf of the application because we
 *          are ODBC3 code and most probably - the application is as well. The application can override
 *          this as needed by calling setAttrODBCVersion method with OVOdbc2.
 *
 *          This is the recommended method to get this attribute.
 *
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 * \param   pb  Output. Pointer to space to return attribute value.
 * 
 * \return  SQLRETURN
 *
 * \sa      setAttrODBCVersion
 */
SQLRETURN ODBCEnvironment::getAttrODBCVersion( AttrODBCVersionTypes *pn )
{
    return getEnvAttr( SQL_ATTR_ODBC_VERSION, (SQLPOINTER)pn, 0, NULL );
}

/*! 
 * \brief   Get SQL_ATTR_OUTPUT_NTS attribute.
 *
 *          Determines how the driver returns string data. 
 * 
 *          \li \c true Default. The driver returns string data null-terminated.
 *          \li \c false The driver does not return string data null-terminated.
 *
 *          This is the recommended method to get this attribute.
 *
 *          This method is a convenience method which calls SQLGetEnvAttr.
 *
 * \note    This attribute can not be changed on MS platforms.
 *
 * \param   pb  Output. Pointer to space to return attribute value.
 * 
 * \return  SQLRETURN
 *
 * \sa      setAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::getAttrOutputNTS( bool *pb )
{
    return getEnvAttr( SQL_ATTR_OUTPUT_NTS, (SQLPOINTER)pb, 0, NULL );
}

/*! 
 * \brief   Get an environment attribute.
 *
 *          Use of this method of getting an attribute guides the coder to using the desired
 *          nAttribute but is not as good as using the more convenient methods such as 
 *          \sa getAttrConnectionPooling etc. 
 * 
 *          This is a convenience method which maps to a call to SQLGetEnvAttr. Using
 *          convenience methods is preferrable to calling other methods since it helps to enforce
 *          valid values. A bonus is that most modern editors will present valid options 
 *          as part of 'code completion' and code comments may also be presented to further
 *          guide coder.
 *
 * \param   nAttribute      Input. One of the \sa ODBCEnvironment::AttributeTypes.
 * \param   pValue          Output. Pointer to a buffer in which to get the desired value.
 * \param   nBufferLength   Input. The number of bytes we can use at pValue.
 * \param   pnStringLength  Output. The number of chars available if value is a string.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrConnectionPooling
 *          getAttrCPMatch
 *          getAttrODBCVersion
 *          getAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::getEnvAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength )
{
    return getEnvAttr( (SQLINTEGER)nAttribute, pValue, nBufferLength, pnStringLength );
}

/*! 
 * \brief   Get an environment attribute.
 *
 *          Use of this method of getting an environment attribute is discouraged. Please consider using
 *          the more convenient methods such as \sa getAttrConnectionPooling etc. This method
 *          can be used to get non-standard environment attributes.
 * 
 * \param   nAttribute      Input. A viable environment attribute such as; SQL_ATTR_CONNECTION_POOLING.
 * \param   pValue          Output. Pointer to a buffer in which to get the desired value.
 * \param   nBufferLength   Input. The number of bytes we can use at pValue.
 * \param   pnStringLength  Output. The number of chars available if value is a string.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrConnectionPooling
 *          getAttrCPMatch
 *          getAttrODBCVersion
 *          getAttrOutputNTS
 */
SQLRETURN ODBCEnvironment::getEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN nReturn = SQLGetEnvAttr( getHandle(), nAttribute, pValue, nBufferLength, pnStringLength );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Gets driver information.
 *
 *          This call maps to SQLDriver. The underlying environment is silently allocated
 *          as needed. Any error messages generated from this call is retrieved from 
 *          ODBC and appended to the ODBCEnvironment's list of errors for subsequent query.
 * 
 * \param   nDirection
 * \param   pszDriverDescription
 * \param   nBufferLength1
 * \param   pnDescriptionLengthPtr
 * \param   pszDriverAttributes
 * \param   nBufferLength2
 * \param   pnAttributesLengthPtr
 * 
 * \return  SQLRETURN
 */
SQLRETURN ODBCEnvironment::doDrivers( SQLUSMALLINT nDirection, ODBCCHAR *pszDriverDescription, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnDescriptionLengthPtr, ODBCCHAR *pszDriverAttributes, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnAttributesLengthPtr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    //
    SQLRETURN nReturn = SQLDrivers( getHandle(), nDirection, pszDriverDescription, nBufferLength1, pnDescriptionLengthPtr, pszDriverAttributes, nBufferLength2, pnAttributesLengthPtr );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Get data source information.
 *
 *          This call maps to SQLDataSources. The underlying environment is silently allocated
 *          as needed. Any error messages generated from this call are retrieved from 
 *          ODBC and appended to the ODBCEnvironment's list of errors for subsequent query.
 * 
 * \param   nDirection
 * \param   pszServerName
 * \param   nBufferLength1
 * \param   pnNameLength1Ptr
 * \param   pszDescription
 * \param   nBufferLength2
 * \param   pnNameLength2Ptr
 * 
 * \return  SQLRETURN
 */
SQLRETURN ODBCEnvironment::doDataSources( SQLUSMALLINT nDirection, ODBCCHAR *pszServerName, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnNameLength1Ptr, ODBCCHAR *pszDescription, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnNameLength2Ptr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    //
    SQLRETURN nReturn = SQLDataSources( getHandle(), nDirection, pszServerName, nBufferLength1, pnNameLength1Ptr, pszDescription, nBufferLength2, pnNameLength2Ptr );
    switch ( nReturn )
    {
        case SQL_SUCCESS:
        case SQL_NO_DATA:
            break;
        case SQL_SUCCESS_WITH_INFO:
            eventDiagnostic();
            break;
        case SQL_ERROR:
            eventDiagnostic();
            break;
        case SQL_INVALID_HANDLE:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( ODBCMessage( ODBCMessage::Error, TEXT(__FUNCTION__), TEXT("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Allocate underlying ODBC environment handle.
 *
 *          We use ODBCHandle::doAlloc but follow it up with a call to set ODBC version to v3.
 * 
 * \return  SQLRETURN
 *
 * \sa      ODBCHandle::doAlloc
 */
SQLRETURN ODBCEnvironment::doAlloc()
{
    SQLRETURN nReturn = ODBCHandle::doAlloc();

    // we must set this as we use ODBC v3 features
    if ( SQL_SUCCEEDED( nReturn ) )
        setEnvAttr( SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0 ); 

    return nReturn;
}



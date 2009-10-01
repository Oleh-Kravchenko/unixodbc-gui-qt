/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "OQEnvironment.h"

OQEnvironment::OQEnvironment( OQSystem *pSystem )
    : OQHandle( Env, pSystem )
{
    setObjectName( "OQEnvironment" );

    // echo up the object hierarchy
    connect( this, SIGNAL(signalMessage(OQMessage)), pSystem, SIGNAL(signalMessage(OQMessage)) );
    connect( this, SIGNAL(signalDiagnostic(OQDiagnostic)), pSystem, SIGNAL(signalDiagnostic(OQDiagnostic)) );
}

OQEnvironment::~OQEnvironment()
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
 * \param   n   Input. One of \sa OQEnvironment::AttrConnectionPoolingTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrConnectionPooling
 */
SQLRETURN OQEnvironment::setAttrConnectionPooling( AttrConnectionPoolingTypes n )
{
    return setEnvAttr( SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)n );
}

/*! 
 * \brief   Sets SQL_ATTR_CP_MATCH attribute.
 * 
 *          See \sa getAttrCPMatch for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \param   n   Input. One of \sa OQEnvironment::AttrCPMatchTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrCPMatch
 */
SQLRETURN OQEnvironment::setAttrCPMatch( AttrCPMatchTypes n )
{
    return setEnvAttr( SQL_ATTR_CP_MATCH, (SQLPOINTER)n );
}

/*! 
 * \brief   Sets SQL_ATTR_ODBC_VERSION attribute.
 * 
 *          See \sa getAttrODBCVersion for information about this attribute.
 *
 *          This is a convenience method which maps to SQLSetEnvAttr.
 *
 * \param   n   Input. One of \sa OQEnvironment::AttrODBCVersionTypes.
 * 
 * \return  SQLRETURN
 *
 * \sa      getAttrODBCVersion
 */
SQLRETURN OQEnvironment::setAttrODBCVersion( AttrODBCVersionTypes n )
{
    return setEnvAttr( SQL_ATTR_ODBC_VERSION, (SQLPOINTER)n );
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
SQLRETURN OQEnvironment::setAttrOutputNTS( bool b )
{
    return setEnvAttr( SQL_ATTR_OUTPUT_NTS, (SQLPOINTER)b );
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
 * \return  OQEnvironment::AttrConnectionPoolingTypes
 *
 * \sa      setAttrConnectionPooling
 */
OQEnvironment::AttrConnectionPoolingTypes OQEnvironment::getAttrConnectionPooling( SQLRETURN *pnReturn )
{
    AttrConnectionPoolingTypes n = CPOff;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_CONNECTION_POOLING, &n );
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
 * \return  OQEnvironment::AttrCPMatchTypes
 *
 * \sa      setAttrCPMatch
 */
OQEnvironment::AttrCPMatchTypes OQEnvironment::getAttrCPMatch( SQLRETURN *pnReturn )
{
    AttrCPMatchTypes n = CPStrictMatch;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_CP_MATCH, &n );
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
 * \return  OQEnvironment::AttrODBCVersionTypes
 *
 * \sa      setAttrODBCVersion
 */
OQEnvironment::AttrODBCVersionTypes OQEnvironment::getAttrODBCVersion( SQLRETURN *pnReturn )
{
    AttrODBCVersionTypes n = OVOdbc3;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_ODBC_VERSION, &n );
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
bool OQEnvironment::getAttrOutputNTS( SQLRETURN *pnReturn )
{
    bool b = true;

    SQLRETURN nReturn = getEnvAttr( SQL_ATTR_OUTPUT_NTS, &b );
    if ( pnReturn ) *pnReturn = nReturn;

    return b;
}

QStringList OQEnvironment::getDrivers( SQLRETURN *pnReturn )
{
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
    QStringList     stringlistDrivers;
    SQLRETURN       nReturn;
    SQLTCHAR        szDRV[100];
    SQLSMALLINT     nLength1;
    SQLTCHAR        szAttribute[300];
    SQLSMALLINT     nLength2;

printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
    nReturn = doDrivers( SQL_FETCH_FIRST, szDRV, sizeof(szDRV) / sizeof(SQLTCHAR), &nLength1, szAttribute, sizeof(szAttribute)  / sizeof(SQLTCHAR), &nLength2 );
printf( "[PAH][%s][%d] %d\n", __FILE__, __LINE__, nReturn );
    while ( SQL_SUCCEEDED( nReturn ) )
    {
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
        stringlistDrivers.append( OQToQString( szDRV ) );
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
        nReturn = doDrivers( SQL_FETCH_NEXT, szDRV, sizeof(szDRV) / sizeof(SQLTCHAR), &nLength1, szAttribute, sizeof(szAttribute) / sizeof(SQLTCHAR), &nLength2 );
printf( "[PAH][%s][%d] %d\n", __FILE__, __LINE__, nReturn );
    }

printf( "[PAH][%s][%d] %d\n", __FILE__, __LINE__, stringlistDrivers.size() );
    if ( pnReturn )
        *pnReturn = nReturn;

    return stringlistDrivers;
}

/*!
    Qt friendly way to get a list of DSN's. 
*/
QStringList OQEnvironment::getDataSources( bool bUser, bool bSystem, SQLRETURN *pnReturn )
{
    QStringList     stringlistDataSources;
    SQLRETURN       nReturn;
    SQLUSMALLINT    nDirection  =   SQL_FETCH_FIRST;
    SQLTCHAR        szDSN[100];
    SQLSMALLINT     nLength1;
    SQLTCHAR        szDescription[100];
    SQLSMALLINT     nLength2;

    if ( bUser || bSystem )
    {
#ifndef Q_WS_MACX
        if ( !bUser && bSystem )
            nDirection = SQL_FETCH_FIRST_SYSTEM;
        else if ( bUser && !bSystem )
            nDirection = SQL_FETCH_FIRST_USER;
#endif

        nReturn = doDataSources( nDirection, szDSN, sizeof(szDSN) / sizeof(SQLTCHAR), &nLength1, szDescription, sizeof(szDescription) / sizeof(SQLTCHAR), &nLength2 );
        while ( SQL_SUCCEEDED( nReturn ) )
        {
            stringlistDataSources += OQToQString(szDSN);
            nReturn = doDataSources( SQL_FETCH_NEXT, szDSN, sizeof(szDSN) / sizeof(SQLTCHAR), &nLength1, szDescription, sizeof(szDescription) / sizeof(SQLTCHAR), &nLength2 );
        }
    }
    else
        nReturn = SQL_NO_DATA;

    if ( pnReturn )
        *pnReturn = nReturn;

    return stringlistDataSources;
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
SQLRETURN OQEnvironment::setEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLRETURN   nReturn = SQLSetEnvAttr( hHandle, nAttribute, pValue, 0 );
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
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
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
SQLRETURN OQEnvironment::getEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    SQLINTEGER  nBufferLength   = 0;
    SQLINTEGER  nStringLength   = 0;
    SQLRETURN   nReturn = SQLGetEnvAttr( hHandle, nAttribute, pValue, nBufferLength, &nStringLength );
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
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}

/*! 
 * \brief   Gets driver information.
 *
 *          This call maps to SQLDriver.
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
SQLRETURN OQEnvironment::doDrivers( SQLUSMALLINT nDirection, SQLTCHAR *pszDriverDescription, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnDescriptionLengthPtr, SQLTCHAR *pszDriverAttributes, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnAttributesLengthPtr )
{
printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
    if ( !isAlloc() )
        return SQL_ERROR;

printf( "[PAH][%s][%d] %p\n", __FILE__, __LINE__, hHandle );
    //
    SQLRETURN nReturn = SQLDrivers( hHandle, nDirection, pszDriverDescription, nBufferLength1, pnDescriptionLengthPtr, pszDriverAttributes, nBufferLength2, pnAttributesLengthPtr );
printf( "[PAH][%s][%d] %d\n", __FILE__, __LINE__, nReturn );
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
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

printf( "[PAH][%s][%d]\n", __FILE__, __LINE__ );
    return nReturn;
}

/*! 
 * \brief   Get data source information.
 *
 *          This call maps to SQLDataSources.
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
SQLRETURN OQEnvironment::doDataSources( SQLUSMALLINT nDirection, SQLTCHAR *pszServerName, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnNameLength1Ptr, SQLTCHAR *pszDescription, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnNameLength2Ptr )
{
    if ( !isAlloc() )
        return SQL_ERROR;

    //
    SQLRETURN nReturn = SQLDataSources( hHandle, nDirection, pszServerName, nBufferLength1, pnNameLength1Ptr, pszDescription, nBufferLength2, pnNameLength2Ptr );
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
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("SQL_INVALID_HANDLE") ) );
            break;
        default:
            eventMessage( OQMessage( OQMessage::Error, QString(__FUNCTION__), QString("Unexpected SQLRETURN value."), nReturn ) );
            break;
    }

    return nReturn;
}



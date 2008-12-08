/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCENVIRONMENT_H
#define ODBCENVIRONMENT_H

#include "ODBCHandle.h"
#include "ODBCConnection.h"

/*! 
 * \brief   An ODBC environment.
 *
 *          This class provides a very thin wrapper to SQLHENV. Using this class is
 *          more convenient for C++ developers (and those with modern code editors)
 *          than using the SQLHENV directly. 
 * 
 * \sa      ODBCConnection
 *          ODBCStatement
 */
class ODBCEnvironment : public ODBCHandle
{
public:
    enum AttributeTypes
    {
        AttrConnectionPooling   = SQL_ATTR_CONNECTION_POOLING,  /*!< On/off/type of connection pooling.         */
        AttrCPMatch             = SQL_ATTR_CP_MATCH,            /*!< Type of matching for connection pooling.   */
        AttrODBCVersion         = SQL_ATTR_ODBC_VERSION,        /*!< ODBC version conforming to.                */
        AttrOutputNTS           = SQL_ATTR_OUTPUT_NTS           /*!< Are strings null terminated.               */
    };

    enum AttrConnectionPoolingTypes
    {
        CPOff           = SQL_CP_OFF,               /*!< Connection pooling is turned off. This is the default.                                                                     */
        CPOnePerDriver  = SQL_CP_ONE_PER_DRIVER,    /*!< A single connection pool is supported for each driver. Every connection in a pool is associated with one driver.           */
        CPOnePerHenv    = SQL_CP_ONE_PER_HENV       /*!< A single connection pool is supported for each environment. Every connection in a pool is associated with one environment. */
    };

    enum AttrCPMatchTypes
    {
        CPStrictMatch   = SQL_CP_STRICT_MATCH,      /*!< Only connections that exactly match the connection options in the call and the connection attributes set by the application are reused. This is the default.   */
        CPRelaxedMatch  = SQL_CP_RELAXED_MATCH      /*!< Connections with matching connection string keywords can be used. Keywords must match, but not all connection attributes must match.                           */
    };

    enum AttrODBCVersionTypes
    {
        OVOdbc3 = SQL_OV_ODBC3,                     /*!< The Driver Manager and driver exhibit some ODBC 3.x behavior.  */
        OVOdbc2 = SQL_OV_ODBC2                      /*!< The Driver Manager and driver exhibit some ODBC 2.x behavior.  */
    };

    explicit ODBCEnvironment();
    virtual ~ODBCEnvironment();

    virtual SQLRETURN setAttrConnectionPooling( AttrConnectionPoolingTypes n = CPOff );
    virtual SQLRETURN setAttrCPMatch( AttrCPMatchTypes n = CPStrictMatch );
    virtual SQLRETURN setAttrODBCVersion( AttrODBCVersionTypes n );
    virtual SQLRETURN setAttrOutputNTS( bool b = SQL_TRUE );
    virtual SQLRETURN setEnvAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );
    virtual SQLRETURN setEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nStringLength );

    virtual AttrConnectionPoolingTypes  getAttrConnectionPooling( SQLRETURN *pnReturn = NULL );
    virtual AttrCPMatchTypes            getAttrCPMatch( SQLRETURN *pnReturn = NULL );
    virtual AttrODBCVersionTypes        getAttrODBCVersion( SQLRETURN *pnReturn = NULL );
    virtual bool                        getAttrOutputNTS( SQLRETURN *pnReturn = NULL );
    virtual SQLRETURN                   getAttrConnectionPooling( AttrConnectionPoolingTypes *pn );
    virtual SQLRETURN                   getAttrCPMatch( AttrCPMatchTypes *pn );
    virtual SQLRETURN                   getAttrODBCVersion( AttrODBCVersionTypes *pn );
    virtual SQLRETURN                   getAttrOutputNTS( bool *pb );
    virtual SQLRETURN                   getEnvAttr( AttributeTypes nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength );
    virtual SQLRETURN                   getEnvAttr( SQLINTEGER nAttribute, SQLPOINTER pValue, SQLINTEGER nBufferLength, SQLINTEGER *pnStringLength );

    virtual SQLRETURN   doDrivers( SQLUSMALLINT nDirection, ODBCCHAR *pszDriverDescription, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnDescriptionLengthPtr, ODBCCHAR *pszDriverAttributes, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnAttributesLengthPtr );
    virtual SQLRETURN   doDataSources( SQLUSMALLINT nDirection, ODBCCHAR *pszServerName, SQLSMALLINT nBufferLength1, SQLSMALLINT *pnNameLength1Ptr, ODBCCHAR *pszDescription, SQLSMALLINT nBufferLength2, SQLSMALLINT *pnNameLength2Ptr );
    virtual SQLRETURN   doAlloc();        
};

#endif




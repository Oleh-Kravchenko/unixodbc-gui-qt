/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "ODBCMetaInfo.h"

ODBCMetaInfoAttr ODBCSysAttr[] =
{
    {
        0, NULL, NULL, NULL, 0, true, NULL
    }
};

ODBCMetaInfoAttrValue ODBCEnvAttrConnectionPooling[] =
{
    { SQL_CP_OFF,               "SQL_CP_OFF",               "Off",                  "Connection pooling is turned off."      },
    { SQL_CP_ONE_PER_DRIVER,    "SQL_CP_ONE_PER_DRIVER",    "OnePerDriver",         "A single connection pool is supported for each driver. Every connection in a pool is associated with one driver."              },
    { SQL_CP_ONE_PER_HENV,      "SQL_CP_ONE_PER_HENV",      "OnePerEnvironment",    "A single connection pool is supported for each environment. Every connection in a pool is associated with one environment."    },
    { 0, NULL, NULL, NULL }
};

ODBCMetaInfoAttrValue ODBCEnvAttrCpMatch[] =
{
    { SQL_CP_STRICT_MATCH,  "SQL_CP_STRICT_MATCH",  "StrictMatch",  "Only connections that exactly match the connection options in the call and the connection attributes set by the application are reused."   },
    { SQL_CP_RELAXED_MATCH, "SQL_CP_RELAXED_MATCH", "RelaxedMatch", "Connections with matching connection string keywords can be used. Keywords must match, but not all connection attributes must match."      },
    { 0, NULL, NULL, NULL }
};

ODBCMetaInfoAttrValue ODBCEnvAttrOdbcVersion[] =
{
    { SQL_OV_ODBC3, "SQL_OV_ODBC3", "OvOdbc3", "Driver Manager and Driver exhibit ODBC Version 3 behaviour."  },
    { SQL_OV_ODBC2, "SQL_OV_ODBC2", "OvOdbc2", "Driver Manager and Driver exhibit ODBC Version 2 behaviour."  },
    { 0, NULL, NULL, NULL }
};

ODBCMetaInfoAttrValue ODBCEnvAttrOutputNts[] =
{
    { SQL_TRUE,     "SQL_TRUE",     "True",     "Driver returns string data null-terminated."           },
    { SQL_FALSE,    "SQL_FALSE",    "False",    "Driver does not return string data null-terminated."   },
    { 0, NULL, NULL, NULL }
};

ODBCMetaInfoAttr ODBCEnvAttr[] =
{
    {
        SQL_ATTR_CONNECTION_POOLING,
        "SQL_ATTR_CONNECTION_POOLING",
        "ConnectionPooling",
        "Enables/disables connection pooling at the environment level. Often used when an application is a server process. Requires a good, stable, driver.",
        SQL_IS_UINTEGER,
        false,
        ODBCEnvAttrConnectionPooling
    },
    {
        SQL_ATTR_CP_MATCH,
        "SQL_ATTR_CP_MATCH",
        "CpMatch",
        "Determines how a connection is chosen from a connection pool.",
        SQL_IS_UINTEGER,
        false,
        ODBCEnvAttrCpMatch
    },
    {
        SQL_ATTR_ODBC_VERSION,
        "SQL_ATTR_ODBC_VERSION",
        "OdbcVersion",
        "Determines how certian functionality behaves.",
        SQL_IS_INTEGER,
        true,   // we set to ODBCv3 and we do not want that to change so make readonly
        ODBCEnvAttrOdbcVersion
    },
    {
        SQL_ATTR_OUTPUT_NTS,
        "SQL_ATTR_OUTPUT_NTS",
        "OutputNts",
        "Determines how the driver returns string data.",
        SQL_IS_SMALLINT,
        true,
        ODBCEnvAttrOutputNts
    },
    {
        0, NULL, NULL, NULL, 0, true, NULL
    }
};

ODBCMetaInfoAttr *ODBCMetaInfo::getSysAttr()
{
    return ODBCSysAttr;
}

ODBCMetaInfoAttr *ODBCMetaInfo::getEnvAttr()
{
    return ODBCEnvAttr;
}

ODBCMetaInfoAttr *ODBCMetaInfo::getAttr( ODBCMetaInfoAttr *pAttr, enumAttrFields nField, QVariant v )
{
    while ( pAttr && pAttr->pszCasualName )
    {
        switch ( nField )
        {
            case AttrFieldNumeric:
                if ( v == pAttr->nNumeric )
                    return pAttr;
                break;
            case AttrFieldFormalName:
                if ( v == pAttr->pszFormalName )
                    return pAttr;
                break;
            case AttrFieldCasualName:
                if ( v == pAttr->pszCasualName )
                    return pAttr;
                break;
        }
        pAttr++;
    }

    return NULL;
}

ODBCMetaInfoAttrValue *ODBCMetaInfo::getAttrValue( ODBCMetaInfoAttr *pAttr, enumAttrFields nField, QVariant v )
{
    if ( !pAttr )
        return NULL;

    ODBCMetaInfoAttrValue *p = pAttr->pValues;
    int n = 0;
    while ( p && p[n].pszCasualName )
    {
        switch ( nField )
        {
            case AttrFieldNumeric:
                switch ( pAttr->nValueType )
                {
                    case SQL_IS_INTEGER:
                        if ( v == p[n].Numeric.nInteger )
                            return &(p[n]);
                        break;
                    case SQL_IS_UINTEGER:
                        if ( v == p[n].Numeric.nUnsignedInteger )
                            return &(p[n]);
                        break;
                    case SQL_IS_SMALLINT:
                        if ( v == p[n].Numeric.nSmallInteger )
                            return &(p[n]);
                        break;
                }
                break;
            case AttrFieldFormalName:
                if ( v == p[n].pszFormalName )
                    return &(p[n]);
                break;
            case AttrFieldCasualName:
                if ( v == p[n].pszCasualName )
                    return &(p[n]);
                break;
        }
        n++;
    }

    return NULL;
}

QVector<QVariant> ODBCMetaInfo::getAttrValues( ODBCMetaInfoAttr *pAttr, enumAttrFields nField )
{
    QVector<QVariant>           vectorValues;
    ODBCMetaInfoAttrValue *     p = pAttr->pValues;
    int n = 0;

    while ( p && p[n].pszCasualName )
    {
        switch ( nField )
        {
            case AttrFieldNumeric:
                switch ( pAttr->nValueType )
                {
                    case SQL_IS_INTEGER:
                        vectorValues.append( QVariant( p[n].Numeric.nInteger ) );
                        break;
                    case SQL_IS_UINTEGER:
                        vectorValues.append( QVariant( p[n].Numeric.nUnsignedInteger ) );
                        break;
                    case SQL_IS_SMALLINT:
                        vectorValues.append( QVariant( p[n].Numeric.nSmallInteger ) );
                        break;
                }
                break;
            case AttrFieldFormalName:
                vectorValues.append( QVariant( p[n].pszFormalName ) );
                break;
            case AttrFieldCasualName:
                vectorValues.append( QVariant( p[n].pszCasualName ) );
                break;
            case AttrFieldDescription:
                vectorValues.append( QVariant( p[n].pszDescription ) );
                break;
        }
        n++;
    }

    return vectorValues;
}

int ODBCMetaInfo::getCount( ODBCMetaInfoAttr *p )
{
    int n = 0;

    while ( p && p[n].pszCasualName )
    {
        n++;
    }

    return n;
}

int ODBCMetaInfo::getCount( ODBCMetaInfoAttrValue *p )
{
    int n = 0;

    while ( p && p[n].pszCasualName )
    {
        n++;
    }

    return n;
}


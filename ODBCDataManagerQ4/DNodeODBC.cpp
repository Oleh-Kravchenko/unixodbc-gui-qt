/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeOQ.h"

#include "DNodeDrivers.h"
#include "DNodeDataSourceNames.h"

#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "ODBC64.xpm"

DNodeODBC::DNodeODBC( DNodeWidget *pNodeWidget )
    : DNode( pNodeWidget )
{
    setIcon( 0, QIcon( xpmODBC64 ) );
    setText( 0, QObject::tr( "ODBC" ) );

    SQLRETURN nReturn = SQLAllocHandle( SQL_HANDLE_ENV, 0, &hEnv );
    // we need the following because we (this app) are going to use v3 api calls...
    SQLSetEnvAttr( hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0 );

    new DNodeDrivers( pNodeWidget, this );
    new DNodeDataSourceNames( pNodeWidget, this );

    setExpanded( true );
}

DNodeODBC::~DNodeODBC()
{
    SQLRETURN nReturn = SQLFreeHandle( SQL_HANDLE_ENV, hEnv );
}

SQLHENV DNodeODBC::getEnvironment()
{
    return hEnv;
}

void DNodeODBC::doLoadProperties( DPropWidget *pPropWidget )
{
    emit signalDiagnosticClear();

    // ODBC config...
    {
        char    szError[FILENAME_MAX+1];
        DWORD   nError;
        char    szKeys[4048];
        char    szValue[501];
        char *  pszKey;
    
        if ( SQLGetPrivateProfileString( "ODBC", NULL, NULL, szKeys, sizeof( szKeys ) - 1, "ODBCINST.INI" ) < 1 )
        {
            SQLInstallerError( 1, &nError, szError, FILENAME_MAX, NULL );
            printf( "DNodeODBC: SQLGetPrivateProfileString failed with %s.\n", szError );
            return;
        }
        pszKey = szKeys;
        while ( *pszKey )
        {
            SQLGetPrivateProfileString( "ODBC", pszKey, "", szValue, sizeof( szValue ) - 1, "ODBCINST.INI" );
    
            DNodeAttribute *p = new DNodeAttribute( pPropWidget->getNodeWidget(), pszKey, szValue );
            p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
            pszKey += strlen( pszKey ) + 1;
        }
    }

    // env attributes
    {
        DNodeAttribute *p;
        SQLUINTEGER     nUnsignedInteger;
        SQLINTEGER      nInteger;
        char            sz[256];

        SQLGetEnvAttr( hEnv, SQL_ATTR_CONNECTION_POOLING, &nUnsignedInteger, 0, 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONNECTION_POOLING", QString::number( nUnsignedInteger ) );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        SQLGetEnvAttr( hEnv, SQL_ATTR_CP_MATCH, &nUnsignedInteger, 0, 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CP_MATCH", QString::number( nUnsignedInteger ) );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        SQLGetEnvAttr( hEnv, SQL_ATTR_ODBC_VERSION, &nInteger, 0, 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ODBC_VERSION", QString::number( nInteger ) );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        SQLGetEnvAttr( hEnv, SQL_ATTR_OUTPUT_NTS, &nInteger, 0, 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_OUTPUT_NTS", QString::number( nInteger ) );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        SQLGetEnvAttr( hEnv, SQL_ATTR_UNIXODBC_SYSPATH, sz, sizeof( sz ), 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_UNIXODBC_SYSPATH", sz );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

        SQLGetEnvAttr( hEnv, SQL_ATTR_UNIXODBC_VERSION, sz, sizeof( sz ), 0 ); 
        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_UNIXODBC_VERSION", sz );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_UNIXODBC_ENVATTR", "" );
        p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
    }
}

void DNodeODBC::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}



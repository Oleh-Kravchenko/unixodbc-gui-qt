/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 **********************************************************************
 *
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "conn.h"
#include "OdbcTest.h"

static attr_options gf_options[] = 
{
    { "SQL_API_ODBC3_ALL_FUNCTIONS", SQL_API_ODBC3_ALL_FUNCTIONS, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_API_ALL_FUNCTIONS", SQL_API_ALL_FUNCTIONS, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLALLOCCONNECT", SQL_API_SQLALLOCCONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLALLOCENV", SQL_API_SQLALLOCENV,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLALLOCHANDLESTD", SQL_API_SQLALLOCHANDLESTD,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLALLOCSTMT", SQL_API_SQLALLOCSTMT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLBINDCOL", SQL_API_SQLBINDCOL,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLBINDPARAMETER", SQL_API_SQLBINDPARAMETER,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLBROWSECONNECT", SQL_API_SQLBROWSECONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLBULKOPERATIONS", SQL_API_SQLBULKOPERATIONS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCANCEL", SQL_API_SQLCANCEL,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCOLATTRIBUTE", SQL_API_SQLCOLATTRIBUTE,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCOLATTRIBUTES", SQL_API_SQLCOLATTRIBUTES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCOLUMNPRIVILEGES", SQL_API_SQLCOLUMNPRIVILEGES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCOLUMNS", SQL_API_SQLCOLUMNS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCONNECT", SQL_API_SQLCONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDATASOURCES", SQL_API_SQLDATASOURCES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDESCRIBECOL", SQL_API_SQLDESCRIBECOL,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDESCRIBEPARAM", SQL_API_SQLDESCRIBEPARAM,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDISCONNECT", SQL_API_SQLDISCONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDRIVERCONNECT", SQL_API_SQLDRIVERCONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLDRIVERS", SQL_API_SQLDRIVERS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLERROR", SQL_API_SQLERROR,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLEXECDIRECT", SQL_API_SQLEXECDIRECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLEXECUTE", SQL_API_SQLEXECUTE,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLEXTENDEDFETCH", SQL_API_SQLEXTENDEDFETCH,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFETCH", SQL_API_SQLFETCH,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFOREIGNKEYS", SQL_API_SQLFOREIGNKEYS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFREECONNECT", SQL_API_SQLFREECONNECT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFREEENV", SQL_API_SQLFREEENV,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFREESTMT", SQL_API_SQLFREESTMT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETCONNECTOPTION", SQL_API_SQLGETCONNECTOPTION,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETCURSORNAME", SQL_API_SQLGETCURSORNAME,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETDATA", SQL_API_SQLGETDATA,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETFUNCTIONS", SQL_API_SQLGETFUNCTIONS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETINFO", SQL_API_SQLGETINFO,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETSTMTOPTION", SQL_API_SQLGETSTMTOPTION,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETTYPEINFO", SQL_API_SQLGETTYPEINFO,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLMORERESULTS", SQL_API_SQLMORERESULTS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLNATIVESQL", SQL_API_SQLNATIVESQL,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLNUMPARAMS", SQL_API_SQLNUMPARAMS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLNUMRESULTCOLS", SQL_API_SQLNUMRESULTCOLS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPARAMDATA", SQL_API_SQLPARAMDATA,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPARAMOPTIONS", SQL_API_SQLPARAMOPTIONS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPREPARE", SQL_API_SQLPREPARE,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPRIMARYKEYS", SQL_API_SQLPRIMARYKEYS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPROCEDURECOLUMNS", SQL_API_SQLPROCEDURECOLUMNS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPROCEDURES", SQL_API_SQLPROCEDURES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLPUTDATA", SQL_API_SQLPUTDATA,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLROWCOUNT", SQL_API_SQLROWCOUNT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETCONNECTOPTION", SQL_API_SQLSETCONNECTOPTION,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETCURSORNAME", SQL_API_SQLSETCURSORNAME,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETPARAM", SQL_API_SQLSETPARAM,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETPOS", SQL_API_SQLSETPOS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETSCROLLOPTIONS", SQL_API_SQLSETSCROLLOPTIONS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETSTMTOPTION", SQL_API_SQLSETSTMTOPTION,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSPECIALCOLUMNS", SQL_API_SQLSPECIALCOLUMNS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSTATISTICS", SQL_API_SQLSTATISTICS,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLTABLEPRIVILEGES", SQL_API_SQLTABLEPRIVILEGES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLTABLES", SQL_API_SQLTABLES,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLTRANSACT", SQL_API_SQLTRANSACT,
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLALLOCHANDLE", SQL_API_SQLALLOCHANDLE,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLBINDPARAM", SQL_API_SQLBINDPARAM,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCLOSECURSOR", SQL_API_SQLCLOSECURSOR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLCOPYDESC", SQL_API_SQLCOPYDESC,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLENDTRAN", SQL_API_SQLENDTRAN,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFETCHSCROLL", SQL_API_SQLFETCHSCROLL,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLFREEHANDLE", SQL_API_SQLFREEHANDLE,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETCONNECTATTR", SQL_API_SQLGETCONNECTATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETDESCFIELD", SQL_API_SQLGETDESCFIELD,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETDESCREC", SQL_API_SQLGETDESCREC,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETDIAGFIELD", SQL_API_SQLGETDIAGFIELD,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETDIAGREC", SQL_API_SQLGETDIAGREC,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETENVATTR", SQL_API_SQLGETENVATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLGETSTMTATTR", SQL_API_SQLGETSTMTATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETCONNECTATTR", SQL_API_SQLSETCONNECTATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETDESCFIELD", SQL_API_SQLSETDESCFIELD,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETDESCREC", SQL_API_SQLSETDESCREC,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETENVATTR", SQL_API_SQLSETENVATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    {"SQL_API_SQLSETSTMTATTR", SQL_API_SQLSETSTMTATTR,
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0 } }, NULL, 0, 0, 0 }
};

static attr_options dc_options[] = 
{
    { "SQL_DRIVER_COMPLETE", SQL_DRIVER_COMPLETE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_NOPROMPT", SQL_DRIVER_NOPROMPT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_COMPLETE", SQL_DRIVER_COMPLETE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_COMPLETE_REQUIRED", SQL_DRIVER_COMPLETE_REQUIRED, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0 } }, NULL, 0, 0, 0 }
};

static attr_options info_options[] = 
{
    { "SQL_ACCESSIBLE_PROCEDURES", SQL_ACCESSIBLE_PROCEDURES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_ACCESSIBLE_TABLES", SQL_ACCESSIBLE_TABLES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_ACTIVE_ENVIRONMENTS", SQL_ACTIVE_ENVIRONMENTS, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_AGGREGATE_FUNCTIONS", SQL_AGGREGATE_FUNCTIONS, 
        {
            { "SQL_AF_ALL",     SQL_AF_ALL, NULL, 0},
            { "SQL_AF_AVG",     SQL_AF_AVG, NULL, 0},
            { "SQL_AF_COUNT",   SQL_AF_COUNT,   NULL, 0},
            { "SQL_AF_DISTINCT",    SQL_AF_DISTINCT,NULL, 0},
            { "SQL_AF_MAX",     SQL_AF_MAX, NULL, 0},
            { "SQL_AF_MIN",     SQL_AF_MIN, NULL, 0},
            { "SQL_AF_SUM",     SQL_AF_SUM, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_ALTER_DOMAIN", SQL_ALTER_DOMAIN, 
        {
            { "SQL_AD_ADD_DOMAIN_CONSTRAINT",       SQL_AD_ADD_DOMAIN_CONSTRAINT,           NULL, 0},
            { "SQL_AD_ADD_DOMAIN_DEFAULT",          SQL_AD_ADD_DOMAIN_DEFAULT,          NULL, 0},
            { "SQL_AD_CONSTRAINT_NAME_DEFINITION",      SQL_AD_CONSTRAINT_NAME_DEFINITION,      NULL, 0},
            { "SQL_AD_DROP_DOMAIN_CONSTRAINT",      SQL_AD_DROP_DOMAIN_CONSTRAINT,          NULL, 0},
            { "SQL_AD_DROP_DOMAIN_DEFAULT",         SQL_AD_DROP_DOMAIN_DEFAULT,         NULL, 0},
            { "SQL_AD_ADD_CONSTRAINT_DEFERRABLE",       SQL_AD_ADD_CONSTRAINT_DEFERRABLE,       NULL, 0},
            { "SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE",   SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE,       NULL, 0},
            { "SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED",   SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED,   NULL, 0},
            { "SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE",  SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE,  NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_ALTER_TABLE", SQL_ALTER_TABLE, 
        {
            { "SQL_AT_ADD_COLUMN_COLLATION",        SQL_AT_ADD_COLUMN_COLLATION, NULL, 0},
            { "SQL_AT_ADD_COLUMN_DEFAULT",          SQL_AT_ADD_COLUMN_DEFAULT, NULL, 0},
            { "SQL_AT_ADD_COLUMN_SINGLE",           SQL_AT_ADD_COLUMN_SINGLE, NULL, 0},
            { "SQL_AT_ADD_CONSTRAINT",          SQL_AT_ADD_CONSTRAINT, NULL, 0},
            { "SQL_AT_ADD_TABLE_CONSTRAINT",        SQL_AT_ADD_TABLE_CONSTRAINT, NULL, 0},
            { "SQL_AT_CONSTRAINT_NAME_DEFINITION",      SQL_AT_CONSTRAINT_NAME_DEFINITION, NULL, 0},
            { "SQL_AT_DROP_COLUMN_CASCADE",         SQL_AT_DROP_COLUMN_CASCADE, NULL, 0},
            { "SQL_AT_DROP_COLUMN_DEFAULT",         SQL_AT_DROP_COLUMN_DEFAULT, NULL, 0},
            { "SQL_AT_DROP_COLUMN_RESTRICT",        SQL_AT_DROP_COLUMN_RESTRICT, NULL, 0},
            { "SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE",   SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE, NULL, 0},
            { "SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT",  SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT, NULL, 0},
            { "SQL_AT_SET_COLUMN_DEFAULT",          SQL_AT_SET_COLUMN_DEFAULT, NULL, 0},
            { "SQL_AT_CONSTRAINT_INITIALLY_DEFERRED",   SQL_AT_CONSTRAINT_INITIALLY_DEFERRED, NULL, 0},
            { "SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE",  SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE, NULL, 0},
            { "SQL_AT_CONSTRAINT_DEFERRABLE",       SQL_AT_CONSTRAINT_DEFERRABLE, NULL, 0},
            { "SQL_AT_CONSTRAINT_NON_DEFERRABLE",       SQL_AT_CONSTRAINT_NON_DEFERRABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_ASYNC_MODE", SQL_ASYNC_MODE, 
        {
            { "SQL_AM_CONNECTION", SQL_AM_CONNECTION, NULL, 0},
            { "SQL_AM_STATEMENT", SQL_AM_STATEMENT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_BATCH_ROW_COUNT", SQL_BATCH_ROW_COUNT, 
        {
            { "SQL_BRC_ROLLED_UP", SQL_BRC_ROLLED_UP, NULL, 0},
            { "SQL_BRC_PROCEDURES", SQL_BRC_PROCEDURES, NULL, 0},
            { "SQL_BRC_EXPLICIT", SQL_BRC_EXPLICIT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_BATCH_SUPPORT", SQL_BATCH_SUPPORT, 
        {
            { "SQL_BS_SELECT_EXPLI|CIT", SQL_BS_SELECT_EXPLICIT, NULL, 0},
            { "SQL_BS_ROW_COUNT_EXPLICIT", SQL_BS_ROW_COUNT_EXPLICIT, NULL, 0},
            { "SQL_BS_SELECT_PROC", SQL_BS_SELECT_PROC, NULL, 0},
            { "SQL_BS_ROW_COUNT_PROC", SQL_BS_ROW_COUNT_PROC, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_BOOKMARK_PERSISTENCE", SQL_BOOKMARK_PERSISTENCE, 
        {
            { "SQL_BP_CLOSE", SQL_BP_CLOSE, NULL, 0},
            { "SQL_BP_DELETE", SQL_BP_DELETE, NULL, 0},
            { "SQL_BP_DROP", SQL_BP_DROP, NULL, 0},
            { "SQL_BP_TRANSACTION", SQL_BP_TRANSACTION, NULL, 0},
            { "SQL_BP_UPDATE", SQL_BP_UPDATE, NULL, 0},
            { "SQL_BP_OTHER_HSTMT", SQL_BP_OTHER_HSTMT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CATALOG_LOCATION", SQL_CATALOG_LOCATION, 
        {
            { "SQL_CL_START", SQL_CL_START, NULL, 0},
            { "SQL_CL_END", SQL_CL_END, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_CATALOG_NAME", SQL_CATALOG_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_CATALOG_NAME_SEPARATOR", SQL_CATALOG_NAME_SEPARATOR, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_CATALOG_TERM", SQL_CATALOG_TERM, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_CATALOG_USAGE", SQL_CATALOG_USAGE, 
        {
            { "SQL_CU_DML_STATEMENTS", SQL_CU_DML_STATEMENTS, NULL, 0},
            { "SQL_CU_PROCEDURE_INVOCATION", SQL_CU_PROCEDURE_INVOCATION, NULL, 0},
            { "SQL_CU_TABLE_DEFINITION", SQL_CU_TABLE_DEFINITION, NULL, 0},
            { "SQL_CU_INDEX_DEFINITION", SQL_CU_INDEX_DEFINITION, NULL, 0},
            { "SQL_CU_PRIVILEGE_DEFINITION", SQL_CU_PRIVILEGE_DEFINITION, NULL, 0},
            { "SQL_CL_END", SQL_CL_END, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_COLLATION_SEQ", SQL_COLLATION_SEQ, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_COLUMN_ALIAS", SQL_COLUMN_ALIAS, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_ODBC_API_CONFORMANCE", SQL_ODBC_API_CONFORMANCE, 
        {
            { "SQL_OAC_NONE", SQL_OAC_NONE, NULL, 0},
            { "SQL_OAC_LEVEL1", SQL_OAC_LEVEL1, NULL, 0},
            { "SQL_OAC_LEVEL2", SQL_OAC_LEVEL2, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ODBC_SAG_CLI_CONFORMANCE", SQL_ODBC_SAG_CLI_CONFORMANCE, 
        {
            { "SQL_OSCC_NOT_COMPLIANT", SQL_OSCC_NOT_COMPLIANT, NULL, 0},
            { "SQL_OSCC_COMPLIANT", SQL_OSCC_COMPLIANT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ODBC_SQL_CONFORMANCE", SQL_ODBC_SQL_CONFORMANCE, 
        {
            { "SQL_OSC_MINIMUM", SQL_OSC_MINIMUM, NULL, 0},
            { "SQL_OSC_CORE", SQL_OSC_CORE, NULL, 0},
            { "SQL_OSC_EXTENDED", SQL_OSC_EXTENDED, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_CONCAT_NULL_BEHAVIOR", SQL_CONCAT_NULL_BEHAVIOR, 
        {
            { "SQL_CB_NULL", SQL_CB_NULL, NULL, 0},
            { "SQL_CB_NON_NULL", SQL_CB_NON_NULL, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_CONVERT_BIGINT", SQL_CONVERT_BIGINT, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_BINARY", SQL_CONVERT_BINARY, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_BIT", SQL_CONVERT_BIT, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_CHAR", SQL_CONVERT_CHAR, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_DATE", SQL_CONVERT_DATE, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_DECIMAL", SQL_CONVERT_DECIMAL, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_DOUBLE", SQL_CONVERT_DOUBLE, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_FLOAT", SQL_CONVERT_FLOAT, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_INTEGER", SQL_CONVERT_INTEGER, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_INTERVAL_YEAR_MONTH", SQL_CONVERT_INTERVAL_YEAR_MONTH, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_INTERVAL_DAY_TIME", SQL_CONVERT_INTERVAL_DAY_TIME, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_LONGVARBINARY", SQL_CONVERT_LONGVARBINARY, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_LONGVARCHAR", SQL_CONVERT_LONGVARCHAR, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_NUMERIC", SQL_CONVERT_NUMERIC, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_REAL", SQL_CONVERT_REAL, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_SMALLINT", SQL_CONVERT_SMALLINT, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_TIME", SQL_CONVERT_TIME, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_TIMESTAMP", SQL_CONVERT_TIMESTAMP, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_TINYINT", SQL_CONVERT_TINYINT, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_VARBINARY", SQL_CONVERT_VARBINARY, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_VARCHAR", SQL_CONVERT_VARCHAR, 
        {
            { "SQL_CVT_BIGINT", SQL_CVT_BIGINT, NULL, 0},
            { "SQL_CVT_BINARY", SQL_CVT_BINARY, NULL, 0},
            { "SQL_CVT_BIT", SQL_CVT_BIT, NULL, 0},
            { "SQL_CVT_CHAR", SQL_CVT_CHAR, NULL, 0},
            { "SQL_CVT_DATE", SQL_CVT_DATE, NULL, 0},
            { "SQL_CVT_DECIMAL", SQL_CVT_DECIMAL, NULL, 0},
            { "SQL_CVT_DOUBLE", SQL_CVT_DOUBLE, NULL, 0},
            { "SQL_CVT_FLOAT", SQL_CVT_FLOAT, NULL, 0},
            { "SQL_CVT_INTEGER", SQL_CVT_INTEGER, NULL, 0},
            { "SQL_CVT_INTERVAL_YEAR_MONTH", SQL_CVT_INTERVAL_YEAR_MONTH, NULL, 0},
            { "SQL_CVT_INTERVAL_DAY_TIME", SQL_CVT_INTERVAL_DAY_TIME, NULL, 0},
            { "SQL_CVT_LONGVARBINARY", SQL_CVT_LONGVARBINARY, NULL, 0},
            { "SQL_CVT_LONGVARCHAR", SQL_CVT_LONGVARCHAR, NULL, 0},
            { "SQL_CVT_NUMERIC", SQL_CVT_NUMERIC, NULL, 0},
            { "SQL_CVT_REAL", SQL_CVT_REAL, NULL, 0},
            { "SQL_CVT_SMALLINT", SQL_CVT_SMALLINT, NULL, 0},
            { "SQL_CVT_TIME", SQL_CVT_TIME, NULL, 0},
            { "SQL_CVT_TIMESTAMP", SQL_CVT_TIMESTAMP, NULL, 0},
            { "SQL_CVT_TINYINT", SQL_CVT_TINYINT, NULL, 0},
            { "SQL_CVT_VARBINARY", SQL_CVT_VARBINARY, NULL, 0},
            { "SQL_CVT_VARCHAR", SQL_CVT_VARCHAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CONVERT_FUNCTIONS", SQL_CONVERT_FUNCTIONS, 
        {
            { "SQL_FN_CVT_CAST", SQL_FN_CVT_CAST, NULL, 0},
            { "SQL_FN_CVT_CONVERT", SQL_FN_CVT_CONVERT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CORRELATION_NAME", SQL_CORRELATION_NAME, 
        {
            { "SQL_CN_NONE", SQL_CN_NONE, NULL, 0},
            { "SQL_CN_DIFFERENT", SQL_CN_DIFFERENT, NULL, 0},
            { "SQL_CN_ANY", SQL_CN_ANY, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_CREATE_ASSERTION", SQL_CREATE_ASSERTION, 
        {
            { "SQL_CA_CREATE_ASSERTION", SQL_CA_CREATE_ASSERTION, NULL, 0},
            { "SQL_CA_CONSTRAINT_INITIALLY_DEFERRED", SQL_CA_CONSTRAINT_INITIALLY_DEFERRED, NULL, 0},
            { "SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE", SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE, NULL, 0},
            { "SQL_CA_CONSTRAINT_DEFERRABLE", SQL_CA_CONSTRAINT_DEFERRABLE, NULL, 0},
            { "SQL_CA_CONSTRAINT_NON_DEFERRABLE", SQL_CA_CONSTRAINT_NON_DEFERRABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_CHARACTER_SET", SQL_CREATE_CHARACTER_SET, 
        {
            { "SQL_CCS_CREATE_CHARACTER_SET", SQL_CCS_CREATE_CHARACTER_SET, NULL, 0},
            { "SQL_CCS_COLLATE_CLAUSE", SQL_CCS_COLLATE_CLAUSE, NULL, 0},
            { "SQL_CCS_LIMITED_COLLATION", SQL_CCS_LIMITED_COLLATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_COLLATION", SQL_CREATE_COLLATION, 
        {
            { "SQL_CCOL_CREATE_COLLATION", SQL_CCOL_CREATE_COLLATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_DOMAIN", SQL_CREATE_DOMAIN, 
        {
            { "SQL_CDO_CREATE_DOMAIN", SQL_CDO_CREATE_DOMAIN, NULL, 0},
            { "SQL_CDO_CONSTRAINT_NAME_DEFINITION", SQL_CDO_CONSTRAINT_NAME_DEFINITION, NULL, 0},
            { "SQL_CDO_DEFAULT", SQL_CDO_DEFAULT, NULL, 0},
            { "SQL_CDO_CONSTRAINT", SQL_CDO_CONSTRAINT, NULL, 0},
            { "SQL_CDO_COLLATION", SQL_CDO_COLLATION, NULL, 0},
            { "SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED", SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED, NULL, 0},
            { "SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE", SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE, NULL, 0},
            { "SQL_CDO_CONSTRAINT_DEFERRABLE", SQL_CDO_CONSTRAINT_DEFERRABLE, NULL, 0},
            { "SQL_CDO_CONSTRAINT_NON_DEFERRABLE", SQL_CDO_CONSTRAINT_NON_DEFERRABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_SCHEMA", SQL_CREATE_SCHEMA, 
        {
            { "SQL_CS_CREATE_SCHEMA", SQL_CS_CREATE_SCHEMA, NULL, 0},
            { "SQL_CS_AUTHORIZATION", SQL_CS_AUTHORIZATION, NULL, 0},
            { "SQL_CS_DEFAULT_CHARACTER_SET", SQL_CS_DEFAULT_CHARACTER_SET, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_TABLE", SQL_CREATE_TABLE, 
        {
            { "SQL_CT_CREATE_TABLE", SQL_CT_CREATE_TABLE, NULL, 0},
            { "SQL_CT_TABLE_CONSTRAINT", SQL_CT_TABLE_CONSTRAINT, NULL, 0},
            { "SQL_CT_CONSTRAINT_NAME_DEFINITION", SQL_CT_CONSTRAINT_NAME_DEFINITION, NULL, 0},
            { "SQL_CT_COMMIT_PRESERVE", SQL_CT_COMMIT_PRESERVE, NULL, 0},
            { "SQL_CT_COMMIT_DELETE", SQL_CT_COMMIT_DELETE, NULL, 0},
            { "SQL_CT_GLOBAL_TEMPORARY", SQL_CT_GLOBAL_TEMPORARY, NULL, 0},
            { "SQL_CT_LOCAL_TEMPORARY", SQL_CT_LOCAL_TEMPORARY, NULL, 0},
            { "SQL_CT_COLUMN_CONSTRAINT", SQL_CT_COLUMN_CONSTRAINT, NULL, 0},
            { "SQL_CT_COLUMN_DEFAULT", SQL_CT_COLUMN_DEFAULT, NULL, 0},
            { "SQL_CT_COLUMN_COLLATION", SQL_CT_COLUMN_COLLATION, NULL, 0},
            { "SQL_CT_CONSTRAINT_INITIALLY_DEFERRED", SQL_CT_CONSTRAINT_INITIALLY_DEFERRED, NULL, 0},
            { "SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE", SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE, NULL, 0},
            { "SQL_CT_CONSTRAINT_DEFERRABLE", SQL_CT_CONSTRAINT_DEFERRABLE, NULL, 0},
            { "SQL_CT_CONSTRAINT_NON_DEFERRABLE", SQL_CT_CONSTRAINT_NON_DEFERRABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_TRANSLATION", SQL_CREATE_TRANSLATION, 
        {
            { "SQL_CTR_CREATE_TRANSLATION", SQL_CTR_CREATE_TRANSLATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_CREATE_VIEW", SQL_CREATE_VIEW, 
        {
            { "SQL_CV_CREATE_VIEW", SQL_CV_CREATE_VIEW, NULL, 0},
            { "SQL_CV_CHECK_OPTION", SQL_CV_CHECK_OPTION, NULL, 0},
            { "SQL_CV_CASCADED", SQL_CV_CASCADED, NULL, 0},
            { "SQL_CV_LOCAL", SQL_CV_LOCAL, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, TRUE, 0
    },
    { "SQL_CURSOR_COMMIT_BEHAVIOR", SQL_CURSOR_COMMIT_BEHAVIOR, 
        {
            { "SQL_CB_DELETE", SQL_CB_DELETE, NULL, 0},
            { "SQL_CB_CLOSE", SQL_CB_CLOSE, NULL, 0},
            { "SQL_CB_PRESERVE", SQL_CB_PRESERVE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_CURSOR_ROLLBACK_BEHAVIOR", SQL_CURSOR_ROLLBACK_BEHAVIOR, 
        {
            { "SQL_CB_DELETE", SQL_CB_DELETE, NULL, 0},
            { "SQL_CB_CLOSE", SQL_CB_CLOSE, NULL, 0},
            { "SQL_CB_PRESERVE", SQL_CB_PRESERVE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_CURSOR_SENSITIVITY", SQL_CURSOR_SENSITIVITY, 
        {
            { "SQL_INSENSITIVE", SQL_INSENSITIVE, NULL, 0},
            { "SQL_UNSPECIFIED", SQL_UNSPECIFIED, NULL, 0},
            { "SQL_SENSITIVE", SQL_SENSITIVE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DATA_SOURCE_NAME", SQL_DATA_SOURCE_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DATA_SOURCE_READ_ONLY", SQL_DATA_SOURCE_READ_ONLY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DATABASE_NAME", SQL_DATABASE_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DATETIME_LITERALS", SQL_DATETIME_LITERALS, 
        {
            { "SQL_DL_SQL92_DATE", SQL_DL_SQL92_DATE, NULL, 0},
            { "SQL_DL_SQL92_TIME", SQL_DL_SQL92_TIME, NULL, 0},
            { "SQL_DL_SQL92_TIMESTAMP", SQL_DL_SQL92_TIMESTAMP, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_YEAR", SQL_DL_SQL92_INTERVAL_YEAR, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_MONTH", SQL_DL_SQL92_INTERVAL_MONTH, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_DAY", SQL_DL_SQL92_INTERVAL_DAY, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_HOUR", SQL_DL_SQL92_INTERVAL_HOUR, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_MINUTE", SQL_DL_SQL92_INTERVAL_MINUTE, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_SECOND", SQL_DL_SQL92_INTERVAL_SECOND, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH", SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR", SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE", SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND", SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE", SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND", SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND, NULL, 0},
            { "SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND", SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DBMS_NAME", SQL_DBMS_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DBMS_VER", SQL_DBMS_VER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DDL_INDEX", SQL_DDL_INDEX, 
        {
            { "SQL_DI_CREATE_INDEX", SQL_DI_CREATE_INDEX, NULL, 0},
            { "SQL_DI_DROP_INDEX", SQL_DI_DROP_INDEX, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DEFAULT_TXN_ISOLATION", SQL_DEFAULT_TXN_ISOLATION, 
        {
            { "SQL_TXN_READ_UNCOMMITTED", SQL_TXN_READ_UNCOMMITTED, NULL, 0},
            { "SQL_TXN_READ_COMMITTED", SQL_TXN_READ_COMMITTED, NULL, 0},
            { "SQL_TXN_REPEATABLE_READ", SQL_TXN_REPEATABLE_READ, NULL, 0},
            { "SQL_TXN_SERIALIZABLE", SQL_TXN_SERIALIZABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DESCRIBE_PARAMETER", SQL_DESCRIBE_PARAMETER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DM_VER", SQL_DM_VER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DRIVER_HDBC", SQL_DRIVER_HDBC, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_HENV", SQL_DRIVER_HENV, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_HDESC", SQL_DRIVER_HDESC, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_HLIB", SQL_DRIVER_HLIB, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_HSTMT", SQL_DRIVER_HSTMT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DRIVER_NAME", SQL_DRIVER_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DRIVER_ODBC_VER", SQL_DRIVER_ODBC_VER, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_DRIVER_VER", SQL_DRIVER_VER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_DROP_ASSERTION", SQL_DROP_ASSERTION, 
        {
            { "SQL_DA_DROP_ASSERTION", SQL_DA_DROP_ASSERTION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_CHARACTER_SET", SQL_DROP_CHARACTER_SET, 
        {
            { "SQL_DCS_DROP_CHARACTER_SET", SQL_DCS_DROP_CHARACTER_SET, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_COLLATION", SQL_DROP_COLLATION, 
        {
            { "SQL_DC_DROP_COLLATION", SQL_DC_DROP_COLLATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_DOMAIN", SQL_DROP_DOMAIN, 
        {
            { "SQL_DD_DROP_DOMAIN", SQL_DD_DROP_DOMAIN, NULL, 0},
            { "SQL_DD_CASCADE", SQL_DD_CASCADE, NULL, 0},
            { "SQL_DD_RESTRICT", SQL_DD_RESTRICT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_SCHEMA", SQL_DROP_SCHEMA, 
        {
            { "SQL_DS_DROP_SCHEMA", SQL_DS_DROP_SCHEMA, NULL, 0},
            { "SQL_DS_CASCADE", SQL_DS_CASCADE, NULL, 0},
            { "SQL_DS_RESTRICT", SQL_DS_RESTRICT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_TABLE", SQL_DROP_TABLE, 
        {
            { "SQL_DT_DROP_TABLE", SQL_DT_DROP_TABLE, NULL, 0},
            { "SQL_DT_CASCADE", SQL_DT_CASCADE, NULL, 0},
            { "SQL_DT_RESTRICT", SQL_DT_RESTRICT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_TRANSLATION", SQL_DROP_TRANSLATION, 
        {
            { "SQL_DTR_DROP_TRANSLATION", SQL_DTR_DROP_TRANSLATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DROP_VIEW", SQL_DROP_VIEW, 
        {
            { "SQL_DV_DROP_VIEW", SQL_DV_DROP_VIEW, NULL, 0},
            { "SQL_DV_CASCADE", SQL_DV_CASCADE, NULL, 0},
            { "SQL_DV_RESTRICT", SQL_DV_RESTRICT, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DYNAMIC_CURSOR_ATTRIBUTES1", SQL_DYNAMIC_CURSOR_ATTRIBUTES1, 
        {
            { "SQL_CA1_NEXT", SQL_CA1_NEXT, NULL, 0},
            { "SQL_CA1_ABSOLUTE", SQL_CA1_ABSOLUTE, NULL, 0},
            { "SQL_CA1_RELATIVE", SQL_CA1_RELATIVE, NULL, 0},
            { "SQL_CA1_BOOKMARK", SQL_CA1_BOOKMARK, NULL, 0},
            { "SQL_CA1_LOCK_EXCLUSIVE", SQL_CA1_LOCK_EXCLUSIVE, NULL, 0},
            { "SQL_CA1_LOCK_NO_CHANGE", SQL_CA1_LOCK_NO_CHANGE, NULL, 0},
            { "SQL_CA1_LOCK_UNLOCK", SQL_CA1_LOCK_UNLOCK, NULL, 0},
            { "SQL_CA1_POS_POSITION", SQL_CA1_POS_POSITION, NULL, 0},
            { "SQL_CA1_POS_UPDATE", SQL_CA1_POS_UPDATE, NULL, 0},
            { "SQL_CA1_POS_DELETE", SQL_CA1_POS_DELETE, NULL, 0},
            { "SQL_CA1_POS_REFRESH", SQL_CA1_POS_REFRESH, NULL, 0},
            { "SQL_CA1_POSITIONED_UPDATE", SQL_CA1_POSITIONED_UPDATE, NULL, 0},
            { "SQL_CA1_POSITIONED_DELETE", SQL_CA1_POSITIONED_DELETE, NULL, 0},
            { "SQL_CA1_SELECT_FOR_UPDATE", SQL_CA1_SELECT_FOR_UPDATE, NULL, 0},
            { "SQL_CA1_BULK_ADD", SQL_CA1_BULK_ADD, NULL, 0},
            { "SQL_CA1_BULK_UPDATE_BY_BOOKMARK", SQL_CA1_BULK_UPDATE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_DELETE_BY_BOOKMARK", SQL_CA1_BULK_DELETE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_FETCH_BY_BOOKMARK", SQL_CA1_BULK_FETCH_BY_BOOKMARK, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_DYNAMIC_CURSOR_ATTRIBUTES2", SQL_DYNAMIC_CURSOR_ATTRIBUTES2, 
        {
            { "SQL_CA2_READ_ONLY_CONCURRENCY", SQL_CA2_READ_ONLY_CONCURRENCY, NULL, 0},
            { "SQL_CA2_LOCK_CONCURRENCY", SQL_CA2_LOCK_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_ROWVER_CONCURRENCY", SQL_CA2_OPT_ROWVER_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_VALUES_CONCURRENCY", SQL_CA2_OPT_VALUES_CONCURRENCY, NULL, 0},
            { "SQL_CA2_SENSITIVITY_ADDITIONS", SQL_CA2_SENSITIVITY_ADDITIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_DELETIONS", SQL_CA2_SENSITIVITY_DELETIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_UPDATES", SQL_CA2_SENSITIVITY_UPDATES, NULL, 0},
            { "SQL_CA2_MAX_ROWS_SELECT", SQL_CA2_MAX_ROWS_SELECT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_INSERT", SQL_CA2_MAX_ROWS_INSERT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_DELETE", SQL_CA2_MAX_ROWS_DELETE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_UPDATE", SQL_CA2_MAX_ROWS_UPDATE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_CATALOG", SQL_CA2_MAX_ROWS_CATALOG, NULL, 0},
            { "SQL_CA2_MAX_ROWS_AFFECTS_ALL", SQL_CA2_MAX_ROWS_AFFECTS_ALL, NULL, 0},
            { "SQL_CA2_CRC_EXACT", SQL_CA2_CRC_EXACT, NULL, 0},
            { "SQL_CA2_CRC_APPROXIMATE", SQL_CA2_CRC_APPROXIMATE, NULL, 0},
            { "SQL_CA2_SIMULATE_NON_UNIQUE", SQL_CA2_SIMULATE_NON_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_TRY_UNIQUE", SQL_CA2_SIMULATE_TRY_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_UNIQUE", SQL_CA2_SIMULATE_UNIQUE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_EXPRESSIONS_IN_ORDERBY", SQL_EXPRESSIONS_IN_ORDERBY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_FILE_USAGE", SQL_FILE_USAGE, 
        {
            { "SQL_FILE_NOT_SUPPORTED", SQL_FILE_NOT_SUPPORTED, NULL, 0},
            { "SQL_FILE_TABLE", SQL_FILE_TABLE, NULL, 0},
            { "SQL_FILE_CATALOG", SQL_FILE_CATALOG, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1", SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1, 
        {
            { "SQL_CA1_NEXT", SQL_CA1_NEXT, NULL, 0},
            { "SQL_CA1_LOCK_EXCLUSIVE", SQL_CA1_LOCK_EXCLUSIVE, NULL, 0},
            { "SQL_CA1_LOCK_NO_CHANGE", SQL_CA1_LOCK_NO_CHANGE, NULL, 0},
            { "SQL_CA1_LOCK_UNLOCK", SQL_CA1_LOCK_UNLOCK, NULL, 0},
            { "SQL_CA1_POS_POSITION", SQL_CA1_POS_POSITION, NULL, 0},
            { "SQL_CA1_POS_UPDATE", SQL_CA1_POS_UPDATE, NULL, 0},
            { "SQL_CA1_POS_DELETE", SQL_CA1_POS_DELETE, NULL, 0},
            { "SQL_CA1_POS_REFRESH", SQL_CA1_POS_REFRESH, NULL, 0},
            { "SQL_CA1_POSITIONED_UPDATE", SQL_CA1_POSITIONED_UPDATE, NULL, 0},
            { "SQL_CA1_POSITIONED_DELETE", SQL_CA1_POSITIONED_DELETE, NULL, 0},
            { "SQL_CA1_SELECT_FOR_UPDATE", SQL_CA1_SELECT_FOR_UPDATE, NULL, 0},
            { "SQL_CA1_BULK_ADD", SQL_CA1_BULK_ADD, NULL, 0},
            { "SQL_CA1_BULK_UPDATE_BY_BOOKMARK", SQL_CA1_BULK_UPDATE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_DELETE_BY_BOOKMARK", SQL_CA1_BULK_DELETE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_FETCH_BY_BOOKMARK", SQL_CA1_BULK_FETCH_BY_BOOKMARK, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2", SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2, 
        {
            { "SQL_CA2_READ_ONLY_CONCURRENCY", SQL_CA2_READ_ONLY_CONCURRENCY, NULL, 0},
            { "SQL_CA2_LOCK_CONCURRENCY", SQL_CA2_LOCK_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_ROWVER_CONCURRENCY", SQL_CA2_OPT_ROWVER_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_VALUES_CONCURRENCY", SQL_CA2_OPT_VALUES_CONCURRENCY, NULL, 0},
            { "SQL_CA2_SENSITIVITY_ADDITIONS", SQL_CA2_SENSITIVITY_ADDITIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_DELETIONS", SQL_CA2_SENSITIVITY_DELETIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_UPDATES", SQL_CA2_SENSITIVITY_UPDATES, NULL, 0},
            { "SQL_CA2_MAX_ROWS_SELECT", SQL_CA2_MAX_ROWS_SELECT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_INSERT", SQL_CA2_MAX_ROWS_INSERT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_DELETE", SQL_CA2_MAX_ROWS_DELETE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_UPDATE", SQL_CA2_MAX_ROWS_UPDATE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_CATALOG", SQL_CA2_MAX_ROWS_CATALOG, NULL, 0},
            { "SQL_CA2_MAX_ROWS_AFFECTS_ALL", SQL_CA2_MAX_ROWS_AFFECTS_ALL, NULL, 0},
            { "SQL_CA2_CRC_EXACT", SQL_CA2_CRC_EXACT, NULL, 0},
            { "SQL_CA2_CRC_APPROXIMATE", SQL_CA2_CRC_APPROXIMATE, NULL, 0},
            { "SQL_CA2_SIMULATE_NON_UNIQUE", SQL_CA2_SIMULATE_NON_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_TRY_UNIQUE", SQL_CA2_SIMULATE_TRY_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_UNIQUE", SQL_CA2_SIMULATE_UNIQUE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_GETDATA_EXTENSIONS", SQL_GETDATA_EXTENSIONS, 
        {
            { "SQL_GD_ANY_COLUMN", SQL_GD_ANY_COLUMN, NULL, 0},
            { "SQL_GD_ANY_ORDER", SQL_GD_ANY_ORDER, NULL, 0},
            { "SQL_GD_BLOCK", SQL_GD_BLOCK, NULL, 0},
            { "SQL_GD_BOUND", SQL_GD_BOUND, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_GROUP_BY", SQL_GROUP_BY, 
        {
            { "SQL_GB_COLLATE", SQL_GB_COLLATE, NULL, 0},
            { "SQL_GB_NOT_SUPPORTED", SQL_GB_NOT_SUPPORTED, NULL, 0},
            { "SQL_GB_GROUP_BY_EQUALS_SELECT", SQL_GB_GROUP_BY_EQUALS_SELECT, NULL, 0},
            { "SQL_GB_GROUP_BY_CONTAINS_SELECT", SQL_GB_GROUP_BY_CONTAINS_SELECT, NULL, 0},
            { "SQL_GB_NO_RELATION", SQL_GB_NO_RELATION, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_IDENTIFIER_CASE", SQL_IDENTIFIER_CASE, 
        {
            { "SQL_IC_UPPER", SQL_IC_UPPER, NULL, 0},
            { "SQL_IC_LOWER", SQL_IC_LOWER, NULL, 0},
            { "SQL_IC_SENSITIVE", SQL_IC_SENSITIVE, NULL, 0},
            { "SQL_IC_MIXED", SQL_IC_MIXED, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_IDENTIFIER_QUOTE_CHAR", SQL_IDENTIFIER_QUOTE_CHAR, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_INDEX_KEYWORDS", SQL_INDEX_KEYWORDS, 
        {
            { "SQL_IK_NONE", SQL_IK_NONE, NULL, 0},
            { "SQL_IK_ASC", SQL_IK_ASC, NULL, 0},
            { "SQL_IK_DESC", SQL_IK_DESC, NULL, 0},
            { "SQL_IK_ALL", SQL_IK_ALL, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_INFO_SCHEMA_VIEWS", SQL_INFO_SCHEMA_VIEWS, 
        {
            { "SQL_ISV_ASSERTIONS", SQL_ISV_ASSERTIONS, NULL, 0},
            { "SQL_ISV_CHARACTER_SETS", SQL_ISV_CHARACTER_SETS, NULL, 0},
            { "SQL_ISV_CHECK_CONSTRAINTS", SQL_ISV_CHECK_CONSTRAINTS, NULL, 0},
            { "SQL_ISV_COLLATIONS", SQL_ISV_COLLATIONS, NULL, 0},
            { "SQL_ISV_COLUMN_DOMAIN_USAGE", SQL_ISV_COLUMN_DOMAIN_USAGE, NULL, 0},
            { "SQL_ISV_COLUMN_PRIVILEGES", SQL_ISV_COLUMN_PRIVILEGES, NULL, 0},
            { "SQL_ISV_COLUMNS", SQL_ISV_COLUMNS, NULL, 0},
            { "SQL_ISV_CONSTRAINT_COLUMN_USAGE", SQL_ISV_CONSTRAINT_COLUMN_USAGE, NULL, 0},
            { "SQL_ISV_CONSTRAINT_TABLE_USAGE", SQL_ISV_CONSTRAINT_TABLE_USAGE, NULL, 0},
            { "SQL_ISV_DOMAIN_CONSTRAINTS", SQL_ISV_DOMAIN_CONSTRAINTS, NULL, 0},
            { "SQL_ISV_DOMAINS", SQL_ISV_DOMAINS, NULL, 0},
            { "SQL_ISV_KEY_COLUMN_USAGE", SQL_ISV_KEY_COLUMN_USAGE, NULL, 0},
            { "SQL_ISV_REFERENTIAL_CONSTRAINTS", SQL_ISV_REFERENTIAL_CONSTRAINTS, NULL, 0},
            { "SQL_ISV_SCHEMATA", SQL_ISV_SCHEMATA, NULL, 0},
            { "SQL_ISV_SQL_LANGUAGES", SQL_ISV_SQL_LANGUAGES, NULL, 0},
            { "SQL_ISV_TABLE_CONSTRAINTS", SQL_ISV_TABLE_CONSTRAINTS, NULL, 0},
            { "SQL_ISV_TABLE_PRIVILEGES", SQL_ISV_TABLE_PRIVILEGES, NULL, 0},
            { "SQL_ISV_TABLES", SQL_ISV_TABLES, NULL, 0},
            { "SQL_ISV_TRANSLATIONS", SQL_ISV_TRANSLATIONS, NULL, 0},
            { "SQL_ISV_USAGE_PRIVILEGES", SQL_ISV_USAGE_PRIVILEGES, NULL, 0},
            { "SQL_ISV_VIEW_COLUMN_USAGE", SQL_ISV_VIEW_COLUMN_USAGE, NULL, 0},
            { "SQL_ISV_VIEW_TABLE_USAGE", SQL_ISV_VIEW_TABLE_USAGE, NULL, 0},
            { "SQL_ISV_VIEWS", SQL_ISV_VIEWS, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_INSERT_STATEMENT", SQL_INSERT_STATEMENT, 
        {
            { "SQL_IS_INSERT_LITERALS", SQL_IS_INSERT_LITERALS, NULL, 0},
            { "SQL_IS_INSERT_SEARCHED", SQL_IS_INSERT_SEARCHED, NULL, 0},
            { "SQL_IS_SELECT_INTO", SQL_IS_SELECT_INTO, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_INTEGRITY", SQL_INTEGRITY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_KEYSET_CURSOR_ATTRIBUTES1", SQL_KEYSET_CURSOR_ATTRIBUTES1, 
        {
            { "SQL_CA1_NEXT", SQL_CA1_NEXT, NULL, 0},
            { "SQL_CA1_ABSOLUTE", SQL_CA1_ABSOLUTE, NULL, 0},
            { "SQL_CA1_RELATIVE", SQL_CA1_RELATIVE, NULL, 0},
            { "SQL_CA1_BOOKMARK", SQL_CA1_BOOKMARK, NULL, 0},
            { "SQL_CA1_LOCK_EXCLUSIVE", SQL_CA1_LOCK_EXCLUSIVE, NULL, 0},
            { "SQL_CA1_LOCK_NO_CHANGE", SQL_CA1_LOCK_NO_CHANGE, NULL, 0},
            { "SQL_CA1_LOCK_UNLOCK", SQL_CA1_LOCK_UNLOCK, NULL, 0},
            { "SQL_CA1_POS_POSITION", SQL_CA1_POS_POSITION, NULL, 0},
            { "SQL_CA1_POS_UPDATE", SQL_CA1_POS_UPDATE, NULL, 0},
            { "SQL_CA1_POS_DELETE", SQL_CA1_POS_DELETE, NULL, 0},
            { "SQL_CA1_POS_REFRESH", SQL_CA1_POS_REFRESH, NULL, 0},
            { "SQL_CA1_POSITIONED_UPDATE", SQL_CA1_POSITIONED_UPDATE, NULL, 0},
            { "SQL_CA1_POSITIONED_DELETE", SQL_CA1_POSITIONED_DELETE, NULL, 0},
            { "SQL_CA1_SELECT_FOR_UPDATE", SQL_CA1_SELECT_FOR_UPDATE, NULL, 0},
            { "SQL_CA1_BULK_ADD", SQL_CA1_BULK_ADD, NULL, 0},
            { "SQL_CA1_BULK_UPDATE_BY_BOOKMARK", SQL_CA1_BULK_UPDATE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_DELETE_BY_BOOKMARK", SQL_CA1_BULK_DELETE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_FETCH_BY_BOOKMARK", SQL_CA1_BULK_FETCH_BY_BOOKMARK, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_KEYSET_CURSOR_ATTRIBUTES2", SQL_KEYSET_CURSOR_ATTRIBUTES2, 
        {
            { "SQL_CA2_READ_ONLY_CONCURRENCY", SQL_CA2_READ_ONLY_CONCURRENCY, NULL, 0},
            { "SQL_CA2_LOCK_CONCURRENCY", SQL_CA2_LOCK_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_ROWVER_CONCURRENCY", SQL_CA2_OPT_ROWVER_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_VALUES_CONCURRENCY", SQL_CA2_OPT_VALUES_CONCURRENCY, NULL, 0},
            { "SQL_CA2_SENSITIVITY_ADDITIONS", SQL_CA2_SENSITIVITY_ADDITIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_DELETIONS", SQL_CA2_SENSITIVITY_DELETIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_UPDATES", SQL_CA2_SENSITIVITY_UPDATES, NULL, 0},
            { "SQL_CA2_MAX_ROWS_SELECT", SQL_CA2_MAX_ROWS_SELECT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_INSERT", SQL_CA2_MAX_ROWS_INSERT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_DELETE", SQL_CA2_MAX_ROWS_DELETE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_UPDATE", SQL_CA2_MAX_ROWS_UPDATE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_CATALOG", SQL_CA2_MAX_ROWS_CATALOG, NULL, 0},
            { "SQL_CA2_MAX_ROWS_AFFECTS_ALL", SQL_CA2_MAX_ROWS_AFFECTS_ALL, NULL, 0},
            { "SQL_CA2_CRC_EXACT", SQL_CA2_CRC_EXACT, NULL, 0},
            { "SQL_CA2_CRC_APPROXIMATE", SQL_CA2_CRC_APPROXIMATE, NULL, 0},
            { "SQL_CA2_SIMULATE_NON_UNIQUE", SQL_CA2_SIMULATE_NON_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_TRY_UNIQUE", SQL_CA2_SIMULATE_TRY_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_UNIQUE", SQL_CA2_SIMULATE_UNIQUE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_KEYWORDS", SQL_KEYWORDS, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_LIKE_ESCAPE_CLAUSE", SQL_LIKE_ESCAPE_CLAUSE, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_MAX_ASYNC_CONCURRENT_STATEMENTS", SQL_MAX_ASYNC_CONCURRENT_STATEMENTS, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_MAX_BINARY_LITERAL_LEN", SQL_MAX_BINARY_LITERAL_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_MAX_CATALOG_NAME_LEN", SQL_MAX_CATALOG_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_CHAR_LITERAL_LEN", SQL_MAX_CHAR_LITERAL_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_MAX_COLUMN_NAME_LEN", SQL_MAX_COLUMN_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_COLUMNS_IN_GROUP_BY", SQL_MAX_COLUMNS_IN_GROUP_BY, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_COLUMNS_IN_INDEX", SQL_MAX_COLUMNS_IN_INDEX, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_COLUMNS_IN_ORDER_BY", SQL_MAX_COLUMNS_IN_ORDER_BY, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_COLUMNS_IN_SELECT", SQL_MAX_COLUMNS_IN_SELECT, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_COLUMNS_IN_TABLE", SQL_MAX_COLUMNS_IN_TABLE, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_CONCURRENT_ACTIVITIES", SQL_MAX_CONCURRENT_ACTIVITIES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_CURSOR_NAME_LEN", SQL_MAX_CURSOR_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_DRIVER_CONNECTIONS", SQL_MAX_DRIVER_CONNECTIONS, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_IDENTIFIER_LEN", SQL_MAX_IDENTIFIER_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_INDEX_SIZE", SQL_MAX_INDEX_SIZE, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_MAX_PROCEDURE_NAME_LEN", SQL_MAX_PROCEDURE_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_ROW_SIZE", SQL_MAX_ROW_SIZE, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, 0, 0
    },
    { "SQL_MAX_ROW_SIZE_INCLUDES_LONG", SQL_MAX_ROW_SIZE_INCLUDES_LONG, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_MAX_STATEMENT_LEN", SQL_MAX_STATEMENT_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_TABLE_NAME_LEN", SQL_MAX_TABLE_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_TABLES_IN_SELECT", SQL_MAX_TABLES_IN_SELECT, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MAX_USER_NAME_LEN", SQL_MAX_USER_NAME_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_MULT_RESULT_SETS", SQL_MULT_RESULT_SETS, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_MULTIPLE_ACTIVE_TXN", SQL_MULTIPLE_ACTIVE_TXN, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_NEED_LONG_DATA_LEN", SQL_NEED_LONG_DATA_LEN, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_NON_NULLABLE_COLUMNS", SQL_NON_NULLABLE_COLUMNS, 
        {
            { "SQL_NNC_NULL", SQL_NNC_NULL, NULL, 0}, 
            { "SQL_NNC_NON_NULL", SQL_NNC_NON_NULL, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_NULL_COLLATION", SQL_NULL_COLLATION, 
        {
            { "SQL_NC_END", SQL_NC_END, NULL, 0}, 
            { "SQL_NC_HIGH", SQL_NC_HIGH, NULL, 0}, 
            { "SQL_NC_LOW", SQL_NC_LOW, NULL, 0}, 
            { "SQL_NC_START", SQL_NC_START, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_NUMERIC_FUNCTIONS", SQL_NUMERIC_FUNCTIONS, 
        {
            { "SQL_FN_NUM_ABS", SQL_FN_NUM_ABS, NULL, 0}, 
            { "SQL_FN_NUM_ACOS", SQL_FN_NUM_ACOS, NULL, 0}, 
            { "SQL_FN_NUM_ASIN", SQL_FN_NUM_ASIN, NULL, 0}, 
            { "SQL_FN_NUM_ATAN", SQL_FN_NUM_ATAN, NULL, 0}, 
            { "SQL_FN_NUM_ATAN2", SQL_FN_NUM_ATAN2, NULL, 0}, 
            { "SQL_FN_NUM_CEILING", SQL_FN_NUM_CEILING, NULL, 0}, 
            { "SQL_FN_NUM_COS", SQL_FN_NUM_COS, NULL, 0}, 
            { "SQL_FN_NUM_COT", SQL_FN_NUM_COT, NULL, 0}, 
            { "SQL_FN_NUM_DEGREES", SQL_FN_NUM_DEGREES, NULL, 0}, 
            { "SQL_FN_NUM_EXP", SQL_FN_NUM_EXP, NULL, 0}, 
            { "SQL_FN_NUM_FLOOR", SQL_FN_NUM_FLOOR, NULL, 0}, 
            { "SQL_FN_NUM_LOG", SQL_FN_NUM_LOG, NULL, 0}, 
            { "SQL_FN_NUM_LOG10", SQL_FN_NUM_LOG10, NULL, 0}, 
            { "SQL_FN_NUM_MOD", SQL_FN_NUM_MOD, NULL, 0}, 
            { "SQL_FN_NUM_PI", SQL_FN_NUM_PI, NULL, 0}, 
            { "SQL_FN_NUM_POWER", SQL_FN_NUM_POWER, NULL, 0}, 
            { "SQL_FN_NUM_RADIANS", SQL_FN_NUM_RADIANS, NULL, 0}, 
            { "SQL_FN_NUM_RAND", SQL_FN_NUM_RAND, NULL, 0}, 
            { "SQL_FN_NUM_ROUND", SQL_FN_NUM_ROUND, NULL, 0}, 
            { "SQL_FN_NUM_SIGN", SQL_FN_NUM_SIGN, NULL, 0}, 
            { "SQL_FN_NUM_SIN", SQL_FN_NUM_SIN, NULL, 0}, 
            { "SQL_FN_NUM_SQRT", SQL_FN_NUM_SQRT, NULL, 0}, 
            { "SQL_FN_NUM_TAN", SQL_FN_NUM_TAN, NULL, 0}, 
            { "SQL_FN_NUM_TRUNCATE", SQL_FN_NUM_TRUNCATE, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_ODBC_INTERFACE_CONFORMANCE", SQL_ODBC_INTERFACE_CONFORMANCE, 
        {
            { "SQL_OIC_CORE", SQL_OIC_CORE, NULL, 0}, 
            { "SQL_OIC_LEVEL1", SQL_OIC_LEVEL1, NULL, 0}, 
            { "SQL_OIC_LEVEL2", SQL_OIC_LEVEL2, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ODBC_SAG_CLI_CONFORMANCE", SQL_ODBC_SAG_CLI_CONFORMANCE, 
        {
            { "SQL_OSCC_NOT_COMPLIANT", SQL_OSCC_NOT_COMPLIANT, NULL, 0}, 
            { "SQL_OSCC_COMPLIANT", SQL_OSCC_COMPLIANT, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ODBC_VER", SQL_ODBC_VER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_OJ_CAPABILITIES", SQL_OJ_CAPABILITIES, 
        {
            { "SQL_OJ_LEFT", SQL_OJ_LEFT, NULL, 0}, 
            { "SQL_OJ_RIGHT", SQL_OJ_RIGHT, NULL, 0}, 
            { "SQL_OJ_FULL", SQL_OJ_FULL, NULL, 0}, 
            { "SQL_OJ_NESTED", SQL_OJ_NESTED, NULL, 0}, 
            { "SQL_OJ_NOT_ORDERED", SQL_OJ_NOT_ORDERED, NULL, 0}, 
            { "SQL_OJ_INNER", SQL_OJ_INNER, NULL, 0}, 
            { "SQL_OJ_ALL_COMPARISON_OPS", SQL_OJ_ALL_COMPARISON_OPS, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "2.01", SQL_INTEGER, TRUE, 0
    },
    { "SQL_ORDER_BY_COLUMNS_IN_SELECT", SQL_ORDER_BY_COLUMNS_IN_SELECT, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_PARAM_ARRAY_ROW_COUNTS", SQL_PARAM_ARRAY_ROW_COUNTS, 
        {
            { "SQL_PARC_BATCH", SQL_PARC_BATCH, NULL, 0}, 
            { "SQL_PARC_NO_BATCH", SQL_PARC_NO_BATCH, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_PARAM_ARRAY_SELECTS", SQL_PARAM_ARRAY_SELECTS, 
        {
            { "SQL_PAS_BATCH", SQL_PAS_BATCH, NULL, 0}, 
            { "SQL_PAS_NO_BATCH", SQL_PAS_NO_BATCH, NULL, 0}, 
            { "SQL_PAS_NO_SELECT", SQL_PAS_NO_SELECT, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_PROCEDURE_TERM", SQL_PROCEDURE_TERM, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_PROCEDURES", SQL_PROCEDURES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_QUOTED_IDENTIFIER_CASE", SQL_QUOTED_IDENTIFIER_CASE, 
        {
            { "SQL_IC_UPPER", SQL_IC_UPPER, NULL, 0}, 
            { "SQL_IC_LOWER", SQL_IC_LOWER, NULL, 0}, 
            { "SQL_IC_SENSITIVE", SQL_IC_SENSITIVE, NULL, 0}, 
            { "SQL_IC_MIXED", SQL_IC_MIXED, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_ROW_UPDATES", SQL_ROW_UPDATES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_SCHEMA_TERM", SQL_SCHEMA_TERM, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_SCHEMA_USAGE", SQL_SCHEMA_USAGE, 
        {
            { "SQL_SU_DML_STATEMENTS", SQL_SU_DML_STATEMENTS, NULL, 0}, 
            { "SQL_SU_PROCEDURE_INVOCATION", SQL_SU_PROCEDURE_INVOCATION, NULL, 0}, 
            { "SQL_SU_TABLE_DEFINITION", SQL_SU_TABLE_DEFINITION, NULL, 0}, 
            { "SQL_SU_INDEX_DEFINITION", SQL_SU_INDEX_DEFINITION, NULL, 0}, 
            { "SQL_SU_PRIVILEGE_DEFINITION", SQL_SU_PRIVILEGE_DEFINITION, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SCROLL_OPTIONS", SQL_SCROLL_OPTIONS, 
        {
            { "SQL_SO_FORWARD_ONLY", SQL_SO_FORWARD_ONLY, NULL, 0}, 
            { "SQL_SO_STATIC", SQL_SO_STATIC, NULL, 0}, 
            { "SQL_SO_KEYSET_DRIVEN", SQL_SO_KEYSET_DRIVEN, NULL, 0}, 
            { "SQL_SO_DYNAMIC", SQL_SO_DYNAMIC, NULL, 0}, 
            { "SQL_SO_MIXED", SQL_SO_MIXED, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SEARCH_PATTERN_ESCAPE", SQL_SEARCH_PATTERN_ESCAPE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_SERVER_NAME", SQL_SERVER_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_SPECIAL_CHARACTERS", SQL_SPECIAL_CHARACTERS, 
        {
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_CHAR, 0, 0
    },
    { "SQL_SQL_CONFORMANCE", SQL_SQL_CONFORMANCE, 
        {
            { "SQL_SC_SQL92_ENTRY", SQL_SC_SQL92_ENTRY, NULL, 0}, 
            { "SQL_SC_FIPS127_2_TRANSITIONAL", SQL_SC_FIPS127_2_TRANSITIONAL, NULL, 0}, 
            { "SQL_SC_SQL92_FULL", SQL_SC_SQL92_FULL, NULL, 0}, 
            { "SQL_SC_SQL92_INTERMEDIATE", SQL_SC_SQL92_INTERMEDIATE, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_SQL92_DATETIME_FUNCTIONS", SQL_SQL92_DATETIME_FUNCTIONS, 
        {
            { "SQL_SDF_CURRENT_DATE", SQL_SDF_CURRENT_DATE, NULL, 0}, 
            { "SQL_SDF_CURRENT_TIME", SQL_SDF_CURRENT_TIME, NULL, 0}, 
            { "SQL_SDF_CURRENT_TIMESTAMP", SQL_SDF_CURRENT_TIMESTAMP, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_FOREIGN_KEY_DELETE_RULE", SQL_SQL92_FOREIGN_KEY_DELETE_RULE, 
        {
            { "SQL_SFKD_CASCADE", SQL_SFKD_CASCADE, NULL, 0}, 
            { "SQL_SFKD_NO_ACTION", SQL_SFKD_NO_ACTION, NULL, 0}, 
            { "SQL_SFKD_SET_DEFAULT", SQL_SFKD_SET_DEFAULT, NULL, 0}, 
            { "SQL_SFKD_SET_NULL", SQL_SFKD_SET_NULL, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_FOREIGN_KEY_UPDATE_RULE", SQL_SQL92_FOREIGN_KEY_UPDATE_RULE, 
        {
            { "SQL_SFKU_CASCADE", SQL_SFKU_CASCADE, NULL, 0}, 
            { "SQL_SFKU_NO_ACTION", SQL_SFKU_NO_ACTION, NULL, 0}, 
            { "SQL_SFKU_SET_DEFAULT", SQL_SFKU_SET_DEFAULT, NULL, 0}, 
            { "SQL_SFKU_SET_NULL", SQL_SFKU_SET_NULL, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_GRANT", SQL_SQL92_GRANT, 
        {
            { "SQL_SG_DELETE_TABLE", SQL_SG_DELETE_TABLE, NULL, 0}, 
            { "SQL_SG_INSERT_COLUMN", SQL_SG_INSERT_COLUMN, NULL, 0}, 
            { "SQL_SG_INSERT_TABLE", SQL_SG_INSERT_TABLE, NULL, 0}, 
            { "SQL_SG_REFERENCES_TABLE", SQL_SG_REFERENCES_TABLE, NULL, 0}, 
            { "SQL_SG_REFERENCES_COLUMN", SQL_SG_REFERENCES_COLUMN, NULL, 0}, 
            { "SQL_SG_SELECT_TABLE", SQL_SG_SELECT_TABLE, NULL, 0}, 
            { "SQL_SG_UPDATE_COLUMN", SQL_SG_UPDATE_COLUMN, NULL, 0}, 
            { "SQL_SG_UPDATE_TABLE", SQL_SG_UPDATE_TABLE, NULL, 0}, 
            { "SQL_SG_USAGE_ON_DOMAIN", SQL_SG_USAGE_ON_DOMAIN, NULL, 0}, 
            { "SQL_SG_USAGE_ON_CHARACTER_SET", SQL_SG_USAGE_ON_CHARACTER_SET, NULL, 0}, 
            { "SQL_SG_USAGE_ON_COLLATION", SQL_SG_USAGE_ON_COLLATION, NULL, 0}, 
            { "SQL_SG_USAGE_ON_TRANSLATION", SQL_SG_USAGE_ON_TRANSLATION, NULL, 0}, 
            { "SQL_SG_WITH_GRANT_OPTION", SQL_SG_WITH_GRANT_OPTION, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_NUMERIC_VALUE_FUNCTIONS", SQL_SQL92_NUMERIC_VALUE_FUNCTIONS, 
        {
            { "SQL_SNVF_BIT_LENGTH", SQL_SNVF_BIT_LENGTH, NULL, 0}, 
            { "SQL_SNVF_CHAR_LENGTH", SQL_SNVF_CHAR_LENGTH, NULL, 0}, 
            { "SQL_SNVF_CHARACTER_LENGTH", SQL_SNVF_CHARACTER_LENGTH, NULL, 0}, 
            { "SQL_SNVF_EXTRACT", SQL_SNVF_EXTRACT, NULL, 0}, 
            { "SQL_SNVF_OCTET_LENGTH", SQL_SNVF_OCTET_LENGTH, NULL, 0}, 
            { "SQL_SNVF_POSITION", SQL_SNVF_POSITION, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_PREDICATES", SQL_SQL92_PREDICATES, 
        {
            { "SQL_SP_BETWEEN", SQL_SP_BETWEEN, NULL, 0}, 
            { "SQL_SP_COMPARISON", SQL_SP_COMPARISON, NULL, 0}, 
            { "SQL_SP_EXISTS", SQL_SP_EXISTS, NULL, 0}, 
            { "SQL_SP_IN", SQL_SP_IN, NULL, 0}, 
            { "SQL_SP_ISNOTNULL", SQL_SP_ISNOTNULL, NULL, 0}, 
            { "SQL_SP_ISNULL", SQL_SP_ISNULL, NULL, 0}, 
            { "SQL_SP_LIKE", SQL_SP_LIKE, NULL, 0}, 
            { "SQL_SP_MATCH_FULL", SQL_SP_MATCH_FULL, NULL, 0}, 
            { "SQL_SP_MATCH_PARTIAL", SQL_SP_MATCH_PARTIAL, NULL, 0}, 
            { "SQL_SP_MATCH_UNIQUE_FULL", SQL_SP_MATCH_UNIQUE_FULL, NULL, 0}, 
            { "SQL_SP_MATCH_UNIQUE_PARTIAL", SQL_SP_MATCH_UNIQUE_PARTIAL, NULL, 0}, 
            { "SQL_SP_OVERLAPS", SQL_SP_OVERLAPS, NULL, 0}, 
            { "SQL_SP_QUANTIFIED_COMPARISON", SQL_SP_QUANTIFIED_COMPARISON, NULL, 0}, 
            { "SQL_SP_UNIQUE", SQL_SP_UNIQUE, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_RELATIONAL_JOIN_OPERATORS", SQL_SQL92_RELATIONAL_JOIN_OPERATORS, 
        {
            { "SQL_SRJO_CORRESPONDING_CLAUSE", SQL_SRJO_CORRESPONDING_CLAUSE, NULL, 0}, 
            { "SQL_SRJO_CROSS_JOIN", SQL_SRJO_CROSS_JOIN, NULL, 0}, 
            { "SQL_SRJO_EXCEPT_JOIN", SQL_SRJO_EXCEPT_JOIN, NULL, 0}, 
            { "SQL_SRJO_FULL_OUTER_JOIN", SQL_SRJO_FULL_OUTER_JOIN, NULL, 0}, 
            { "SQL_SRJO_INNER_JOIN", SQL_SRJO_INNER_JOIN, NULL, 0}, 
            { "SQL_SRJO_INTERSECT_JOIN", SQL_SRJO_INTERSECT_JOIN, NULL, 0}, 
            { "SQL_SRJO_LEFT_OUTER_JOIN", SQL_SRJO_LEFT_OUTER_JOIN, NULL, 0}, 
            { "SQL_SRJO_NATURAL_JOIN", SQL_SRJO_NATURAL_JOIN, NULL, 0}, 
            { "SQL_SRJO_RIGHT_OUTER_JOIN", SQL_SRJO_RIGHT_OUTER_JOIN, NULL, 0}, 
            { "SQL_SRJO_UNION_JOIN", SQL_SRJO_UNION_JOIN, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_REVOKE", SQL_SQL92_REVOKE, 
        {
            { "SQL_SR_CASCADE", SQL_SR_CASCADE, NULL, 0}, 
            { "SQL_SR_DELETE_TABLE", SQL_SR_DELETE_TABLE, NULL, 0}, 
            { "SQL_SR_GRANT_OPTION_FOR", SQL_SR_GRANT_OPTION_FOR, NULL, 0}, 
            { "SQL_SR_INSERT_COLUMN", SQL_SR_INSERT_COLUMN, NULL, 0}, 
            { "SQL_SR_INSERT_TABLE", SQL_SR_INSERT_TABLE, NULL, 0}, 
            { "SQL_SR_REFERENCES_COLUMN", SQL_SR_REFERENCES_COLUMN, NULL, 0}, 
            { "SQL_SR_REFERENCES_TABLE", SQL_SR_REFERENCES_TABLE, NULL, 0}, 
            { "SQL_SR_RESTRICT", SQL_SR_RESTRICT, NULL, 0}, 
            { "SQL_SR_SELECT_TABLE", SQL_SR_SELECT_TABLE, NULL, 0}, 
            { "SQL_SR_UPDATE_COLUMN", SQL_SR_UPDATE_COLUMN, NULL, 0}, 
            { "SQL_SR_UPDATE_TABLE", SQL_SR_UPDATE_TABLE, NULL, 0}, 
            { "SQL_SR_USAGE_ON_DOMAIN", SQL_SR_USAGE_ON_DOMAIN, NULL, 0}, 
            { "SQL_SR_USAGE_ON_CHARACTER_SET", SQL_SR_USAGE_ON_CHARACTER_SET, NULL, 0}, 
            { "SQL_SR_USAGE_ON_COLLATION", SQL_SR_USAGE_ON_COLLATION, NULL, 0}, 
            { "SQL_SR_USAGE_ON_TRANSLATION", SQL_SR_USAGE_ON_TRANSLATION, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_ROW_VALUE_CONSTRUCTOR", SQL_SQL92_ROW_VALUE_CONSTRUCTOR, 
        {
            { "SQL_SRVC_VALUE_EXPRESSION", SQL_SRVC_VALUE_EXPRESSION, NULL, 0}, 
            { "SQL_SRVC_NULL", SQL_SRVC_NULL, NULL, 0}, 
            { "SQL_SRVC_DEFAULT", SQL_SRVC_DEFAULT, NULL, 0}, 
            { "SQL_SRVC_ROW_SUBQUERY", SQL_SRVC_ROW_SUBQUERY, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_STRING_FUNCTIONS", SQL_SQL92_STRING_FUNCTIONS, 
        {
            { "SQL_SSF_CONVERT", SQL_SSF_CONVERT, NULL, 0}, 
            { "SQL_SSF_LOWER", SQL_SSF_LOWER, NULL, 0}, 
            { "SQL_SSF_UPPER", SQL_SSF_UPPER, NULL, 0}, 
            { "SQL_SSF_SUBSTRING", SQL_SSF_SUBSTRING, NULL, 0}, 
            { "SQL_SSF_TRANSLATE", SQL_SSF_TRANSLATE, NULL, 0}, 
            { "SQL_SSF_TRIM_BOTH", SQL_SSF_TRIM_BOTH, NULL, 0}, 
            { "SQL_SSF_TRIM_LEADING", SQL_SSF_TRIM_LEADING, NULL, 0}, 
            { "SQL_SSF_TRIM_TRAILING", SQL_SSF_TRIM_TRAILING, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SQL92_VALUE_EXPRESSIONS", SQL_SQL92_VALUE_EXPRESSIONS, 
        {
            { "SQL_SVE_CASE", SQL_SVE_CASE, NULL, 0}, 
            { "SQL_SVE_CAST", SQL_SVE_CAST, NULL, 0}, 
            { "SQL_SVE_COALESCE", SQL_SVE_COALESCE, NULL, 0}, 
            { "SQL_SVE_NULLIF", SQL_SVE_NULLIF, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_STANDARD_CLI_CONFORMANCE", SQL_STANDARD_CLI_CONFORMANCE, 
        {
            { "SQL_SCC_XOPEN_CLI_VERSION1", SQL_SCC_XOPEN_CLI_VERSION1, NULL, 0}, 
            { "SQL_SCC_ISO92_CLI", SQL_SCC_ISO92_CLI, NULL, 0}, 
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_STATIC_CURSOR_ATTRIBUTES1", SQL_STATIC_CURSOR_ATTRIBUTES1, 
        {
            { "SQL_CA1_NEXT", SQL_CA1_NEXT, NULL, 0},
            { "SQL_CA1_ABSOLUTE", SQL_CA1_ABSOLUTE, NULL, 0},
            { "SQL_CA1_RELATIVE", SQL_CA1_RELATIVE, NULL, 0},
            { "SQL_CA1_BOOKMARK", SQL_CA1_BOOKMARK, NULL, 0},
            { "SQL_CA1_LOCK_EXCLUSIVE", SQL_CA1_LOCK_EXCLUSIVE, NULL, 0},
            { "SQL_CA1_LOCK_NO_CHANGE", SQL_CA1_LOCK_NO_CHANGE, NULL, 0},
            { "SQL_CA1_LOCK_UNLOCK", SQL_CA1_LOCK_UNLOCK, NULL, 0},
            { "SQL_CA1_POS_POSITION", SQL_CA1_POS_POSITION, NULL, 0},
            { "SQL_CA1_POS_UPDATE", SQL_CA1_POS_UPDATE, NULL, 0},
            { "SQL_CA1_POS_DELETE", SQL_CA1_POS_DELETE, NULL, 0},
            { "SQL_CA1_POS_REFRESH", SQL_CA1_POS_REFRESH, NULL, 0},
            { "SQL_CA1_POSITIONED_UPDATE", SQL_CA1_POSITIONED_UPDATE, NULL, 0},
            { "SQL_CA1_POSITIONED_DELETE", SQL_CA1_POSITIONED_DELETE, NULL, 0},
            { "SQL_CA1_SELECT_FOR_UPDATE", SQL_CA1_SELECT_FOR_UPDATE, NULL, 0},
            { "SQL_CA1_BULK_ADD", SQL_CA1_BULK_ADD, NULL, 0},
            { "SQL_CA1_BULK_UPDATE_BY_BOOKMARK", SQL_CA1_BULK_UPDATE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_DELETE_BY_BOOKMARK", SQL_CA1_BULK_DELETE_BY_BOOKMARK, NULL, 0},
            { "SQL_CA1_BULK_FETCH_BY_BOOKMARK", SQL_CA1_BULK_FETCH_BY_BOOKMARK, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_STATIC_CURSOR_ATTRIBUTES2", SQL_STATIC_CURSOR_ATTRIBUTES2, 
        {
            { "SQL_CA2_READ_ONLY_CONCURRENCY", SQL_CA2_READ_ONLY_CONCURRENCY, NULL, 0},
            { "SQL_CA2_LOCK_CONCURRENCY", SQL_CA2_LOCK_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_ROWVER_CONCURRENCY", SQL_CA2_OPT_ROWVER_CONCURRENCY, NULL, 0},
            { "SQL_CA2_OPT_VALUES_CONCURRENCY", SQL_CA2_OPT_VALUES_CONCURRENCY, NULL, 0},
            { "SQL_CA2_SENSITIVITY_ADDITIONS", SQL_CA2_SENSITIVITY_ADDITIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_DELETIONS", SQL_CA2_SENSITIVITY_DELETIONS, NULL, 0},
            { "SQL_CA2_SENSITIVITY_UPDATES", SQL_CA2_SENSITIVITY_UPDATES, NULL, 0},
            { "SQL_CA2_MAX_ROWS_SELECT", SQL_CA2_MAX_ROWS_SELECT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_INSERT", SQL_CA2_MAX_ROWS_INSERT, NULL, 0},
            { "SQL_CA2_MAX_ROWS_DELETE", SQL_CA2_MAX_ROWS_DELETE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_UPDATE", SQL_CA2_MAX_ROWS_UPDATE, NULL, 0},
            { "SQL_CA2_MAX_ROWS_CATALOG", SQL_CA2_MAX_ROWS_CATALOG, NULL, 0},
            { "SQL_CA2_MAX_ROWS_AFFECTS_ALL", SQL_CA2_MAX_ROWS_AFFECTS_ALL, NULL, 0},
            { "SQL_CA2_CRC_EXACT", SQL_CA2_CRC_EXACT, NULL, 0},
            { "SQL_CA2_CRC_APPROXIMATE", SQL_CA2_CRC_APPROXIMATE, NULL, 0},
            { "SQL_CA2_SIMULATE_NON_UNIQUE", SQL_CA2_SIMULATE_NON_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_TRY_UNIQUE", SQL_CA2_SIMULATE_TRY_UNIQUE, NULL, 0},
            { "SQL_CA2_SIMULATE_UNIQUE", SQL_CA2_SIMULATE_UNIQUE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_STRING_FUNCTIONS", SQL_STRING_FUNCTIONS, 
        {
            { "SQL_FN_STR_ASCII", SQL_FN_STR_ASCII, NULL, 0},
            { "SQL_FN_STR_BIT_LENGTH", SQL_FN_STR_BIT_LENGTH, NULL, 0},
            { "SQL_FN_STR_CHAR", SQL_FN_STR_CHAR, NULL, 0},
            { "SQL_FN_STR_CHAR_LENGTH", SQL_FN_STR_CHAR_LENGTH, NULL, 0},
            { "SQL_FN_STR_CHARACTER_LENGTH", SQL_FN_STR_CHARACTER_LENGTH, NULL, 0},
            { "SQL_FN_STR_CONCAT", SQL_FN_STR_CONCAT, NULL, 0},
            { "SQL_FN_STR_DIFFERENCE", SQL_FN_STR_DIFFERENCE, NULL, 0},
            { "SQL_FN_STR_INSERT", SQL_FN_STR_INSERT, NULL, 0},
            { "SQL_FN_STR_LCASE", SQL_FN_STR_LCASE, NULL, 0},
            { "SQL_FN_STR_LEFT", SQL_FN_STR_LEFT, NULL, 0},
            { "SQL_FN_STR_LENGTH", SQL_FN_STR_LENGTH, NULL, 0},
            { "SQL_FN_STR_LOCATE", SQL_FN_STR_LOCATE, NULL, 0},
            { "SQL_FN_STR_LTRIM", SQL_FN_STR_LTRIM, NULL, 0},
            { "SQL_FN_STR_OCTET_LENGTH", SQL_FN_STR_OCTET_LENGTH, NULL, 0},
            { "SQL_FN_STR_POSITION", SQL_FN_STR_POSITION, NULL, 0},
            { "SQL_FN_STR_REPEAT", SQL_FN_STR_REPEAT, NULL, 0},
            { "SQL_FN_STR_REPLACE", SQL_FN_STR_REPLACE, NULL, 0},
            { "SQL_FN_STR_RIGHT", SQL_FN_STR_RIGHT, NULL, 0},
            { "SQL_FN_STR_RTRIM", SQL_FN_STR_RTRIM, NULL, 0},
            { "SQL_FN_STR_SOUNDEX", SQL_FN_STR_SOUNDEX, NULL, 0},
            { "SQL_FN_STR_SPACE", SQL_FN_STR_SPACE, NULL, 0},
            { "SQL_FN_STR_SUBSTRING", SQL_FN_STR_SUBSTRING, NULL, 0},
            { "SQL_FN_STR_UCASE", SQL_FN_STR_UCASE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SUBQUERIES", SQL_SUBQUERIES, 
        {
            { "SQL_SQ_CORRELATED_SUBQUERIES", SQL_SQ_CORRELATED_SUBQUERIES, NULL, 0},
            { "SQL_SQ_COMPARISON", SQL_SQ_COMPARISON, NULL, 0},
            { "SQL_SQ_EXISTS", SQL_SQ_EXISTS, NULL, 0},
            { "SQL_SQ_IN", SQL_SQ_IN, NULL, 0},
            { "SQL_SQ_QUANTIFIED", SQL_SQ_QUANTIFIED, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_SYSTEM_FUNCTIONS", SQL_SYSTEM_FUNCTIONS, 
        {
            { "SQL_FN_SYS_DBNAME", SQL_FN_SYS_DBNAME, NULL, 0},
            { "SQL_FN_SYS_IFNULL", SQL_FN_SYS_IFNULL, NULL, 0},
            { "SQL_FN_SYS_USERNAME", SQL_FN_SYS_USERNAME, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_TABLE_TERM", SQL_TABLE_TERM, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_TIMEDATE_ADD_INTERVALS", SQL_TIMEDATE_ADD_INTERVALS, 
        {
            { "SQL_FN_TSI_FRAC_SECOND", SQL_FN_TSI_FRAC_SECOND, NULL, 0},
            { "SQL_FN_TSI_SECOND", SQL_FN_TSI_SECOND, NULL, 0},
            { "SQL_FN_TSI_MINUTE", SQL_FN_TSI_MINUTE, NULL, 0},
            { "SQL_FN_TSI_HOUR", SQL_FN_TSI_HOUR, NULL, 0},
            { "SQL_FN_TSI_DAY", SQL_FN_TSI_DAY, NULL, 0},
            { "SQL_FN_TSI_WEEK", SQL_FN_TSI_WEEK, NULL, 0},
            { "SQL_FN_TSI_MONTH", SQL_FN_TSI_MONTH, NULL, 0},
            { "SQL_FN_TSI_QUARTER", SQL_FN_TSI_QUARTER, NULL, 0},
            { "SQL_FN_TSI_YEAR", SQL_FN_TSI_YEAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_TIMEDATE_DIFF_INTERVALS", SQL_TIMEDATE_DIFF_INTERVALS, 
        {
            { "SQL_FN_TSI_FRAC_SECOND", SQL_FN_TSI_FRAC_SECOND, NULL, 0},
            { "SQL_FN_TSI_SECOND", SQL_FN_TSI_SECOND, NULL, 0},
            { "SQL_FN_TSI_MINUTE", SQL_FN_TSI_MINUTE, NULL, 0},
            { "SQL_FN_TSI_HOUR", SQL_FN_TSI_HOUR, NULL, 0},
            { "SQL_FN_TSI_DAY", SQL_FN_TSI_DAY, NULL, 0},
            { "SQL_FN_TSI_WEEK", SQL_FN_TSI_WEEK, NULL, 0},
            { "SQL_FN_TSI_MONTH", SQL_FN_TSI_MONTH, NULL, 0},
            { "SQL_FN_TSI_QUARTER", SQL_FN_TSI_QUARTER, NULL, 0},
            { "SQL_FN_TSI_YEAR", SQL_FN_TSI_YEAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_TIMEDATE_FUNCTIONS", SQL_TIMEDATE_FUNCTIONS, 
        {
            { "SQL_FN_TD_CURRENT_DATE", SQL_FN_TD_CURRENT_DATE, NULL, 0},
            { "SQL_FN_TD_CURRENT_TIME", SQL_FN_TD_CURRENT_TIME, NULL, 0},
            { "SQL_FN_TD_CURRENT_TIMESTAMP", SQL_FN_TD_CURRENT_TIMESTAMP, NULL, 0},
            { "SQL_FN_TD_CURDATE", SQL_FN_TD_CURDATE, NULL, 0},
            { "SQL_FN_TD_CURTIME", SQL_FN_TD_CURTIME, NULL, 0},
            { "SQL_FN_TD_DAYNAME", SQL_FN_TD_DAYNAME, NULL, 0},
            { "SQL_FN_TD_DAYOFMONTH", SQL_FN_TD_DAYOFMONTH, NULL, 0},
            { "SQL_FN_TD_DAYOFWEEK", SQL_FN_TD_DAYOFWEEK, NULL, 0},
            { "SQL_FN_TD_DAYOFYEAR", SQL_FN_TD_DAYOFYEAR, NULL, 0},
            { "SQL_FN_TD_EXTRACT", SQL_FN_TD_EXTRACT, NULL, 0},
            { "SQL_FN_TD_HOUR", SQL_FN_TD_HOUR, NULL, 0},
            { "SQL_FN_TD_MINUTE", SQL_FN_TD_MINUTE, NULL, 0},
            { "SQL_FN_TD_MONTH", SQL_FN_TD_MONTH, NULL, 0},
            { "SQL_FN_TD_MONTHNAME", SQL_FN_TD_MONTHNAME, NULL, 0},
            { "SQL_FN_TD_NOW", SQL_FN_TD_NOW, NULL, 0},
            { "SQL_FN_TD_QUARTER", SQL_FN_TD_QUARTER, NULL, 0},
            { "SQL_FN_TD_SECOND", SQL_FN_TD_SECOND, NULL, 0},
            { "SQL_FN_TD_TIMESTAMPADD", SQL_FN_TD_TIMESTAMPADD, NULL, 0},
            { "SQL_FN_TD_TIMESTAMPDIFF", SQL_FN_TD_TIMESTAMPDIFF, NULL, 0},
            { "SQL_FN_TD_WEEK", SQL_FN_TD_WEEK, NULL, 0},
            { "SQL_FN_TD_YEAR", SQL_FN_TD_YEAR, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_TXN_CAPABLE", SQL_TXN_CAPABLE, 
        {
            { "SQL_TC_NONE", SQL_TC_NONE, NULL, 0},
            { "SQL_TC_DML", SQL_TC_DML, NULL, 0},
            { "SQL_TC_DDL_COMMIT", SQL_TC_DDL_COMMIT, NULL, 0},
            { "SQL_TC_DDL_IGNORE", SQL_TC_DDL_IGNORE, NULL, 0},
            { "SQL_TC_ALL", SQL_TC_ALL, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_SMALLINT, 0, 0
    },
    { "SQL_TXN_ISOLATION_OPTION", SQL_TXN_ISOLATION_OPTION, 
        {
            { "SQL_TXN_READ_UNCOMMITTED", SQL_TXN_READ_UNCOMMITTED, NULL, 0},
            { "SQL_TXN_READ_COMMITTED", SQL_TXN_READ_COMMITTED, NULL, 0},
            { "SQL_TXN_REPEATABLE_READ", SQL_TXN_REPEATABLE_READ, NULL, 0},
            { "SQL_TXN_SERIALIZABLE", SQL_TXN_SERIALIZABLE, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_UNION", SQL_UNION, 
        {
            { "SQL_U_UNION", SQL_U_UNION, NULL, 0},
            { "SQL_U_UNION_ALL", SQL_U_UNION_ALL, NULL, 0},
            { NULL, 0, NULL, 0}
        }, "2.0", SQL_INTEGER, TRUE, 0
    },
    { "SQL_USER_NAME", SQL_USER_NAME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_CHAR, 0, 0
    },
    { "SQL_XOPEN_CLI_YEAR", SQL_XOPEN_CLI_YEAR, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_CHAR, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0 } }, NULL, 0, 0, 0 }
};

void dDriverConnect::out_str_clkd()
{
    if ( out_str_valid -> isChecked() )
        out_str_valid -> setText( "OutConnectionString: SQL_NULL_POINTER" );
    else
        out_str_valid -> setText( "OutConnectionString: VALID" );
}

void dDriverConnect::strlen_clkd()
{
    if ( strlen_valid -> isChecked() )
        strlen_valid -> setText( "StrLenPtr: SQL_NULL_POINTER" );
    else
        strlen_valid -> setText( "StrLenPtr: VALID" );
}

void dDriverConnect::Ok()
{
    const char *in_string, *string_len;
    SQLCHAR *conn_str_in;
    SQLCHAR *out_string;
    SQLINTEGER in_string_len, con_str_out_max;
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle;
    SQLSMALLINT con_str_out, *ptr_con_str_out;
    SQLUSMALLINT dc_type;
    int index;
    QString qstring_len, qin_string;

    if ( hand )
        in_handle = hand -> getHandle();

    qstring_len = str_len -> currentText();
    string_len = qstring_len.toAscii().constData();

    odbctest -> out_win -> insertLineLimited( "SQLDriverConnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    txt.sprintf( "    Window Handle: NULL" );
    odbctest -> out_win -> insertLineLimited( txt );

    qin_string = in_str -> currentText();
    in_string = qin_string.toAscii().constData();

    if ( strcmp( in_string, "<null ptr>" ) == 0 )
    {
        conn_str_in = NULL;
        odbctest -> out_win -> insertLineLimited( "    InConnectionString: <null ptr>" );
    }
    else if ( strcmp( in_string, "<empty string>" ) == 0 )
    {
        conn_str_in = ( SQLCHAR * ) "";
        odbctest -> out_win -> insertLineLimited( "    InConnectionString: <empty string>" );
    }
    else
    {
        txt.sprintf( "    InConnectionString: %s", in_string );
        conn_str_in = ( SQLCHAR * ) in_string;
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( string_len, "SQL_NTS", 7 ) == 0 )
    {
        in_string_len = SQL_NTS;
        txt.sprintf( "    StringLength1: SQL_NTS=-3" );
    }
    else
    {
        in_string_len = atoi( string_len );
        txt.sprintf( "    StringLength1: %d", in_string_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out_max = buffer_len -> text().toInt();

    if ( out_str_valid -> isChecked())
    {
        out_string = ( SQLCHAR * ) NULL;
    }
    else if ( con_str_out_max < 300 )
    {
        out_string = new SQLCHAR[ 300 ];    
    }
    else
    {
        out_string = new SQLCHAR[ con_str_out_max ];    
    }

    if ( out_string )
    {
        txt.sprintf( "    OutConnectionString: %p", out_string );
    }
    else
    {
        txt.sprintf( "    OutConnectionString: NULL_POINTER" );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    txt.sprintf( "    Buffer Length %d", con_str_out_max );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strlen_valid -> isChecked())
    {
        ptr_con_str_out = NULL;
        txt.sprintf( "    StringLengthPtr: NULL_POINTER" );
    }
    else
    {
        ptr_con_str_out = &con_str_out;
        txt.sprintf( "    StringLengthPtr: %p", ptr_con_str_out );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out = -9999;

    index = driver_completion -> currentIndex(); 

    dc_type = dc_options[ index ].attr;
    txt.sprintf( "    Driver Complete: %s=%d (%s)", dc_options[ index ].text,
                 dc_options[ index ].attr, dc_options[ index ].version );
    odbctest -> out_win -> insertLineLimited( txt );

    SQLRETURN ret = SQLDriverConnect( in_handle, 
                                      NULL,
                                      conn_str_in,
                                      in_string_len,
                                      out_string,
                                      con_str_out_max,
                                      ptr_con_str_out,
                                      dc_type );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        if ( out_string )
        {
            txt.sprintf( "    OutConnectionString: %s", out_string );
            odbctest -> out_win -> insertLineLimited( txt );
        }

        if ( ptr_con_str_out )
        {
            if ( con_str_out == -9999 )
            {
                txt.sprintf( "    *StrLenPtr: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *StrLenPtr: %d", con_str_out );
            }
            odbctest -> out_win -> insertLineLimited( txt );
        }
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dDriverConnect::dDriverConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 100, 15, 150, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle -> setGeometry( 10, 15, 80, 20 );

    in_str = new QComboBox( this );
    in_str->setEditable( true );
    in_str -> setGeometry( 130, 50, 300, 20 );
    l_in_str = new QLabel( "InConnectionString:", this );
    l_in_str -> setGeometry( 10, 50, 90, 20 );
    in_str -> insertItem( 0, "<null ptr>" );
    in_str -> insertItem( 1, "<empty string>" );

    str_len = new QComboBox( this );
    str_len->setEditable( true );
    str_len -> setGeometry( 130, 80, 150, 20 );
    l_str_len = new QLabel( "StringLength1:", this );
    l_str_len -> setGeometry( 10, 80, 90, 20 );
    str_len -> insertItem( 0, "SQL_NTS=-3" );
    str_len -> insertItem( 1, "0" );

    out_str_valid = new QCheckBox( "OutConnectionString: VALID", this );
    out_str_valid -> setGeometry( 10, 110, 300, 15 );

    strlen_valid = new QCheckBox( "StrLenPtr: VALID", this );
    strlen_valid -> setGeometry( 10, 140, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len -> setGeometry( 400, 80, 70, 20 );
    buffer_len -> setMaxLength( 6 );
    buffer_len -> setText( "300" );

    l_buffer_len = new QLabel( "Buffer Len:", this );
    l_buffer_len -> setGeometry( 320, 80, 60, 20 );

    driver_completion = new QComboBox( this );
    driver_completion -> setGeometry( 100, 170, 300, 20 );

    parent->fill_list_box( dc_options, driver_completion );

    l_driver_completion = new QLabel( "Driver Completion:", this );
    l_driver_completion -> setGeometry( 10, 170, 80, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( out_str_valid, SIGNAL( clicked()), this, SLOT( out_str_clkd()));
    connect( strlen_valid, SIGNAL( clicked()), this, SLOT( strlen_clkd()));
}

dDriverConnect::~dDriverConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete in_str;
    delete str_len;
    delete l_handle;
    delete l_in_str;
    delete l_str_len;
    delete out_str_valid;
    delete strlen_valid;
    delete buffer_len;
    delete l_buffer_len;
    delete driver_completion;
    delete l_driver_completion;
}

void dBrowseConnect::out_str_clkd()
{
    if ( out_str_valid -> isChecked() )
        out_str_valid -> setText( "OutConnectionString: SQL_NULL_POINTER" );
    else
        out_str_valid -> setText( "OutConnectionString: VALID" );
}

void dBrowseConnect::strlen_clkd()
{
    if ( strlen_valid -> isChecked() )
        strlen_valid -> setText( "StrLenPtr: SQL_NULL_POINTER" );
    else
        strlen_valid -> setText( "StrLenPtr: VALID" );
}

void dBrowseConnect::Ok()
{
    const char *in_string, *string_len;
    SQLCHAR *conn_str_in;
    SQLCHAR *out_string;
    SQLINTEGER in_string_len, con_str_out_max;
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle;
    SQLSMALLINT con_str_out, *ptr_con_str_out;
    QString qstring_len, qin_string;

    if ( hand )
        in_handle = hand -> getHandle();

    qstring_len = str_len -> currentText();
    string_len = qstring_len.toAscii().constData(); 

    odbctest -> out_win -> insertLineLimited( "SQLBrowseConnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    qin_string = in_str -> currentText();
    in_string = qin_string.toAscii().constData();

    if ( strcmp( in_string, "<null ptr>" ) == 0 )
    {
        conn_str_in = NULL;
        odbctest -> out_win -> insertLineLimited( "    InConnectionString: <null ptr>" );
    }
    else if ( strcmp( in_string, "<empty string>" ) == 0 )
    {
        conn_str_in = ( SQLCHAR * ) "";
        odbctest -> out_win -> insertLineLimited( "    InConnectionString: <empty string>" );
    }
    else
    {
        txt.sprintf( "    InConnectionString: %s", in_string );
        conn_str_in = ( SQLCHAR * ) in_string;
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( string_len, "SQL_NTS", 7 ) == 0 )
    {
        in_string_len = SQL_NTS;
        txt.sprintf( "    StringLength1: SQL_NTS=-3" );
    }
    else
    {
        in_string_len = atoi( string_len );
        txt.sprintf( "    StringLength1: %d", in_string_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out_max = buffer_len -> text().toInt();

    if ( out_str_valid -> isChecked())
    {
        out_string = ( SQLCHAR * ) NULL;
    }
    else if ( con_str_out_max < 300 )
    {
        out_string = new SQLCHAR[ 300 ];    
    }
    else
    {
        out_string = new SQLCHAR[ con_str_out_max ];    
    }

    if ( out_string )
    {
        txt.sprintf( "    OutConnectionString: %p", out_string );
    }
    else
    {
        txt.sprintf( "    OutConnectionString: NULL_POINTER" );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    txt.sprintf( "    Buffer Length %d", con_str_out_max );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strlen_valid -> isChecked())
    {
        ptr_con_str_out = NULL;
        txt.sprintf( "    StringLengthPtr: NULL_POINTER" );
    }
    else
    {
        ptr_con_str_out = &con_str_out;
        txt.sprintf( "    StringLengthPtr: %p", ptr_con_str_out );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out = -9999;

    SQLRETURN ret = SQLBrowseConnect( in_handle, 
                                      conn_str_in,
                                      in_string_len,
                                      out_string,
                                      con_str_out_max,
                                      ptr_con_str_out );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ) || (SQL_NEED_DATA == ret))
    {
        if ( out_string )
        {
            txt.sprintf( "    OutConnectionString: %s", out_string );
            odbctest -> out_win -> insertLineLimited( txt );
        }

        if ( ptr_con_str_out )
        {
            if ( con_str_out == -9999 )
            {
                txt.sprintf( "    *StrLenPtr: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *StrLenPtr: %d", con_str_out );
            }
            odbctest -> out_win -> insertLineLimited( txt );
        }
    }

    if ( out_string )
    {
        delete out_string;
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dBrowseConnect::dBrowseConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 100, 15, 150, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle -> setGeometry( 10, 15, 80, 20 );

    in_str = new QComboBox( this );
    in_str->setEditable( true );
    in_str -> setGeometry( 130, 50, 300, 20 );
    l_in_str = new QLabel( "InConnectionString:", this );
    l_in_str -> setGeometry( 10, 50, 90, 20 );
    in_str -> insertItem( 0, "<null ptr>" );
    in_str -> insertItem( 1, "<empty string>" );

    str_len = new QComboBox( this );
    str_len->setEditable( true );
    str_len -> setGeometry( 130, 80, 150, 20 );
    l_str_len = new QLabel( "StringLength1:", this );
    l_str_len -> setGeometry( 10, 80, 90, 20 );
    str_len -> insertItem( 0, "SQL_NTS=-3" );
    str_len -> insertItem( 1, "0" );

    out_str_valid = new QCheckBox( "OutConnectionString: VALID", this );
    out_str_valid -> setGeometry( 10, 110, 300, 15 );

    strlen_valid = new QCheckBox( "StrLenPtr: VALID", this );
    strlen_valid -> setGeometry( 10, 140, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len -> setGeometry( 400, 80, 70, 20 );
    buffer_len -> setMaxLength( 6 );
    buffer_len -> setText( "300" );

    l_buffer_len = new QLabel( "Buffer Len:", this );
    l_buffer_len -> setGeometry( 320, 80, 60, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( out_str_valid, SIGNAL( clicked()), this, SLOT( out_str_clkd()));
    connect( strlen_valid, SIGNAL( clicked()), this, SLOT( strlen_clkd()));
}

dBrowseConnect::~dBrowseConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete in_str;
    delete str_len;
    delete l_handle;
    delete l_in_str;
    delete l_str_len;
    delete out_str_valid;
    delete strlen_valid;
    delete buffer_len;
    delete l_buffer_len;
}

void dConnect::Ok()
{
    const char *dsn, *usr, *pwd, *ldsn, *lusr, *lpwd;
    QString qdsn, qusr, qpwd, qldsn, qlusr, qlpwd;
    int dsn_len, usr_len, pwd_len;
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle;

    if ( hand )
        in_handle = hand -> getHandle();

    qdsn = server -> currentText();
    qusr = user -> currentText();
    qpwd = auth -> currentText();
    qldsn = server_len -> currentText();
    qlusr = user_len -> currentText();
    qlpwd = auth_len -> currentText();

    dsn = qdsn.toAscii().constData();
    usr = qusr.toAscii().constData();
    pwd = qpwd.toAscii().constData();
    ldsn = qldsn.toAscii().constData();
    lusr = qlusr.toAscii().constData();
    lpwd = qlpwd.toAscii().constData();

    odbctest -> out_win -> insertLineLimited( "SQLConnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strcmp( dsn, "<null ptr>" ) == 0 )
    {
        dsn = NULL;
        odbctest -> out_win -> insertLineLimited( "    Server: <null ptr>" );
    }
    else if ( strcmp( dsn, "<empty string>" ) == 0 )
    {
        dsn = "";
        odbctest -> out_win -> insertLineLimited( "    Server: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Server: %s", dsn );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( ldsn, "SQL_NTS", 7 ) == 0 )
    {
        dsn_len = SQL_NTS;
        txt.sprintf( "    Server Len: SQL_NTS=-3" );
    }
    else
    {
        dsn_len = atoi( ldsn );
        txt.sprintf( "    Server Len: %d", dsn_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strcmp( usr, "<null ptr>" ) == 0 )
    {
        usr = NULL;
        odbctest -> out_win -> insertLineLimited( "    User: <null ptr>" );
    }
    else if ( strcmp( usr, "<empty string>" ) == 0 )
    {
        usr = "";
        odbctest -> out_win -> insertLineLimited( "    User: <empty string>" );
    }
    else
    {
        txt.sprintf( "    User: %s", usr );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( lusr, "SQL_NTS", 7 ) == 0 )
    {
        usr_len = SQL_NTS;
        txt.sprintf( "    User Len: SQL_NTS=-3" );
    }
    else
    {
        usr_len = atoi( lusr );
        txt.sprintf( "    User Len: %d", usr_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strcmp( pwd, "<null ptr>" ) == 0 )
    {
        pwd = NULL;
        odbctest -> out_win -> insertLineLimited( "    Auth: <null ptr>" );
    }
    else if ( strcmp( pwd, "<empty string>" ) == 0 )
    {
        pwd = "";
        odbctest -> out_win -> insertLineLimited( "    Auth: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Auth: %s", usr );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( lpwd,  "SQL_NTS", 7 ) == 0 )
    {
        pwd_len = SQL_NTS;
        txt.sprintf( "    Auth Len: SQL_NTS=-3" );
    }
    else
    {
        pwd_len = atoi( lpwd );
        txt.sprintf( "    Auth Len: %d", pwd_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    SQLRETURN ret = SQLConnect( in_handle, 
                                (SQLCHAR*)dsn, dsn_len,
                                (SQLCHAR*)usr, usr_len, 
                                (SQLCHAR*)pwd, pwd_len );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );
    odbctest -> out_win -> insertLineLimited( "" );
}

dConnect::dConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 100, 15, 150, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle -> setGeometry( 10, 15, 80, 20 );

    server = new QComboBox( this );
    server->setEditable( true );
    server -> setGeometry( 100, 50, 150, 20 );
    l_server = new QLabel( "Server:", this );
    l_server -> setGeometry( 10, 50, 90, 20 );
    server -> insertItem( 0, "<null ptr>" );
    server -> insertItem( 1, "<empty string>" );

    /*
     * find a env handle
     */

    SQLHANDLE henv = SQL_NULL_HANDLE;
    {
        QListIterator<Handle*> i( parent->listHandle );

        while ( i.hasNext() )
        {
            Handle *hand = i.next();
            if ( hand && hand->getType() == SQL_HANDLE_ENV )
            {
                henv = hand->getHandle();
            }
        }
    }

    if ( henv )
    {
        SQLRETURN ret;
        SQLCHAR dsn[ 128 ];
        int index = 2;

        ret = SQLDataSources( henv, 
                              SQL_FETCH_FIRST,
                              dsn,
                              sizeof( dsn ),
                              NULL,
                              NULL,
                              0,
                              NULL );

        while ( SQL_SUCCEEDED( ret ))
        {
            server -> insertItem( index ++, ( char * )dsn );
            ret = SQLDataSources( henv, 
                                  SQL_FETCH_NEXT,
                                  dsn,
                                  sizeof( dsn ),
                                  NULL,
                                  NULL,
                                  0,
                                  NULL );
        }
    }

    user = new QComboBox( this );
    user->setEditable( true );
    user -> setGeometry( 100, 80, 150, 20 );
    l_user = new QLabel( "User:", this );
    l_user -> setGeometry( 10, 80, 90, 20 );
    user -> insertItem( 0, "<null ptr>" );
    user -> insertItem( 1, "<empty string>" );

    auth = new QComboBox( this );
    auth->setEditable( true );
    auth -> setGeometry( 100, 110, 150, 20 );
    l_auth = new QLabel( "Authentication:", this );
    l_auth -> setGeometry( 10, 110, 90, 20 );
    auth -> insertItem( 0, "<null ptr>" );
    auth -> insertItem( 1, "<empty string>" );

    server_len = new QComboBox( this );
    server_len->setEditable( true );
    server_len -> setGeometry( 370, 50, 150, 20 );
    l_server_len = new QLabel( "String Length:", this );
    l_server_len -> setGeometry( 280, 50, 90, 20 );
    server_len -> insertItem( 0, "SQL_NTS=-3" );
    server_len -> insertItem( 1, "0" );

    user_len = new QComboBox( this );
    user_len->setEditable( true );
    user_len -> setGeometry( 370, 80, 150, 20 );
    l_user_len = new QLabel( "String Length:", this );
    l_user_len -> setGeometry( 280, 80, 90, 20 );
    user_len -> insertItem( 0, "SQL_NTS=-3" );
    user_len -> insertItem( 1, "0" );

    auth_len = new QComboBox( this );
    auth_len->setEditable( true );
    auth_len -> setGeometry( 370, 110, 150, 20 );
    l_auth_len = new QLabel( "String Length:", this );
    l_auth_len -> setGeometry( 280, 110, 90, 20 );
    auth_len -> insertItem( 0, "SQL_NTS=-3" );
    auth_len -> insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dConnect::~dConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete server;
    delete server_len;
    delete user;
    delete user_len;
    delete auth;
    delete auth_len;
    delete l_handle;
    delete l_server;
    delete l_server_len;
    delete l_user;
    delete l_user_len;
    delete l_auth;
    delete l_auth_len;
}

void dDisconnect::Ok()
{
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle;

    if ( hand )
        in_handle = hand -> getHandle();

    odbctest -> out_win -> insertLineLimited( "SQLDisconnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    SQLRETURN ret = SQLDisconnect( in_handle );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );
    odbctest -> out_win -> insertLineLimited( "" );
}

dDisconnect::dDisconnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 110,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 190,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 270,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 140, 50, 200, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Connection Handle:", this );
    l_handle -> setGeometry( 10, 50, 120, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dDisconnect::~dDisconnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handle;
}

void dFullConnect::set_dsn( const QString & s )
{
    dsn -> setText( s );
}

void dFullConnect::Ok()
{
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_ENV, handles );
    SQLINTEGER odbc_ver, odbc_cur;
    SQLHANDLE henv, hdbc, hstmt;    
    SQLRETURN ret;

    henv = SQL_NULL_HENV;

    /*
     * do we need to allocate a env handle ?
     */

    if ( !hand )
    {
        ret = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HENV, &henv );

        if ( !SQL_SUCCEEDED( ret ))
        {
            odbctest->out_win->insertLineLimited( "SQLAllocHandle( SQL_HANDLE_ENV ) failed" );
            return;
        }

        /*
         * set the odbc version
         */

        if ( ver_2 -> isChecked() )
            odbc_ver = SQL_OV_ODBC2;
        else if ( ver_3 -> isChecked() )
            odbc_ver = SQL_OV_ODBC3;
        else
            odbc_ver = SQL_OV_ODBC3;

        ret = SQLSetEnvAttr( henv, SQL_ATTR_ODBC_VERSION, ( SQLPOINTER ) odbc_ver, 0 );
        odbctest->dumpError( SQL_HANDLE_ENV, henv );

        if ( !SQL_SUCCEEDED( ret ))
        {
            odbctest->out_win->insertLineLimited( "SQLSetEnvAttr( SQL_ATTR_ODBC_VERSION ) failed" );
            return;
        }
    }
    else
    {
        henv = hand->getHandle();
    }

    /*
     * allocate a dbc handle
     */

    ret = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc );
    odbctest->dumpError( SQL_HANDLE_ENV, henv );

    if ( !SQL_SUCCEEDED( ret ))
    {
        odbctest->out_win->insertLineLimited( "SQLAllocHandle( SQL_HANDLE_DBC ) failed" );
        if ( !hand )
        {
            SQLFreeHandle( SQL_HANDLE_ENV, henv );
        }
        return;
    }

    /*
     * set the cursor lib setting
     */

    if ( cur_ifneeded -> isChecked() )
        odbc_cur = SQL_CUR_USE_IF_NEEDED;
    else if ( cur_use -> isChecked() )
        odbc_cur = SQL_CUR_USE_ODBC;
    else if ( cur_driver -> isChecked() )
        odbc_cur = SQL_CUR_USE_DRIVER;
    else
        odbc_cur = SQL_CUR_DEFAULT;

    ret = SQLSetConnectAttr( hdbc, SQL_ODBC_CURSORS, ( SQLPOINTER ) odbc_cur, 0 );
    odbctest->dumpError( SQL_HANDLE_DBC, hdbc );

    if ( !SQL_SUCCEEDED( ret ))
    {
        odbctest->out_win->insertLineLimited( "SQLSetConnectAttr( SQL_ODBC_CURSORS ) failed" );
        SQLFreeHandle( SQL_HANDLE_DBC, hdbc );
        if ( !hand )
        {
            SQLFreeHandle( SQL_HANDLE_ENV, henv );
        }
        return;
    }

    /*
     * connect
     */

    char cstr[ 1024 ], tmp[ 1024 ];

    QString qdsn = dsn -> text();
    QString quid = usr -> text();
    QString qpwd = pwd -> text();

    cstr[ 0 ] = '\0';

    if ( qdsn.isEmpty())
        strcpy( tmp, "DSN=" );
    else if ( qdsn.isNull())
        strcpy( tmp, "" );
    else
        sprintf( tmp, "DSN=%s", qdsn.toAscii().constData());

    strcpy( cstr, tmp );

    if ( quid.isEmpty())
        strcpy( tmp, "UID=" );
    else if ( quid.isNull())
        strcpy( tmp, "" );
    else
        sprintf( tmp, "UID=%s", quid.toAscii().constData());

    if ( strlen( tmp ) > 0 )
    {
        if ( strlen( cstr ) > 0 )
        {
            strcat( cstr, ";" );
            strcat( cstr, tmp );
        }
        else
        {
            strcpy( cstr, tmp );
        }
    }

    if ( qpwd.isEmpty())
        strcpy( tmp, "PWD=" );
    else if ( qpwd.isNull())
        strcpy( tmp, "" );
    else
        sprintf( tmp, "PWD=%s", qpwd.toAscii().constData());

    if ( strlen( tmp ) > 0 )
    {
        if ( strlen( cstr ) > 0 )
        {
            strcat( cstr, ";" );
            strcat( cstr, tmp );
        }
        else
        {
            strcpy( cstr, tmp );
        }
    }

    ret = SQLDriverConnect( hdbc, (void*)1, (SQLCHAR*)cstr, strlen( cstr ), NULL, 0, NULL, SQL_DRIVER_COMPLETE );

    odbctest->dumpError( SQL_HANDLE_DBC, hdbc );

    if ( !SQL_SUCCEEDED( ret ))
    {
        odbctest->out_win->insertLineLimited( "SQLConnect() failed" );
        SQLFreeHandle( SQL_HANDLE_DBC, hdbc );
        if ( !hand )
        {
            SQLFreeHandle( SQL_HANDLE_ENV, henv );
        }
        return;
    }

    /*
     * allocate a statement handle
     */

    ret = SQLAllocHandle( SQL_HANDLE_STMT, hdbc, &hstmt );
    odbctest->dumpError( SQL_HANDLE_DBC, hdbc );

    if ( !SQL_SUCCEEDED( ret ))
    {
        odbctest->out_win->insertLineLimited( "SQLAllocHandle( SQL_HANDLE_STMT ) failed" );
        SQLDisconnect( hdbc );
        SQLFreeHandle( SQL_HANDLE_DBC, hdbc );
        if ( !hand )
        {
            SQLFreeHandle( SQL_HANDLE_ENV, henv );
        }
        return;
    }

    /*
     * all done, record the handles
     */
    if ( !hand )
    {
        odbctest->listHandle.append( new Handle( SQL_HANDLE_ENV, henv ));
    }
    odbctest->listHandle.append( new Handle( SQL_HANDLE_DBC, hdbc ));
    odbctest->listHandle.append( new Handle( SQL_HANDLE_STMT, hstmt, odbctest->listHandle  ));

    odbctest->out_win->insertLineLimited( "Full Connect Succeeded\n" );
}

dFullConnect::dFullConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 110,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 190,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 270,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 140, 50, 200, 20 );

    Handle * hand = odbctest->fill_handle_list( SQL_HANDLE_ENV, handles );

    l_handle = new QLabel( "Envronment Handle:", this );
    l_handle -> setGeometry( 10, 50, 120, 20 );

    dsn = new QLineEdit( this );
    dsn -> setGeometry( 80, 85, 120, 20 );

    l_dsn = new QLabel( "DSN:", this );
    l_dsn -> setGeometry( 10, 85, 60, 20 );

    dsn_list = new QListWidget( this );
    dsn_list -> setGeometry( 80, 106, 120, 100 );

    /*
     * find a env handle, hand is set above
     */

    SQLHANDLE henv;
    SQLRETURN ret;
    SQLCHAR dsn_txt[ 128 ];

    /*
     * allocate a handle if required
     */

    if ( !hand )
    {
        ret = SQLAllocEnv( &henv );

        if ( !SQL_SUCCEEDED( ret ))
        {
            parent -> out_win -> insertLineLimited( "SQLAllocHandle fails allocating a environment handle" );
            return;
        }
    }
    else
    {
        henv = hand -> getHandle();
    }

    ret = SQLDataSources( henv, 
                          SQL_FETCH_FIRST,
                          dsn_txt,
                          sizeof( dsn_txt ),
                          NULL,
                          NULL,
                          0,
                          NULL );

    while ( SQL_SUCCEEDED( ret ))
    {
        dsn_list -> addItem( (char *)dsn_txt );
        ret = SQLDataSources( henv, 
                              SQL_FETCH_NEXT,
                              dsn_txt,
                              sizeof( dsn_txt ),
                              NULL,
                              NULL,
                              0,
                              NULL );
    }

    /*
     * remove the temp henv
     */

    if ( !hand )
    {
        SQLFreeEnv( henv );
    }

    usr = new QLineEdit( this );
    usr -> setGeometry( 80, 215, 120, 20 );
    usr -> setMaxLength( 32 );

    l_usr = new QLabel( "User:", this );
    l_usr -> setGeometry( 10, 215, 60, 20 );

    pwd = new QLineEdit( this );
    pwd -> setGeometry( 80, 245, 120, 20 );
    pwd -> setEchoMode( QLineEdit::Password );
    pwd -> setMaxLength( 32 );

    l_pwd = new QLabel( "Password:", this );
    l_pwd -> setGeometry( 10, 245, 60, 20 );

    version = new QGroupBox( "ODBC Version", this );
    version -> setGeometry( 220, 80, 120, 100 );

    ver_2 = new QRadioButton( "ODBC 2", version );
    ver_2 -> setGeometry( 10, 20, 100, 20 );

    ver_3 = new QRadioButton( "ODBC 3", version );
    ver_3 -> setGeometry( 10, 45, 100, 20 );

    ver_def = new QRadioButton( "Default", version );
    ver_def -> setGeometry( 10, 70, 100, 20 );
    ver_def -> setChecked( TRUE );

    cursor = new QGroupBox( "ODBC Cursors", this );
    cursor -> setGeometry( 220, 180, 120, 130 );

    cur_ifneeded = new QRadioButton( "Use If Needed", cursor );
    cur_ifneeded -> setGeometry( 10, 20, 100, 20 );

    cur_use = new QRadioButton( "Use ODBC", cursor );
    cur_use -> setGeometry( 10, 45, 100, 20 );

    cur_driver = new QRadioButton( "Use Driver", cursor );
    cur_driver -> setGeometry( 10, 70, 100, 20 );

    cur_default = new QRadioButton( "Default", cursor );
    cur_default -> setGeometry( 10, 95, 100, 20 );
    cur_default -> setChecked( TRUE );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( dsn_list, SIGNAL(selected(const QString &)), SLOT(set_dsn( const QString &)));
}

dFullConnect::~dFullConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handle;
    delete dsn;
    delete l_dsn;
    delete dsn_list;
    delete usr;
    delete l_usr;
    delete pwd;
    delete l_pwd;
    delete ver_2;
    delete ver_3;
    delete ver_def;
    delete version;
    delete cur_ifneeded;
    delete cur_use;
    delete cur_driver;
    delete cur_default;
    delete cursor;
}

void dGetInfo::target_clkd()
{
    if ( target_valid -> isChecked() )
        target_valid -> setText( "InfoValuePtr: SQL_NULL_POINTER" );
    else
        target_valid -> setText( "InfoValuePtr: VALID" );
}

void dGetInfo::strlen_clkd()
{
    if ( strlen_valid -> isChecked() )
        strlen_valid -> setText( "StrLenPtr: SQL_NULL_POINTER" );
    else
        strlen_valid -> setText( "StrLenPtr: VALID" );
}

void dGetInfo::Ok()
{
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    int index;
    SQLHANDLE in_handle;
    SQLINTEGER b_len, info_type;
    SQLSMALLINT strlen, *strlen_ptr;
    char *buf = NULL;

    if ( hand )
        in_handle = hand -> getHandle();

    odbctest -> out_win -> insertLineLimited( "SQLGetInfo():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );

    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HSTMT" );
    odbctest -> out_win -> insertLineLimited( txt );

    index = type -> currentIndex(); 

    info_type = info_options[ index ].attr;
    txt.sprintf( "    Info Type: %s=%d (%s)", info_options[ index ].text,
                 info_options[ index ].attr, info_options[ index ].version );
    odbctest -> out_win -> insertLineLimited( txt );

    b_len = buffer_len -> text().toInt();
    if ( b_len < 1 )
    {
        b_len = 0;
    }

    if ( target_valid -> isChecked())
    {
        buf = NULL;
    }
    else if ( b_len < 300 )
    {
        buf = new char[ 300 ];  
    }
    else
    {
        buf = new char[ b_len ];    
    }

    if ( buf )
    {
        txt.sprintf( "    Info Value Ptr: %p", buf );
        odbctest -> out_win -> insertLineLimited( txt );
    }
    else
    {
        txt.sprintf( "    Info Value Ptr: SQL_NULL_POINTER" );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    txt.sprintf( "    Buffer Length: %d", b_len );
    odbctest -> out_win -> insertLineLimited( txt );

    strlen = -9999;

    if ( strlen_valid -> isChecked())
    {
        strlen_ptr = NULL;
    }
    else
    {
        strlen_ptr = &strlen;
    }

    if ( strlen_ptr )
    {
        txt.sprintf( "    Strlen Ptr: %p", strlen_ptr );
        odbctest -> out_win -> insertLineLimited( txt );
    }
    else
    {
        txt.sprintf( "    Strlen Ptr: SQL_NULL_POINTER" );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    SQLRETURN ret = SQLGetInfo( in_handle, 
                                info_type, buf, b_len, strlen_ptr );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    odbctest -> out_win -> insertLineLimited( "  Out:" );
    if ( strlen_ptr )
    {
        if ( strlen == -9999 )
        {
            txt.sprintf( "    *Strlen Ptr: <unchanged>" );
        }
        else
        {
            txt.sprintf( "    *Strlen Ptr: %d", strlen );
        }
        odbctest -> out_win -> insertLineLimited( txt );
    }
    if ( SQL_SUCCEEDED( ret ))
    {
        switch ( info_options[ index ].data_type )
        {
            case SQL_CHAR:
                txt.sprintf( "    *InfoValuePtr = \"%s\"", buf );
                odbctest -> out_win -> insertLineLimited( txt );
                break;

            case SQL_INTEGER:
                SQLUINTEGER ival;
                memcpy( &ival, buf, sizeof( ival ));
                txt.sprintf( "    *InfoValuePtr = %d (0x%08X)", ival, ival );
                odbctest -> out_win -> insertLineLimited( txt );

                if ( info_options[ index ].values[ 0 ].text )
                {
                    if ( info_options[ index ].is_bitmap )
                    {
                        int i;

                        for ( i = 0; info_options[ index ].values[ i ].text; i ++ )
                        {
                            if ( info_options[ index ].values[ i ].value & ival )
                            {
                                txt.sprintf( "        %s", 
                                             info_options[ index ].values[ i ].text );
                                odbctest -> out_win -> insertLineLimited( txt );
                            }
                        }
                    }
                    else
                    {
                        int i;

                        for ( i = 0; info_options[ index ].values[ i ].text; i ++ )
                        {
                            if ( (SQLUINTEGER)(info_options[ index ].values[ i ].value) == ival )
                            {
                                txt.sprintf( "        %s", 
                                             info_options[ index ].values[ i ].text );
                                odbctest -> out_win -> insertLineLimited( txt );
                            }
                        }
                    }
                }
                break;

            case SQL_SMALLINT:
                SQLSMALLINT sval;
                memcpy( &sval, buf, sizeof( sval ));
                txt.sprintf( "    *InfoValuePtr = %d (0x%04X)", sval, sval );
                odbctest -> out_win -> insertLineLimited( txt );

                if ( info_options[ index ].values[ 0 ].text )
                {
                    if ( info_options[ index ].is_bitmap )
                    {
                        int i;

                        for ( i = 0; info_options[ index ].values[ i ].text; i ++ )
                        {
                            if ( info_options[ index ].values[ i ].value & sval )
                            {
                                txt.sprintf( "        %s", 
                                             info_options[ index ].values[ i ].text );
                                odbctest -> out_win -> insertLineLimited( txt );
                            }
                        }
                    }
                    else
                    {
                        int i;

                        for ( i = 0; info_options[ index ].values[ i ].text; i ++ )
                        {
                            if ( info_options[ index ].values[ i ].value == sval )
                            {
                                txt.sprintf( "        %s", 
                                             info_options[ index ].values[ i ].text );
                                odbctest -> out_win -> insertLineLimited( txt );
                            }
                        }
                    }
                }
                break;
        }       
    }

    if ( buf )
        delete buf;

    odbctest -> out_win -> insertLineLimited( "" );
}

dGetInfo::dGetInfo( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 240,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 320,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 400,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 130, 50, 200, 20 );
    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Connection Handle:", this );
    l_handle -> setGeometry( 10, 50, 120, 20 );

    type = new QComboBox( this );
    type -> setGeometry( 130, 80, 340, 20 );

    parent->fill_list_box( info_options, type );

    l_type = new QLabel( "Info Type:", this );
    l_type -> setGeometry( 10, 80, 120, 20 );

    target_valid = new QCheckBox( "InfoValuePtr: VALID", this );
    target_valid -> setGeometry( 10, 110, 300, 15 );

    strlen_valid = new QCheckBox( "StrLenPtr: VALID", this );
    strlen_valid -> setGeometry( 10, 140, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len -> setGeometry( 400, 110, 70, 20 );
    buffer_len -> setMaxLength( 6 );
    buffer_len -> setText( "300" );

    l_buffer_len = new QLabel( "Buffer Len:", this );
    l_buffer_len -> setGeometry( 320, 110, 60, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( target_valid, SIGNAL( clicked()), this, SLOT( target_clkd()));
    connect( strlen_valid, SIGNAL( clicked()), this, SLOT( strlen_clkd()));
}

dGetInfo::~dGetInfo()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handle;
    delete type;
    delete l_type;
    delete target_valid;
    delete strlen_valid;
    delete buffer_len;
    delete l_buffer_len;
}

void dGetFunctions::target_clkd()
{
    if ( target_valid -> isChecked() )
        target_valid -> setText( "SupportedPtr: SQL_NULL_POINTER" );
    else
        target_valid -> setText( "SupportedPtr: VALID" );
}

void dGetFunctions::Ok()
{
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    int index;
    SQLHANDLE in_handle = NULL;
    SQLINTEGER func_type;
    SQLUSMALLINT single_value, odbc_3_all[ SQL_API_ODBC3_ALL_FUNCTIONS ], odbc_2_all[ 100 ];
    SQLUSMALLINT *supported_ptr;

    if ( hand )
        in_handle = hand -> getHandle();

    odbctest -> out_win -> insertLineLimited( "SQLGetFunctions():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );

    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HSTMT" );
    odbctest -> out_win -> insertLineLimited( txt );

    index = type -> currentIndex(); 

    func_type = gf_options[ index ].attr;
    txt.sprintf( "    FunctionId: %s=%d (%s)", gf_options[ index ].text,
                 gf_options[ index ].attr, gf_options[ index ].version );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( target_valid -> isChecked())
    {
        supported_ptr = NULL;
    }
    else
    {
        if ( func_type == SQL_API_ODBC3_ALL_FUNCTIONS )
        {
            supported_ptr = odbc_3_all;
        }
        else if ( func_type == SQL_API_ALL_FUNCTIONS )
        {
            supported_ptr = odbc_2_all;
        }
        else
        {
            supported_ptr = &single_value;
        }
    }

    if ( supported_ptr )
    {
        txt.sprintf( "    Supported Ptr: %p", supported_ptr );
        odbctest -> out_win -> insertLineLimited( txt );
    }
    else
    {
        txt.sprintf( "    Supported Ptr: SQL_NULL_POINTER" );
        odbctest -> out_win -> insertLineLimited( txt );
    }

    SQLRETURN ret = SQLGetFunctions( in_handle, 
                                     func_type, supported_ptr );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        if ( func_type == SQL_API_ODBC3_ALL_FUNCTIONS )
        {
            odbctest -> out_win -> insertLineLimited( "  Out:" );
            for ( int i = 0; gf_options[ i ].text; i ++ )
            {
                if ( gf_options[ i ].attr == SQL_API_ODBC3_ALL_FUNCTIONS ||
                     gf_options[ i ].attr == SQL_API_ALL_FUNCTIONS )
                {
                    continue;
                }

                if ( SQL_FUNC_EXISTS( odbc_3_all, gf_options[ i ].attr ))
                {
                    txt.sprintf( "    %s=%d            SQL_TRUE", gf_options[ i ].text,
                                 gf_options[ i ].attr );
                }
                else
                {
                    txt.sprintf( "    %s=%d            SQL_FALSE", gf_options[ i ].text,
                                 gf_options[ i ].attr );
                }
                odbctest -> out_win -> insertLineLimited( txt );
            }
        }
        else if ( func_type == SQL_API_ALL_FUNCTIONS )
        {
            odbctest -> out_win -> insertLineLimited( "  Out:" );
            for ( int i = 0; gf_options[ i ].text; i ++ )
            {
                if ( gf_options[ i ].attr > 99 || 
                     gf_options[ i ].attr == SQL_API_ALL_FUNCTIONS )
                {
                    continue;
                }

                if ( odbc_2_all[ gf_options[ i ].attr ] )
                {
                    txt.sprintf( "    %s=%d            SQL_TRUE", gf_options[ i ].text,
                                 gf_options[ i ].attr );
                }
                else
                {
                    txt.sprintf( "    %s=%d            SQL_FALSE", gf_options[ index ].text,
                                 gf_options[ index ].attr );
                }
                odbctest -> out_win -> insertLineLimited( txt );
            }
        }
        else
        {
            odbctest -> out_win -> insertLineLimited( "  Out:" );
            if ( single_value )
            {
                txt.sprintf( "    *SupportedPtr: = SQL_TRUE" );
            }
            else
            {
                txt.sprintf( "    *SupportedPtr: = SQL_FALSE" );
            }
            odbctest -> out_win -> insertLineLimited( txt );
        }
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dGetFunctions::dGetFunctions( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 240,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 320,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 400,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 130, 50, 200, 20 );
    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Connection Handle:", this );
    l_handle -> setGeometry( 10, 50, 120, 20 );

    type = new QComboBox( this );
    type -> setGeometry( 130, 80, 340, 20 );

    parent->fill_list_box( gf_options, type );

    l_type = new QLabel( "FunctionId:", this );
    l_type -> setGeometry( 10, 80, 120, 20 );

    target_valid = new QCheckBox( "SupportedPtr: VALID", this );
    target_valid -> setGeometry( 10, 110, 300, 15 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( target_valid, SIGNAL( clicked()), this, SLOT( target_clkd()));
}

dGetFunctions::~dGetFunctions()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handle;
    delete type;
    delete l_type;
    delete target_valid;
}

void dNativeSQL::out_str_clkd()
{
    if ( out_str_valid -> isChecked() )
        out_str_valid -> setText( "OutStatementText: SQL_NULL_POINTER" );
    else
        out_str_valid -> setText( "OutStatementText: VALID" );
}

void dNativeSQL::strlen_clkd()
{
    if ( strlen_valid -> isChecked() )
        strlen_valid -> setText( "TextLength2Ptr: SQL_NULL_POINTER" );
    else
        strlen_valid -> setText( "TextLength2Ptr2: VALID" );
}

void dNativeSQL::Ok()
{
    const char *in_string, *string_len;
    SQLCHAR *conn_str_in;
    SQLCHAR *out_string;
    SQLINTEGER in_string_len, con_str_out_max;
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle;
    SQLINTEGER con_str_out, *ptr_con_str_out;
    QString qstring_len, qin_string;

    if ( hand )
        in_handle = hand -> getHandle();

    qstring_len = str_len -> currentText();
    string_len = qstring_len.toAscii().constData();

    odbctest -> out_win -> insertLineLimited( "SQLNativeSql():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Connection Handle: %p", in_handle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    qin_string = in_str -> currentText();
    in_string = qin_string.toAscii().constData();

    if ( strcmp( in_string, "<null ptr>" ) == 0 )
    {
        conn_str_in = NULL;
        odbctest -> out_win -> insertLineLimited( "    InStatementTxt: <null ptr>" );
    }
    else if ( strcmp( in_string, "<empty string>" ) == 0 )
    {
        conn_str_in = ( SQLCHAR * ) "";
        odbctest -> out_win -> insertLineLimited( "    InStatementTxt: <empty string>" );
    }
    else if ( strcmp( in_string, "<input window>" ) == 0 )
    {
        QString *s = new QString( odbctest->in_win->toPlainText() );
        if ( s -> isEmpty())
            in_string = "";
        else if ( s -> isNull())
            in_string = NULL;
        else
            in_string = s->toLatin1();
        txt.sprintf( "    InStatementTxt: %s", in_string );
        odbctest -> out_win -> insertLineLimited( txt );
        conn_str_in = ( SQLCHAR * ) in_string;
    }
    else
    {
        txt.sprintf( "    InStatementTxt: %s", in_string );
        conn_str_in = ( SQLCHAR * ) in_string;
        odbctest -> out_win -> insertLineLimited( txt );
    }

    if ( strncmp( string_len, "SQL_NTS", 7 ) == 0 )
    {
        in_string_len = SQL_NTS;
        txt.sprintf( "    TextLength1: SQL_NTS=-3" );
    }
    else
    {
        in_string_len = atoi( string_len );
        txt.sprintf( "    TextLength1: %d", in_string_len );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out_max = buffer_len ->text().toInt();

    if ( out_str_valid -> isChecked())
    {
        out_string = ( SQLCHAR * ) NULL;
    }
    else if ( con_str_out_max < 300 )
    {
        out_string = new SQLCHAR[ 300 ];    
    }
    else
    {
        out_string = new SQLCHAR[ con_str_out_max ];    
    }

    if ( out_string )
    {
        txt.sprintf( "    OutStatementText: %p", out_string );
    }
    else
    {
        txt.sprintf( "    OutStatementText: NULL_POINTER" );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    txt.sprintf( "    Buffer Length %d", con_str_out_max );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( strlen_valid -> isChecked())
    {
        ptr_con_str_out = NULL;
        txt.sprintf( "    TextLength2Ptr: NULL_POINTER" );
    }
    else
    {
        ptr_con_str_out = &con_str_out;
        txt.sprintf( "    TextLength2Ptr: %p", ptr_con_str_out );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    con_str_out = -9999;

    SQLRETURN ret = SQLNativeSql( in_handle, 
                                  conn_str_in,
                                  in_string_len,
                                  out_string,
                                  con_str_out_max,
                                  ptr_con_str_out );


    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        if ( out_string )
        {
            txt.sprintf( "    OutStatementText: %s", out_string );
            odbctest -> out_win -> insertLineLimited( txt );
        }

        if ( ptr_con_str_out )
        {
            if ( con_str_out == -9999 )
            {
                txt.sprintf( "    *TextLength2Ptr: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *TextLength2Ptr: %d", con_str_out );
            }
            odbctest -> out_win -> insertLineLimited( txt );
        }
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dNativeSQL::dNativeSQL( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 100, 15, 150, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle -> setGeometry( 10, 15, 80, 20 );

    in_str = new QComboBox( this );
    in_str->setEditable( true );
    in_str -> setGeometry( 130, 50, 300, 20 );
    l_in_str = new QLabel( "InStatementText:", this );
    l_in_str -> setGeometry( 10, 50, 90, 20 );
    in_str -> insertItem( 0, "<input window>" );
    in_str -> insertItem( 1, "<null ptr>" );
    in_str -> insertItem( 2, "<empty string>" );

    str_len = new QComboBox( this );
    str_len->setEditable( true );
    str_len -> setGeometry( 130, 80, 150, 20 );
    l_str_len = new QLabel( "TextLength1:", this );
    l_str_len -> setGeometry( 10, 80, 90, 20 );
    str_len -> insertItem( 0, "SQL_NTS=-3" );
    str_len -> insertItem( 1, "0" );

    out_str_valid = new QCheckBox( "OutStatementText: VALID", this );
    out_str_valid -> setGeometry( 10, 110, 300, 15 );

    strlen_valid = new QCheckBox( "TextLength2Ptr: VALID", this );
    strlen_valid -> setGeometry( 10, 140, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len -> setGeometry( 400, 80, 70, 20 );
    buffer_len -> setMaxLength( 6 );
    buffer_len -> setText( "300" );

    l_buffer_len = new QLabel( "Buffer Len:", this );
    l_buffer_len -> setGeometry( 320, 80, 60, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( out_str_valid, SIGNAL( clicked()), this, SLOT( out_str_clkd()));
    connect( strlen_valid, SIGNAL( clicked()), this, SLOT( strlen_clkd()));
}

dNativeSQL::~dNativeSQL()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete in_str;
    delete str_len;
    delete l_handle;
    delete l_in_str;
    delete l_str_len;
    delete out_str_valid;
    delete strlen_valid;
    delete buffer_len;
    delete l_buffer_len;
}

void dAllocConnect::handle_clkd()
{
    if ( handle_valid -> isChecked() )
        handle_valid -> setText( "phdbc: SQL_NULL_POINTER" );
    else
        handle_valid -> setText( "phdbc: VALID" );
}

void dAllocConnect::Ok()
{
    SQLHDBC hdbc, *hdbc_ptr;
    Handle *hand = odbctest->extract_handle_list( SQL_HANDLE_ENV, handles );
    SQLHANDLE in_handle;

    if ( hand )
        in_handle = hand -> getHandle();

    odbctest -> out_win -> insertLineLimited( "SQLAllocConnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );

    if ( in_handle )
        txt.sprintf( "    Environment Handle: %p", in_handle );
    else
        txt.sprintf( "    Environment Handle: SQL_NULL_HENV" );

    odbctest -> out_win -> insertLineLimited( txt );

    if ( handle_valid -> isChecked())
    {
        hdbc_ptr = NULL;
        txt.sprintf( "    phdbc: SQL_NULL_HANDLE" );
    }
    else
    {
        hdbc_ptr = &hdbc;
        txt.sprintf( "    phdbc: %p", hdbc_ptr );
    }
    odbctest -> out_win -> insertLineLimited( txt );

    SQLRETURN ret = SQLAllocConnect( in_handle, hdbc_ptr );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ) && hdbc_ptr )
    {
        txt.sprintf( "    *phdbc: %p", hdbc );
        odbctest -> out_win -> insertLineLimited( txt );

        odbctest->listHandle.append( new Handle( SQL_HANDLE_DBC, hdbc ) );
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dAllocConnect::dAllocConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 90,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 170,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 250,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 100, 50, 200, 20 );

    odbctest->fill_handle_list( SQL_HANDLE_ENV, handles );

    l_handles = new QLabel( "Handle:", this );
    l_handles -> setGeometry( 10, 50, 80, 20 );

    handle_valid = new QCheckBox( "phdbc: VALID", this );
    handle_valid -> setGeometry( 10, 80, 300, 15 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
    connect( handle_valid, SIGNAL( clicked()), this, SLOT( handle_clkd()));
}

dAllocConnect::~dAllocConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handle_valid;
    delete handles;
    delete l_handles;
}

void dFreeConnect::Ok()
{
    Handle *dbc = odbctest->extract_handle_list( SQL_HANDLE_DBC, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( dbc )
        in_handle = dbc -> getHandle();

    odbctest -> out_win -> insertLineLimited( "SQLFreeConnect():" );
    odbctest -> out_win -> insertLineLimited( "  In:" );

    if ( in_handle )
        txt.sprintf( "    hdbc: %p", in_handle );
    else
        txt.sprintf( "    hdbc: SQL_NULL_HDBC" );
    odbctest -> out_win -> insertLineLimited( txt );

    SQLRETURN ret = SQLFreeConnect( in_handle );

    odbctest -> out_win -> insertLineLimited( "  Return:" );
    txt.sprintf( "    %s=%d", odbctest->return_as_text( ret ), ret );
    odbctest -> out_win -> insertLineLimited( txt );

    if ( SQL_SUCCEEDED( ret ) && in_handle )
    {
        odbctest->listHandle.removeOne( dbc );
        delete dbc;
    }

    odbctest -> out_win -> insertLineLimited( "" );
}

dFreeConnect::dFreeConnect( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );
    setModal( true );

    odbctest = parent;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 90,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 170,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 250,10, 70,25 );

    handles = new QComboBox( this );
    handles -> setGeometry( 120, 50, 200, 20 );
    odbctest->fill_handle_list( SQL_HANDLE_DBC, handles );

    l_handles = new QLabel( "hdbc:", this );
    l_handles -> setGeometry( 10, 50, 100, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dFreeConnect::~dFreeConnect()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handles;
}

void OdbcTest::sqlbrowseconnect()
{
    dBrowseConnect *dlg = new dBrowseConnect( this, "SQLBrowseConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqlconnect()
{
    dConnect *dlg = new dConnect( this, "SQLConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqldriverconnect()
{
    dDriverConnect *dlg = new dDriverConnect( this, "SQLDriverConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqldisconnect()
{
    dDisconnect *dlg = new dDisconnect( this, "SQLDisconnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqlgetinfo()
{
    dGetInfo *dlg = new dGetInfo( this, "GetInfo" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqlgetfunctions()
{
    dGetFunctions *dlg = new dGetFunctions( this, "GetFunctions" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqlnativesql()
{
    dNativeSQL *dlg = new dNativeSQL( this, "NativeSql" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::fullconnect()
{
    dFullConnect *dlg = new dFullConnect( this, "FullConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::fulldisconnect()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

void OdbcTest::sqlallocconnect()
{
    dAllocConnect *dlg = new dAllocConnect( this, "AllocConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::sqlfreeconnect()
{
    dFreeConnect *dlg = new dFreeConnect( this, "FreeConnect" );

    dlg -> exec();

    delete dlg;
}

void OdbcTest::getinfodbc( SQLHANDLE hdbc )
{
    attr_options *opt = info_options;

    if ( !hdbc )
    {
        return;
    }

    /* 
     * go through each option, and report
     */

    out_win -> insertLineLimited( "SQLGetInfo All" );

    while ( opt -> text )
    {
        char buf[ 300 ];
        SQLSMALLINT str_len;
        SQLINTEGER info_type;
        QString txt;

        info_type = opt -> attr;

        SQLRETURN ret = SQLGetInfo( hdbc, 
                                    info_type, buf, sizeof( buf ), &str_len );

        if ( SQL_SUCCEEDED( ret ))
        {
            switch ( opt -> data_type )
            {
                case SQL_CHAR:
                    txt.sprintf( "    %s=%d (%s) = \"%s\"", 
                                 opt -> text, opt -> attr, opt -> version, buf );
                    out_win -> insertLineLimited( txt );
                    break;

                case SQL_INTEGER:
                    SQLUINTEGER ival;
                    memcpy( &ival, buf, sizeof( ival ));

                    if ( opt -> values[ 0 ].text )
                    {
                        if ( opt -> is_bitmap )
                        {
                            int i;

                            txt.sprintf( "    %s=%d (%s) = 0x%08x", 
                                         opt -> text, opt -> attr, opt -> version, ival );
                            out_win -> insertLineLimited( txt );

                            for ( i = 0; opt -> values[ i ].text; i ++ )
                            {
                                if ( opt -> values[ i ].value & ival )
                                {
                                    txt.sprintf( "            %s", 
                                                 opt -> values[ i ].text );
                                    out_win -> insertLineLimited( txt );
                                }
                            }
                        }
                        else
                        {
                            int i;

                            txt.sprintf( "    %s=%d (%s) = 0x%08x", 
                                         opt -> text, opt -> attr, opt -> version, ival );
                            out_win -> insertLineLimited( txt );

                            for ( i = 0; opt -> values[ i ].text; i ++ )
                            {
                                if ( (SQLUINTEGER)(opt -> values[ i ].value) == ival )
                                {
                                    txt.sprintf( "            %s", 
                                                 opt -> values[ i ].text );
                                    out_win -> insertLineLimited( txt );
                                }
                            }
                        }
                    }
                    break;

                case SQL_SMALLINT:
                    SQLSMALLINT sval;
                    memcpy( &sval, buf, sizeof( sval ));

                    if ( opt -> values[ 0 ].text )
                    {
                        if ( opt -> is_bitmap )
                        {
                            int i;

                            txt.sprintf( "    %s=%d (%s) = 0x%04x", 
                                         opt -> text, opt -> attr, opt -> version, sval );
                            out_win -> insertLineLimited( txt );

                            for ( i = 0; opt -> values[ i ].text; i ++ )
                            {
                                if ( opt -> values[ i ].value & sval )
                                {
                                    txt.sprintf( "        %s", 
                                                 opt -> values[ i ].text );
                                    out_win -> insertLineLimited( txt );
                                }
                            }
                        }
                        else
                        {
                            int i;

                            txt.sprintf( "    %s=%d (%s) = 0x%04x", 
                                         opt -> text, opt -> attr, opt -> version, sval );
                            out_win -> insertLineLimited( txt );

                            for ( i = 0; opt -> values[ i ].text; i ++ )
                            {
                                if ( opt -> values[ i ].value == sval )
                                {
                                    txt.sprintf( "        %s", 
                                                 opt -> values[ i ].text );
                                    out_win -> insertLineLimited( txt );
                                }
                            }
                        }
                    }
                    break;
            }       
        }
        else
        {
            txt.sprintf( "    %s=%d (%s) Not Supported", 
                         opt -> text, opt -> attr, opt -> version );
            out_win -> insertLineLimited( txt );
        }

        opt ++;
    }
}

void OdbcTest::getinfoall()
{
    /*
     * look for a connection handle
     */

    SQLHANDLE hdbc;
    int handle_count = 0;

    {
        QListIterator<Handle*> i( listHandle );
        char txt[ 128 ];

        while ( i.hasNext() )
        {
            Handle *hand = i.next();
            if ( hand ) hand->toStr( txt );
            if ( hand && hand->getType() == SQL_HANDLE_DBC )
            {
                    handle_count ++;
                    hdbc = hand->getHandle();
            }
        }
    }

    if ( handle_count == 0 )
    {
        QMessageBox::about( this, "Get Info All",
                            "No connection handles avalable" );
    }
    else if ( handle_count == 1 )
    {
        getinfodbc( hdbc );
    }
    else
    {
        getinfodbc();
    }
}

void OdbcTest::getfunctionsall()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

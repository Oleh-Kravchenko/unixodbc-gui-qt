/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 **********************************************************************
 *
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "OdbcHandle.h"

attr_value pEnvHandleTypes[] = 
{
	{ "SQL_HANDLE_ENV",     SQL_HANDLE_ENV,     NULL,   0 },
	{ "SQL_HANDLE_DBC",     SQL_HANDLE_DBC,     NULL,   0 },
    { NULL,                 0,                  NULL,   0 }
};

attr_value pEnvCompletionTypes[] = 
{
	{ "SQL_COMMIT",         SQL_COMMIT,         NULL,   0 },
	{ "SQL_ROLLBACK",       SQL_ROLLBACK,       NULL,   0 },
    { NULL,                 0,                  NULL,   0 }
};

attr_value pEnvDataSourcesDirections[] = 
{
	{ "SQL_FETCH_NEXT",         SQL_FETCH_NEXT,         NULL,   0 },
	{ "SQL_FETCH_FIRST",        SQL_FETCH_FIRST,        NULL,   0 },
	{ "SQL_FETCH_FIRST_USER",   SQL_FETCH_FIRST_USER,   NULL,   0 },
	{ "SQL_FETCH_FIRST_SYSTEM", SQL_FETCH_FIRST_SYSTEM, NULL,   0 },
    { NULL,                     0,                      NULL,   0 }
};

attr_value pEnvDriversDirections[] = 
{
	{ "SQL_FETCH_NEXT",     SQL_FETCH_NEXT,     NULL,   0 },
	{ "SQL_FETCH_FIRST",    SQL_FETCH_FIRST,    NULL,   0 },
    { NULL,                 0,                  NULL,   0 }
};

OdbcHandle::OdbcHandle( int t, SQLHANDLE h, QString desc, SQLHANDLE stmt ) 
{ 
	type = t; 
	handle = h; 

    description = desc;
    stmt_handle = stmt;

    if ( stmt )
    {
        implicit = 1;
    }
    else
    {
        implicit = 0;
    }

    handle_list = NULL;

	bookmark_ptr = new char[ 256 ];
	param_bind_offset_ptr = &param_bind_offset;
	param_opt_ptr = &param_opt;
	param_status_ptr = &param_status;
	params_processed_ptr = &params_processed;
	row_bind_offset_ptr = &row_bind_offset;
	row_operation_ptr = &row_operation;
	row_status_ptr = &row_status;
	rows_fetched_ptr = &rows_fetched;

    row_array_size = 0;
    param_array_size = 0;
}

OdbcHandle::OdbcHandle( int t, SQLHANDLE h, QList<OdbcHandle*> &list ) 
{ 
	type = t; 
	handle = h; 

    implicit = 0;
    description = "";
    stmt_handle = SQL_NULL_HANDLE;
    handle_list = &list;

	bookmark_ptr = new char[ 256 ];
	param_bind_offset_ptr = &param_bind_offset;
	param_opt_ptr = &param_opt;
	param_status_ptr = &param_status;
	params_processed_ptr = &params_processed;
	row_bind_offset_ptr = &row_bind_offset;
	row_operation_ptr = &row_operation;
	row_status_ptr = &row_status;
	rows_fetched_ptr = &rows_fetched;

    row_array_size = 0;
    param_array_size = 0;

    /*
     * extract any desc handles associated with a statement handle 
     */

    if ( type == SQL_HANDLE_STMT )
    {
        SQLRETURN ret;
        SQLHANDLE desc;

        ret = SQLGetStmtAttr( h, SQL_ATTR_APP_PARAM_DESC, &desc, 0, NULL );
        if ( SQL_SUCCEEDED( ret ))
		    list.append( new OdbcHandle( SQL_HANDLE_DESC, desc, "Implicit APD", h ));

        ret = SQLGetStmtAttr( h, SQL_ATTR_APP_ROW_DESC, &desc, 0, NULL );
        if ( SQL_SUCCEEDED( ret ))
		    list.append( new OdbcHandle( SQL_HANDLE_DESC, desc, "Implicit ARD", h ));

        ret = SQLGetStmtAttr( h, SQL_ATTR_IMP_PARAM_DESC, &desc, 0, NULL );
        if ( SQL_SUCCEEDED( ret ))
		    list.append( new OdbcHandle( SQL_HANDLE_DESC, desc, "Implicit IPD", h ));

        ret = SQLGetStmtAttr( h, SQL_ATTR_IMP_ROW_DESC, &desc, 0, NULL );
        if ( SQL_SUCCEEDED( ret ))
		    list.append( new OdbcHandle( SQL_HANDLE_DESC, desc, "Implicit IRD", h ));
    }
}

OdbcHandle::OdbcHandle( OdbcHandle &e ) 
{ 
	type = e.type; 
	handle = e.handle; 

    implicit = 0;
    description = "";
    stmt_handle = SQL_NULL_HANDLE;

	bookmark_ptr = new char[ 256 ];
	param_bind_offset_ptr = &param_bind_offset;
	param_opt_ptr = &param_opt;
	param_status_ptr = &param_status;
	params_processed_ptr = &params_processed;
	row_bind_offset_ptr = &row_bind_offset;
	row_operation_ptr = &row_operation;
	row_status_ptr = &row_status;
	rows_fetched_ptr = &rows_fetched;

    row_array_size = 0;
    param_array_size = 0;
};

OdbcHandle::~OdbcHandle()
{
    /*
     * remove the implicit descriptors if a stmt is removed
     */

    if ( type == SQL_HANDLE_STMT )
    {
        int changed = 0;

        do
        {
            changed = 0;
            
			{
				for ( int i = 0; i < handle_list->size(); ++i ) 
				{
					OdbcHandle *hand = handle_list->at( i );

					if ( hand && hand->getType() == SQL_HANDLE_DESC && hand->getStmtHandle() == handle )
					{
						handle_list->removeAll( hand );
						delete hand;
						changed = 1;
						break;
					}
				}
			}
        }
        while( changed );
	}
}

char * OdbcHandle::toStr( char * str )
{
	switch( type )
	{
		case SQL_HANDLE_ENV:
			sprintf( str, "henv: %p", handle );
			break;

		case SQL_HANDLE_DBC:
			sprintf( str, "hdbc: %p", handle );
			break;

		case SQL_HANDLE_STMT:
			sprintf( str, "hstmt: %p", handle );
			break;

		case SQL_HANDLE_DESC:
			sprintf( str, "hdesc: %p \"%s\"", handle, description.toAscii().constData() );
			break;
	}

	return str;
};



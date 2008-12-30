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

#pragma once

/*
 * This is the first include file ODBCTestQ4 code needs to get in -
 * directly or indirectly. This brings in the; standard C, ODBC, and Qt 
 * includes.
 */

/* bring in standard C stuff */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

/* this will bring in the ODBC 'test' stuff we need (and then some) */
#include <autotest.h>

typedef BOOL (*AUTOTESTNAME)(LPSTR,UINT*);
typedef BOOL (*AUTOTESTDESC)(UWORD,LPSTR,LPSTR);
typedef void (*AUTOTESTFUNC)(SERVERINFO*);

/* bring in more ODBC stuff */
#include <sqlucode.h>
#include <odbcinst.h>

/* this brings in all of the Qt stuff we need */
#include <QtGui>

/*
 * structure that defines the options and values
 */

typedef struct attr_value
{
	const char *    text;
	int 	        value;
	const char *    version;
	int		        data_type;
} attr_value;

typedef struct attr_options
{
	const char *    text;
	int		        attr;
	attr_value      values[ 25 ];
	const char *    version;
	int		        data_type;
	int		        is_bitmap;
	int		        is_pointer;
} attr_options;


/*!
 * \brief   ODBC handle. 
 *  
 *          Our, not so, general purpose handle. This is a general purpose handle in that
 *          it supports all of the ODBC handle types. Its no so general purpose in the
 *          fact that we toss in some other stuff simply for convenience.
 * 
 */
class OdbcHandle
{
public:
	OdbcHandle( int t, SQLHANDLE h, QList<OdbcHandle*> &list );
	OdbcHandle( int t, SQLHANDLE h, QString desc = NULL, SQLHANDLE stmt = SQL_NULL_HANDLE );
	OdbcHandle( OdbcHandle &e );
	~OdbcHandle();
	char * toStr( char * str );
	SQLHANDLE getHandle( void ) { return handle; };
	SQLHANDLE getStmtHandle( void ) { return stmt_handle; };
	int getType( void ) { return type; };
	char *bookmark_ptr;

    SQLUINTEGER row_array_size;
    SQLUINTEGER param_array_size;

	SQLUINTEGER *param_bind_offset_ptr, param_bind_offset;
	SQLUSMALLINT *param_opt_ptr, param_opt;
	SQLUSMALLINT *param_status_ptr, param_status;
	SQLUINTEGER *params_processed_ptr, params_processed;
	SQLUINTEGER *row_bind_offset_ptr, row_bind_offset;
	SQLUSMALLINT *row_operation_ptr, row_operation;
	SQLUSMALLINT *row_status_ptr, row_status;
	SQLUINTEGER *rows_fetched_ptr, rows_fetched;

private:
	int                 type;           // handle type
	SQLHANDLE           handle;         // the underlying ODBC handle
    QString             description;    //
    int                 implicit;       // for when we are a descriptor handle
	SQLHANDLE           stmt_handle;    // for when we are a descriptor handle?
    QList<OdbcHandle*> *handle_list;    // subordinate/child handles
};



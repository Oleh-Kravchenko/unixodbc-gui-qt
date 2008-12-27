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
 **********************************************************************/
/*
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 */

#pragma once

#include "odbctest.h"

/*!
 * \brief   Supports ODBCTestQ4. 
 *  
 *          This class serves as a namespace and as a global. The idea is we
 *          create just 1 instance of this, make it global, and use it through-out
 *          the ODBCTestQ4 code. The principle features can be grouped as follows;
 *  
 *          - global settings handle
 *          - methods to produce output on behalf of test plugin (via callback_function)
 *          - convenience methods (loading list boxs etc)
 *  
 *          This global is instantiated in the OdbcTest constructor.
 *  
 * \author  pharvey (12/27/2008)
 */
class OdbcTools
{
public:
    OdbcTools( OdbcTest *pOdbcTest );
    ~OdbcTools();

    OdbcTest *  pOdbcTest;
    QSettings * pSettings;

    void post_to_odbctest( lpSERVERINFO lps );
    void print_to_odbctest( lpSERVERINFO lps, char *str, int log );
    int  show_message_box( int style, const char *title, const char *msg );
    void fill_dsn_list( QComboBox *box );
    void set_dsn_list( QComboBox *box, const QString &str );
};

// our global...
extern OdbcTools *gOdbcTools;



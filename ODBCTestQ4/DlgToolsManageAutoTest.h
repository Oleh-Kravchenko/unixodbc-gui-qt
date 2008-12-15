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

#ifndef DLGTOOLSMANAGEAUTOTEST_H
#define DLGTOOLSMANAGEAUTOTEST_H

#include "odbctest.h"

class DlgToolsManageAutoTest : public QDialog 
{
    Q_OBJECT

    public:
		DlgToolsManageAutoTest( OdbcTest *parent, QString name );
        ~DlgToolsManageAutoTest();

	protected:
		QPushButton *close, *add, *remove, *from;
		OdbcTest *odbctest;
		QLabel *l_avail, *l_name, *l_lib, *l_so, *l_installed, *s_from, *s_name, *s_lib;
		QListWidget *lib_list, *test_list;
        char curr_dir[ 256 ];

        void SetPath( QString &str );
        void SetPath( const char *str );

	protected slots:
		void Ok();
        void From();
        void Add();
        void ListSelect( const QString &name );
        void Remove();
};

#endif

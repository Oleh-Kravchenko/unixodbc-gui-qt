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

#ifndef DLGTOOLSRUNAUTOTESTS_H
#define DLGTOOLSRUNAUTOTESTS_H

#include "odbctest.h"

class DlgToolsRunAutoTests : public QDialog 
{
    Q_OBJECT

    public:
		DlgToolsRunAutoTests( OdbcTest *parent, QString name );
        ~DlgToolsRunAutoTests();

	protected:
		QPushButton *run_list, *ok, *cancel, *log_file;
		OdbcTest *odbctest;
		QComboBox *rlist;
		QLabel *l_tests, *l_sources, *l_log;
		QGroupBox *output, *options;
        QListWidget *sources;
        QTreeWidget *tests;
        QCheckBox *b_log_file, *b_screen, *b_debug, *b_isolate, *b_cursor;

        void add_auto_test( const char * test_name, MYQListViewItem *top, MYQListViewItem **last_test );

	protected slots:
		void Ok();
        void Log();
        void LogChanged(int);
        void CursorChanged(int);
        void TestsChanged();

    private:
        int cursor_state;
};


#endif

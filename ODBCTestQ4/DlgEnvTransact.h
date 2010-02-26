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

#pragma once

#include "OdbcHandle.h"

class OdbcTest;

class DlgEnvTransact : public QDialog 
{
    Q_OBJECT

    public:
        DlgEnvTransact( OdbcTest *pOdbcTest, QString name );
        ~DlgEnvTransact();

	protected:
		QPushButton *ok, *cancel, *help;
		QTextEdit *in_win;
		QComboBox *ehandles, *chandles;
		QLabel *l_ehandles, *l_chandles;
		QComboBox *completion_type;
		QLabel *l_completion_type;
		QTextEdit *out_win;
		OdbcTest *pOdbcTest;
		QString txt;

	protected slots:
		void Ok();
};



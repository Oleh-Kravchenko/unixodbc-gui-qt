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

#ifndef DIAG_H
#define DIAG_H

#include "odbctest.h"

class dError : public QDialog 
{
    Q_OBJECT

    public:
		dError( OdbcTest *parent, QString name );
        ~dError();

	protected:
		QPushButton *ok, *cancel, *help;
		QComboBox *ehandles, *chandles, *shandles;
		QLabel *l_ehandle, *l_chandle, *l_shandle, *l_buffer_len;
		QCheckBox *native_valid, *error_valid, *perror_valid, *sqlstate_valid;
		QLineEdit *buffer_len;
		QTextEdit *in_win;
		OutputWin *out_win;
		OdbcTest *odbctest;
		QString txt;

	protected slots:
		void Ok();
        void native_clkd();
        void error_clkd();
        void perror_clkd();
        void sqlstate_clkd();
};

class dGetDiagRec : public QDialog 
{
    Q_OBJECT

    public:
		dGetDiagRec( OdbcTest *parent, QString name );
        ~dGetDiagRec();

	protected:
		QPushButton *ok, *cancel, *help;
		QComboBox *handle_type, *handles;
		QLabel *l_handle_type, *l_handles, *l_buffer_len, *l_rec_num;
		QCheckBox *native_valid, *error_valid, *perror_valid, *sqlstate_valid;
		QLineEdit *buffer_len, *rec_num;
		QTextEdit *in_win;
		OutputWin *out_win;
		OdbcTest *odbctest;
		QString txt;

	protected slots:
		void Ok();
        void native_clkd();
        void error_clkd();
        void perror_clkd();
        void sqlstate_clkd();
        void sel_handle( int );
};

class dGetDiagField : public QDialog 
{
    Q_OBJECT

    public:
		dGetDiagField( OdbcTest *parent, QString name );
        ~dGetDiagField();

	protected:
		QPushButton *ok, *cancel, *help;
		QComboBox *handle_type, *handles, *diag_info;
		QLabel *l_handle_type, *l_handles, *l_buffer_len, *l_rec_num, *l_diag_info;
		QCheckBox *diag_ptr_valid, *strlen_valid;
		QLineEdit *buffer_len, *rec_num;
		QTextEdit *in_win;
		OutputWin *out_win;
		OdbcTest *odbctest;
		QString txt;

	protected slots:
		void Ok();
        void diag_ptr_clkd();
        void strlen_clkd();
        void sel_handle( int );
};

#endif

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

#include "OdbcTest.h"

void OdbcTest::slotManageDataSources()
{
#ifdef WIN32
    if ( !SQLManageDataSources( (SQLHWND)this->winId() ) )
    {
        QMessageBox::about( this, "ODBC Test", "SQLManageDataSources() returned FALSE." );
    }
#else
    ODBCINSTWND Wnd;

    strcpy( Wnd.szUI, "odbcinstQ4" );
    Wnd.hWnd = this;

    if ( !SQLManageDataSources( &Wnd ) )
    {
        QMessageBox::about( this, "ODBC Test", "SQLManageDataSources() returned FALSE." );
    }
#endif
}

void OdbcTest::slotRemoveDefaultDataSource()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotConfigDataSource()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotCreateDataSource()
{
#ifdef WIN32
    if ( !SQLCreateDataSource( (SQLHWND)this->winId(), NULL ) )
    {
        QMessageBox::about( this, "ODBC Test", "SQLCreateDataSource() returned FALSE." );
    }
#else
    ODBCINSTWND Wnd;

    strcpy( Wnd.szUI, "odbcinstQ4" );
    Wnd.hWnd = this;

    if ( !SQLCreateDataSource( &Wnd, NULL ) )
    {
        QMessageBox::about( this, "ODBC Test", "SQLCreateDataSource() returned FALSE." );
    }
#endif
}

void OdbcTest::slotValidDSN()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotRemoveDSNFromIni()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotWriteDSNToIni()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotRemoveDrivers()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotConfigDrivers()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotInstallDriver()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotInstallDriverEx()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotGetInstalledDrivers()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotRemoveDriverManager()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotInstallDriverManager()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotReadFileDSN()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotWriteFileDSN()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotWritePrivateProfileString()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotGetPrivateProfileString()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotInstallTranslator()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotInstallTranslatorEx()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotRemoveTranslator()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotGetTranslator()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotSetConfigMode()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

void OdbcTest::slotGetConfigMode()
{
    QMessageBox::about( this, "ODBC Test",
			"Not yet implemented" );
}

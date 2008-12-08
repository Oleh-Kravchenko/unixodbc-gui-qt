/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#include <odbcinst.h>
#include <odbcinstext.h>

#include "DDataManager.h"

int main( int argc, char **argv )
{
    // init Qt application...
    QApplication app( argc, argv );
    QCoreApplication::setOrganizationName("unixODBC");
    QCoreApplication::setOrganizationDomain("unixodbc.org");
    QCoreApplication::setApplicationName("ODBC Data Manager");

    DDataManager datamanager;
    datamanager.show();

    return app.exec();
}


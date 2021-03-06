/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "OQGConsole.h"

#include <qapplication.h>
#include <qstring.h>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv  );

    OQGConsole *pmainwidget = new OQGConsole();
    pmainwidget->show();
    app.connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
    int nResult = app.exec();
    delete pmainwidget;
    
    return nResult;
}






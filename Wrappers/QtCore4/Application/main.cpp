/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "OQConsole.h"

#ifdef WIN32
int _tmain( int argc, ODBCCHAR *argv[] )
{
    OQConsole Console;

    if ( !Console.doParseArgs( argc, argv ) )
        return 1;

    if ( !Console.isConnected() )
        return 1;

    if ( !Console.doProcess() )
        return 1;

    Console.doDisconnect();

    return 0;
}
#else
#ifdef UNICODE
#else
int main( int argc, char *argv[] )
{
    OQConsole Console;

    if ( !Console.doParseArgs( argc, (ODBCCHAR**)argv ) )
        return 1;

    if ( !Console.isConnected() )
        return 1;

    if ( !Console.doProcess() )
        return 1;

    Console.doDisconnect();

    return 0;
}
#endif
#endif



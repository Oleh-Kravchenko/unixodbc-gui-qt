/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2009
 * \license Copyright unixODBC-GUI-Qt Project 2009-2010, LGPL
 */
#include <autotest.h>

#include <QtGui>

/*!
 * \brief   szLogPrintf.
 *
 *          This is a Qt specific implementation of szLogPrintf. This call
 *          is declared in unixODBC-Test::autotest.h.
 * 
 *          AutoTest libraries link to this when they want to be run from
 *          ODBCTestQ4.
 */
BOOL EXTFUNCDECL FAR szLogPrintf_( lpSERVERINFO pServerInfo )
{
    // ensure text is terminated...
    pServerInfo -> szBuff[ pServerInfo -> cBuff ] = '\0';

    // to GUI...
    if ( pServerInfo -> fScreen && pServerInfo->hwnd )
    {
        // the app (ie ODBCTestQ4) should have provided a QTextEdit for window handle...
        QTextEdit *pTextEdit = (QTextEdit*)pServerInfo->hwnd;
        pTextEdit->append( pServerInfo -> szBuff );
    }

    // to file...
    if ( pServerInfo -> fLog )
    {
        FILE *fp = fopen( pServerInfo -> szLogFile, "a+" );
        if ( fp )
        {
            fputs( pServerInfo -> szBuff, fp );
            fputs( "\n", fp );
            fclose( fp );
        }
    }

    // reset...
    pServerInfo -> cBuff = 0;

    return true;
}

BOOL EXTFUNCDECL FAR szLogPrintf( lpSERVERINFO pServerInfo, BOOL bForce, LPTSTR szFormat, ... )
{
    va_list         VariableArguments;
    char            szFormatted[4096];
    BOOL            bReturn = FALSE;

    /* sanity checks... */
    if ( !pServerInfo )
        return FALSE;

    /* format the message... */
    va_start( VariableArguments, szFormat );
    vsprintf( szFormatted, szFormat, VariableArguments );
    va_end( VariableArguments );


    /* pass call via SERVERINFO::szBuff - 1 line at-a-time... */
    char *pc = szFormatted;

    while ( *pc )
    {
        if ( *pc == '\n' || pServerInfo->cBuff >= ( MAXFLUSH - 1 ) )
        {
            bReturn = szLogPrintf_( pServerInfo );
        }
        else if ( isprint( *pc ))
        {
            pServerInfo->szBuff[ pServerInfo->cBuff ] = *pc;
            pServerInfo->cBuff++;
        }
        pc++;
    }

    if ( bForce && pServerInfo->cBuff > 0 )
        bReturn = szLogPrintf_( pServerInfo );

    /* fini... */

    return bReturn;
}


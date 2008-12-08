/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "ODBCConsole.h"

#include "ODBCDiagnostic.h"

#define MAX_LINE_IN_CHARS 4096
#define MAX_LINE_OUT_CHARS 32001

const char *szSyntax =
"\n" \
"**********************************************\n" \
"* ODBCConsole                                *\n" \
"**********************************************\n" \
"* Syntax                                     *\n" \
"*                                            *\n" \
"*   ODBCConsole [DSN [UID [PWD]]] [options]  *\n" \
"*                                            *\n" \
"* Options                                    *\n" \
"*                                            *\n" \
"* -s         list data source names          *\n" \
"* -r         list drivers                    *\n" \
"* -b         batch.(no prompting etc)        *\n" \
"* -dx        delimit columns with x          *\n" \
"* -x0xXX     delimit columns with XX, where  *\n" \
"*            x is in hex, ie 0x09 is tab     *\n" \
"* -w         wrap results in an HTML table   *\n" \
"* -tTable    wrap results in INSERT SQL      *\n" \
"* -qn,n,...  comma seperated list of column  *\n" \
"*            numbers where values should be  *\n" \
"*            quoted (use with -t)            *\n" \
"* -ux        char to use to quote char data  *\n" \
"* -ex        char(s) to use to terminate     *\n" \
"*            statements (i.e. use with -t)   *\n" \
"* -c         column names on first row.      *\n" \
"*            (only used when -d)             *\n" \
"* -mn        limit column display width to n *\n" \
"* -i         wide-char string data           *\n" \
"* -a         make ODBC calls asynch          *\n" \
"* -v         verbose.                        *\n" \
"* --version  version                         *\n" \
"*                                            *\n" \
"* Notes                                      *\n" \
"*                                            *\n" \
"*      odbcplus supports redirection and     *\n" \
"*      piping for batch processing.          *\n" \
"*                                            *\n" \
"* Examples                                   *\n" \
"*                                            *\n" \
"*  ODBCConsole MyDSN MyID MyPWD -w < My.sql  *\n" \
"*                                            *\n" \
"* Please visit;                              *\n" \
"*                                            *\n" \
"*      http://www.unixodbc.org               *\n" \
"*      pharvey@codebydesign.com              *\n" \
"**********************************************\n\n";

const char *szHelp = 
"\n" \
"+---------------------------------------+\n" \
"| HELP                                  |\n" \
"|                                       |\n" \
"| sql-statement                         |\n" \
"| show                                  |\n" \
"| quit                                  |\n" \
"|                                       |\n" \
"| IMPORTANT                             |\n" \
"|                                       |\n" \
"| ALL commands and statements should end|\n" \
"| with a ';'. This can be changed using |\n" \
"| -e option.                            |\n" \
"|                                       |\n" \
"+---------------------------------------+\n\n"; 

const char *szShow =
"\n" \
"show\n" \
"show config\n" \
"show driver [name]\n" \
"show dsn [name]\n" \
"show catalog [catalog]\n" \
"show schema [[catalog.]schema]\n" \
"show table [[[catalog.]schema.]table]\n" \
"show column [[[[catalog.]schema.]table.]column]\n" \
"show types\n" \
"\n" \
"NOTE: use %% as a wildcard as needed\n" \
"\n\n";

ODBCConsole::ODBCConsole()
{
    nInteraction            = InteractionUndefined; // try to figure it out based upon call order
    nResultFormat           = Boxed;
    bWideCharData           = false;
    bAsynch                 = false;
    bVerbose                = false;
    nUserWidth              = 0; // 0=not applicable
    cDelimiter              = '|';
    bColumnNames            = false;
    pszInsertTable          = NULL;
    pszColumnsToQuote       = NULL;
    pszQuoteToUse           = NULL;

    setQuoteToUse( TEXT("\"") );
    setStatementTerminator( ';' );

    pEnvironment            = 0;
    pConnection             = 0;
    pStatement              = 0;

    // We always want to have an ODBCEnvironment. We could create more than one in an application
    // but this seldom makes any sense.
    getEnvironment()->doAlloc();
    // We always want to have an ODBCConnection. Some applications will want to create more than
    // one of these but this application only needs one.
    getConnection()->doAlloc();
    // We always want to have an ODBCStatement. Some applications will want to create more than
    // one of these but this application only needs one.
    getStatement();
}

ODBCConsole::~ODBCConsole()
{
    if ( pStatement )
        delete pStatement;
    if ( pConnection )
        delete pConnection;
    if ( pEnvironment )
        delete pEnvironment;

    if ( pszInsertTable ) free( pszInsertTable );
    if ( pszColumnsToQuote ) free( pszColumnsToQuote );
    if ( pszQuoteToUse ) free( pszQuoteToUse );
}

void ODBCConsole::setUserWidth( SQLUINTEGER n ) 
{ 
    getStatement()->setStmtAttr( ODBCStatement::AttrMaxLength, (SQLPOINTER)n, 0 );
    nUserWidth = n; 
}

void ODBCConsole::setInsertTable( const ODBCCHAR *psz )
{
    if ( pszInsertTable ) free( pszInsertTable );
    pszInsertTable = NULL;
    if ( psz )
        pszInsertTable = (ODBCCHAR*)ODBCStrDup( psz );
}

void ODBCConsole::setColumnToQuote( const ODBCCHAR *psz )
{
    if ( pszColumnsToQuote ) free( pszColumnsToQuote );
    pszColumnsToQuote = NULL;
    if ( psz )
        pszColumnsToQuote = (ODBCCHAR*)ODBCStrDup( psz );
}

void ODBCConsole::setQuoteToUse( const ODBCCHAR *psz )
{
    if ( pszQuoteToUse ) free( pszQuoteToUse );
    pszQuoteToUse = NULL;
    if ( psz )
        pszQuoteToUse = (ODBCCHAR*)ODBCStrDup( psz );
}

/*!
    doParseArgs
    
*/    
bool ODBCConsole::doParseArgs( int argc, ODBCCHAR *argv[] )
{
    int         nArg;
    int         nCount;
    ODBCCHAR    cCommand = ' ';
    ODBCCHAR *  pszDSN      = NULL;
    ODBCCHAR *  pszUID      = NULL;
    ODBCCHAR *  pszPWD      = NULL;

    if ( argc < 2 )
    {
        fprintf( stderr, szSyntax );
        return false;
    }

    nInteraction    = CommandLineInteractive;
    nResultFormat   = Boxed;

    for ( nArg = 1, nCount = 1 ; nArg < argc; nArg++ )
    {
        if ( argv[nArg][0] == '-' )
        {
            /* Options */
            switch ( argv[nArg][1] )
            {
                case 's':
                    cCommand = 's';
                    break;
                case 'r':
                    cCommand = 'r';
                    break;
                case 'd':
                    cDelimiter = argv[nArg][2];
                    nResultFormat = Delimited;
                    break;
                case 'm':
                    setUserWidth( ODBCToI( &(argv[nArg][2]) ) );
                    break;
                case 'a':
                    bAsynch = true;
                    break;
                case 'w':
                    nResultFormat = Html;
                    break;
                case 't':
                    pszInsertTable = &(argv[nArg][2]);
                    nResultFormat = Insert;
                    break;
                case 'q':
                    pszColumnsToQuote = &(argv[nArg][2]);
                    break;
                case 'u':
                    pszQuoteToUse = &(argv[nArg][2]);
                    break;
                case 'e':
                    cStatementTerminator = argv[nArg][2];
                    break;
                case 'b':
                    nInteraction = CommandLineBatch;
                    break;
                case 'c':
                    bColumnNames = true;
                    break;
                case 'i':
                    bWideCharData = true;
                    break;
                case 'v':
                    bVerbose = true;
                    break;
                case '-':
                    printf( "ODBCConsole %d.%d.%d\n", V_MAJOUR, V_MINOR, V_RELEASE );
                    return false;
                case 'x':
                    cDelimiter = argv[nArg][2];
                    break;
                default:
                    fprintf( stderr, szSyntax );
                    return false;
            }
            continue;
        }
        else if ( nCount == 1 )
        {
            pszDSN = argv[nArg];
        }
        else if ( nCount == 2 )
        {
            pszUID = argv[nArg];
        }
        else if ( nCount == 3 )
        {
            pszPWD = argv[nArg];
        }
        nCount++;
    } // for each arg

    //
    if ( cCommand == 's' )
    {
        doExecuteShow( TEXT("dsn") );
    }
    else if ( cCommand == 'r' )
    {
        doExecuteShow( TEXT("driver") );
    }
    else
    {
        // connect...
        if ( !doConnect( pszDSN, pszUID, pszPWD ) )
            return false;
    }

    return true;
}

bool ODBCConsole::doConnect( const ODBCCHAR *pszDSN, const ODBCCHAR *pszUID, const ODBCCHAR *pszPWD )
{
    if ( nInteraction == ODBCConsole::InteractionUndefined )
        nInteraction = ApplicationControlled;

    if ( !SQL_SUCCEEDED( getConnection()->doConnect( pszDSN, SQL_NTS, pszUID, SQL_NTS, pszPWD, SQL_NTS ) ) )
    {
        if ( bVerbose ) doDisplayErrors( pConnection );
        fprintf( stderr, "[ODBCConsole]ERROR: Failed to connect\n" );
        return false;
    }

    return true;
}

bool ODBCConsole::doDisconnect()
{
    if ( getStatement()->isAlloc( false ) )
        getStatement()->doFree();

    if ( !SQL_SUCCEEDED( getConnection()->doDisconnect() ) )
    {
        if ( bVerbose ) doDisplayErrors( pConnection );
        fprintf( stderr, "[ODBCConsole]ERROR: Failed to properly disconnect\n" );
        return false;
    }

    return true;
}

/*!
    doProcess
    
    This is the main loop for the application. It accepts and processes
    user input.
*/
bool ODBCConsole::doProcess()
{
    // Turning the ODBC asynch on may result in some feedback while long requests
    // are waited on. Mostly its just here to test asynch.
/*
    if ( bAsynch )
    {
        if ( !SQL_SUCCEEDED( getConnection()->setAttrAsyncEnable( SQL_ASYNC_ENABLE_ON ) ) )
        {
            if ( bVerbose ) doDisplayErrors( getConnection()->doMessages() );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to turn asynch on\n" );
            return false;
        }
    }
    if ( bVerbose ) doDisplayErrors( getConnection()->getMessages() );
*/

    // Turning the ODBC asynch on may result in some feedback while long requests
    // are waited on. Mostly its just here to test asynch.
    if ( bAsynch )
    {
        if ( !SQL_SUCCEEDED( getStatement()->setAttrAsyncEnable( ODBCStatement::AsyncEnableOn ) ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to turn asynch on\n" );
            return false;
        }
    }

    //
    // PROCESS
    //
    switch ( nInteraction )
    {
        case ApplicationControlled:
            doProcessInteractive();
            break;
        case CommandLineBatch:
            doProcessBatch();
            break;
        case CommandLineInteractive:
            doProcessInteractive();
            break;
        case InteractionUndefined:
            nInteraction = ApplicationControlled;
            doProcessInteractive();
            break;
    }

    return true;
}

/*!
    doProcessBatch
    
    Main loop.
*/
bool ODBCConsole::doProcessBatch()
{
    ODBCCHAR *  pszCommand      = 0;    // command in the making
    ODBCCHAR    cRead           = 0;    // contains last char read
    ODBCCHAR    cQuote          = 0;    // contains quote if we are in quote
    int         nCommandSize    = 0;

    while ( 1 )
    {
        cRead = ODBCFGetC( stdin );
        if ( cRead == (ODBCCHAR)ODBCEof )
            break;

        if ( cRead == cStatementTerminator && cQuote == 0 )
        {
            // we have a command
            if ( pszCommand )
            {
                // append '\0'
                nCommandSize++;
                pszCommand = (ODBCCHAR*)realloc( pszCommand, nCommandSize * sizeof(ODBCCHAR) );
                pszCommand[nCommandSize - 1] = '\0';

                // process command
                if ( !doProcessCommand( pszCommand ) )
                    break;

                // cleanup
                free( pszCommand );
                pszCommand      = 0;
                nCommandSize    = 0;
            }
        }
        else
        {
            // toggle quote state as required
            // - we do not want to interpret a statement terminator when it is in quotes
            // - this is simplistic because it does not handle quotes which may be escaped in string
            if ( cQuote )
            {
                if ( cQuote == cRead )
                    cQuote = 0;
            }
            else
            {
                if ( cRead == '\'' || cRead == '\"' )
                    cQuote = cRead;
            }

            // accumilate
            nCommandSize++;
            pszCommand = (ODBCCHAR*)realloc( pszCommand, nCommandSize *sizeof(ODBCCHAR) );
            pszCommand[nCommandSize - 1] = cRead;
        }

    } // while

    // cleanup
    if ( pszCommand )
        free( pszCommand );

    return 1;
}

/*!
    doProcessInteractive
    
    Main loop.
*/
bool ODBCConsole::doProcessInteractive()
{
    ODBCCHAR *  pszCommand      = 0;    // command in the making
    ODBCCHAR *  pszLine         = 0;    // contains last line read
    ODBCCHAR    cQuote          = 0;    // contains quote if we are in quote
    int         nCommandSize    = 0;    // current length of pszCommand
    bool        bReadLines      = true;
    ODBCCHAR    szLine[MAX_LINE_IN_CHARS + 1];

    // display some help
    printf( szHelp );

    // 
    while ( bReadLines )
    {
        if ( cQuote )
            printf( "ODBCConsole (text currently in quotes)> " );
        else
            printf( "ODBCConsole> " );

        pszLine = ODBCFGetS( szLine, sizeof(szLine), stdin );
        if ( !pszLine ) // EOF - ctrl D - this should not happen but may if file directed into us without batch flag being set
            break;

        // process line
        for ( ODBCCHAR *psz = pszLine; *psz != '\0'; psz++ )
        {
            if ( *psz == cStatementTerminator && cQuote == 0 )
            {
                // we have a command
                if ( pszCommand )
                {
                    // append '\0'
                    nCommandSize++;
                    pszCommand = (ODBCCHAR*)realloc( pszCommand, nCommandSize * sizeof(ODBCCHAR) );
                    pszCommand[nCommandSize - 1] = '\0';

                    // process command
                    if ( !doProcessCommand( pszCommand ) )
                    {
                        // we have a quit command so quit both loops and exit function
                        bReadLines = false;
                        break; 
                    }

                    // cleanup
                    free( pszCommand );
                    pszCommand      = 0;
                    nCommandSize    = 0;
                }
            }
            else
            {
                // toggle quote state as required
                // - we do not want to interpret a statement terminator when it is in quotes
                // - this is simplistic because it does not handle quotes which may be escaped in string
                if ( cQuote )
                {
                    if ( cQuote == *psz )
                        cQuote = 0;
                }
                else
                {
                    if ( *psz == '\'' || *psz == '\"' )
                        cQuote = *psz;
                }

                // accumilate
                nCommandSize++;
                pszCommand = (ODBCCHAR*)realloc( pszCommand, nCommandSize * sizeof(ODBCCHAR) );
                pszCommand[nCommandSize - 1] = *psz;
            }
        }
    } // while

    // cleanup
    if ( pszCommand )
        free( pszCommand );

    return 1;
}

/*!
    doProcessCommand

    Return false to exit main loop and app.    
*/
bool ODBCConsole::doProcessCommand( ODBCCHAR *pszCommand )
{
//	ODBCCHAR *pEscapeChar;
    ODBCCHAR *pCharCursor;
    ODBCCHAR *pCharAnchor;

    // strip away escape chars
//    while ( (pEscapeChar=(char*)strchr( (char*)pszCommand, '\n')) != NULL || (pEscapeChar=(char*)strchr( (char*)pszCommand, '\r')) != NULL )
//        *pEscapeChar = ' ';

    // trim leading spaces - end up on null term at end of string
    pCharCursor = pCharAnchor = pszCommand;
    while ( ODBCIsSpace( *pCharCursor ) )
    {
        pCharCursor++;
    }
    if ( pCharCursor != pCharAnchor )
        while ( 1 )
        {
            *pCharAnchor = *pCharCursor; if ( *pCharCursor == '\0' ) break;pCharAnchor++; pCharCursor++;
        }
    else
        while ( *pCharAnchor != '\0' )
        {
            pCharAnchor++;
        }

    // trim trailing spaces
//    pCharCursor = pCharAnchor;
//    while ( *pCharCursor != '\0' && isspace( *pCharCursor ) ) { *pCharCursor = '\0'; if ( pCharCursor == pszCommand ) break; pCharCursor--; }

    //
    if ( *pszCommand == '\0' )
        return 1;

    //
    if ( ODBCStrNCmp( pszCommand, TEXT("quit"), 4 ) == 0 )
        return 0;
    else if ( ODBCStrNCmp( pszCommand, TEXT("show "), 5 ) == 0 )            // process the given 'show' command
        doExecuteShow( &(pszCommand[5]) );
    else if ( ODBCStrNCmp( pszCommand, TEXT("show"), 4 ) == 0 )             // display the 'show' commands
        doExecuteShow();
    else if ( ODBCStrNCmp( pszCommand, TEXT("help"), 4 ) == 0 )             // display some help
    {
        printf( szHelp );
        printf( "ODBCConsole> " );
    }
    else
        doExecuteSQL( pszCommand );                         // process the given 'SQL' statement

    return 1;
}

/*!
    doExecuteSQL
    
    Prepare and execute SQL then process any results.
*/
bool ODBCConsole::doExecuteSQL( const ODBCCHAR *pszSQL )
{
    ODBCCHAR    szSepLine[MAX_LINE_OUT_CHARS + 1];
    SQLSMALLINT nCols   = -1;
    SQLLEN      nRows   = 0;

    *szSepLine = '\0';

    if ( !SQL_SUCCEEDED( getStatement()->doPrepare( (ODBCCHAR*)pszSQL, SQL_NTS ) ) )
    {
        if ( bVerbose ) doDisplayErrors( pStatement );
        getStatement()->doFree();
        fprintf( stderr, "[ODBCConsole]ERROR: While preparing statement\n" );
        return false;
    }

    if ( !SQL_SUCCEEDED( getStatement()->doExecute() ) )
    {
        if ( bVerbose ) doDisplayErrors( pStatement );
        getStatement()->doFree();
        fprintf( stderr, "[ODBCConsole]ERROR: While executing statement\n" );
        return false;
    }

    /*
     * check to see if it has generated a result set
     */
    if ( !SQL_SUCCEEDED( getStatement()->doNumResultCols( &nCols ) ) )
    {
        if ( bVerbose ) doDisplayErrors( pStatement );
        getStatement()->doFree();
        fprintf( stderr, "[ODBCConsole]ERROR: While requesting number of columns\n" );
        return false;
    }

    if ( nCols > 0 )
    {
        /****************************
         * WRITE HEADER
         ***************************/
        switch ( nResultFormat )
        {
            case Boxed:
                doWriteHeaderNormal( szSepLine );
                break;
            case Delimited:
                doWriteHeaderDelimited();
                break;
            case Html:
                doWriteHeaderHTMLTable();
                break;
            case Insert:
                break;
        }

        /****************************
         * WRITE BODY
         ***************************/
        switch ( nResultFormat )
        {
            case Boxed:
                nRows = doWriteBodyNormal();
                break;
            case Delimited:
                doWriteBodyDelimited();
                break;
            case Html:
                nRows = doWriteBodyHTMLTable();
                break;
            case Insert:
                doWriteBodyInsertTable();
                break;
        }
    }

    /****************************
     * WRITE FOOTER
     ***************************/
    switch ( nResultFormat )
    {
        case Boxed:
            doWriteFooterNormal( szSepLine, nRows );
            break;
        case Delimited:
            break;
        case Html:
            doWriteFooterHTMLTable( nRows );
            break;
        case Insert:
            break;
    }

    // fini
    getStatement()->doCloseCursor();

    return true;
}

/*!
    doExecuteShow
    
    Process "show" commands.
*/
bool ODBCConsole::doExecuteShow( const ODBCCHAR *pszShow )
{
    if ( !pszShow || *pszShow == '\0' )
    {
        printf( szShow );
        return true;
    }

    // show config
    ODBCSystem OdbcSystem;
    if ( ODBCStrNCmp( pszShow, TEXT("config"), 6 ) == 0 )
    {
        vector<ODBCKeyValue> vectorProperties = OdbcSystem.getProperties();
        vector<ODBCKeyValue>::iterator i;
        const char *pszSep0   = "----------------------";
        const char *pszSep1   = "------------------------------------------------------------------------------------------------------";
        const char *pszTitle0 = "Key";
        const char *pszTitle1 = "Value";
        SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
        SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

        printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
        printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
        printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

        for ( i = vectorProperties.begin(); i != vectorProperties.end(); i++ )
        {
            ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szKey, nWidth1, nWidth1, (*i).szValue );
        }

        printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

        return true;
    }
    // show driver
    else if ( ODBCStrNCmp( pszShow, TEXT("driver"), 6 ) == 0 )
    {
        // driver details?
        if ( ODBCStrNCmp( pszShow, TEXT("driver "), 7 ) == 0 )
        {
            ODBCDriver Driver = OdbcSystem.getDriver( (ODBCCHAR*)&pszShow[7] );
            vector<ODBCKeyValue>::iterator i;
            const char *pszSep0   = "----------------------";
            const char *pszSep1   = "-----------------------------------------------------------------------------";
            const char *pszTitle0 = "Key";
            const char *pszTitle1 = "Value";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            ODBCPrintF( (ODBCCPTR)TEXT("%s\n"), (ODBCCHAR*)&pszShow[7] );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            for ( i = Driver.vectorProperties.begin(); i != Driver.vectorProperties.end(); i++ )
            {
                ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szKey, nWidth1, nWidth1, (*i).szValue );
            }

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            return true;
        }
        else
        {
            // list drivers...

            /*
             * METHOD 1
             */
            vector<ODBCDriver> vectorDrivers = OdbcSystem.getDrivers();
            vector<ODBCDriver>::iterator i;
            const char *pszSep0   = "----------------------------------------------";
            const char *pszSep1   = "----------------------------------------------";
            const char *pszTitle0 = "Driver";
            const char *pszTitle1 = "Description";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            for ( i = vectorDrivers.begin(); i != vectorDrivers.end(); i++ )
            {
                const ODBCCHAR *pszDescription = OdbcSystem.getValue( (*i).vectorProperties, (ODBCCHAR*)TEXT("description") );
                if ( pszDescription )
                    ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, pszDescription );
                else
                    ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, TEXT("") );
            }

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            /*
             * METHOD 2
             */
            /* 
            SQLRETURN   nReturn;
            ODBCCHAR    szDescription[21];
            SQLSMALLINT nDescriptionLength;
            ODBCCHAR    szAttributes[4096];
            SQLSMALLINT nAttributesLength;
            char *pszSep0   = "----------------------";
            char *pszSep1   = "------------------------------------------------------------------------------------------------------";
            char *pszTitle0 = "Driver";
            char *pszTitle1 = "First Attribute";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );
    
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            nReturn = pEnvironment->doDrivers( SQL_FETCH_FIRST, szDescription, sizeof(szDescription) - 1, &nDescriptionLength, szAttributes, sizeof(szAttributes) - 1, &nAttributesLength );
            while ( SQL_SUCCEEDED( nReturn ) )
            {
                ODBCPrintF( TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, szDescription, nWidth1, nWidth1, szAttributes );
                nReturn = pEnvironment->doDrivers( SQL_FETCH_NEXT, szDescription, sizeof(szDescription) - 1, &nDescriptionLength, szAttributes, sizeof(szAttributes) - 1, &nAttributesLength );
            }
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            if ( nReturn != SQL_NO_DATA )
            {
                if ( bVerbose ) doDisplayErrors( pEnvironment->getMessages() );
                fprintf( stderr, "[ODBCConsole]ERROR: While getting driver listing\n" );
                return false;
            }
            */
            return true;
        }
    }
    // show dsn
    else if ( ODBCStrNCmp( pszShow, TEXT("dsn"), 3 ) == 0 )
    {
        // dsn details?
        if ( ODBCStrNCmp( pszShow, TEXT("dsn "), 4 ) == 0 )
        {
            ODBCDataSourceName DataSourceName = OdbcSystem.getDataSourceName( (ODBCCHAR*)&pszShow[4] );
            vector<ODBCKeyValue>::iterator i;
            const char *pszSep0   = "----------------------";
            const char *pszSep1   = "------------------------------------------------------------------------------------------------------";
            const char *pszTitle0 = "Key";
            const char *pszTitle1 = "Value";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            ODBCPrintF( (ODBCCPTR)TEXT("%s\n"), (ODBCCHAR*)&pszShow[4] );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            for ( i = DataSourceName.vectorProperties.begin(); i != DataSourceName.vectorProperties.end(); i++ )
            {
                ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szKey, nWidth1, nWidth1, (*i).szValue );
            }

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            return true;
        }
        else
        {
            // list dsn's...
            /*
             * METHOD 1
             */
            vector<ODBCDataSourceName> vectorDataSourceNames = OdbcSystem.getDataSourceNames();
            vector<ODBCDataSourceName>::iterator i;
            const char *pszSep0   = "----------------------";
            const char *pszSep1   = "------------------------------------------------------------------------------------------------------";
            const char *pszTitle0 = "DataSourceName";
            const char *pszTitle1 = "Description";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            for ( i = vectorDataSourceNames.begin(); i != vectorDataSourceNames.end(); i++ )
            {
                const ODBCCHAR *pszDescription = OdbcSystem.getValue( (*i).vectorProperties, (ODBCCHAR*)TEXT("description") );
                if ( pszDescription )
                    ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, pszDescription );
                else
                    ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, TEXT("") );
            }

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

            /*
             * METHOD 2
             */
            /* 
            SQLRETURN   nReturn;
            ODBCCHAR    szDSN[21];
            SQLSMALLINT nNameLength1;
            ODBCCHAR    szDescription[101];
            SQLSMALLINT nNameLength2;
            char *pszSep0   = "----------------------";
            char *pszSep1   = "------------------------------------------------------------------------------------------------------";
            char *pszTitle0 = "Data Source Name";
            char *pszTitle1 = "Description";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            printf( "| %-*.*s | %-*.*s |\n", nWidth0, nWidth0, pszTitle0, nWidth1, nWidth1, pszTitle1 );
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            nReturn = pEnvironment->doDataSources( SQL_FETCH_FIRST, szDSN, sizeof(szDSN) - 1, &nNameLength1, szDescription, sizeof(szDescription) - 1, &nNameLength2 );
            while ( SQL_SUCCEEDED( nReturn ) )
            {
                ODBCPrintF( TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, szDSN, nWidth1, nWidth1, szDescription );
                nReturn = pEnvironment->doDataSources( SQL_FETCH_NEXT, szDSN, sizeof(szDSN) - 1, &nNameLength1, szDescription, sizeof(szDescription) - 1, &nNameLength2 );
            }
            printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );
            if ( nReturn != SQL_NO_DATA )
            {
                if ( bVerbose ) doDisplayErrors( pEnvironment->getMessages() );
                fprintf( stderr, "[ODBCConsole]ERROR: While getting data source listing\n" );
                return false;
            }
            */ 
            return true; 
        }
    }
    // show catalog
    else if ( ODBCStrNCmp( pszShow, TEXT("catalog"), 7 ) == 0 )
    {
        SQLRETURN nReturn;

        if ( pszShow[7] == ' ' )
            nReturn = getStatement()->doTables( (ODBCCHAR*)&pszShow[8] );
        else
            nReturn = getStatement()->doTables( (ODBCCHAR*)TEXT(SQL_ALL_CATALOGS) );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to get catalogs\n" );
            return false;
        }
    }
    // show schema
    else if ( ODBCStrNCmp( pszShow, TEXT("schema"), 6 ) == 0 )
    {
        SQLRETURN nReturn;

        if ( pszShow[6] == ' ' )
            nReturn = getStatement()->doTables( NULL, 0, (ODBCCHAR*)&pszShow[7], SQL_NTS );
        else
            nReturn = getStatement()->doTables( NULL, 0, (ODBCCHAR*)TEXT(SQL_ALL_SCHEMAS), SQL_NTS );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to get schemas\n" );
            return false;
        }
    }
    // show table
    else if ( ODBCStrNCmp( pszShow, TEXT("table"), 5 ) == 0 )
    {
        SQLRETURN nReturn;

        if ( pszShow[5] == ' ' )
        {
            nReturn = getStatement()->doColumns( NULL, 0, NULL, 0, (ODBCCHAR*)&pszShow[6], SQL_NTS, NULL, 0 );
        }
        else
        {
            nReturn = getStatement()->doTables( NULL, 0, NULL, 0, NULL, 0, (ODBCCHAR*)TEXT("TABLE"), SQL_NTS );
        }

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to get tables\n" );
            return false;
        }
    }
    // show column
    else if ( ODBCStrNCmp( pszShow, TEXT("column"), 6 ) == 0 )
    {
        pszShow = &(pszShow[7]);
        /*! 
         * \note    1. MS Access needs Catalog = NULL. Catalog = "" does not work.
         *  
         */
        if ( !SQL_SUCCEEDED( getStatement()->doColumns( NULL, SQL_NTS, NULL, SQL_NTS, (ODBCCHAR*)pszShow, SQL_NTS, TEXT("%"), SQL_NTS ) ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: While requesting column listing\n" );
            return false;
        }
    }
    // show types
    else if ( ODBCStrNCmp( pszShow, TEXT("types"), 5 ) == 0 )
    {
        if ( !SQL_SUCCEEDED( getStatement()->doTypeInfo() ) )
        {
            if ( bVerbose ) doDisplayErrors( pStatement );
            fprintf( stderr, "[ODBCConsole]ERROR: Failed to get type info\n" );
            return false;
        }
    }

    /****************************
     * WRITE HEADER
     ***************************/
    ODBCCHAR szSepLine[MAX_LINE_OUT_CHARS + 1];
    SQLLEN   nRows            = 0;

    *szSepLine = '\0';

    switch ( nResultFormat )
    {
        case Boxed:
            doWriteHeaderNormal( szSepLine );
            break;
        case Delimited:
            doWriteHeaderDelimited();
            break;
        case Html:
            doWriteHeaderHTMLTable();
            break;
        case Insert:
            break;
    }

    /****************************
     * WRITE BODY
     ***************************/
    switch ( nResultFormat )
    {
        case Boxed:
            nRows = doWriteBodyNormal();
            break;
        case Delimited:
            doWriteBodyDelimited();
            break;
        case Html:
            nRows = doWriteBodyHTMLTable();
            break;
        case Insert:
            doWriteBodyInsertTable();
            break;
    }

    /****************************
     * WRITE FOOTER
     ***************************/
    switch ( nResultFormat )
    {
        case Boxed:
            doWriteFooterNormal( szSepLine, nRows );
            break;
        case Delimited:
            break;
        case Html:
            doWriteFooterHTMLTable( nRows );
            break;
        case Insert:
            break;
    }

    // fini
    getStatement()->doCloseCursor();

    return true;
}

/****************************
 * WRITE HTML
 ***************************/
void ODBCConsole::doWriteHeaderHTMLTable()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    ODBCCHAR        szColumnName[MAX_DATA_WIDTH+1];

    *szColumnName = '\0';

    if ( !SQL_SUCCEEDED( getStatement()->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    printf( "<div id=ResultSet>\n" );
    printf( "<table border>\n" );

    printf( "\t<thead>\n" );
    printf( "\t\t<tr>\n" );

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        getStatement()->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, MAX_DATA_WIDTH, NULL, NULL );
        printf( "\t\t\t<th scope=\"col\">" );
        ODBCPrintF( (ODBCCPTR)TEXT("%s"), szColumnName );
        printf( "</th>\n" );
    }
    printf( "\t\t</tr>\n" );
    printf( "\t</thead>\n" );

    printf( "\t<tbody>\n" );
}

SQLLEN ODBCConsole::doWriteBodyHTMLTable()
{
    SQLUSMALLINT    nCol        = 0;
    SQLSMALLINT     nColumns    = 0;
    SQLRETURN       nReturn     = 0;
    SQLLEN          nRows       = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    getStatement()->doNumResultCols( &nColumns );

    /* ROWS */
    while ( SQL_SUCCEEDED( getStatement()->doFetch() ) )
    {
        nRows++;
        printf( "\t\t<tr>\n" );
        printf( "\t\t\t<th scope=\"row\" id=\"%d\"></th>\n", nRows );
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            printf( "\t\t\t<td>" );
            nReturn = getStatement()->doData( nCol, &v );
            if ( !v.isNull() )
            {
                if ( bWideCharData )
                    wprintf( L"%s", (SQLWCHAR*)v.getBuffer() );
                else
                    printf( (const char *)v.getBuffer() );
            }
            printf( "</td>\n" );
        }
        printf( "\t\t</tr>\n" );
    }

    if ( bVerbose ) doDisplayErrors( pStatement );

    return nRows;
}

void ODBCConsole::doWriteFooterHTMLTable( SQLLEN nRows )
{
    SQLSMALLINT nColumns      = 1;
    SQLLEN      nRowsAffected = -1;

    getStatement()->doNumResultCols( &nColumns );
    getStatement()->doRowCount( &nRowsAffected );

    printf( "\t</tbody>\n" );

    printf( "\t<tfoot>\n" );
    printf( "\t\t<tr>\n" );
    printf( "\t\t\t<td colspan=\"%d\">Rows affected: %d returned: %d</th>\n", nColumns, nRowsAffected, nRows );
    printf( "\t\t</tr>\n" );
    printf( "\t</tfoot>\n" );

    printf( "</table>\n" );
    printf( "</div>\n" );
}

/****************************
 * WRITE INSERT TABLE 
 ***************************/
void ODBCConsole::doWriteBodyInsertTable()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLRETURN       nReturn                         = 0;
    bool *          pbQuote                         = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    getStatement()->doNumResultCols( &nColumns );

    if ( nColumns <= 0 )
        return;

    pbQuote = (bool*)calloc( sizeof(bool), nColumns );

    // parse pszColumnsToQuote
    if ( pszColumnsToQuote )
    {
        int         nCursorColumnsToQuote   = 0;
        int         nCursorColumn           = 0;
        ODBCCHAR    szColumn[100];

        while ( 1 )
        {
            if ( pszColumnsToQuote[nCursorColumnsToQuote] == ',' || pszColumnsToQuote[nCursorColumnsToQuote] == '\0' )
            {
                if ( nCursorColumn )
                {
                    szColumn[nCursorColumn] = '\0';
                    int nColumn = ODBCToI( szColumn );
                    if ( nColumn > 0 && nColumn <= nColumns )
                    {
                        pbQuote[nColumn - 1] = 1;
                    }
                    nCursorColumn = 0;

                }
            }
            else
            {
                szColumn[nCursorColumn] = pszColumnsToQuote[nCursorColumnsToQuote];
                nCursorColumn++;
            }

            if ( pszColumnsToQuote[nCursorColumnsToQuote] == '\0' )
                break;

            nCursorColumnsToQuote++;
        }
    }

    // process results
    while ( SQL_SUCCEEDED( getStatement()->doFetch() ) ) /* ROWS */
    {
        ODBCPrintF( (ODBCCPTR)TEXT("INSERT INTO %s VALUES ( "), pszInsertTable );
        for ( nCol = 1; nCol <= nColumns; nCol++ ) /* COLS */
        {
            if ( nCol > 1 )
                printf( ", " );

            nReturn = getStatement()->doData( nCol, &v );
            if ( v.isNull() )
                printf( "NULL" );
            else
            {
                // TODO: Escape any quote char embedded in char data
                ODBCPrintF( (ODBCCPTR)TEXT("%s"), ( pbQuote[nCol - 1] ? pszQuoteToUse : TEXT("") ) ); 
                if ( bWideCharData )
                    wprintf( L"%s", (SQLWCHAR*)v.getBuffer() );
                else
                    printf( (const char *)v.getBuffer() );
                ODBCPrintF( (ODBCCPTR)TEXT("%s"), ( pbQuote[nCol - 1] ? pszQuoteToUse : TEXT("") ) ); 
            }
        } // cols
        ODBCPrintF( (ODBCCPTR)TEXT(" )%c\n"), cStatementTerminator );
    } // rows

    free( pbQuote );
}

/****************************
 * WRITE DELIMITED
 * - this output can be used by the ODBC Text File driver
 * - last column no longer has a delimit char (it is implicit)...
 *   this is consistent with odbctxt
 ***************************/
void ODBCConsole::doWriteHeaderDelimited()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    ODBCCHAR        szColumnName[MAX_DATA_WIDTH+1];

    *szColumnName = '\0';

    if ( !SQL_SUCCEEDED( getStatement()->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        getStatement()->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), NULL, NULL );
        ODBCFPutS( szColumnName, stdout );
        if ( nCol < nColumns )
            ODBCPutChar( cDelimiter );
    }
    ODBCPutChar( '\n' );
}

void ODBCConsole::doWriteBodyDelimited()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLRETURN       nReturn                         = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    getStatement()->doNumResultCols( &nColumns );

    /* ROWS */
    while ( SQL_SUCCEEDED( getStatement()->doFetch() ) )
    {
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            nReturn = getStatement()->doData( nCol, &v );
            if ( v.isNull() )
            {
                if ( nCol < nColumns )
                    ODBCPutChar( cDelimiter );
            }
            else
            {
                if ( bWideCharData )
                    wprintf( L"%s", v.getBuffer() );
                else
                    printf( (const char *)v.getBuffer() );
                if ( nCol < nColumns )
                    ODBCPutChar( cDelimiter );
            }
        }
        printf( "\n" );
    }

    if ( bVerbose ) doDisplayErrors( pStatement );
}

/****************************
 * WRITE NORMAL
 ***************************/
void ODBCConsole::doWriteHeaderNormal( ODBCCHAR *szSepLine )
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    ODBCCHAR        szColumn[MAX_DATA_WIDTH+20];
    ODBCCHAR        szColumnName[MAX_DATA_WIDTH+1];
    ODBCCHAR        szHdrLine[MAX_LINE_OUT_CHARS + 1];
    SQLUINTEGER     nSepLine                        = 0;    // index to next char

    *szColumn       = '\0';
    *szColumnName   = '\0';
    *szHdrLine      = '\0';

    vectorColumnWidths = getColumnWidths( pStatement, nUserWidth );

    if ( !SQL_SUCCEEDED( getStatement()->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        SQLUINTEGER nColumnWidth = vectorColumnWidths.at( nCol - 1 );
        getStatement()->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), NULL, NULL );

        /* SEP */
        szSepLine[nSepLine] = '+'; nSepLine++;
        for ( SQLUINTEGER n = 0; n <= nColumnWidth; n++, nSepLine++ ) { szSepLine[nSepLine] = '-'; }

        /* HDR */
        ODBCSPrintF( (ODBCCPTR)szColumn, (ODBCCPTR)TEXT("| %-*.*s"), (int)nColumnWidth, (int)nColumnWidth, szColumnName );
        ODBCStrCat( szHdrLine, MAX_LINE_OUT_CHARS, szColumn );
    }
    szSepLine[nSepLine] = '+'; nSepLine++;
    szSepLine[nSepLine] = '\n'; nSepLine++;
    szSepLine[nSepLine] = '\0'; nSepLine++;

    ODBCStrCat( szHdrLine, MAX_LINE_OUT_CHARS, TEXT("|\n") );

    ODBCPrintF( (ODBCCPTR)szSepLine );
    ODBCPrintF( (ODBCCPTR)szHdrLine );
    ODBCPrintF( (ODBCCPTR)szSepLine );
}

SQLLEN ODBCConsole::doWriteBodyNormal()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLRETURN       nReturn                         = 0;
    SQLLEN          nRows                           = 0;

    /*! 
     * \note
     *          We can be a single-char app and still work with wide-char data. Conversely; we can be 
     *          a wide-char app and need to work with single-char data.
     *  
     * \sa      setWideCharData
     */
    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    getStatement()->doNumResultCols( &nColumns );
    
    /* ROWS */
    while ( SQL_SUCCEEDED( getStatement()->doFetch() ) )
    {
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            SQLUINTEGER nColumnWidth = vectorColumnWidths.at( nCol - 1 );

            // get the data
            nReturn = getStatement()->doData( nCol, &v );
            if ( v.isNull() )
                ODBCPrintF( (ODBCCPTR)TEXT("| %-*s"), (int)nColumnWidth, TEXT("") );
            else
            {
                if ( bWideCharData )
                    wprintf( L"| %-*.*s", (int)nColumnWidth, (int)nColumnWidth, (SQLWCHAR*)v.getBuffer() );
                else
                    printf( "| %-*.*s", (int)nColumnWidth, (int)nColumnWidth, (SQLCHAR*)v.getBuffer() );
            }

            v.clear();

        } /* for columns */

        nRows++;
        printf( "|\n" );
    } /* while rows */

    if ( bVerbose ) doDisplayErrors( pStatement );

    return nRows;
}

void ODBCConsole::doWriteFooterNormal( ODBCCHAR *szSepLine, SQLLEN nRows )
{
    SQLLEN nRowsAffected = -1;

    ODBCPrintF( (ODBCCPTR)szSepLine );

    getStatement()->doRowCount( &nRowsAffected );
    if ( nRowsAffected >= 0 && nInteraction == CommandLineInteractive )
        printf( "%d rows affected\n", (int)nRowsAffected );

    if ( nRows && nInteraction == CommandLineInteractive )
        printf( "%d rows returned\n", (int)nRows );
}

void ODBCConsole::doDisplayErrors( ODBCHandle *pHandle )
{
    if ( !pHandle )
        return;

    ODBCDiagnostic  Diagnostic( pHandle );
    SQLINTEGER      nRecords = Diagnostic.getNumber();

    for ( SQLINTEGER nRecord = 1; nRecord <= nRecords; nRecord++ )
    {
        ODBCDiagnosticRecord Record( &Diagnostic, nRecord );
        SQLSMALLINT nBytes = SQL_MAX_MESSAGE_LENGTH * sizeof(ODBCCHAR);
        ODBCCHAR    szText[SQL_MAX_MESSAGE_LENGTH];
        ODBCFPrintF( stderr, (ODBCCPTR)TEXT("%s "), Record.getSqlstate( szText ) );
        ODBCFPrintF( stderr, (ODBCCPTR)TEXT("%s\n"), Record.getMessageText( szText, nBytes ) );
    }
}

vector<SQLUINTEGER> ODBCConsole::getColumnWidths( ODBCStatement *pStatement, SQLUINTEGER nUserWidth )
{
    vector<SQLUINTEGER> vectorColumnWidths;
    SQLUSMALLINT        nCol       = 0;
    SQLSMALLINT         nColumns   = 0;

    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        SQLUINTEGER nColumnWidth = getColumnWidth( pStatement, nUserWidth, nCol );
        vectorColumnWidths.push_back( nColumnWidth );
    }

    return vectorColumnWidths;
}

/*!
 * \brief   Get the optimal display width for a column.
 * 
 *          The display width is calculated using;
 * 
 *          \li SQL_DESC_DISPLAY_SIZE (not less than this - subject to following values)
 *          \li width of SQL_DESC_LABEL (not less than this - subject to following values)
 *          \li any User provided max (never exceeds this)
 *          \li MAX_DATA_WIDTH (never exceeds this)
 * 
 * \param pStatement 
 * \param nUserWidth 
 * \param nCol 
 * 
 * \return SQLUINTEGER 
 *
 * \author pharvey (8/22/2008)
 */
SQLUINTEGER ODBCConsole::getColumnWidth( ODBCStatement *pStatement, SQLUINTEGER nUserWidth, SQLUSMALLINT nCol )
{
    SQLLEN      nLabelWidth                     = 10;
    SQLLEN      nDataWidth                      = 10;
    SQLUINTEGER nOptimalDisplayWidth            = 10;
    ODBCCHAR    szColumnName[MAX_DATA_WIDTH+1];

    *szColumnName = '\0';

    pStatement->doColAttribute( nCol, SQL_DESC_DISPLAY_SIZE, NULL, 0, NULL, &nDataWidth );
    pStatement->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), NULL, NULL );
    nLabelWidth = ODBCStrLen( szColumnName );

    nOptimalDisplayWidth = max( nLabelWidth, nDataWidth );

    if ( nUserWidth > 0 )
        nOptimalDisplayWidth = min( nOptimalDisplayWidth, nUserWidth );

    if ( nOptimalDisplayWidth > MAX_DATA_WIDTH )
        nOptimalDisplayWidth = MAX_DATA_WIDTH;

    return nOptimalDisplayWidth;
}

ODBCEnvironment *ODBCConsole::getEnvironment()
{
    if ( !pEnvironment )
        pEnvironment = new ODBCEnvironment();
    return pEnvironment;
}

ODBCConnection *ODBCConsole::getConnection()
{
    if ( !pConnection )
        pConnection = new ODBCConnection( getEnvironment() );
    return pConnection;
}

ODBCStatement *ODBCConsole::getStatement()
{
    if ( !pStatement )
        pStatement = new ODBCStatement( getConnection() );
    return pStatement;
}


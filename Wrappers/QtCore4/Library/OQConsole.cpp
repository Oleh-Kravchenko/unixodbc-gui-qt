/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#include "OQConsole.h"
#include "OQDiagnostic.h"

#define MAX_LINE_IN_CHARS 4096
#define MAX_LINE_OUT_CHARS 32001

const char *szSyntax =
"\n" \
"**********************************************\n" \
"* OQConsole                                  *\n" \
"**********************************************\n" \
"* Syntax                                     *\n" \
"*                                            *\n" \
"*   OQConsole [options]                      *\n" \
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
"*      OQConsole supports redirection and  *\n" \
"*      piping for batch processing.          *\n" \
"*                                            *\n" \
"* Examples                                   *\n" \
"*                                            *\n" \
"*  OQConsole MyDSN MyID MyPWD -w < My.sql  *\n" \
"*                                            *\n" \
"* Please visit;                              *\n" \
"*                                            *\n" \
"*      http://www.unixodbc.org               *\n" \
"*      pharvey@peterharvey.org               *\n" \
"**********************************************\n\n";

const char *szIntro = 
"\n" \
"+---------------------------------------+\n" \
"|                                       |\n" \
"| Commands starts with a .              |\n" \
"|                                       |\n" \
"| Default command/statement terminator  |\n" \
"| is a ;                                |\n" \
"|                                       |\n" \
"| For example...                        |\n" \
"|                                       |\n" \
"| .help;                                |\n" \
"| .quit;                                |\n" \
"| SELECT COUNT(*) FROM MyTable;         |\n" \
"|                                       |\n" \
"+---------------------------------------+\n\n"; 

const char *szHelp =
"\n" \
".help sql;\n" \
".help show;\n" \
".help connect;\n" \
".help disconnect;\n" \
"\n\n";

const char *szHelpSql =
"\n" \
"SQL statements never start with a .\n\n" \
"The default terminator is a ;\n\n" \
"For example...\n\n" \
"SELECT COUNT(*) FROM MyTable;\n" \
"\n\n";

const char *szShow =
"\n" \
".show;\n" \
".show config;\n" \
".show driver [name];\n" \
".show dsn [name];\n" \
".show catalog [catalog];\n" \
".show schema [[catalog.]schema];\n" \
".show table [[[catalog.]schema.]table];\n" \
".show column [[[[catalog.]schema.]table.]column];\n" \
".show types;\n" \
"\n" \
"NOTE: use %% as a wildcard as needed\n" \
"\n\n";

const char *szHelpConnect =
"\n" \
".connect [DSN[UID[PWD]]];\n\n" \
"Connects to the data source (DSN).\n\n" \
"\n\n";

const char *szHelpDisconnect =
"\n" \
".disconnect;\n\n" \
"Disconnects from the data source.\n" \
"\n\n";


OQConsole::OQConsole( const QStringList &stringlistArguments, QTextStream *pstreamInCommands, QTextStream *pstreamOutData, QTextStream *pstreamOutErrors )
{
    this->pstreamInCommands     = pstreamInCommands;
    this->pstreamOutData        = pstreamOutData;
    this->pstreamOutErrors      = pstreamOutErrors;

    nInteraction            = InteractionUndefined; // try to figure it out based upon call order
    nResultFormat           = Boxed;
    bWideCharData           = false;
    bAsynch                 = false;
    bVerbose                = false;
    nUserWidth              = 0; // 0=not applicable
    cDelimiter              = '|';
    bColumnNames            = false;
    stringQuoteToUse        = "\"";
    cStatementTerminator    = ';';

    pSystem         = new OQSystem();
    pEnvironment    = new OQEnvironment( pSystem );
    pConnection     = new OQConnection( pEnvironment );
    pStatement      = new OQStatement( pConnection );

    connect( pSystem, SIGNAL(signalMessage(OQMessage)), SLOT(slotMessage(OQMessage)) );
    connect( pSystem, SIGNAL(signalDiagnostic(OQDiagnostic)), SLOT(slotDiagnostic(OQDiagnostic)) );

    doParseArgs( stringlistArguments );
}

OQConsole::~OQConsole()
{
    delete pStatement;
    delete pConnection;
    delete pEnvironment;
    delete pSystem;
}

bool OQConsole::exec()
{
    if ( nInteraction == CommandLineInteractive )
        return doProcessInteractive();

    return doProcessBatch();
}


/*!
    doParseArgs
    
*/    
bool OQConsole::doParseArgs( const QStringList &stringlistArguments )
{
    for ( int n = 0; n < stringlistArguments.size(); n++ )
    {
        QString stringArgument = stringlistArguments.at( n );

        if ( stringArgument == "-b" )
        {
            continue;
        }

        if ( stringArgument == "-e" )
        {
        }
    }

    return true;
}

bool OQConsole::doConnect( const QString &stringDSN, const QString &stringUID, const QString &stringPWD )
{
    if ( nInteraction == OQConsole::InteractionUndefined )
        nInteraction = ApplicationControlled;

    if ( !SQL_SUCCEEDED( pConnection->doConnect( stringDSN, stringUID, stringPWD ) ) )
    {
        *pstreamOutErrors << "[OQConsole]ERROR: Failed to connect\n";
        return false;
    }

    pStatement->setAttrMaxLength( nUserWidth );

    return true;
}

bool OQConsole::doDisconnect()
{
//    if ( pStatement->isAlloc( false ) )
//        pStatement->doFree();

    if ( !SQL_SUCCEEDED( pConnection->doDisconnect() ) )
    {
        *pstreamOutErrors << "[OQConsole]ERROR: Failed to properly disconnect\n";
        return false;
    }

    return true;
}

/*!
    doProcess
    
    This is the main loop for the application. It accepts and processes
    user input.
*/
bool OQConsole::doProcess()
{
    // Turning the ODBC asynch on may result in some feedback while long requests
    // are waited on. Mostly its just here to test asynch.
    if ( bAsynch )
    {
        if ( !SQL_SUCCEEDED( pStatement->setAttrAsyncEnable( OQStatement::AsyncEnableOn ) ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: Failed to turn asynch on\n";
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
bool OQConsole::doProcessBatch()
{
    QString     stringCommand;          // command in the making
    QString     stringLine;             // contains last line read
    QChar       cQuote          = 0;    // contains quote if we are in quote

    // display some help
    *pstreamOutData << szHelp;

    // 
    do 
    {
        stringLine = pstreamInCommands->readLine();

        // process line
        for ( int n = 0; n < stringLine.size(); n++ )
        {
            if ( stringLine[n] == cStatementTerminator && cQuote == 0 )
            {
                // we have a command
                if ( !stringCommand.isEmpty() )
                {
                    // process command
                    if ( !doProcessCommand( stringCommand ) )
                    {
                        // we have a quit command so quit both loops and exit function
                        stringLine = QString::null;
                        break; 
                    }

                    // cleanup
                    stringCommand == "";
                }
            }
            else
            {
                // toggle quote state as required
                // - we do not want to interpret a statement terminator when it is in quotes
                // - this is simplistic because it does not handle quotes which may be escaped in string
                if ( cQuote != 0 )
                {
                    if ( cQuote == stringLine[n] )
                        cQuote = 0;
                }
                else
                {
                    if ( stringLine[n] == '\'' || stringLine[n] == '\"' )
                        cQuote = stringLine[n];
                }

                // accum
                stringCommand.append( stringLine[n] );
            }
        }

    } while ( !stringLine.isNull() );

    return 1;
}

/*!
    doProcessInteractive
    
    Main loop.
*/
bool OQConsole::doProcessInteractive()
{
    QString     stringCommand;          // command in the making
    QString     stringLine;             // contains last line read
    QChar       cQuote          = 0;    // contains quote if we are in quote

    // display some help
    *pstreamOutData << szHelp;

    // 
    do 
    {
        if ( cQuote != 0 )
            *pstreamOutData << "OQConsole (text currently in quotes)> ";
        else
            *pstreamOutData << "OQConsole> ";

        stringLine = pstreamInCommands->readLine();

        // process line
        for ( int n = 0; n < stringLine.size(); n++ )
        {
            if ( stringLine[n] == cStatementTerminator && cQuote == 0 )
            {
                // we have a command
                if ( !stringCommand.isEmpty() )
                {
                    // process command
                    if ( !doProcessCommand( stringCommand ) )
                    {
                        // we have a quit command so quit both loops and exit function
                        stringLine = QString::null;
                        break; 
                    }

                    // cleanup
                    stringCommand == "";
                }
            }
            else
            {
                // toggle quote state as required
                // - we do not want to interpret a statement terminator when it is in quotes
                // - this is simplistic because it does not handle quotes which may be escaped in string
                if ( cQuote != 0 )
                {
                    if ( cQuote == stringLine[n] )
                        cQuote = 0;
                }
                else
                {
                    if ( stringLine[n] == '\'' || stringLine[n] == '\"' )
                        cQuote = stringLine[n];
                }

                // accum
                stringCommand.append( stringLine[n] );
            }
        }

    } while ( !stringLine.isNull() );

    return 1;
}

/*!
    doProcessCommand

    Return false to exit main loop and app.    
*/
bool OQConsole::doProcessCommand( const QString &stringCommand )
{
    QString stringCommandTrimmed = stringCommand.trimmed();

    //
    if ( stringCommandTrimmed.isEmpty() )
        return 1;

    //
    if ( stringCommandTrimmed.left( 4 ) == "quit" )
        return 0;
    else if ( stringCommandTrimmed.left( 5 ) == "show " )            // process the given 'show' command
        doExecuteShow( stringCommandTrimmed.mid( 6 ) );
    else if ( stringCommandTrimmed.left( 4 ) == "show" )             // display the 'show' commands
        doExecuteShow();
    else if ( stringCommandTrimmed.left( 4 ) == "help" )             // display some help
    {
        *pstreamOutData << szHelp;
        *pstreamOutData << "OQConsole> ";
    }
    else
        doExecuteSQL( stringCommandTrimmed );                         // process the given 'SQL' statement

    return 1;
}

/*!
    doExecuteSQL
    
    Prepare and execute SQL then process any results.
*/
bool OQConsole::doExecuteSQL( const QString &stringSQL )
{
    QString     stringSepLine;
    SQLSMALLINT nCols   = -1;
    SQLLEN      nRows   = 0;

    if ( !SQL_SUCCEEDED( pStatement->doPrepare( stringSQL ) ) )
    {
//        pStatement->doFree();
        *pstreamOutErrors << "[OQConsole]ERROR: While preparing statement\n";
        return false;
    }

    if ( !SQL_SUCCEEDED( pStatement->doExecute() ) )
    {
//        pStatement->doFree();
        *pstreamOutErrors << "[OQConsole]ERROR: While executing statement\n";
        return false;
    }

    /*
     * check to see if it has generated a result set
     */
    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nCols ) ) )
    {
//        pStatement->doFree();
        *pstreamOutErrors << "[OQConsole]ERROR: While requesting number of columns\n";
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
                stringSepLine = doWriteHeaderNormal();
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
            doWriteFooterNormal( stringSepLine, nRows );
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
    pStatement->doCloseCursor();

    return true;
}

/*!
    doExecuteShow
    
    Process "show" commands.
*/
bool OQConsole::doExecuteShow( const QString &stringShow )
{
    if ( !stringShow.isEmpty() )
    {
        *pstreamOutData << szShow;
        return true;
    }

    // show config
    ODBCSystem OdbcSystem;
    if ( stringShow.left( 6 ) == "config" )
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
    // driver details?
    else if ( stringShow.left( 7 ) == "driver " )
    {
        QMap<QString,QString> mapAttributes = pSystem->getDriverAttributes( stringShow.mid( 8 ) );

        const char *pszTitle0 = "Key";
        const char *pszTitle1 = "Value";
        SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, 22 ) : 22 );
        SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, 77 ) : 77 );

        *pstreamOutData << stringShow.mid( 7 );
        
        // header    
        *pstreamOutData <<  '+' << qSetFieldWidth( nWidth0 ) <<  qSetPadChar( '-' ) <<  '-' << qSetFieldWidth( 1 ) <<  '+' << qSetFieldWidth( nWidth1 ) <<  '-' << qSetFieldWidth( 1 ) <<  '+';
        *pstreamOutData <<  '|' << qSetFieldWidth( nWidth0 ) <<  qSetPadChar( ' ' ) <<  pszTitle0 << qSetFieldWidth( 1 ) <<  '+' << qSetFieldWidth( nWidth1 ) << '|' <<  pszTitle1 << qSetFieldWidth( 1 ) <<  '+';
        *pstreamOutData <<  '+' << qSetFieldWidth( nWidth0 ) <<  qSetPadChar( '-' ) <<  '-' << qSetFieldWidth( 1 ) <<  '+' << qSetFieldWidth( nWidth1 ) <<  '-' << qSetFieldWidth( 1 ) <<  '+';
        // data
        QMap<QString, QString>::const_iterator i = mapAttributes.constBegin();
        while ( i != map.constEnd() ) 
        {
            ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, i.key(), nWidth1, nWidth1, i.value() );
            ++i;
        }
        // footer
        *pstreamOutData <<  '+' << qSetFieldWidth( nWidth0 ) <<  qSetPadChar( '-' ) <<  '-' << qSetFieldWidth( 1 ) <<  '+' << qSetFieldWidth( nWidth1 ) <<  '-' << qSetFieldWidth( 1 ) <<  '+';
        return true;
    }
    // show driver
    else if ( stringShow.left( 6 ) == "driver" )
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
            const QString &stringDescription = OdbcSystem.getValue( (*i).vectorProperties, (SQLTCHAR*)TEXT("description") );
            if ( pszDescription )
                ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, pszDescription );
            else
                ODBCPrintF( (ODBCCPTR)TEXT("| %-*.*s | %-*.*s |\n"), nWidth0, nWidth0, (*i).szName, nWidth1, nWidth1, TEXT("") );
        }

        printf( "+-%-*.*s-+-%-*.*s-+\n", nWidth0, nWidth0, pszSep0, nWidth1, nWidth1, pszSep1 );

        return true;
    }
    // show dsn
    else if ( ODBCStrNCmp( pszShow, TEXT("dsn"), 3 ) == 0 )
    {
        // dsn details?
        if ( ODBCStrNCmp( pszShow, TEXT("dsn "), 4 ) == 0 )
        {
            ODBCDataSourceName DataSourceName = OdbcSystem.getDataSourceName( (SQLTCHAR*)&pszShow[4] );
            vector<ODBCKeyValue>::iterator i;
            const char *pszSep0   = "----------------------";
            const char *pszSep1   = "------------------------------------------------------------------------------------------------------";
            const char *pszTitle0 = "Key";
            const char *pszTitle1 = "Value";
            SQLUINTEGER nWidth0 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep0 ) ) : strlen( pszSep0 ) );
            SQLUINTEGER nWidth1 = ( nUserWidth > 0 ? min( nUserWidth, strlen( pszSep1 ) ) : strlen( pszSep1 ) );

            ODBCPrintF( (ODBCCPTR)TEXT("%s\n"), (SQLTCHAR*)&pszShow[4] );
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
                const QString &stringDescription = OdbcSystem.getValue( (*i).vectorProperties, (SQLTCHAR*)TEXT("description") );
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
            SQLTCHAR    szDSN[21];
            SQLSMALLINT nNameLength1;
            SQLTCHAR    szDescription[101];
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
                fprintf( stderr, "[OQConsole]ERROR: While getting data source listing\n" );
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
            nReturn = pStatement->doTables( (SQLTCHAR*)&pszShow[8] );
        else
            nReturn = pStatement->doTables( (SQLTCHAR*)TEXT(SQL_ALL_CATALOGS) );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: Failed to get catalogs\n";
            return false;
        }
    }
    // show schema
    else if ( ODBCStrNCmp( pszShow, TEXT("schema"), 6 ) == 0 )
    {
        SQLRETURN nReturn;

        if ( pszShow[6] == ' ' )
            nReturn = pStatement->doTables( NULL, 0, (SQLTCHAR*)&pszShow[7], SQL_NTS );
        else
            nReturn = pStatement->doTables( NULL, 0, (SQLTCHAR*)TEXT(SQL_ALL_SCHEMAS), SQL_NTS );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: Failed to get schemas\n";
            return false;
        }
    }
    // show table
    else if ( ODBCStrNCmp( pszShow, TEXT("table"), 5 ) == 0 )
    {
        SQLRETURN nReturn;

        if ( pszShow[5] == ' ' )
        {
            nReturn = pStatement->doColumns( NULL, 0, NULL, 0, (SQLTCHAR*)&pszShow[6], SQL_NTS, NULL, 0 );
        }
        else
        {
            nReturn = pStatement->doTables( NULL, 0, NULL, 0, NULL, 0, (SQLTCHAR*)TEXT("TABLE"), SQL_NTS );
        }

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: Failed to get tables\n";
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
        if ( !SQL_SUCCEEDED( pStatement->doColumns( NULL, SQL_NTS, NULL, SQL_NTS, (SQLTCHAR*)pszShow, SQL_NTS, TEXT("%"), SQL_NTS ) ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: While requesting column listing\n";
            return false;
        }
    }
    // show types
    else if ( ODBCStrNCmp( pszShow, TEXT("types"), 5 ) == 0 )
    {
        if ( !SQL_SUCCEEDED( pStatement->doTypeInfo() ) )
        {
            *pstreamOutErrors << "[OQConsole]ERROR: Failed to get type info\n";
            return false;
        }
    }

    /****************************
     * WRITE HEADER
     ***************************/
    SQLTCHAR szSepLine[MAX_LINE_OUT_CHARS + 1];
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
    pStatement->doCloseCursor();

    return true;
}

/****************************
 * WRITE HTML
 ***************************/
void OQConsole::doWriteHeaderHTMLTable()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLTCHAR        szColumnName[MAX_DATA_WIDTH+1];

    *szColumnName = '\0';

    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    printf( "<div id=ResultSet>\n" );
    printf( "<table border>\n" );

    printf( "\t<thead>\n" );
    printf( "\t\t<tr>\n" );

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        pStatement->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, MAX_DATA_WIDTH, NULL, NULL );
        printf( "\t\t\t<th scope=\"col\">" );
        ODBCPrintF( (ODBCCPTR)TEXT("%s"), szColumnName );
        printf( "</th>\n" );
    }
    printf( "\t\t</tr>\n" );
    printf( "\t</thead>\n" );

    printf( "\t<tbody>\n" );
}

SQLLEN OQConsole::doWriteBodyHTMLTable()
{
    SQLUSMALLINT    nCol        = 0;
    SQLSMALLINT     nColumns    = 0;
    SQLRETURN       nReturn     = 0;
    SQLLEN          nRows       = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    pStatement->doNumResultCols( &nColumns );

    /* ROWS */
    while ( SQL_SUCCEEDED( pStatement->doFetch() ) )
    {
        nRows++;
        printf( "\t\t<tr>\n" );
        printf( "\t\t\t<th scope=\"row\" id=\"%d\"></th>\n", nRows );
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            printf( "\t\t\t<td>" );
            nReturn = pStatement->doData( nCol, &v );
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

    return nRows;
}

void OQConsole::doWriteFooterHTMLTable( SQLLEN nRows )
{
    SQLSMALLINT nColumns      = 1;
    SQLLEN      nRowsAffected = -1;

    pStatement->doNumResultCols( &nColumns );
    pStatement->doRowCount( &nRowsAffected );

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
void OQConsole::doWriteBodyInsertTable()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLRETURN       nReturn                         = 0;
    bool *          pbQuote                         = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    pStatement->doNumResultCols( &nColumns );

    if ( nColumns <= 0 )
        return;

    pbQuote = (bool*)calloc( sizeof(bool), nColumns );

    // parse stringColumnsToQuote
    if ( stringColumnsToQuote )
    {
        int         nCursorColumnsToQuote   = 0;
        int         nCursorColumn           = 0;
        SQLTCHAR    szColumn[100];

        while ( 1 )
        {
            if ( stringColumnsToQuote[nCursorColumnsToQuote] == ',' || stringColumnsToQuote[nCursorColumnsToQuote] == '\0' )
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
                szColumn[nCursorColumn] = stringColumnsToQuote[nCursorColumnsToQuote];
                nCursorColumn++;
            }

            if ( stringColumnsToQuote[nCursorColumnsToQuote] == '\0' )
                break;

            nCursorColumnsToQuote++;
        }
    }

    // process results
    while ( SQL_SUCCEEDED( pStatement->doFetch() ) ) /* ROWS */
    {
        ODBCPrintF( (ODBCCPTR)TEXT("INSERT INTO %s VALUES ( "), stringInsertTable );
        for ( nCol = 1; nCol <= nColumns; nCol++ ) /* COLS */
        {
            if ( nCol > 1 )
                printf( ", " );

            nReturn = pStatement->doData( nCol, &v );
            if ( v.isNull() )
                printf( "NULL" );
            else
            {
                // TODO: Escape any quote char embedded in char data
                ODBCPrintF( (ODBCCPTR)TEXT("%s"), ( pbQuote[nCol - 1] ? stringQuoteToUse : TEXT("") ) ); 
                if ( bWideCharData )
                    wprintf( L"%s", (SQLWCHAR*)v.getBuffer() );
                else
                    printf( (const char *)v.getBuffer() );
                ODBCPrintF( (ODBCCPTR)TEXT("%s"), ( pbQuote[nCol - 1] ? stringQuoteToUse : TEXT("") ) ); 
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
void OQConsole::doWriteHeaderDelimited()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLTCHAR        szColumnName[MAX_DATA_WIDTH+1];

    *szColumnName = '\0';

    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        pStatement->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), NULL, NULL );
        ODBCFPutS( szColumnName, stdout );
        if ( nCol < nColumns )
            ODBCPutChar( cDelimiter );
    }
    ODBCPutChar( '\n' );
}

void OQConsole::doWriteBodyDelimited()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLRETURN       nReturn                         = 0;

    ODBCVariant v( ( bWideCharData ? ODBCVariant::WideChar : ODBCVariant::Char ) );
    v.setElementsMax( MAX_DATA_WIDTH );

    pStatement->doNumResultCols( &nColumns );

    /* ROWS */
    while ( SQL_SUCCEEDED( pStatement->doFetch() ) )
    {
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            nReturn = pStatement->doData( nCol, &v );
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

}

/****************************
 * WRITE NORMAL
 ***************************/
QString OQConsole::doWriteHeaderNormal()
{
    SQLUSMALLINT    nCol                            = 0;
    SQLSMALLINT     nColumns                        = 0;
    SQLTCHAR        szColumn[MAX_DATA_WIDTH+20];
    SQLTCHAR        szColumnName[MAX_DATA_WIDTH+1];
    SQLTCHAR        szHdrLine[MAX_LINE_OUT_CHARS + 1];
    SQLUINTEGER     nSepLine                        = 0;    // index to next char

    *szColumn       = '\0';
    *szColumnName   = '\0';
    *szHdrLine      = '\0';

    vectorColumnWidths = getColumnWidths( pStatement, nUserWidth );

    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nColumns ) ) )
        nColumns = -1;

    for ( nCol = 1; nCol <= nColumns; nCol++ )
    {
        SQLUINTEGER nColumnWidth = vectorColumnWidths.at( nCol - 1 );
        pStatement->doColAttribute( nCol, SQL_DESC_LABEL, szColumnName, sizeof(szColumnName), NULL, NULL );

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

SQLLEN OQConsole::doWriteBodyNormal()
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

    pStatement->doNumResultCols( &nColumns );
    
    /* ROWS */
    while ( SQL_SUCCEEDED( pStatement->doFetch() ) )
    {
        /* COLS */
        for ( nCol = 1; nCol <= nColumns; nCol++ )
        {
            SQLUINTEGER nColumnWidth = vectorColumnWidths.at( nCol - 1 );

            // get the data
            nReturn = pStatement->doData( nCol, &v );
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

    return nRows;
}

void OQConsole::doWriteFooterNormal( SQLTCHAR *szSepLine, SQLLEN nRows )
{
    SQLLEN nRowsAffected = -1;

    ODBCPrintF( (ODBCCPTR)szSepLine );

    pStatement->doRowCount( &nRowsAffected );
    if ( nRowsAffected >= 0 && nInteraction == CommandLineInteractive )
        printf( "%d rows affected\n", (int)nRowsAffected );

    if ( nRows && nInteraction == CommandLineInteractive )
        printf( "%d rows returned\n", (int)nRows );
}

vector<SQLUINTEGER> OQConsole::getColumnWidths( OQStatement *pStatement, SQLUINTEGER nUserWidth )
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
SQLUINTEGER OQConsole::getColumnWidth( OQStatement *pStatement, SQLUINTEGER nUserWidth, SQLUSMALLINT nCol )
{
    SQLLEN      nLabelWidth                     = 10;
    SQLLEN      nDataWidth                      = 10;
    SQLUINTEGER nOptimalDisplayWidth            = 10;
    SQLTCHAR    szColumnName[MAX_DATA_WIDTH+1];

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

void OQConsole::slotMessage( OQMessage Message )
{
    pstreamOutErrors < Message.getText();
}

void OQConsole::slotDiagnostic( OQDiagnostic Diagnostic )
{
    SQLINTEGER nRecords = Diagnostic.getNumber();

    for ( SQLINTEGER nRecord = 1; nRecord <= nRecords; nRecord++ )
    {
        ODBCDiagnosticRecord Record = Diagnostic.getRecord( nRecord );
        pstreamOutErrors < Record.getMessageText();
    }
}



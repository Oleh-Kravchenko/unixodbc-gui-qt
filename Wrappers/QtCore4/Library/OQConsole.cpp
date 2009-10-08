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


OQConsole::OQConsole( const QStringList &stringlistArguments )
{
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

    doProcessResultSet();

    return true;
}

/*!
    doExecuteShow
    
    Process "show" commands.
*/
bool OQConsole::doExecuteShow( const QString &stringShow )
{
    QTextStream streamOut( stdout );
    QTextStream streamErr( stderr );

    if ( !stringShow.isEmpty() )
    {
        streamOut << szShow;
        return true;
    }

    // config
    if ( stringShow.left( 6 ) == "config" )
    {
        return doExecuteShowConfig();
    }
    // driver details
    else if ( stringShow.left( 7 ) == "driver " )
    {
        return doExecuteShowDriver( stringShow.mid( 8 ) );
    }
    // driver list
    else if ( stringShow.left( 6 ) == "driver" )
    {
        return doExecuteShowDrivers();
    }
    // show dsn
    else if ( stringShow.left( 4 ) ==  "dsn " )
    {
        return doExecuteShowDataSourceName( stringShow.mid( 5 ) );
    }
    else if ( stringShow.left( 3 ) ==  "dsn" )
    {
        return doExecuteShowDataSourceNames();
    }
    // show catalog
    else if ( stringShow.left( 7 ) == "catalog" )
    {
        SQLRETURN nReturn;

        if ( stringShow.at( 7 ) == ' ' )
            nReturn = pStatement->doTables( stringShow.mid( 8 ) );
        else
            nReturn = pStatement->doTables( SQL_ALL_CATALOGS );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            streamErr << "[OQConsole]ERROR: Failed to get catalogs\n";
            return false;
        }
    }
    // show schema
    else if ( stringShow.left( 6 ) == "schema" )
    {
        SQLRETURN nReturn;

        if ( stringShow.at( 6 ) == ' ' )
            nReturn = pStatement->doTables( QString::null, stringShow.mid( 7 ) );
        else
            nReturn = pStatement->doTables( QString::null, SQL_ALL_SCHEMAS );

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            streamErr << "[OQConsole]ERROR: Failed to get schemas\n";
            return false;
        }
    }
    // show table
    else if ( stringShow.left( 5 ) == "table" )
    {
        SQLRETURN nReturn;

        if ( stringShow.at( 5 ) == ' ' )
        {
            nReturn = pStatement->doColumns( QString::null, QString::null, stringShow.mid( 6 ), QString::null );
        }
        else
        {
            nReturn = pStatement->doTables( QString::null, QString::null, QString::null, "TABLE" );
        }

        if ( !SQL_SUCCEEDED( nReturn ) )
        {
            streamErr << "[OQConsole]ERROR: Failed to get tables\n";
            return false;
        }
    }
    // show column
    else if ( stringShow.left( 6 ) == "column" )
    {
        /*! 
         * \note    1. MS Access needs Catalog = NULL. Catalog = "" does not work.
         *  
         */
        if ( !SQL_SUCCEEDED( pStatement->doColumns( QString::null, QString::null, stringShow.mid( 7 ), "%" ) ) )
        {
            streamErr << "[OQConsole]ERROR: While requesting column listing\n";
            return false;
        }
    }
    // show types
    else if ( stringShow.left( 5 ) == "types" )
    {
        if ( !SQL_SUCCEEDED( pStatement->doTypeInfo() ) )
        {
            streamErr << "[OQConsole]ERROR: Failed to get type info\n";
            return false;
        }
    }

    doProcessResultSet();

    return true;
}

bool OQConsole::doExecuteShowConfig()
{
    QTextStream  streamOut( stdout );
    OQAttributes Attributes = pSystem->getAttributes();

    // get col widths
    int nKeyMaxChars    = 5;
    int nValueMaxChars  = 7;
    {
        QMapIterator<QString, QString> i( Attributes.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            nKeyMaxChars    = max( i.key().length(), nKeyMaxChars );
            nValueMaxChars  = max( i.value().length(), nValueMaxChars );
        }
    }

    // header
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;
    streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << "Key" << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << "Value" << qSetFieldWidth( 1 ) << "|" << endl;
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;

    // body
    {
        QMapIterator<QString, QString> i( Attributes.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << i.key() << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << i.value() << qSetFieldWidth( 1 ) << "|" << endl;
        }
    }

    // footer
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << endl;

    return true;
}

bool OQConsole::doExecuteShowDriver( const QString &stringDriver )
{
    QTextStream streamOut( stdout );
    OQDriver    Driver = pSystem->getDriver( stringDriver );

    // get col widths
    int nKeyMaxChars    = 5;
    int nValueMaxChars  = 7;
    {
        QMapIterator<QString, QString> i( Driver.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            nKeyMaxChars    = max( i.key().length(), nKeyMaxChars );
            nValueMaxChars  = max( i.value().length(), nValueMaxChars );
        }
    }

    // header
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;
    streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << "Key" << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << "Value" << qSetFieldWidth( 1 ) << "|" << endl;
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;

    // body
    {
        QMapIterator<QString, QString> i( Driver.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << i.key() << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << i.value() << qSetFieldWidth( 1 ) << "|" << endl;
        }
    }

    // footer
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << endl;

    return true;
}

bool OQConsole::doExecuteShowDrivers()
{
    QTextStream         streamOut( stdout );
    QVector<OQDriver>   vectorDrivers = pSystem->getDrivers();

    // get col widths
    int nNameMaxChars        = 6;
    int nDescriptionMaxChars = 13;
    for ( int n = 0; n < vectorDrivers.count(); n++ )
    {
        nNameMaxChars        = max( vectorDrivers[n].stringName.length(), nNameMaxChars );
        nDescriptionMaxChars = max( vectorDrivers[n].mapAttributes["DESCRIPTION"].length(), nDescriptionMaxChars );
    }

    // header
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << ""     << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << ""            << qSetFieldWidth( 1 ) << "+" << endl;
    streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nNameMaxChars ) << "Name" << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nDescriptionMaxChars ) << "Description" << qSetFieldWidth( 1 ) << "|" << endl;
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << ""     << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << ""            << qSetFieldWidth( 1 ) << "+" << endl;

    // body
    for ( int n = 0; n < vectorDrivers.count(); n++ )
    {
        streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nNameMaxChars ) << vectorDrivers[n].stringName << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nDescriptionMaxChars ) << vectorDrivers[n].mapAttributes["DESCRIPTION"] << qSetFieldWidth( 1 ) << "|" << endl;
    }

    // footer
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << endl;

    return true;
}

bool OQConsole::doExecuteShowDataSourceName( const QString &stringDataSourceName )
{
    QTextStream      streamOut( stdout );
    OQDataSourceName DataSourceName = pSystem->getDataSource( stringDataSourceName );

    // get col widths
    int nKeyMaxChars    = 5;
    int nValueMaxChars  = 7;
    {
        QMapIterator<QString, QString> i( DataSourceName.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            nKeyMaxChars    = max( i.key().length(), nKeyMaxChars );
            nValueMaxChars  = max( i.value().length(), nValueMaxChars );
        }
    }

    // header
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;
    streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << "Key" << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << "Value" << qSetFieldWidth( 1 ) << "|" << endl;
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << ""    << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << ""      << qSetFieldWidth( 1 ) << "+" << endl;

    // body
    {
        QMapIterator<QString, QString> i( DataSourceName.mapAttributes );
        while ( i.hasNext() ) 
        {
            i.next();
            streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nKeyMaxChars ) << i.key() << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nValueMaxChars ) << i.value() << qSetFieldWidth( 1 ) << "|" << endl;
        }
    }

    // footer
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nKeyMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nValueMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << endl;

    return true;
}

bool OQConsole::doExecuteShowDataSourceNames()
{
    QTextStream               streamOut( stdout );
    QVector<OQDataSourceName> vectorDataSourceNames = pSystem->getDataSources();

    // get col widths
    int nNameMaxChars        = 6;
    int nDescriptionMaxChars = 13;
    for ( int n = 0; n < vectorDataSourceNames.count(); n++ )
    {
        nNameMaxChars        = max( vectorDataSourceNames[n].stringName.length(), nNameMaxChars );
        nDescriptionMaxChars = max( vectorDataSourceNames[n].mapAttributes["DESCRIPTION"].length(), nDescriptionMaxChars );
    }

    // header
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << ""     << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << ""            << qSetFieldWidth( 1 ) << "+" << endl;
    streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nNameMaxChars ) << "Name" << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nDescriptionMaxChars ) << "Description" << qSetFieldWidth( 1 ) << "|" << endl;
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << ""     << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << ""            << qSetFieldWidth( 1 ) << "+" << endl;

    // body
    for ( int n = 0; n < vectorDataSourceNames.count(); n++ )
    {
        streamOut << qSetPadChar( ' ' ) << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nNameMaxChars ) << vectorDataSourceNames[n].stringName << qSetFieldWidth( 1 ) << "|" << qSetFieldWidth( nDescriptionMaxChars ) << vectorDataSourceNames[n].mapAttributes["DESCRIPTION"] << qSetFieldWidth( 1 ) << "|" << endl;
    }

    // footer
    streamOut << qSetPadChar( '-' ) << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nNameMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << qSetFieldWidth( nDescriptionMaxChars ) << "" << qSetFieldWidth( 1 ) << "+" << endl;

    return true;
}

void OQConsole::doProcessResultSet()
{
    QTextStream streamErr( stderr );

    QString     stringSepLine;
    SQLSMALLINT nCols   = -1;
    SQLLEN      nRows   = 0;

    /*
     * check to see if it has generated a result set
     */
    if ( !SQL_SUCCEEDED( pStatement->doNumResultCols( &nCols ) ) )
    {
//        pStatement->doFree();
        streamErr << "[OQConsole]ERROR: While requesting number of columns\n";
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
    if ( !pStatement )
    {
    }

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

    return stringSepLine;
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

void OQConsole::doWriteFooterNormal( const QString &stringSepLine, SQLLEN nRows )
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
    QTextStream streamErr( stderr );
    streamErr << Message.getText();
}

void OQConsole::slotDiagnostic( OQDiagnostic Diagnostic )
{
    QTextStream streamErr( stderr );
    SQLINTEGER nRecords = Diagnostic.getNumber();

    for ( SQLINTEGER nRecord = 1; nRecord <= nRecords; nRecord++ )
    {
        OQDiagnosticRecord Record = Diagnostic.getRecord( nRecord );
        streamErr << Record.getMessageText();
    }
}



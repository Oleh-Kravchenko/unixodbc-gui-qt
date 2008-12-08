/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCCONSOLE_H
#define ODBCCONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

//
#include <ODBCSystem.h>
#include <ODBCEnvironment.h>
#include <ODBCConnection.h>
#include <ODBCStatement.h>

#define MAX_DATA_WIDTH 300

#ifndef max
#define max( a, b ) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min( a, b ) (((a) < (b)) ? (a) : (b))
#endif

#ifndef V_MAJOUR
    #define V_MAJOUR 1
    #define V_MINOR 0
    #define V_RELEASE 1
#endif

/*!
 * \class   ODBCConsole 
 * \brief   This class provides a high-level interface to the ODBC system.
 *
 *          The core feature of this class is its ability to submit a request to the data source and
 *          produce a ResultSet in a number of formats. It provides the functionality of iterating over
 *          the ResultSet and translating the data into the desired format. This class also supplies
 *          functionality to (optionaly) process command-line arguments, interact with the User at the
 *          command-line and process batch commands.
 *
 *          This is used as the basis for the ODBCConsole command-line utility. In such a case a minimal
 *          amount of code creates a useful program;
 *  
\code 
int main( int argc, char *argv[] )
{
    ODBCConsole Console;

    Console.doParseArgs( argc, (ODBCCHAR**)argv );
    Console.doProcess();

    return 0;
}
\endcode 
 *
 *          Alternatively a program may want to assert more control...
 *
\code 
int main( int argc, char *argv[] )
{
    ODBCConsole Console;
 
    Console.setResultFormat( ODBCConsole::Html );
    Console.doConnect( "Northwind" );
    Console.doProcessCommand( "SELECT SupplierID, Address FROM Suppliers" );
    Console.doDisconnect();
 
    return 0;
}
\endcode 
 *
 *          At some point in the future the application will be able to set where the
 *          output goes (in-memory buffer, file, etc). Also; more format types for output
 *          will be added (xml with binary, binary, html with binary, etc).
 *
 * \author  pharvey (8/22/2008)
 */
class ODBCConsole 
{
public:
    enum Interaction
    {
        InteractionUndefined,
        CommandLineInteractive,
        CommandLineBatch,
        ApplicationControlled
    };

    enum ResultFormats
    {
        Boxed,
        Html,
        Delimited,
        Insert
    };

    explicit ODBCConsole();
    virtual ~ODBCConsole();

    // options
    virtual void setResultFormat( ResultFormats n ) { nResultFormat = n; }
    virtual void setInteraction( Interaction n ) { nInteraction = n; }
    virtual void setWideCharData( bool b ) { bWideCharData = b; }
    virtual void setAsynch( bool b ) { bAsynch = b; }
    virtual void setVerbose( bool b ) { bVerbose = b; }
    virtual void setUserWidth( SQLUINTEGER n );
    virtual void setDelimiter( ODBCCHAR c ) { cDelimiter = c; }
    virtual void setColumnNames( bool b ) { bColumnNames = b; }
    virtual void setInsertTable( const ODBCCHAR *pszInsertTable );
    virtual void setColumnToQuote( const ODBCCHAR *pszColumnsToQuote );
    virtual void setQuoteToUse( const ODBCCHAR *pszQuoteToUse );
    virtual void setStatementTerminator( ODBCCHAR c ) { cStatementTerminator = c; }

    //
    virtual bool doParseArgs( int argc, ODBCCHAR *argv[] );
    virtual bool doConnect( const ODBCCHAR *pszDSN, const ODBCCHAR *pszUID, const ODBCCHAR *pszPWD );
    virtual bool doDisconnect();
    virtual bool doProcess();
    virtual bool doProcessCommand( ODBCCHAR *pszCommand );

    //
    virtual bool isConnected() { if ( !pConnection ) return false; if ( !pConnection->isConnected() ) return false; return true; }

protected:
    // options
    Interaction         nInteraction;
    ResultFormats       nResultFormat;
    bool                bWideCharData;
    bool                bAsynch;
    bool                bVerbose;
    SQLUINTEGER         nUserWidth;
    ODBCCHAR            cDelimiter;
    bool                bColumnNames;
    ODBCCHAR *          pszInsertTable;
    ODBCCHAR *          pszColumnsToQuote;
    ODBCCHAR *          pszQuoteToUse;
    ODBCCHAR            cStatementTerminator;

    // use getEnvironment(), getConnection() and getStatement() instead of these
    ODBCEnvironment *   pEnvironment;
    ODBCConnection *    pConnection;
    ODBCStatement *     pStatement;

    // process incoming commands 
    virtual bool doProcessBatch();
    virtual bool doProcessInteractive();
    virtual bool doExecuteSQL( const ODBCCHAR *pszCommand );
    virtual bool doExecuteShow( const ODBCCHAR *pszShow = NULL );

    // produce output
    // boxed with ascii art
    virtual void doWriteHeaderNormal( ODBCCHAR *szSepLine );
    virtual SQLLEN doWriteBodyNormal();
    virtual void doWriteFooterNormal( ODBCCHAR *szSepLine, SQLLEN nRows );
    // boxed with html table
    virtual void doWriteHeaderHTMLTable();
    virtual SQLLEN doWriteBodyHTMLTable();
    virtual void doWriteFooterHTMLTable( SQLLEN nRows );
    // columns delimited (may contain column names in first row) 
    virtual void doWriteHeaderDelimited();
    virtual void doWriteBodyDelimited();
    // each result row is wrapped in an INSERT SQL statement
    virtual void doWriteBodyInsertTable();

    //
    virtual void doDisplayErrors( ODBCHandle *pHandle );

    // resultset processing helper stuff
    vector<SQLUINTEGER> vectorColumnWidths;

    virtual vector<SQLUINTEGER> getColumnWidths( ODBCStatement *pStatement, SQLUINTEGER nUserWidth );
    virtual SQLUINTEGER getColumnWidth( ODBCStatement *pStatement, SQLUINTEGER nUserWidth, SQLUSMALLINT nCol );

    virtual ODBCEnvironment *   getEnvironment();
    virtual ODBCConnection *    getConnection();
    virtual ODBCStatement *     getStatement();
};

#endif


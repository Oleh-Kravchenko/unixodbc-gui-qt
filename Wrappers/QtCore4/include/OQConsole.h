/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2003
 * \license Copyright unixODBC-GUI-Qt Project 2003-2012, See LGPL.txt
 */
#pragma once

//
#include <OQSystem.h>
#include <OQEnvironment.h>
#include <OQConnection.h>
#include <OQStatement.h>

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
 * \class   OQConsole 
 * \brief   This class provides a high-level interface to the ODBC system.
 *
 *          The core feature of this class is its ability to submit a request to the data source and
 *          produce a ResultSet in a number of formats. It provides the functionality of iterating over
 *          the ResultSet and translating the data into the desired format. This class also supplies
 *          functionality to (optionaly) process command-line arguments, interact with the User at the
 *          command-line and process batch commands.
 *
 *          This is used as the basis for the OQConsole command-line utility. In such a case a minimal
 *          amount of code creates a useful program;
 *  
\code 
int main( int argc, char *argv[] )
{ 
    QCoreApplication    theApplication( argc, argv ); 
    QTextStream         streamIn( stdin ); 
    QTextStream         streamOutData( stdout );
    QTextStream         streamOutErrors( stderr ); 
    OQConsole           theConsole( theApplication.arguments(), &streamIn, &streamOutData, &streamOutErrors );

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
class OQConsole : public QObject
{
    Q_OBJECT
public:
    explicit OQConsole( const QStringList &stringlistArguments );
    virtual ~OQConsole();

    virtual bool exec();

protected:
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

    // we pick these up from our app args
    Interaction     nInteraction;
    ResultFormats   nResultFormat;
    bool            bWideCharData;
    bool            bAsynch;
    bool            bVerbose;
    int             nUserWidth;
    QChar           cDelimiter;
    bool            bColumnNames;
    QString         stringInsertTable;
    QString         stringColumnsToQuote;
    QString         stringQuoteToUse;
    QChar           cStatementTerminator;

    // I/O - do not set the streams - just where they point to
//    QTextStream *   pstreamInCommands;
//    QTextStream *   pstreamOutData;
//    QTextStream *   pstreamOutErrors;

    // handles
    OQSystem *          pSystem;
    OQEnvironment *     pEnvironment;
    OQConnection *      pConnection;
    OQStatement *       pStatement;

    //
    virtual bool doParseArgs( const QStringList &stringlistArguments );
    virtual bool doConnect( const QString &stringDSN, const QString &stringUID, const QString &stringPWD );
    virtual bool doDisconnect();
    virtual bool doProcess();
    virtual bool doProcessCommand( const QString &stringCommand );

    // process incoming commands 
    virtual bool doProcessBatch();
    virtual bool doProcessInteractive();
    virtual bool doExecuteSQL( const QString &stringCommand );
    virtual bool doExecuteShow( const QString &stringShow = QString::null );
    virtual bool doExecuteShowConfig();
    virtual bool doExecuteShowDriver( const QString &stringDriver );
    virtual bool doExecuteShowDrivers();
    virtual bool doExecuteShowDataSourceName( const QString &stringDataSourceName );
    virtual bool doExecuteShowDataSourceNames();

    // produce output
    virtual void    doProcessResultSet();
    // boxed with ascii art
    virtual QString doWriteHeaderNormal();
    virtual SQLLEN  doWriteBodyNormal();
    virtual void    doWriteFooterNormal( const QString &stringSepLine, SQLLEN nRows );
    // boxed with html table
    virtual void    doWriteHeaderHTMLTable();
    virtual SQLLEN  doWriteBodyHTMLTable();
    virtual void    doWriteFooterHTMLTable( SQLLEN nRows );
    // columns delimited (may contain column names in first row) 
    virtual void    doWriteHeaderDelimited();
    virtual void    doWriteBodyDelimited();
    // each result row is wrapped in an INSERT SQL statement
    virtual void    doWriteBodyInsertTable();

    // resultset processing helper stuff
    QVector<SQLUINTEGER> vectorColumnWidths;

    virtual QVector<SQLUINTEGER>    getColumnWidths( OQStatement *pStatement, SQLUINTEGER nUserWidth );
    virtual SQLUINTEGER             getColumnWidth( OQStatement *pStatement, SQLUINTEGER nUserWidth, SQLUSMALLINT nCol );

protected slots:
    virtual void slotMessage( OQMessage Message );
    virtual void slotDiagnostic( OQDiagnostic Diagnostic );
};



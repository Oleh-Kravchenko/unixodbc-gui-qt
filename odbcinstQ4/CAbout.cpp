/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#include <QtGui>

#include "CAbout.h"

#include "About48.xpm"

CAbout::CAbout( QWidget *pwidgetParent )
	: QTabWidget( pwidgetParent )
{

    // introduction to ODBC
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( "<B>What is ODBC?</B><P>Open Database Connectivity (ODBC) is an open specification for providing application developers with a predictable API with which to access Data Sources. Data Sources include SQL Servers and any Data Source with an ODBC Driver.</P><B>Why Use ODBC?</B><P>Software developers like to code to the ODBC specification because; <UL><LI>cross-database API</LI><LI>cross-platform API</LI><LI>API in their langauge of choice (C/C++)</LI><LI>ubiquitous support</LI><LI>no purchase required</LI><LI>good debugging support</LI><LI>good community support</LI><LI>knowledge of is relatively common</LI><LI>well documented API</LI></UL></P><P>Application Users like ODBC for some of the same reasons as Developers but also because;<UL><LI>many applications, particularly database appplications, support ODBC</LI><LI>easy to administrate</LI><LI>all majour databases (and then some) have an ODBC driver</LI><LI>an ODBC application can be told to use a different database without having to go to a developer to recode or even rebuild.</LI></UL></P><P>Whatever your reason is for using ODBC you can rest assured that you are in good company.</P><B>Resources</B><UL><LI>Microsoft - msdn.microsoft.com/library</LI></UL>" );
        addTab( pwidget, tr( "ODBC" ) );
    }

    // introduction to unixODBC
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( "<B>What is unixODBC?</B><P>unixODBC is an Open Source, free, implementation of ODBC for non-Microsoft platforms (platforms such as UNIX/Linux/OSX etc). ODBC applications developed on one platform have a very good chance of working on another platform with a simple recompile.</P><B>Resources</B><UL><LI>unixODBC - www.unixodbc.org</LI></UL>" );
        addTab( pwidget, tr( "unixODBC" ) );
    }

    // introduction to unixODBC-GUI-Qt
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( "<B>What is unixODBC-GUI-Qt?</B><P>unixODBC-GUI-Qt adds Qt-based GUI support to unixODBC. This was formally part of the unixODBC project but now exists as its own project.</P><B>Resources</B><UL><LI>unixODBC-GUI-Qt - unixodbc-gui-qt.sourceforge.net</LI></UL>" );
        addTab( pwidget, tr( "unixODBC-GUI-Qt" ) );
    }

    // introduction to people
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( "<P><B>Peter Harvey</B> (current project lead). Many others have contributed to unixODBC-GUI-Qt.</P><P>Please see the <B>AUTHORS</B> file in the source distribution for more information.</P>" );
        addTab( pwidget, tr( "People" ) );
    }

    // license
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( "<P>unixODBC-GUI-Qt is Open Source and licensed under GPL and LGPL. Those developing commercial software can safely build upon unixODBC-GUI-Qt without having to worry about additional licensing and cost issues.</P><P>The source includes a copy of the relevant license information in the <B>COPYING</B> file.</P>" );
        addTab( pwidget, tr( "License" ) );
    }

    // version
    {
        QWidget *       pwidget         = new QWidget( this );
        QVBoxLayout *   playout         = new QVBoxLayout( pwidget );
        QTextBrowser *  ptextbrowser    = new QTextBrowser( pwidget );

        playout->addWidget( ptextbrowser );
        ptextbrowser->setHtml( QString( "<TABLE><TR><TD>unixODBC-GUI-Qt</TD><TD>%1.%2.%3</TD><TR></TABLE>" ).arg( V_MAJOUR ).arg( V_MINOR ).arg( V_RELEASE ) );
        addTab( pwidget, tr( "Version" ) );
    }

    setWindowIcon( QPixmap( xpmAbout48 ) );
    setWindowTitle( tr( "About" ) );
}

CAbout::~CAbout()
{
}



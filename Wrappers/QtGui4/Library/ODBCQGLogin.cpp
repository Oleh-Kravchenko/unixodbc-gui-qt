/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "../include/ODBCQGLogin.h"

#include <ODBCMessage.h>

#include "../include/ODBCQGEnvironment.h"
#include "../include/ODBCQGMessageOutput.h"

#include "ODBC64.xpm"

ODBCQGLogin::ODBCQGLogin( QWidget *pwidgetParent, ODBCQGEnvironment *penvironment )
    : QDialog( pwidgetParent )
{
    setObjectName( "ODBCQGLogin" );
    this->penvironment = penvironment;

    QVBoxLayout *playoutTop = new QVBoxLayout;

    // init fields...
    {
        QGridLayout *playoutFields = new QGridLayout;

        // DRIVER
        plabelDriver = new QLabel( tr( "Driver" ) );
        pcomboboxDriver = new QComboBox;
        playoutFields->addWidget( plabelDriver, 0, 0 );
        playoutFields->addWidget( pcomboboxDriver, 0, 1 );

        // DSN
        plabelDataSourceName = new QLabel( tr( "Data Source Name" ) );
        pcomboboxDataSourceName = new QComboBox;
        playoutFields->addWidget( plabelDataSourceName, 1, 0 );
        playoutFields->addWidget( pcomboboxDataSourceName, 1, 1 );

        // UID
        plabelUserID  = new QLabel( tr( "User ID" ) );
        plineeditUserID = new QLineEdit;
    #ifndef Q_WS_WIN
        plineeditUserID->setText( ((struct passwd *)getpwuid(getuid()))->pw_name );
    #endif
        plineeditUserID->setToolTip( tr( "your User ID\nHINT: you get this from your database administrator" ) );
        playoutFields->addWidget( plabelUserID, 2, 0 );
        playoutFields->addWidget( plineeditUserID, 2, 1 );

        // PWD
        plabelPassword = new QLabel( tr( "Password" ) );
        plineeditPassword = new QLineEdit;
        plineeditPassword->setEchoMode( QLineEdit::Password );
        plineeditPassword->setToolTip( tr( "your password\nHINT: sometimes; you can leave this blank" ) );
        playoutFields->addWidget( plabelPassword, 3, 0 );
        playoutFields->addWidget( plineeditPassword, 3, 1 );

        playoutFields->setRowStretch( 4, 10 );
        playoutTop->addLayout( playoutFields );
    }

    // init dialog buttons...
    {
        QDialogButtonBox *  pDialogButtonBox    = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
        QFrame *            pFrame              = new QFrame;

        pFrame->setFrameStyle( QFrame::HLine );

        connect( pDialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()) );
        connect( pDialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()) );

        playoutTop->addWidget( pFrame );
        playoutTop->addWidget( pDialogButtonBox );
    }

    // messages
    {
        pmessageoutput = new ODBCQGMessageOutput( this );
        playoutTop->addWidget( pmessageoutput );
//        pmessageoutput->hide();
//        pmessageoutput->setMinimumHeight( 50 );
//        setExtension( pmessageoutput );
//        setOrientation( Qt::Vertical );
        connect( penvironment, SIGNAL(signalMessage(ODBCMessage*)), pmessageoutput, SLOT(slotMessage(ODBCMessage*)) );
    //    connect( pbMessages, SIGNAL(toggled(bool)), this, SLOT(showExtension(bool)) );
    }

    // 
    setLayout( playoutTop );
    setWindowTitle( tr( "Connect..." ) );
    setWindowIcon( QPixmap( xpmODBC64 ) );
    
#ifndef Q_WS_WIN
    plineeditPassword->setFocus();
#else
	plineeditUserID->setFocus();
#endif

    // do these last so we catch any errors with slotMessage
    loadDrivers();
    loadDataSourceNames();
}

ODBCQGLogin::~ODBCQGLogin()
{
}


void ODBCQGLogin::setShowDriver( bool b )
{
    if ( b )
    {
        plabelDriver->show();
        pcomboboxDriver->show();
    }
    else
    {
        plabelDriver->hide();
        pcomboboxDriver->hide();
    }
}

void ODBCQGLogin::setShowDataSourceName( bool b )
{
    if ( b )
    {
        plabelDataSourceName->show();
        pcomboboxDataSourceName->show();
    }
    else
    {
        plabelDataSourceName->hide();
        pcomboboxDataSourceName->hide();
    }
}

void ODBCQGLogin::setShowUserID( bool b )
{
    if ( b )
    {
        plabelUserID->show();
        plineeditUserID->show();
    }
    else
    {
        plabelUserID->hide();
        plineeditUserID->hide();
    }
}

void ODBCQGLogin::setShowPassword( bool b )
{
    if ( b )
    {
        plabelPassword->show();
        plineeditPassword->show();
    }
    else
    {
        plabelPassword->hide();
        plineeditPassword->hide();
    }
}

void ODBCQGLogin::setDriver( const QString &string )
{
/*
    QListBoxItem *plistboxitem = pcomboboxDriver->listBox()->findItem( string );
    if ( plistboxitem )
        pcomboboxDriver->listBox()->setCurrentItem( plistboxitem );
*/
    pcomboboxDriver->setEditText( string );
}

void ODBCQGLogin::setDataSourceName( const QString &string )
{
    pcomboboxDataSourceName->setEditText( string );
}

void ODBCQGLogin::setUserID( const QString &string )
{
    plineeditUserID->setText( string );
}

void ODBCQGLogin::setPassword( const QString &string )
{
    plineeditPassword->setText( string );
}

void ODBCQGLogin::loadDrivers()
{
    pcomboboxDriver->insertItems( 0, penvironment->getDrivers() );
    pcomboboxDriver->insertItem( 0, "" );
}

void ODBCQGLogin::loadDataSourceNames()
{
    pcomboboxDataSourceName->insertItems( 0, penvironment->getDataSources() );
    pcomboboxDataSourceName->insertItem( 0, "" );
}



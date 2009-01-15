/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2009
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#include <QtGui>

#include "CDriverConnectPrompt.h"
#include "CDataSourceNames.h"
#include "CDataSourceNamesFile.h"
#include "CPage.h"

CDriverConnectPrompt::CDriverConnectPrompt( SQLCHAR *pszDataSourceName, SQLSMALLINT nMaxChars, QWidget *pwidgetParent )
    : QDialog( pwidgetParent )
{
    this->pszDataSourceName = pszDataSourceName;
    this->nMaxChars         = nMaxChars;

    QVBoxLayout *playout00 = new QVBoxLayout;

    //
    pManageDataSourceNames  = new CManageDataSourceNames;
    playout00->addWidget( pManageDataSourceNames );

    // init dialog buttons...
    {
        QDialogButtonBox *  pdialogbuttonbox    = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help );

        connect( pdialogbuttonbox, SIGNAL(accepted()), this, SLOT(slotAccept()) );
        connect( pdialogbuttonbox, SIGNAL(rejected()), this, SLOT(reject()) );
//        connect( pdialogbuttonbox, SIGNAL(helpRequested()), this, SLOT(slotHelp()) );

        playout00->addWidget( pdialogbuttonbox );
    }

    // 
    setLayout( playout00 );
    setWindowTitle( tr( "Select Data Source..." ) );
    setWindowIcon( pManageDataSourceNames->windowIcon() );

    // restore last state...
    loadState();
}

CDriverConnectPrompt::~CDriverConnectPrompt()
{
    saveState();
}

void CDriverConnectPrompt::slotAccept()
{
    QString stringDataSourceName;
    QWidget *pwidgetPage = pManageDataSourceNames->currentWidget();

    // sanity checks...
    if ( !pwidgetPage )
        return;

    if ( pwidgetPage->inherits( "CPage" ) )
        return;

    // get data source name...
    QWidget *pwidgetContent = ((CPage*)pwidgetPage)->getContent();

    if ( pwidgetContent->inherits( "CDataSourceNames" ) )
    {
        CDataSourceNames *pDataSourceNames = (CDataSourceNames*)pwidgetContent;
        stringDataSourceName = pDataSourceNames->getDataSourceName();
        if ( !stringDataSourceName.isEmpty() )
            stringDataSourceName = "DSN=" + stringDataSourceName;
    }
    else if ( pwidgetContent->inherits( "CDataSourceNamesFile" ) )
    {
        CDataSourceNamesFile *pDataSourceNamesFile = (CDataSourceNamesFile*)pwidgetContent;
        stringDataSourceName = pDataSourceNamesFile->getDataSourceName();
        if ( !stringDataSourceName.isEmpty() )
            stringDataSourceName = "FILEDSN=" + stringDataSourceName;
    }
    else
        return;

    // must select a data source name...
    if ( stringDataSourceName.isEmpty() )
    {
        QMessageBox::warning( this, "Select a data source name...", "Please select a data source name or Cancel." );
        return;
    }

    if ( stringDataSourceName.length() >= nMaxChars )
    {
        QMessageBox::warning( this, "Select a data source name...", "Buffer provided is too small. Select a Data Source Name with less characters or Cancel." );
        return;
    }

    // cool - we have it...
    strncpy( (char*)pszDataSourceName, stringDataSourceName.toAscii().constData(), nMaxChars ); 
    pszDataSourceName[nMaxChars - 1] = '\0';

    accept();
}

void CDriverConnectPrompt::loadState()
{
    QSettings settings;

    int nW = settings.value( "CDriverConnectPrompt/w", geometry().width() ).toInt();
    int nH = settings.value( "CDriverConnectPrompt/h", geometry().height() ).toInt();

    resize( nW, nH );
}

void CDriverConnectPrompt::saveState()
{
    QSettings settings;

    settings.setValue( "CDriverConnectPrompt/w", width() );
    settings.setValue( "CDriverConnectPrompt/h", height() );
}



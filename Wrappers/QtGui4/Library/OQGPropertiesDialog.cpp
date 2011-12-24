/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2008, LGPL
 */
#include <QtGui>

#include "../include/OQGPropertiesDialog.h"
#include "../include/OQGPropertiesModel.h"
#include "../include/OQGPropertiesDelegate.h"

#include "ODBC64.xpm"

OQGPropertiesDialog::OQGPropertiesDialog( QVector<OQGProperty> vectorProperties, QWidget *pwidgetParent )
	: QDialog( pwidgetParent )
{
    QVBoxLayout *           playout                 = new QVBoxLayout;
    QTableView *            ptableview              = new QTableView;
    QFrame *                pframe                  = new QFrame;
    QDialogButtonBox *      pdialogbuttonbox        = new QDialogButtonBox( QDialogButtonBox::Cancel | QDialogButtonBox::Ok | QDialogButtonBox::Help );

    pframe->setFrameStyle( QFrame::HLine );

    ppropertiesmodel    = new OQGPropertiesModel( vectorProperties );
    ppropertiesdelegate = new OQGPropertiesDelegate;
    ptableview->setModel( ppropertiesmodel );
    ptableview->setItemDelegateForColumn ( 1, ppropertiesdelegate );
    ptableview->verticalHeader()->hide();

    connect( pdialogbuttonbox, SIGNAL(accepted()), this, SLOT(accept()) );
    connect( pdialogbuttonbox, SIGNAL(rejected()), this, SLOT(reject()) );

    playout->addWidget( ptableview, 10 );
    playout->addWidget( pframe );
    playout->addWidget( pdialogbuttonbox );

    setWindowIcon( QPixmap( xpmODBC64 ) );
    setLayout( playout );

    loadState();
}

OQGPropertiesDialog::~OQGPropertiesDialog()
{
    saveState();
    delete ppropertiesdelegate;
    delete ppropertiesmodel;
}

void OQGPropertiesDialog::loadState()
{
    QSettings settings;

    int nW = settings.value( "OQGPropertiesDialog/w", geometry().width() ).toInt();
    int nH = settings.value( "OQGPropertiesDialog/h", geometry().height() ).toInt();

    resize( nW, nH );
}

void OQGPropertiesDialog::saveState()
{
    QSettings settings;

    settings.setValue( "OQGPropertiesDialog/w", width() );
    settings.setValue( "OQGPropertiesDialog/h", height() );
}



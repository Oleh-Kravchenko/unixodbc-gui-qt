/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#include <QtGui>

#include "../include/ODBCQGPropertiesDialog.h"
#include "../include/ODBCQGPropertiesModel.h"
#include "../include/ODBCQGPropertiesDelegate.h"

#include "ODBC64.xpm"

ODBCQGPropertiesDialog::ODBCQGPropertiesDialog( QVector<ODBCQGProperty> vectorProperties, QWidget *pwidgetParent )
	: QDialog( pwidgetParent )
{
    QVBoxLayout *           playout                 = new QVBoxLayout;
    QTableView *            ptableview              = new QTableView;
    QFrame *                pframe                  = new QFrame;
    QDialogButtonBox *      pdialogbuttonbox        = new QDialogButtonBox( QDialogButtonBox::Cancel | QDialogButtonBox::Ok | QDialogButtonBox::Help );

    pframe->setFrameStyle( QFrame::HLine );

    ppropertiesmodel    = new ODBCQGPropertiesModel( vectorProperties );
    ppropertiesdelegate = new ODBCQGPropertiesDelegate;
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

ODBCQGPropertiesDialog::~ODBCQGPropertiesDialog()
{
    saveState();
    delete ppropertiesdelegate;
    delete ppropertiesmodel;
}

void ODBCQGPropertiesDialog::loadState()
{
    QSettings settings;

    int nW = settings.value( "ODBCQGPropertiesDialog/w", geometry().width() ).toInt();
    int nH = settings.value( "ODBCQGPropertiesDialog/h", geometry().height() ).toInt();

    resize( nW, nH );
}

void ODBCQGPropertiesDialog::saveState()
{
    QSettings settings;

    settings.setValue( "ODBCQGPropertiesDialog/w", width() );
    settings.setValue( "ODBCQGPropertiesDialog/h", height() );
}



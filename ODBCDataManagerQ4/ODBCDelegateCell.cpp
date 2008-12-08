/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2008
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#include <QtGui>

#include "ODBCDelegateCell.h"
#include "ODBCValueCell.h"
#include "ODBCModel.h"

ODBCDelegateCell::ODBCDelegateCell( QObject *pobjectParent )
    : QItemDelegate( pobjectParent )
{
}

QWidget *ODBCDelegateCell::createEditor( QWidget *pwidgetParent, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    if ( modelindex.column() != 1 )
        return 0;

    ODBCValueCell ValueCell = modelindex.model()->data( modelindex, Qt::EditRole ).value<ODBCValueCell>();

    switch ( ValueCell.nPromptType )
    {
        case ODBCValueCell::PromptTypeLabel:
            {
                QLabel *pLabel = new QLabel( pwidgetParent );
                return pLabel;
            }
            break;

        case ODBCValueCell::PromptTypeList:
            {
                QComboBox *pComboBox = new QComboBox( pwidgetParent );
                for ( int n = 0; n < ValueCell.vectorValues.count(); n++ )
                {
                    pComboBox->insertItem( 0, ValueCell.vectorValues.at( n ).toString() );
                }
                return pComboBox;
            }
            break;

        case ODBCValueCell::PromptTypeCombo:
            {
                QComboBox *pComboBox = new QComboBox( pwidgetParent );
                for ( int n = 0; n < ValueCell.vectorValues.count(); n++ )
                {
                    pComboBox->insertItem( 0, ValueCell.vectorValues.at( n ).toString() );
                }
                pComboBox->setEditable( true );
                return pComboBox;
            }
            break;

        case ODBCValueCell::PromptTypeFile:
            {
//                CFileSelector *pFileSelector = new CFileSelector( CFileSelector::Driver, QString::null, true, true, pwidgetParent );
//                return pFileSelector;
            }
            break;

        case ODBCValueCell::PromptTypeBool:
            {
                QCheckBox *pCheckBox = new QCheckBox( pwidgetParent );
                return pCheckBox;
            }
            break;

        case ODBCValueCell::PromptTypeHidden:
            break;

        case ODBCValueCell::PromptTypeText:
            {
                QLineEdit *pLineEdit = new QLineEdit( pwidgetParent );
                return pLineEdit;
            }
            break;

        case ODBCValueCell::PromptTypePassword:
            {
                QLineEdit *pLineEdit = new QLineEdit( pwidgetParent );
                pLineEdit->setEchoMode( QLineEdit::Password ) ;
                return pLineEdit;
            }
            break;

        case ODBCValueCell::PromptTypeDefault:
            break;

        default: 
            break;
    }

    return 0;
}

void ODBCDelegateCell::setEditorData( QWidget *pwidgetEditor, const QModelIndex &modelindex ) const
{
    ODBCValueCell ValueCell = modelindex.model()->data( modelindex, Qt::EditRole ).value<ODBCValueCell>();

    switch ( ValueCell.nPromptType )
    {
        case ODBCValueCell::PromptTypeLabel:
            break;

        case ODBCValueCell::PromptTypeList:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                pComboBox->setCurrentIndex( pComboBox->findText( ValueCell.vValue.toString(), Qt::MatchExactly ) );
            }
            break;

        case ODBCValueCell::PromptTypeCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                pComboBox->lineEdit()->setText( ValueCell.vValue.toString() );
            }
            break;

        case ODBCValueCell::PromptTypeFile:
            {
//                CFileSelector *pFileSelector = static_cast<CFileSelector*>( pwidgetEditor );
//                pFileSelector->setText( pProperty->szValue );
            }
            break;

        case ODBCValueCell::PromptTypeBool:
            {
                QCheckBox *pCheckBox = static_cast<QCheckBox*>( pwidgetEditor );
                if ( ValueCell.vValue.toString() == "On" || ValueCell.vValue.toString() == "True" )
                    pCheckBox->setChecked( true );
                else
                    pCheckBox->setChecked( true );
            }
            break;

        case ODBCValueCell::PromptTypeHidden:
            break;

        case ODBCValueCell::PromptTypeText:
        case ODBCValueCell::PromptTypePassword:
            {
                QLineEdit *pLineEdit = static_cast<QLineEdit*>( pwidgetEditor );
                pLineEdit->setText( ValueCell.vValue.toString() );
            }
            break;

        case ODBCValueCell::PromptTypeDefault:
            break;

        default:
            break;
    }
}

void ODBCDelegateCell::setModelData( QWidget *pwidgetEditor, QAbstractItemModel *abstractitemmodel, const QModelIndex &modelindex) const
{
    ODBCValueCell ValueCell = abstractitemmodel->data( modelindex, Qt::EditRole ).value<ODBCValueCell>();

    switch ( ValueCell.nPromptType )
    {
        case ODBCValueCell::PromptTypeLabel:
            break;

        case ODBCValueCell::PromptTypeList:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                ValueCell.vValue = pComboBox->currentText();
                abstractitemmodel->setData( modelindex, QVariant::fromValue( ValueCell ), Qt::EditRole );              
            }
            break;

        case ODBCValueCell::PromptTypeCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                ValueCell.vValue = pComboBox->currentText();
                abstractitemmodel->setData( modelindex, QVariant::fromValue( ValueCell ), Qt::EditRole );
            }
            break;

        case ODBCValueCell::PromptTypeFile:
            {
//                CFileSelector *pFileSelector = static_cast<CFileSelector*>( pwidgetEditor );
//                abstractitemmodel->setData( modelindex, pFileSelector->getText(), Qt::EditRole );
            }
            break;

        case ODBCValueCell::PromptTypeHidden:
            break;

        case ODBCValueCell::PromptTypeText:
        case ODBCValueCell::PromptTypePassword:
            {
                QLineEdit *pLineEdit = static_cast<QLineEdit*>( pwidgetEditor );
                ValueCell.vValue = pLineEdit->text();
                abstractitemmodel->setData( modelindex, QVariant::fromValue( ValueCell ), Qt::EditRole );
            }
            break;

        case ODBCValueCell::PromptTypeDefault:
            break;

        default:
            break;
    }
}

void ODBCDelegateCell::updateEditorGeometry( QWidget *pwidgetEditor, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    pwidgetEditor->setGeometry( styleoptionviewitem.rect );
}


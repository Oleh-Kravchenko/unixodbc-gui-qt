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

#include "../include/ODBCQGProperty.h"
#include "../include/ODBCQGPropertiesDelegate.h"
#include "../include/ODBCQGPropertiesModel.h"

ODBCQGPropertiesDelegate::ODBCQGPropertiesDelegate( QObject *pobjectParent )
    : QItemDelegate( pobjectParent )
{
}

QWidget *ODBCQGPropertiesDelegate::createEditor( QWidget *pwidgetParent, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    if ( modelindex.column() != 1 )
        return 0;

    ODBCQGProperty property = modelindex.model()->data( modelindex, Qt::EditRole ).value<ODBCQGProperty>();

    switch ( property.getPromptType() )
    {
        case ODBCQGProperty::PromptLabel:
            {
                QLabel *pLabel = new QLabel( pwidgetParent );
                return pLabel;
            }
            break;

        case ODBCQGProperty::PromptCombo:
            {
                QComboBox *pComboBox = new QComboBox( pwidgetParent );
                QStringList listOptions = property.getOptions();
                for ( int n = 0; n < listOptions.count(); n++ )
                {
                    pComboBox->insertItem( 0, listOptions.at( n ) );
                }
                return pComboBox;
            }
            break;

        case ODBCQGProperty::PromptComboWrite:
            {
                QComboBox *pComboBox = new QComboBox( pwidgetParent );
                QStringList listOptions = property.getOptions();
                for ( int n = 0; n < listOptions.count(); n++ )
                {
                    pComboBox->insertItem( 0, listOptions.at( n ) );
                }
                pComboBox->setEditable( true );
                return pComboBox;
            }
            break;

        default: // PROMPTTYPE_TEXTEDIT and PROMPTTYPE_TEXTEDIT_PASSWORD
            {
                QLineEdit *pLineEdit = new QLineEdit( pwidgetParent );
                return pLineEdit;
            }
            break;
    }

    return 0;
}

void ODBCQGPropertiesDelegate::setEditorData( QWidget *pwidgetEditor, const QModelIndex &modelindex ) const
{
    ODBCQGProperty property = modelindex.model()->data( modelindex, Qt::EditRole ).value<ODBCQGProperty>();

    switch ( property.getPromptType() )
    {
        case ODBCQGProperty::PromptLabel:
            break;

        case ODBCQGProperty::PromptCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                pComboBox->setCurrentIndex( pComboBox->findText( property.getValue(), Qt::MatchExactly ) );
            }
            break;

        case ODBCQGProperty::PromptComboWrite:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                pComboBox->lineEdit()->setText( property.getValue() );
            }
            break;

        default:
            {
                QLineEdit *pLineEdit = static_cast<QLineEdit*>( pwidgetEditor );
                pLineEdit->setText( property.getValue() );
            }
            break;
    }
}

void ODBCQGPropertiesDelegate::setModelData( QWidget *pwidgetEditor, QAbstractItemModel *abstractitemmodel, const QModelIndex &modelindex) const
{
    ODBCQGProperty property = abstractitemmodel->data( modelindex, Qt::EditRole ).value<ODBCQGProperty>();

    switch ( property.getPromptType() )
    {
        case ODBCQGProperty::PromptLabel:
            break;

        case ODBCQGProperty::PromptCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                abstractitemmodel->setData( modelindex, pComboBox->currentText(), Qt::EditRole );
            }
            break;

        case ODBCQGProperty::PromptComboWrite:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                abstractitemmodel->setData( modelindex, pComboBox->currentText(), Qt::EditRole );
            }
            break;

        default: 
            {
                QLineEdit *pLineEdit = static_cast<QLineEdit*>( pwidgetEditor );
                abstractitemmodel->setData( modelindex, pLineEdit->text(), Qt::EditRole );
            }
            break;
    }
}

void ODBCQGPropertiesDelegate::updateEditorGeometry( QWidget *pwidgetEditor, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    pwidgetEditor->setGeometry( styleoptionviewitem.rect );
}


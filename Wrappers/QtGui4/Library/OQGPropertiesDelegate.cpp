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

#include "../include/OQGProperty.h"
#include "../include/OQGPropertiesDelegate.h"
#include "../include/OQGPropertiesModel.h"

OQGPropertiesDelegate::OQGPropertiesDelegate( QObject *pobjectParent )
    : QItemDelegate( pobjectParent )
{
}

QWidget *OQGPropertiesDelegate::createEditor( QWidget *pwidgetParent, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    if ( modelindex.column() != 1 )
        return 0;

    OQGProperty property = modelindex.model()->data( modelindex, Qt::EditRole ).value<OQGProperty>();

    switch ( property.getPromptType() )
    {
        case OQGProperty::PromptLabel:
            {
                QLabel *pLabel = new QLabel( pwidgetParent );
                return pLabel;
            }
            break;

        case OQGProperty::PromptCombo:
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

        case OQGProperty::PromptComboWrite:
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

void OQGPropertiesDelegate::setEditorData( QWidget *pwidgetEditor, const QModelIndex &modelindex ) const
{
    OQGProperty property = modelindex.model()->data( modelindex, Qt::EditRole ).value<OQGProperty>();

    switch ( property.getPromptType() )
    {
        case OQGProperty::PromptLabel:
            break;

        case OQGProperty::PromptCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                pComboBox->setCurrentIndex( pComboBox->findText( property.getValue(), Qt::MatchExactly ) );
            }
            break;

        case OQGProperty::PromptComboWrite:
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

void OQGPropertiesDelegate::setModelData( QWidget *pwidgetEditor, QAbstractItemModel *abstractitemmodel, const QModelIndex &modelindex) const
{
    OQGProperty property = abstractitemmodel->data( modelindex, Qt::EditRole ).value<OQGProperty>();

    switch ( property.getPromptType() )
    {
        case OQGProperty::PromptLabel:
            break;

        case OQGProperty::PromptCombo:
            {
                QComboBox *pComboBox = static_cast<QComboBox*>( pwidgetEditor );
                abstractitemmodel->setData( modelindex, pComboBox->currentText(), Qt::EditRole );
            }
            break;

        case OQGProperty::PromptComboWrite:
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

void OQGPropertiesDelegate::updateEditorGeometry( QWidget *pwidgetEditor, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const
{
    pwidgetEditor->setGeometry( styleoptionviewitem.rect );
}


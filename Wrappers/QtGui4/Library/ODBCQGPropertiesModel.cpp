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

#include "../include/ODBCQGPropertiesModel.h"
#include "../include/ODBCQGPropertiesDelegate.h"

/*! 
 * \brief   Construct a properties model.
 * 
 * \param   pobjectParent
 * \param   vectorProperties
 */
ODBCQGPropertiesModel::ODBCQGPropertiesModel( QVector<ODBCQGProperty> vectorProperties, QObject *pobjectParent )
    : QAbstractTableModel( pobjectParent )
{
    this->vectorProperties = vectorProperties;
}

ODBCQGPropertiesModel::~ODBCQGPropertiesModel()
{
}

/*! 
 * \brief   Return the number of rows needed to view the properties.
 * 
 *          
 * \return  int Output. The number of properties.
 */
int ODBCQGPropertiesModel::rowCount( const QModelIndex & ) const
{
    return vectorProperties.size();
}

/*! 
 * \brief   Return the number of columns needed to view the properties.
 * 
 *          We always return 2. We have 1 column with the property name and 1 column with the
 *          value - the latter us typically, but not always, editable.
 * 
 * \return  int Output. Always 2.
 */
int ODBCQGPropertiesModel::columnCount( const QModelIndex & ) const
{
    return 2;
}

/*! 
 * \brief   Provide cell data to the view and any delegate we may have in play
 *          for the cell.
 *
 *          We expect that the 2nd column will have ODBCQGPropertiesDelegate installed on it. So for
 *          the 2nd column we may return the value text or HODBCINSTPROPERTY.
 *
 * \param   index
 * \param   nRole   Input. Qt::ItemDataRole. This is provided to request a specific variant of the
 *                  data associated with the cell.
 * 
 * \return  QVariant
 */
QVariant ODBCQGPropertiesModel::data( const QModelIndex &index, int nRole ) const
{
    /* \todo are these sanity checks really needed? */
    if ( !index.isValid() )
        return QVariant();
    if ( index.row() >= vectorProperties.size() )
         return QVariant();

    ODBCQGProperty property = vectorProperties.at( index.row() );

    /* which column ? */
    if ( index.column() == 0 )
    {
        switch ( nRole )
        {
            case Qt::DisplayRole:   /* called by QTableView to display the value text   */
            case Qt::EditRole:      /* the 1st column should not be editable but...     */
                return property.getName();
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
                return property.getHelp();
            default:
                break;
        }
    }
    else
    {
        switch ( nRole )
        {
            case Qt::DisplayRole:   /* called by QTableView to display the value text without editor                    */
                return property.getValue();
            case Qt::EditRole:      /* called by ODBCQGPropertiesDelegate:: createEditor & setEditorData to load cell editor */
                return QVariant::fromValue( property );
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
                return property.getHelp();
            default:
                break;
        }
    }

    return QVariant();
}

/*! 
 * \brief   Set data.
 * 
 *          The view (possibly via a delegate) will ask to set the cell value which will result
 *          in a call to this method.
 *
 * \param   index           Input. Index into the cell.
 * \param   variantValue    Input. The only column we deal with here is the 2nd column (the value) and 
 *                          we expect to get that as a QString. This should come from 
 *                          \sa ODBCQGPropertiesDelegate::setModelData.
 * \param   nRole           Input. Qt::ItemDataRole. This is provided to request setting a specific variant 
 *                          of the data associated with the cell.
 * 
 * \return bool
 */
bool ODBCQGPropertiesModel::setData( const QModelIndex &index, const QVariant &variantValue, int nRole )
{
    if ( !index.isValid() )
        return false;

    if ( index.column() == 0 )
        return false;

    if ( nRole == Qt::EditRole )
    {
        ODBCQGProperty *pProperties = vectorProperties.data();
        pProperties[index.row()].setValue( variantValue.toString() );
        emit dataChanged( index, index );
        return true;
    }

    return false;
}

/*! 
 * \brief   The delegate will check this to determine what it can do with a cell.
 * 
 * \param   index   Input. Cell index.
 * 
 * \return  Qt::ItemFlags
 */
Qt::ItemFlags ODBCQGPropertiesModel::flags( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return Qt::ItemIsEnabled; /* for lack of a better choice :/ */

    if ( index.column() == 1 )
        return ( QAbstractItemModel::flags( index ) | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled );

    return Qt::ItemIsEnabled; /* for lack of a better choice :/ */
}

/*! 
 * \brief   QTableView (or possibly a delegate) will get column headers here.
 * 
 * \param   nSection        Input. Column/row.
 * \param   nOrientation    Input. Qt::Orientation.
 * \param   nRole           Input. Qt::ItemDataRole. This is provided to request a specific variant 
 *                          of the data associated with the cell.
 * 
 * \return QVariant
 */
QVariant ODBCQGPropertiesModel::headerData( int nSection, Qt::Orientation nOrientation, int nRole ) const
{
    if ( nRole != Qt::DisplayRole )
         return QVariant();
    if ( nOrientation != Qt::Horizontal )
        return QVariant();

    if ( nSection == 0 )
        return QString( tr( "Name" ) );

    if ( nSection == 1 )
        return QString( tr( "Value" ) );

    return QVariant();
}




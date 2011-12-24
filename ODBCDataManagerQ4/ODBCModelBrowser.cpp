/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "ODBCModelBrowser.h"

ODBCModelBrowser::ODBCModelBrowser( ODBCModel *pModel, QObject *pobjectParent )
    : QAbstractItemModel( pobjectParent )
{
    pmodelRoot = pModel;
}

ODBCModelBrowser::~ODBCModelBrowser()
{
}

QModelIndex ODBCModelBrowser::index( int nRow, int nColumn, const QModelIndex &indexParent ) const
{
    // is valid request...
    if ( nColumn != 0 || nRow < 0 || indexParent.column() > 0 )
        return QModelIndex();

    // are we requesting the root model... 
    if ( !indexParent.isValid() )
    {
        // we only have 1 root model
        if ( nRow != 0 )
            return QModelIndex();
        return createIndex( nRow, nColumn, pmodelRoot );
    }

    // get parent model...
    ODBCModel *pmodelParent = getModel( indexParent );
    if ( !pmodelParent )
        return QModelIndex();

    // make sure the list of children is up to date

    // do we have child/row?
    if ( nRow >= pmodelParent->children().count() )
        return QModelIndex();

    return createIndex( nRow, nColumn, pmodelParent->children().at( nRow ) );
}

QModelIndex ODBCModelBrowser::parent( const QModelIndex &indexChild ) const
{
    // valid request?
    if ( !indexChild.isValid() )
        return QModelIndex();

    ODBCModel *pmodelChild = getModel( indexChild );
    if ( !pmodelChild )
        return QModelIndex();

    // is child root (no parent)...
    if ( pmodelChild == pmodelRoot )
        return QModelIndex();

    ODBCModel *pmodelParent = (ODBCModel*)((QObject*)pmodelChild)->parent();
    if ( !pmodelParent )
        return QModelIndex();

    // is parent root...
    if ( pmodelParent == pmodelRoot )
        return createIndex( 0, 0, pmodelParent );

    // get the row number of the parent and create index...
    ODBCModel *pmodelParentParent = (ODBCModel*)((QObject*)pmodelParent)->parent();
    if ( !pmodelParentParent )
        return QModelIndex();

    return createIndex( pmodelParentParent->children().indexOf( pmodelParent ), 0, pmodelParent );
}

/*! 
 * \brief   Return the number of rows needed to view the children.
 * 
 *          
 * \return  int Output. The number of children.
 */
int ODBCModelBrowser::rowCount( const QModelIndex &indexParent ) const
{
    if ( indexParent.column() > 0 )
        return 0;

    // request is for root items (we always have 1)...
    if ( !indexParent.isValid() ) 
        return 1;

    // request is for child count...
    ODBCModel *pmodelParent = getModel( indexParent );
    if ( !pmodelParent )
        return 0;

    // lazy load
    if ( !pmodelParent->isLoaded() )
        pmodelParent->doLoad();

    return pmodelParent->children().count();
}

/*! 
 * \brief   Return the number of columns needed to view.
 * 
 *          We return 1 so we can view an icon and text.
 * 
 * \return  int Output.
 */
int ODBCModelBrowser::columnCount( const QModelIndex &indexParent ) const
{
    if ( indexParent.column() > 0 )
        return 0;

    return 1;
}

/*! 
 * \brief   Provide cell data to the view and any delegate we may have in play
 *          for the cell.
 *
 *          We expect that the 2nd column will have CPropertiesDelegate installed on it. So for
 *          the 2nd column we may return the value text or HODBCINSTPROPERTY.
 *
 * \param   index
 * \param   nRole   Input. Qt::ItemDataRole. This is provided to request a specific variant of the
 *                  data associated with the cell.
 * 
 * \return  QVariant
 */
QVariant ODBCModelBrowser::data( const QModelIndex &index, int nRole ) const
{
    ODBCModel *pModel = getModel( index );
    if ( !pModel )
         return QVariant();

    if ( index.column() == 0 )
    {
        switch ( nRole )
        {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return pModel->getText();
            case Qt::DecorationRole:
                return pModel->getIcon();
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
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
 *                          \sa CPropertiesDelegate::setModelData.
 * \param   nRole           Input. Qt::ItemDataRole. This is provided to request setting a specific variant 
 *                          of the data associated with the cell.
 * 
 * \return bool
 */
bool ODBCModelBrowser::setData( const QModelIndex &index, const QVariant &variantValue, int nRole )
{
    ODBCModel *pModel = getModel( index );
    if ( !pModel )
         return false;

    if ( index.column() == 0 )
        return false;

    if ( nRole == Qt::EditRole )
    {
        pModel->setText( variantValue.toString() );
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
Qt::ItemFlags ODBCModelBrowser::flags( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return Qt::ItemIsEnabled; /* for lack of a better choice :/ */

    if ( index.column() == 0 )
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
QVariant ODBCModelBrowser::headerData( int nSection, Qt::Orientation nOrientation, int nRole ) const
{
    if ( nRole != Qt::DisplayRole )
         return QVariant();

    if ( nOrientation != Qt::Horizontal )
        return QVariant();

    if ( nSection == 0 )
        return QString( tr( "Name" ) );

    return QVariant();
}

bool ODBCModelBrowser::hasChildren( const QModelIndex &indexParent ) const
{
    ODBCModel *pModel = getModel( indexParent );
    if ( !pModel )
         return true;
    if ( !pModel->isLoaded() )
        return true;
    if ( pModel->children().count() )
        return true;
    return false;
}

void ODBCModelBrowser::doContextMenu( const QModelIndex &index, QWidget *pwidgetParent, QPoint pos )
{
    ODBCModel *pModel = getModel( index );
    if ( !pModel )
         return;
    pModel->doContextMenu( pwidgetParent, pos );
}

ODBCModel *ODBCModelBrowser::getModel( const QModelIndex &index ) const
{
    if ( index.isValid() )
        return (ODBCModel*)(index.internalPointer());
    return 0;
}


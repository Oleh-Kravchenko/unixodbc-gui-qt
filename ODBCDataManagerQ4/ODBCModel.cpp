/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "ODBCModel.h"

ODBCModel::ODBCModel( ODBCModel *pmodelParent )
    : QAbstractTableModel( pmodelParent )
{
    bLoaded     = false;
    nRows       = 0;
    nColumns    = 2;
}

ODBCModel::~ODBCModel()
{
}

int ODBCModel::rowCount( const QModelIndex & /* no parent in this model */ ) const
{
    return nRows;
}

int ODBCModel::columnCount( const QModelIndex & /* no parent in this model */ ) const
{
    return nColumns;
}

Qt::ItemFlags ODBCModel::flags( const QModelIndex &index ) const
{
    if ( index.isValid() && index.column() == 1 )
        return ( QAbstractItemModel::flags( index ) | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled );

    return Qt::ItemIsEnabled;
}

QVariant ODBCModel::headerData( int nSection, Qt::Orientation nOrientation, int nRole ) const
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

void ODBCModel::setText( const QString &stringText )
{
    setObjectName( stringText );
}

QString ODBCModel::getText()
{
    return objectName();
}

ODBCQGSystem *ODBCModel::getSystem()
{
    QObject *pObject = QObject::parent();
    if ( !pObject )
        return NULL;

    ODBCModel *pModel = (ODBCModel*)pObject;

    return pModel->getSystem();
}

ODBCQGEnvironment *ODBCModel::getEnvironment()
{
    QObject *pObject = QObject::parent();
    if ( !pObject )
        return NULL;

    ODBCModel *pModel = (ODBCModel*)pObject;

    return pModel->getEnvironment();
}

ODBCQGConnection *ODBCModel::getConnection()
{
    QObject *pObject = QObject::parent();
    if ( !pObject )
        return NULL;

    ODBCModel *pModel = (ODBCModel*)pObject;

    return pModel->getConnection();
}



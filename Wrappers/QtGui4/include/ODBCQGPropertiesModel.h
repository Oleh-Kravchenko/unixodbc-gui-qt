/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#ifndef ODBCQGPROPERTIESMODEL_H
#define ODBCQGPROPERTIESMODEL_H
#include <QAbstractTableModel>

#include <QVector>

#include "ODBCQGProperty.h"

/* declare a non-standard data type so we can have it pass to/from as QVariant */
Q_DECLARE_METATYPE(ODBCQGProperty)

class ODBCQGPropertiesModel : public QAbstractTableModel
{
public:
    ODBCQGPropertiesModel( QVector<ODBCQGProperty> vectorProperties, QObject *pobjectParent = 0 );
    virtual ~ODBCQGPropertiesModel();

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QVector<ODBCQGProperty> getProperties() { return vectorProperties; }

private:
    QVector<ODBCQGProperty> vectorProperties;
};

#endif


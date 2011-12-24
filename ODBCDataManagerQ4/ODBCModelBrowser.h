/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef ODBCMODELBROWSER_H
#define ODBCMODELBROWSER_H

#include <QtGui>

#include <ODBCModel.h>

class ODBCModelBrowser : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ODBCModelBrowser( ODBCModel *pModel, QObject *pobjectParent = 0 );
    virtual ~ODBCModelBrowser();

    QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
    QModelIndex parent( const QModelIndex &child ) const;
    int rowCount( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;
    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    bool hasChildren( const QModelIndex &parent = QModelIndex() ) const;

    void doContextMenu( const QModelIndex &index, QWidget *pwidgetParent, QPoint pos );

    ODBCModel *getModel( const QModelIndex &index ) const;

protected:
    ODBCModel *pmodelRoot; // items are, themselves, models - and the root item is usually an ODBCModelEnvironment

};

#endif


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef ODBCMODELDRIVER_H
#define ODBCMODELDRIVER_H

#include "ODBCModel.h"

class ODBCModelDriver : public ODBCModel
{
    Q_OBJECT
public:
    explicit ODBCModelDriver( ODBCModel *pmodelParent, const QString &stringDriver );
    ~ODBCModelDriver();

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    void setText( const QString & ) {}

    QIcon getIcon();

    bool doLoad();
    bool doClear();
    void doContextMenu( QWidget *pwidgetParent, QPoint pos );

protected slots:
    void slotConnect();
    void slotRemove();

protected:
    QVector<QString>  vectorKeys;       // property keys...
    QVector<QString>  vectorValues;     // ...and corresponding values (we need to access via index not key)
    QAction *         pactionConnect; 
    QAction *         pactionRemove;

    void doLoadProperties();
    bool doSaveProperty( const QString &stringKey, const QString &stringValue );
};

#endif


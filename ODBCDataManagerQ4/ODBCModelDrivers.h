#ifndef ODBCMODELDRIVERS_H
#define ODBCMODELDRIVERS_H

#include "ODBCModel.h"
#include "ODBCModelDriver.h"

class ODBCModelDrivers : public ODBCModel
{
    Q_OBJECT
public:
    explicit ODBCModelDrivers( ODBCModel *pmodelParent );
    ~ODBCModelDrivers();

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    void    setText( const QString & ) {}

    QIcon   getIcon();

    bool doLoad();
    bool doClear();
};

#endif


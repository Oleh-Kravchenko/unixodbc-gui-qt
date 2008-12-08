#ifndef ODBCMODELSYSTEM_H
#define ODBCMODELSYSTEM_H

#include "ODBCModel.h"
#include "ODBCModelDrivers.h"

/*!
 * \class   ODBCModelSystem
 * \brief   This model encapsulates the entire ODBC system - including 
 *          the system information related to installing and configuring
 *          ODBC components such as drivers and data source names.
 * \author  pharvey (8/7/2008)
 */
class ODBCModelSystem : public ODBCModel
{
    Q_OBJECT
public:
    explicit ODBCModelSystem( ODBCQGSystem *pSystem );
    ~ODBCModelSystem();

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    QIcon           getIcon();
    ODBCQGSystem *  getSystem();

    bool doLoad();
    bool doClear();

private:
    ODBCMetaInfoAttr *  pSysAttr;
    ODBCQGSystem *      pSystem;
};

#endif


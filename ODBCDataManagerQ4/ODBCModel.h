/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef ODBCMODEL_H
#define ODBCMODEL_H

#include <QtGui>

#include <ODBCQGSystem.h>
#include <ODBCQGEnvironment.h>
#include <ODBCQGConnection.h>
#include "ODBCMetaInfo.h"
#include "ODBCValueCell.h"

/* declare a non-standard data type so we can have it pass to/from as QVariant */
Q_DECLARE_METATYPE(ODBCValueCell)

/*!
 *  \class  ODBCModel
 *
 *  \brief  This is the basis for our models. In our case... all of our principle objects are 
 *          models organized in a hierarchy. The hiearchy itself is used by \sa ODBCModelBrowser.
 *          ODBCModelBrowser will also use some of the features in each model such as; icon, text,
 *          and context menu. Each model can be provided to a view (ie an \sa ODBCViewProperties) 
 *          for viewing/editing the properties.
 */
class ODBCModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ODBCModel( ODBCModel *pmodelParent = 0 );
    virtual ~ODBCModel();

    int rowCount ( const QModelIndex &indexParent = QModelIndex() ) const;
    int columnCount( const QModelIndex &indexParent = QModelIndex() ) const;
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

    virtual void setText( const QString &stringText );

    virtual QString             getText();
    virtual QIcon               getIcon() = 0;
    virtual ODBCQGSystem *      getSystem();
    virtual ODBCQGEnvironment * getEnvironment();
    virtual ODBCQGConnection *  getConnection();

    virtual bool doLoad() = 0;   // load children    
    virtual bool doClear() = 0;  // clear children (presumably for a refresh/reload)    
    virtual void doContextMenu( QWidget *pwidgetParent, QPoint pos ) {;}

    virtual bool isLoaded() { return bLoaded; }


protected:
    bool    bLoaded;        // support for lazy loading
    int     nRows;          // default is 0; derived classes need to set to number of properties
    int     nColumns;       // default is 2; 0=Name, 1=Value
};

#endif


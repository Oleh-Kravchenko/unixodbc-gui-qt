#include "ODBCModelSystem.h"

#include "ODBC64.xpm"

ODBCModelSystem::ODBCModelSystem( ODBCQGSystem *pSystem )
    : ODBCModel()
{
    this->pSystem = pSystem;
    pSysAttr    = ODBCMetaInfo::getSysAttr();
    nRows       = ODBCMetaInfo::getCount( pSysAttr ); // just attr but perhaps add number of active connections row

    setObjectName( "System" );
}

ODBCModelSystem::~ODBCModelSystem()
{
}

QVariant ODBCModelSystem::data( const QModelIndex &index, int nRole ) const
{
    if ( index.row() < 0 || index.row() >= nRows )
        return QVariant();

    // get metainfo regarding the attribute we are working on...
    ODBCMetaInfoAttr *pAttr = &(pSysAttr[ index.row() ]);

    /* Name column... */
    if ( index.column() == 0 )
    {
        switch ( nRole )
        {
            case Qt::DisplayRole:
                return pAttr->pszCasualName;
        }
    }

    /* Value column... */
    return QVariant();
}

bool ODBCModelSystem::setData( const QModelIndex &index, const QVariant &variantValue, int nRole )
{
    if ( !index.isValid() )
        return false;

    if ( index.column() != 1 )
        return false;

    if ( index.row() < 0 || index.row() >= nRows )
        return false;

    if ( nRole == Qt::EditRole )
    {
        emit dataChanged( index, index );
        return true;
    }

    return false;
}

QIcon ODBCModelSystem::getIcon()
{
    return QIcon( xpmODBC64 );
}

ODBCQGSystem *ODBCModelSystem::getSystem()
{
    return pSystem;
}

bool ODBCModelSystem::doLoad()
{
    new ODBCModelDrivers( this );
    bLoaded = true;
    return true;
}

bool ODBCModelSystem::doClear()
{
    bLoaded = false;
    return true;
}



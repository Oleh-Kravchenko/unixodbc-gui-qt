#include "ODBCVariant.h"

ODBCVariant::ODBCVariant( Types n )
{
    nType       = n;
    nElements   = 0;
    nElementsMax= 0;
    pBuffer     = NULL;
}

ODBCVariant::~ODBCVariant()
{
    if ( pBuffer ) free( pBuffer );
}

bool ODBCVariant::setElements( SQLLEN n )
{
    // expand buffer?
    if ( n > nElementsMax && !setElementsMax( n ) )
        return false;

// printf( "[PAH][%s][%d][%s] nElements=%d n=%d\n", __FILE__, __LINE__, __FUNCTION__, nElements, n );
    nElements = n;

    return true;
}

bool ODBCVariant::setElementsMax( SQLLEN n )
{
    bool bReturn = true;

    switch ( nType )
    {
        case WideChar:
            {
                if ( n )
                {
                    SQLWCHAR *p = (SQLWCHAR*)realloc( pBuffer, n * getElementBytes( nType ) );
                    if ( p )
                    {
                        nElementsMax = n;
                        pBuffer = p;
                    }
                    else
                        bReturn = false;
                }
                else if ( pBuffer )
                {
                    free( pBuffer );
                    pBuffer = NULL;
                    nElementsMax = 0;
                }
            }
            break;
        case Char:
            {
                if ( n )
                {
                    SQLCHAR *p = (SQLCHAR*)realloc( pBuffer, n * getElementBytes( nType ) );
                    if ( p )
                    {
                        nElementsMax = n;
                        pBuffer = p;
                    }
                    else
                        bReturn = false;
                }
                else if ( pBuffer )
                {
                    free( pBuffer );
                    pBuffer = NULL;
                    nElementsMax = 0;
                }
            }
            break;
    }

    // adjust nElements (data truncated)?
    if ( nElements > nElementsMax )
        nElements = nElementsMax;

    return bReturn;
}

void ODBCVariant::setValue( SQLWCHAR *pwsz )
{
}

void ODBCVariant::setValue( SQLCHAR *psz )
{
}

void ODBCVariant::setValue( SQLLEN nIndex, SQLWCHAR c )
{
}

void ODBCVariant::setValue( SQLLEN nIndex, SQLCHAR c )
{
}

ODBCVariant &ODBCVariant::operator=( const ODBCVariant &v )
{
    nType           = v.nType;
    nElements       = 0;
    nElementsMax    = 0;

    if ( setElementsMax( v.nElementsMax ) )
    {
        nElements = v.nElements;
        if ( nElements )
            memcpy( pBuffer, v.pBuffer, nElements * getElementBytes( nType ) );
    }

    return *this;
}

SQLLEN ODBCVariant::getElementBytes( Types n )
{
    switch ( n )
    {
        case WideChar:
            return sizeof(SQLWCHAR);
        case Char:
            return sizeof(SQLCHAR);
    }

    return 1;
}


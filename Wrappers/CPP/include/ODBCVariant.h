#ifndef ODBCVARIANT_H
#define ODBCVARIANT_H

#include "ODBC.h"

/*!
 * \class   ODBCVariant
 * \brief   Our universal data type.
 * 
 *          This type manages a single element of an intrinsic type or arrays of an intrinsic type. By doing both
 *          we cover the bits of functionality we need from; dynamic arrays, strings, and simple variants
 *          in one class. This variant type has been created to assist calling \sa ODBCStatement::doData.
 *
 * \author  pharvey (8/25/2008)
 */
class ODBCVariant
{
public:
    enum Types
    {
        WideChar    = SQL_C_WCHAR,
        Char        = SQL_C_CHAR
    };

    explicit ODBCVariant( Types n );
    virtual ~ODBCVariant();

    bool setElements( SQLLEN n );                   // sets the number of valid elements (will expand ElementsMax as needed)
    bool setElementsMax( SQLLEN n );                // max number of elements of Type (ie number of chars for WideChar or Char types) which can be stored in buffer
    void setValue( SQLWCHAR *pwsz );                // loads buffer with wide-char data (ElementsMax will expand as needed)
    void setValue( SQLCHAR *psz );                  // loads buffer with char data (ElementsMax will expand as needed)
    void setValue( SQLLEN nIndex, SQLWCHAR c );     // sets, 0-based, nIndex in buffer to given char (Elements & ElementsMax will expand as needed)
    void setValue( SQLLEN nIndex, SQLCHAR c );      // sets, 0-based, nIndex in buffer to given char (Elements & ElementsMax will expand as needed)

    Types           getType() { return nType; }
    SQLPOINTER      getBuffer() { return pBuffer; }             // buffer pointer (will be invalid if buffer size altered for any reason)
    SQLLEN          getElements() { return nElements; }         // number of elements of Type (ie number of chars for WideChar or Char types)
    SQLLEN          getElementsMax() { return nElementsMax; }   // max number of elements of Type (ie number of chars for WideChar or Char types) which can be stored in buffer
    static SQLLEN   getElementBytes( Types n );                 // size of (as in bytes) of a single, intrinsic, data element of nType

    void clear() { nElements = 0; }                 
    bool isNull() { return ( nElements ? false : true ); }

    ODBCVariant &operator=( const ODBCVariant &v );

protected:
    Types           nType;              // type data in pBuffer
    SQLLEN          nElements;          // number of valid elements in pBuffer (we are Null if 0)
    SQLLEN          nElementsMax;       // max number of elements we can store in pBuffer
    SQLPOINTER      pBuffer;            // buffer where we store our data (is big enough for nElementsMax)
};

#endif


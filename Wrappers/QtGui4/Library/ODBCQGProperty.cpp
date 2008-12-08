/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#include "../include/ODBCQGProperty.h"

ODBCQGProperty::ODBCQGProperty()
{
    nPromptType = PromptLabel;
}

ODBCQGProperty::ODBCQGProperty( PromptType nPromptType, const QString &stringName )
{
    this->nPromptType     = nPromptType;
    this->stringName      = stringName;
}

ODBCQGProperty::~ODBCQGProperty()
{
}

void ODBCQGProperty::setValue( const QString &stringValue ) 
{ 
    this->stringValue = stringValue; 

//    uint n0 = 0;
//    uint n1 = listOptions.findIndex( stringValue );
}



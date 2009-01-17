/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "../include/OQGProperty.h"

OQGProperty::OQGProperty()
{
    nPromptType = PromptLabel;
}

OQGProperty::OQGProperty( PromptType nPromptType, const QString &stringName )
{
    this->nPromptType     = nPromptType;
    this->stringName      = stringName;
}

OQGProperty::~OQGProperty()
{
}

void OQGProperty::setValue( const QString &stringValue ) 
{ 
    this->stringValue = stringValue; 

//    uint n0 = 0;
//    uint n1 = listOptions.findIndex( stringValue );
}



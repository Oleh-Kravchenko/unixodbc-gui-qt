/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGPROPERTY_h
#define OQGPROPERTY_h

//
#include <QtGui>

class OQGProperty
{
public:

    enum PromptType 
	{ 
		PromptLabel, 
		PromptLineEdit, 
		PromptCombo, 
		PromptComboWrite, 
		PromptCheck 
	};

    OQGProperty();
    OQGProperty( PromptType nPromptType, const QString &stringName );
    virtual ~OQGProperty();

    // SETTERS
    void setName( const QString &stringName ) { this->stringName = stringName; }
    void setHelp( const QString &stringHelp ) { this->stringHelp = stringHelp; }
    void setOptions( const QString &stringOption ) { listOptions.append( stringOption ); }
    void setValue( int nValue ) { this->stringValue = QString::number( nValue ); }
    void setValue( const QString &stringValue );

    // GETTERS
    QString getName() { return stringName; }
    QString getValue() { return stringValue; }
    QStringList getOptions() { return listOptions; }
    QString getHelp() { return stringHelp; }
    PromptType getPromptType() { return nPromptType; }


protected:
    PromptType      nPromptType;

    // current state
    QString         stringName;
    QString         stringValue;

    QString         stringHelp;
    QStringList     listOptions;
};

#endif


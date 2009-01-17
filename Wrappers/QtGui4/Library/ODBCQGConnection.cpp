/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#include "../include/OQGEnvironment.h"
#include "../include/OQGConnection.h"
#include "../include/OQGPropertiesDialog.h"
#include "../include/OQGProperty.h"
#include "../include/OQGLogin.h"

OQGConnection::OQGConnection( OQGEnvironment *pEnvironment )
    : OQConnection( pEnvironment )
{
    bPromptDriver           = true;
    bPromptDataSourceName   = true;
    bPromptUserID           = true;
    bPromptPassword         = true;
}

/*!
    doConnect
    
    Allows the use of QString instead of SQLCHAR*.
    
    OQG will provide a login dialog.
*/
bool OQGConnection::doConnect( QWidget *pwidgetParent, const QString &stringDSN, const QString &stringUID, const QString &stringPWD )
{
    bool bReturn = false;

    // With Prompting.
    OQGLogin *plogin = new OQGLogin( pwidgetParent, (OQGEnvironment*)getEnvironment() );
    plogin->setWindowTitle( tr( "Connect..." ) );
    plogin->setShowDriver( false );
    bool bPromptSomething = bPromptDataSourceName || bPromptUserID || bPromptPassword;
    if ( !bPromptDataSourceName ) plogin->setShowDataSourceName( false );
    if ( !bPromptUserID ) plogin->setShowUserID( false );
    if ( !bPromptPassword ) plogin->setShowPassword( false );
    if ( !stringDSN.isNull() )
        plogin->setDataSourceName( stringDSN );
    if ( !stringUID.isNull() )
        plogin->setUserID( stringUID );
    if ( ! stringPWD.isNull() )
        plogin->setPassword( stringPWD );
    while ( 1 )
    {
        if ( !bPromptSomething || (plogin->exec() == QDialog::Accepted) ) 
        {
            SQLRETURN nReturn = OQConnection::doConnect( plogin->getDataSourceName(), plogin->getUserID(), plogin->getPassword() );
            if ( SQL_SUCCEEDED( nReturn ) )
            {
                bReturn = true;
                break;
            }
            else
            {
                // if login failed - prompt for all
                plogin->setShowDataSourceName( true );
                plogin->setShowUserID( true );
                plogin->setShowPassword( true );
                bPromptSomething = true;
                QMessageBox::warning( pwidgetParent, objectName(),  tr( "failed to connect" ) ); 
            }
        }
        else
            break;
    }
    delete plogin;

    return bReturn;
}

/*!
    doBrowseConnect
    
    This method assumes that we have been given one of the following in stringConnect;
    
        "DRIVER=drivername"
        "DSN=dsnname"
        "FILEDSN=filename"

    Other connect options may be included.
    
    Call doBrowseConnect( QWidget * ) if you want OQG to prompt for the above 
    connect options as well.
            
    stringConnect is used to start the browse connect process.
    
    This method will use OQG based prompting as required.
*/
bool OQGConnection::doBrowseConnect( QWidget *pwidgetParent, const QString &stringConnect )
{
    bool        bReturn     = false;
    SQLRETURN   nReturn     = SQL_NEED_DATA;
    QString     stringIn    = stringConnect;
    QString     stringOut   = "";

    while ( nReturn == SQL_NEED_DATA )
    {
        nReturn = OQConnection::doBrowseConnect( stringIn, &stringOut );
        switch ( nReturn )
        {
            case SQL_SUCCESS:
            case SQL_SUCCESS_WITH_INFO:
                bReturn = true;
                break;
            case SQL_NEED_DATA:
                {
                    OQGPropertiesDialog propertiesdialog( getProperties( stringOut ), pwidgetParent );
                    // prepare new stringIn
                    if ( propertiesdialog.exec() == QDialog::Accepted )
                    {
                        stringIn = getString( propertiesdialog.getProperties() );
                    }
                    // handle cancel
                    else
                        nReturn = SQL_ERROR;
                }
                break;
            case SQL_ERROR:
            case SQL_INVALID_HANDLE:
            default:
                break;
        }
    }

    return bReturn;
}

/*!
    doBrowseConnect
    
    This method will prompt for Driver/DSN/FileDSN before starting the regular 
    browse connect process.

    This method will use OQG based prompting.
*/
bool OQGConnection::doBrowseConnect( QWidget *pwidgetParent )
{
    bool bReturn = false;
    
    OQGLogin *plogin = new OQGLogin( pwidgetParent, (OQGEnvironment*)getEnvironment() );
    plogin->setWindowTitle( tr( "Browse Connect..." ) );
    while ( 1 )
    {
        if ( plogin->exec() == QDialog::Accepted ) 
        {
            QString stringConnection;
            QString stringDriver            = plogin->getDriver();
            QString stringDataSourceName    = plogin->getDataSourceName();
            QString stringUserID            = plogin->getUserID();
            QString stringPassword          = plogin->getPassword();

            if ( stringDriver.isEmpty() && stringDataSourceName.isEmpty() )
                QMessageBox::warning( pwidgetParent, objectName(), tr( "please select a Driver or Data Source Name" ) ); 
            else
            {
                delete plogin;

                if ( !stringDriver.isEmpty() )
                    stringConnection += "DRIVER=" + stringDriver + ";";
//                if ( !stringFileDataSourceName.isEmpty() )
//                    stringConnection += "FILEDSN=" + stringFileDataSourceName + ";";
                if ( !stringDataSourceName.isEmpty() )
                    stringConnection += "DSN=" + stringDataSourceName + ";";
                if ( !stringUserID.isEmpty() )
                    stringConnection += "UID=" + stringUserID + ";";
                if ( !stringPassword.isEmpty() )
                    stringConnection += "PWD=" + stringPassword + ";";

                return doBrowseConnect( pwidgetParent, stringConnection );
            }
        }
        else
        {
            delete plogin;
            break;
        }
    }

    return bReturn;
}

/*!
    getString
    
    Return a string list suitable for an *input* connection string for a browse connect.
    
    A browse request connection string has the following syntax:
    
    connection-string ::= attribute[;] | attribute; connection-string
    attribute ::= attribute-keyword=attribute-value | DRIVER=[{]attribute-value[}]
    attribute-keyword ::= DSN | UID | PWD
              | driver-defined-attribute-keyword
    attribute-value ::= character-string
    driver-defined-attribute-keyword ::= identifier
    
    where character-string has zero or more characters; identifier has one or more characters; 
    attribute-keyword is not case-sensitive; attribute-value may be case-sensitive; and the 
    value of the DSN keyword does not consist solely of blanks. Because of connection string 
    and initialization file grammar, keywords and attribute values that contain the characters 
    []{}(),;?*=!@ should be avoided. Because of the grammar in the system information, 
    keywords and data source names cannot contain the backslash (\) character. For an ODBC 
    2.x driver, braces are required around the attribute value for the DRIVER keyword.
    
    If any keywords are repeated in the browse request connection string, the driver uses the 
    value associated with the first occurrence of the keyword. If the DSN and DRIVER keywords 
    are included in the same browse request connection string, the Driver Manager and driver 
    use whichever keyword appears first.
    
    For information about how an application chooses a data source or driver, see 
    "Choosing a Data Source or Driver" in Chapter 6: Connecting to a Data Source or Driver.
*/
QString OQGConnection::getString( QVector<OQGProperty> vectorProperties )
{
    QString stringReturn;
    int     nPrompt           = 0;
    int     nPrompts          = vectorProperties.count();

    for ( ; nPrompt < nPrompts; nPrompt++ )
    {
        OQGProperty property = vectorProperties.at( nPrompt );
        stringReturn    += property.getName() + "=";
        stringReturn    += property.getValue() + ";";
    }

    return stringReturn;
}

/*!
    getPromptList
    
    Return a list of prompts based upon a string list returned from a browse connect call.
    
    The browse result connection string is a list of connection attributes. A connection attribute 
    consists of an attribute keyword and a corresponding attribute value. The browse result 
    connection string has the following syntax:
    
    connection-string ::= attribute[;] | attribute; connection-string
    attribute ::= [*]attribute-keyword=attribute-value
    attribute-keyword ::= ODBC-attribute-keyword
              | driver-defined-attribute-keyword
    ODBC-attribute-keyword = {UID | PWD}[:localized-identifier]
    driver-defined-attribute-keyword ::= identifier[:localized-identifier]
    attribute-value ::= {attribute-value-list} | ?
    (The braces are literal; they are returned by the driver.)
    attribute-value-list ::= character-string [:localized-character string] | character-string 
    [:localized-character string], attribute-value-list
    
    where character-string and localized-character string have zero or more characters; 
    identifier and localized-identifier have one or more characters; attribute-keyword is not 
    case-sensitive; and attribute-value may be case-sensitive. Because of connection string and 
    initialization file grammar, keywords, localized identifiers, and attribute values that 
    contain the characters []{}(),;?*=!@ should be avoided. Because of the grammar in the system 
    information, keywords and data source names cannot contain the backslash (\) character.
    
    The browse result connection string syntax is used according to the following semantic rules:
    
        * If an asterisk (*) precedes an attribute-keyword, the attribute is optional and can be 
          omitted in the next call to SQLBrowseConnect.
        * The attribute keywords UID and PWD have the same meaning as defined in SQLDriverConnect.
        * A driver-defined-attribute-keyword names the kind of attribute for which an attribute 
          value may be supplied. For example, it might be SERVER, DATABASE, HOST, or DBMS.
        * ODBC-attribute-keywords and driver-defined-attribute-keywords include a localized or 
          user-friendly version of the keyword. This might be used by applications as a label in a 
          dialog box. However, UID, PWD, or the identifier alone must be used when passing a browse 
          request string to the driver.
        * The {attribute-value-list} is an enumeration of actual values valid for the corresponding 
          attribute-keyword. Note that the braces ({}) do not indicate a list of choices; they are 
          returned by the driver. For example, it might be a list of server names or a list of database 
          names.
        * If the attribute-value is a single question mark (?), a single value corresponds to the 
          attribute-keyword. For example, UID=JohnS; PWD=Sesame.
        * Each call to SQLBrowseConnect returns only the information required to satisfy the next 
          level of the connection process. The driver associates state information with the 
          connection handle so that the context can always be determined on each call.

*/
QVector<OQGProperty> OQGConnection::getProperties( const QString &stringProperties )
{
    QVector<OQGProperty> vectorProperties;
    
    QStringList stringlistProperties = stringProperties.split( ';' );

    for ( QStringList::Iterator it = stringlistProperties.begin(); it != stringlistProperties.end(); ++it ) 
    {
        QStringList stringlistProperty = (*it).split( ':' );
        if ( stringlistProperty.count() > 0 )
        {
            OQGProperty property( OQGProperty::PromptLineEdit, stringlistProperty[0] );
            if ( stringlistProperty.count() > 1 )
                property.setValue( stringlistProperty[1] );
            vectorProperties.append( property );
        }
    }

    return vectorProperties;
}


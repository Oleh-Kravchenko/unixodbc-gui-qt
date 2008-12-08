/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGLOGIN_H
#define ODBCQGLOGIN_H

//
#include <sys/types.h>

// Qt
#include <QtGui>

//
#ifndef Q_WS_WIN
#include <unistd.h>
#include <pwd.h>
#endif

//
class ODBCQGEnvironment;
class ODBCMessage;
class ODBCQGMessageOutput;

class ODBCQGLogin: public QDialog
{
	Q_OBJECT
public:
    ODBCQGLogin( QWidget *pwidgetParent, ODBCQGEnvironment *penvironment );
    ~ODBCQGLogin();

    // SETTERS
    virtual void setShowDriver( bool b );
    virtual void setShowDataSourceName( bool b );
    virtual void setShowUserID( bool b );
    virtual void setShowPassword( bool b );
    virtual void setDriver( const QString &string );
    virtual void setDataSourceName( const QString &string );
    virtual void setUserID( const QString &string );
    virtual void setPassword( const QString &string );

    // GETTERS
    QString getDriver() { return pcomboboxDriver->currentText(); }
    QString getDataSourceName() { return pcomboboxDataSourceName->currentText(); }
    QString getUserID() { return plineeditUserID->text(); }
    QString getPassword() { return plineeditPassword->text(); }

protected:
    ODBCQGEnvironment*      penvironment;
    QLabel *                plabelDriver;
    QComboBox *             pcomboboxDriver;
    QLabel *                plabelDataSourceName;
    QComboBox *             pcomboboxDataSourceName;
    QLabel *                plabelUserID;
	QLineEdit *             plineeditUserID;
    QLabel *                plabelPassword;
	QLineEdit *             plineeditPassword;
    ODBCQGMessageOutput *   pmessageoutput;

    virtual void loadDrivers();
    virtual void loadDataSourceNames();
};

#endif


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2003-2008, LGPL
 */
#ifndef ODBCQGMESSAGEOUTPUT_h
#define ODBCQGMESSAGEOUTPUT_h

// Qt
#include <QtGui>

//
#include <ODBCMessage.h>
#include <ODBCDiagnostic.h>

class ODBCQGMessageOutput: public QTableWidget
{
	Q_OBJECT
public:
    ODBCQGMessageOutput( QWidget *pwidgetParent );
    ~ODBCQGMessageOutput();

    // SETTERS
    virtual void setWaitingMessages( int n );

    // GETTERS
    virtual int getWaitingMessages() { return nWaitingMessages; }

signals:
    void signalWaitingMessages( ODBCQGMessageOutput * );

public slots:
    virtual void slotMessage( ODBCMessage Message );
    virtual void slotDiagnostic( ODBCDiagnostic Diagnostic );

protected:
    int nWaitingMessages;
};

#endif


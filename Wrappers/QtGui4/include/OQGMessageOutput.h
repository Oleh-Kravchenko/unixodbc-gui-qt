/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2003-2009, LGPL
 */
#ifndef OQGMESSAGEOUTPUT_h
#define OQGMESSAGEOUTPUT_h

// Qt
#include <QtGui>

//
#include <OQMessage.h>
#include <OQDiagnostic.h>

class OQGMessageOutput: public QTableWidget
{
	Q_OBJECT
public:
    OQGMessageOutput( QWidget *pwidgetParent );
    ~OQGMessageOutput();

    // SETTERS
    virtual void setWaitingMessages( int n );

    // GETTERS
    virtual int getWaitingMessages() { return nWaitingMessages; }

signals:
    void signalWaitingMessages( OQGMessageOutput * );

public slots:
    virtual void slotMessage( OQMessage Message );
    virtual void slotDiagnostic( OQDiagnostic Diagnostic );

protected:
    int nWaitingMessages;
};

#endif


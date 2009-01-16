/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#ifndef CMONITOR_H
#define CMONITOR_H

#include "CODBCInst.h"

#define ODBC_HELP_MONITOR "unixODBC is unique in that it provides a rich means of monitoring ODBC activity."

class CMonitorHandleCounts;
class CMonitorProcesses;

/*! 
 * \class   CMonitor
 * \brief   Monitor widget for tabs/property pages.
 * 
 *          This widget shows stats such as how many handles are in use.
 *
 *          This widget is used by the CODBCConfig tab/property widgets.
 *
 */
class CMonitor : public QTabWidget
{
	Q_OBJECT
public:
	CMonitor( QWidget* pwidgetParent = NULL );
	virtual ~CMonitor();

    QString windowHelp() { return QString( tr( ODBC_HELP_MONITOR ) ); }
    bool saveData() { return true; }

protected:
    CMonitorHandleCounts *  pMonitorHandleCounts;
    CMonitorProcesses *     pMonitorProcesses;
};

#endif


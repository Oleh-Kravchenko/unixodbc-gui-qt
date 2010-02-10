/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2009
 * \license Copyright unixODBC-GUI-Qt Project 2009-2010, LGPL
 */
#ifndef CDRIVERCONNECTPROMPT_H
#define CDRIVERCONNECTPROMPT_H

#include "CManageDataSourceNames.h"

#include <QDialog>

/*! 
 * \class   CDriverConnectPrompt
 *
 * \brief   Prompt for a Data Source Name (File, User, or System). 
 *
 *          This dialog supports the SQLDriverConnect() call. This
 *          is needed when an application calls SQLDriverConnect() with
 *          an empty connect string.
 * 
 * \sa      ODBCDriverConnectPrompt
 *          unixODBC::DriverManager::SQLDriverConnect
 *          unixODBC::DriverManager::SQLDriverConnectPrompt
 */
class CDriverConnectPrompt : public QDialog
{
    Q_OBJECT
public:
    CDriverConnectPrompt( SQLCHAR *pszDataSourceName, SQLSMALLINT nMaxChars, QWidget *pwidgetParent = 0 );
    virtual ~CDriverConnectPrompt();

protected slots:
    void slotAccept();

protected:
    SQLCHAR *               pszDataSourceName;
    SQLSMALLINT             nMaxChars;
    CManageDataSourceNames *pManageDataSourceNames;

    void loadState();
    void saveState();

};

#endif


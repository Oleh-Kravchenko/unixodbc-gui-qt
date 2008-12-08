/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#ifndef CPAGE_H
#define CPAGE_H

#include "CODBCInst.h"

class CPage : public QWidget
{
public:
    CPage( QWidget* pwidgetParent, const QString &stringTitle, QWidget *pwidgetContent, const QIcon &icon, const QString &stringHelp );
    virtual ~CPage();

    QWidget *getContent() { return pwidgetContent; }

protected:
    QWidget *pwidgetContent;
};

#endif


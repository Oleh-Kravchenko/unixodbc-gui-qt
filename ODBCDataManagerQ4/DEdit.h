/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DEDIT_H
#define DEDIT_H

#include <QtGui>

#include "DNode.h"

class DEdit : public QWidget
{
    Q_OBJECT
public: 
    DEdit( QWidget *pwidgetParent, DNode *pNode );

    virtual void setActionSubmit( QAction * );

protected:
    DNode *pNode;
};


#endif


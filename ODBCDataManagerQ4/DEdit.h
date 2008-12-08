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


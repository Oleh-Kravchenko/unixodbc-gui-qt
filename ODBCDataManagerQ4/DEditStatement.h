/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DEDITSTATEMENT_H
#define DEDITSTATEMENT_H

#include <QtGui>

#include "DEdit.h"
#include "DNodeStatement.h"

class DEditStatement : public DEdit
{
    Q_OBJECT
public: 
    DEditStatement( QWidget *pwidgetParent, DNodeStatement *pNode );

    void setActionSubmit( QAction *pactionSubmit );

    static QString getStringData( SQLHANDLE hStmt, int nColumn, int nSize, bool bUnicode = false );

public slots:
    void slotSubmit();

private:
    QSplitter *     pSplitter;
    QTextEdit *     pTextEdit;
    QTableWidget *  pTableWidget;
};

#endif


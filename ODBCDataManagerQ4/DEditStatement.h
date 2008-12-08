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


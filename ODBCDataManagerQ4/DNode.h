/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef DNODE_H
#define DNODE_H

#include <QtGui>

#include <sqlext.h>
#include <odbcinstext.h>
// #include <ini.h>

#include <ODBCString.h>

#include "DDiagnostic.h"

class DNodeWidget;
class DPropWidget;

/*! 
 * \brief   Base class for all nodes.
 *
 *          All ODBC information can be represented in hierarchial form. Each node of that
 *          hierarchy is derived from DNode.
 */
class DNode : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    DNode( DNodeWidget *pNodeWidget );
    DNode( DNodeWidget *pNodeWidget, DNode *pNode );
    virtual ~DNode();

    virtual SQLHENV getEnvironment();
    virtual SQLHDBC getConnection();

    virtual void doLoadToolBar( QToolBar *pToolBar ) {}
    virtual void doClearToolBar( QToolBar *pToolBar ) {}
    virtual void doLoadProperties( DPropWidget *pPropWidget ) {}
    virtual void doClearProperties( DPropWidget *pPropWidget ) {}
    virtual void doLoad() = 0;
    virtual void doClear() = 0;
    virtual void doDiagnosticClearSignal();
    virtual void doDiagnosticSignal( DDiagnostic d );

signals:
    void signalDiagnosticClear();
    void signalDiagnostic( DDiagnostic d );

protected:
    QWidget *getEditorParent();

    DNodeWidget *pNodeWidget;
};

#endif


/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DNodeStatement.h"

#include "DEditStatement.h"
#include "DNodeAttribute.h"
#include "DPropWidget.h"
#include "DNodeWidget.h"

#include "Remove32.xpm"
#include "SQL48.xpm"

DNodeStatement::DNodeStatement( DNodeWidget *pNodeWidget, DNodeConnection *pNode )
    : DNode( pNodeWidget, pNode )
{
    hStmt = 0;

    setIcon( 0, QIcon( xpmSQL48 ) );
    setText( 0, "Statement" );

    pactionRemove = new QAction( QIcon( xpmRemove32 ), "Remove", 0 );
    connect( pactionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()) );

    setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicatorWhenChildless );

    // create editor...
    QWidget *pwidgetEditorParent = getEditorParent();
    pEditStatement = new DEditStatement( pwidgetEditorParent, this );
    if ( pwidgetEditorParent && pwidgetEditorParent->inherits( "QMdiArea" ) )
        ((QMdiArea*)pwidgetEditorParent)->addSubWindow( pEditStatement );
    pEditStatement->show();
}

DNodeStatement::~DNodeStatement()
{
    if ( pEditStatement )
        delete pEditStatement;

    if ( hStmt )
        SQLFreeHandle( SQL_HANDLE_STMT, hStmt );

    delete pactionRemove;
}

SQLHSTMT DNodeStatement::getStatement()
{
    isAllocated( true );
    return hStmt;
}

void DNodeStatement::doLoadToolBar( QToolBar *pToolBar )
{
    pToolBar->addAction( pactionRemove );
}

void DNodeStatement::doClearToolBar( QToolBar *pToolBar )
{
    pToolBar->removeAction( pactionRemove );
}

bool DNodeStatement::isAllocated( bool bEnsure )
{
    if ( hStmt )
        return true;

    if ( bEnsure )
    {
        SQLRETURN nReturn = SQLAllocHandle( SQL_HANDLE_STMT, getConnection(), &hStmt );
        if ( nReturn != SQL_SUCCESS )
            doDiagnosticSignal( DDiagnostic( SQL_HANDLE_DBC, getConnection() ) );
        if ( SQL_SUCCEEDED( nReturn ) )
            return true;
    }

    return false;
}

void DNodeStatement::slotRemove()
{
    delete this;
}

void DNodeStatement::doLoadProperties( DPropWidget *pPropWidget )
{
    doDiagnosticClearSignal();

    if ( !isAllocated( true ) )
        return;

    SQLRETURN       nReturn;
    DNodeAttribute *p;
    SQLUINTEGER     nUnsignedInteger;
    SQLUINTEGER *   pnUnsignedInteger;
    SQLINTEGER      nInteger;
    char            sz[256];
    SQLPOINTER      pPointer;
    SQLULEN         nULen;
    SQLLEN *        pnLen;
    SQLULEN *       pnULen;
    SQLUSMALLINT *  pnUnsignedSmallInteger;

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_APP_PARAM_DESC, &pPointer, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_APP_PARAM_DESC", QString::number( (long)pPointer ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_APP_ROW_DESC, &pPointer, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_APP_ROW_DESC", QString::number( (long)pPointer ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ASYNC_ENABLE, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ASYNC_ENABLE", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_CONCURRENCY, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CONCURRENCY", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_CURSOR_SCROLLABLE, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURSOR_SCROLLABLE", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_CURSOR_SENSITIVITY, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURSOR_SENSITIVITY", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_CURSOR_TYPE, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_CURSOR_TYPE", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ENABLE_AUTO_IPD, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ENABLE_AUTO_IPD", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_FETCH_BOOKMARK_PTR, &pnLen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_FETCH_BOOKMARK_PTR", QString::number( (long)pnLen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_IMP_PARAM_DESC, &pPointer, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_IMP_PARAM_DESC", QString::number( (long)pPointer ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_IMP_ROW_DESC, &pPointer, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_IMP_ROW_DESC", QString::number( (long)pPointer ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_KEYSET_SIZE, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_KEYSET_SIZE", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_MAX_LENGTH, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_MAX_LENGTH", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_MAX_ROWS, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_MAX_ROWS", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_METADATA_ID, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_METADATA_ID", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_NOSCAN, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_NOSCAN", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAM_BIND_OFFSET_PTR, &pnULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAM_BIND_OFFSET_PTR", QString::number( (long)pnULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAM_BIND_TYPE, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAM_BIND_TYPE", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAM_OPERATION_PTR, &pnUnsignedSmallInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAM_OPERATION_PTR", QString::number( (long)pnUnsignedSmallInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAM_STATUS_PTR, &pnUnsignedSmallInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAM_STATUS_PTR", QString::number( (long)pnUnsignedSmallInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &pnULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAMS_PROCESSED_PTR", QString::number( (long)pnULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_PARAMSET_SIZE, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_PARAMSET_SIZE", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_QUERY_TIMEOUT, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_QUERY_TIMEOUT", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_RETRIEVE_DATA, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_RETRIEVE_DATA", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_ARRAY_SIZE, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_ARRAY_SIZE", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_BIND_OFFSET_PTR, &pnULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_BIND_OFFSET_PTR", QString::number( (long)pnULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_BIND_TYPE, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_BIND_TYPE", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_NUMBER, &nULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_NUMBER", QString::number( nULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_OPERATION_PTR, &pnUnsignedSmallInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_OPERATION_PTR", QString::number( (long)pnUnsignedSmallInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROW_STATUS_PTR, &pnUnsignedSmallInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROW_STATUS_PTR", QString::number( (long)pnUnsignedSmallInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_ROWS_FETCHED_PTR, &pnULen, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_ROWS_FETCHED_PTR", QString::number( (long)pnULen ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_SIMULATE_CURSOR, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_SIMULATE_CURSOR", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

    nReturn = SQLGetStmtAttr( hStmt, SQL_ATTR_USE_BOOKMARKS, &nUnsignedInteger, 0, 0 ); 
    p = new DNodeAttribute( pPropWidget->getNodeWidget(), "SQL_ATTR_USE_BOOKMARKS", QString::number( nUnsignedInteger ) );
    p->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
}

void DNodeStatement::doClearProperties( DPropWidget *pPropWidget )
{
    pPropWidget->getNodeWidget()->clear();
}



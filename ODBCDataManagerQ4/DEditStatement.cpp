/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DEditStatement.h"

DEditStatement::DEditStatement( QWidget *pwidgetParent, DNodeStatement *pNode )
    : DEdit( pwidgetParent, pNode )
{
    QVBoxLayout *playoutMain = new QVBoxLayout;
    playoutMain->setSpacing( 0 );

    //
    pSplitter       = new QSplitter( Qt::Vertical, this );
    pTextEdit       = new QTextEdit( pSplitter );
    pTableWidget    = new QTableWidget( pSplitter );

    playoutMain->addWidget( pSplitter );
    pSplitter->addWidget( pTextEdit );
    pSplitter->addWidget( pTableWidget );

    //
    setLayout( playoutMain );
}

void DEditStatement::setActionSubmit( QAction *pactionSubmit )
{
    pactionSubmit->setEnabled( true );
    connect( pactionSubmit, SIGNAL(triggered()), this, SLOT(slotSubmit()) );
}

void DEditStatement::slotSubmit()
{
    // clear...
    pNode->doDiagnosticClearSignal();
    pTableWidget->setRowCount( 0 );
    pTableWidget->setColumnCount( 0 );

    // submit request to data source...
    DNodeStatement *    pNodeStatement  = (DNodeStatement*)pNode;
    SQLHSTMT            hStmt           = pNodeStatement->getStatement();
    QString             stringText      = pTextEdit->toPlainText();
#ifdef UNICODE
    SQLRETURN nReturn = SQLExecDirect( hStmt, (SQLWCHAR*)stringText.unicode(), (SQLINTEGER)stringText.length() );
#else
    QByteArray bytearrayText = stringText.toLocal8Bit();
    SQLRETURN nReturn = SQLExecDirect( hStmt, (SQLCHAR*)bytearrayText.constData(), (SQLINTEGER)bytearrayText.length() );
#endif
    if ( nReturn != SQL_SUCCESS )
    {
        pNode->doDiagnosticSignal( DDiagnostic( SQL_HANDLE_STMT, hStmt ) );
        if ( nReturn != SQL_SUCCESS_WITH_INFO )
            return;
    }

    // load table widget with results...
    SQLSMALLINT nColumns = 0;
    if ( SQLNumResultCols( hStmt, &nColumns ) != SQL_SUCCESS )
    {
        pNode->doDiagnosticSignal( DDiagnostic( SQL_HANDLE_STMT, hStmt ) );
        return;
    }

    pTableWidget->setColumnCount( nColumns );
    int nRow = 0;

//    while ( (nReturn = SQLFetchScroll( hStmt, SQL_FETCH_NEXT, 0 )) == SQL_SUCCESS )
    while ( (nReturn = SQLFetch( hStmt )) == SQL_SUCCESS )
    {
        pTableWidget->setRowCount( nRow + 1 );
        for ( SQLSMALLINT nColumn = 0; nColumn < nColumns; nColumn++ )
        {
            QString stringData = getStringData( hStmt, nColumn, -1 );
            pTableWidget->setItem( nRow, nColumn, new QTableWidgetItem( stringData ) );
        }
        nRow++;
    }
}

QString DEditStatement::getStringData( SQLHANDLE hStmt, int column, int colSize, bool unicode )
{
    QString fieldVal;
    SQLRETURN r = SQL_ERROR;
    SQLLEN lengthIndicator = 0;

    // NB! colSize must be a multiple of 2 for unicode enabled DBs
    if (colSize <= 0) {
        colSize = 256;
    } else if (colSize > 65536) { // limit buffer size to 64 KB
        colSize = 65536;
    } else {
        colSize++; // make sure there is room for more than the 0 termination
        if (unicode) {
            colSize *= 2; // a tiny bit faster, since it saves a SQLGetData() call
        }
    }
    char* buf = new char[colSize];
    while (true) {
        r = SQLGetData(hStmt,
                        column+1,
                        unicode ? SQL_C_WCHAR : SQL_C_CHAR,
                        (SQLPOINTER)buf,
                        colSize,
                        &lengthIndicator);
        if (r == SQL_SUCCESS || r == SQL_SUCCESS_WITH_INFO) {
            if (lengthIndicator == SQL_NULL_DATA || lengthIndicator == SQL_NO_TOTAL) {
                fieldVal = QString();
                break;
            }
            // if SQL_SUCCESS_WITH_INFO is returned, indicating that
            // more data can be fetched, the length indicator does NOT
            // contain the number of bytes returned - it contains the
            // total number of bytes that CAN be fetched
            // colSize-1: remove 0 termination when there is more data to fetch
            int rSize = (r == SQL_SUCCESS_WITH_INFO) ? (unicode ? colSize-2 : colSize-1) : lengthIndicator;
            if (unicode) {
                fieldVal += QString((QChar*) buf, rSize / 2);
            } else {
                buf[rSize] = 0;
                fieldVal += QString::fromAscii(buf);
            }
            if (lengthIndicator < colSize) {
                // workaround for Drivermanagers that don't return SQL_NO_DATA
                break;
            }
        } else if (r == SQL_NO_DATA) {
            break;
        } else {
            qWarning("qGetStringData: Error while fetching data (%d)", r);
            fieldVal = QString();
            break;
        }
    }
    delete[] buf;
    return fieldVal;
}


/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 **********************************************************************
 *
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "catalog.h"
#include "OdbcTest.h"

static attr_options get_type_options[] = 
{
    { "SQL_ALL_TYPES", SQL_ALL_TYPES, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_CHAR", SQL_CHAR, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_VARCHAR", SQL_VARCHAR, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_LONGVARCHAR", SQL_LONGVARCHAR, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DECIMAL", SQL_DECIMAL, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_NUMERIC", SQL_NUMERIC, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_SMALLINT", SQL_SMALLINT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTEGER", SQL_INTEGER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_REAL", SQL_REAL, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_FLOAT", SQL_FLOAT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DOUBLE", SQL_DOUBLE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_BIT", SQL_BIT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TINYINT", SQL_TINYINT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_BIGINT", SQL_BIGINT, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_BINARY", SQL_BINARY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_VARBINARY", SQL_VARBINARY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_LONGVARBINARY", SQL_LONGVARBINARY, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TYPE_DATE", SQL_TYPE_DATE, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DATE", SQL_DATE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TYPE_TIME", SQL_TYPE_TIME, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TIME", SQL_TIME, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TYPE_TIMESTAMP", SQL_TYPE_TIMESTAMP, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_TIMESTAMP", SQL_TIMESTAMP, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_MONTH", SQL_INTERVAL_MONTH, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_YEAR", SQL_INTERVAL_YEAR, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_YEAR_TO_MONTH", SQL_INTERVAL_YEAR_TO_MONTH, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_DAY", SQL_INTERVAL_DAY, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_HOUR", SQL_INTERVAL_HOUR, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_MINUTE", SQL_INTERVAL_MINUTE, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_SECOND", SQL_INTERVAL_SECOND, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_DAY_TO_HOUR", SQL_INTERVAL_DAY_TO_HOUR, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_DAY_TO_MINUTE", SQL_INTERVAL_DAY_TO_MINUTE, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_DAY_TO_SECOND", SQL_INTERVAL_DAY_TO_SECOND, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_HOUR_TO_MINUTE", SQL_INTERVAL_HOUR_TO_MINUTE, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INTERVAL_HOUR_TO_SECOND", SQL_INTERVAL_HOUR_TO_SECOND, 
        {
            { NULL, 0, NULL, 0}
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

static attr_options unique_options[ 3 ] = 
{
    { "SQL_INDEX_UNIQUE", SQL_INDEX_UNIQUE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_INDEX_ALL", SQL_INDEX_ALL, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

static attr_options reserved_options[ 3 ] = 
{
    { "SQL_QUICK", SQL_QUICK, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ENSURE", SQL_ENSURE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

static attr_options ident_options[ 3 ] = 
{
    { "SQL_BEST_ROWID", SQL_BEST_ROWID, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_ROWVER", SQL_ROWVER, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

static attr_options scope_options[ 4 ] = 
{
    { "SQL_SCOPE_CURROW", SQL_SCOPE_CURROW, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_SCOPE_TRANSACTION", SQL_SCOPE_TRANSACTION, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_SCOPE_SESSION", SQL_SCOPE_SESSION, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

static attr_options null_options[ 3 ] = 
{
    { "SQL_NO_NULLS", SQL_NO_NULLS, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { "SQL_NULLABLE", SQL_NULLABLE, 
        {
            { NULL, 0, NULL, 0}
        }, "1.0", SQL_INTEGER, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0}}, NULL, 0, 0, 0},
};

void dTables::Ok()
{
    QString stringLength;

    pOdbcTest->out_win->append( "SQLTables():" );
    pOdbcTest->out_win->append( "  In:" );

    // handle...
    OdbcHandle *hand            = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE   hStatement      = SQL_NULL_HANDLE;

    if ( hand )
        hStatement = hand->getHandle();

    if ( hStatement )
        pOdbcTest->out_win->append( QString( tr("    Statement Handle: %1") ).arg( (qulonglong)hStatement ) );
    else
        pOdbcTest->out_win->append( tr("    Statement Handle: SQL_NULL_HSTMT") );

    // catalog...
    QString stringCatalog = catalog ->currentText();
    const char *pszCatalog = NULL;
    if ( stringCatalog == "<null ptr>"  || stringCatalog.isNull() )
    {
        pszCatalog = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( stringCatalog == "<empty string>" || stringCatalog.isEmpty() )
    {
        pszCatalog = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else if ( stringCatalog == "SQL_ALL_CATALOGS" )
    {
        pszCatalog = SQL_ALL_CATALOGS;
        pOdbcTest->out_win->append( QString( tr("    Type: SQL_ALL_CATALOGS=%1") ).arg( SQL_ALL_CATALOGS ) );
    }
    else
    {
        pszCatalog = stringCatalog.toAscii().constData();
        pOdbcTest->out_win->append( QString( tr("    Catalog: %1") ).arg( pszCatalog ) );
    }

    // catalog length...
    stringLength = catalog_len ->currentText();
    SQLSMALLINT nCatalog = SQL_NTS; 
    if ( stringLength.left( 7 ) == "SQL_NTS" )
    {
        nCatalog = SQL_NTS;
        pOdbcTest->out_win->append( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        nCatalog = stringLength.toInt();
        pOdbcTest->out_win->append( QString( tr("    Catalog Len: %1") ).arg( nCatalog ) );
    }

    // schema...
    QString stringSchema = schema->currentText();
    const char *pszSchema = NULL;
    if ( stringSchema == "<null ptr>"  || stringSchema.isNull() )
    {
        pszSchema = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( stringSchema == "<empty string>" || stringSchema.isEmpty() )
    {
        pszSchema = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else if ( stringSchema == "SQL_ALL_SCHEMAS" )
    {
        pszSchema = SQL_ALL_SCHEMAS;
        pOdbcTest->out_win->append( QString( tr("    Type: SQL_ALL_SCHEMAS=%1") ).arg( SQL_ALL_SCHEMAS ) );
    }
    else
    {
        pszSchema = stringSchema.toAscii().constData();
        pOdbcTest->out_win->append( QString( tr("    Schema: %1") ).arg( pszSchema ) );
    }

    // schema length...
    stringLength = schema_len ->currentText();
    SQLSMALLINT nSchema = SQL_NTS; 
    if ( stringLength.left( 7 ) == "SQL_NTS" )
    {
        nSchema = SQL_NTS;
        pOdbcTest->out_win->append( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        nSchema = stringLength.toInt();
        pOdbcTest->out_win->append( QString( tr("    Schema Len: %1") ).arg( nSchema ) );
    }

    // table...
    QString stringTable = table->currentText();
    const char *pszTable = NULL;
    if ( stringTable == "<null ptr>"  || stringTable.isNull() )
    {
        pszTable = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( stringTable == "<empty string>" || stringTable.isEmpty() )
    {
        pszTable = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        pszTable = stringTable.toAscii().constData();
        pOdbcTest->out_win->append( QString( tr("    Table: %1") ).arg( pszTable ) );
    }
    
    // table length...
    stringLength = table_len ->currentText();
    SQLSMALLINT nTable = SQL_NTS; 
    if ( stringLength.left( 7 ) == "SQL_NTS" )
    {
        nTable = SQL_NTS;
        pOdbcTest->out_win->append( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        nTable = stringLength.toInt();
        pOdbcTest->out_win->append( QString( tr("    Table Len: %1") ).arg( nTable ) );
    }

    // type...
    QString stringType = type->currentText();
    const char *pszType = NULL;
    if ( stringType == "<null ptr>"  || stringType.isNull() )
    {
        pszType = NULL;
        pOdbcTest->out_win->append( "    Type: <null ptr>" );
    }
    else if ( stringType == "<empty string>" || stringType.isEmpty() )
    {
        pszType = "";
        pOdbcTest->out_win->append( "    Type: <empty string>" );
    }
    else if ( stringType == "SQL_ALL_TABLE_TYPES" )
    {
        pszType = SQL_ALL_TABLE_TYPES;
        pOdbcTest->out_win->append( QString( tr("    Type: SQL_ALL_TABLE_TYPES=%1") ).arg( SQL_ALL_TABLE_TYPES ) );
    }
    else
    {
        pszType = stringType.toAscii().constData();
        pOdbcTest->out_win->append( QString( tr("    Type: %1") ).arg( pszType ) );
    }

    // type length...
    stringLength = type_len->currentText();
    SQLSMALLINT nType = SQL_NTS; 
    if ( stringLength.left( 7 ) == "SQL_NTS" )
    {
        nType = SQL_NTS;
        pOdbcTest->out_win->append( "    Type Len: SQL_NTS=-3" );
    }
    else
    {
        nType = stringLength.toInt();
        pOdbcTest->out_win->append( QString( tr("    Type Len: %1") ).arg( nType ) );
    }

    // do it...
    SQLRETURN nReturn = SQLTables( hStatement, 
                                   (SQLCHAR*)pszCatalog, nCatalog,
                                   (SQLCHAR*)pszSchema, nSchema, 
                                   (SQLCHAR*)pszTable, nTable,
                                   (SQLCHAR*)pszType, nType );

    pOdbcTest->out_win->append( "  Return:" );
    pOdbcTest->out_win->append( QString( tr("    %1=%2") ).arg( pOdbcTest->return_as_text( nReturn ) ).arg( nReturn ) );
    pOdbcTest->out_win->append( "" );
}

dTables::dTables( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this ); // "Handle"
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this ); // "catalog"
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );
    catalog->insertItem( 2, "SQL_ALL_CATALOGS" );

    schema = new QComboBox( this ); // "schema"
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );
    schema->insertItem( 2, "SQL_ALL_SCHEMAS" );

    table = new QComboBox( this ); // "table"
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    /*! \todo consider getting from SQLGetInfo (with a fallback)... */
    type = new QComboBox( this ); // "table"
    type->setEditable( true );
    type->setGeometry( 100, 140, 150, 20 );
    l_type = new QLabel( "Table Type:", this );
    l_type->setGeometry( 10, 140, 90, 20 );
    type->insertItem( 0, "<null ptr>" );
    type->insertItem( 1, "<empty string>" );
    type->insertItem( 2, "SQL_ALL_TABLE_TYPES" );

    catalog_len = new QComboBox( this ); // "catalog len"
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this ); // "schema len"
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this ); // "table len"
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    type_len = new QComboBox( this ); // "type len"
    type_len->setEditable( true );
    type_len->setGeometry( 370, 140, 150, 20 );
    l_type_len = new QLabel( "String Length:", this );
    l_type_len->setGeometry( 280, 140, 90, 20 );
    type_len->insertItem( 0, "SQL_NTS=-3" );
    type_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dTables::~dTables()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete type;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete l_type;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete type_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete l_type_len;
}

void dColumns::Ok()
{
    const char *cat, *sch, *tab, *col;
    const char *lcat, *lsch, *ltab, *lcol;
    QString qcat, qsch, qtab, qcol;
    QString qlcat, qlsch, qltab, qlcol;
    int cat_len, sch_len, tab_len, col_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qcol = column ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();
    qlcol = column_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    col = qcol.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();
    lcol = qlcol.toAscii().constData();

    pOdbcTest->out_win->append( "SQLColumns():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( col, "<null ptr>" ) == 0 )
    {
        col = NULL;
        pOdbcTest->out_win->append( "    Column: <null ptr>" );
    }
    else if ( strcmp( col, "<empty string>" ) == 0 )
    {
        col = "";
        pOdbcTest->out_win->append( "    Column: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Column: %s", col );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcol, "SQL_NTS", 7 ) == 0 )
    {
        col_len = SQL_NTS;
        txt.sprintf( "    Column Len: SQL_NTS=-3" );
    }
    else
    {
        col_len = atoi( lcol );
        txt.sprintf( "    Column Len: %d", col_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLColumns( in_handle, 
                                (SQLCHAR*)cat, cat_len,
                                (SQLCHAR*)sch, sch_len, 
                                (SQLCHAR*)tab, tab_len,
                                (SQLCHAR*)col, col_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

void dColumnPrivileges::Ok()
{
    const char *cat, *sch, *tab, *col;
    const char *lcat, *lsch, *ltab, *lcol;
    QString qcat, qsch, qtab, qcol;
    QString qlcat, qlsch, qltab, qlcol;
    int cat_len, sch_len, tab_len, col_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qcol = column ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();
    qlcol = column_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    col = qcol.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();
    lcol = qlcol.toAscii().constData();

    pOdbcTest->out_win->append( "SQLColumnPrivileges():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( col, "<null ptr>" ) == 0 )
    {
        col = NULL;
        pOdbcTest->out_win->append( "    Column: <null ptr>" );
    }
    else if ( strcmp( col, "<empty string>" ) == 0 )
    {
        col = "";
        pOdbcTest->out_win->append( "    Column: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Column: %s", col );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcol, "SQL_NTS", 7 ) == 0 )
    {
        col_len = SQL_NTS;
        txt.sprintf( "    Column Len: SQL_NTS=-3" );
    }
    else
    {
        col_len = atoi( lcol );
        txt.sprintf( "    Column Len: %d", col_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLColumnPrivileges( in_handle, 
                                         (SQLCHAR*)cat, cat_len,
                                         (SQLCHAR*)sch, sch_len, 
                                         (SQLCHAR*)tab, tab_len,
                                         (SQLCHAR*)col, col_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dColumnPrivileges::dColumnPrivileges( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    column = new QComboBox( this );
    column->setEditable( true );
    column->setGeometry( 100, 140, 150, 20 );
    l_column = new QLabel( "Column:", this );
    l_column->setGeometry( 10, 140, 90, 20 );
    column->insertItem( 0, "<null ptr>" );
    column->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    column_len = new QComboBox( this );
    column_len->setEditable( true );
    column_len->setGeometry( 370, 140, 150, 20 );
    l_column_len = new QLabel( "String Length:", this );
    l_column_len->setGeometry( 280, 140, 90, 20 );
    column_len->insertItem( 0, "SQL_NTS=-3" );
    column_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dColumnPrivileges::~dColumnPrivileges()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete column;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete l_column;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete column_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete l_column_len;
}

dColumns::dColumns( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    column = new QComboBox( this );
    column->setEditable( true );
    column->setGeometry( 100, 140, 150, 20 );
    l_column = new QLabel( "Column:", this );
    l_column->setGeometry( 10, 140, 90, 20 );
    column->insertItem( 0, "<null ptr>" );
    column->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    column_len = new QComboBox( this );
    column_len->setEditable( true );
    column_len->setGeometry( 370, 140, 150, 20 );
    l_column_len = new QLabel( "String Length:", this );
    l_column_len->setGeometry( 280, 140, 90, 20 );
    column_len->insertItem( 0, "SQL_NTS=-3" );
    column_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dColumns::~dColumns()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete column;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete l_column;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete column_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete l_column_len;
}

void dForeignKeys::Ok()
{
    const char *cat, *sch, *tab;
    const char *fk_cat, *fk_sch, *fk_tab;
    const char *lcat, *lsch, *ltab;
    const char *fk_lcat, *fk_lsch, *fk_ltab;
    QString qcat, qsch, qtab;
    QString qfk_cat, qfk_sch, qfk_tab;
    QString qlcat, qlsch, qltab;
    QString qfk_lcat, qfk_lsch, qfk_ltab;
    int cat_len, sch_len, tab_len;
    int fk_cat_len, fk_sch_len, fk_tab_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();
    qfk_cat = fk_catalog ->currentText();
    qfk_sch = fk_schema ->currentText();
    qfk_tab = fk_table ->currentText();
    qfk_lcat = fk_catalog_len ->currentText();
    qfk_lsch = fk_schema_len ->currentText();
    qfk_ltab = fk_table_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();
    fk_cat = qfk_cat.toAscii().constData();
    fk_sch = qfk_sch.toAscii().constData();
    fk_tab = qfk_tab.toAscii().constData();
    fk_lcat = qfk_lcat.toAscii().constData();
    fk_lsch = qfk_lsch.toAscii().constData();
    fk_ltab = qfk_ltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLForeignKeys():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    PKCatalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    PKCatalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    PKCatalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    PKCatalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    PKCatalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    PKSchema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    PKSchema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    PKSchema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    PKSchema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    PKSchema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    PKTable: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    PKTable: <empty string>" );
    }
    else
    {
        txt.sprintf( "    PKTable: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    PKTable Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    PKTable Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( fk_cat, "<null ptr>" ) == 0 )
    {
        fk_cat = NULL;
        pOdbcTest->out_win->append( "    FKCatalog: <null ptr>" );
    }
    else if ( strcmp( fk_cat, "<empty string>" ) == 0 )
    {
        fk_cat = "";
        pOdbcTest->out_win->append( "    FKCatalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    FKCatalog: %s", fk_cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( fk_lcat, "SQL_NTS", 7 ) == 0 )
    {
        fk_cat_len = SQL_NTS;
        txt.sprintf( "    FKCatalog Len: SQL_NTS=-3" );
    }
    else
    {
        fk_cat_len = atoi( fk_lcat );
        txt.sprintf( "    FKCatalog Len: %d", fk_cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( fk_sch, "<null ptr>" ) == 0 )
    {
        fk_sch = NULL;
        pOdbcTest->out_win->append( "    FKSchema: <null ptr>" );
    }
    else if ( strcmp( fk_sch, "<empty string>" ) == 0 )
    {
        fk_sch = "";
        pOdbcTest->out_win->append( "    FKSchema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    FKSchema: %s", fk_sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( fk_lsch, "SQL_NTS", 7 ) == 0 )
    {
        fk_sch_len = SQL_NTS;
        txt.sprintf( "    FKSchema Len: SQL_NTS=-3" );
    }
    else
    {
        fk_sch_len = atoi( lsch );
        txt.sprintf( "    FKSchema Len: %d", fk_sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( fk_tab, "<null ptr>" ) == 0 )
    {
        fk_tab = NULL;
        pOdbcTest->out_win->append( "    FKTable: <null ptr>" );
    }
    else if ( strcmp( fk_tab, "<empty string>" ) == 0 )
    {
        fk_tab = "";
        pOdbcTest->out_win->append( "    FKTable: <empty string>" );
    }
    else
    {
        txt.sprintf( "    FKTable: %s", fk_tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( fk_ltab, "SQL_NTS", 7 ) == 0 )
    {
        fk_tab_len = SQL_NTS;
        txt.sprintf( "    FKTable Len: SQL_NTS=-3" );
    }
    else
    {
        fk_tab_len = atoi( ltab );
        txt.sprintf( "    FKTable Len: %d", fk_tab_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLForeignKeys( in_handle, 
                                    (SQLCHAR*)cat, cat_len,
                                    (SQLCHAR*)sch, sch_len, 
                                    (SQLCHAR*)tab, tab_len,
                                    (SQLCHAR*)fk_cat, fk_cat_len,
                                    (SQLCHAR*)fk_sch, fk_sch_len, 
                                    (SQLCHAR*)fk_tab, fk_tab_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dForeignKeys::dForeignKeys( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "PKCatalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "PKSchema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "PKTable:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    fk_catalog = new QComboBox( this );
    fk_catalog->setEditable( true );
    fk_catalog->setGeometry( 100, 140, 150, 20 );
    fk_l_catalog = new QLabel( "FKCatalog:", this );
    fk_l_catalog->setGeometry( 10, 140, 90, 20 );
    fk_catalog->insertItem( 0, "<null ptr>" );
    fk_catalog->insertItem( 1, "<empty string>" );

    fk_schema = new QComboBox( this );
    fk_schema->setEditable( true );
    fk_schema->setGeometry( 100, 170, 150, 20 );
    fk_l_schema = new QLabel( "FKSchema:", this );
    fk_l_schema->setGeometry( 10, 170, 90, 20 );
    fk_schema->insertItem( 0, "<null ptr>" );
    fk_schema->insertItem( 1, "<empty string>" );

    fk_table = new QComboBox( this );
    fk_table->setEditable( true );
    fk_table->setGeometry( 100, 200, 150, 20 );
    fk_l_table = new QLabel( "FKTable:", this );
    fk_l_table->setGeometry( 10, 200, 90, 20 );
    fk_table->insertItem( 0, "<null ptr>" );
    fk_table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 140, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 140, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    fk_catalog_len = new QComboBox( this );
    fk_catalog_len->setEditable( true );
    fk_catalog_len->setGeometry( 370, 140, 150, 20 );
    fk_l_catalog_len = new QLabel( "String Length:", this );
    fk_l_catalog_len->setGeometry( 280, 140, 90, 20 );
    fk_catalog_len->insertItem( 0, "SQL_NTS=-3" );
    fk_catalog_len->insertItem( 1, "0" );

    fk_schema_len = new QComboBox( this );
    fk_schema_len->setEditable( true );
    fk_schema_len->setGeometry( 370, 170, 150, 20 );
    fk_l_schema_len = new QLabel( "String Length:", this );
    fk_l_schema_len->setGeometry( 280, 170, 90, 20 );
    fk_schema_len->insertItem( 0, "SQL_NTS=-3" );
    fk_schema_len->insertItem( 1, "0" );

    fk_table_len = new QComboBox( this );
    fk_table_len->setEditable( true );
    fk_table_len->setGeometry( 370, 200, 150, 20 );
    fk_l_table_len = new QLabel( "String Length:", this );
    fk_l_table_len->setGeometry( 280, 200, 90, 20 );
    fk_table_len->insertItem( 0, "SQL_NTS=-3" );
    fk_table_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dForeignKeys::~dForeignKeys()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete fk_catalog;
    delete fk_schema;
    delete fk_table;
    delete fk_l_catalog;
    delete fk_l_schema;
    delete fk_l_table;
    delete fk_catalog_len;
    delete fk_schema_len;
    delete fk_table_len;
    delete fk_l_catalog_len;
    delete fk_l_schema_len;
    delete fk_l_table_len;
}

void dPrimaryKeys::Ok()
{
    const char *cat, *sch, *tab;
    const char *lcat, *lsch, *ltab;
    QString qcat, qsch, qtab;
    QString qlcat, qlsch, qltab;
    int cat_len, sch_len, tab_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLPrimaryKeys():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLPrimaryKeys( in_handle, 
                                    (SQLCHAR*)cat, cat_len,
                                    (SQLCHAR*)sch, sch_len, 
                                    (SQLCHAR*)tab, tab_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dPrimaryKeys::dPrimaryKeys( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox(this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dPrimaryKeys::~dPrimaryKeys()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
}

void dProcedures::Ok()
{
    const char *cat, *sch, *tab;
    const char *lcat, *lsch, *ltab;
    QString qcat, qsch, qtab;
    QString qlcat, qlsch, qltab;
    int cat_len, sch_len, tab_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLProcedures():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Procedure: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Procedure: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Procedure: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Procedure Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Procedure Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLProcedures( in_handle, 
                                   (SQLCHAR*)cat, cat_len,
                                   (SQLCHAR*)sch, sch_len, 
                                   (SQLCHAR*)tab, tab_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dProcedures::dProcedures( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Procedure:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dProcedures::~dProcedures()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
}

void dProcedureColumns::Ok()
{
    const char *cat, *sch, *tab, *col;
    const char *lcat, *lsch, *ltab, *lcol;
    QString qcat, qsch, qtab, qcol;
    QString qlcat, qlsch, qltab, qlcol;
    int cat_len, sch_len, tab_len, col_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qcol = column ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();
    qlcol = column_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    col = qcol.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();
    lcol = qlcol.toAscii().constData();

    pOdbcTest->out_win->append( "SQLProcedureColumns():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Procedure: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Procedure: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Procedure: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( col, "<null ptr>" ) == 0 )
    {
        col = NULL;
        pOdbcTest->out_win->append( "    Column: <null ptr>" );
    }
    else if ( strcmp( col, "<empty string>" ) == 0 )
    {
        col = "";
        pOdbcTest->out_win->append( "    Column: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Column: %s", col );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcol, "SQL_NTS", 7 ) == 0 )
    {
        col_len = SQL_NTS;
        txt.sprintf( "    Column Len: SQL_NTS=-3" );
    }
    else
    {
        col_len = atoi( lcol );
        txt.sprintf( "    Column Len: %d", col_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLProcedureColumns( in_handle, 
                                         (SQLCHAR*)cat, cat_len,
                                         (SQLCHAR*)sch, sch_len, 
                                         (SQLCHAR*)tab, tab_len,
                                         (SQLCHAR*)col, col_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dProcedureColumns::dProcedureColumns( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Procedure:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    column = new QComboBox( this );
    column->setEditable( true );
    column->setGeometry( 100, 140, 150, 20 );
    l_column = new QLabel( "Column:", this );
    l_column->setGeometry( 10, 140, 90, 20 );
    column->insertItem( 0, "<null ptr>" );
    column->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    column_len = new QComboBox( this );
    column_len->setEditable( true );
    column_len->setGeometry( 370, 140, 150, 20 );
    l_column_len = new QLabel( "String Length:", this );
    l_column_len->setGeometry( 280, 140, 90, 20 );
    column_len->insertItem( 0, "SQL_NTS=-3" );
    column_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dProcedureColumns::~dProcedureColumns()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete column;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete l_column;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete column_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete l_column_len;
}

void dTablePrivileges::Ok()
{
    const char *cat, *sch, *tab;
    const char *lcat, *lsch, *ltab;
    QString qcat, qsch, qtab;
    QString qlcat, qlsch, qltab;
    int cat_len, sch_len, tab_len;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len ->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLTablePrivileges():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLTablePrivileges( in_handle, 
                                        (SQLCHAR*)cat, cat_len,
                                        (SQLCHAR*)sch, sch_len, 
                                        (SQLCHAR*)tab, tab_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dTablePrivileges::dTablePrivileges( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dTablePrivileges::~dTablePrivileges()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
}

void dGetTypeInfo::Ok()
{
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    int index;
    SQLHANDLE in_handle = SQL_NULL_HANDLE;
    SQLINTEGER info_type;

    if ( hand )
        in_handle = hand->getHandle();

    pOdbcTest->out_win->append( "SQLGetTypeInfo():" );
    pOdbcTest->out_win->append( "  In:" );

    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    index = type->currentIndex(); 

    info_type = get_type_options[ index ].attr;
    txt.sprintf( "    Data Type: %s=%d (%s)", get_type_options[ index ].text,
                 get_type_options[ index ].attr, get_type_options[ index ].version );
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLGetTypeInfo( in_handle, info_type );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );

    pOdbcTest->out_win->append( "" );
}

dGetTypeInfo::dGetTypeInfo( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 240,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 320,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 400,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 130, 50, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Statement Handle:", this );
    l_handle->setGeometry( 10, 50, 120, 20 );

    type = new QComboBox( this );
    type->setGeometry( 130, 80, 340, 20 );

    pOdbcTest->fill_list_box( get_type_options, type );

    l_type = new QLabel( "Data Type:", this );
    l_type->setGeometry( 10, 80, 120, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dGetTypeInfo::~dGetTypeInfo()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handle;
    delete type;
    delete l_type;
}

void dStatistics::Ok()
{
    const char *cat, *sch, *tab;
    const char *lcat, *lsch, *ltab;
    QString qcat, qsch, qtab;
    QString qlcat, qlsch, qltab;
    int cat_len, sch_len, tab_len;
    int res, res_val, uniq, uniq_val;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog ->currentText();
    qsch = schema ->currentText();
    qtab = table ->currentText();
    qlcat = catalog_len ->currentText();
    qlsch = schema_len ->currentText();
    qltab = table_len->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();
    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLStatistics():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    uniq = unique->currentIndex(); 

    uniq_val = unique_options[ uniq ].attr;
    txt.sprintf( "    Unique: %s=%d (%s)", unique_options[ uniq ].text,
                 unique_options[ uniq ].attr, unique_options[ uniq ].version );
    pOdbcTest->out_win->append( txt );

    res = reserved->currentIndex(); 

    res_val = reserved_options[ res ].attr;
    txt.sprintf( "    Reserved: %s=%d (%s)", reserved_options[ res ].text,
                 reserved_options[ res ].attr, reserved_options[ res ].version );
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLStatistics( in_handle, 
                                   (SQLCHAR*)cat, cat_len,
                                   (SQLCHAR*)sch, sch_len, 
                                   (SQLCHAR*)tab, tab_len, 
                                   uniq_val,
                                   res_val );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dStatistics::dStatistics( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true );
    catalog->setGeometry( 100, 50, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 50, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 80, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 80, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 110, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 110, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 50, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 50, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 80, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 80, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 110, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 110, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    unique = new QComboBox( this );
    unique->setGeometry( 100, 140, 200, 20 );
    pOdbcTest->fill_list_box( unique_options, unique );
    l_unique = new QLabel( "Unique:", this );
    l_unique->setGeometry( 10, 140, 90, 20 );

    reserved = new QComboBox( this );
    reserved->setGeometry( 100, 170, 200, 20 );
    pOdbcTest->fill_list_box( reserved_options, reserved );
    l_reserved = new QLabel( "Reserved:", this );
    l_reserved->setGeometry( 10, 170, 90, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dStatistics::~dStatistics()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete unique;
    delete reserved;
    delete l_unique;
    delete l_reserved;
}

void dSpecialColumns::Ok()
{
    const char *cat, *sch, *tab;
    const char *lcat, *lsch, *ltab;
    QString qcat, qsch, qtab;
    QString qlcat, qlsch, qltab;
    int cat_len, sch_len, tab_len;
    int nul, nul_val, scp, scp_val;
    int id, id_val;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;

    if ( hand )
        in_handle = hand->getHandle();

    qcat = catalog->currentText();
    qsch = schema->currentText();
    qtab = table->currentText();

    qlcat = catalog_len->currentText();
    qlsch = schema_len->currentText();
    qltab = table_len->currentText();

    cat = qcat.toAscii().constData();
    sch = qsch.toAscii().constData();
    tab = qtab.toAscii().constData();

    lcat = qlcat.toAscii().constData();
    lsch = qlsch.toAscii().constData();
    ltab = qltab.toAscii().constData();

    pOdbcTest->out_win->append( "SQLSpecialColumns():" );
    pOdbcTest->out_win->append( "  In:" );
    if ( in_handle )
        txt.sprintf( "    Statement Handle: %p", in_handle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    id = ident->currentIndex(); 

    id_val = ident_options[ id ].attr;
    txt.sprintf( "    Identifier Type: %s=%d (%s)", ident_options[ id ].text,
                 ident_options[ id ].attr, ident_options[ id ].version );
    pOdbcTest->out_win->append( txt );

    if ( strcmp( cat, "<null ptr>" ) == 0 )
    {
        cat = NULL;
        pOdbcTest->out_win->append( "    Catalog: <null ptr>" );
    }
    else if ( strcmp( cat, "<empty string>" ) == 0 )
    {
        cat = "";
        pOdbcTest->out_win->append( "    Catalog: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Catalog: %s", cat );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lcat, "SQL_NTS", 7 ) == 0 )
    {
        cat_len = SQL_NTS;
        txt.sprintf( "    Catalog Len: SQL_NTS=-3" );
    }
    else
    {
        cat_len = atoi( lcat );
        txt.sprintf( "    Catalog Len: %d", cat_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( sch, "<null ptr>" ) == 0 )
    {
        sch = NULL;
        pOdbcTest->out_win->append( "    Schema: <null ptr>" );
    }
    else if ( strcmp( sch, "<empty string>" ) == 0 )
    {
        sch = "";
        pOdbcTest->out_win->append( "    Schema: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Schema: %s", sch );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( lsch, "SQL_NTS", 7 ) == 0 )
    {
        sch_len = SQL_NTS;
        txt.sprintf( "    Schema Len: SQL_NTS=-3" );
    }
    else
    {
        sch_len = atoi( lsch );
        txt.sprintf( "    Schema Len: %d", sch_len );
    }
    pOdbcTest->out_win->append( txt );

    if ( strcmp( tab, "<null ptr>" ) == 0 )
    {
        tab = NULL;
        pOdbcTest->out_win->append( "    Table: <null ptr>" );
    }
    else if ( strcmp( tab, "<empty string>" ) == 0 )
    {
        tab = "";
        pOdbcTest->out_win->append( "    Table: <empty string>" );
    }
    else
    {
        txt.sprintf( "    Table: %s", tab );
        pOdbcTest->out_win->append( txt );
    }

    if ( strncmp( ltab, "SQL_NTS", 7 ) == 0 )
    {
        tab_len = SQL_NTS;
        txt.sprintf( "    Table Len: SQL_NTS=-3" );
    }
    else
    {
        tab_len = atoi( ltab );
        txt.sprintf( "    Table Len: %d", tab_len );
    }
    pOdbcTest->out_win->append( txt );

    scp = scope->currentIndex(); 

    scp_val = unique_options[ scp ].attr;
    txt.sprintf( "    Scope: %s=%d (%s)", scope_options[ scp ].text,
                 scope_options[ scp ].attr, scope_options[ scp ].version );
    pOdbcTest->out_win->append( txt );

    nul = nullable->currentIndex(); 

    nul_val = null_options[ nul ].attr;
    txt.sprintf( "    Nullable: %s=%d (%s)", null_options[ nul ].text,
                 null_options[ nul ].attr, null_options[ nul ].version );
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLSpecialColumns( in_handle, 
                                       id_val,
                                       (SQLCHAR*)cat, cat_len,
                                       (SQLCHAR*)sch, sch_len, 
                                       (SQLCHAR*)tab, tab_len, 
                                       scp_val,
                                       nul_val );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );
    pOdbcTest->out_win->append( "" );
}

dSpecialColumns::dSpecialColumns( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 290,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 370,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 450,10, 70,25 );

    handles = new QComboBox( this );
    handles->setGeometry( 100, 15, 150, 20 );

    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, handles );

    l_handle = new QLabel( "Handle:", this );
    l_handle->setGeometry( 10, 15, 80, 20 );

    ident = new QComboBox( this );
    ident->setGeometry( 100, 50, 250, 20 );
    pOdbcTest->fill_list_box( ident_options, ident );
    l_ident = new QLabel( "Identifier Type:", this );
    l_ident->setGeometry( 10, 50, 90, 20 );

    catalog = new QComboBox( this );
    catalog->setEditable( true ); 
    catalog->setGeometry( 100, 80, 150, 20 );
    l_catalog = new QLabel( "Catalog:", this );
    l_catalog->setGeometry( 10, 80, 90, 20 );
    catalog->insertItem( 0, "<null ptr>" );
    catalog->insertItem( 1, "<empty string>" );

    schema = new QComboBox( this );
    schema->setEditable( true );
    schema->setGeometry( 100, 110, 150, 20 );
    l_schema = new QLabel( "Schema:", this );
    l_schema->setGeometry( 10, 110, 90, 20 );
    schema->insertItem( 0, "<null ptr>" );
    schema->insertItem( 1, "<empty string>" );

    table = new QComboBox( this );
    table->setEditable( true );
    table->setGeometry( 100, 140, 150, 20 );
    l_table = new QLabel( "Table:", this );
    l_table->setGeometry( 10, 140, 90, 20 );
    table->insertItem( 0, "<null ptr>" );
    table->insertItem( 1, "<empty string>" );

    catalog_len = new QComboBox( this );
    catalog_len->setEditable( true );
    catalog_len->setGeometry( 370, 80, 150, 20 );
    l_catalog_len = new QLabel( "String Length:", this );
    l_catalog_len->setGeometry( 280, 80, 90, 20 );
    catalog_len->insertItem( 0, "SQL_NTS=-3" );
    catalog_len->insertItem( 1, "0" );

    schema_len = new QComboBox( this );
    schema_len->setEditable( true );
    schema_len->setGeometry( 370, 110, 150, 20 );
    l_schema_len = new QLabel( "String Length:", this );
    l_schema_len->setGeometry( 280, 110, 90, 20 );
    schema_len->insertItem( 0, "SQL_NTS=-3" );
    schema_len->insertItem( 1, "0" );

    table_len = new QComboBox( this );
    table_len->setEditable( true );
    table_len->setGeometry( 370, 140, 150, 20 );
    l_table_len = new QLabel( "String Length:", this );
    l_table_len->setGeometry( 280, 140, 90, 20 );
    table_len->insertItem( 0, "SQL_NTS=-3" );
    table_len->insertItem( 1, "0" );

    scope = new QComboBox( this );
    scope->setGeometry( 100, 170, 250, 20 );
    pOdbcTest->fill_list_box( scope_options, scope );
    l_scope = new QLabel( "Scope:", this );
    l_scope->setGeometry( 10, 170, 90, 20 );

    nullable = new QComboBox( this );
    nullable->setGeometry( 100, 200, 250, 20 );
    pOdbcTest->fill_list_box( null_options, nullable );
    l_nullable = new QLabel( "Reserved:", this );
    l_nullable->setGeometry( 10, 200, 90, 20 );

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dSpecialColumns::~dSpecialColumns()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete catalog;
    delete schema;
    delete table;
    delete l_handle;
    delete l_catalog;
    delete l_schema;
    delete l_table;
    delete catalog_len;
    delete schema_len;
    delete table_len;
    delete l_catalog_len;
    delete l_schema_len;
    delete l_table_len;
    delete scope;
    delete nullable;
    delete l_scope;
    delete l_nullable;
    delete ident;
    delete l_ident;
}

void OdbcTest::slotColumns()
{
    dColumns *dlg = new dColumns( this, "SQLColumns" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotColumnPrivileges()
{
    dColumnPrivileges *dlg = new dColumnPrivileges( this, "SQLColumnPrivileges" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotGetTypeInfo()
{
    dGetTypeInfo *dlg = new dGetTypeInfo( this, "SQLGetTypeInfo" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotForeignKeys()
{
    dForeignKeys *dlg = new dForeignKeys( this, "SQLForeignKeys" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotPrimaryKeys()
{
    dPrimaryKeys *dlg = new dPrimaryKeys( this, "SQLPrimaryKeys" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotProcedures()
{
    dProcedures *dlg = new dProcedures( this, "SQLProcedures" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotProcedureColumns()
{
    dProcedureColumns *dlg = new dProcedureColumns( this, "SQLProcedureColumns" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotSpecialColumns()
{
    dSpecialColumns *dlg = new dSpecialColumns( this, "SQLSpecialColumns" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotStatistics()
{
    dStatistics *dlg = new dStatistics( this, "SQLStatistics" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotTables()
{
    dTables *dlg = new dTables( this, "SQLTables" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotTablePrivileges()
{
    dTablePrivileges *dlg = new dTablePrivileges( this, "SQLTablePrivileges" );

    dlg->exec();

    delete dlg;
}

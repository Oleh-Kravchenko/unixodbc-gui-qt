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

#include "diag.h"
#include "OdbcTest.h"

static attr_value handle_type_struct[] = 
{
    { "SQL_HANDLE_ENV",     SQL_HANDLE_ENV,     NULL,   0},
    { "SQL_HANDLE_DBC",     SQL_HANDLE_DBC,     NULL,   0},
    { "SQL_HANDLE_STMT",    SQL_HANDLE_STMT,    NULL,   0},
    { "SQL_HANDLE_DESC",    SQL_HANDLE_DESC,    NULL,   0},
    { NULL,                 0,                  NULL,   0}
};

static attr_options field_type_struct[] = 
{
    { "SQL_DIAG_CURSOR_ROW_COUNT", SQL_DIAG_CURSOR_ROW_COUNT, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_DYNAMIC_FUNCTION", SQL_DIAG_DYNAMIC_FUNCTION, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_DYNAMIC_FUNCTION_CODE", SQL_DIAG_DYNAMIC_FUNCTION_CODE, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_NUMBER", SQL_DIAG_NUMBER, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_RETURNCODE", SQL_DIAG_RETURNCODE, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_ROW_COUNT", SQL_DIAG_ROW_COUNT, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_CLASS_ORIGIN", SQL_DIAG_CLASS_ORIGIN, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_COLUMN_NUMBER", SQL_DIAG_COLUMN_NUMBER, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_CONNECTION_NAME", SQL_DIAG_CONNECTION_NAME, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_MESSAGE_TEXT", SQL_DIAG_MESSAGE_TEXT, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_NATIVE", SQL_DIAG_NATIVE, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_ROW_NUMBER", SQL_DIAG_ROW_NUMBER, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_INTEGER, 0, 0
    },
    { "SQL_DIAG_SERVER_NAME", SQL_DIAG_SERVER_NAME, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_SQLSTATE", SQL_DIAG_SQLSTATE, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { "SQL_DIAG_SUBCLASS_ORIGIN", SQL_DIAG_SUBCLASS_ORIGIN, 
        {
            { NULL, 0, NULL, 0 }
        }, "3.0", SQL_CHAR, 0, 0
    },
    { NULL, 0, { { NULL, 0, NULL, 0 } }, NULL, 0, 0, 0 }
};

void dError::sqlstate_clkd()
{
    if ( sqlstate_valid->isChecked() )
        sqlstate_valid->setText( "szSqlState: SQL_NULL_POINTER" );
    else
        sqlstate_valid->setText( "szSqlState: VALID" );
}

void dError::native_clkd()
{
    if ( native_valid->isChecked() )
        native_valid->setText( "pfNativeError: SQL_NULL_POINTER" );
    else
        native_valid->setText( "pfNativeError: VALID" );
}

void dError::error_clkd()
{
    if ( error_valid->isChecked() )
        error_valid->setText( "szErrorMsg: SQL_NULL_POINTER" );
    else
        error_valid->setText( "szErrorMsg: VALID" );
}

void dError::perror_clkd()
{
    if ( perror_valid->isChecked() )
        perror_valid->setText( "pcbErrorMsg: SQL_NULL_POINTER" );
    else
        perror_valid->setText( "pcbErrorMsg: VALID" );
}

void dError::Ok()
{
    OdbcHandle *stmt = pOdbcTest->extract_handle_list( SQL_HANDLE_STMT, shandles );
    OdbcHandle *dbc = pOdbcTest->extract_handle_list( SQL_HANDLE_DBC, chandles );
    OdbcHandle *env = pOdbcTest->extract_handle_list( SQL_HANDLE_ENV, ehandles );
    SQLHANDLE in_shandle = SQL_NULL_HANDLE;
    SQLHANDLE in_dhandle = SQL_NULL_HANDLE;
    SQLHANDLE in_ehandle = SQL_NULL_HANDLE;
    SQLCHAR sqlstate[ 7 ], *psqlstate;
    SQLSMALLINT b_len, text_len, *ptext_len;
    SQLINTEGER native, *pnative;
    SQLCHAR *buf;

    if ( env )
        in_ehandle = env->getHandle();
    if ( dbc )
        in_dhandle = dbc->getHandle();
    if ( stmt )
        in_shandle = stmt->getHandle();

    pOdbcTest->out_win->append( "SQLError():" );
    pOdbcTest->out_win->append( "  In:" );

    if ( in_ehandle )
        txt.sprintf( "    Environment Handle: %p", in_ehandle );
    else
        txt.sprintf( "    Environment Handle: SQL_NULL_HENV" );
    pOdbcTest->out_win->append( txt );

    if ( in_dhandle )
        txt.sprintf( "    Connection Handle: %p", in_dhandle );
    else
        txt.sprintf( "    Connection Handle: SQL_NULL_HDBC" );
    pOdbcTest->out_win->append( txt );

    if ( in_shandle )
        txt.sprintf( "    Statement Handle: %p", in_shandle );
    else
        txt.sprintf( "    Statement Handle: SQL_NULL_HSTMT" );
    pOdbcTest->out_win->append( txt );

    if ( sqlstate_valid->isChecked() )
    {
        txt.sprintf( "    szSqlState: <null pointer>" );
        psqlstate = NULL;
    }
    else
    {
        psqlstate = sqlstate;
        strcpy(( char * ) sqlstate, "XYXYXZ" );
        txt.sprintf( "    szSqlState: %p", psqlstate );
    }
    pOdbcTest->out_win->append( txt );

    if ( native_valid->isChecked() )
    {
        txt.sprintf( "    pfNativeError: <null pointer>" );
        pnative = NULL;
    }
    else
    {
        pnative = &native;
        native = -999999;
        txt.sprintf( "    pfNativeError: %p", pnative );
    }
    pOdbcTest->out_win->append( txt );

    b_len = buffer_len->text().toInt();
    if ( error_valid->isChecked() )
    {
        buf = NULL;
        txt.sprintf( "    szErrorMsg: <null pointer>" );
    }
    else
    {
        if ( b_len < 0 )
            b_len = 300;

        buf = new SQLCHAR[ b_len ];

        txt.sprintf( "    szErrorMsg: %p", buf );
    }
    pOdbcTest->out_win->append( txt );

    txt.sprintf( "    cbErrorMsgMax: %d", b_len );
    pOdbcTest->out_win->append( txt );

    if ( perror_valid->isChecked() )
    {
        txt.sprintf( "    pcbErrorMsg: <null pointer>" );
        ptext_len = NULL;
    }
    else
    {
        ptext_len = &text_len;
        text_len = -9999;
        txt.sprintf( "    pcbErrorMsg: %p", ptext_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLError( in_ehandle, in_dhandle, in_shandle,
                              psqlstate, pnative, buf, b_len, ptext_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        pOdbcTest->out_win->append( "  Out:" );
        if ( psqlstate )
        {
            if ( strcmp(( char * ) sqlstate, "XYXYXZ" ) == 0 )
            {
                txt.sprintf( "    *szSqlState: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *szSqlState: %6s", sqlstate );
            }
            pOdbcTest->out_win->append( txt );
        }
        if ( pnative )
        {
            if ( native == -999999 )
            {
                txt.sprintf( "    *pfNativeError: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *pfNativeError: %d", native );
            }
            pOdbcTest->out_win->append( txt );
        }
        if ( buf )
        {
            txt.sprintf( "    *szErrorMsg: %s", buf );
            pOdbcTest->out_win->append( txt );
        }
        if ( ptext_len )
        {
            if ( text_len == -9999 )
            {
                txt.sprintf( "    *pcbErrorMsg: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *pcbErrorMsg: %d", text_len );
            }
            pOdbcTest->out_win->append( txt );
        }
    }

    pOdbcTest->out_win->append( "" );

    if ( buf )
        delete buf;
}

dError::dError( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );

    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 190,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 270,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 350,10, 70,25 );

    ehandles = new QComboBox( this );
    ehandles->setGeometry( 130, 50, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, ehandles );

    l_ehandle = new QLabel( "Environment Handle:", this );
    l_ehandle->setGeometry( 10, 50, 120, 20 );

    chandles = new QComboBox( this );
    chandles->setGeometry( 130, 80, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_DBC, chandles );

    l_chandle = new QLabel( "Connection Handle:", this );
    l_chandle->setGeometry( 10, 80, 120, 20 );

    shandles = new QComboBox( this );
    shandles->setGeometry( 130, 110, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_STMT, shandles );

    l_shandle = new QLabel( "Statement Handle:", this );
    l_shandle->setGeometry( 10, 110, 120, 20 );

    sqlstate_valid = new QCheckBox( "szSqlState: VALID", this );
    sqlstate_valid->setGeometry( 10, 140, 300, 15 );

    native_valid = new QCheckBox( "pfNativeError: VALID", this );
    native_valid->setGeometry( 10, 170, 300, 15 );

    error_valid = new QCheckBox( "szErrorMsg: VALID", this );
    error_valid->setGeometry( 10, 200, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len->setGeometry( 350, 200, 70, 20 );
    buffer_len->setMaxLength( 6 );
    buffer_len->setText( "300" );

    l_buffer_len = new QLabel( "cbErrorMsgMax:", this );
    l_buffer_len->setGeometry( 240, 200, 100, 20 );

    perror_valid = new QCheckBox( "pcbErrorMsg: VALID", this );
    perror_valid->setGeometry( 10, 230, 300, 15 );

    connect( native_valid, SIGNAL( clicked()), this, SLOT( native_clkd()));
    connect( sqlstate_valid, SIGNAL( clicked()), this, SLOT( sqlstate_clkd()));
    connect( error_valid, SIGNAL( clicked()), this, SLOT( error_clkd()));
    connect( perror_valid, SIGNAL( clicked()), this, SLOT( perror_clkd()));

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );
}

dError::~dError()
{
    delete ok;
    delete cancel;
    delete help;
    delete ehandles;
    delete chandles;
    delete shandles;
    delete l_ehandle;
    delete l_chandle;
    delete l_shandle;
    delete sqlstate_valid;
    delete native_valid;
    delete error_valid;
    delete perror_valid;
    delete buffer_len;
    delete l_buffer_len;
}

void dGetDiagRec::sel_handle( int /* index */ )
{
    int handle_t;

    handles->clear();
    handle_t = handle_type_struct[ handle_type->currentIndex() ].value;

    pOdbcTest->fill_handle_list( handle_t, handles );
}

void dGetDiagRec::sqlstate_clkd()
{
    if ( sqlstate_valid->isChecked() )
        sqlstate_valid->setText( "szSqlState: SQL_NULL_POINTER" );
    else
        sqlstate_valid->setText( "szSqlState: VALID" );
}

void dGetDiagRec::native_clkd()
{
    if ( native_valid->isChecked() )
        native_valid->setText( "pfNativeError: SQL_NULL_POINTER" );
    else
        native_valid->setText( "pfNativeError: VALID" );
}

void dGetDiagRec::error_clkd()
{
    if ( error_valid->isChecked() )
        error_valid->setText( "szErrorMsg: SQL_NULL_POINTER" );
    else
        error_valid->setText( "szErrorMsg: VALID" );
}

void dGetDiagRec::perror_clkd()
{
    if ( perror_valid->isChecked() )
        perror_valid->setText( "pcbErrorMsg: SQL_NULL_POINTER" );
    else
        perror_valid->setText( "pcbErrorMsg: VALID" );
}

void dGetDiagRec::Ok()
{
    int htype = handle_type_struct[ handle_type->currentIndex() ].value;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( htype, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;
    SQLCHAR sqlstate[ 7 ], *psqlstate;
    SQLSMALLINT b_len, text_len, *ptext_len;
    SQLINTEGER native, *pnative, rec_number;
    SQLCHAR *buf;

    if ( hand )
        in_handle = hand->getHandle();

    pOdbcTest->out_win->append( "SQLGetDiagRec():" );
    pOdbcTest->out_win->append( "  In:" );

    txt.sprintf( "    Handle Type: %s", handle_type_struct[ handle_type->currentIndex() ].text );
    pOdbcTest->out_win->append( txt );

    if ( in_handle )
        txt.sprintf( "    Handle: %p", in_handle );
    else
        txt.sprintf( "    Handle: SQL_NULL_HANDLE" );
    pOdbcTest->out_win->append( txt );

    rec_number = rec_num->text().toInt();
    txt.sprintf( "    RecNumber: %d", rec_number );

    if ( sqlstate_valid->isChecked() )
    {
        txt.sprintf( "    szSqlState: <null pointer>" );
        psqlstate = NULL;
    }
    else
    {
        psqlstate = sqlstate;
        strcpy(( char * ) sqlstate, "XYXYXZ" );
        txt.sprintf( "    szSqlState: %p", psqlstate );
    }
    pOdbcTest->out_win->append( txt );

    if ( native_valid->isChecked() )
    {
        txt.sprintf( "    pfNativeError: <null pointer>" );
        pnative = NULL;
    }
    else
    {
        pnative = &native;
        native = -999999;
        txt.sprintf( "    pfNativeError: %p", pnative );
    }
    pOdbcTest->out_win->append( txt );

    b_len = buffer_len->text().toInt();
    if ( error_valid->isChecked() )
    {
        buf = NULL;
        txt.sprintf( "    szErrorMsg: <null pointer>" );
    }
    else
    {
        if ( b_len < 0 )
            b_len = 300;

        buf = new SQLCHAR[ b_len ];

        txt.sprintf( "    szErrorMsg: %p", buf );
    }
    pOdbcTest->out_win->append( txt );

    txt.sprintf( "    cbErrorMsgMax: %d", b_len );
    pOdbcTest->out_win->append( txt );

    if ( perror_valid->isChecked() )
    {
        txt.sprintf( "    pcbErrorMsg: <null pointer>" );
        ptext_len = NULL;
    }
    else
    {
        ptext_len = &text_len;
        text_len = -9999;
        txt.sprintf( "    pcbErrorMsg: %p", ptext_len );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLGetDiagRec( htype, in_handle, rec_number,
                                   psqlstate, pnative, buf, b_len, ptext_len );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        pOdbcTest->out_win->append( "  Out:" );
        if ( psqlstate )
        {
            if ( strcmp(( char * ) sqlstate, "XYXYXZ" ) == 0 )
            {
                txt.sprintf( "    *szSqlState: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *szSqlState: %6s", sqlstate );
            }
            pOdbcTest->out_win->append( txt );
        }
        if ( pnative )
        {
            if ( native == -999999 )
            {
                txt.sprintf( "    *pfNativeError: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *pfNativeError: %d", native );
            }
            pOdbcTest->out_win->append( txt );
        }
        if ( buf )
        {
            txt.sprintf( "    *szErrorMsg: %s", buf );
            pOdbcTest->out_win->append( txt );
        }
        if ( ptext_len )
        {
            if ( text_len == -9999 )
            {
                txt.sprintf( "    *pcbErrorMsg: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *pcbErrorMsg: %d", text_len );
            }
            pOdbcTest->out_win->append( txt );
        }
    }

    pOdbcTest->out_win->append( "" );

    if ( buf )
        delete buf;
}

dGetDiagRec::dGetDiagRec( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 190,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 270,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 350,10, 70,25 );

    handle_type = new QComboBox( this );
    handle_type->setGeometry( 130, 50, 200, 20 );
    pOdbcTest->fill_list_box( handle_type_struct, handle_type );

    l_handle_type = new QLabel( "Handle Type:", this );
    l_handle_type->setGeometry( 10, 50, 120, 20 );

    handles = new QComboBox( this );
    handles->setGeometry( 130, 80, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, handles );

    l_handles = new QLabel( "Handle:", this );
    l_handles->setGeometry( 10, 80, 120, 20 );

    rec_num = new QLineEdit( this );
    rec_num->setGeometry( 130, 110, 70, 20 );
    rec_num->setMaxLength( 6 );
    rec_num->setText( "1" );

    l_rec_num = new QLabel( "Rec Number:", this );
    l_rec_num->setGeometry( 10, 110, 100, 20 );

    sqlstate_valid = new QCheckBox( "szSqlState: VALID", this );
    sqlstate_valid->setGeometry( 10, 140, 300, 15 );

    native_valid = new QCheckBox( "pfNativeError: VALID", this );
    native_valid->setGeometry( 10, 170, 300, 15 );

    error_valid = new QCheckBox( "szErrorMsg: VALID", this );
    error_valid->setGeometry( 10, 200, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len->setGeometry( 350, 200, 70, 20 );
    buffer_len->setMaxLength( 6 );
    buffer_len->setText( "300" );

    l_buffer_len = new QLabel( "cbErrorMsgMax:", this );
    l_buffer_len->setGeometry( 240, 200, 100, 20 );

    perror_valid = new QCheckBox( "pcbErrorMsg: VALID", this );
    perror_valid->setGeometry( 10, 230, 300, 15 );

    connect( native_valid, SIGNAL( clicked()), this, SLOT( native_clkd()));
    connect( sqlstate_valid, SIGNAL( clicked()), this, SLOT( sqlstate_clkd()));
    connect( error_valid, SIGNAL( clicked()), this, SLOT( error_clkd()));
    connect( perror_valid, SIGNAL( clicked()), this, SLOT( perror_clkd()));

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

    connect( handle_type, SIGNAL(activated(int)), this, SLOT( sel_handle(int)));
}

dGetDiagRec::~dGetDiagRec()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handles;
    delete handle_type;
    delete l_handle_type;
    delete sqlstate_valid;
    delete native_valid;
    delete error_valid;
    delete perror_valid;
    delete buffer_len;
    delete l_buffer_len;
    delete rec_num;
    delete l_rec_num;
}

void dGetDiagField::sel_handle( int /* index */ )
{
    int handle_t;

    handles->clear();
    handle_t = handle_type_struct[ handle_type->currentIndex() ].value;

    pOdbcTest->fill_handle_list( handle_t, handles );
}

void dGetDiagField::diag_ptr_clkd()
{
    if ( diag_ptr_valid->isChecked() )
        diag_ptr_valid->setText( "DiagInfoPtr: SQL_NULL_POINTER" );
    else
        diag_ptr_valid->setText( "DiagInfoPtr: VALID" );
}

void dGetDiagField::strlen_clkd()
{
    if ( strlen_valid->isChecked() )
        strlen_valid->setText( "StringLengthPtr: SQL_NULL_POINTER" );
    else
        strlen_valid->setText( "StringLengthPtr: VALID" );
}

void dGetDiagField::Ok()
{
    int htype = handle_type_struct[ handle_type->currentIndex() ].value;
    OdbcHandle *hand = pOdbcTest->extract_handle_list( htype, handles );
    SQLHANDLE in_handle = SQL_NULL_HANDLE;
    SQLSMALLINT b_len, *strlen_ptr, strlen_val, attribute;
    SQLINTEGER rec_number;
    SQLCHAR *buf;

    if ( hand  )
        in_handle = hand->getHandle();

    pOdbcTest->out_win->append( "SQLGetDiagField():" );
    pOdbcTest->out_win->append( "  In:" );

    txt.sprintf( "    Handle Type: %s", handle_type_struct[ handle_type->currentIndex() ].text );
    pOdbcTest->out_win->append( txt );

    if ( in_handle )
        txt.sprintf( "    Handle: %p", in_handle );
    else
        txt.sprintf( "    Handle: SQL_NULL_HANDLE" );
    pOdbcTest->out_win->append( txt );

    rec_number = rec_num->text().toInt();
    txt.sprintf( "    RecNumber: %d", rec_number );

    attribute = field_type_struct[ diag_info->currentIndex() ].attr;
    txt.sprintf( "    DiagIdentifier: %s=%d", 
                 field_type_struct[ diag_info->currentIndex() ].text,
                 field_type_struct[ diag_info->currentIndex() ].attr );

    b_len = buffer_len->text().toInt();
    if ( diag_ptr_valid->isChecked() )
    {
        buf = NULL;
        txt.sprintf( "    DiagInfo: <null pointer>" );
    }
    else
    {
        if ( b_len < 0 )
            b_len = 300;

        buf = new SQLCHAR[ b_len ];

        txt.sprintf( "    DiagInfo: %p", buf );
    }
    pOdbcTest->out_win->append( txt );

    if ( strlen_valid->isChecked() )
    {
        txt.sprintf( "    StringLengthPtr: <null pointer>" );
        strlen_ptr = NULL;
    }
    else
    {
        strlen_ptr = &strlen_val;
        strlen_val = -9999;
        txt.sprintf( "    StringLengthPtr: %p", strlen_ptr );
    }
    pOdbcTest->out_win->append( txt );

    SQLRETURN ret = SQLGetDiagField( htype, in_handle, rec_number,
                                     attribute, buf, b_len, strlen_ptr );

    pOdbcTest->out_win->append( "  Return:" );
    txt.sprintf( "    %s=%d", pOdbcTest->return_as_text( ret ), ret );
    pOdbcTest->out_win->append( txt );

    if ( SQL_SUCCEEDED( ret ))
    {
        pOdbcTest->out_win->append( "  Out:" );
        if ( field_type_struct[ diag_info->currentIndex() ].data_type == SQL_INTEGER )
        {
            if ( buf )
            {
                int lval;

                memcpy( &lval, buf, sizeof( lval ));
                txt.sprintf( "    *DiagInfo: %d", lval );
                pOdbcTest->out_win->append( txt );
            }
        }
        else
        {
            if ( buf )
            {
                txt.sprintf( "    *DiagInfo: %s", buf );
                pOdbcTest->out_win->append( txt );
            }
        }

        if ( strlen_ptr )
        {
            if ( strlen_val == -9999 )
            {
                txt.sprintf( "    *StringLengthPtr: <unchanged>" );
            }
            else
            {
                txt.sprintf( "    *StringLengthPtr: %d", strlen_val );
            }
            pOdbcTest->out_win->append( txt );
        }
    }

    pOdbcTest->out_win->append( "" );

    if ( buf )
        delete buf;
}

dGetDiagField::dGetDiagField( OdbcTest *pOdbcTest, QString name )
: QDialog( pOdbcTest )
{
    setWindowTitle( name );
    setModal( true );
    this->pOdbcTest = pOdbcTest;

    ok = new QPushButton( "OK", this );
    ok->setGeometry( 250,10, 70,25 );

    cancel = new QPushButton( "Cancel", this );
    cancel->setGeometry( 330,10, 70,25 );

    help = new QPushButton( "Help", this );
    help->setGeometry( 410,10, 70,25 );

    handle_type = new QComboBox( this );
    handle_type->setGeometry( 130, 50, 200, 20 );
    pOdbcTest->fill_list_box( handle_type_struct, handle_type );

    l_handle_type = new QLabel( "Handle Type:", this );
    l_handle_type->setGeometry( 10, 50, 120, 20 );

    handles = new QComboBox( this );
    handles->setGeometry( 130, 80, 200, 20 );
    pOdbcTest->fill_handle_list( SQL_HANDLE_ENV, handles );

    l_handles = new QLabel( "Handle:", this );
    l_handles->setGeometry( 10, 80, 120, 20 );

    rec_num = new QLineEdit( this );
    rec_num->setGeometry( 130, 110, 70, 20 );
    rec_num->setMaxLength( 6 );
    rec_num->setText( "1" );

    l_rec_num = new QLabel( "Rec Number:", this );
    l_rec_num->setGeometry( 10, 110, 100, 20 );

    diag_info = new QComboBox( this );
    diag_info->setGeometry( 130, 140, 350, 20 );
    pOdbcTest->fill_list_box( field_type_struct, diag_info );

    l_diag_info = new QLabel( "Diag Identifier::", this );
    l_diag_info->setGeometry( 10, 140, 120, 20 );

    diag_ptr_valid = new QCheckBox( "DiagInfoPtr: VALID", this );
    diag_ptr_valid->setGeometry( 10, 170, 300, 15 );

    buffer_len = new QLineEdit( this );
    buffer_len->setGeometry( 130, 200, 70, 20 );
    buffer_len->setMaxLength( 6 );
    buffer_len->setText( "300" );

    l_buffer_len = new QLabel( "Buffer Length:", this );
    l_buffer_len->setGeometry( 10, 200, 100, 20 );

    strlen_valid = new QCheckBox( "pcbErrorMsg: VALID", this );
    strlen_valid->setGeometry( 10, 230, 300, 15 );

    connect( diag_ptr_valid, SIGNAL( clicked()), this, SLOT( diag_ptr_clkd()));
    connect( strlen_valid, SIGNAL( clicked()), this, SLOT( strlen_clkd()));

    connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
    connect( ok, SIGNAL(clicked()), SLOT(Ok()) );
    connect( ok, SIGNAL(clicked()), SLOT(accept()) );

    connect( handle_type, SIGNAL(activated(int)), this, SLOT( sel_handle(int)));
}

dGetDiagField::~dGetDiagField()
{
    delete ok;
    delete cancel;
    delete help;
    delete handles;
    delete l_handles;
    delete handle_type;
    delete l_handle_type;
    delete diag_ptr_valid;
    delete strlen_valid;
    delete buffer_len;
    delete l_buffer_len;
    delete rec_num;
    delete l_rec_num;
}

void OdbcTest::slotGetDiagRec()
{
    dGetDiagRec *dlg = new dGetDiagRec( this, "SQLGetDiagRec" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotGetDiagField()
{
    dGetDiagField *dlg = new dGetDiagField( this, "SQLGetDiagField" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotError()
{
    dError *dlg = new dError( this, "SQLError" );

    dlg->exec();

    delete dlg;
}

void OdbcTest::slotErrorsAll()
{
    QMessageBox::about( this, "ODBC Test",
                        "Not yet implemented" );
}

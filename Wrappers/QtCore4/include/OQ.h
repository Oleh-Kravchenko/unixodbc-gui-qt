/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 1
 * \date    2008
 * \license Copyright unixODBC-CPP Project 2003-2009, LGPL
 */
#ifndef ODBC_H
#define ODBC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

using namespace std;

/*
 * This comment is for unixODBC.
 *
 * unixODBC will use a 2-byte wide char (unsigned short) for unicode - by default. We want it to use the 
 * system defined default (wchar_t). So we build unixODBC with the SQL_WCHART_CONVERT flag and then build
 * our code with the flag as well. This allows us to use C wide-char functions and C++ basic_string 
 * without having to dumb the string down to 16 bit.
 *
 * We define SQL_WCHART_CONVERT on the compile-line. We do not define UNICODE on the compile-line for unixODBC 
 * - we define it in the code that needs it.
 */
#ifdef SQL_WCHART_CONVERT
    #define UNICODE
#endif

/*
 * Use ODBCString as our C++ version of a TCHAR. Hopefully we can get rid of all the plain 
 * C string calls and just use ODBCString.
 */
#ifdef UNICODE
    typedef basic_string<wchar_t> ODBCString;
#else
    typedef basic_string<char> ODBCString;
#endif

#ifdef WIN32
    /*
     * With MS'ism UNICODE is passed in as a compiler option but _UNICODE is defined otherwise? I define
     * here. Its probably not used on other platforms.
     */
    #ifdef UNICODE
        #define _UNICODE
        #define ODBCEof WEOF
    #else
        #define ODBCEof EOF
    #endif
    
    #include <windows.h>
    #include <tchar.h>
    #include <sqlext.h>
    #include <odbcinst.h>

    /*
     * With MS'ism we use SQLTCHAR and things pretty much just work. We can build for ASCII or define
     * UNICODE to build for wide-char (a 16bit char for MS'ism).
     */
    #define ODBCCHAR SQLTCHAR 
    #define ODBCCPTR LPWSTR

    #define ODBCStrNCpy(sDest,nDestMaxChars,sSource,nSourceMaxChars) _tcsncpy_s(sDest,nDestMaxChars,sSource,nSourceMaxChars)
    #define ODBCStrDup(sSource) _tcsdup(sSource)
    #define ODBCStrCpy(sDest,sSource) _tcscpy_s(sDest,sSource)
    #define ODBCStrLen(s) _tcslen(s)
    #define ODBCToI(s) _tstoi(s)
    #define ODBCToL(s,a,b) _tcstol(s,a,b)
    #define ODBCFGetC(f) _fgettc(f)
    #define ODBCFGetS(a,b,c) _fgetts(a,b,c)
    #define ODBCIsSpace(a) _istspace(a)
    #define ODBCStrNCmp(a,b,c) _tcsnccmp(a,b,c)
    #define ODBCStrCaseCmp _tcsicmp
    #define ODBCPutS(a,b) _fputts(a,b)
    #define ODBCPrintF _tprintf_s
    #define ODBCFPutS _fputts
    #define ODBCPutChar _puttchar
    #define ODBCStrCat _tcscat_s
    #define ODBCFPrintF _ftprintf_s
    #define ODBCSPrintF _stprintf
#else

    #include <sqlext.h>

    /*
     * With UNIX'ism (and gcc) we do not have a fully baked SQLTCHAR (just the teaser unixODBC has to offer) so we
     * do our own version of it here.
     */
    #ifdef UNICODE
        #include <sqlucode.h>

        #define ODBCCPTR LPWSTR
        #define ODBCCHAR SQLWCHAR

        #define TEXT(a) (const ODBCCHAR*)(L##a)
        #define ODBCStrNCpy(sDest,nDestMaxChars,sSource,nSourceChars) wcsncpy(sDest,sSource,nDestMaxChars); 
        #define ODBCStrDup(sSource) wcsdup(sSource)
        #define ODBCStrCpy(sDest,sSource) wcscpy(sDest,sSource)
        #define ODBCStrLen(s) wcslen(s)
        #define ODBCToI(s) aoti(s) 
        #define ODBCToL(s,a,b) atol(s)
        #define ODBCFGetC(f) fgetwc(f)
        #define ODBCEof WEOF
        #define ODBCFGetS(a,b,c) fgetws(a,b,c)
        #define ODBCIsSpace(a) iswspace(a)
        #define ODBCStrNCmp(a,b,c) wcsncmp(a,b,c)
        #define ODBCPutS(a,b) fputws(a,b)
        #define ODBCPrintF wprintf
        #define ODBCFPutS fputws
        #define ODBCPutChar putwchar
        #define ODBCStrCat(a,b,c) strcat(a,c)
        #define ODBCFPrintF wfprintf
    #else
        #define ODBCCPTR LPSTR
        #define ODBCCHAR SQLCHAR

        /* it totally sucks to put the casts in these but we do <sigh> */
        #define TEXT(a) (const ODBCCHAR*)a
        #define ODBCStrNCpy(sDest,nDestMaxChars,sSource,nSourceChars) strncpy((char*)sDest,(char*)sSource,nDestMaxChars); 
        #define ODBCStrDup(sSource) strdup((const char*)sSource)
        #define ODBCStrCpy(sDest,sSource) strcpy((char*)sDest,(char*)sSource)
        #define ODBCStrLen(s) strlen((const char*)s)
        #define ODBCToI(s) atoi((const char*)s)
        #define ODBCToL(s,a,b) atol((const char*)s)
        #define ODBCFGetC(f) fgetc(f)
        #define ODBCEof EOF
        #define ODBCFGetS(a,b,c) (ODBCCHAR*)fgets((char*)a,b,c)
        #define ODBCIsSpace(a) isspace(a)
        #define ODBCStrNCmp(a,b,c) strncmp((const char*)a,(const char*)b,c)
        #define ODBCStrCmp(a,b) strcmp((const char*)a,(const char*)b)
        #define ODBCStrCaseCmp(a,b) strcasecmp((const char*)a,(const char*)b)
        #define ODBCPutS(a,b) fputs((const char*)a,b)
        #define ODBCPrintF printf
        #define ODBCFPutS(a,b) fputs((const char*)a,b)
        #define ODBCPutChar putchar
        #define ODBCStrCat(a,b,c) strcat((char*)a,(const char*)c)
        #define ODBCFPrintF fprintf
        #define ODBCSPrintF sprintf
    #endif

    /*
     * An MS'ism which we ignore with UNIX'ism - compiler still needs to see something.
     */
    #define _TRUNCATE 0

#endif


#endif

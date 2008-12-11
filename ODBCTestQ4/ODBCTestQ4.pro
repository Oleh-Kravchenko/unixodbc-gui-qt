include(../common.pri)
include(../config.pri)
include(../defines.pri)
include(../odbc.pri)

TEMPLATE= app
TARGET  = ODBCTestQ4
VERSION = %V_MAJOUR%.%V_MINOR%.%V_RELEASE%
DESTDIR	= ../bin

INCLUDEPATH	+= ../ini
LIBS		+= -L../lib -lini

HEADERS		= \
		attr.h \
		catalog.h \
		conn.h \
		desc.h \
		diag.h \
		env.h \
		odbctest.h \
		results.h \
		stmt.h \
		tools.h

SOURCES 	= \
		attr.cpp \
		catalog.cpp \
		conn.cpp \
		desc.cpp \
		diag.cpp \
		edit.cpp \
		env.cpp \
		installer.cpp \
		odbctest.cpp \
		open.cpp \
		results.cpp \
		stmt.cpp \
		tools.cpp


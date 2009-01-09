include(../common.pri)
include(../config.pri)
include(../defines.pri)
include(../odbc.pri)

win32 {
        LIBS            += ..\lib\gtrtstQ4.lib
        LIBS            += user32.lib
}

TEMPLATE        = app
TARGET          = ODBCTestQ4
VERSION         = 1.0.0
DESTDIR	        = ../bin

RESOURCES       = 

HEADERS		= \
		attr.h \
		catalog.h \
		conn.h \
		desc.h \
		diag.h \
		DlgDbcConnect.h \
		DlgToolsManageAutoTest.h \
		DlgToolsManageTestGroup.h \
		DlgToolsManageTest.h \
		DlgToolsNewGroup.h \
		DlgToolsNewSource.h \
		DlgToolsRunAutoTests.h \
		env.h \
		OdbcHandle.h \
		OdbcTest.h \
		results.h \
		stmt.h


SOURCES 	= \
		attr.cpp \
		catalog.cpp \
		conn.cpp \
		desc.cpp \
		diag.cpp \
		DlgDbcConnect.cpp \
		DlgToolsManageAutoTest.cpp \
		DlgToolsManageTest.cpp \
		DlgToolsManageTestGroup.cpp \
		DlgToolsNewGroup.cpp \
		DlgToolsNewSource.cpp \
		DlgToolsRunAutoTests.cpp \
		env.cpp \
		installer.cpp \
		main.cpp \
		OdbcHandle.cpp \
		OdbcTest.cpp \
		results.cpp \
		stmt.cpp


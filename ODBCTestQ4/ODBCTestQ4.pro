include(../common.pri)
include(../config.pri)
include(../defines.pri)
include(../odbc.pri)

win32 {
        LIBS            += ..\lib\gtrtstQ4.lib
        LIBS            += user32.lib
}

unix {
        LIBS            += -L../lib -lgtrtstQ4
}

TEMPLATE        = app
TARGET          = ODBCTestQ4
VERSION 	= 1.0.1
DESTDIR	        = ../bin

# RC_FILE         = ODBCTestQ4.rc
# RESOURCES       =

HEADERS		= \
	attr.h \
	catalog.h \
	conn.h \
	desc.h \
	diag.h \
	DlgDbcConnect.h \
	DlgEnvAllocEnv.h \
	DlgEnvAllocHandle.h \
	DlgEnvDataSources.h \
	DlgEnvDrivers.h \
	DlgEnvEndTran.h \
	DlgEnvFreeEnv.h \
	DlgEnvFreeHandle.h \
	DlgEnvTransact.h \
	DlgToolsManageAutoTest.h \
	DlgToolsManageTest.h \
	DlgToolsManageTestGroup.h \
	DlgToolsNewGroup.h \
	DlgToolsNewSource.h \
	DlgToolsRunAutoTests.h \
	main.h \
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
	DlgEnvAllocEnv.cpp \
	DlgEnvAllocHandle.cpp \
	DlgEnvDataSources.cpp \
	DlgEnvDrivers.cpp \
	DlgEnvEndTran.cpp \
	DlgEnvFreeEnv.cpp \
	DlgEnvFreeHandle.cpp \
	DlgEnvTransact.cpp \
	DlgToolsManageAutoTest.cpp \
	DlgToolsManageTest.cpp \
	DlgToolsManageTestGroup.cpp \
	DlgToolsNewGroup.cpp \
	DlgToolsNewSource.cpp \
	DlgToolsRunAutoTests.cpp \
	installer.cpp \
	main.cpp \
	OdbcHandle.cpp \
	OdbcTest.cpp \
	results.cpp \
	stmt.cpp

#
# INSTALLS
#
!win32 {
target.path = $$INSTALL_TARGET_BIN
INSTALLS += target
}


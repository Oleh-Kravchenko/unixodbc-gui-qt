include(../common.pri)
include(../config.pri)
include(../defines.pri)
include(../odbc.pri)

TEMPLATE= lib
TARGET  = gtrtstQ4
DESTDIR	= ../lib
CONFIG	+= staticlib

HEADERS = 

SOURCES = \
	szLogPrintf.cpp \
	szMessageBox.cpp

#
# INSTALLS
#
!win32 {
target.path = $$INSTALL_TARGET_LIB
INSTALLS += target
}


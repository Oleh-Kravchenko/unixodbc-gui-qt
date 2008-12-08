TEMPLATE        = lib
VERSION         = 1.0.1
TARGET          = odbcplus 
DESTDIR         = ../../../lib
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += staticlib
CONFIG          -= qt

INCLUDEPATH     += ../include

HEADERS =       ../include/ODBC.h \
                ../include/ODBCConnection.h \
                ../include/ODBCConsole.h \
                ../include/ODBCDiagnostic.h \
		../include/ODBCEnvironment.h \
                ../include/ODBCHandle.h \
		../include/ODBCMessage.h \
		../include/ODBCStatement.h \
		../include/ODBCSystem.h \
		../include/ODBCVariant.h
SOURCES =       ODBCConnection.cpp \
                ODBCConsole.cpp \
                ODBCDiagnostic.cpp \
		ODBCEnvironment.cpp \
                ODBCHandle.cpp \
		ODBCMessage.cpp \
		ODBCStatement.cpp \
		ODBCSystem.cpp \
		ODBCVariant.cpp


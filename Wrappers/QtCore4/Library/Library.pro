TEMPLATE        = lib
VERSION 	= %V_MAJOUR%.%V_MINOR%.%V_RELEASE%
TARGET          = odbc_OQ 
DESTDIR         = ../../../lib
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += staticlib
CONFIG          += console

INCLUDEPATH     += ../include ../../CPP/include

HEADERS =       ../include/OQConnection.h \
		../include/OQConsole.h \
		../include/OQEnvironment.h \
		../include/OQStatement.h \
		../include/OQSystem.h
SOURCES =       OQConnection.cpp \
                OQConsole.cpp \
		OQEnvironment.cpp \
		OQStatement.cpp \
		OQSystem.cpp


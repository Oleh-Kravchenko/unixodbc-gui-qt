TEMPLATE        = lib
VERSION 	= %V_MAJOUR%.%V_MINOR%.%V_RELEASE%
TARGET          = OQ4 
DESTDIR         = ../../../lib
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += staticlib
CONFIG          += console

INCLUDEPATH     += ../include

HEADERS =       ../include/OQConnection.h \
		../include/OQConsole.h \
		../include/OQDiagnostic.h \
		../include/OQEnvironment.h \
		../include/OQHandle.h \
		../include/OQMessage.h \
		../include/OQStatement.h \
		../include/OQSystem.h
SOURCES =       OQConnection.cpp \
                OQConsole.cpp \
                OQDiagnostic.cpp \
		OQEnvironment.cpp \
		OQHandle.cpp \
		OQMessage.cpp \
		OQStatement.cpp \
		OQSystem.cpp


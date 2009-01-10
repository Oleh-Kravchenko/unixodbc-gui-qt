TEMPLATE        = lib
VERSION 	= %V_MAJOUR%.%V_MINOR%.%V_RELEASE%
TARGET          = odbcqg4 
DESTDIR         = ../../../lib
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += staticlib

INCLUDEPATH     += ../include  ../../CPP/include  ../../QtCore4/include

HEADERS =       ../include/ODBCQGConnection.h \
		../include/ODBCQGEnvironment.h \
                ../include/ODBCQGLogin.h \
		../include/ODBCQGMessageOutput.h \
		../include/ODBCQGPropertiesDelegate.h \
		../include/ODBCQGPropertiesDialog.h \
                ../include/ODBCQGPropertiesModel.h \
                ../include/ODBCQGProperty.h \
		../include/ODBCQGStatement.h \
		../include/ODBCQGSystem.h
SOURCES =       ODBCQGConnection.cpp \
		ODBCQGEnvironment.cpp \
                ODBCQGLogin.cpp \
		ODBCQGMessageOutput.cpp \
		ODBCQGPropertiesDelegate.cpp \
		ODBCQGPropertiesDialog.cpp \
                ODBCQGPropertiesModel.cpp \
                ODBCQGProperty.cpp \
		ODBCQGStatement.cpp \
		ODBCQGSystem.cpp


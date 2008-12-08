TEMPLATE         = app 
TARGET           = ODBCConsole
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += console
CONFIG          -= qt
INCLUDEPATH     += ../include

LIBS += -L../../../lib -lodbcplus

HEADERS		=
SOURCES 	= main.cpp



TEMPLATE         = app 
TARGET           = ODBCQConsole
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += console
CONFIG          -= qt
INCLUDEPATH     += ../include  ../../CPP/include

LIBS += -L../../../lib -lodbcplus -lodbcq4

HEADERS		=
SOURCES 	= main.cpp



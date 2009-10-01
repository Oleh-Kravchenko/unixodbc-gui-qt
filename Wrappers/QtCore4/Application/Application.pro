TEMPLATE         = app 
TARGET           = OQConsole4
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += console
CONFIG          -= qt
INCLUDEPATH     += ../include

LIBS += -L../../../lib -lOQ4

HEADERS		=
SOURCES 	= main.cpp



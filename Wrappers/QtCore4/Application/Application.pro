TEMPLATE         = app 
TARGET           = OQConsole4
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )
CONFIG          += console
CONFIG          -= qt
INCLUDEPATH     += ../include  ../../CPP/include

LIBS += -L../../../lib -lodbc_CPP -lodbc_OQ4

HEADERS		=
SOURCES 	= main.cpp



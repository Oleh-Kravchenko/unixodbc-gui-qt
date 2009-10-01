TEMPLATE         = app 
TARGET           = OQGConsole4
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )

INCLUDEPATH     += ../include  ../../QtCore4/include

LIBS += -L../../../lib -lOQG4  -lOQ

HEADERS		= \
                OQGConsole4.h
SOURCES 	= \
                main.cpp \
                OQGConsole4.cpp



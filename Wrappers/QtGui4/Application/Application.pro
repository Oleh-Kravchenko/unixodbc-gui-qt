TEMPLATE         = app 
TARGET           = odbcqg4
DESTDIR          = ../../../bin
include( ../../../common.pri )
include( ../../../config.pri )
include( ../../../defines.pri )
include( ../../../odbc.pri )

INCLUDEPATH     += ../include  ../../CPP/include  ../../QtCore4/include

LIBS += -L../../../lib -lodbcplus -lodbcq4 -lodbcqg4

HEADERS		= \
                odbcqg.h
SOURCES 	= \
                main.cpp \
                odbcqg.cpp



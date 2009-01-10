#
# a qmake project file - an alternative to GNU auto tools
#
TEMPLATE	= lib
TARGET          = ini 
DESTDIR		= ../lib
CONFIG		+= staticlib

include( ../common.pri )
include( ../config.pri )
include( ../defines.pri )

HEADERS		= ini.h
SOURCES		= _iniDump.c \
		_iniObjectRead.c \
		_iniPropertyRead.c \
		_iniScanUntilObject.c \
		iniAllTrim.c \
		iniAppend.c \
		iniClose.c \
		iniCommit.c \
		iniCursor.c \
		iniDelete.c \
		iniElement.c \
		iniElementCount.c \
		iniGetBookmark.c \
		iniGotoBookmark.c \
		iniObject.c \
		iniObjectDelete.c \
		iniObjectEOL.c \
		iniObjectFirst.c \
		iniObjectInsert.c \
		iniObjectLast.c \
		iniObjectNext.c \
		iniObjectSeek.c \
		iniObjectSeekSure.c \
		iniObjectUpdate.c \
		iniOpen.c \
		iniProperty.c \
		iniPropertyDelete.c \
		iniPropertyEOL.c \
		iniPropertyFirst.c \
		iniPropertyInsert.c \
		iniPropertyLast.c \
		iniPropertyNext.c \
		iniPropertySeek.c \
		iniPropertySeekSure.c \
		iniPropertyUpdate.c \
		iniPropertyValue.c \
		iniToUpper.c \
		iniValue.c


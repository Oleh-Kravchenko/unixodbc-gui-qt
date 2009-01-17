bin_PROGRAMS = OQGConsole4

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-I../include \
	-I../../QtCore4/include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\"

#	$(LTDLINCL)

OQGConsole4_LDADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst \
	-lodbc_CPP \
	../../QtCore4/Library/libodbc_OQ4.la \
	../Library/libodbc_OQG4.la

OQGConsole4_DEPENDANCIES = \
	../../QtCore4/Library/libodbc_OQ4.la \
	../Library/libodbc_OQG4.la

OQGConsole4_SOURCES = \
	main.cpp \
	OQGConsole.cpp \
	mOQGConsole.cpp

mOQGConsole.cpp: @srcdir@/OQGConsole.h
	@MOC@ @srcdir@/OQGConsole.h -o mOQGConsole.cpp

CLEANFILES = \
	mOQGConsole.cpp

EXTRA_DIST = \
	OQGConsole.h \
	Connected16.xpm \
	Disconnected16.xpm \
	Execute16.xpm \
	ODBC64.xpm \
	Stop16.xpm


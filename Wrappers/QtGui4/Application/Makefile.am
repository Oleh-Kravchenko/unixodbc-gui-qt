bin_PROGRAMS = OQGConsole4

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-I../include \
	-I../../CPP/include \
	-I../../QtCore4/include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	$(LTDLINCL)

OQGConsole4_LDADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../../CPP/Library/libodbc_CPP.la \
	../../QtCore4/Library/libodbc_OQ.la \
	../Library/libodbcqg4.la

OQGConsole4_DEPENDANCIES = \
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../../CPP/Library/libodbc_CPP.la \
	../../QtCore4/Library/libodbc_OQ.la \
	../Library/libodbcqg4.la

OQGConsole4_SOURCES = \
	main.cpp \
	odbcqg.cpp \
	modbcqg.cpp

modbcqg.cpp: @srcdir@/odbcqg.h
	@MOC@ @srcdir@/odbcqg.h -o modbcqg.cpp

CLEANFILES = \
	modbcqg.cpp

EXTRA_DIST = \
	odbcqg.h \
	Connected16.xpm \
	Disconnected16.xpm \
	Execute16.xpm \
	ODBC64.xpm \
	Stop16.xpm


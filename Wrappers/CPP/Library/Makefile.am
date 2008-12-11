noinst_LTLIBRARIES = libodbcplus.la 

libodbcplus_la_LDFLAGS = -no-undefined 

INCLUDES = \
	-I../include \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	-DSHLIBEXT=\"@SHLIBEXT@\" \
	$(LTDLINCL)

libodbcplus_la_SOURCES = \
	ODBCConnection.cpp \
	ODBCConsole.cpp \
	ODBCDiagnostic.cpp \
	ODBCEnvironment.cpp \
	ODBCHandle.cpp \
	ODBCMessage.cpp \
	ODBCStatement.cpp \
	ODBCSystem.cpp \
	ODBCVariant.cpp

EXTRA_DIST = \
	../include/ODBC.h \
	../include/ODBCConnection.h \
	../include/ODBCConsole.h \
	../include/ODBCDiagnostic.h \
	../include/ODBCEnvironment.h \
	../include/ODBCHandle.h \
	../include/ODBCMessage.h \
	../include/ODBCStatement.h \
	../include/ODBCSystem.h \
	../include/ODBCVariant.h



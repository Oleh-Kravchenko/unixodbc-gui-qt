lib_LTLIBRARIES = libodbcplus.la 

libodbcplus_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

INCLUDES = \
	-I../include \
	-I@top_srcdir@/include \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	-DSHLIBEXT=\"@SHLIBEXT@\" \
	$(LTDLINCL)

libodbcplus_la_LIBADD = \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la 

libodbcplus_la_DEPENDENCIES = \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la 

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



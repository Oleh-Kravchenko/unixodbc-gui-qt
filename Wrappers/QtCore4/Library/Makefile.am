libodbcq4_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

if QT4

lib_LTLIBRARIES = libodbcq4.la 

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	-I../../CPP/include \
	$(QT_CXXFLAGS) \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	-DSHLIBEXT=\"@SHLIBEXT@\" \
	$(LTDLINCL)

libodbcq4_la_LIBADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la  \
	../../CPP/Library/libodbcplus.la 

libodbcq4_la_DEPENDENCIES = \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la \
	../../CPP/Library/libodbcplus.la 

CLEANFILES = \
	mODBCQConnection.cpp \
	mODBCQEnvironment.cpp \
	mODBCQStatement.cpp \
	mODBCQSystem.cpp

libodbcq4_la_SOURCES = \
	ODBCQConnection.cpp \
	ODBCQConsole.cpp \
	ODBCQEnvironment.cpp \
	ODBCQStatement.cpp \
	ODBCQSystem.cpp \
	mODBCQConnection.cpp \
	mODBCQEnvironment.cpp \
	mODBCQStatement.cpp \
	mODBCQSystem.cpp

mODBCQConnection.cpp: @srcdir@/../include/ODBCQConnection.h
	@MOC@ @srcdir@/../include/ODBCQConnection.h -o mODBCQConnection.cpp

mODBCQEnvironment.cpp: @srcdir@/../include/ODBCQEnvironment.h
	@MOC@ @srcdir@/../include/ODBCQEnvironment.h -o mODBCQEnvironment.cpp

mODBCQStatement.cpp: @srcdir@/../include/ODBCQStatement.h
	@MOC@ @srcdir@/../include/ODBCQStatement.h -o mODBCQStatement.cpp

mODBCQSystem.cpp: @srcdir@/../include/ODBCQSystem.h
	@MOC@ @srcdir@/../include/ODBCQSystem.h -o mODBCQSystem.cpp

endif

EXTRA_DIST = \
	../include/ODBCQConnection.h \
	../include/ODBCQConsole.h \
	../include/ODBCQEnvironment.h \
	../include/ODBCQStatement.h \
	../include/ODBCQSystem.h



libodbcqg4_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

if QT4

lib_LTLIBRARIES = libodbcqg4.la 

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	-I../../CPP/include \
	-I../../QtCore4/include \
	$(QT_CXXFLAGS) \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	-DSHLIBEXT=\"@SHLIBEXT@\" \
	$(LTDLINCL)

libodbcqg4_la_LIBADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la  \
	../../CPP/Library/libodbc_CPP.la \
	../../QtCore4/Library/libodbc_OQ.la 

libodbcqg4_la_DEPENDENCIES = \
	../../../DriverManager/libodbc.la \
	../../../odbcinst/libodbcinst.la \
	../../CPP/Library/libodbc_CPP.la \
	../../QtCore4/Library/libodbc_OQ.la 

CLEANFILES = \
	mODBCQGConnection.cpp \
	mODBCQGEnvironment.cpp \
	mODBCQGLogin.cpp \
	mODBCQGMessageOutput.cpp \
	mODBCQGPropertiesDelegate.cpp \
	mODBCQGPropertiesDialog.cpp \
	mODBCQGStatement.cpp \
	mODBCQGSystem.cpp

libodbcqg4_la_SOURCES = \
	ODBCQGConnection.cpp \
	ODBCQGEnvironment.cpp \
	ODBCQGLogin.cpp \
	ODBCQGMessageOutput.cpp \
	ODBCQGProperty.cpp \
	ODBCQGPropertiesDelegate.cpp \
	ODBCQGPropertiesDialog.cpp \
	ODBCQGPropertiesModel.cpp \
	ODBCQGStatement.cpp \
	ODBCQGSystem.cpp \
	mODBCQGConnection.cpp \
	mODBCQGEnvironment.cpp \
	mODBCQGLogin.cpp \
	mODBCQGMessageOutput.cpp \
	mODBCQGPropertiesDelegate.cpp \
	mODBCQGPropertiesDialog.cpp \
	mODBCQGStatement.cpp \
	mODBCQGSystem.cpp

mODBCQGConnection.cpp: @srcdir@/../include/ODBCQGConnection.h
	@MOC@ @srcdir@/../include/ODBCQGConnection.h -o mODBCQGConnection.cpp

mODBCQGEnvironment.cpp: @srcdir@/../include/ODBCQGEnvironment.h
	@MOC@ @srcdir@/../include/ODBCQGEnvironment.h -o mODBCQGEnvironment.cpp

mODBCQGLogin.cpp: @srcdir@/../include/ODBCQGLogin.h
	@MOC@ @srcdir@/../include/ODBCQGLogin.h -o mODBCQGLogin.cpp

mODBCQGMessageOutput.cpp: @srcdir@/../include/ODBCQGMessageOutput.h
	@MOC@ @srcdir@/../include/ODBCQGMessageOutput.h -o mODBCQGMessageOutput.cpp

mODBCQGPropertiesDelegate.cpp: @srcdir@/../include/ODBCQGPropertiesDelegate.h
	@MOC@ @srcdir@/../include/ODBCQGPropertiesDelegate.h -o mODBCQGPropertiesDelegate.cpp

mODBCQGPropertiesDialog.cpp: @srcdir@/../include/ODBCQGPropertiesDialog.h
	@MOC@ @srcdir@/../include/ODBCQGPropertiesDialog.h -o mODBCQGPropertiesDialog.cpp

mODBCQGStatement.cpp: @srcdir@/../include/ODBCQGStatement.h
	@MOC@ @srcdir@/../include/ODBCQGStatement.h -o mODBCQGStatement.cpp

mODBCQGSystem.cpp: @srcdir@/../include/ODBCQGSystem.h
	@MOC@ @srcdir@/../include/ODBCQGSystem.h -o mODBCQGSystem.cpp

EXTRA_DIST = \
	../include/ODBCQGConnection.h \
	../include/ODBCQGEnvironment.h \
	../include/ODBCQGLogin.h \
	../include/ODBCQGMessageOutput.h \
	../include/ODBCQGProperty.h \
	../include/ODBCQGPropertiesDelegate.h \
	../include/ODBCQGPropertiesDialog.h \
	../include/ODBCQGPropertiesModel.h \
	../include/ODBCQGStatement.h \
	Error16.xpm \
	Information16.xpm \
	Warning16.xpm \
	ODBC64.xpm

endif



libodbc_OQG4_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

lib_LTLIBRARIES = libodbc_OQG4.la 

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	-I../../QtCore4/include \
	$(QT_CXXFLAGS) \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	-DSHLIBEXT=\"@SHLIBEXT@\"

#	$(LTDLINCL)

libodbc_OQG4_la_LIBADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst \
	-lodbc_CPP \
	../../QtCore4/Library/libodbc_OQ4.la 

libodbc_OQG4_la_DEPENDENCIES = \
	../../QtCore4/Library/libodbc_OQ4.la 

CLEANFILES = \
	mOQGConnection.cpp \
	mOQGEnvironment.cpp \
	mOQGLogin.cpp \
	mOQGMessageOutput.cpp \
	mOQGPropertiesDelegate.cpp \
	mOQGPropertiesDialog.cpp \
	mOQGStatement.cpp \
	mOQGSystem.cpp

libodbc_OQG4_la_SOURCES = \
	OQGConnection.cpp \
	OQGEnvironment.cpp \
	OQGLogin.cpp \
	OQGMessageOutput.cpp \
	OQGProperty.cpp \
	OQGPropertiesDelegate.cpp \
	OQGPropertiesDialog.cpp \
	OQGPropertiesModel.cpp \
	OQGStatement.cpp \
	OQGSystem.cpp \
	mOQGConnection.cpp \
	mOQGEnvironment.cpp \
	mOQGLogin.cpp \
	mOQGMessageOutput.cpp \
	mOQGPropertiesDelegate.cpp \
	mOQGPropertiesDialog.cpp \
	mOQGStatement.cpp \
	mOQGSystem.cpp

mOQGConnection.cpp: @srcdir@/../include/OQGConnection.h
	@MOC@ @srcdir@/../include/OQGConnection.h -o mOQGConnection.cpp

mOQGEnvironment.cpp: @srcdir@/../include/OQGEnvironment.h
	@MOC@ @srcdir@/../include/OQGEnvironment.h -o mOQGEnvironment.cpp

mOQGLogin.cpp: @srcdir@/../include/OQGLogin.h
	@MOC@ @srcdir@/../include/OQGLogin.h -o mOQGLogin.cpp

mOQGMessageOutput.cpp: @srcdir@/../include/OQGMessageOutput.h
	@MOC@ @srcdir@/../include/OQGMessageOutput.h -o mOQGMessageOutput.cpp

mOQGPropertiesDelegate.cpp: @srcdir@/../include/OQGPropertiesDelegate.h
	@MOC@ @srcdir@/../include/OQGPropertiesDelegate.h -o mOQGPropertiesDelegate.cpp

mOQGPropertiesDialog.cpp: @srcdir@/../include/OQGPropertiesDialog.h
	@MOC@ @srcdir@/../include/OQGPropertiesDialog.h -o mOQGPropertiesDialog.cpp

mOQGStatement.cpp: @srcdir@/../include/OQGStatement.h
	@MOC@ @srcdir@/../include/OQGStatement.h -o mOQGStatement.cpp

mOQGSystem.cpp: @srcdir@/../include/OQGSystem.h
	@MOC@ @srcdir@/../include/OQGSystem.h -o mOQGSystem.cpp

EXTRA_DIST = \
	Error16.xpm \
	Information16.xpm \
	Warning16.xpm \
	ODBC64.xpm



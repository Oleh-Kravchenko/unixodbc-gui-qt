libodbc-OQ4_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

lib_LTLIBRARIES = libodbc-OQ4.la 

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	$(QT_CXXFLAGS) \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\"

#	-DSHLIBEXT=\"@SHLIBEXT@\" \
#	$(LTDLINCL)

libodbc-OQ4_la_LIBADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst \
	-lodbc_CPP

libodbc-OQ4_la_DEPENDENCIES =

CLEANFILES = \
	mOQConnection.cpp \
	mOQEnvironment.cpp \
	mOQStatement.cpp \
	mOQSystem.cpp

libodbc-OQ4_la_SOURCES = \
	OQConnection.cpp \
	OQConsole.cpp \
	OQEnvironment.cpp \
	OQStatement.cpp \
	OQSystem.cpp \
	mOQConnection.cpp \
	mOQEnvironment.cpp \
	mOQStatement.cpp \
	mOQSystem.cpp

mOQConnection.cpp: @srcdir@/../include/OQConnection.h
	@MOC@ @srcdir@/../include/OQConnection.h -o mOQConnection.cpp

mOQEnvironment.cpp: @srcdir@/../include/OQEnvironment.h
	@MOC@ @srcdir@/../include/OQEnvironment.h -o mOQEnvironment.cpp

mOQStatement.cpp: @srcdir@/../include/OQStatement.h
	@MOC@ @srcdir@/../include/OQStatement.h -o mOQStatement.cpp

mOQSystem.cpp: @srcdir@/../include/OQSystem.h
	@MOC@ @srcdir@/../include/OQSystem.h -o mOQSystem.cpp

EXTRA_DIST = \
	../include/OQConnection.h \
	../include/OQConsole.h \
	../include/OQEnvironment.h \
	../include/OQStatement.h \
	../include/OQSystem.h



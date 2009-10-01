libOQ4_la_LDFLAGS = \
	-version-info @LIB_VERSION@ \
	-export-dynamic

lib_LTLIBRARIES = libOQ4.la 

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	$(QT_CXXFLAGS) \
	-DTHEPREFIX=\"@prefix@\" \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\"

#	-DSHLIBEXT=\"@SHLIBEXT@\" \
#	$(LTDLINCL)

libOQ4_la_LIBADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst

libOQ4_la_DEPENDENCIES =

CLEANFILES = \
	mOQConnection.cpp \
	mOQConsole.cpp \
	mOQEnvironment.cpp \
	mOQHandle.cpp \
	mOQStatement.cpp \
	mOQSystem.cpp

libOQ4_la_SOURCES = \
	OQConnection.cpp \
	OQConsole.cpp \
	OQDiagnostic.cpp \
	OQEnvironment.cpp \
	OQHandle.cpp \
	OQMessage.cpp \
	OQStatement.cpp \
	OQSystem.cpp \
	mOQConnection.cpp \
	mOQConsole.cpp \
	mOQEnvironment.cpp \
	mOQHandle.cpp \
	mOQStatement.cpp \
	mOQSystem.cpp

mOQConnection.cpp: @srcdir@/../include/OQConnection.h
	@MOC@ @srcdir@/../include/OQConnection.h -o mOQConnection.cpp

mOQConsole.cpp: @srcdir@/../include/OQConsole.h
	@MOC@ @srcdir@/../include/OQConsole.h -o mOQConsole.cpp

mOQEnvironment.cpp: @srcdir@/../include/OQEnvironment.h
	@MOC@ @srcdir@/../include/OQEnvironment.h -o mOQEnvironment.cpp

mOQHandle.cpp: @srcdir@/../include/OQHandle.h
	@MOC@ @srcdir@/../include/OQHandle.h -o mOQHandle.cpp

mOQStatement.cpp: @srcdir@/../include/OQStatement.h
	@MOC@ @srcdir@/../include/OQStatement.h -o mOQStatement.cpp

mOQSystem.cpp: @srcdir@/../include/OQSystem.h
	@MOC@ @srcdir@/../include/OQSystem.h -o mOQSystem.cpp




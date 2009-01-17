bin_PROGRAMS = OQConsole

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-I../include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\"

#	$(LTDLINCL)

OQConsole_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst \
	-lodbc_CPP \
	../Library/libodbc_OQ4.la

OQConsole_DEPENDANCIES = \
	../Library/libodbc_OQ4.la

OQConsole_SOURCES = \
	main.cpp




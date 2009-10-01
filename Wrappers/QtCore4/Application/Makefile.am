bin_PROGRAMS = OQConsole4

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-I../include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\"

OQConsole4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst \
	../Library/libOQ4.la

OQConsole4_DEPENDANCIES = \
	../Library/libOQ4.la

OQConsole4_SOURCES = \
	main.cpp




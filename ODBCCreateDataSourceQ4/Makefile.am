bin_PROGRAMS = ODBCCreateDataSourceQ4

INCLUDES = $(QT_CXXFLAGS) \
    -DSYSTEM_FILE_PATH=\"@sysconfdir@\" -DDEFLIB_PATH=\"@libdir@\" $(LTDLINCL)

ODBCCreateDataSourceQ4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst

ODBCCreateDataSourceQ4_DEPENDANCIES = ../odbcinstQ4/libodbcinstQ4.la

ODBCCreateDataSourceQ4_SOURCES = \
	main.cpp


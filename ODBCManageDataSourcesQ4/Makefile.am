bin_PROGRAMS = ODBCManageDataSourcesQ4

INCLUDES = $(QT_CXXFLAGS) \
    -DSYSTEM_FILE_PATH=\"@sysconfdir@\" -DDEFLIB_PATH=\"@libdir@\" $(LTDLINCL)

ODBCManageDataSourcesQ4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst

ODBCManageDataSourcesQ4_DEPENDANCIES = ../odbcinstQ4/libodbcinstQ4.la

ODBCManageDataSourcesQ4_SOURCES = \
	main.cpp


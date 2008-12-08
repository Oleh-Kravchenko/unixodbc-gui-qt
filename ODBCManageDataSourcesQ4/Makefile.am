if QT4
bin_PROGRAMS = ODBCManageDataSourcesQ4

INCLUDES = -I@top_srcdir@/include $(QT_CXXFLAGS) \
    -DSYSTEM_FILE_PATH=\"@sysconfdir@\" -DDEFLIB_PATH=\"@libdir@\" $(LTDLINCL)

ODBCManageDataSourcesQ4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../odbcinst/libodbcinst.la \
	../extras/libodbcextraslc.la \
	../DriverManager/libodbc.la 

ODBCManageDataSourcesQ4_DEPENDANCIES = ../odbcinst/libodbcinst.la ../extras/libodbcextraslc.la ../DriverManager/libodbc.la

ODBCManageDataSourcesQ4_SOURCES = \
	main.cpp
endif

if QT4
bin_PROGRAMS = ODBCCreateDataSourceQ4

INCLUDES = -I@top_srcdir@/include $(QT_CXXFLAGS) \
    -DSYSTEM_FILE_PATH=\"@sysconfdir@\" -DDEFLIB_PATH=\"@libdir@\" $(LTDLINCL)

ODBCCreateDataSourceQ4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../odbcinst/libodbcinst.la \
	../extras/libodbcextraslc.la \
	../DriverManager/libodbc.la 

ODBCCreateDataSourceQ4_DEPENDANCIES = ../odbcinst/libodbcinst.la ../extras/libodbcextraslc.la ../DriverManager/libodbc.la

ODBCCreateDataSourceQ4_SOURCES = \
	main.cpp
endif


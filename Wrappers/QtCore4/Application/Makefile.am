if QT4

bin_PROGRAMS = ODBCQConsole

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-I../include \
	-I../../CPP/include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-DDEFLIB_PATH=\"@libdir@\" \
	$(LTDLINCL)

ODBCQConsole_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../../CPP/Library/libodbcplus.la \
	../Library/libodbcq4.la

ODBCQConsole_DEPENDANCIES = 
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../../CPP/Library/libodbcplus.la \
	../Library/libodbcq4.la

ODBCQConsole_SOURCES = \
	main.cpp

endif




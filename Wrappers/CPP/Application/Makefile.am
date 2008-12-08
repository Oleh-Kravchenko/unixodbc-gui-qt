bin_PROGRAMS = ODBCConsole

INCLUDES = \
	-I@top_srcdir@/include \
	-I../include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	$(LTDLINCL)

ODBCConsole_LDADD = \
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../Library/libodbcplus.la \
	$(LIBLTDL) $(LIBADD_DL) 

ODBCConsole_DEPENDANCIES = \
	../../../odbcinst/libodbcinst.la \
	../../../DriverManager/libodbc.la \
	../Library/libodbcplus.la

ODBCConsole_SOURCES = \
	main.cpp

EXTRA_DIST = 


bin_PROGRAMS = ODBCConsole

INCLUDES = \
	-I../include \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\"

ODBCConsole_LDADD = \
	-lodbcinst \
	-lodbc \
	../Library/libodbcplus.la

ODBCConsole_DEPENDANCIES = \
	../Library/libodbcplus.la

ODBCConsole_SOURCES = \
	main.cpp

EXTRA_DIST = 


#
# \brief	These bring in the core and dev stuff.
#
#
# \sa		*.pri *.pro
#

#
# unixODBC-Test sources must be available so we can access autotest.h. unixODBC-Test
# does not have to be built yet. This is needed for, at least, ODBCTestQ4.
#
INCLUDEPATH	+= $(UNIXODBC_TEST_SRC)/AutoTests/include

# #########################################################
# WIN32
# #########################################################
win32 {
        INCLUDEPATH     += ../../include
#
#       We use MS's Driver Manager and Installer library.
#
        LIBS            += odbc32.lib odbccp32.lib
}

# #########################################################
# MAC/UNIX common
# #########################################################
unix {
}

# #########################################################
# MAC/UNIX specific
# #########################################################
mac {
        LIBS	        += -liodbc -liodbcinst
} else:unix {
#
#       unixODBC-Core and unixODBC-Dev must be installed. Here we bring them into our build.
#
	INCLUDEPATH	+= $(UNIXODBC_DIR)/include 
	LIBS		+= -L$(UNIXODBC_LIBDIR)
	LIBS		+= -lodbc -lodbcinst
}




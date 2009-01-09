#
# \brief	These bring in the core and dev stuff.
#
#
# \sa		*.pri *.pro
#

# #########################################################
# WIN32
# #########################################################
win32 {
        INCLUDEPATH     += ../../include
        INCLUDEPATH     += ../../../unixodbc-test/AutoTests/include
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
#       unixODBC-core and unixODBC-dev must be installed. Here we bring
#	them into our build.
	INCLUDEPATH	+= $(UNIXODBC_DIR)/include
	LIBS		+= -L$(UNIXODBC_LIBDIR)
	LIBS		+= -lodbc -lodbcinst
}




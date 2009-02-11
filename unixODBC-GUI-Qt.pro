#
# building
# ========
#
# This can be built for UNIX'ism or MS'ism.
#
# UNIX'ism
# --------
#
# Install unixODBC-Core and unixODBC-Dev. Set the following
# environment variables to tell us where unixODBC was
# installed;
#
# export UNIXODBC_DIR=/usr
# export UNIXODBC_LIBDIR=$UNIXODBC_DIR/lib64
#
# Get unixODBC-Test (do not build it yet) and set the
# following environment variable to tell us where it is;
#
# export UNIXODBC_TEST_SRC=~/unixodbc-test/trunk
#
# Build This
# 
# $ qmake
# $ make
# $ sudo make install
#
# MS'ism
# ------
#
# Get unixODBC-Test (do not build it yet) and set the
# following environment variable to tell us where it is;
#
# SET UNIXODBC_TEST_SRC=C:/unixodbc-test/trunk
#
# Get & Build unixODBC-CPP and set the following environment 
# variable to tell us where it is;
#
# SET UNIXODBC_CPP=C:/unixODBC-CPP/ODBC++
#
# Build This
# 
# > qmake
# > nmake
#

TEMPLATE	= subdirs

# #########################################################
# WIN32
# #########################################################
win32 {
        DEFINES -= UNICODE 
        DEFINES += _CRT_SECURE_NO_WARNINGS

	SUBDIRS	= \
		gtrtstQ4 \
		ODBCTestQ4 \
                Wrappers
}

# #########################################################
# MAC/UNIX shared
# #########################################################
unix {
	SUBDIRS	= \
		ini \
		odbcinstQ4 \
		gtrtstQ4 \
		ODBCCreateDataSourceQ4 \
		ODBCManageDataSourcesQ4 \
		ODBCTestQ4 \
                Wrappers
}

# #########################################################
# MAC/UNIX specific
# #########################################################
mac {

} else:unix {

}



#
# \brief	These are some DEFINES for qmake.
#
#               Edit these settings, as needed, before using qmake to
#		generate the Makefiles. All sources are likely to use
#		the options reflected here.
#
# \sa		*.pri *.pro 
#

DEFINES = V_MAJOUR=1 V_MINOR=0 V_RELEASE=1

# #########################################################
# WIN32
# #########################################################
win32 {
        DEFINES -= UNICODE 
        DEFINES += _CRT_SECURE_NO_WARNINGS
}

# #########################################################
# MAC/UNIX shared
# #########################################################
unix {
	INSTALL_TARGET_BIN	= /usr/bin
	INSTALL_TARGET_LIB	= /usr/lib64 
}

# #########################################################
# MAC/UNIX specific
# #########################################################
mac {

} else:unix {

}




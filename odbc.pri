#
# \brief	These bring in the core and dev stuff.
#
#               unixODBC-core and unixODBC-dev must be installed. Here we bring
#		them into our build.
#
# \sa		*.pri *.pro
#

INCLUDEPATH	+= /usr/include
LIBS		+= -L/usr/lib64 -lodbc -lodbcinst


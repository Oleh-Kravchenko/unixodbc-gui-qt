if QT4
if QTMDIAREA

bin_PROGRAMS = ODBCDataManagerQ4

INCLUDES = \
	-I@top_srcdir@/include \
	$(QT_CXXFLAGS) \
	-DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	-I../Wrappers/CPP/include \
	-I../Wrappers/QtCore4/include \
	-I../Wrappers/QtGui4/include \
	-DDEFLIB_PATH=\"@libdir@\" \
	$(LTDLINCL)

ODBCDataManagerQ4_LDADD =  \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../ini/libinilc.la \
	../ODBCString/libODBCStringlc.la \
	../odbcinst/libodbcinst.la \
	../extras/libodbcextraslc.la \
	../DriverManager/libodbc.la \
	../Wrappers/CPP/Library/libodbc_CPP.la \
	../Wrappers/QtCore4/Library/libodbc_OQ.la \
	../Wrappers/QtGui4/Library/libodbcqg4.la

ODBCDataManagerQ4_DEPENDANCIES = \
	../ini/libinilc.la \
	../ODBCString/libODBCStringlc.la \
	../odbcinst/libodbcinst.la \
	../extras/libodbcextraslc.la \
	../DriverManager/libodbc.la \
	../Wrappers/CPP/Library/libodbc_CPP.la \
	../Wrappers/QtCore4/Library/libodbc_OQ.la \
	../Wrappers/QtGui4/Library/libodbcqg4.la

CLEANFILES = \
	mDBrowser.cpp \
	mDDataManager.cpp \
	mDEdit.cpp \
	mDEditStatement.cpp \
	mDNode.cpp \
	mDNodeAttribute.cpp \
	mDNodeConnection.cpp \
	mDNodeDataSourceNameFile.cpp \
	mDNodeDataSourceNames.cpp \
	mDNodeDataSourceNameSystem.cpp \
	mDNodeDataSourceNameUser.cpp \
	mDNodeDriver.cpp \
	mDNodeDrivers.cpp \
	mDNodeODBC.cpp \
	mDNodeStatement.cpp \
	mDNodeWidget.cpp \
	mDOutputMessages.cpp \
	mDPropWidget.cpp \
	mODBCDelegateCell.cpp \
	mODBCModel.cpp \
	mODBCModelBrowser.cpp \
	mODBCModelDriver.cpp \
	mODBCModelDrivers.cpp \
	mODBCModelEnvironment.cpp \
	mODBCModelSystem.cpp \
	mODBCViewBrowser.cpp

ODBCDataManagerQ4_SOURCES = \
	main.cpp \
	DBrowser.cpp \
	DDataManager.cpp \
	DDiagnostic.cpp \
	DEdit.cpp \
	DEditStatement.cpp \
	DNode.cpp \
	DNodeAttribute.cpp \
	DNodeConnection.cpp \
	DNodeDataSourceNameFile.cpp \
	DNodeDataSourceNames.cpp \
	DNodeDataSourceNameSystem.cpp \
	DNodeDataSourceNameUser.cpp \
	DNodeDriver.cpp \
	DNodeDrivers.cpp \
	DNodeODBC.cpp \
	DNodeSchema.cpp \
	DNodeSchemas.cpp \
	DNodeStatement.cpp \
	DNodeTable.cpp \
	DNodeTableColumn.cpp \
	DNodeTableColumns.cpp \
	DNodeTables.cpp \
	DNodeWidget.cpp \
	DOutputLog.cpp \
	DOutputMessages.cpp \
	DPropWidget.cpp \
	ODBCDelegateCell.cpp \
	ODBCMetaInfo.cpp \
	ODBCModel.cpp \
	ODBCModelBrowser.cpp \
	ODBCModelDriver.cpp \
	ODBCModelDrivers.cpp \
	ODBCModelEnvironment.cpp \
	ODBCModelSystem.cpp \
	ODBCValueCell.cpp \
	ODBCViewBrowser.cpp \
	mDBrowser.cpp \
	mDDataManager.cpp \
	mDEdit.cpp \
	mDEditStatement.cpp \
	mDNode.cpp \
	mDNodeAttribute.cpp \
	mDNodeConnection.cpp \
	mDNodeDataSourceNameFile.cpp \
	mDNodeDataSourceNames.cpp \
	mDNodeDataSourceNameSystem.cpp \
	mDNodeDataSourceNameUser.cpp \
	mDNodeDriver.cpp \
	mDNodeDrivers.cpp \
	mDNodeODBC.cpp \
	mDNodeStatement.cpp \
	mDNodeWidget.cpp \
	mDOutputMessages.cpp \
	mDPropWidget.cpp \
	mODBCDelegateCell.cpp \
	mODBCModel.cpp \
	mODBCModelBrowser.cpp \
	mODBCModelDriver.cpp \
	mODBCModelDrivers.cpp \
	mODBCModelEnvironment.cpp \
	mODBCModelSystem.cpp \
	mODBCViewBrowser.cpp

mDBrowser.cpp: @srcdir@/DBrowser.h
	@MOC@ @srcdir@/DBrowser.h -o mDBrowser.cpp

mDDataManager.cpp: @srcdir@/DDataManager.h
	@MOC@ @srcdir@/DDataManager.h -o mDDataManager.cpp

mDEdit.cpp: @srcdir@/DEdit.h
	@MOC@ @srcdir@/DEdit.h -o mDEdit.cpp

mDEditStatement.cpp: @srcdir@/DEditStatement.h
	@MOC@ @srcdir@/DEditStatement.h -o mDEditStatement.cpp

mDNode.cpp: @srcdir@/DNode.h
	@MOC@ @srcdir@/DNode.h -o mDNode.cpp

mDNodeAttribute.cpp: @srcdir@/DNodeAttribute.h
	@MOC@ @srcdir@/DNodeAttribute.h -o mDNodeAttribute.cpp

mDNodeConnection.cpp: @srcdir@/DNodeConnection.h
	@MOC@ @srcdir@/DNodeConnection.h -o mDNodeConnection.cpp

mDNodeDataSourceNameFile.cpp: @srcdir@/DNodeDataSourceNameFile.h
	@MOC@ @srcdir@/DNodeDataSourceNameFile.h -o mDNodeDataSourceNameFile.cpp

mDNodeDataSourceNames.cpp: @srcdir@/DNodeDataSourceNames.h
	@MOC@ @srcdir@/DNodeDataSourceNames.h -o mDNodeDataSourceNames.cpp

mDNodeDataSourceNameSystem.cpp: @srcdir@/DNodeDataSourceNameSystem.h
	@MOC@ @srcdir@/DNodeDataSourceNameSystem.h -o mDNodeDataSourceNameSystem.cpp

mDNodeDataSourceNameUser.cpp: @srcdir@/DNodeDataSourceNameUser.h
	@MOC@ @srcdir@/DNodeDataSourceNameUser.h -o mDNodeDataSourceNameUser.cpp

mDNodeDriver.cpp: @srcdir@/DNodeDriver.h
	@MOC@ @srcdir@/DNodeDriver.h -o mDNodeDriver.cpp

mDNodeDrivers.cpp: @srcdir@/DNodeDrivers.h
	@MOC@ @srcdir@/DNodeDrivers.h -o mDNodeDrivers.cpp

mDNodeODBC.cpp: @srcdir@/DNodeODBC.h
	@MOC@ @srcdir@/DNodeODBC.h -o mDNodeODBC.cpp

mDNodeStatement.cpp: @srcdir@/DNodeStatement.h
	@MOC@ @srcdir@/DNodeStatement.h -o mDNodeStatement.cpp

mDNodeWidget.cpp: @srcdir@/DNodeWidget.h
	@MOC@ @srcdir@/DNodeWidget.h -o mDNodeWidget.cpp

mDOutputMessages.cpp: @srcdir@/DOutputMessages.h
	@MOC@ @srcdir@/DOutputMessages.h -o mDOutputMessages.cpp

mDPropWidget.cpp: @srcdir@/DPropWidget.h
	@MOC@ @srcdir@/DPropWidget.h -o mDPropWidget.cpp

mODBCDelegateCell.cpp: @srcdir@/ODBCDelegateCell.h
	@MOC@ @srcdir@/ODBCDelegateCell.h -o mODBCDelegateCell.cpp

mODBCModel.cpp: @srcdir@/ODBCModel.h
	@MOC@ @srcdir@/ODBCModel.h -o mODBCModel.cpp

mODBCModelBrowser.cpp: @srcdir@/ODBCModelBrowser.h
	@MOC@ @srcdir@/ODBCModelBrowser.h -o mODBCModelBrowser.cpp

mODBCModelDriver.cpp: @srcdir@/ODBCModelDriver.h
	@MOC@ @srcdir@/ODBCModelDriver.h -o mODBCModelDriver.cpp

mODBCModelDrivers.cpp: @srcdir@/ODBCModelDrivers.h
	@MOC@ @srcdir@/ODBCModelDrivers.h -o mODBCModelDrivers.cpp

mODBCModelEnvironment.cpp: @srcdir@/ODBCModelEnvironment.h
	@MOC@ @srcdir@/ODBCModelEnvironment.h -o mODBCModelEnvironment.cpp

mODBCModelSystem.cpp: @srcdir@/ODBCModelSystem.h
	@MOC@ @srcdir@/ODBCModelSystem.h -o mODBCModelSystem.cpp

mODBCViewBrowser.cpp: @srcdir@/ODBCViewBrowser.h
	@MOC@ @srcdir@/ODBCViewBrowser.h -o mODBCViewBrowser.cpp

endif
endif

EXTRA_DIST = \
	DBrowser.h \
	DDataManager.h \
	DDiagnostic.h \
	DEdit.h \
	DEditStatement.h \
	DNode.h \
	DNodeAttribute.h \
	DNodeConnection.h \
	DNodeDataSourceNameFile.h \
	DNodeDataSourceNames.h \
	DNodeDataSourceNameSystem.h \
	DNodeDataSourceNameFile.h \
	DNodeDriver.h \
	DNodeDrivers.h \
	DNodeODBC.h \
	DNodeSchema.h \
	DNodeSchemas.h \
	DNodeTable.h \
	DNodeTableColumn.h \
	DNodeTableColumns.h \
	DNodeTables.h


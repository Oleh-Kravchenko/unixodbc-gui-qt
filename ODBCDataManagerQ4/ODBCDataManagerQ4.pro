TEMPLATE         = app 
TARGET           = ODBCDataManagerQ4
DESTDIR          = ../bin
include( ../common.pri )
include( ../config.pri )
include( ../defines.pri )
include( ../odbc.pri )

INCLUDEPATH     += ../../Wrappers/CPP/include  ../../Wrappers/QtCore4/include

LIBS += -L../../lib -lodbcplus -lodbcq4 -lodbcqg4

HEADERS		= \
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
	DNodeDataSourceNameUser.h \
	DNodeDriver.h \
	DNodeDrivers.h \
	DNodeODBC.h \
	DNodeSchema.h \
	DNodeSchemas.h \
	DNodeStatement.h \
	DNodeTable.h \
	DNodeTableColumn.h \
	DNodeTableColumns.h \
	DNodeTables.h \
	DNodeWidget.h \
	DOutputLog.h \
	DOutputMessages.h \
	DPropWidget.h \
	ODBCDelegateCell.h \
	ODBCMetaInfo.h \
	ODBCModel.h \
	ODBCModelBrowser.h \
	ODBCModelDriver.h \
	ODBCModelDrivers.h \
	ODBCModelEnvironment.h \
	ODBCModelSystem.h \
	ODBCValueCell.h \
	ODBCViewBrowser.h
SOURCES 	= \
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
	ODBCViewBrowser.cpp

#
# INSTALLS
#
target.path = $$INSTALL_TARGET_BIN
INSTALLS += target


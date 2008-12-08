include(../common.pri)
include(../config.pri)
include(../defines.pri)
include(../odbc.pri)

TEMPLATE= lib
TARGET  = odbcinstQ4
VERSION = %V_MAJOUR%.%V_MINOR%.%V_RELEASE%
DESTDIR	= ../lib
CONFIG	+= plugin

INCLUDEPATH	+= ../ini
LIBS		+= -L../lib -lini

HEADERS = \
	CAbout.h \
	CAdvanced.h \
	CDataSourceNameList.h \
	CDataSourceNamesFile.h \
	CDataSourceNamesFileModel.h \
	CDataSourceNames.h \
	CDriverList.h \
	CDriverPrompt.h \
	CDSNWizardProperties.h \
	CDSNWizardDriver.h \
	CDSNWizardEntre.h \
	CDSNWizardFini.h \
	CDSNWizard.h \
	CDSNWizardType.h \
	CFileSelector.h \
	CHelp.h \
	CManageDataSourceNames.h \
	CManageDrivers.h \
	CMonitor.h \
	CMonitorHandleCounts.h \
	CMonitorProcesses.h \
	CODBCConfig.h \
	CODBCInst.h \
	CPage.h \
	CPooling.h \
	CPropertiesDelegate.h \
	CPropertiesDialog.h \
	CPropertiesModel.h \
	CThreading.h \
	CTracing.h \
	About48.xpm \
	Advanced48.xpm \
	Canada.xpm \
	DataSourceName48.xpm \
	DataSourceNameFile48.xpm \
	DataSourceNameSystem48.xpm \
	DataSourceNameUser48.xpm \
	Driver128.xpm \
	Driver48.xpm \
	GreatBritain.xpm \
	Info16.xpm \
	InfoArrow16.xpm \
	NoFlag.xpm \
	ODBC.xpm \
	Pooling48.xpm \
	Set.xpm \
	Stats48.xpm \
	Threading48.xpm \
	Tracing48.xpm \
	ODBCManageDataSources64.xpm \
	WizardCreateDataSourceName.xpm

SOURCES = CAbout.cpp \
	CAdvanced.cpp \
	CDataSourceNameList.cpp \
	CDataSourceNamesFile.cpp \
	CDataSourceNamesFileModel.cpp \
	CDataSourceNames.cpp \
	CDriverList.cpp \
	CDriverPrompt.cpp \
	CDSNWizardProperties.cpp \
	CDSNWizardDriver.cpp \
	CDSNWizardEntre.cpp \
	CDSNWizardFini.cpp \
	CDSNWizard.cpp \
	CDSNWizardType.cpp \
	CFileSelector.cpp \
	CHelp.cpp \
	CManageDataSourceNames.cpp \
	CManageDrivers.cpp \
	CODBCConfig.cpp \
	CODBCInst.cpp \
	CPage.cpp \
	CPooling.cpp \
	CPropertiesDelegate.cpp \
	CPropertiesDialog.cpp \
	CPropertiesModel.cpp \
	CMonitorHandleCounts.cpp \
	CMonitor.cpp \
	CMonitorProcesses.cpp \
	CThreading.cpp \
	CTracing.cpp \
	SQLManageDataSources.cpp



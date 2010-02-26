bin_PROGRAMS = ODBCTestQ4

INCLUDES = $(QT_CXXFLAGS) \
           $(INCLUDES_COMMON) \
           -DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	   $(LTDLINCL)

ODBCTestQ4_LDADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	../gtrtstQ4/libgtrtstQ4.la \
	-lodbc -lodbcinst

ODBCTestQ4_SOURCES = \
	attr.cpp \
	catalog.cpp \
	conn.cpp \
	desc.cpp \
	diag.cpp \
	DlgDbcConnect.cpp \
	DlgEnvAllocEnv.cpp \
	DlgEnvAllocHandle.cpp \
	DlgEnvDataSources.cpp \
	DlgEnvDrivers.cpp \
	DlgEnvEndTran.cpp \
	DlgEnvFreeEnv.cpp \
	DlgEnvFreeHandle.cpp \
	DlgEnvTransact.cpp \
	DlgToolsManageAutoTest.cpp \
	DlgToolsManageTest.cpp \
	DlgToolsManageTestGroup.cpp \
	DlgToolsNewGroup.cpp \
	DlgToolsNewSource.cpp \
	DlgToolsRunAutoTests.cpp \
	installer.cpp \
	main.cpp \
	OdbcHandle.cpp \
	OdbcTest.cpp \
	results.cpp \
	stmt.cpp \
	mattr.cpp \
	mcatalog.cpp \
	mconn.cpp \
	mdesc.cpp \
	mdiag.cpp \
	mDlgDbcConnect.cpp \
	mDlgToolsManageAutoTest.cpp \
	mDlgToolsManageTest.cpp \
	mDlgToolsManageTestGroup.cpp \
	mDlgToolsNewGroup.cpp \
	mDlgToolsNewSource.cpp \
	mDlgToolsRunAutoTests.cpp \
	mDlgEnvAllocEnv.cpp \
	mDlgEnvAllocHandle.cpp \
	mDlgEnvDataSources.cpp \
	mDlgEnvDrivers.cpp \
	mDlgEnvEndTran.cpp \
	mDlgEnvFreeEnv.cpp \
	mDlgEnvFreeHandle.cpp \
	mDlgEnvTransact.cpp \
	mOdbcTest.cpp \
	mresults.cpp \
	mstmt.cpp

mresults.cpp: @srcdir@/results.h
	@MOC@ @srcdir@/results.h -o mresults.cpp

mstmt.cpp: @srcdir@/stmt.h
	@MOC@ @srcdir@/stmt.h -o mstmt.cpp

mOdbcTest.cpp: @srcdir@/OdbcTest.h
	@MOC@ @srcdir@/OdbcTest.h -o mOdbcTest.cpp

mdesc.cpp: @srcdir@/desc.h
	@MOC@ @srcdir@/desc.h -o mdesc.cpp

mdiag.cpp: @srcdir@/diag.h
	@MOC@ @srcdir@/diag.h -o mdiag.cpp

mDlgEnvAllocEnv.cpp: @srcdir@/DlgEnvAllocEnv.h
	@MOC@ @srcdir@/DlgEnvAllocEnv.h -o mDlgEnvAllocEnv.cpp

mDlgEnvAllocHandle.cpp: @srcdir@/DlgEnvAllocHandle.h
	@MOC@ @srcdir@/DlgEnvAllocHandle.h -o mDlgEnvAllocHandle.cpp

mDlgEnvDataSources.cpp: @srcdir@/DlgEnvDataSources.h
	@MOC@ @srcdir@/DlgEnvDataSources.h -o mDlgEnvDataSources.cpp

mDlgEnvDrivers.cpp: @srcdir@/DlgEnvDrivers.h
	@MOC@ @srcdir@/DlgEnvDrivers.h -o mDlgEnvDrivers.cpp

mDlgEnvEndTran.cpp: @srcdir@/DlgEnvEndTran.h
	@MOC@ @srcdir@/DlgEnvEndTran.h -o mDlgEnvEndTran.cpp

mDlgEnvFreeEnv.cpp: @srcdir@/DlgEnvFreeEnv.h
	@MOC@ @srcdir@/DlgEnvFreeEnv.h -o mDlgEnvFreeEnv.cpp

mDlgEnvFreeHandle.cpp: @srcdir@/DlgEnvFreeHandle.h
	@MOC@ @srcdir@/DlgEnvFreeHandle.h -o mDlgEnvFreeHandle.cpp

mDlgEnvTransact.cpp: @srcdir@/DlgEnvTransact.h
	@MOC@ @srcdir@/DlgEnvTransact.h -o mDlgEnvTransact.cpp

mcatalog.cpp: @srcdir@/catalog.h
	@MOC@ @srcdir@/catalog.h -o mcatalog.cpp

mconn.cpp: @srcdir@/conn.h
	@MOC@ @srcdir@/conn.h -o mconn.cpp

mattr.cpp: @srcdir@/attr.h
	@MOC@ @srcdir@/attr.h -o mattr.cpp

mDlgDbcConnect.cpp: @srcdir@/DlgDbcConnect.h
	@MOC@ @srcdir@/DlgDbcConnect.h -o mDlgDbcConnect.cpp

mDlgToolsManageAutoTest.cpp: @srcdir@/DlgToolsManageAutoTest.h
	@MOC@ @srcdir@/DlgToolsManageAutoTest.h -o mDlgToolsManageAutoTest.cpp

mDlgToolsManageTest.cpp: @srcdir@/DlgToolsManageTest.h
	@MOC@ @srcdir@/DlgToolsManageTest.h -o mDlgToolsManageTest.cpp

mDlgToolsManageTestGroup.cpp: @srcdir@/DlgToolsManageTestGroup.h
	@MOC@ @srcdir@/DlgToolsManageTestGroup.h -o mDlgToolsManageTestGroup.cpp

mDlgToolsNewGroup.cpp: @srcdir@/DlgToolsNewGroup.h
	@MOC@ @srcdir@/DlgToolsNewGroup.h -o mDlgToolsNewGroup.cpp

mDlgToolsNewSource.cpp: @srcdir@/DlgToolsNewSource.h
	@MOC@ @srcdir@/DlgToolsNewSource.h -o mDlgToolsNewSource.cpp

mDlgToolsRunAutoTests.cpp: @srcdir@/DlgToolsRunAutoTests.h
	@MOC@ @srcdir@/DlgToolsRunAutoTests.h -o mDlgToolsRunAutoTests.cpp

CLEANFILES = \
	mattr.cpp \
	mcatalog.cpp \
	mconn.cpp \
	mdesc.cpp \
	mdiag.cpp \
	mDlgDbcConnect.cpp \
	mDlgEnvAllocEnv.cpp \
	mDlgEnvAllocHandle.cpp \
	mDlgEnvDataSources.cpp \
	mDlgEnvDrivers.cpp \
	mDlgEnvEndTran.cpp \
	mDlgEnvFreeEnv.cpp \
	mDlgEnvFreeHandle.cpp \
	mDlgEnvTransact.cpp \
	mDlgToolsManageAutoTest.cpp \
	mDlgToolsManageTest.cpp \
	mDlgToolsManageTestGroup.cpp \
	mDlgToolsNewGroup.cpp \
	mDlgToolsNewSource.cpp \
	mDlgToolsRunAutoTests.cpp \
	mOdbcTest.cpp \
	mresults.cpp \
	mstmt.cpp

EXTRA_DIST = \
	attr.h \
	catalog.h \
	conn.h \
	desc.h \
	diag.h \
	DlgDbcConnect.h \
	DlgEnvAllocEnv.h \
	DlgEnvAllocHandle.h \
	DlgEnvDataSources.h \
	DlgEnvDrivers.h \
	DlgEnvEndTran.h \
	DlgEnvFreeEnv.h \
	DlgEnvFreeHandle.h \
	DlgEnvTransact.h \
	DlgToolsManageAutoTest.h \
	DlgToolsManageTest.h \
	DlgToolsManageTestGroup.h \
	DlgToolsNewGroup.h \
	DlgToolsNewSource.h \
	DlgToolsRunAutoTests.h \
	OdbcHandle.h \
	OdbcTest.h \
	results.h \
	stmt.h


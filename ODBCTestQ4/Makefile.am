if GTRTST

bin_PROGRAMS = ODBCTestQ4

INCLUDES = $(QT_CXXFLAGS) \
           $(INCLUDES_COMMON) \
           -DSYSTEM_FILE_PATH=\"@sysconfdir@\" \
	   $(LTDLINCL)

ODBCTestQ4_LDADD = \
	$(QT_LDFLAGS) \
	$(QT_LIBS) \
	-lodbc -lodbcinst

ODBCTestQ4_SOURCES = \
	attr.cpp \
	catalog.cpp \
	conn.cpp \
	desc.cpp \
	diag.cpp \
	DlgDbcConnect.cpp \
	DlgToolsManageAutoTest.cpp \
	DlgToolsManageTest.cpp \
	DlgToolsManageTestGroup.cpp \
	DlgToolsNewGroup.cpp \
	DlgToolsNewSource.cpp \
	DlgToolsRunAutoTests.cpp \
	env.cpp \
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
	menv.cpp \
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

menv.cpp: @srcdir@/env.h
	@MOC@ @srcdir@/env.h -o menv.cpp

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
	mDlgToolsManageAutoTest.cpp \
	mDlgToolsManageTest.cpp \
	mDlgToolsManageTestGroup.cpp \
	mDlgToolsNewGroup.cpp \
	mDlgToolsNewSource.cpp \
	mDlgToolsRunAutoTests.cpp \
	menv.cpp \
	mOdbcTest.cpp \
	mresults.cpp \
	mstmt.cpp

endif

EXTRA_DIST = \
	attr.h \
	catalog.h \
	conn.h \
	desc.h \
	diag.h \
	DlgDbcConnect.h \
	DlgToolsManageAutoTest.h \
	DlgToolsManageTest.h \
	DlgToolsManageTestGroup.h \
	DlgToolsNewGroup.h \
	DlgToolsNewSource.h \
	DlgToolsRunAutoTests.h \
	env.h \
	OdbcHandle.h \
	OdbcTest.h \
	results.h \
	stmt.h


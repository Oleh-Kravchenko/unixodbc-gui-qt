# FUN_CHECK_QT()
# check for qt (headers, libs, progs and compilation)
# substs QT_CXXFLAGS, QT_LDFLAGS, and QT_LIBS

AC_DEFUN([FUN_CHECK_QT],
[
  AC_REQUIRE([AC_PROG_CXX])
  AC_REQUIRE([AC_PATH_X])
  AC_REQUIRE([AC_PATH_XTRA])

  AC_CACHE_SAVE

  AC_MSG_NOTICE([checking for Qt])

  # Variables we want to fill...
  qt_dir=""
  qt_dir_include=""
  qt_dir_lib=""
  qt_dir_bin=""
  qt_libs="-lQtGui -lQtCore -lQtAssistantClient -lQtNetwork"
  MOC=""
  UIC=""

  # Create configure option...
  AC_ARG_WITH([qt_dir], AC_HELP_STRING([--with-qt-dir=DIR],
                        [where the Qt package is installed ie /usr/lib/qt4]),
    [ qt_dir="$withval"
    ])

  # If configure option not used - try to be smart.
  if test "x$qt_dir" = x; then
    if test -d "$QTDIR"; then
      qt_dir=$QTDIR
    elif test -d "/usr/lib64/qt4"; then
      qt_dir="/usr/lib64/qt4"
    elif test -d "/usr/lib/qt4"; then 
      qt_dir="/usr/lib/qt4"
    fi
  fi

  # Still not found - we fail.
  if test "x$qt_dir" = x; then
    AC_MSG_RESULT([no ($qt_dir try specifying with --with-qt-dir or try a different value)])
    AC_MSG_ERROR([cannot find Qt!])
  fi

  AC_MSG_RESULT([yes ($qt_dir)])
  qt_dir_include="$qt_dir"/include
  qt_dir_lib="$qt_dir"/lib
  qt_dir_bin="$qt_dir"/bin

  AC_CHECK_FILE([$qt_dir_include/QtGui/QWizard], [have_qtwizard=yes], [have_qtwizard=no])
  AC_CHECK_FILE([$qt_dir_include/QtGui/QMdiArea], [have_qtmdiarea=yes], [have_qtmdiarea=no])

  MOC="$qt_dir_bin"/moc
  UIC="$qt_dir_bin"/uic

  FUN_QT_COMPILE

  AC_SUBST(MOC)
  AC_SUBST(UIC)
  QT_CXXFLAGS="-I$qt_dir_include -I$qt_dir_include/QtCore -I$qt_dir_include/QtGui -I$qt_dir_include/QtAssistant -I$qt_dir_include/QtNetwork"
  AC_SUBST(QT_CXXFLAGS)
  QT_LDFLAGS="-L$qt_dir_lib"
  AC_SUBST(QT_LDFLAGS)
  QT_LIBS="$qt_libs"
  AC_SUBST(QT_LIBS)

  have_qt="yes"

])#FUN_CHECK_QT

# FUN_QT_COMPILE
# helper function for FUN_CHECK_QT
# compile a simple qt program

AC_DEFUN([FUN_QT_COMPILE],
[

  AC_LANG_PUSH(C++)

  AC_MSG_NOTICE([qt_dir_lib=$qt_dir_lib])
  AC_MSG_NOTICE([LDFLAGS=$LDFLAGS])
  AC_MSG_NOTICE([X_LIBS=$X_LIBS])

  AC_MSG_CHECKING([whether a simple Qt program compiles])

  ac_cxxflags_save="$CXXFLAGS"
  ac_ldflags_save="$LDFLAGS"
  ac_libs_save="$LIBS"
  CXXFLAGS="$CXXFLAGS $PTHREAD_CFLAGS -I$qt_dir_include -I$qt_dir_include/QtCore -I$qt_dir_include/QtGui $X_CFLAGS $all_includes"
  LDFLAGS="$LDFLAGS -L$qt_dir_lib $X_LIBS $X_LDFLAGS"
  LIBS="$LIBS $PTHREAD_LIBS $qt_libs $X_EXTRA_LIBS -lXext -lX11 $X_PRE_LIBS $EXTRA_XLIBS"

  AC_TRY_LINK([
    #include <QMessageBox>
    #include <QString>],
    [QString s = "hello world";
    QMessageBox::information(0, s, "no he is not");
    return 0;],
  qt_compile=yes, qt_compile=no)

  CXXFLAGS="$ac_cxxflags_save"
  LDFLAGS="$ac_ldflags_save"
  LIBS="$ac_libs_save"

  AC_LANG_POP(C++)

  if test "x$qt_compile" = "xyes" ; then
    AC_MSG_RESULT([yes])
  else
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([cannot compile a Qt program!])
  fi
])#FUN_QT_COMPILE

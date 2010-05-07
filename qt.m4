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

  #
  # Create configure option for include location...
  #
  AC_ARG_WITH([qt_dir_include], AC_HELP_STRING([--with-qt-include=DIR],
                        [location of Qt include files]),
    [ qt_dir_include="$withval"
    ])

  #
  # Create configure option for lib location...
  #
  AC_ARG_WITH([qt_dir_lib], AC_HELP_STRING([--with-qt-lib=DIR],
                        [location of Qt lib files]),
    [ qt_dir_lib="$withval"
    ])

  #
  # Create configure option for bin location...
  #
  AC_ARG_WITH([qt_dir_bin], AC_HELP_STRING([--with-qt-bin=DIR],
                        [location of Qt bin files]),
    [ qt_dir_bin="$withval"
    ])

  #
  # No include location given? Lets check a few known places.
  #
  if test "x$qt_dir_include" = x; then
    if test -d "/usr/include/QtCore"; then
      qt_dir_include="/usr/include"
    fi
  fi

  #
  # No lib location given? Lets check a few known places.
  #
  if test "x$qt_dir_lib" = x; then
    if test -e "/usr/lib64/libQtCore.so"; then
      qt_dir_lib="/usr/lib64"
    elif test -e "/usr/lib/libQtCore.so"; then 
      qt_dir_lib="/usr/lib"
    fi
  fi

  #
  # No bin location given? Lets check a few known places.
  #
  if test "x$qt_dir_bin" = x; then
    if test -e "/usr/bin/moc"; then
      qt_dir_bin="/usr/bin"
    fi
  fi

  #
  # Still not found - we fail.
  #
  if test "x$qt_dir_include" = x; then
    AC_MSG_RESULT([no (include try specifying with --with-qt-include or try a different value)])
    AC_MSG_ERROR([cannot find Qt!])
  fi

  #
  # Still not found - we fail.
  #
  if test "x$qt_dir_lib" = x; then
    AC_MSG_RESULT([no (lib try specifying with --with-qt-lib or try a different value)])
    AC_MSG_ERROR([cannot find Qt!])
  fi

  #
  # Still not found - we fail.
  #
  if test "x$qt_dir_bin" = x; then
    AC_MSG_RESULT([no (bin try specifying with --with-qt-bin or try a different value)])
    AC_MSG_ERROR([cannot find Qt!])
  fi

  AC_MSG_RESULT([yes ($qt_dir_include)])
  AC_MSG_RESULT([yes ($qt_dir_lib)])
  AC_MSG_RESULT([yes ($qt_dir_bin)])

  # qt_dir_include="$qt_dir"/include
  # qt_dir_lib="$qt_dir"/lib
  # qt_dir_bin="$qt_dir"/bin

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

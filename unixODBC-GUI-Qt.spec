%define name     unixODBC-GUI-Qt
%define ver      2.2.15
%define rel      1
%define prefix   /usr

Summary: Several GUI (Qt) programs and plugins for unixODBC.
Name: %{name}
Version: %ver
Release: %rel
License: LGPL and GPL
Group: Applications/Databases
Source: %{name}-%{ver}.tar.gz
BuildRoot: /var/tmp/%{name}-%{ver}-root
URL: http://sourceforge.net/projects/unixodbc-gui-qt/
Vendor: unixODBC-GUI-Qt Project
Packager: Peter Harvey
Docdir: %{prefix}/doc
Prefix: %prefix

%description
unixODBC-GUI-Qt provides several GUI (Qt) programs and plugins.
All programs are GPL.
All libs are LGPL.

%prep
%setup

export -n LANG LINGUAS LC_ALL 
if [ ! -f configure ]; then
  CFLAGS="$RPM_OPT_FLAGS" ./autogen.sh $ARCH_FLAGS --prefix=%{prefix}
else
  CFLAGS="$RPM_OPT_FLAGS" ./configure $ARCH_FLAGS --prefix=%{prefix}
fi

%build
export -n LANG LINGUAS LC_ALL 

if [ "$SMP" != "" ]; then
  (make "MAKE=make -k -j $SMP"; exit 0)
  make
else
  make
fi

%install
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install-strip

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT

%pre

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)

%doc AUTHORS COPYING ChangeLog NEWS README README.dist README.qmake README.svn doc

%{prefix}/bin/ODBCCreateDataSourceQ4
%{prefix}/bin/ODBCManageDataSourcesQ4
%{prefix}/bin/ODBCTestQ4
%{_libdir}/libgtrtstQ4.so*
%{_libdir}/libodbcinstQ4.so*



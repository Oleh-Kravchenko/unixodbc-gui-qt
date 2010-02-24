%define name     unixODBC-GUI-Qt
%define ver      2.3.0
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

  * administrator (program)
  * create data source wizard (program) 
  * test (program)
  * installer (plugin)
  * auto test (plugin)

All programs are GPL.
All libs are LGPL.

%prep
%setup -q

%build
make -f Makefile.svn
cd doc/External/
qcollectiongenerator CollectionQ4.qhcp -o CollectionQ4.qhc
cd ../../
./configure CXXFLAGS=-O3 --prefix=$RPM_BUILD_ROOT/usr --libdir=$RPM_BUILD_ROOT%{_libdir}
make

%install
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT
make install

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT

%pre

%post
cd %{_docdir}/unixODBC-GUI-Qt/doc/External/
assistant -collectionFile CollectionQ4.qhc -register Project.qch
/sbin/ldconfig

%preun
cd %{_docdir}/unixODBC-GUI-Qt/doc/External/
assistant -collectionFile CollectionQ4.qhc -unregister Project.qch

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)

%doc AUTHORS COPYING ChangeLog NEWS doc

%{prefix}/bin/ODBCCreateDataSourceQ4
%{prefix}/bin/ODBCManageDataSourcesQ4
%{prefix}/bin/ODBCTestQ4
%{_libdir}/libgtrtstQ4.so*
%{_libdir}/libgtrtstQ4.a
%{_libdir}/libgtrtstQ4.la
%{_libdir}/libodbcinstQ4.so*
%{_libdir}/libodbcinstQ4.a
%{_libdir}/libodbcinstQ4.la



bin_PROGRAMS=
BUILT_SOURCES=
CLEANFILES=

AM_CPPFLAGS = $(MODULES_CFLAGS) -I/usr/include/boost141
LDADD = $(MODULES_LIBS)

%.pb.h %.pb.cc: %.proto
	protoc -I. --cpp_out=. $<

BUILT_SOURCES += s3fx.pb.h s3fx.pb.cc

# --- main ---

bin_PROGRAMS += main

main_SOURCES = main.cpp
main_SOURCES += s3fx.pb.cc

main_LDADD = -levent $(LDADD)

CLEANFILES += $(BUILT_SOURCES)

rpm: all
	rpmbuild --buildroot `pwd`/buildroot --define="_topdir ." --define="_builddir ." -bb s3fx.spec

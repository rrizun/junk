AC_INIT(s3fx, 0.9.0)
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror -Wno-portability])

AC_PROG_CXX

AC_CONFIG_FILES([Makefile])

AC_CHECK_LIB([dl], [main])
AC_CHECK_LIB([rt], [main])
AC_CHECK_LIB([pthread], [main])

PKG_CHECK_MODULES([MODULES], [libcurl libidn openssl protobuf libxml-2.0])

AC_OUTPUT

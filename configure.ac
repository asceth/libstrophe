AC_INIT([libstrophe], [trunk], [jack@metajack.im])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AC_PROG_LIBTOOL

AC_PROG_CC

PKG_CHECK_MODULES([openssl],[libssl], [], [AC_MSG_ERROR([couldn't find openssl headers, openssl required])])

# check for 'check' unit-testing framework
PKG_CHECK_MODULES([check], [check >= 0.9.4], [HAVE_CHECK=yes], [
HAVE_CHECK=no
echo "Regression tests will not be built"
])
AM_CONDITIONAL([HAVE_CHECK], [test x$HAVE_CHECK = xyes])

LIBXML2_REQUIRE=
AC_ARG_WITH([libxml2],
            [AS_HELP_STRING([--with-libxml2], [use libxml2 for XML parsing])],
            [with_libxml2=check],
            [with_libxml2=no])

if test "x$with_libxml2" != xno; then
  PKG_CHECK_MODULES([libxml2], [libxml-2.0 >= 2.7],
                    [with_libxml2=yes; LIBXML2_REQUIRE="libxml-2.0"],
                    [AC_MSG_ERROR([couldn't find libxml2])])
else
  AC_CHECK_FUNCS(memmove)
  AC_C_BIGENDIAN([byteorder=1234], [byteorder=4321], [], [])
fi
AC_SUBST(LIBXML2_REQUIRE)

AC_CHECK_FUNCS(snprintf)
AC_CHECK_FUNCS(vsnprintf)

if test "x$with_libxml2" = xyes; then
  with_parser=libxml2
  PARSER_NAME=libxml2
  PARSER_CFLAGS=\$\(libxml2_CFLAGS\)
  PARSER_LIBS=\$\(libxml2_LIBS\)
else
  with_parser=builtin
  PARSER_NAME=expat
  PARSER_CFLAGS=\$\(builtin_CFLAGS\)
  PARSER_LIBS=\$\(builtin_LIBS\)
fi

AC_MSG_NOTICE([libstrophe will use the $with_parser XML parser])
AC_SEARCH_LIBS([socket], [socket])
AC_CHECK_LIB([resolv], [main])

AM_CONDITIONAL([BUILD_EXPAT], [test x$with_parser = xbuiltin])
AM_CONDITIONAL([PARSER_EXPAT], [test x$with_parser != xlibxml2])
AC_DEFINE_UNQUOTED([BYTEORDER], [$byteorder])
AC_SUBST(PARSER_NAME)
AC_SUBST(PARSER_CFLAGS)
AC_SUBST(PARSER_LIBS)
AC_CONFIG_FILES([Makefile libstrophe.pc])
AC_OUTPUT

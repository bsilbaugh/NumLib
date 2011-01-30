# Process this script with autoconf to generate the configure script

dnl Standard initialization stuff
AC_INIT([NumLib],[0.0],[silbaugh@umd.edu])
AM_INIT_AUTOMAKE

dnl Fix installation directory to be source code directory
AC_PREFIX_DEFAULT('$(top_srcdir)')

dnl Allow for non-standard install location of Boost libraries
AC_ARG_WITH(boost,
		    AC_HELP_STRING([--with-boost=PATH],
						   [Specify install location of Boost libraries]))

AC_ARG_ENABLE(debug,
			  AC_HELP_STRING([--enable-debug],
							 [Enables all debugging assertions (default: no)]),,enable_debug=no)
AC_ARG_ENABLE(debug_print,
			  AC_HELP_STRING([--enable-debug-print],
							 [Enables all debug assertions and print statements (default: no)]),,enable_debug_print=no)

AC_ARG_ENABLE(debug_log,
			  AC_HELP_STRING([--enable-debug-log],
							 [Enables all debug assertions, print statements, and log streams (default: no)]),,enable_debug_log=no)


if test "$ac_cv_env_CXXFLAGS_set" != set ; then
	CXXFLAGS=" -g -ansi -O3 -fPIC -fno-common -Werror -Wall -W"
	CXXFLAGS="$CXXFLAGS -Wconversion -Wshadow -Wcast-qual -Wcast-align"
fi

dnl Check if debuggin is to be enabled
if test "$enable_debug" = yes; then
	AC_DEFINE(DEBUG,1)
fi

if test "$enable_debug_print" = yes; then
	AC_DEFINE(DEBUG,2)
fi

if test "$enable_debug_log" = yes; then
	AC_DEFINE(DEBUG,3)
fi

dnl Check for Boost Libraries, if not given assume installed 
dnl under /usr/local
if test "x$with_boost" != "x" ; then
	CPPFLAGS="$CPPFLAGS -I$with_boost/include"
	LDFLAGS="$LDFLAGS -L$with_boost/lib"
	boost_incdir="$with_boost/include"
	boost_libdir="$with_boost/lib"
else
	CPPFLAGS="$CPPFLAGS -I$/usr/local/include"
	LDFLAGS="$LDFLAGS -L$/usr/local/lib"
	boost_incdir="$/usr/local/include"
	boost_libdir="$/usr/local/lib"
fi

dnl Setup standard programs
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CC
AC_PROG_CXX

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 src/base/Makefile
				 src/linalg/Makefile
				 src/solvers/Makefile
				 src/array/Makefile
				 src/tensor/Makefile
				 src/integration/Makefile
				 src/reconstruction/Makefile
				 src/optimization/Makefile
				 ])
AC_OUTPUT

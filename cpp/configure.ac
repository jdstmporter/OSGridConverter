#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([geoconv], [0.1], [julian@porternet.org.uk])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AC_PROG_CXX
AC_PROG_RANLIB
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	test/Makefile
])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_14
AX_CXX_BOOL



AC_OUTPUT

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([CVM-S], [4])
AC_CONFIG_SRCDIR([src])
AM_INIT_AUTOMAKE([foreign no-exeext])
AC_PROG_RANLIB

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h unistd.h])

# On OS X?
AC_CHECK_HEADERS([alloc.h])

if [[ -z "HAVE_ALLOC_H" ]]
then
	CFLAGS="-Wall -O3 -static"
	FCFLAGS="-Wall -O3 -static -ffixed-line-length-132"
else
	CFLAGS="-Wall -O3"	
	FCFLAGS="-Wall -O3 -ffixed-line-length-132"	
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_FC

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getcwd gethostname gettimeofday memset])

AC_CONFIG_FILES([Makefile data/Makefile src/Makefile test/Makefile])
AC_OUTPUT

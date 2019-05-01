#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([PreVent], [4.2], [ry@os-em.com])
AC_CONFIG_SRCDIR([libtdms/TdmsObject.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_PROG_AR
AC_PROG_LIBTOOL

AM_INIT_AUTOMAKE([-Wall])
LT_INIT([disable-static])

# Checks for programs.
AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CC

m4_include([m4/ax_cxx_compile_stdcxx.m4])
m4_include([m4/libuv-check-flags.m4])
dnl AX_CXX_COMPILE_STDCXX(17, [noext], [mandatory])
CC_CHECK_CXXFLAGS_APPEND([-std=c++17])
CC_CHECK_CXXFLAGS_APPEND([-Wall])
CC_CHECK_CXXFLAGS_APPEND([-Wextra])

# check for WFDB library
AC_CHECK_PROG([WFDB_CHECK],[wfdb-config], [yes])
AS_IF([test x"$WFDB_CHECK" != x"yes"], [AC_MSG_ERROR([Please install wfdb before configuring])])
AC_SUBST([WFDB_LIBS], `wfdb-config --libs`)
AC_SUBST([WFDB_CFLAGS], `wfdb-config --cflags`)

AC_CHECK_PROG([GIT_CHECK], [git], [yes])
AS_IF([test x"$GIT_CHECK" != x"yes"], [AC_MSG_ERROR([Please install git client before configuring])])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h fenv.h float.h inttypes.h limits.h locale.h stddef.h stdint.h stdlib.h string.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_STRUCT_TIMEZONE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MKTIME
AC_FUNC_STRTOD
AC_CHECK_FUNCS([floor getcwd localeconv memmove memset modf pow strtoull])


AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

PKG_CHECK_MODULES([zlib],[zlib])
PKG_CHECK_MODULES([matio], [matio])
PKG_CHECK_MODULES([expat], [expat])

AC_CONFIG_FILES([Makefile
                 libtdms/Makefile
                 Formats/Makefile
                 FormatConverter/Makefile
                 PreVentTools/Makefile])
AC_OUTPUT

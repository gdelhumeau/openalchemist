% Prelude
AC_INIT([openalchemist], [0.3], [contact@openalchemist.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/Application.cpp])

% Check for programs
AC_PROG_CXX

% Check for header files
% AC_CHECK_HEADER([iostream string vector list])

% Check for libraries
REQUIRED_CLANLIB_VERSION="0.8.0"
PKG_CHECK_MODULES(clanlib,
[
	clanCore-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanApp-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanDisplay-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanGL-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanSDL-0.8 >= $REQUIRED_CLANLIB_VERSION
], [], [echo "This program needs ClanLib >= 0.8 (clanCore, clanApp, clanDisplay, clanGL, clanSDL)"; exit])

% Outputfiles
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile build/Makefile])
AC_OUTPUT


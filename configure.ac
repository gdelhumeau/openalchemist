% Prelude
AC_INIT([openalchemist], [0.4], [contact@openalchemist.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/main.cpp])

% Check for programs
AC_PROG_CXX

% Check for header files
% AC_CHECK_HEADER([iostream string vector list])

% Check for libraries
REQUIRED_CLANLIB_VERSION="2.1.0"
PKG_CHECK_MODULES(clanlib,
[
	clanCore-2.1 >= $REQUIRED_CLANLIB_VERSION
	clanApp-2.1 >= $REQUIRED_CLANLIB_VERSION
	clanDisplay-2.1 >= $REQUIRED_CLANLIB_VERSION
	clanGL-2.1 >= $REQUIRED_CLANLIB_VERSION
	clanSound-2.1 >= $REQUIRED_CLANLIB_VERSION
  clanVorbis-2.1 >= $REQUIRED_CLANLIB_VERSION
], [], [echo "This program needs ClanLib >= 2.0 (clanCore, clanApp, clanDisplay, clanGL, clanSound, clanVorbis)"; exit])

% Outputfiles
% AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile build/Makefile])
AC_OUTPUT


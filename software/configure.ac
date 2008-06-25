AC_INIT([openalchemist], [0.3], [openalchemist@gmail.com])
AM_INIT_AUTOMAKE([-Wall])
AC_PROG_CXX

REQUIRED_CLANLIB_VERSION="0.8.0"
PKG_CHECK_MODULES(clanlib,
[
	clanCore-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanApp-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanDisplay-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanGL-0.8 >= $REQUIRED_CLANLIB_VERSION
	clanSDL-0.8 >= $REQUIRED_CLANLIB_VERSION
], [], [echo "This program needs ClanLib >= 0.8 (clanCore, clanApp, clanDisplay, clanGL, clanSDL)"; exit])

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

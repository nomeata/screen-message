AC_INIT(screen-message, 0.18, mail@joachim-breitner.de)
AC_CONFIG_SRCDIR([sm.c])
AM_INIT_AUTOMAKE([foreign])

PKG_PROG_PKG_CONFIG
AC_ARG_WITH([win32-gtk],
            [AS_HELP_STRING([--with-win32-gtk=PATH],
              [path to the gtk+ source bundle for win32 cross builds])],
            [],
            [with_win32_gtk=no])

AS_IF([test "x$with_win32_gtk" != xno],
            [AS_VAR_APPEND(PKG_CONFIG," --define-variable prefix=$with_win32_gtk")
	     export PKG_CONFIG_PATH="$with_win32_gtk/lib/pkgconfig:$PKG_CONFIG_PATH"
	    ],
	    [
	    AS_CASE($host,[*mingw32msvc*],[
	    	AC_MSG_ERROR("You need to specify --with-win32-gtk when building for Win32")
	   	])
	    ])

AC_CONFIG_HEADERS(config.h)

AC_PROG_CC
AC_PROG_INSTALL
AC_STDC_HEADERS

PKG_CHECK_MODULES(DEPS, gtk+-2.0 >= 2.10 gdk-2.0 >= 2.10 pango >= 1.16)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

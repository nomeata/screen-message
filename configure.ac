AC_INIT(screen-message, 0.26, mail@joachim-breitner.de)
AC_CONFIG_SRCDIR([sm.c])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_FILES([setup.iss README.Win32])

AS_CASE($host,
	[*mingw32msvc*],[win32=true],
	[win32=false])

AM_CONDITIONAL(WIN32, test "x$win32" = xtrue)
AS_IF([test "x$win32" = xtrue],[
        AC_CHECK_TOOL(WINE,[wine],[],[])
        AC_CHECK_TOOL(WINEPATH,[winepath],[],[])
        AC_CHECK_TOOL(WINDRES,[windres],[],[])
	])

AC_ARG_WITH([iscc],
            [AS_HELP_STRING([--with-issc=PATH],
              [path to the Inno Setup compiler for win32 cross builds])],
            [ ],
            [with_iscc=no])

AS_IF([test "x$with_iscc" = xyes],[
	AC_MSG_ERROR("You need to pass a parameter to --with-iscc")
	])

AS_IF([test "x$with_iscc" != xno],
	    [
	    AC_SUBST(ISCC,[$with_iscc])
	    ],
	    [
	    AS_IF([test "x$win32" = xtrue],
	    	[AC_MSG_ERROR("You need to specify --with-iscc when building for Win32")]
	   	)
	    ])


PKG_PROG_PKG_CONFIG
AC_ARG_WITH([win32-gtk],
            [AS_HELP_STRING([--with-win32-gtk=PATH],
              [path to the gtk+ source bundle for win32 cross builds])],
            [],
            [with_win32_gtk=no])

AS_IF([test "x$with_win32_gtk" = xyes],[
	AC_MSG_ERROR("You need to pass a parameter to --with-win32_-gtk")
	])

AS_IF([test "x$with_win32_gtk" != xno],
	    [AC_SUBST(WIN32_GTK, [`$WINEPATH -w $with_win32_gtk`])
	     AS_VAR_APPEND(PKG_CONFIG," --define-variable prefix=$with_win32_gtk")
	     export PKG_CONFIG_PATH="$with_win32_gtk/lib/pkgconfig:$PKG_CONFIG_PATH"
	    ],
	    [
	    AS_IF([test "x$win32" = xtrue],
	    	[AC_MSG_ERROR("You need to specify --with-win32-gtk when building for Win32")]
	   	)
	    ])


AC_CONFIG_HEADERS(config.h)

AC_PROG_CC
AC_PROG_INSTALL
AC_STDC_HEADERS

PKG_CHECK_MODULES(DEPS, gtk+-3.0 gdk-3.0 pango >= 1.16)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

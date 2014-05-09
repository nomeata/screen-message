
sm_SOURCES = sm.c
sm_CFLAGS = $(DEPS_CFLAGS)
sm_LDADD = $(DEPS_LIBS)

execgamesdir= $(prefix)/games
execgames_PROGRAMS=sm

sm.desktop: sm.desktop.in
	sed -e s%@BINPATH@%${execgamesdir}% <$< >$@

desktopdir = $(datadir)/applications
desktop_DATA = sm.desktop

icondir = $(datadir)/icons/hicolor/48x48/apps
dist_icon_DATA = sm.png

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache
update-icon-cache:
	@-if test -z "$(DESTDIR)"; then \
	        echo "Updating Gtk icon cache."; \
	        $(gtk_update_icon_cache); \
	else \
	        echo "*** Icon cache not updated.  After (un)install, run this:"; \
	        echo "***   $(gtk_update_icon_cache)"; \
	fi

dist_man_MANS = sm.6
# some of these files are just added to make the Debian packaging based on the
# same VCS painless... (otherwise dpkg would try to add these files as patches)
EXTRA_DIST = sm.py sm.desktop.in sm.html sm.webapp webapp.html README.Win32 sm.ico sm.rc sm-128.png sm.svg gtkzoom.h gtkzoom.c sm-fsmi-ka.jpg
CLEANFILES = sm.desktop 

if WIN32
AM_LDFLAGS = -Wl,--subsystem,windows
sm_LDADD += sm-icon.o

INSTALLER_BASE = screen-message-setup-@PACKAGE_VERSION@
INSTALLER = $(INSTALLER_BASE).exe
CLEANFILES +=  setup.iss $(INSTALLER)

sm-icon.o: sm.rc
	$(WINDRES) $< $@

$(INSTALLER): setup.iss sm.exe README.Win32
	"$(WINE)" "$(ISCC)" /O. "/F$(INSTALLER_BASE)" $< 

installer: $(INSTALLER)

endif


bin_PROGRAMS = sm
sm_SOURCES = sm.c
sm_CFLAGS = $(DEPS_CFLAGS)
sm_LDADD = $(DEPS_LIBS)

icondir = $(datadir)/icons/hicolor/48x48/apps
icon_DATA = sm.png

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


man_MANS = sm.1
EXTRA_DIST = sm.1 sm.py sm.png

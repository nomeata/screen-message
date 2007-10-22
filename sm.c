/*
#     vlshow.c
#     Copyright (C) 2006 Joachim Breitner
#
#     This program is free software; you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation; either version 2 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <pango/pango.h>
#include <string.h>
#include <stdio.h>

static int min(int x, int y) {
	return x < y ? x : y;
}


static gboolean quality = TRUE;
static gboolean need_resize = TRUE;
static gboolean need_quick = TRUE;

static GtkWidget* window;
static GtkWidget* draw;
static GdkCursor *cursor;
static GtkWidget* quit;
static GtkWidget* tv;
static GtkSettings* settings;
static GtkTextBuffer* tb;
static PangoFontDescription *font;
static PangoLayout* layout;

static void realize(GtkWindow *window, GdkScreen *screen, gpointer data) {
	gdk_window_set_cursor(draw->window, cursor);
}

static void clear_text(GtkAccelGroup *accel, GObject *window, guint keyval,  GdkModifierType modifier) {
	if( gtk_text_buffer_get_char_count(tb) )
		gtk_text_buffer_set_text(tb,"",-1);
	else
		gtk_main_quit();
}

static char *get_text() {
	GtkTextIter start, end;
	gtk_text_buffer_get_start_iter(tb,&start);
	gtk_text_buffer_get_end_iter(tb,&end);
	return gtk_text_buffer_get_text(tb, &start, &end, FALSE);
}


static void hq(gboolean q, gboolean force){
	if (q != quality) 
		if (q)
			gtk_settings_set_long_property(settings,"gtk-xft-antialias",1,"Hier halt");
		else
			gtk_settings_set_long_property(settings,"gtk-xft-antialias",0,"Hier halt");
	else
		if (force)
			gtk_widget_queue_draw(draw);

	quality = q;
}

static void redraw() {
	const char *text = pango_layout_get_text(layout);
	if (strlen(text) > 0) {
		GdkGC *gc = gtk_widget_get_style(draw)->fg_gc[GTK_STATE_NORMAL];
		int w1, h1;
		pango_layout_get_pixel_size(layout, &w1, &h1);
		if (w1>0 && h1>0) {
			int w2 = draw->allocation.width;
			int h2 = draw->allocation.height;
			gdk_draw_layout(draw->window, gc, (w2-w1)/2,(h2-h1)/2,layout);
			hq(TRUE, FALSE);
		}
	}
}

static gboolean text_clicked(GtkWidget *widget, GdkEventButton *event, gpointer *user_data) {
	if (event->type == GDK_BUTTON_PRESS && event->button == 2) {
		GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

		gchar *txt = gtk_clipboard_wait_for_text(cb);
		if (txt != NULL) {
			gtk_text_buffer_set_text(tb,txt,-1);
			g_free(txt);
		}

	}
	return FALSE;
}

static void resize() {
	int w1, h1, w2, h2;
	pango_layout_get_pixel_size(layout, &w1, &h1);
	if (w1>0 && h1>0) {
		w2 = draw->allocation.width;
		h2 = draw->allocation.height;
		int s = pango_font_description_get_size(font);
		s = min ((s*w2/w1), (s*h2/h1));
		pango_font_description_set_size(font,s);
		pango_layout_set_font_description(layout, font);
		need_resize = FALSE;
	}
	else
		need_resize = TRUE;
}


static void newtext(char *text) {
	pango_layout_set_text(layout, get_text(), -1);
	resize();
	hq(FALSE, TRUE);
}

int main(int argc, char **argv) {
	GString *input;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	GdkScreen *screen = gtk_window_get_screen(GTK_WINDOW(window));
	gtk_widget_set_size_request(window, gdk_screen_get_width(screen),
					    gdk_screen_get_height(screen));
	gtk_window_fullscreen(GTK_WINDOW(window));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	settings = gtk_settings_get_default();
	GdkColormap *colormap = gtk_widget_get_colormap(GTK_WIDGET(window));
	GdkColor white, black;
	gdk_colormap_alloc_color(colormap, &white, TRUE, TRUE);
	gdk_color_parse("white", &white);
	gdk_color_parse("black", &black);
	gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &white);
	gtk_widget_modify_fg(window, GTK_STATE_NORMAL, &black);

	draw = gtk_drawing_area_new();
	gtk_widget_set_events(draw, GDK_BUTTON_PRESS_MASK);
	gtk_widget_set_size_request(draw,400,400);
	gtk_widget_modify_bg(draw, GTK_STATE_NORMAL, &white);
	gtk_widget_modify_fg(draw, GTK_STATE_NORMAL, &black);
	g_signal_connect(G_OBJECT(draw), "realize", G_CALLBACK(realize), NULL);
	g_signal_connect(G_OBJECT(draw), "button-press-event", G_CALLBACK(text_clicked), NULL);

	GdkPixmap *pixmap = gdk_pixmap_new(NULL, 1, 1, 1);
	GdkColor color;
	cursor = gdk_cursor_new_from_pixmap(pixmap, pixmap, &color, &color, 0, 0);

	tv = gtk_text_view_new();
	gtk_widget_modify_bg(tv, GTK_STATE_NORMAL, &white);
	gtk_widget_modify_fg(tv, GTK_STATE_NORMAL, &black);
	tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));

	if (argc > 1)
		if (!strcmp(argv[1], "-") ) {
			// read from stdin
			gchar buf[1024];
			int num;

			input = g_string_new("");

			while ((num = fread (buf, 1, sizeof(buf), stdin)) > 0) {
				g_string_append_len(input, buf, num);
			}
		} else {
			int i;

			input = g_string_new("");

			for (i = 1; i < argc; i++) {
				g_string_append(input, argv[i]);

				if (i < argc - 1) {
					g_string_append(input, " ");
				}
			}
		}
	else
		input = g_string_new(":-)");

	gtk_text_buffer_set_text(tb, input->str, input->len);

	quit = gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_modify_bg(quit, GTK_STATE_NORMAL, &white);
	gtk_widget_modify_fg(quit, GTK_STATE_NORMAL, &black);

	GtkWidget *hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox), tv,   TRUE,  TRUE,  0);
	gtk_box_pack_start(GTK_BOX(hbox), quit, FALSE, FALSE, 0);

	GtkWidget *vbox = gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox), draw, TRUE,  TRUE,  0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(window), vbox);

	font = pango_font_description_new();
        pango_font_description_set_family(font, "sans-serif");
	pango_font_description_set_size(font, 20*PANGO_SCALE);

	layout=  gtk_widget_create_pango_layout(draw,get_text());
	pango_layout_set_font_description(layout, font);
	pango_layout_set_alignment(layout,PANGO_ALIGN_CENTER);

	GtkAccelGroup *accel = gtk_accel_group_new();
	guint key;
	GdkModifierType mod;
	gtk_accelerator_parse("<Ctrl>Q", &key, &mod);
	gtk_accel_group_connect(accel, key, mod, 0, g_cclosure_new(G_CALLBACK(gtk_main_quit), NULL, NULL));
	gtk_accelerator_parse("Escape", &key, &mod);
	gtk_accel_group_connect(accel, key, mod, 0, g_cclosure_new(G_CALLBACK(clear_text), NULL, NULL));
	gtk_window_add_accel_group(GTK_WINDOW(window), accel);
	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(draw), "configure-event", G_CALLBACK(resize), NULL);
	g_signal_connect(G_OBJECT(draw), "expose-event", G_CALLBACK(redraw), NULL);
	g_signal_connect(G_OBJECT(tb), "changed", G_CALLBACK(newtext), NULL);

	resize();

	gtk_main();
}

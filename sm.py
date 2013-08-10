#!/usr/bin/python
# encoding:utf8

#
# This is the original version of screen message (then call vlshow); kept here
# for historical reasons. sm.c is the real thing.
#

#     vlshow.py
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


import pygtk
pygtk.require('2.0')
import gtk
import pango
import sys
import gobject

window = gtk.Window(gtk.WINDOW_TOPLEVEL)
window.set_decorated(False)
window.modify_bg(gtk.STATE_NORMAL, gtk.gdk.color_parse("white"))
window.fullscreen()

settings = gtk.settings_get_default()

draw = gtk.DrawingArea()
draw.modify_bg(gtk.STATE_NORMAL, gtk.gdk.color_parse("white"))
draw.set_size_request(400,300)

pixmap = gtk.gdk.Pixmap(None, 1, 1, 1)
color = gtk.gdk.Color()
cursor = gtk.gdk.Cursor(pixmap, pixmap, color, color, 0, 0)


tv = gtk.TextView()
tb = tv.get_buffer()

def get_text():
	return tb.get_text(tb.get_start_iter(), tb.get_end_iter())

if len(sys.argv) > 1:
	tb.set_text(" ".join(sys.argv[1:]))
else:
	tb.set_text(";-)")

quit = gtk.Button(stock=gtk.STOCK_QUIT)
quit.modify_bg(gtk.STATE_NORMAL, gtk.gdk.color_parse("white"))
quit.connect("clicked",gtk.main_quit)

hbox = gtk.HBox()
hbox.pack_start(tv, expand=True, fill=True)
hbox.pack_start(quit,  expand=False,fill=False)

vbox = gtk.VBox()
vbox.pack_start(draw, expand=True, fill=True)
vbox.pack_start(hbox, expand=False, fill=False)
window.add(vbox)

font = pango.FontDescription()
font.set_family("sans-serif")
font.set_size(60*pango.SCALE)
layout = draw.create_pango_layout(get_text())
layout.set_font_description(font)
layout.set_alignment(pango.ALIGN_CENTER)


accel = gtk.AccelGroup()
key, mod = gtk.accelerator_parse("<Ctrl>Q")
accel.connect_group(key, mod, 0, gtk.main_quit)
key, mod = gtk.accelerator_parse("Escape")
#accel.connect_group(key, mod, 0, gtk.main_quit)
#key, mod = gtk.accelerator_parse("<Ctrl>C")
accel.connect_group(key, mod, 0, (lambda x,y,z,v: tb.set_text("")))
window.add_accel_group(accel)

window.connect("destroy", gtk.main_quit)

window.show_all()

need_resize=True
need_quick=True

def resize(w=None,rect=None):
	global need_resize
	draw.window.set_cursor(cursor)
	(w1,h1) = layout.get_pixel_size()
	if h1>0 and w1>0:
		(x,y,w2,h2) = draw.get_allocation()
		s = font.get_size()
		s = min ( int (s*w2/w1), int (s*h2/h1) )
		font.set_size(s)
		layout.set_font_description(font)
		need_resize=False
	else:
		need_resize=True

def redraw(w=None,e=None):
	global need_resize, need_quick
	if layout.get_text(): # Fails for empty lines :-(
		gc = draw.get_style().fg_gc[gtk.STATE_NORMAL]
		(w1,h1) = layout.get_pixel_size()
		if h1>0 and w1>0:
			(x,y,w2,h2) = draw.get_allocation()
			draw.window.draw_layout(gc,(w2-w1)/2,(h2-h1)/2,layout)
			hq(True)

quality = False
def hq(q,force=False):
	global quality
	if q != quality:
		if q:
			settings.set_long_property("gtk-xft-antialias",1,"Hier halt")
		else:
			settings.set_long_property("gtk-xft-antialias",0,"Hier halt")
	else:
		if force:
			draw.queue_draw()

	quality = q
	return False

def newtext(w):
	global timeout_id
	layout.set_text(get_text())
	resize()
	hq(False, True)

draw.connect("configure-event", resize)
draw.connect("expose-event", redraw)
tb.connect("changed", newtext)

gtk.main()

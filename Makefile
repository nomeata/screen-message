CFLAGS=-O3 `pkg-config pango gtk+-2.0 gdk-2.0 --cflags `
LDFLAGS=-lm `pkg-config pango gtk+-2.0 gdk-2.0 --libs `

all: sm

sm: sm.c
	gcc $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f sm


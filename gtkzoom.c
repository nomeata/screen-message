#include "gtkzoom.h"

struct _GtkZoomPrivate
{
	int dummy;
//  GtkWidget *child;
};

static gboolean
gtk_zoom_draw      (GtkWidget      *widget,
                                     cairo_t        *cr);
static void
gtk_zoom_size_allocate (GtkWidget     *widget, GtkAllocation *allocation);
static void
gtk_zoom_get_preferred_width (GtkWidget *widget,
                                 gint      *minimum,
                                 gint      *natural);
static void
gtk_zoom_get_preferred_height (GtkWidget *widget,
                                 gint      *minimum,
                                 gint      *natural);

G_DEFINE_TYPE (GtkZoom, gtk_zoom, GTK_TYPE_BIN)

static void
gtk_zoom_class_init (GtkZoomClass *class)
{
  GtkWidgetClass *widget_class = (GtkWidgetClass*) class;

  widget_class->draw          = gtk_zoom_draw;
  widget_class->size_allocate = gtk_zoom_size_allocate;
  widget_class->get_preferred_width = gtk_zoom_get_preferred_width;
  widget_class->get_preferred_height = gtk_zoom_get_preferred_height;


  g_type_class_add_private (class, sizeof (GtkZoomPrivate));
}

static void
gtk_zoom_init (GtkZoom *zoom)
{
  GtkZoomPrivate *priv;

  zoom->priv = G_TYPE_INSTANCE_GET_PRIVATE (zoom,
                                           GTK_TYPE_ZOOM,
                                           GtkZoomPrivate);
  priv = zoom->priv;
}

GtkWidget*
gtk_zoom_new (void)
{
  return g_object_new (GTK_TYPE_ZOOM, NULL);
}


static void
gtk_zoom_size_allocate (GtkWidget     *widget, GtkAllocation *allocation)
{
  GtkWidget *main_widget;

  GTK_WIDGET_CLASS (gtk_zoom_parent_class)->size_allocate (widget, allocation);

  main_widget = gtk_bin_get_child (GTK_BIN (widget));
  if (!main_widget || !gtk_widget_get_visible (main_widget))
    return;

  gtk_widget_size_allocate (main_widget, allocation);
}

static void
gtk_zoom_get_preferred_width (GtkWidget *widget,
                                 gint      *minimum,
                                 gint      *natural)
{
  GtkBin *bin = GTK_BIN (widget);
  GtkWidget *child;

  if (minimum)
    *minimum = 0;

  if (natural)
    *natural = 0;

  child = gtk_bin_get_child (bin);
  if (child && gtk_widget_get_visible (child))
    gtk_widget_get_preferred_width (child, minimum, natural);
}

static void
gtk_zoom_get_preferred_height (GtkWidget *widget,
                                  gint      *minimum,
                                  gint      *natural)
{
  GtkBin *bin = GTK_BIN (widget);
  GtkWidget *child;

  if (minimum)
    *minimum = 0;

  if (natural)
    *natural = 0;

  child = gtk_bin_get_child (bin);
  if (child && gtk_widget_get_visible (child))
    gtk_widget_get_preferred_height (child, minimum, natural);
}



static gboolean
gtk_zoom_draw (GtkWidget *widget, cairo_t   *cr)
{
	GtkWidget *child;
	child = gtk_bin_get_child (GTK_BIN(widget));
	if (child) {
		cairo_save(cr);
		cairo_scale(cr, 2, 2);
		gtk_widget_draw(child, cr);
		cairo_restore(cr);
	}

	//GTK_WIDGET_CLASS (gtk_zoom_parent_class)->draw (widget, cr);

	return FALSE;
}


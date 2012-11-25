#ifndef __GTK_ZOOM_H__
#define __GTK_ZOOM_H__


#include <gtk/gtk.h>


G_BEGIN_DECLS

#define GTK_TYPE_ZOOM                  (gtk_zoom_get_type ())
#define GTK_ZOOM(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ZOOM, GtkZoom))
#define GTK_ZOOM_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ZOOM, GtkZoomClass))
#define GTK_IS_ZOOM(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ZOOM))
#define GTK_IS_ZOOM_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ZOOM))
#define GTK_ZOOM_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ZOOM, GtkZoomClass))


typedef struct _GtkZoom              GtkZoom;
typedef struct _GtkZoomPrivate       GtkZoomPrivate;
typedef struct _GtkZoomClass         GtkZoomClass;

struct _GtkZoom
{
  GtkBin container;

  /*< private >*/
  GtkZoomPrivate *priv;
};

struct _GtkZoomClass
{
  GtkBinClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};


GType      gtk_zoom_get_type  (void) G_GNUC_CONST;
GtkWidget* gtk_zoom_new       (void);


G_END_DECLS

#endif /* __GTK_ZOOM_H__ */

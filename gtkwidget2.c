/*
	Copyright (C) 2015 Minho Jo <whitestone8214@openmailbox.org>

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the
	Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA 02111-1307, USA.
*/

// gcc -O3 -std=gnu99 $(pkg-config --cflags --libs gtk+-2.0) gtkwidget2.c -shared -o libgtkwidget2.so


#include "gtkwidget2.h"


static void gtk_widget_2_callbacks (GtkWidget2Class *class);
static void gtk_widget_2_contents (GtkWidget2 *widget);
static void gtk_widget_2_size_request (GtkWidget *widget, GtkRequisition *requisition);
static void gtk_widget_2_size_allocate (GtkWidget *widget, GtkAllocation *allocation);
static void gtk_widget_2_show (GtkWidget *widget);
static gboolean gtk_widget_2_refresh (GtkWidget *widget, GdkEventExpose *event);
static void gtk_widget_2_destroy (GtkObject *object);


unsigned long gtk_widget_2_get_id () {
	static unsigned long id = 0; if (id == 0) {
		static const GtkTypeInfo information = {
			"GtkWidget2",
			sizeof (GtkWidget2),
			sizeof (GtkWidget2Class),
			(GtkClassInitFunc) gtk_widget_2_callbacks,
			(GtkObjectInitFunc) gtk_widget_2_contents,
			NULL,
			NULL,
			(GtkClassInitFunc) NULL
		};
		id = gtk_type_unique (gtk_widget_get_type (), &information);
	}
	
	return id;
}

static void gtk_widget_2_callbacks (GtkWidget2Class *class) {
	GtkWidgetClass *class_widget = (GtkWidgetClass *) class;
	class_widget->realize = gtk_widget_2_show;
	class_widget->size_request = gtk_widget_2_size_request;
	class_widget->size_allocate = gtk_widget_2_size_allocate;
	class_widget->expose_event = gtk_widget_2_refresh;
	
	GtkObjectClass *class_object = (GtkObjectClass *) class;
	class_object->destroy = gtk_widget_2_destroy;
}

static void gtk_widget_2_contents (GtkWidget2 *widget) {
	widget->index = 0; widget->label = NULL; widget->data = NULL;
	widget->width = 1; widget->height = 1;
	widget->draw = NULL;
}

static void gtk_widget_2_size_request (GtkWidget *widget, GtkRequisition *requisition) {
	requisition->width = ((GtkWidget2 *) widget)->width; requisition->height = ((GtkWidget2 *) widget)->height;
}

static void gtk_widget_2_size_allocate (GtkWidget *widget, GtkAllocation *allocation) {
	widget->allocation = *allocation;
	if (gtk_widget_get_realized (widget) == TRUE) {gdk_window_move_resize (widget->window, allocation->x, allocation->y, allocation->width, allocation->height); ((GtkWidget2 *) widget)->width = allocation->width; ((GtkWidget2 *) widget)->height = allocation->height;}
}

static void gtk_widget_2_show (GtkWidget *widget) {
	GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
	
	GdkWindowAttr status1; status1.window_type = GDK_WINDOW_CHILD; status1.x = widget->allocation.x; status1.y = widget->allocation.y; status1.width = ((GtkWidget2 *) widget)->width; status1.height = ((GtkWidget2 *) widget)->height; status1.wclass = GDK_INPUT_OUTPUT; status1.event_mask = GDK_ALL_EVENTS_MASK;
	widget->window = gdk_window_new (gtk_widget_get_parent_window (widget), &status1, GDK_WA_X | GDK_WA_Y);
	gdk_window_set_user_data (widget->window, widget);
	widget->style = gtk_style_attach (widget->style, widget->window);
	gtk_style_set_background (widget->style, widget->window, GTK_STATE_NORMAL);
}

static gboolean gtk_widget_2_refresh (GtkWidget *widget, GdkEventExpose *event) {
	if (((GtkWidget2 *) widget)->draw != NULL) return ((GtkWidget2 *) widget)->draw ((GtkWidget2 *) widget, event); else return FALSE;
}

static void gtk_widget_2_destroy (GtkObject *object) {
	GtkWidget2Class *class = (GtkWidget2Class *) gtk_type_class (gtk_widget_get_type ());
	if (((GtkWidget2 *) object)->forget != NULL) ((GtkWidget2 *) object)->forget ((GtkWidget2 *) object);
	if (GTK_OBJECT_CLASS (class)->destroy != NULL) (* GTK_OBJECT_CLASS (class)->destroy) (object);
}

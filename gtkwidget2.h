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

#include <gtk/gtk.h>

typedef struct GtkWidget2Class GtkWidget2Class;
typedef struct GtkWidget2 GtkWidget2;

struct GtkWidget2Class {GtkWidgetClass parent;};
struct GtkWidget2 {
	GtkWidget widget;
	int index; char *label; void *data;
	int width, height;
	
	gboolean (* draw) (GtkWidget2 *widget, GdkEventExpose *event);
	void (* forget) (GtkWidget2 *widget);
};

unsigned long gtk_widget_2_get_id ();

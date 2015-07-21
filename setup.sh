#!/bin/bash

if (test "$1" = "build"); then
	rm -rf libgtkwidget2.so || exit 1
	gcc gtkwidget2.c $(pkg-config --cflags --libs gtk+-2.0) -fPIC -shared -o libgtkwidget2.so || exit 1
	
elif (test "$1" = "install"); then
	cp -f libgtkwidget2.so /usr/lib || exit 1
	cp -f gtkwidget2.h /usr/include || exit 1
	cp -f gtkwidget2.pc /usr/lib/pkgconfig || exit 1
	
elif (test "$1" = "remove"); then
	rm -rf /usr/lib/libgtkwidget2.so /usr/include/gtkwidget2.h /usr/lib/pkgconfig/gtkwidget2.pc || exit 1
	
fi

#Compiler choose for the process:
CC=gcc
GC=g++
#Compilation flags:
#pkg-config --libs --cflags dbus-1 gobject-2.0 glib-2.0 gio-2.0 gthread-2.0 gio-unix-2.0
CFLAGS=-c -Wall
PICFLAG=-c -fPIC -Wall
PLUSFLAGS=-c -Wall

#PATH=home/catalin/Documents/DBus/CDBusSharedLibrary/SharedObject/clientproxylibrary.o

#INCLUDES=-I/usr/include/glib-2.0 \
#-I/usr/include/dbus-1.0 \
#-I/usr/include/gio-unix-2.0 \
#-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
#-I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
#-I/usr/lib/x86_64-linux-gnu

INCLUDES=-I.
SOURCES=-L.

GLIB=-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0

LIBS=`pkg-config --libs --cflags dbus-1 glib-2.0 gio-2.0 gthread-2.0 gio-unix-2.0 gobject-2.0`



all:libCP.so CPPClient

CPPClient:CPPClient.o  libCP.so
	$(GC) -Wall -I$(PWD) -L$(PWD) -Wl,-rpath=$(PWD) CPPClient.o -o CPPClient -lCP -lglib-2.0

CPPClient.o:CPPClient.cpp
	$(GC) $(PLUSFLAGS)  CPPClient.cpp -o CPPClient.o $(LIBS)

libCP.so: clientproxylibrary.o
	$(CC) -shared clientproxylibrary.o alarmClockStubs.o -o libCP.so $(LIBS)

clientproxylibrary.o: alarmClockStubs.o
	$(CC) -c -fPIC clientproxylibrary.c -o clientproxylibrary.o $(LIBS)

alarmClockStubs.o:alarmClockStubs.c 
	gcc -c -fPIC alarmClockStubs.c -o alarmClockStubs.o $(LIBS)
	
alarmClockStubs.c:
	gdbus-codegen --generate-c-code alarmClockStubs --c-namespace alarmClock --interface-prefix com.time.service. --c-generate-object-manager time_service_alarmClock.xml

clean:
	rm -f libCP.so *.o CPPClient




PROGNAME = listflock
#PROGNAME = treeflock
PROGNAME = arrayflock
PROGNAME = arraydel

objects =$(PROGNAME).o birds.o
#CFLAGS = -g -Wall -O3
CFLAGS = -g -Wall `pkg-config --cflags glib-2.0` -std=gnu99 #-O3 
LINKFLAGS = -L/usr/local/lib -lapophenia -lgsl -lgslcblas -lsqlite3 `pkg-config --libs glib-2.0` 
CC = gcc
#CC = g++

#By default, this runs latex twice on the document named above.
#Alternatively, you can run any of the targets listed below.

c: $(objects)
	$(CC) $(CFLAGS) $(objects) $(LINKFLAGS) -o $(PROGNAME)


$(DOCNAME).dvi: $(DOCNAME).tex
	latex $(DOCNAME);echo "-------------------------------";latex $(DOCNAME)


$(objects): %.o: %.c 
		$(CC) $(CFLAGS) -c $< -o $@

debug:
	kdbg $(PROGNAME)&
linect:
	grep -i "void\|,\|;" *.c|wc -l
	grep "[^ 	]" *.c |wc -l 

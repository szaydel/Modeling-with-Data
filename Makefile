#This Makefile will work for most simple C projects.
#
#To make it work, you may have to make a few changes:
#
#Set PROGNAME to your main file (without the .c ending). 
#E.g., if you are compiling dosomething.c, change the first non-comment
#line to 
#PROGNAME = dosomething
#
#Second, the LINKFLAGS line refers to all of Apophenia, the GSL,
#and SQLITE. If any of these elements are not on your system,
#you will need to delete the corresponding link flag from
#this line. Notice that the GSL has two -l flags and the other
#libraries have only one.
#In some cases, (if you get errors like `undefined symbol sqrt') 
#you will need to add the -lm flag (for the math library) to this line.

#After you make these two changes, you should be able to type
# make
#from the command prompt to compile your program. If you get a 
#`command not found' error, then you will need to go back to your
#package manager to install make.

PROGNAME = main_file_name

OBJECTS =$(PROGNAME).o
CFLAGS = -g -Wall -std=gnu99
LINKFLAGS = -L/usr/local/lib -lapophenia -lgsl -lgslcblas -lsqlite3

$(PROGNAME): $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $(LINKFLAGS) -o $(PROGNAME)

$(objects): %.o: %.c 
	gcc $(CFLAGS) -c $< -o $@

clean: 
	rm *.o

run: $(PROGNAME)
	./$(PROGNAME) $(PARGS)

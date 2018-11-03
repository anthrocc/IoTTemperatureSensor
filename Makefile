CC=gcc
CFLAGS=-lWarn -pedantic

temp: temp.o libmyifttt.a
	 cc temp.o -L. -lmyifttt -lcurl -o temp

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

alarm.o:	temp.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	temp

clean:
	rm tester irtester *.o

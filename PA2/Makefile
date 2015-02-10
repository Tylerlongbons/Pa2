#MakeFile for PA2
#Tyler Longbons

CC=g++
CFLAGS=-c -Wall -I.
OFLAGS=-o

pa2: main.o image.o
				$(CC) main.o image.o $(OFLAGS) pa2

main.o: main.cpp
				$(CC) $(CFLAGS) main.cpp

image.o: image.cpp image.h
				$(CC) $(CFLAGS) image.cpp

clean:
				rm -f *.o pa2

tar:
				tar cf pa2.tar *.cpp *.h Makefile																
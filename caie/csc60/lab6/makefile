#Eric Cai
#Section 3
CC=gcc
CFLAGS=-lm
EXE = lab6
all: $(EXE)

$(EXE): main.o radius_inside_circle.o radius_outside_circle.o semi_perimeter.o
	$(CC) $(CFLAGS) -o lab6  main.o radius_inside_circle.o radius_outside_circle.o semi_perimeter.o 

main.o: lab6.h main.c
	$(CC) $(CFLAGS) -c main.c

radius_inside_circle.o: lab6.h  radius_inside_circle.c
	$(CC) $(CFLAGS) -c radius_inside_circle.c

radius_outside_circle.o: lab6.h radius_outside_circle.c
	$(CC) $(CFLAGS) -c radius_outside_circle.c
	
semi_perimeter.o: lab6.h semi_perimeter.c
	$(CC) $(CFLAGS) -c semi_perimeter.c

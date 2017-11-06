CFLAGS = -Wall -pedantic
Zad1: main.c
	gcc main.c -o Zad1.exe ${CFLAGS} -DPIPE

Zad2: main.c
	gcc main.c -o Zad2.exe ${CFLAGS} -DFIFO
	
all: Zad1 Zad2

clean:
	@rm -fr *.o
	@rm -fr *.exe
    

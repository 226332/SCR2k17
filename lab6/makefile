CFLAGS = -Wall -pedantic -lrt
Zad1: main.c
	gcc main.c -o Zad1.exe ${CFLAGS} 
	
all: Zad1 

run: Zad1
	./Zad1.exe lena.png
	
format:
	@clang-format main.c -i

clean:
	@rm -fr *.o
	@rm -fr *.exe
    

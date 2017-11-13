CFLAGS = -Wall -pedantic -lrt
Zad1: main.c
	gcc main.c -o Zad1.exe -O3 ${CFLAGS} 
	
all: Zad1 

valgrind: main.c
	gcc main.c -o Zad1.exe ${CFLAGS} -DVALGRIND
	valgrind ./Zad1.exe lena.png

run: Zad1
	./Zad1.exe lena.png
	
format:
	@clang-format main.c -i

clean:
	@rm -fr *.o
	@rm -fr *.exe
    

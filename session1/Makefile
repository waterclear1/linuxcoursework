all: main_static main_shared



#static
static: main_static
main_static: main.c libstrutils.a
	gcc main.c -L. -lstrutils -o main_static
libstrutils.a: bstrutils.o 
	ar rcs libstrutils.a bstrutils.o
bstrutils.o: bstrutils.c strutils.h
	gcc -Wall -c bstrutils.c -o bstrutils.o
#shared
shared: main_shared
main_shared: main.c libstrutils.a
	gcc main.c -L. -lstrutils -o main_shared
libstrutils.so: bstrutils_PIC.o
	gcc -shared bstrutils_PIC.o -o libstrutils.so
bstrutils_PIC.o:
	gcc -Wall -c -fPIC  bstrutils.c -o bstrutils_PIC.o
clean:
	rm -f *.o *.a *.so main_static main_shared


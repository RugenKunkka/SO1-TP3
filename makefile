CC= gcc
CFLAGS= -Wall -Werror -pedantic
DEPS = tp2.h cJSON.h
OBJ = main.o tp2.o cJSON.o libpto3.o
.INTERMEDIATE: $(OBJ)

compile: $(OBJ)	libpto3static.a libpto3.so
		$(CC) -o main $(OBJ) -L. libpto3static.a -L. libpto3.so -ldl -Wl,-rpath,. $(CFLAGS)	

main.o: main.c	libpto3.so 
		$(CC) -c $(CFLAGS) main.c

tp2.o: tp2.c tp2.h
		$(CC) -c $(CFLAGS) tp2.c	

libpto3.so: libpto3.o cJSON.o		
		$(CC) $(CFLAGS) -shared -fPIC -o libpto3.so libpto3.o cJSON.o

libpto3.o: libpto3.c libpto3static.a
		$(CC) -c $(CFLAGS) -fPIC libpto3.c

libpto3static.a: cJSON.o
		ar crs libpto3static.a cJSON.o

cJSON.o: cJSON.c cJSON.h
		$(CC) -c $(CFLAGS) cJSON.c
    
.PHONY: clean

clean:
		rm -rf main *.o *.so *.a
objects := $(wildcard lib/*.c)

CFLAGS := -fPIC -ggdb -I. -L. -labcrypto -lcrypto

all: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 libabcrypto.so

ex1: ex/ex1.c
	gcc -o ex1 ex/ex1.c $(CFLAGS) 

ex2: ex/ex2.c
	gcc -o ex2 ex/ex2.c $(CFLAGS) 

ex3: ex/ex3.c
	gcc -o ex3 ex/ex3.c $(CFLAGS) 

ex4: ex/ex4.c
	gcc -o ex4 ex/ex4.c $(CFLAGS) 

ex5: ex/ex5.c
	gcc -o ex5 ex/ex5.c $(CFLAGS) 

ex6: ex/ex6.c libabcrypto.so
	gcc -o ex6 ex/ex6.c $(CFLAGS) 

ex7: ex/ex7.c
	gcc -o ex7 ex/ex7.c $(CFLAGS) 

ex8: ex/ex8.c
	gcc -o ex8 ex/ex8.c $(CFLAGS) 

libabcrypto.so: $(objects)
	gcc -fPIC -shared -O0 -ggdb -o libabcrypto.so $(objects)

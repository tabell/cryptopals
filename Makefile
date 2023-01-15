objects := $(wildcard lib/*.c)

COMPILER := clang
BUILDDIR := build
CFLAGS := -fPIC -ggdb -I. -L$(BUILDDIR)/lib -lssl -lcrypto -labcrypto


all: abcrypto ex1 ex2 ex3 ex4 ex5 ex6 ex7

ex1: ex/ex1.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex1 ex/ex1.c $(CFLAGS)

ex2: ex/ex2.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex2 ex/ex2.c $(CFLAGS)

ex3: ex/ex3.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex3 ex/ex3.c $(CFLAGS)

ex4: ex/ex4.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex4 ex/ex4.c $(CFLAGS)

ex5: ex/ex5.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex5 ex/ex5.c $(CFLAGS)

ex6: ex/ex6.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex6 ex/ex6.c $(CFLAGS)

ex7: ex/ex7.c abcrypto
	$(COMPILER) -o $(BUILDDIR)/bin/ex7 ex/ex7.c $(CFLAGS)

abcrypto: $(objects)
	$(COMPILER) -fPIC -shared -O0 -ggdb -o $(BUILDDIR)/lib/libabcrypto.so $(objects)

clean:
	rm -rfv $(BUILDDIR)

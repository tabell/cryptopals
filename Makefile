objects := $(wildcard *.c)
main: $(objects)
	gcc -O0 -ggdb -o cpals $(objects)

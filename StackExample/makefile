all:py input

py:test.c tree.c stack.c link.c
	gcc -ggdb -o $@ $^

input:input.c tree.c stack.c link.c
	gcc -ggdb -o $@ $^

clean:
	rm py input

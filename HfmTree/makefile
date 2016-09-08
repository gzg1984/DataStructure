all:hfm hfmcode

hfm:test.c stack.c link.c
	gcc -ggdb -o $@ $^

hfmcode:hfmcode.c
	gcc -ggdb -o $@ $^


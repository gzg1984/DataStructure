all:
	gcc -pg -o box.d box.c -lcurses
	./box.d
	gprof box.d gmon.out

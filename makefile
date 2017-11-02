all: dir.c
	gcc -o "dir" dir.c
run: all
	./dir
clean:
	rm dir
	rm *~
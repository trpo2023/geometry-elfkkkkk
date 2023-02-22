main: main.c
	gcc -Wall -Werror -o bin/main main.c

run: main
	./bin/main
clean:
	rm bin/main
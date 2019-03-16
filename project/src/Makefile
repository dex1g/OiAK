all: clean buildSource run

buildSource:
	gcc -g -Wall -o oiakProject.exe $(wildcard *.c)
run:
	./oiakProject.exe

clean:
	rm -f ./oiakProject.exe
all: clean buildSource run

buildSource:
	gcc -m32 -g -Wall -o oiakProject.exe $(wildcard *.c)
run:
	./oiakProject.exe

clean:
	rm -f ./oiakProject.exe
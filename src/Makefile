all: clean Source

buildSource:
	gcc -g -m32 -std=c99 -Wno-unused-result -Wall $(wildcard *.c) $(wildcard *.s) -o oiakProject.exe

Source: buildSource
	./oiakProject.exe

Valgrind: buildSource
	valgrind -v --leak-check=full ./oiakProject.exe

clean:
	rm -f ./oiakProject.exe

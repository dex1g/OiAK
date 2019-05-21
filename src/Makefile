all: clean Source

buildSource:
	gcc -g -m32 -std=c99 -Wno-unused-result -fsanitize=address -fno-omit-frame-pointer -Wall $(wildcard *.c) $(wildcard *.s) -o oiakProject.exe

buildSourceValgrind:
	gcc -g -m32 -std=c99 -Wno-unused-result -Wall $(wildcard *.c) $(wildcard *.s) -o oiakProjectValgrind.exe

Source: buildSource
	./oiakProject.exe

Valgrind: buildSourceValgrind
	valgrind -v --leak-check=full ./oiakProjectValgrind.exe

clean:
	rm -f ./oiakProject.exe

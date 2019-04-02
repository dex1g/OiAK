all: clean buildUnitTests runUnitTests

sourcePath = ../src/

buildUnitTests: 
	gcc -m32 $(wildcard *.c) $(filter-out ../src/main.c, $(wildcard ../src/*.c)) ./unity/src/unity.c -o tests.exe

runUnitTests:
	./tests.exe

clean:
	rm -f tests.exe
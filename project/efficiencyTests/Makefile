all: EfficiencyTests

buildEfficiencyTests:
	gcc -g -m32 EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c -o EfficiencyTests.exe

EfficiencyTests: buildEfficiencyTests
	./EfficiencyTests.exe

clean:
	rm -f EfficiencyTests.exe
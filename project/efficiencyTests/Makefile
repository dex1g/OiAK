all: EfficiencyTests

buildEfficiencyTests:
	gcc -O3 -m32 EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTests.exe

EfficiencyTests: buildEfficiencyTests
	./EfficiencyTests.exe

clean:
	rm -f EfficiencyTests.exe
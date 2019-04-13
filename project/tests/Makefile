all: clean

buildParserTests: 
	gcc -m32 $(wildcard ParserTests.c) $(filter-out ../src/main.c, $(wildcard ../src/*.c)) ./unity/src/unity.c -o parserTests.exe

buildArithmeticTests: 
	gcc -m32 $(wildcard ArithmeticOperationTests.c) $(filter-out ../src/main.c, $(wildcard ../src/*.c)) ./unity/src/unity.c -o testsArithmetic.exe

ParserTests: buildParserTests
	./parserTests.exe

ArithmeticOperationTests: buildArithmeticTests
	./testsArithmetic.exe

AllTests: ParserTests OperationTests

clean:
	rm -f parserTests.exe testsArithmetic.exe
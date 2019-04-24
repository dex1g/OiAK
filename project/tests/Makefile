all: clean

buildParserTests: 
	gcc -m32 ParserTests.c ../src/Parser.c ./unity/src/unity.c -o ParserTests.exe

buildArithmeticTests: 
	gcc -m32 ArithmeticOperationsTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./unity/src/unity.c -o ArithmeticOperationTests.exe

ParserTests: buildParserTests
	./ParserTests.exe

ArithmeticOperationTests: buildArithmeticTests
	./ArithmeticOperationTests.exe

AllTests: ParserTests ArithmeticOperationTests

clean:
	rm -f ParserTests.exe ArithmeticOperationTests.exe
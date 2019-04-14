all: clean

buildParserTests: 
	gcc -m32 ParserTests.c ../src/Parser.c ./unity/src/unity.c -o ParserTests.exe

buildArithmeticTests: 
	gcc -m32 ArithmeticOperationsTests.c ../src/ArithmeticOperations.c ../src/Parser.c ./unity/src/unity.c -o ArithmeticOperationTests.exe

ParserTests: buildParserTests
	./ParserTests.exe

ArithmeticOperationTests: buildArithmeticTests
	./ArithmeticOperationTests.exe

AllTests: ParserTests OperationTests

clean:
	rm -f ParserTests.exe ArithmeticOperationTests.exe
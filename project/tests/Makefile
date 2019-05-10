all: clean

buildParserTests: 
	gcc -Wall -std=c99 -Wno-unused-result -m32 ParserTests.c ../src/Parser.c ./unity/src/unity.c -o ParserTests.exe

buildArithmeticTests: 
	gcc -g -Wall -std=c99 -Wno-unused-result -m32 ArithmeticOperationsTests.c $(wildcard ../src/*.s) ../efficiencyTests/PastImplementations/LessEfficientOperations.c ../src/ArithmeticOperations.c ../src/Parser.c ./unity/src/unity.c -o ArithmeticOperationTests.exe

ParserTests: buildParserTests
	./ParserTests.exe

ArithmeticOperationTests: buildArithmeticTests
	./ArithmeticOperationTests.exe

AllTests: ParserTests ArithmeticOperationTests

clean:
	rm -f ParserTests.exe ArithmeticOperationTests.exe

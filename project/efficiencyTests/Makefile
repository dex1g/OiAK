all: EfficiencyTests

buildEfficiencyTests:
	gcc -Wall -O0 -std=c99 -Wno-unused-result -m32 EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTests.exe

EfficiencyTests: buildEfficiencyTests
	./EfficiencyTests.exe

buildEfficiencyTestsExcel:
	gcc -Wall -Ofast -std=c99 -Wno-unused-result -m32 EfficiencyTestsExcel.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTestsExcel.exe

EfficiencyTestsExcel: buildEfficiencyTestsExcel
	./EfficiencyTestsExcel.exe

buildGprofTest:
	gcc -Wall -std=c99 -Wno-unused-result -m32 -pg EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyGprof.exe

outputGprofToFile:
	gprof EfficiencyGprof.exe gmon.out > profile-data.txt    

runGprofExe:
	./EfficiencyGprof.exe

GprofTest: buildGprofTest runGprofExe outputGprofToFile

clean:
	rm -f EfficiencyTests.exe EfficiencyGprof.exe profile-data.txt gmon.out EfficiencyTestsExcel.exe


all: EfficiencyTests

buildEfficiencyTests:
	gcc -Wall -O3 -m32 EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTests.exe

EfficiencyTests: buildEfficiencyTests
	./EfficiencyTests.exe

buildGprofTest:
	gcc -Wall -m32 -pg EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyGprof.exe

outputGprofToFile:
	gprof EfficiencyGprof.exe gmon.out > profile-data.txt    

runGprofExe:
	./EfficiencyGprof.exe

GprofTest: buildGprofTest runGprofExe outputGprofToFile

clean:
	rm -f EfficiencyTests.exe EfficiencyGprof.exe profile-data.txt gmon.out
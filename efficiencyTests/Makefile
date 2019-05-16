all: EfficiencyTests

buildEfficiencyTests:
	gcc -g -Wall -O3 -std=c99 -Wno-unused-result -m32 EfficiencyTests.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTests.exe

EfficiencyTests: buildEfficiencyTests
	./EfficiencyTests.exe

buildEfficiencyTestsExcel:
	gcc -Wall -Ofast -std=c99 -Wno-unused-result -m32 EfficiencyTestsExcel.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c ./PastImplementations/LessEfficientOperations.c  -o EfficiencyTestsExcel.exe

EfficiencyTestsExcel: buildEfficiencyTestsExcel
	./EfficiencyTestsExcel.exe

buildGprofTest:
	gcc -Wall -std=c99 -Wno-unused-result -m32 -pg Profiling.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c -o Profiling.exe

buildGprofTestDebug:
	gcc -g -fsanitize=address -fno-omit-frame-pointer -Wall -std=c99 -Wno-unused-result -m32 Profiling.c $(wildcard ../src/*.s) ../src/ArithmeticOperations.c ../src/Parser.c -o Profiling.exe


outputGprofToFile:
	gprof Profiling.exe gmon.out > profile-data.txt    

runGprofExe:
	./Profiling.exe

GprofTest: buildGprofTest runGprofExe outputGprofToFile

clean:
	rm -f EfficiencyTests.exe EfficiencyTestsExcel.exe Profiling.exe profile-data.txt gmon.out 


all: app

app:
	gcc -m32 -O3 -std=c99 -o app timetest.c registryOperationTime.s proctime.s memoryOperationTime.s writeOperationTime.s

clean:
	rm app

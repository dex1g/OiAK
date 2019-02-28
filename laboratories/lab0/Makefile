all: hello read

hello: hello.o
	ld hello.o -o hello

hello.o: hello.s
	as hello.s -o hello.o

read: read.o
	ld read.o -o read

read.o: read.s
	as read.s -o read.o

clean:
	rm -f hello hello.o read read.o

# Automaticaly assembles the program, creates object file and produces executable
# to run it simply run make
# to clean the file simply run make clean

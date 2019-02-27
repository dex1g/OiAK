hello: hello.o
	ld hello.o -o hello

hello.o: hello.s
	as hello.s -o hello.o

all: hello

clean:
	rm -f hello hello.o

# Automaticaly assembles the program, creates object file and produces executable
# to run it simply run make
# to clean the file simply run make clean
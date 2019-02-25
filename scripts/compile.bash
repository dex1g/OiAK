# a quick script to assembly && link file specified by name in parameter
# usage ./compile scriptName WITHOUT ANY EXTENSION
as $1.s -o $1.o;
ld $1.o -o $1;
./$1;
echo $?
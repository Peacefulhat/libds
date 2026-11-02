#!/bin/zsh
#compile the .c file
#gcc -c libds.c
#ar rcs libds.a libds.o # this command creates the static library
#gcc -ggdb -o main main.c libda.c #-L. -l:libds.a
Mode=$1

if [[ "$Mode" == "Debug" ]]; then
    gcc -ggdb -o main main.c libda.c libstr.c libstack.c
else
    gcc -ggdb -o main main.c -L. -l:libda.a -l:libstr.a -l:libstack.a

fi

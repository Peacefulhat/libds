#!/bin/zsh
#compile the .c file
#gcc -c libds.c
#ar rcs libds.a libds.o # this command creates the static library
#gcc -ggdb -o main main.c libda.c #-L. -l:libds.a

gcc -ggdb -o main main.c -L. -l:libda.a -l:libstr.a

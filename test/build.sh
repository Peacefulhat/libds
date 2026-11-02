#!/bin/zsh

gcc -o main $1 -L../ -l:libda.a -l:libstr.a -l:libstack.a

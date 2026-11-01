#!/bin/zsh

FileName="$1"
ArgHelp="$1"

Usage(){
    echo "Usage: build.sh <filename>"
    echo "Run build.sh script with filename for which you want to generate a static library."
    exit 1
}

if [[ -z "$FileName" ]]; then
    echo "Error: No file name was provided. For help, run build.sh with 'h' as an argument."
    exit 1

elif [[ "$ArgHelp" == "h" ]]; then
    Usage
else
    gcc -c "$FileName"
    LibFileName="${FileName:0:(-2)}.a"
    ObjFileName="${FileName:0:(-2)}.o"
    ar rcs "$LibFileName" "$ObjFileName"
    echo "Library: $LibFileName, generated."
    echo "  use -l:$LibFileName to link it to static library."
    rm -rf "$ObjFileName"
fi

#ar rcs libds.a libds.o

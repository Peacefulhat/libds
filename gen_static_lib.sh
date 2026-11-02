#!/bin/zsh

# put file name here which you want to generate library for
LibsToGenFrom=("libda.c" "libstr.c" "libstack.c")
LinkerFlag=()

for File in "${LibsToGenFrom[@]}"; do
    gcc -c "$File"
    LibFileName="${File:0:(-2)}.a"
    ObjFileName="${File:0:(-2)}.o"
    ar rcs "$LibFileName" "$ObjFileName"
    echo "Library: $LibFileName, generated."
    LinkerFlag+=("$LibFileName")
    rm -rf "$ObjFileName"
done

echo -n "use "
for LFile in "${LinkerFlag[@]}"; do
    echo -n "-l:$LFile, "
done
echo -n "to link it to static library."

#ar rcs libds.a libds.o

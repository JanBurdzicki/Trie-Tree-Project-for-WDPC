#!/bin/bash

cd "/media/jan/Shared/Janek/PROGRAMOWANIE/C++/Studia/Wstep Do Programowania w Jezyku C/Lista 9/Drzewo Trie/"

mkdir -p build

cd src

gcc Trie_Tree.c -c
gcc Input_Handling.c -c
gcc Messages_Printing.c -c

gcc -g -std=c17 -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector 'main.c' -o 'main' Input_Handling.o Messages_Printing.o Trie_Tree.o -lm

mv *.o ../build
mv main ../build

cd ..
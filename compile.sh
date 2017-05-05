#!/usr/bin/env bash

echo "Compiling to source and linking headers";
g++ -c main.cpp;

g++ main.o -o sfml-game -lsfml-graphics -lsfml-window -lsfml-system;

echo "Done!"

exit 0;
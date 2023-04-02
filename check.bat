@echo off

set CFLAGS=-fsyntax-only -O3 -Iinclude -std=c17 -Wall -Wextra -Wpedantic -pedantic -Wno-strict-prototypes -Wmissing-prototypes -Wimplicit-fallthrough

gcc src/*.c -o build/main.exe %CFLAGS%
clang src/*.c -o build/main.exe %CFLAGS%

@echo off

set CC=clang
set CFLAGS=-O3 -Iinclude -Wall -Wextra -Wpedantic -std=c17 -Wno-strict-prototypes

%CC% src/*.c -o build/main.exe %CFLAGS%

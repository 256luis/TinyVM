@echo off

set CC=clang
set CFLAGS=-O3 -Iinclude -std=c17 -Wall -Wextra -Wpedantic -pedantic -Wno-strict-prototypes -Wmissing-prototypes -Wimplicit-fallthrough

%CC% src/*.c -o build/main.exe %CFLAGS%

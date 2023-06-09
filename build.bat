@echo off

set CC=clang
set CFLAGS=-fsanitize=address -g -O0 -Iinclude -std=c17 -Wall -Wextra -Wpedantic -pedantic -Wno-strict-prototypes -Wmissing-prototypes -Wimplicit-fallthrough

%CC% src/*.c -o build/tvm.exe %CFLAGS%

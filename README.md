# Jotto-Problem
A fast O(n^3/64) solution written in C++ for the so called Jotto problem

On my machine, this runs in ~0.22s for the first word list and in ~0.44s for the second one. The implementation is (somewhat) parallelised but it's not faster than running it sequentially on my 8 thread CPU.

Compiled on WSL2 with
```
g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=256144 -Wall -Wextra -pedantic -o C.exe C.cpp -ltbb
```

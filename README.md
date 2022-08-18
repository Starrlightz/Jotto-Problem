# Jotto-Problem
A fast O(n^3/64) solution written in C++ for the so called Jotto problem, finding 5 words which use 25 different letters of the alphabet.

On my machine, this runs in ~0.22s for the first word list and in ~0.44s for the second one. The implementation is (somewhat) parallelised but it's not faster than running it sequentially on my 8 thread CPU.

Compiled on WSL2 with
```b
g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=65536 -Wall -Wextra -pedantic -o B B.cpp -ltbb
```
You can test the code by doing 
```b
# smaller dictionary
make B
./B
# bigger dictionary
make C
./C
```

- `words_alpha.txt` is taken from https://github.com/dwyl/english-words
- `wordle-combined.txt` is a merger of the two files from https://gist.github.com/cfreshman

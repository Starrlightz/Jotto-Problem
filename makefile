B: B.cpp
	sudo apt install libtbb-dev
	ulimit -s 65536
	g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=65536 -Wall -Wextra -pedantic -o B B.cpp -ltbb
C: C.cpp
	sudo apt install libtbb-dev
	ulimit -s 65536
	g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=65536 -Wall -Wextra -pedantic -o C C.cpp -ltbb

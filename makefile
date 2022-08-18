B: B.cpp
	sudo apt install libtbb-dev
	g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=256144 -Wall -Wextra -pedantic -o B.exe B.cpp -ltbb
C: C.cpp
	sudo apt install libtbb-dev
	g++ -Ofast -unroll-loops -std=c++17 -Wl,-z,stack-size=256144 -Wall -Wextra -pedantic -o C.exe C.cpp -ltbb
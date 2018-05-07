
GCC=g++ -std=c++17
D=Build

all: 
	$(GCC) main.cpp -o $D/run.exe

run: all
	$D/run.exe


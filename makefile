
GCC=g++ -std=c++17
D=Build

all: main.o Parse.o
	$(GCC) $D/main.o $D/Parse.o -o $D/run.exe

main.o: main.cpp
	$(GCC) main.cpp -c -o $D/main.o
	
Parse.o: Parse.cpp
	$(GCC) Parse.cpp -c -o $D/Parse.o

run: all
	$D/run.exe

clean:
	rm $D/*
	
force: clean all



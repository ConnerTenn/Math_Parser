
GCC=g++ -std=c++17 -Wall
D=Build

all: main.o Parse.o ReversePolish.o
	$(GCC) $D/main.o $D/Parse.o $D/ReversePolish.o -o $D/run.exe

main.o: main.cpp
	$(GCC) main.cpp -c -o $D/main.o
	
Parse.o: Parse.cpp
	$(GCC) Parse.cpp -c -o $D/Parse.o

ReversePolish.o: ReversePolish.cpp
	$(GCC) ReversePolish.cpp -c -o $D/ReversePolish.o

run: all
	$D/run.exe

clean:
	rm $D/*
	
force: clean all



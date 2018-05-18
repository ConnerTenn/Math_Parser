
VERSION=2

GPP=g++ -std=c++17 -Wall
D=Build
F=-D VERSION="$(VERSION)"

all1: main.o Parse.o ReversePolish.o
	$(GPP) $D/main.o $D/Parse.o $D/ReversePolish.o -o $D/run.exe

all2: main.o
	$(GPP) $D/main.o -o $D/run.exe

main.o: main.cpp
	$(GPP) main.cpp $F -c -o $D/main.o
	
Parse.o: Parse.cpp
	$(GPP) Parse.cpp -c -o $D/Parse.o

ReversePolish.o: ReversePolish.cpp
	$(GPP) ReversePolish.cpp -c -o $D/ReversePolish.o

run: all$(VERSION)
	$D/run.exe

clean:
	rm $D/* -f
	
force: clean all$(VERSION)



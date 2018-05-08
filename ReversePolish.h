
class Elem;
class Value;
class Operation;

#ifndef _REVERSEPOLISH_H_
#define _REVERSEPOLISH_H_

#include <iostream>
#include <string>
#include <vector>

extern std::vector<Elem> ElemList;

enum Operations
{
	ADD,
	SUB
};

struct Elem
{
	int Type;
	int Value;
	
	Elem(int type, int value);
};

int Evaluate();

#endif

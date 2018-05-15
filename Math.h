
#ifndef _MATH_H_
#define _MATH_H_

#include <iostream>
#include <string>
#include <math.h>

template<typename T>
struct Elem
{
	T Value;
	
	Elem<T> *Prev = 0;
	Elem<T> *Next = 0;
};

template<typename T>
struct List
{
	Elem<T> *First = 0;
	Elem<T> *Last = 0;
};

template<typename T>
void Push(List<T> list, T value)
{
	Elem<T> *newElem = new Elem<T>;
	
	if (!list.First) { list.First = newElem; }
	if (list.Last) { list.Last->Next = newElem; }
	newElem->Prev = list.Last;	
	list.Last = newElem;
}

template<typename T>
T Pop(List<T> list)
{
	Elem<T> *last = list.Last;
	if (last)
	{
		T value = last->Value;
		list.Last = last->Prev;
		if (last == list.First) { list.First = 0; }
		
		delete last; 
		return value;
	}
	return 0;
}


List<char> OperatorList;
List<double> ValueList;

double Accumulator = 0;
int DecimalPlace = -1;

enum States
{
	NUL,
	NUM,
	OPE,
	OBR,
	CBR,
	END
};
States State = NUL, PrevState = NUL;


void Operator()
{
	
}

void Calc(char *line)
{
	int i = 0;
	
	while (State != END)
	{
		if (line[i] != ' ')
		{
			if (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
			{
				State = NUM;
				//Create a loop in here
				if (line[i] == '.')
				{
					DecimalPlace = 1;
				}
				else if (DecimalPlace > 0)
				{
					Accumulator+= (line[i]-'0')/pow(10, DecimalPlace);
				}
				else
				{
					Accumulator *= 10;
					Accumulator += (line[i] - '0');
				}
			}
			else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
			{
				State = OPE;
			}
			else if (line[i] == '(')
			{
				State = OBR;
				Push<char>(OperatorList, '(');
			}
			else if (line[i] == ')')
			{
				State = CBR;
			}
			
			//Move to after loop in number handling section
			if (PrevState == NUM && PrevState != State)
			{
				Push<double>(ValueList, Accumulator);
				Accumulator = 0;
			}
			
			PrevState = State;
		}
	}
}

#endif

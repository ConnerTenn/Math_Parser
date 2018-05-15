
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
};

template<typename T>
struct Stack
{
	Elem<T> *Last = 0;
	
	void Push(T value)
	{
		Elem<T> *newElem = new Elem<T>;
		newElem->Prev = Last;
		Last = newElem;
	}
	
	T Pop()
	{
		Elem<T> last = Last;
		T value = last->Value;
		Last = last->Prev;
		delete last;
		return value;
	}
};


Stack<char> OperatorStack;
Stack<double> ValueStack;

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
		if (line[i] == ' ')
		{
			i++;
		}
		else if (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
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
			OperatorStack.Push('(');
		}
		else if (line[i] == ')')
		{
			State = CBR;
		}
		
		//Move to after loop in number handling section
		if (PrevState == NUM && PrevState != State)
		{
			ValueStack.Push(Accumulator);
			Accumulator = 0;
		}
		
		PrevState = State;
	}
}

#endif


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
		newElem->Value = value;
		newElem->Prev = Last;
		Last = newElem;
	}
	
	T Pop()
	{
		Elem<T> *last = Last;
		T value = last->Value;
		Last = last->Prev;
		delete last;
		return value;
	}
};

Stack<char> OperatorStack;
Stack<double> ValueStack;

enum States { NUL, NUM, OPE, OBR, CBR };

int Eval(char ope)
{
	if (!ValueStack.Last) { return 0; } double num2 = ValueStack.Pop();
	if (!ValueStack.Last) { return 0; } double num1 = ValueStack.Pop();
	
	double result = 0;
	
	switch (ope)
	{
	case '+':
		result = num1+num2;
		break;
	case '-':
		result = num1-num2;
		break;
	case '*':
		result = num1*num2;
		break;
	case '/':
		result = num1/num2;
		break;
	case '^':
		result = pow(num1,num2);
		break;
	}
	
	std::cout << "eval:" << num1 << " " << ope << " " << num2 << " = " << result << "\n";
	ValueStack.Push(result);
	return 1;
}


int Precidance(char ope)
{
	//Priority map for each operator
	char order[9][2] = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'P', 1}, {'N', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
	
	for (int i = 0; i < 9; i++)
	{
		if (ope == order[i][0]) { return order[i][1]; }
	}
	
	return -1;
}

double Calc(char *line, int *report = 0, int *errorPos = 0)
{
	bool negative = false;
	States State = NUL, PrevState = NUL;
	
	auto errorFunc = [&](int reportVal, int pos)->int{ if (report) { *report = reportVal; } if (errorPos) { *errorPos = pos; } return 0; };
	
	if (report) { *report = 0; }
	if (errorPos) { *errorPos = 0; }
	
	while (ValueStack.Last) { ValueStack.Pop(); }
	while (OperatorStack.Last) { OperatorStack.Pop(); }
	
	int i = 0;
	while (line[i])
	{
		if (line[i] == ' ') { i++; }
		else if (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
		{
			State = NUM;
			double Accumulator = 0;
			int DecimalPlace = -1;
			int numState = 0;
			
			if (PrevState == NUM) { return errorFunc(1, i); }
			
			while (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
			{
				if (line[i] == '.')
				{
					if (numState != 1) { return errorFunc(1, i); }
					numState = 2;
					DecimalPlace = 10;
				}
				else if (numState == 2)
				{
					Accumulator += double(line[i]-'0')/DecimalPlace;
					DecimalPlace *= 10;
				}
				else
				{
					numState = 1;
					Accumulator *= 10;
					Accumulator += (line[i] - '0');
				}
				
				i++;
			}
			
			//std::cout<< "Acc:" << Accumulator << "\n";
			ValueStack.Push( (negative ? -1 : 1) * Accumulator);
			negative = false;
		}
		else if (Precidance(line[i] >= 0))
		{
			State = OPE;
			
			if (line[i] == '-' && PrevState != NUM && PrevState != CBR) { negative = !negative; }
			else if (line[i] == '+' && PrevState != NUM && PrevState != CBR) { }
			else
			{
				if (PrevState == NUL || PrevState == OPE || PrevState == OBR) { return errorFunc(1, i); }
			
				while (OperatorStack.Last && Precidance(OperatorStack.Last->Value) >= Precidance(line[i]))
				{
					if (!Eval(OperatorStack.Pop())) { return errorFunc(2, i); }
				}
				OperatorStack.Push(line[i]);
			}
			
			i++;
		}
		else if (line[i] == '(')
		{
			State = OBR;
			
			if (PrevState == CBR || PrevState == NUM) { return errorFunc(1, i); }
			
			OperatorStack.Push('(');
			i++;
		}
		else if (line[i] == ')')
		{
			State = CBR;
			
			if (PrevState == NUL || PrevState == OPE || PrevState == OBR) { return errorFunc(1, i); }
			
			char ope = OperatorStack.Pop();
			while (ope != '(')
			{
				if (!Eval(ope)) { errorFunc(2, i); }
				ope = OperatorStack.Pop();
			}
			i++;
		}
		else
		{
			return errorFunc(4, i);
		}
	
		PrevState = State;
	}
	
	while (OperatorStack.Last) { if (!Eval(OperatorStack.Pop())) { return errorFunc(2, i); } }
	
	double result = ValueStack.Pop();
	if (ValueStack.Last) { return errorFunc(3, -1); }
	return result;
}

#endif


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
		if (!Last) { return 0; }
		Elem<T> *last = Last;
		T value = last->Value;
		Last = last->Prev;
		delete last;
		return value;
	}
	
	T Back()
	{
		return Last->Value;
	}
};


Stack<char> OperatorStack;
Stack<double> ValueStack;

enum States
{
	NUL,
	NUM,
	OPE,
	OBR,
	CBR
};

int Eval(char ope)
{
	if (!ValueStack.Last) { return 0; }
	double num1 = ValueStack.Pop();
	if (!ValueStack.Last) { return 0; }
	double num2 = ValueStack.Pop();
	double result = 0;
	
	std::cout << "eval:" << num1 << ope << num2 << "\n";
	
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
	}
	ValueStack.Push(result);
	return 1;
}


int Precidance(char ope)
{
	//Priority map for each operator
	char order[6][2] = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
	
	for (int i = 0; i < 6; i++)
	{
		if (ope == order[i][0]) { return order[i][1]; }
	}
	
	return -1;
}

double Calc(char *line, int *report = 0, int *errorPos = 0)
{
	States State = NUL, PrevState = NUL;
	
	if (report) { *report = 0; }
	
	while (ValueStack.Last) { ValueStack.Pop(); }
	while (OperatorStack.Last) { OperatorStack.Pop(); }
	
	//auto gg = 2;
	auto errorFunc = [&](int reportVal, int pos)->int{ if (report) { *report = reportVal; } if (errorPos) { *errorPos = pos; } return 0; };
	//[=](int reportVal, int pos)->int{ if (report) { *report = reportVal; } if (errorPos) { *errorPos = pos; } return 0; };
	//class lambda []int (int reportVal, int pos)->int errorFunc;
	//lambda 
	/*struct Functor
	{
		int *report, *errorPos;
		Functor(int *reportIn, int *errorPosIn) : report(reportIn), errorPos(errorPosIn) {} 
		int operator()(int reportVal, int pos) { if (report) { *report = reportVal; } if (errorPos) { *errorPos = pos; } return 0; }
	} errorFunc(report, errorPos);*/
	
	int i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
		}
		else if (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
		{
			State = NUM;
			double Accumulator = 0;
			int DecimalPlace = -1;
			
			if (PrevState == NUM) { return errorFunc(1, i); }
			//Create a loop in here
			while (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
			{
				if (line[i] == '.')
				{
					//fix allowing leading decimal place
					if (DecimalPlace >= 0) { return errorFunc(1, i); }
					DecimalPlace = 1;
				}
				else if (DecimalPlace > 0)
				{
					Accumulator+= (line[i]-'0')/pow(10, DecimalPlace);
					DecimalPlace++;
				}
				else
				{
					Accumulator *= 10;
					Accumulator += (line[i] - '0');
				}
				
				i++;
			}
			
			//std::cout<< "Acc:" << Accumulator << "\n";
			ValueStack.Push(Accumulator);
		}
		else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
		{	
			State = OPE;
			
			if (PrevState == NUL || PrevState == OPE || PrevState == OBR) { return errorFunc(1, i); }
			
			if (OperatorStack.Last && Precidance(OperatorStack.Back()) >= Precidance(line[i]))
			{
				if (!Eval(OperatorStack.Pop())) { errorFunc(2, i); }
			}
			OperatorStack.Push(line[i]);
			
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
	
		PrevState = State;
	}
	
	while (OperatorStack.Last) { if (!Eval(OperatorStack.Pop())) { return errorFunc(2, i); } }
	
	double result = ValueStack.Pop();
	if (ValueStack.Last) { return errorFunc(3, -1); }
	return result;
}

#endif

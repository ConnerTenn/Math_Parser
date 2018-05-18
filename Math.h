
#ifndef _MATH_H_
#define _MATH_H_

#include <iostream>
#include <string>
#include <math.h>

//Element of stack
template<typename T>
struct Elem
{
	T Value;
	Elem<T> *Prev = 0;
};

//Stack object
template<typename T>
struct Stack
{
	Elem<T> *Last = 0;
	
	//Adds new element to the stack
	void Push(T value)
	{
		Elem<T> *newElem = new Elem<T>;
		newElem->Value = value;
		newElem->Prev = Last;
		Last = newElem;
	}
	
	//Retrieves the last element and deletes it from the stack
	T Pop()
	{
		Elem<T> *last = Last;
		T value = last->Value;
		Last = last->Prev;
		delete last;
		return value;
	}
};

//Parse States
enum States { NUL, NUM, OPE, OBR, CBR };

//Evaluates an operator using the last two numbers on the stack
int Eval(char ope, Stack<double> &valueStack)
{
	//Retrieve numbers and ensure that they exist on the stack before retrieval
	if (!valueStack.Last) { return 0; } double num2 = valueStack.Pop();
	if (!valueStack.Last) { return 0; } double num1 = valueStack.Pop();
	
	double result = 0;
	
	//evaluate each operator
	if (ope == '+') { result = num1+num2; }
	else if (ope == '-') { result = num1-num2; }
	else if (ope == '*') { result = num1*num2; }
	else if (ope == '/') { result = num1/num2; }
	else if (ope == '^') { result = pow(num1,num2); }
	
	//std::cout << "eval:" << num1 << " " << ope << " " << num2 << " = " << result << "\n";
	valueStack.Push(result); //Add result back to the stack
	return 1;
}


int Precedence(char ope)
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
	//Stacks
	Stack<char> OperatorStack;
	Stack<double> ValueStack;
	
	bool negative = false;
	States State = NUL, PrevState = NUL;
	
	//Function that encapsulates assigning report and errorPos, and checking if the variables are being used 
	auto errorFunc = [&](int reportVal, int pos)->int{ if (report) { *report = reportVal; } if (errorPos) { *errorPos = pos; } return 0; };
	
	//Initilize values if being used
	if (report) { *report = 0; }
	if (errorPos) { *errorPos = 0; }
	
	int i = 0;
	while (line[i]) //Loop till the end of the string
	{
		//Ignore spaces
		if (line[i] == ' ') { i++; } 
		//Parse numbers
		else if (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
		{
			State = NUM;
			double Accumulator = 0;
			int DecimalPlace = -1;
			int numState = 0; //1:integer, 2:decimal
			
			//Check for correct syntax
			if (PrevState == NUM) { return errorFunc(1, i); }
			
			//Loop over the entire number in the string
			while (('0' <= line[i] && line[i] <= '9') || line[i] == '.')
			{
				//Handle period
				if (line[i] == '.')
				{
					if (numState != 1) { return errorFunc(1, i); } //Error; Multiple periods or number has no digit before period
					numState = 2;
					DecimalPlace = 10;
				}
				//Handle the decimal portion
				else if (numState == 2)
				{
					Accumulator += double(line[i]-'0')/DecimalPlace;
					DecimalPlace *= 10;
				}
				//Handle the integer portion
				else
				{
					//Parse the whole number portion
					numState = 1;
					Accumulator *= 10;
					Accumulator += (line[i] - '0');
				}
				
				i++;
			}
			
			//std::cout<< "Acc:" << Accumulator << "\n";
			//Push the number onto the stack. Use correct sign determined by negative operators
			ValueStack.Push( (negative ? -1 : 1) * Accumulator);
			negative = false;
		}
		else if (Precedence(line[i]) > 0)
		{
			State = OPE;
			
			//Detect if a negative or positive operator is used (preceding + or -)
			if (line[i] == '-' && PrevState != NUM && PrevState != CBR) { negative = !negative; }
			else if (line[i] == '+' && PrevState != NUM && PrevState != CBR) { }
			else
			{
				//check for correct syntax
				if (PrevState == NUL || PrevState == OPE || PrevState == OBR) { return errorFunc(1, i); }
			
				//Handle order of operations. Must evaluate operators of higher precedence before a new one is added onto the stack
				while (OperatorStack.Last && Precedence(OperatorStack.Last->Value) >= Precedence(line[i]))
				{
					//Evaluate any operations that need to be completed
					if (!Eval(OperatorStack.Pop(), ValueStack)) { return errorFunc(2, i); }
				}
				//Add new operator onto the stack
				OperatorStack.Push(line[i]);
			}
			
			i++;
		}
		else if (line[i] == '(')
		{
			State = OBR;
			
			//check for correct syntax
			if (PrevState == CBR || PrevState == NUM) { return errorFunc(1, i); }
			
			//Add open bracket marker onto the stack
			OperatorStack.Push('(');
			i++;
		}
		else if (line[i] == ')')
		{
			State = CBR;
			
			//check for correct syntax
			if (PrevState == NUL || PrevState == OPE || PrevState == OBR) { return errorFunc(1, i); }
			
			//Evaluate all operators between the brackets now
			char ope = OperatorStack.Pop();
			while (ope != '(')
			{
				if (!Eval(ope, ValueStack)) { errorFunc(2, i); }
				ope = OperatorStack.Pop();
			}
			i++;
		}
		else
		{
			//Invalid character
			return errorFunc(4, i);
		}
	
		PrevState = State;
	}
	
	//Handle any remaining operators that are on the stack
	while (OperatorStack.Last) { if (!Eval(OperatorStack.Pop(), ValueStack)) { return errorFunc(2, i); } }
	
	double result = ValueStack.Pop();
	if (ValueStack.Last) { return errorFunc(3, -1); } //Error should never occur; syntax checking should catch this error before this point
	return result;
}

#endif

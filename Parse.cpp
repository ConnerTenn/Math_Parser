
#include "Parse.h"

void (* Func)();
void (* LastFunc)();

std::vector<Elem> ElemStack;
std::string String;
long Index = 0;
char Curr = 0;
char Next = 0;

double Acc;
int DecPlace;

void Start();
void End();
void Error();
void White();
void Num();
void Dot();
void Dec();
void Operator();


int Priority(char ope)
{
	//Priority map for each operator
	char order[6][2] = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
	
	for (int i = 0; i < 6; i++)
	{
		if (ope == order[i][0]) { return order[i][1]; }
	}
	
	return -1;
}

bool HandleBracket()
{
	// Found complete set of brackets; Transfer operations between them from stack to list.
	while (ElemStack.size() && ElemStack.back().Value != '(')
	{
		ElemList.push_back(ElemStack.back());
		ElemStack.pop_back();
	}
	if (ElemStack.back().Value == '(') { ElemStack.pop_back(); } //Clean up remaining open Bracket
	else { return false; } //No open bracket found; Signal an error
	return true;
}

void Start()
{
	//std::cout << "Start \"" << Curr << "\" \"" << Next << "\"\n";
	
	LastFunc = Start;
	
	if (Next == -1)
	{
		Func = End;
	}
	else if (Next == ' ')
	{
		Func = White;
	}
	else if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		Func = Num;
	}
	else if (Priority(Next) > 0) //If an operator is next
	{
		ElemList.push_back(Elem(1,0)); //implicitly append a zero
		Func = Operator;
	}
	else if (Next == '(') //If the next character is an open bracket
	{
		Func = Operator;
	}
	else
	{
		Func = Error;
	}
}

void End()
{
	//std::cout << "End \"" << Curr << "\" \"" << Next << "\"\n";
	
	//Go through any remaining operators in the stack
	while (ElemStack.size())
	{
		if (ElemStack.back().Value == ')') //Clean up remaining Close brackets
		{
			if (!HandleBracket()) { Func = Error; Func(); return; }
		}
		else if (ElemStack.back().Value == '(') //There shouldnt be any remaining open brackets
		{
			Func = Error;
			Func();
			return;
		}
		else
		{	
			//Append the operators from the stack onto the list
			ElemList.push_back(ElemStack.back());
			ElemStack.pop_back();		
		}
	}
}

void Error()
{
	std::cout << "Parse Error \"" << Curr << "\" \"" << Next << "\"\n";
	
	ElemStack.clear();
	ElemList.clear();
}

void White()
{
	//std::cout << "White \"" << Curr << "\" \"" << Next << "\"\n";
	
	if (Next == -1)
	{
		Func = End;
	}
	else if (Next == ' ')
	{
		Func = White;
	}
	else if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		if (LastFunc == Num || LastFunc == Dec) { Func = Error; } //Error; number following number
		else { Func = Num; } 
	}
	else if (Priority(Next) >= 0)
	{
		Func = Operator;
	}
	else
	{
		Func = Error;
	}
}

void Num()
{
	//std::cout << "Num \"" << Curr << "\" \"" << Next << "\"\n";
	
	if (LastFunc == Num) { Acc*=10; }
	else { Acc = 0;}
	Acc += Curr - '0';
	
	LastFunc = Num;
	
	if (Next == -1)
	{
		ElemList.push_back(Elem(1, Acc));
		Func = End;
	}
	else if (Next == ' ')
	{
		ElemList.push_back(Elem(1, Acc));
		Func = White;
	}
	else if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		Func = Num;
	}
	else if (Next == '.')
	{
		Func = Dot;
	}
	else if (Priority(Next) >= 0)
	{
		ElemList.push_back(Elem(1, Acc));
		Func = Operator;
	}
	else
	{
		Func = Error;
	}
}

void Dot()
{
	if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		Func = Dec;
	}
	else
	{
		Func = Error;
	}
}

void Dec()
{
	//std::cout << "Dec \"" << Curr << "\" \"" << Next << "\"\n";
	if (LastFunc == Num) { DecPlace = 0; }
	if (LastFunc == Dec) { Func = Error; return; }
	DecPlace++;
	Acc += (double)(Curr - '0') / pow(10.0, (double)DecPlace);
	
	LastFunc = Dec;
	
	if (Next == -1)
	{
		ElemList.push_back(Elem(1, Acc));
		Func = End;
	}
	else if (Next == ' ')
	{
		ElemList.push_back(Elem(1, Acc));
		Func = White;
	}
	else if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		Func = Num;
	}
	else if (Priority(Next) >= 0)
	{
		ElemList.push_back(Elem(1, Acc));
		Func = Operator;
	}
	else
	{
		Func = Error;
	}
}

void Operator()
{
	//std::cout << "Add \"" << Curr << "\" \"" << Next << "\"\n";
	
	
	if (Curr == '(')
	{
		ElemStack.push_back(Elem(2,'('));
	}
	else if (Curr == ')')
	{
		if (!HandleBracket()) { Func = Error; return; }
	}
	else if (LastFunc != Operator)
	{
		while (ElemStack.size() && Priority((char)ElemStack.back().Value) >= Priority(Curr)) //If stack has greater or equal to priority than current
		{
			//Add stack to list
			ElemList.push_back(ElemStack.back());
			ElemStack.pop_back();
		}
		
		ElemStack.push_back(Elem(2,Curr));
	}
	else
	{
		Func = Error; return;
	}
	
	LastFunc = Operator;
	
	if (Next == -1)
	{
		Func = End;
	}
	else if (Next == ' ')
	{
		Func = White;
	}
	else if (Next - '0' >= 0 && Next - '0' <= 9)
	{
		Func = Num;
	}
	else if (Priority(Next) == 0 || (Priority(Next) > 0 && Curr == ')')) //Allow an open bracket or a non open bracket operator to follow closed bracket
	{
		Func = Operator;
	}
	else if ((Next == '+' || Next == '-') && Curr == '(') //Allow Add or Sub to follow an open bracket
	{
		ElemList.push_back(Elem(1,0)); // Append implicit 0
		Func = Operator;
	}
	else
	{
		Func = Error;
	}
}


void Parse(std::string line)
{
	String = line;
	Func = Start;
	Index = -1;
	ElemStack.clear();
	ElemList.clear();
	
	while(Func != End && Func != Error)
	{
		Curr = (Index >= 0 ? String[Index] : -1);
		Next = (Index < (int)String.length() - 1 ? String[Index+1] : -1);
		
		Func();
		
		Index++;
	}
	Func();
}



#include "Parse.h"

void (* Func)();
void (* LastFunc)();

std::vector<Elem> ElemStack;
std::string String;
long Index = 0;
char Curr = 0;
char Next = 0;
int Acc;

void Start();
void End();
void Error();
void White();
void Num();
void Operator();


int Priority(char ope)
{
	char order[5][2] = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2} };
	
	for (int i = 0; i < 5; i++)
	{
		if (ope == order[i][0]) { return order[i][1]; }
	}
	
	return -1;
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
	else if (Priority(Next) > 0)
	{
		ElemList.push_back(Elem(1,0));
		Func = Operator;
	}
	else if (Priority(Next) == 0)
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
	///std::cout << "End \"" << Curr << "\" \"" << Next << "\"\n";
	
	while (ElemStack.size())
	{
		if (Curr == ')')
		{
			while (ElemStack.size() && ElemStack.back().Value != '(')
			{
				ElemList.push_back(ElemStack.back());
				ElemStack.pop_back();
			}
			if (ElemStack.back().Value == '(') { ElemStack.pop_back(); }
		}
		else
		{	
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
		Func = Num;
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
	
	if (LastFunc == Num)
	{
		return;
	}
	
	ElemList.push_back(Elem(1, Curr-'0'));
	
	LastFunc = Num;
	
	if (Next == -1)
	{
		Func = End;
	}
	else if (Next == ' ')
	{
		Func = White;
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

void Operator()
{
	//std::cout << "Add \"" << Curr << "\" \"" << Next << "\"\n";
	
	
	if (Curr == '(')
	{
		ElemStack.push_back(Elem(2,'('));
	}
	else if (Curr == ')')
	{
		while (ElemStack.size() && ElemStack.back().Value != '(')
		{
			ElemList.push_back(ElemStack.back());
			ElemStack.pop_back();
		}
		if (ElemStack.back().Value == '(') { ElemStack.pop_back(); }
	}
	else
	{
		while (ElemStack.size() && Priority((char)ElemStack.back().Value) >= Priority(Curr)) //If stack has greater or equal to priority than current
		{
			//Add stack to list
			ElemList.push_back(ElemStack.back());
			ElemStack.pop_back();
		}
		
		ElemStack.push_back(Elem(2,Curr));
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
	else if (Priority(Next) == 0)
	{
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


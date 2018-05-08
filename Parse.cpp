
#include "Parse.h"

void (* Func)();
void (* LastFunc)();

std::vector<Elem> ElemStack;
std::string String;
long Index = 0;
char Curr = 0;
char Next = 0;
int Acc;

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
	else if (Next == '+')
	{
		ElemList.push_back(Elem(1,0));
		Func = Add;
	}
	else if (Next == '-')
	{
		ElemList.push_back(Elem(1,0));
		Func = Sub;
	}
	else
	{
		Func = Error;
	}
}

void End()
{
	///std::cout << "End \"" << Curr << "\" \"" << Next << "\"\n";
	
	if (ElemStack.size())
	{
		Error();
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
	else if (Next == '+')
	{
		Func = Add;
	}
	else if (Next == '-')
	{
		Func = Sub;
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
	
	if (ElemStack.size())
	{
		ElemList.push_back(ElemStack.back());
		ElemStack.pop_back();
	}
	
	LastFunc = Num;
	
	if (Next == -1)
	{
		Func = End;
	}
	else if (Next == ' ')
	{
		Func = White;
	}
	else if (Next == '+')
	{
		Func = Add;
	}
	else if (Next == '-')
	{
		Func = Sub;
	}
	else
	{
		Func = Error;
	}
}

void Add()
{
	//std::cout << "Add \"" << Curr << "\" \"" << Next << "\"\n";
	
	ElemStack.push_back(Elem(2,ADD));
	
	LastFunc = Add;
	
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
	else
	{
		Func = Error;
	}
}

void Sub()
{
	//std::cout << "Sub \"" << Curr << "\" \"" << Next << "\"\n";
	
	ElemStack.push_back(Elem(2,SUB));
	
	LastFunc = Sub;
	
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


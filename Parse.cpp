
#include "Parse.h"

void (* Func)();
void (* LastFunc)();

double Tot;
double Acc;

std::string String;
u64 Index = 0;
char Curr = 0;
char Next = 0;

void Start()
{
	std::cout << "Start::" << Curr << "\n";
	
	Tot = 0;
	Acc = 0;
	LastFunc = Start;
	
	if (Next = -1)
	{
		Func = End;
	}
	else if (Next = ' ')
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

void End()
{
	std::cout << "End::" << Curr << "\n";
	
	
}

void Error()
{
	std::cout << "Error::" << Curr << "\n";
}

void White()
{
	std::cout << "White::" << Curr << "\n";
	
	if (Next = -1)
	{
		Func = End;
	}
	else if (Next = ' ')
	{
		Func = White;
	}
}

void Num()
{
	std::cout << "Num::" << Curr << "\n";
	
	if (Next = -1)
	{
		Func = End;
	}
	else if (Next = ' ')
	{
		Func = White;
	}
}

void Add()
{
	std::cout << "Add::" << Curr << "\n";
	
	if (Next = -1)
	{
		Func = End;
	}
	else if (Next = ' ')
	{
		Func = White;
	}
}

void Sub()
{
	std::cout << "Sub::" << Curr << "\n";
	
	if (Next = -1)
	{
		Func = End;
	}
	else if (Next = ' ')
	{
		Func = White;
	}
}


void Interpret(std::string line)
{
	String = line;
	Func = Start;
	Index = -1;
	
	while(Func != End && Func != Error)
	{
		Curr = (Index >= 0 ? String[Index] : -1);
		Next = (Index < String.length() - 1 ? String[Index+1] : -1);
	
	
		Func();
	}
	Func();
}


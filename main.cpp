
#include <iostream>
#include <string>

void Start();
void End();
void Add();
void Sub();

void (* Func)();
double Value;

void Start()
{
	std::cout << "Start\n";
	Func = Add;
}

void End()
{
	std::cout << "End\n";
}

void Add()
{
	std::cout << "Add\n";
	Func = Sub;
}

void Sub()
{
	std::cout << "Sub\n";
	Func = End;
}


void Interpret(std::string line)
{
	Func = Start;
	while(Func != End)
	{
		Func();
	}
	Func();
}

int main()
{	
	bool run = true;
	std::string line;
	
	Func = Start;
	
	while (run)
	{		
		std::getline(std::cin, line);
		
		if (line == "end" || line == "exit")
		{
			run = false;
		}
		else
		{
			Interpret(line);
		}
		
	}
	
	
	
	return 0;
}

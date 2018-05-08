
#include "Parse.h"


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

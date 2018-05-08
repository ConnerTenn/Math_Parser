
#include "Parse.h"
#include "ReversePolish.h"


int main()
{	
	bool run = true;
	std::string line;
	
	while (run)
	{		
		std::getline(std::cin, line);
		
		if (line == "end" || line == "exit")
		{
			run = false;
		}
		else
		{
			Parse(line);
			std::cout << "Result:" << Evaluate() << "\n";
		}
		
	}
	
	//std::cout << "\n";
	
	//ElemList = { Elem(1, 4), Elem(1, 7), Elem(2, ADD), Elem(1, 2), Elem(2, SUB) };
	
	
	
	
	return 0;
}

/*

2 * 4 - 3


STACK:


OUT:
2 
 

*/

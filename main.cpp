
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
			
			std::cout << "Reverse Polish Eqn: "; for (int i = 0; i < (int)ElemList.size(); i++) { if (ElemList[i].Type == 1) { std::cout << ElemList[i].Value << " "; } else { std::cout << (char)ElemList[i].Value << " "; } } std::cout << "\n";
			
			std::cout << "Result:" << Evaluate() << "\n\n";
		}
		
	}
	
	//std::cout << "\n";
	
	//ElemList = { Elem(1, 4), Elem(1, 7), Elem(2, ADD), Elem(1, 2), Elem(2, SUB) };
	
	
	
	
	return 0;
}

/*

1 * (2 + 3)


STACK:
* O + 

OUT:
1 2
 

*/

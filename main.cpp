
//#include "Parse.h"
//#include "ReversePolish.h"
#include "Math.h"

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
			//std::cout << "Parsing:" << line << "\n";
			int report, errorPos;
			double result =  Calc((char *)line.c_str(), &report, &errorPos);
			if (report) 
			{ 
				std::cout << "\033[1;31m";
				std::cout << "Error: " << report << "\n"; 
				if (errorPos >= 0)
				{
					std::cout << line << "\n";
					std::cout << std::string(errorPos, ' ') << "^\n";
				}
				std::cout << "\033[0m";
			}
			else { std::cout << "=" << result << "\n"; }
			std::cout << "\n";
			
			//Parse(line);
			
			//std::cout << "Reverse Polish Eqn: "; for (int i = 0; i < (int)ElemList.size(); i++) { if (ElemList[i].Type == 1) { std::cout << ElemList[i].Value << " "; } else { std::cout << (char)ElemList[i].Value << " "; } } std::cout << "\n";
			
			//std::cout << "Result:" << Evaluate() << "\n\n";
		}
		
	}
	
	//std::cout << "\n";
	
	//ElemList = { Elem(1, 4), Elem(1, 7), Elem(2, ADD), Elem(1, 2), Elem(2, SUB) };
	
	
	
	
	return 0;
}

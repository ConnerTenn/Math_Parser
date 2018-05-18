
#if VERSION==1
#include "Parse.h"
#include "ReversePolish.h"
#elif VERSION==2
#include "Math.h"
#endif

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
#if VERSION==1
			Parse(line);
			
			std::cout << "Reverse Polish Eqn: "; for (int i = 0; i < (int)ElemList.size(); i++) { if (ElemList[i].Type == 1) { std::cout << ElemList[i].Value << " "; } else { std::cout << (char)ElemList[i].Value << " "; } } std::cout << "\n";
			
			std::cout << "Result:" << Evaluate() << "\n\n";
#elif VERSION==2
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
#endif
		}
		
	}
	
	
	return 0;
}

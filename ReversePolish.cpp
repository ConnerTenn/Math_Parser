
#include "ReversePolish.h"

std::vector<Elem> ElemList;

Elem::Elem(int type, double value) : Type(type), Value(value) {}

double Evaluate()
{
	char ope;
	double num1, num2;
	
	int i = 0;
	while (ElemList.size() > 1)
	{
		if (ElemList[i].Type == 2)
		{
			ope = ElemList[i].Value;
			if (ElemList.size()) { ElemList.erase(ElemList.begin()+i); i--; } else { std::cout << "Eval Error\n"; return 0; }
			
			num2 = ElemList[i].Value;
			if (ElemList.size()) { ElemList.erase(ElemList.begin()+i); i--; } else { std::cout << "Eval Error\n"; return 0; }
			num1 = ElemList[i].Value;
			
			if (!ElemList.size()) { std::cout << "Eval Error\n"; return 0; }
			
			if (ope == '+') { ElemList[i].Value = num1 + num2; }
			if (ope == '-') { ElemList[i].Value = num1 - num2; }
			if (ope == '*') { ElemList[i].Value = num1 * num2; }
			if (ope == '/') { ElemList[i].Value = num1 / num2; }
		}
		
		i++;
		
		if (i > (int)ElemList.size()) { std::cout << "Eval Error\n"; return 0; }
	}
	
	return (ElemList.size() ? ElemList[0].Value : 0);
}


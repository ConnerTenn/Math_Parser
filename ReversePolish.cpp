
#include "ReversePolish.h"

std::vector<Elem> ElemList;

Elem::Elem(int type, int value) : Type(type), Value(value) {}

int Evaluate()
{
	int ope;
	int num1, num2;
	
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
			
			if (ope == ADD) { ElemList[i].Value = num1 + num2; }
			if (ope == SUB) { ElemList[i].Value = num1 - num2; }
		}
		
		i++;
		
		if (i > ElemList.size()) { std::cout << "Eval Error\n"; return 0; }
	}
	
	return ElemList[0].Value;
}


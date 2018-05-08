
#include "ReversePolish.h"

std::vector<Elem> ElemList;

Elem::Elem(int type, double value) : Type(type), Value(value) {}

double Evaluate()
{
	int ope;
	double num1, num2;
	
	int i = 0;
	while (ElemList.size() > 1)
	{
		if (ElemList[i].Type == 2)
		{
			ope = ElemList[i].Value;
			ElemList.erase(ElemList.begin()+i); i--;
			
			num2 = ElemList[i].Value;
			ElemList.erase(ElemList.begin()+i); i--;
			num1 = ElemList[i].Value;
			
			if (ope == ADD) { ElemList[i].Value = num1 + num2; }
			if (ope == SUB) { ElemList[i].Value = num1 - num2; }
		}
		
		i++;
	}
	
	return ElemList[0].Value;
}


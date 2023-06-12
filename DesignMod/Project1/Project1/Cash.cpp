#include"Cash.h"

int Cash::scan_self()
{
	int sum = 0;
	char t;
	do {
		int a = 0;
		std::cout << "ÇëÊäÈëµ¥¼Û" << std::endl;
		std::cin >> a;
		int b = 0;
		std::cout << "ÇëÊäÈëÊýÁ¿" << std::endl;
		std::cin >> b;
		sum += a * b;
		std::cout << "continue 'y' or 'no'" << std::endl;
		std::cin >> t;

	} while (t == 'y');

	return sum;
	
}

void Cash::GetResoult(int rotal)
{
	std::cout << _type->GetResult(rotal);
}


void CashReturn::GetParam()
{
	std::cout << "ÇëÊäÈëÂú" << std::endl;
	std::cin >> first;
	std::cout << "ÇëÊäÈë¼õ" << std::endl;
	std::cin >> second;
}

void CashDisCount::GetParam()
{
	std::cout << "ÇëÊäÈëÕÛ¿Û" << std::endl;
	std::cin >> first;
}

int CashReturn::GetResult(int rotal)
{
	return rotal - rotal / first * second;
}

int CashDisCount::GetResult(int rotal)
{
	return rotal * first / 10;
}
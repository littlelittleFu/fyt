#include"Cash.h"

int Cash::scan_self()
{
	int sum = 0;
	char t;
	do {
		int a = 0;
		std::cout << "�����뵥��" << std::endl;
		std::cin >> a;
		int b = 0;
		std::cout << "����������" << std::endl;
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
	std::cout << "��������" << std::endl;
	std::cin >> first;
	std::cout << "�������" << std::endl;
	std::cin >> second;
}

void CashDisCount::GetParam()
{
	std::cout << "�������ۿ�" << std::endl;
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
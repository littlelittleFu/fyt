#include <iostream>

//�ݹ�
int Fib(int n) {
	return n < 2 ? 1 : (Fib(n - 1) + Fib(n - 2));
}

//����
int Fib_Seq(int n) {
	int fib[1000];
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i <= n; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib[n];
}

//������ ������˼��
long long int Quick_Power(int base, int power) {
	long long int result = 1;
	while(power > 0) { // ָ������0
		if (power & 1)result *= base;  // ָ���ݲ�Ϊ0���۳���ȥ
		base *= base;                  // �����һ���baseֵ
		power >>= 1;                   // ��������
	}
	return result;
}

// ָ���۰�
long long int Quick_Power_Binary(int base, int power) {
	long long int result = 1;
	while (power > 0) {
		//if (power % 2 == 1) 
		if (power & 1) 
			result *= base;
		//power /= 2;
		power >>= 1;
		base *= base;
	}
	return result;
}

// ���ÿ����ݵ��㷨 ��base��ɾ��� ��Ϊ��������ݼ���쳲���������
const int Mod = 10000;

struct matrix {
	int m[2][2];
}ans,base;

// ����˷�
matrix Multi(matrix a, matrix b) {
	matrix tmp;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			tmp.m[i][j] = 0;
			for (int k = 0; k < 2; ++k) {
				tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]) % Mod;
			}
		}
	}
	return tmp;
}

int Fast_Mod(int n) {
	base.m[0][0] = base.m[0][1] = base.m[1][0] = 1;
	base.m[1][1] = 0;
	ans.m[0][0] = ans.m[1][1] = 1;
	ans.m[0][1] = ans.m[1][0] = 0;
	while (n) {
		if (n & 1) ans = Multi(ans, base);
		base = Multi(base, base);
		n >>= 1;
	}
	return ans.m[0][1];
}


int main()
{
	//eg
	int n = 100;
	std::cout << Fast_Mod(n) << std::endl;
	return 0;
}
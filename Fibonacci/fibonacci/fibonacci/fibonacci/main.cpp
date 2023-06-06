#include <iostream>

//递归
int Fib(int n) {
	return n < 2 ? 1 : (Fib(n - 1) + Fib(n - 2));
}

//递推
int Fib_Seq(int n) {
	int fib[1000];
	fib[0] = 1; fib[1] = 1;
	for (int i = 2; i <= n; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib[n];
}

//快速幂 二进制思想
long long int Quick_Power(int base, int power) {
	long long int result = 1;
	while(power > 0) { // 指数大于0
		if (power & 1)result *= base;  // 指数幂不为0的累乘上去
		base *= base;                  // 获得下一项的base值
		power >>= 1;                   // 幂数右移
	}
	return result;
}

// 指数折半
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

// 利用快速幂的算法 将base变成矩阵 则为矩阵快速幂计算斐波那契数列
//const int Mod = 10000;

struct matrix {
	int m[2][2];
}ans,base;

// 矩阵乘法
matrix Multi(matrix a, matrix b) {
	matrix tmp;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			tmp.m[i][j] = 0;
			for (int k = 0; k < 2; ++k) {
				//tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]) % Mod;
				tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]);

			}
		}
	}
	return tmp;
}

int Fast_Mod(int n) {
	if (n < 0)return -1;
	base.m[0][0] = base.m[0][1] = base.m[1][0] = 1;
	base.m[1][1] = 0;
	ans.m[0][0] = ans.m[1][1] = 1;
	ans.m[0][1] = ans.m[1][0] = 1;
	while (n) {
		if (n & 1) ans = Multi(ans, base);
		base = Multi(base, base);
		n >>= 1;
	}
	return ans.m[0][1];
}

void GetFibonacciArray(int* pData, int destIdx)
{
	if (nullptr == pData || destIdx < 2)return;
	pData[0] = 1; pData[1] = 1;
	for (int idx = 2; idx < destIdx; ++idx)pData[idx] = pData[idx - 1] + pData[idx - 2];
}

int FibonacciSearch(int* pData, int size, int value)
{
	if (nullptr == pData || size < 1)return -1;

	// 获取fib数组 10000长度以内
	const int FIBONACCI_MAX_IDX = 50;
	int* pFibData = new int[FIBONACCI_MAX_IDX];
	GetFibonacciArray(pFibData, FIBONACCI_MAX_IDX);

	// 获取idx
	int destIdx = 0;
	while (pFibData[destIdx] - 1 < size)++destIdx;

	// 构造临时数组
	int* pTempData = new int[pFibData[destIdx] - 1];

	// 填充数据
	memcpy(pTempData, pData, size * sizeof(int));
	for (int idx = size; idx < pFibData[destIdx] - 1; ++idx)pTempData[idx] = pData[size - 1];
	
	int left = 0, right = size - 1;
	while (left <= right)
	{
		int middle = left + pFibData[destIdx - 1] - 1;
		if (value == pTempData[middle]) // 找到
		{
			if (middle < size) return middle; // 元素位于原本空间中，直接返回下标
			else return size - 1; // 元素位于扩充空间，因为扩充空间都是用pData[size - 1]进行的赋值，所以返回下标size - 1
		}
		else if (value > pTempData[middle]) // 右区间查找
		{
			left = middle + 1;
			destIdx = destIdx - 2;
		}
		else // 左区间查找
		{
			right = middle - 1;
			destIdx = destIdx - 1;
		}
	}

	delete[] pTempData;
	delete[] pFibData;

	return -1;
}

int FibonacciSearchAdvance(int* pData, int size, int value) 
{
	if (nullptr == pData || size < 1)return -1;
	if (size == 1)return value == *pData ? 0 : -1;

	const int FIBONACCI_MAX_IDX = 50;
	int* pFibData = new int[FIBONACCI_MAX_IDX];
	GetFibonacciArray(pFibData, FIBONACCI_MAX_IDX);

	// 获取idx
	int fibIdx = 0;
	while (pFibData[fibIdx] - 1 < size)++fibIdx;

	int low = 0; 
	int high = size - 1;

	while (low <= high) {
		int middle = low + pFibData[fibIdx - 1] - 1;

		// 查询为middle逐渐逼近过程 high可以不变 
		if (middle > size - 1) {
			if (pData[high] == value)return high;
			if (value > pData[high]) {
				low = middle + 1;
				fibIdx -= 2;
			}
			else {
				--fibIdx;
			}
			continue;
		}

		if (pData[middle] == value) {
			if (middle < size)return middle;
			return size - 1;
		}
		else if (value > pData[middle]) {
			low = middle + 1;
			fibIdx -= 2;
		}
		else {
			high = middle - 1;
			--fibIdx;
		}
	}

	delete[] pFibData;

	return -1;
}


int main()
{
	int n = 44;
	std::cout << Fast_Mod(20) << std::endl;
	std::cout << Fib_Seq(2) << std::endl;
	int arr[10000] = { 0 };
	for (int i = 1; i <= 10000; ++i) {
		arr[i-1] = i + 100;
		auto idx = FibonacciSearch(arr, i, 1189);
		auto _idx = FibonacciSearchAdvance(arr, i, 1189);
		std::cout << idx << " " << _idx << std::endl;
	}
	return 0;
}
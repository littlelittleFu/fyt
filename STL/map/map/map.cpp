#include<iostream>
#include<map>
#include<functional>
#include<vector>
#include<list>
//#include<hash_set>

#include"self_algorithm.h"
#define A 0.001
// map的第三个参数 仿函数
//template<class _Ty = void>
//struct myless {
//	bool operator()(const _Ty& lh, const _Ty& rh )const {
//		return lh > rh;
//	}
//
//};

//template<typename C>
//bool lastGreaterThanFirst(const C& container) {
//	if (container.empty())return false;
//	typename C::const_iterator begin(container.begin());
//	typename C::const_iterator end(container.end());
//	return *--end() > *begin;
//
//}

// 编译器可以自动推导类型
//template<typename T>
//int func(const T a) {
//	return a + 1;
//}

int main() {
	myclass a;
	a.test();
	//std::map<int, int, myless<int>> m;
	//m.emplace(1, 10);
	//m.emplace(10, 100);
	//m.emplace(2, 5);
	//for (auto it = m.begin(); it != m.end();) {
	//	m.erase(it++);
	//}
	//std::list<int >l;
	//l.push_back(2);
	//l.push_back(1);

	//std::vector<int>v;
	//v.push_back(5);
	//v.push_back(3);
	//v.push_back(3);

	//std::hash_set<int> a;

	//auto ret = v.lastGreaterThanFirst(v);
	//int c = 10;
	//auto d = c * A;
	//auto e = typeid(d).name();

	return 0;
}
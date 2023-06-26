#include<vector>
#include<map>
#include <list>
#include<iostream>
#include <string>
#include<algorithm>
struct mystruct
{
	int id = 0;
	std::string name;
	mystruct(int _id, std::string _name) :id(_id), name(_name) {};
};

using MY_STRUCT_SP = std::shared_ptr<mystruct>;

template<typename T>
class myless
{
public:
	myless() = default;
	~myless() = default;
	bool operator()(const T&lhs,const T&rhs)const
	{
		return std::strcmp(lhs->name.c_str(), rhs->name.c_str()) < 0;
	}
};

template<typename T>
class myless1
{
public:
	myless1() = default;
	~myless1() = default;
	bool operator()(const T& lhs, const T& rhs)const
	{
		return lhs->id < rhs->id;
	}
};

class myclass
{
public:
	void test()
	{
		mystruct a[10] = { {1,"zhang" },{2,"li"} ,{4,"wang"},{3,"zheng"},{6,"shao"},
						{11,"qi"},{7,"zhao"},{8,"liu"},{8,"fu"},{10,"shi"} };
		for (int i = 0; i < 10; ++i) {
			v.push_back(std::make_shared<mystruct>(a[i]));
			l.push_back(std::make_shared<mystruct>(a[i]));
			m.emplace(make_pair(std::make_shared<mystruct>(a[i]), i));

		}

		myprint();
		myprint(1.1);
		myprint(1);

		sort(v.begin(), v.end(), myless1<MY_STRUCT_SP>());
		l.sort(myless1<MY_STRUCT_SP>());
		myprint();
		myprint(1.1);

		auto s = std::make_shared<mystruct>(8,"");
		// µ»º€≈–∂œ !(x < y) && !(y < x)
		auto ret = std::binary_search(v.begin(), v.end(), s, myless1<MY_STRUCT_SP>());

		auto it1 = std::lower_bound(v.begin(), v.end(), s, myless1<MY_STRUCT_SP>());
		auto it2 = std::upper_bound(v.begin(), v.end(), s, myless1<MY_STRUCT_SP>());
		std::cout << std::count(v.begin(), v.end(), s) << std::endl;
		auto ret1 = std::equal_range(v.begin(), v.end(), s, myless1<MY_STRUCT_SP>());
		if (ret1.first == ret1.second) {
			std::cout << "no equal val" << std::endl;
		} {
			for (auto it = ret1.first; it != ret1.second; ++it) {
				std::cout << it->get()->id << " " << it->get()->name << std::endl;
			}
		}

		if (it2 != v.end()) {
			std::cout << it2->get()->id << " " << it2->get()->name << std::endl;
		}
		if (it1 != v.end()) {
			std::cout << it1->get()->id << " " << it1->get()->name << std::endl;
		}

		std::cout << ret << std::endl;

		auto it = std::find_if(v.begin(), v.end(),  [](const MY_STRUCT_SP data) {
			if (data->id == 5)return true;
			return false;
			});

		//std::cout << it->get()->id << std::endl;
	}

	void myprint() {
		std::cout << "vector ************" << std::endl;

		for (auto i : v) {
			std::cout << i->id << " " << i->name << std::endl;
		}
	}
	void myprint(double) {
		std::cout << "list ************" << std::endl;
		for (auto i : l) {
			std::cout << i->id << " " << i->name << std::endl;
		}
	}
	void myprint(int) {
		std::cout << "map ************" << std::endl;
		for (auto i : m) {
			std::cout << i.first->id << " " << i.first->name <<" " << i.second << std::endl;

		}
	}




private:
	std::vector<MY_STRUCT_SP>v;
	std::list<MY_STRUCT_SP>l;
	std::map < MY_STRUCT_SP, int, myless<MY_STRUCT_SP>> m;
};
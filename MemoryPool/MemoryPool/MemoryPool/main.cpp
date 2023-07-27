#include<iostream>
#include"MemoryPool.h"
#include<string>
struct childData {
	int num;
};
struct data {

	int id;
	int pid;
	char name[1000];
	//std::string name;
	childData chData;
};

class clData {
public:
	clData() {
		std::cout << "gouzao" << std::endl;
	};
	void init(int id,int pid,const char*name,childData data) {
		mydata.id = id;
		mydata.pid = pid;
		//mydata.name = name;
		strcpy_s(mydata.name, name);
		mydata.chData = data;
	}
	void Print() {
		std::cout << mydata.id << "   " << mydata.pid << "   " << mydata.name << "   " << mydata.chData.num << std::endl;
	};
private:
	data mydata;
};

int main() {

	Memory::Declare::MemoryPool MP;
	auto a = sizeof(clData);
	MP.CreateMemoryBlock();
	auto addr = MP.Allocate<clData>(sizeof(clData));
	//addr = new clData;
	const char* name = "ss";
	childData d;
	d.num = 10;
	addr->init(1, 1, name, d);
	addr->Print();

	MP.StartScope();
	MP.DumpPoolData();
	MP.EndScope();

	return  0;
}
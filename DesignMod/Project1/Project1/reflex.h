#pragma once
#include<map>
#include<iostream>
#include<string.h>

// 定义指向回调函数的函数指针
typedef void* (*PTRCreateObj)(void);

#define REGISTER(className)           \
static className* CreateObj##className(){    \
	return new className;             \
}                                     \
static RegisterAction g_createRegister##className(       \
	#className,(PTRCreateObj)CreateObj##className \
)



class Factory
{
public:
	void* GetClassByName(std::string className);
	void RegisterClass(std::string className, PTRCreateObj method);
	virtual void m_print() {};
	
	static Factory* instance;
	static Factory* GetInstance();
	
public:
	std::map<std::string, PTRCreateObj>m_classMap;
};

class RegisterAction
{
public:
	RegisterAction(std::string className, PTRCreateObj method) {
		Factory::GetInstance()->RegisterClass(className, method);
	}
};

class A :public Factory
{
public:
	void m_print() { std::cout << "a" << std::endl; }
};
REGISTER(A);
//static A* CreateObjA() { return new A; }
//static RegisterAction g_createRegisterA("A", (PTRCreateObj)CreateObjA);

class B :public Factory
{
public:
	void m_print() { std::cout << "b" << std::endl; }
};
REGISTER(B);




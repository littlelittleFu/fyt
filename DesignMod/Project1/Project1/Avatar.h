#pragma once
#include<string.h>
#include<iostream>
// 装饰模式

class Person
{
public:
	Person() {};
	~Person() {};


	//void WearShose() { std::cout << "shose" << std::endl; }
	//void WearSuit() { std::cout << "Suit" << std::endl; }
	//void WearTie() { std::cout << "Tie" << std::endl; }
	//void WearShose1() { std::cout << "Shose1" << std::endl; }

	virtual void Show() { std::cout << "the person is:" << name << "   的装扮为" << std::endl; };

protected:
	std::string name;
};

class YellowPerson :public Person
{
public:
	YellowPerson(const char* name):name(name) {};
	void Show()override;
private:
	std::string name;
};

class WhitePerson :public Person
{
public:
	WhitePerson(const char* name):name(name){};
	void Show()override;
private:
	std::string name;
};

class Decorator :public Person
{
public:
	virtual void Show()override;
	virtual void SetPerson(Person* person) { this->person = person; };

protected:
	Person *person;
};

class ConcreteDecoratorA :public Decorator
{
public:
	virtual void Show()override;
	void WearTS() { std::cout << "T-shirt" << std::endl; }

};

class ConcreteDecoratorB :public Decorator
{
public:
	virtual void Show()override;
	void WearTrouser() { std::cout << "Trouser" << std::endl; }

};
#pragma once

#include<iostream>
#include<string.h>
#include<list>

class Component
{
public:
	Component(std::string& name) :name(name) {};

	virtual void Add(Component* c) {};
	virtual void Remove(Component* c) {};
	virtual void Display(int depth) {};

	bool operator== (const Component& a) {
		return a.name == this->name;
	}
	
protected:
	std::string name;
};

class Leaf :public Component
{
public:
	Leaf(std::string name) :Component(name) {};

	void Add(Component* c);
	void Remove(Component* c);
	void Display(int depth);
private:

};

class Composite :public Component
{
public:
	Composite(std::string name) :Component(name) {};
	void Add(Component* c);
	void Remove(Component* c);
	void Display(int depth);
private:
	std::list<Component*>child;
};
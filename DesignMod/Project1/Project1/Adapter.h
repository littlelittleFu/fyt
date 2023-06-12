#pragma once
#include<iostream>
#include<string.h>

class Target
{
public:
	virtual void request() { std::cout << "normal" << std::endl; };
};

class Adapteer
{
public:
	void SpecificRequest() { std::cout << "specificial" << std::endl; };
};

class Adapter :Target
{
public:
	void request() {
		a.SpecificRequest();
	};
private:
	Adapteer a;
};
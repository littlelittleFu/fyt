#pragma once
#include<iostream>
#include<string.h>

class PersonBuilder
{
public:
	virtual void BuildHead() {};
	virtual void BuildBody() {};
	virtual void BuildArmL() {};
	virtual void BuildArmR() {};
	virtual void BuildLegL() {};
	virtual void BuildLegR() {};

	virtual void Show() {};
};

class ThinPerson :public PersonBuilder
{
public:
	void BuildHead() override;
    void BuildBody() override;
	void BuildArmL() override;
	void BuildArmR() override;
	void BuildLegL() override;
	void BuildLegR() override;

	void Show()override
	{
		std::cout << "构建成功" << std::endl;
	};
};

class PerDirector
{
public:
	void ConcreteDirector(PersonBuilder *bp) { this->m_pb = bp; };
	PersonBuilder* CreatePerson();

private:
	PersonBuilder *m_pb;
};
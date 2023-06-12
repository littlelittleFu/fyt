#pragma once
#include<iostream>
#include<string.h>

class Resume
{
public:
	Resume(const std::string& name) :name(name) {};
	Resume(const Resume& a) {
		std::cout << "..." << std::endl;
		this->name = a.name;
		this->age = a.age;
		this->sex = a.sex;
		this->timeArea = a.timeArea;
		this->company = a.company;
	}
	void SetPersonInfo(std::string sex, std::string age);
	void SetWorkExprience(std::string timeArea, std::string company);
	void Show();
private:
	std::string name;
	std::string sex;
	std::string age;
	std::string timeArea;
	std::string company;
};
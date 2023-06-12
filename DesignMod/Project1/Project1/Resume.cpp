#include"Resume.h"

void Resume::SetPersonInfo(std::string sex, std::string age)
{
	this->sex = sex;
	this->age = age;
}
void Resume::SetWorkExprience(std::string timeArea, std::string company)
{
	this->timeArea = timeArea;
	this->company = company;
}
void Resume::Show()
{
	std::cout << "姓名:" << name << std::endl
		<< "性别:" << sex << std::endl
		<< "年龄:" << age << std::endl
		<< "工作年限:" << timeArea << std::endl
		<< "公司:" << company << std::endl;
}
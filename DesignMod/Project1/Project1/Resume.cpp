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
	std::cout << "����:" << name << std::endl
		<< "�Ա�:" << sex << std::endl
		<< "����:" << age << std::endl
		<< "��������:" << timeArea << std::endl
		<< "��˾:" << company << std::endl;
}
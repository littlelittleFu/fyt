#include"Avatar.h"

void YellowPerson::Show()
{
	std::cout << "the person is:" << name << "   的装扮为" << std::endl;
	std::cout << "i am Yellow" << "my style is :" << std::endl;
}

void WhitePerson::Show()
{
	std::cout << "the person is:" << name << "   的装扮为" << std::endl;
	std::cout << "i am white" << "my style is :" << std::endl;
}

void Decorator::Show()
{
	if (this->person != nullptr)
	{
		person->Show();
	}
}

void ConcreteDecoratorA::Show()
{
	if (this->person != nullptr)
	{
		Decorator::person->Show();
		WearTS();
	}
}

void ConcreteDecoratorB::Show()
{
	if (this->person != nullptr)
	{
		Decorator::person->Show();
		WearTrouser();
	}
}
#pragma once
#include<iostream>
#include<string.h>

class Receiver
{
public:
	void Action() {
		std::cout << "execute command" << std::endl;
	};
};

class Command
{
public:
	Command(Receiver* re) :receiver(re) {};
	virtual void Execute() {};

protected:
	Receiver* receiver;
};

class ConcreteCommand :public Command
{
public:
	ConcreteCommand(Receiver* re):Command(re) {};
	void Execute()override;
};

class Invoker
{
public:
	void SetCommand(Command* co){ command = co;}
	void ExecuteCommand(){ command->Execute();}
private:
	Command *command;
	// std::vector<Command*>v_C;
};
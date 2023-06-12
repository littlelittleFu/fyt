#pragma once
#include<iostream>
#include<string.h>
class Memento
{
public:
	Memento(const std::string& sta) :state(sta) {};
	std::string GetState() { return state; }
private:
	std::string state;
};

class Originator
{
public:
	std::string GetState() { return state; }
	void SetState(std::string sta) { state = sta; }

	Memento CreateMemento() { return*( new Memento(state)); };

private:

	std::string state;
};

class Caretaker
{
public:
	Memento GetMemento() { return memento; }
	void SetMemento(Memento me) { memento = me; }


private:
	Memento memento;
};
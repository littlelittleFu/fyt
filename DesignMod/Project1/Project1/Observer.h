#pragma once
#include<iostream>
#include<string.h>
#include<list>
class StockObserver;
using StockObserverSP = std::shared_ptr<StockObserver>;
using ColleageList = std::list<StockObserverSP>;

class Secretary
{
public:
	void Attach(StockObserverSP ob);
	void Notify();
	std::string SecretatyAction(int _event);

private:
	std::string action;
	ColleageList m_colleagerList;
};

class StockObserver
{
public:
	StockObserver(const std::string& _name,Secretary* _sub ):name(_name),sub(_sub) {};
	void Update() {
		std::cout << name << " go to work!" <<std::endl;
	};

private:
	std::string name;
	Secretary* sub;
};
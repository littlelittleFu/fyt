#pragma once

#include<iostream>
#include<string.h>


class Work
{
public:
	void SetHour(int hour) { m_Hour = hour; }
	int GetHour() { return m_Hour; }

	bool IsFinished() { return m_Finished; }
	void SetFinished(bool set) { m_Finished = set; }

private:
	int m_Hour;
	bool m_Finished;


};


class Context;
class State
{
public:

	virtual void Handle(Context* context) {};
private:
};


class Context
{
public:
	Context(State* sta):state(sta) {};
	State* GetState() { return state; }
	void SetState(State* sta) { state = sta; }

	void Request()
	{
		state->Handle(this);
	}
private:
	State *state;
};


class ConcreteStateA :public State
{
public:
	virtual void Handle(Context context) {
		context.SetState(new ConcreteStateA());
	};

private:
};

class ConcreteStateB :public State
{
public:
	virtual void Handle(Context context) {
		context.SetState(new ConcreteStateB());
	};

private:
};
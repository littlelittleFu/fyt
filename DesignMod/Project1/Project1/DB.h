#pragma once
#include<iostream>
#include<string.h>
//#include<Winsock2.h>
//#pragma comment(lib,"ws2_32.lib")
//
//#include"MySql/include/mysql.h"
//#pragma comment(lib,"mysql.lib")
class User
{
public:
	void SetID(int id) { this->id = id; }
	int GetID() { return id; }

	void SetName(std::string& name) { this->name = name; }
	std::string GetName() { return name; }

private:
	int id;
	std::string name;

};

class IUser
{
	virtual void Insert(User* user) { };
	virtual User* GetUser(int id) { return nullptr; };

};

class SqlServerUser:public IUser
{
public:
	void Insert(User* user) {
		std::cout << user->GetName() << "插入了一条数据" << std::endl;
	}

	User* GetUser(int id) { 
		std::cout << "根据user id：" << id << " 获取了一条信息" << std::endl;
		return nullptr; 
	}

};

class AccessUser :public IUser
{
public:
	void Insert(User* user) {
		std::cout<<"Access*******" << user->GetName() << "插入了一条数据" << std::endl;
	}

	User* GetUser(int id) {
		std::cout <<"Access********" << "根据user id：" << id << " 获取了一条信息" << std::endl;
		return nullptr;
	}

};

class Ifactory
{
public:
	virtual IUser* CreateUser() { return nullptr; };
};

class SqlServerFactory :public Ifactory
{
public:
	IUser* CreateUser()
	{
		return new SqlServerUser();
	}
};

class AccessFactory :public Ifactory
{
public:
	IUser* CreateUser()
	{
		return new AccessUser();
	}
};
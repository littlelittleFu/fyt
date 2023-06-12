#include<iostream>
// 策略--简单工厂
class CashType
{
public:
	virtual void GetParam() {};
	virtual int GetResult(int rotal) { return 0; };
};

class CashReturn:public CashType
{
public:
	virtual void GetParam()override;
	virtual int GetResult(int rotal)override;



private:
	int first = 0;
	int second = 0;
	
};

class CashDisCount:public CashType
{
public:
	virtual void GetParam()override;
	virtual int GetResult(int rotal)override;


private:
	int first = 0;
};



class Cash
{
public:
	Cash(int type) {
		switch (type)
		{
		case 1:
			_type = new CashReturn();
			break;
		case 2:
			_type = new CashDisCount();
			break;
		default:
			std::cout << "error" << std::endl;
			break;
		}
		_type->GetParam();
	};
	~Cash() {};

public:
	int scan_self();
	void GetResoult(int rotal);


private:
	CashType* _type;
};

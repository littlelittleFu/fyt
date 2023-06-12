#include <iostream>
#include<string>
#include "Cash.h"
#include"Avatar.h"
#include"reflex.h"
#include"Resume.h"
#include"Builder.h"
#include"Observer.h"
#include "DB.h"
#include "Status.h"
#include"Composite.h"
#include<map>
#include<vector>
#include<chrono>
time_t GetTimeStamp()
{
	auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	std::time_t timestamp = tmp.count();
	return timestamp;
};

class data
{
public:
	~data() { std::cout << "xigou" << std::endl; }
	std::string name = "lisi";
	int age = 10;
};

void GetData(std::vector<std::unique_ptr<data>>&vec)
{
	auto a = std::make_unique<data>();
	auto b = std::make_unique<data>();

	vec.push_back(std::move(a));
	vec.push_back(std::move(b));
}
void print()
{
	std::vector<std::unique_ptr<data>> vec;
	GetData(vec);
	std::cout << vec[0]->age << std::endl;
}

int main()
{

	print();
	/***
	* 1、
	* 简单工厂 
	* 策略模式
	***/
	//std::cout << "选择打折模式" << std::endl;
	//int a = 0;
	//std::cin >> a;
	//Cash cash(a);
	//cash.GetResoult(cash.scan_self());

	/***
	* 2、装饰模式
	***/
	//auto person1 = new WhitePerson("peter");
	//auto person2 = new YellowPerson("小明");

	//auto A = new ConcreteDecoratorA;
	//auto B = new ConcreteDecoratorB;
	//A->SetPerson(person1);
	//B->SetPerson(A);
	//B->Show();


	//A->SetPerson(person2);
	//B->SetPerson(A);
	//B->Show();

	/***
	* 3、反射
	***/
	//Factory* ptr = (Factory*)Factory::GetInstance()->GetClassByName("A");
	//ptr->m_print();

	/***
	* 4、工厂方法
	***/

	/***
	*5、原型模式
	***/
	//深浅拷贝 拷贝构造问题 指针的话 单独写个new对象指针
	//Resume* a = new Resume("张三");
	//Resume b = *a;
	//delete(a);
	//b.Show();

	/***
	* 6、模板方法
	* 模板方法将“固定流程”移至父类 去除子类重复代码 子类中实现父类虚方法的多态
	***/
	
	/***
	* 7、外观者模式
	* 将主系统与子系统分开 建立层与层的意识 将主系统部分功能实现接口供子系统使用
	***/

	/***
	* 8、建造者模式
	* 复杂对象构建与表示分离 使得同样的构建流程可以构建不同的表示
	*/
	//auto Director = new PerDirector();
	//Director->ConcreteDirector(new ThinPerson());
	//auto thinperson = Director->CreatePerson();
	//thinperson->Show();

	/***
	* 9、观察者模式
	***/
	// 被通知者要抽象出来 通知者也要抽象出来 变成通知类通知被通知类 解耦合
	// 通知者抽象类或者接口实现 对观察者（订阅者）的引用保存在一起 
	// 发布模式可以 接任何发布者的变化 通知各个订阅者 而订阅者和发布者互不耦合
	// 订阅者也可能是不同类 调用subject开出的接口即可
	//auto tong = new Secretary();
	//StockObserverSP sp1(new StockObserver("zhangsan",tong));
	//std::cout << sp1.use_count() << std::endl;
	//StockObserverSP sp2(new StockObserver("lsii", tong));
	//tong->Attach(sp1);
	//tong->Attach(sp2);
	//sp1.~shared_ptr();
	//std::cout << sp1.use_count() << std::endl;
	//tong->SecretatyAction(1);

	/***
	* 10、抽象工厂模式
	***/

	/***
	* 11、状态模式
	***/
	// 当控制一个对象转换的条件表达式过于复杂，把状态的判断转移到不同状态
    // 的一系列类中去，可以把复杂的判断逻辑简化

	// 与策略模式基图相似 但是状态模式在不同状态下进行不同的操作
	// 策略模式 根据不同的策略执行不同的算法 但是都能归结于算法 同种东西


	/***
	* 12、适配器模式
	* 子类中已经实现相同功能的接口名不同 通过adapter继承父类 命名相同名称的
	* 接口 该子类中包含原子类 并调用原子类中功能相同的函数
	***/

	/***
	* 13、 备忘录模式 
	* 在另一个类内包含此类部分属性 通过创造类封装 备忘此类中部分属性
	***/

	/***
	* 14、组合模式
	* 适用于整体与部分相同的情况 树形结构
	***/
	//Composite root("root");
	//root.Add(new Leaf("leaf a"));
	//root.Add(new Leaf("leaf b"));

	//Composite comp("cmp X");
	//comp.Add(new Leaf("leaf Xa"));
	//comp.Add(new Leaf("leaf Xb"));

	//root.Add(&comp);

	//Composite comp1("cmp Y");
	//comp1.Add(new Leaf("leaf Ya"));
	//comp1.Add(new Leaf("leaf Yb"));

	//comp.Add(&comp1);

	//root.Display(1);
	//std::cout << "**********************" << std::endl;
	//comp.Display(1);

	/***
	* 15、桥接模式
	* 怪物 AI 宠物的模式即为桥接模式
	***/

	/***
	*16、命令模式
	* 实现队列命令的插入与删除   在无需撤销与删除命令的情况下 不需要实现命令模式
	***/

	return 0;
}
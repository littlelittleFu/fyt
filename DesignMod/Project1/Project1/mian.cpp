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
	* 1��
	* �򵥹��� 
	* ����ģʽ
	***/
	//std::cout << "ѡ�����ģʽ" << std::endl;
	//int a = 0;
	//std::cin >> a;
	//Cash cash(a);
	//cash.GetResoult(cash.scan_self());

	/***
	* 2��װ��ģʽ
	***/
	//auto person1 = new WhitePerson("peter");
	//auto person2 = new YellowPerson("С��");

	//auto A = new ConcreteDecoratorA;
	//auto B = new ConcreteDecoratorB;
	//A->SetPerson(person1);
	//B->SetPerson(A);
	//B->Show();


	//A->SetPerson(person2);
	//B->SetPerson(A);
	//B->Show();

	/***
	* 3������
	***/
	//Factory* ptr = (Factory*)Factory::GetInstance()->GetClassByName("A");
	//ptr->m_print();

	/***
	* 4����������
	***/

	/***
	*5��ԭ��ģʽ
	***/
	//��ǳ���� ������������ ָ��Ļ� ����д��new����ָ��
	//Resume* a = new Resume("����");
	//Resume b = *a;
	//delete(a);
	//b.Show();

	/***
	* 6��ģ�巽��
	* ģ�巽�������̶����̡��������� ȥ�������ظ����� ������ʵ�ָ����鷽���Ķ�̬
	***/
	
	/***
	* 7�������ģʽ
	* ����ϵͳ����ϵͳ�ֿ� ������������ʶ ����ϵͳ���ֹ���ʵ�ֽӿڹ���ϵͳʹ��
	***/

	/***
	* 8��������ģʽ
	* ���Ӷ��󹹽����ʾ���� ʹ��ͬ���Ĺ������̿��Թ�����ͬ�ı�ʾ
	*/
	//auto Director = new PerDirector();
	//Director->ConcreteDirector(new ThinPerson());
	//auto thinperson = Director->CreatePerson();
	//thinperson->Show();

	/***
	* 9���۲���ģʽ
	***/
	// ��֪ͨ��Ҫ������� ֪ͨ��ҲҪ������� ���֪ͨ��֪ͨ��֪ͨ�� �����
	// ֪ͨ�߳�������߽ӿ�ʵ�� �Թ۲��ߣ������ߣ������ñ�����һ�� 
	// ����ģʽ���� ���κη����ߵı仯 ֪ͨ���������� �������ߺͷ����߻������
	// ������Ҳ�����ǲ�ͬ�� ����subject�����Ľӿڼ���
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
	* 10�����󹤳�ģʽ
	***/

	/***
	* 11��״̬ģʽ
	***/
	// ������һ������ת�����������ʽ���ڸ��ӣ���״̬���ж�ת�Ƶ���ͬ״̬
    // ��һϵ������ȥ�����԰Ѹ��ӵ��ж��߼���

	// �����ģʽ��ͼ���� ����״̬ģʽ�ڲ�ͬ״̬�½��в�ͬ�Ĳ���
	// ����ģʽ ���ݲ�ͬ�Ĳ���ִ�в�ͬ���㷨 ���Ƕ��ܹ�����㷨 ͬ�ֶ���


	/***
	* 12��������ģʽ
	* �������Ѿ�ʵ����ͬ���ܵĽӿ�����ͬ ͨ��adapter�̳и��� ������ͬ���Ƶ�
	* �ӿ� �������а���ԭ���� ������ԭ�����й�����ͬ�ĺ���
	***/

	/***
	* 13�� ����¼ģʽ 
	* ����һ�����ڰ������ಿ������ ͨ���������װ ���������в�������
	***/

	/***
	* 14�����ģʽ
	* �����������벿����ͬ����� ���νṹ
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
	* 15���Ž�ģʽ
	* ���� AI �����ģʽ��Ϊ�Ž�ģʽ
	***/

	/***
	*16������ģʽ
	* ʵ�ֶ�������Ĳ�����ɾ��   �����賷����ɾ������������ ����Ҫʵ������ģʽ
	***/

	return 0;
}
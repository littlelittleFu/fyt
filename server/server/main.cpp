#include"CNetMgr.h"
#include"CIocp.h"
#include<list>

int main()
{
	// 1. ��ʼ���������
	CIocp::GetInstance()->init();

	// 2. ��listensocket����ɶ˿ڰ� ��Ͷ��accept���� ʣ������ɶ˿ڴ�������
	CNetMgr::GetInstance()->AddListener();



		

	return 0;
}
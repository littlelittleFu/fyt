#include"CNetMgr.h"
#include"CIocp.h"
#include<list>

int main()
{
	// 1. 初始化网络相关
	CIocp::GetInstance()->init();

	// 2. 将listensocket与完成端口绑定 并投递accept请求 剩下由完成端口处理请求
	CNetMgr::GetInstance()->AddListener();



		

	return 0;
}
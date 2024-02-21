#pragma once
//#include<pthread.h> LINUX
#include<iostream>
#include<thread>
#include<List>
#include<mutex>
#include<vector>
class ThreadPool;

struct S_Worker {
	std::thread::id threadId; //�߳�id
	bool terminate; //�Ƿ������worker�ı�־
	int isWorking;  //��worker�Ƿ��ڹ���
	ThreadPool* pool; //�����ڵ��̳߳�
};

struct S_Job {
	void(*func)(void* arg); // ������
	void* userData;         // ��������
};

class ThreadPool {
public:
	ThreadPool();
	ThreadPool(int workNums,int maxJobNums = 10);
	~ThreadPool();

	// �������api
	int PushJob(void(*func)(void* data), void* arg, int len);

private:
	// ���̳߳����������
	bool _addJob(S_Job* job);

	// �ص�����
	static void* _run(void* arg);
	void _threadLoop(void* arg);

private:
	std::list<S_Job*>m_JobList;
	int m_MaxJobs; // ���������
	int m_ThreadNums; // �����߳���
	int m_FreeThreadNums; // ���й�����
	std::vector<std::thread*>m_v;
	S_Worker* m_workers;

	std::condition_variable m_cv; // �߳������ȴ�
	std::mutex m_mutex;  // ������
};
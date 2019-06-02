// �������    �洢�߳�Ҫִ�е�����
#pragma  once
#include <deque>
#include "Mutex.h"

class CTask;  //����CTask��  ��ֻ������  ��ʵ��������ͷ�ļ���

class CQueue{
public:
	CQueue(void);
	~CQueue(void);
public:
	CTask* pop();
	bool pushBack(CTask*t);
	bool pushFront(CTask*t);
	bool isEmpty();
	bool clear();
private:
	std::deque<CTask*> m_TaskQueue; //����һ������ �����������
	CMutex m_mutex;   //�������
};

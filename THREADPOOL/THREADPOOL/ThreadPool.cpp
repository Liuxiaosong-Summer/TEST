#include "ThreadPool.h"
#include "Thread.h"
#include "Task.h"
#include  <cassert>
#include  <iostream>

CMyThreadPool::CMyThreadPool(int num) {
	m_bIsExit = false;
	for (int i = 0; i<num; i++)
	{
		CThread* p = new CThread(this);
		m_IdleThreadStack.push(p);  //�������̼߳��뵽stack��
		p->startThread();
	}
}

CMyThreadPool::~CMyThreadPool(void) {

}

CThread* CMyThreadPool::PopIdleThread()
{
	//���������߳�
	CThread* pThread=m_IdleThreadStack.pop();
	//pThread->m_bIsActive=true;
	return pThread;
}
//���̴߳ӻ����ȡ������������߳�ջ�С���ȡ֮ǰ�жϴ�ʱ��������Ƿ����������������Ϊ��ʱ�Ź��𡣷�����������ȡ�������ִ�С�
bool CMyThreadPool::SwitchActiveThread(CThread* t)
{
	if (!m_TaskQueue.isEmpty())//������в�Ϊ�գ�����ȡ����ִ��
	{
		CTask *pTask = NULL;
		pTask = m_TaskQueue.pop();
		std::cout << "�߳�" << t->m_threadID << "ִ�� " << pTask->getid() << std::endl;

		t->assignTask(pTask);
		t->startTask();
	}
	else//�������Ϊ�գ��̹߳���
	{
		m_ActiveThreadList.removeThread(t);
		m_IdleThreadStack.push(t);
	}
	return true;
}

bool CMyThreadPool::addTask(CTask*t, PRIORITY priority)
{
	assert(t);
	if (!t || m_bIsExit)
	return false;
	CTask *task = NULL;
	std::cout << "[" << t->getid() << "]��ӣ�" << std::endl;
	if (priority == PRIORITY::NORMAL)
	{
		m_TaskQueue.pushBack(t);//����������С�
	}
	else if (PRIORITY::HIGH)
	{
		m_TaskQueue.pushFront(t);//�����ȼ�����
	}

	if (!m_IdleThreadStack.isEmpty())//���ڿ����̡߳����ÿ����̴߳�������
	{
		task = m_TaskQueue.pop();//ȡ����ͷ����
		if (task == NULL)
		{
			std::cout << "����ȡ������" << std::endl;
			return 0;
		}
		CThread* pThread = PopIdleThread();
		std::cout << "��" << pThread->m_threadID << "�� ִ��   ��" << task->getid() << "��" << std::endl;
		m_ActiveThreadList.addThread(pThread);
		pThread->assignTask(task);
		pThread->startTask();
	}
	return true;
}

bool CMyThreadPool::start()
{
	return 0;
}

CTask* CMyThreadPool::GetNewTask()
{
	if (m_TaskQueue.isEmpty())
	{
		return NULL;
	}
	CTask *task = m_TaskQueue.pop();//ȡ����ͷ����
	if (task == NULL)
	{
		std::cout << "����ȡ������" << std::endl;
		return 0;
	}
	return task;
}

//�����̳߳�
bool CMyThreadPool::destroyThreadPool()
{

	m_bIsExit = true;
	m_TaskQueue.clear();
	m_IdleThreadStack.clear();
	m_ActiveThreadList.clear();
	return true;
}
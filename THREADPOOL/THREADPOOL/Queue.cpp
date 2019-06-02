#include "Queue.h"
#include "Task.h"

CQueue::CQueue(void) {
}

CQueue::~CQueue(void) {
}

CTask* CQueue::pop()
{
	CTask* p = NULL;
	m_mutex.lock();
	//�Զ��н��зǿ��жϣ�
	if (!m_TaskQueue.empty())  
	{
		p = m_TaskQueue.front();//������Ԫ��
		m_TaskQueue.pop_front();//ɾ�����е���Ԫ��
	}
	m_mutex.unlock();
	return p;
}

bool CQueue::pushBack(CTask* t){
	if (t == NULL){
		return false;
	}
	m_mutex.lock();
	m_TaskQueue.push_back(t);
	m_mutex.unlock();
	return true;
}

bool CQueue::pushFront(CTask* t) {
	if (t == NULL) {
		return false;
	}
	m_mutex.lock();
	m_TaskQueue.push_front(t);
	m_mutex.unlock();
	return true;
}

bool CQueue::isEmpty(){
	bool ret;
	m_mutex.lock();
	ret = m_TaskQueue.empty();
	m_mutex.unlock();
	return ret;
}

bool CQueue::clear(){
	m_mutex.lock();
	m_TaskQueue.clear();
	m_mutex.unlock();
	return true;
}
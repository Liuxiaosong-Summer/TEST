
#include "Stack.h"
#include<cassert>
#include"Thread.h"

CStack::CStack(void)
{
}
CStack::~CStack(void)
{
}
CThread* CStack::pop()
{
	m_mutext.lock();
	if (!m_stack.empty())
	{
		CThread *t = m_stack.top();
		m_stack.pop();
		m_mutext.unlock();
		return t;
	}
	m_mutext.unlock();
	return NULL;
}
bool CStack::push(CThread* t)
{
	assert(t);
	if (!t)
		return false;
	m_mutext.lock();
	m_stack.push(t);
	m_mutext.unlock();
	return true;
}
int CStack::getSize()
{
	m_mutext.lock();
	int size = m_stack.size();
	m_mutext.unlock();
	return size;
}
bool CStack::isEmpty()
{
	m_mutext.lock();
	bool ret = m_stack.empty();
	m_mutext.unlock();
	return ret;
}
bool CStack::clear()
{
	m_mutext.lock();
	CThread* pThread = NULL;
	while (!m_stack.empty())
	{
		pThread = m_stack.top();
		m_stack.pop();
		pThread->resumeThread(); //»½ÐÑÏß³Ì
		pThread->m_bIsExit = true;
		delete pThread;
	}
	m_mutext.unlock();
	return true;
}
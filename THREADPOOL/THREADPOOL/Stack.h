//用来存放空闲线程

#pragma once

#include<stack>
#include "Mutex.h"

class CThread;

class CStack
{
public:
	CStack(void);
	~CStack(void);
public:
	CThread* pop();
	bool push(CThread*);
	int getSize();
	bool isEmpty();
	bool clear();
private:
	std::stack<CThread*> m_stack;
	CMutex m_mutext;
};

#pragma once
#include  <list>
#include "Mutex.h"
#include "Stack.h"
#include "List.h"
#include "Queue.h"

class CThread;
class CTask;

//设置线程优先集
enum PRIORITY
{
	NORMAL,
	HIGH
};

class CBaseThreadpool
{
public:
	virtual bool SwitchActiveThread(CThread*) = 0;
};

class CMyThreadPool :public CBaseThreadpool
{
public:
	CMyThreadPool(int num);
	~CMyThreadPool(void);
public:
	virtual CThread* PopIdleThread();
	virtual bool SwitchActiveThread(CThread*);
	virtual CTask*GetNewTask();
public:
	bool addTask(CTask*t, PRIORITY priority);
	bool start();
	bool destroyThreadPool();
private:
	int m_nThreadNum;
	bool m_bIsExit;

	CStack m_IdleThreadStack;
	CList m_ActiveThreadList;
	CQueue m_TaskQueue;
};

//活动线程列表   用来存储正在执行任务的线程

#pragma once
#include <list>
#include "Mutex.h"

class  CThread;

class CList{
public:
	CList(void);
	~CList(void);
public:
	bool addThread(CThread* Th);
	bool removeThread(CThread* Th);
	int getsize();
	bool isempty();
	bool clear();
private:
	std::list<CThread* > m_List;
	CMutex m_mutex;
};
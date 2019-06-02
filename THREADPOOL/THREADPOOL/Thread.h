
//工作线程类  每一个类管理一个线程 同时关联一个任务类对象
#pragma  once
#include "windows.h"
class CTask;
class CBaseThreadpool;

class CThread {
public :
	CThread(CBaseThreadpool*  threadPool);
	~CThread(void);
public:
	bool startThread();  //启动线程
	bool suspendThread(); //暂停线程
	bool resumeThread();  //唤醒线程
	bool assignTask(CTask*pTask);  //标记任务
	bool startTask();  //开始执行任务
	static DWORD WINAPI threadProc(LPVOID pParam); //作为线程的起始地址
	DWORD m_threadID;
	HANDLE m_hThread; //线程句柄 用来操作线程
	bool m_bIsExit;
private:
	HANDLE m_hEvent;  //互斥对象的句柄
	CTask* m_pTask;  //关联的任务类对象
	CBaseThreadpool* m_pThreadPool;
};

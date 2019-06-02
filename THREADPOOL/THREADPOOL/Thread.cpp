#include "Thread.h"
#include"Task.h"
#include "ThreadPool.h"
#include<cassert>
#define WAIT_TIME 20

CThread::CThread(CBaseThreadpool*  threadPool){
	m_pThreadPool = threadPool;
	m_hEvent = CreateEvent(NULL, false, false, NULL); // 创建信号量
	m_bIsExit = false;
}
CThread::~CThread(void){
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}


bool CThread::startThread() {
	m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);   //创建一个线程
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

bool CThread::suspendThread() {
	//暂停进程
	ResetEvent(m_hEvent);
	return true;
}

bool CThread::resumeThread() {
	//唤醒进程
	SetEvent(m_hEvent);
	return true;
}

bool CThread::startTask() {
	//线程开始执行任务
	resumeThread();
	return true;
}

bool CThread::assignTask(CTask* pTask){
	if (pTask) {
		return false;
	}
	m_pTask = pTask;
	return true;
}
DWORD WINAPI CThread::threadProc(LPVOID pParam) {
	CThread* pThread = (CThread*)pParam;
	while (!pThread->m_bIsExit) {
		DWORD ret = WaitForSingleObject(pThread->m_hEvent, INFINITE);   //通过检测m_hEvent（互斥对象的句柄）状态  来判断程序是否执行
		//对象有状态
		if (ret == WAIT_OBJECT_0) {
			if (pThread->m_pTask) {
				pThread->m_pTask = NULL;
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
	}
	return 0;
}

#include "Thread.h"
#include"Task.h"
#include "ThreadPool.h"
#include<cassert>
#define WAIT_TIME 20

CThread::CThread(CBaseThreadpool*  threadPool){
	m_pThreadPool = threadPool;
	m_hEvent = CreateEvent(NULL, false, false, NULL); // �����ź���
	m_bIsExit = false;
}
CThread::~CThread(void){
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}


bool CThread::startThread() {
	m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);   //����һ���߳�
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

bool CThread::suspendThread() {
	//��ͣ����
	ResetEvent(m_hEvent);
	return true;
}

bool CThread::resumeThread() {
	//���ѽ���
	SetEvent(m_hEvent);
	return true;
}

bool CThread::startTask() {
	//�߳̿�ʼִ������
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
		DWORD ret = WaitForSingleObject(pThread->m_hEvent, INFINITE);   //ͨ�����m_hEvent���������ľ����״̬  ���жϳ����Ƿ�ִ��
		//������״̬
		if (ret == WAIT_OBJECT_0) {
			if (pThread->m_pTask) {
				pThread->m_pTask = NULL;
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
	}
	return 0;
}


//�����߳���  ÿһ�������һ���߳� ͬʱ����һ�����������
#pragma  once
#include "windows.h"
class CTask;
class CBaseThreadpool;

class CThread {
public :
	CThread(CBaseThreadpool*  threadPool);
	~CThread(void);
public:
	bool startThread();  //�����߳�
	bool suspendThread(); //��ͣ�߳�
	bool resumeThread();  //�����߳�
	bool assignTask(CTask*pTask);  //�������
	bool startTask();  //��ʼִ������
	static DWORD WINAPI threadProc(LPVOID pParam); //��Ϊ�̵߳���ʼ��ַ
	DWORD m_threadID;
	HANDLE m_hThread; //�߳̾�� ���������߳�
	bool m_bIsExit;
private:
	HANDLE m_hEvent;  //�������ľ��
	CTask* m_pTask;  //���������������
	CBaseThreadpool* m_pThreadPool;
};

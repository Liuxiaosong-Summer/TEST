#pragma once

//�������
class CTask
{
public:
	CTask(int id);
	~CTask(void);
public:
	virtual void taskProc() = 0;  //���麯�� ��������Ҫ�̳д��� ʵ��taskProc()����
	int getid();
private:
	int m_ID;
};
#pragma once

//任务基类
class CTask
{
public:
	CTask(int id);
	~CTask(void);
public:
	virtual void taskProc() = 0;  //纯虚函数 所有任务都要继承此类 实现taskProc()方法
	int getid();
private:
	int m_ID;
};
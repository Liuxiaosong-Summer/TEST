// 任务队列    存储线程要执行的任务
#pragma  once
#include <deque>
#include "Mutex.h"

class CTask;  //依赖CTask类  （只是声明  在实现里边添加头文件）

class CQueue{
public:
	CQueue(void);
	~CQueue(void);
public:
	CTask* pop();
	bool pushBack(CTask*t);
	bool pushFront(CTask*t);
	bool isEmpty();
	bool clear();
private:
	std::deque<CTask*> m_TaskQueue; //定义一个队列 用来存放任务
	CMutex m_mutex;   //互斥变量
};

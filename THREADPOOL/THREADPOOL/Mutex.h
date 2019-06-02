//互斥类   实现线程之间的互斥访问
#pragma  once
#include "windows.h"

class CMutex {
public:
	CMutex(void);
	~CMutex(void);
public:
	bool lock();
	bool unlock();
private:
	CRITICAL_SECTION m_cs;  //多线程之间的共享资源 （临界资源）
};

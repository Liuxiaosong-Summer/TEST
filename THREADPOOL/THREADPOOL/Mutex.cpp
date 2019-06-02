#include "Mutex.h"

CMutex::CMutex(){
	InitializeCriticalSection(&m_cs);
}

CMutex::~CMutex() {

}

bool CMutex::lock() {
	//判断是否有线程访问临界资源，如果没有直接改变CRITICAL_SECTION
	//结构体的值，把访问权给当前线程，立即返回。如果有，则等待
	EnterCriticalSection(&m_cs); 
	return true;
}

bool CMutex::unlock() {
	//释放CRITICAL_SECTION结构指针
	LeaveCriticalSection(&m_cs);
	return false;
}
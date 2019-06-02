#include "Mutex.h"

CMutex::CMutex(){
	InitializeCriticalSection(&m_cs);
}

CMutex::~CMutex() {

}

bool CMutex::lock() {
	//�ж��Ƿ����̷߳����ٽ���Դ�����û��ֱ�Ӹı�CRITICAL_SECTION
	//�ṹ���ֵ���ѷ���Ȩ����ǰ�̣߳��������ء�����У���ȴ�
	EnterCriticalSection(&m_cs); 
	return true;
}

bool CMutex::unlock() {
	//�ͷ�CRITICAL_SECTION�ṹָ��
	LeaveCriticalSection(&m_cs);
	return false;
}
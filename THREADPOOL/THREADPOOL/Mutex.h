//������   ʵ���߳�֮��Ļ������
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
	CRITICAL_SECTION m_cs;  //���߳�֮��Ĺ�����Դ ���ٽ���Դ��
};

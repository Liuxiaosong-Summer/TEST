#include "Task.h"
//#include "windows.h"

CTask::CTask(int id){
	m_ID = id;
}

CTask::~CTask(void){
}

int CTask::getid(){
	return m_ID;  //���������ID��
}
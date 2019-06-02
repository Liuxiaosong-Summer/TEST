#include "List.h"
#include "Thread.h"

CList::CList(void) {
}
CList::~CList(void) {

}
bool CList::addThread(CThread* Th){
	if (Th == NULL) {
		return NULL;
	}
	m_mutex.lock();
	m_List.push_back(Th);
	m_mutex.unlock();
	return true;
}

bool CList::removeThread(CThread* Th){
	if (Th == NULL) {
		return false;
	}
	m_mutex.lock();
	m_List.remove(Th);
	m_mutex.unlock();
	return true;
}

int CList::getsize() {
	int size;
	m_mutex.lock();
	size = m_List.size();
	m_mutex.unlock();
	return size;
}

bool CList::clear(){
	m_mutex.lock();
	std::list<CThread*>::iterator iter = m_List.begin();
	for (; iter != m_List.end(); iter++)
	{
		delete (*iter);
	}
	m_List.clear();
	m_mutex.unlock();
	return true;
}
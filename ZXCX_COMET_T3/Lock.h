//////////////////////////////////////////////////////////////////////
//	Lock.cpp
//////////////////////////////////////////////////////////////////////
#include <windows.h>
class CZSSLockObject
{
public:
	CZSSLockObject();
	virtual ~CZSSLockObject();

	CRITICAL_SECTION m_sect;

	void Enter();
	void Leave();
};

class CZSSAutoLock
{
public:
	CZSSAutoLock(CZSSLockObject *plock);
	~CZSSAutoLock();

private:
	CZSSLockObject *m_plock;
};
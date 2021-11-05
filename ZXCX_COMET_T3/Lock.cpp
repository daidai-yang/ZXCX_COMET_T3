#include "Lock.h"
#include "pch.h"

CZSSLockObject::CZSSLockObject()
{
	::InitializeCriticalSection(&m_sect);
}
CZSSLockObject::~CZSSLockObject()
{
	::DeleteCriticalSection(&m_sect);
}
void CZSSLockObject::Enter()
{
	::EnterCriticalSection(&m_sect);
}
void CZSSLockObject::Leave()
{
	::LeaveCriticalSection(&m_sect);
}
CZSSAutoLock::CZSSAutoLock(CZSSLockObject *plock)
{
	m_plock = plock;
	m_plock->Enter();
}
CZSSAutoLock::~CZSSAutoLock()
{
	m_plock->Leave();
}
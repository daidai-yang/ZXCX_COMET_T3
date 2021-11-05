#pragma once

class CSocketPool
{
public:
	CSocketPool();
	virtual ~CSocketPool();
public:
	BOOL m_bRunning;
	SOCKET m_hSocket;
	int StopThread(CSocket* pSocket);
	int StopAll();
};

int ThreadServer(CSocketPool* pSocketPool);
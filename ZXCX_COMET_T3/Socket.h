#pragma once
#define   DATA_BUFSIZE   4096

class CSocket
{
public:
	CSocket(HWND hWnd);
	~CSocket(void);

public:
	HWND			m_hWnd;
	DWORD			m_dwRecvBytes, m_Flags;
	BOOL			m_bIsConnected;
	HANDLE			m_hThreadWatch;
	BOOL			bWrited;
	char			sRcvBuf[4096];	
	UINT			usRcvLen;

	SOCKET			m_hSocket;	//¾ä±ú
	WSAOVERLAPPED	m_osRead, m_osWrite;

public:
	BOOL	OpenSocket(CString ip, DWORD port);
	void	CloseSocket();
	void	InitBuffer();									// when start new send/recv
	DWORD	SendData(char* pBuff, DWORD nToWrite);
	DWORD	WriteSocket(WSABUF *pBuff, DWORD nToWrite);
	DWORD	ReadSocket(WSABUF *pBuff, DWORD nToRead);

	__inline BOOL SocketAddRcvData(char *bInBuf, UINT iLen);
	BOOL	SocketGetWaitLen(int *iWaitLen);
	BOOL	SocketGetRcvPacket(char *bPacket, int iPacketLen);
};


DWORD WINAPI ThreadWatchSocket(CSocket* pSocket);



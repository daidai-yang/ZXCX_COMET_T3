#include "pch.h"

CSocketPool::CSocketPool()
{
	m_bRunning = TRUE;
}

CSocketPool::~CSocketPool()
{
	m_bRunning = FALSE;
}

int ThreadServer(CSocketPool* pSocketPool)
{
	int nRet			= TRUE;
	int iResult			= 0;
	DWORD dwByte		= 0;
	WSADATA wsaData;

	SOCKADDR_IN ClientAddr;																									// 定义一个客户端得地址结构作为参数
	int addr_length = sizeof(ClientAddr);
	LPCTSTR lpIP; 
	UINT nPort;


	if(nRet = WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		ZxcxLogERROR(_T("<%s  %d> %s() WSAStartup failed: %d\n"), __FILE__, __LINE__, __FUNCTION__, nRet);
		WSACleanup(); 
		return nRet;
	}

	if((pSocketPool->m_hSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)								//创建TCP套接字
	{
		ZxcxLogERROR(_T("<%s  %d> %s() socket Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		WSACleanup();
		return FALSE;
	}

	SOCKADDR_IN ServerAddr;																									//分配端口及协议族并绑定
	ServerAddr.sin_family = AF_INET;                                
	//ServerAddr.sin_addr.S_un.S_addr  = htonl(INADDR_ANY);     
	ServerAddr.sin_addr.S_un.S_addr = htonl(g_ip);
	ServerAddr.sin_port = htons(g_nPort);

	if((nRet = bind(pSocketPool->m_hSocket,(LPSOCKADDR)&ServerAddr, sizeof(ServerAddr))) == SOCKET_ERROR)					// 绑定套接字
	{
		ZxcxLogERROR(_T("<%s  %d> %s() bind Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		closesocket(pSocketPool->m_hSocket);
		WSACleanup();
		return nRet;
	}

	if(nRet = listen(pSocketPool->m_hSocket, 100) == SOCKET_ERROR)
	{
		ZxcxLogERROR(_T("<%s  %d> %s() listen Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		closesocket(pSocketPool->m_hSocket);
		WSACleanup();
		return nRet;
	}

	while(pSocketPool->m_bRunning)
	{

		CSocket *pSocket = new CSocket(g_hMsgWnd);

		pSocket->m_AcceptSocket = accept(pSocketPool->m_hSocket,(SOCKADDR*)&ClientAddr, &addr_length);
		if(pSocket->m_AcceptSocket  == INVALID_SOCKET)
		{
			ZxcxLogERROR(_T("<%s  %d> %s() listen Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
			nRet = FALSE;
		}
		else
		{

			lpIP = inet_ntoa(ClientAddr.sin_addr);
			nPort = ClientAddr.sin_port;
			ZxcxLogINFO(_T("<%s  %d> %s() A Client is Connected(IP: %s, Port: %d)"), __FILE__, __LINE__, __FUNCTION__, lpIP, nPort);
			ZeroMemory(&pSocket->m_osRead, sizeof(WSAOVERLAPPED));
			if ((pSocket->m_osRead.hEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
			{
				ZxcxLogERROR(_T("<%s  %d> %s() WSACreateEvent Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
				nRet = FALSE;
			}
			ZeroMemory(&pSocket->m_osWrite, sizeof(WSAOVERLAPPED));
			if ((pSocket->m_osWrite.hEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
			{
				ZxcxLogERROR(_T("<%s  %d> %s() WSACreateEvent Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
				nRet = FALSE;
			}

			g_cObjectList.Add(pSocket);
			pSocket->m_bIsConnected = TRUE;
			pSocket->m_hThreadWatch = CreateThread(NULL, 0,
 				(LPTHREAD_START_ROUTINE)ThreadWatchSocket, pSocket, 0, NULL);
		}
	}
 
	return nRet;
}
int CSocketPool::StopThread(CSocket* pSocket)
{
	pSocket->m_bIsConnected = FALSE;
	SetEvent(pSocket->m_osRead.hEvent);
	SetEvent(pSocket->m_osWrite.hEvent);
	Sleep(300);
	WSACloseEvent(pSocket->m_osRead.hEvent);
	WSACloseEvent(pSocket->m_osWrite.hEvent);
	
	if (pSocket->m_hThreadWatch != NULL)
		CloseHandle(pSocket->m_hThreadWatch);
	closesocket(pSocket->m_AcceptSocket);
	
	pSocket->m_osRead.hEvent		= NULL;
	pSocket->m_osWrite.hEvent		= NULL;
	pSocket->m_hThreadWatch			= NULL;

	g_cObjectList.Remove(pSocket);
	delete pSocket;

	return TRUE;
}
int CSocketPool::StopAll()
{
	CSocket* pSocket = NULL;

	if (g_cObjectList.IsEmtpy())
		return TRUE;

	g_cObjectList.GetLast(pSocket);
	m_bRunning = FALSE;
	StopThread(pSocket);

	while (!g_cObjectList.IsEmtpy())
	{
		g_cObjectList.GetLast(pSocket);
		StopThread(pSocket);
	}

	return TRUE;
}


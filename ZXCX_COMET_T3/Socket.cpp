//*******************************************************************************************************
//** Copyright (C)  2021 ZXCX Technologies Co., Ltd.
//** 版权所有。 
//**
//** 文件名: Socket.cpp
//** 模块功能描述：tcp通讯客户端代码
//** 创建标记：ydd
//** 创建日期：2021/09/16 08:43:51
//-------------------------------------------------------------------------------------------------------
//** 修改标记：
//** 修改描述：
//**
//** 修改标记：
//** 修改描述：
//**
//*******************************************************************************************************

#include "pch.h"

CSocket::CSocket(HWND hWnd)
{
	m_hWnd = hWnd;
	m_bIsConnected = FALSE;
	m_dwRecvBytes = 0;
	m_Flags = 0;
	m_hSocket = NULL;
}

CSocket::~CSocket(void)
{
	m_hWnd = NULL;
}

BOOL CSocket::OpenSocket(CString ip, DWORD port)
{
	int nRet		= TRUE;
	DWORD			dwThreadID;
	m_bIsConnected	= FALSE;

	ZeroMemory(&m_osRead, sizeof(WSAOVERLAPPED));
	if ((m_osRead.hEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		ZxcxLogERROR(_T("<%s  %d> %s() WSACreateEvent Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		return FALSE;
	}

	ZeroMemory(&m_osWrite, sizeof(WSAOVERLAPPED));
	if ((m_osWrite.hEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		ZxcxLogERROR(_T("<%s  %d> %s() WSACreateEvent Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		return FALSE;
	}


	WSADATA wsaData;

	SOCKADDR_IN ClientAddr;				// 定义一个客户端得地址结构作为参数
	int addr_length = sizeof(ClientAddr);

	if (nRet = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ZxcxLogERROR(_T("<%s  %d> %s() WSAStartup failed: %d\n"), __FILE__, __LINE__, __FUNCTION__, nRet);
		WSACleanup();
		return FALSE;
	}

	if ((m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)								//创建TCP套接字
	{
		ZxcxLogERROR(_T("<%s  %d> %s() socket Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		WSACleanup();
		return FALSE;
	}
	ZxcxLogINFO("ip:%s--port:%d", ip, port);

	SOCKADDR_IN ServerAddr;					//分配端口及协议族
	ServerAddr.sin_family = AF_INET;    
	//ServerAddr.sin_addr.S_un.S_addr = htonl(atol(ip));
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(ip.GetBuffer(0));
	ServerAddr.sin_port = htons(port);

	if ((nRet = connect(m_hSocket, (LPSOCKADDR)&ServerAddr, sizeof(SOCKADDR))) == SOCKET_ERROR)		//建立连接
	{
		ZxcxLogERROR(_T("<%s  %d> %s() bind Failed(ErrorNO: %d)"), __FILE__, __LINE__, __FUNCTION__, WSAGetLastError());
		closesocket(m_hSocket);
		WSACleanup();
		return FALSE;
	}

	m_bIsConnected = TRUE;
	m_hThreadWatch = CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE)ThreadWatchSocket, this, 0, &dwThreadID);					//创建接收线程

	if (! m_hThreadWatch)
	{
		CloseSocket();
		return FALSE;
	}

	return TRUE;
}

void CSocket::CloseSocket()
{
	BOOL bRet = FALSE;
	m_bIsConnected = FALSE;

	SetEvent(m_osRead.hEvent);
	SetEvent(m_osWrite.hEvent);
	Sleep(300);
	WSACloseEvent(m_osRead.hEvent);
	WSACloseEvent(m_osWrite.hEvent);

	if (m_hSocket)
	{
		CloseHandle(m_hThreadWatch);
		closesocket(m_hSocket);
	}
	m_osRead.hEvent = NULL;
	m_osWrite.hEvent = NULL;
	m_hThreadWatch = NULL;

}

void CSocket::InitBuffer()
{
	memset(sRcvBuf, 0x00, sizeof(sRcvBuf));
	usRcvLen = 0;
}

DWORD CSocket::SendData(char* pBuff, DWORD nToWrite)
{
	DWORD	dwWritten = 0;

	WSABUF	wsaBuf;

	wsaBuf.buf = pBuff;
	wsaBuf.len = nToWrite;

	dwWritten = WriteSocket(&wsaBuf, 1);

	return dwWritten;
}

DWORD CSocket::WriteSocket(WSABUF *DataBuf, DWORD nToWrite)
{
	DWORD	dwWritten;
	DWORD dwIndex;
	DWORD dwSendBytes = 0;
	dwWritten = 0;

	bWrited = FALSE;
	if (WSASend(m_hSocket, DataBuf, nToWrite, &dwSendBytes, m_Flags, &m_osWrite, NULL) == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSA_IO_PENDING)
		{
			dwIndex = WSAWaitForMultipleEvents(1, &m_osWrite.hEvent ,FALSE ,WSA_INFINITE,FALSE);
			dwIndex = dwIndex - WSA_WAIT_EVENT_0;
			WSAResetEvent(m_osWrite.hEvent);
			WSAGetOverlappedResult(m_hSocket, &m_osWrite ,&dwSendBytes, FALSE, &m_Flags);
		}
		int err  = WSAGetLastError();
	}

	if (dwSendBytes != 0)
		bWrited = TRUE;

	return dwSendBytes; 
}
DWORD CSocket::ReadSocket(WSABUF *DataBuf, DWORD nToRead)
{
	DWORD dwIndex = 0;
	DWORD dwBytesTransferred = 0;

	if (WSARecv(m_hSocket, DataBuf, 1, &m_dwRecvBytes, &m_Flags, &m_osRead, NULL) == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSA_IO_PENDING)
		{
			dwIndex = WSAWaitForMultipleEvents(1, &m_osRead.hEvent ,FALSE ,WSA_INFINITE,FALSE);
			dwIndex = dwIndex - WSA_WAIT_EVENT_0;
			WSAResetEvent(m_osRead.hEvent);
			WSAGetOverlappedResult(m_hSocket, &m_osRead,&dwBytesTransferred, FALSE, &m_Flags);
			return dwBytesTransferred;
		}
		else
			m_dwRecvBytes = 0;

		if(dwBytesTransferred == 0)
		{
			return m_dwRecvBytes;
		}
	}

	
	return m_dwRecvBytes;
}

__inline BOOL CSocket::SocketAddRcvData(char *bInBuf, UINT iLen)
{
	if((usRcvLen+iLen) > 2048)
		return FALSE;

	memcpy(&sRcvBuf[usRcvLen], bInBuf, iLen);
	usRcvLen+=iLen;

	return TRUE;
}

BOOL CSocket::SocketGetWaitLen(int *iWaitLen)
{
	*iWaitLen = usRcvLen;
	return TRUE;
}

BOOL CSocket::SocketGetRcvPacket(char *bPacket, int iPacketLen)
{
	memcpy(bPacket, sRcvBuf, iPacketLen);
	usRcvLen-=iPacketLen;
	memcpy(sRcvBuf, &sRcvBuf[iPacketLen],usRcvLen); 
	memset(&sRcvBuf[usRcvLen], 0x00, iPacketLen); 
	//add your code
	//return CheckBCC(bPacket, iPacketLen);

	return TRUE;
}

DWORD WINAPI ThreadWatchSocket(CSocket* pSocket)
{
	DWORD		dwEvent;
	char		buff[2048] = {0};
	char		bPacket[2048] = {0};	 
	DWORD		dwRead;	
	int			iBuflen=0, iPacketlen=0;

	WSABUF DataBuf;

	DataBuf.len = DATA_BUFSIZE;
	DataBuf.buf = (char *)buff;	

	memset(pSocket->sRcvBuf, 0x00, sizeof(pSocket->sRcvBuf));
	pSocket->usRcvLen = 0;
	while (pSocket->m_bIsConnected)
	{
		dwEvent = 0;	 
		do	
		{
			dwRead = pSocket->ReadSocket(&DataBuf, 2048);
			if(!dwRead)
				break;

			if(!pSocket->SocketAddRcvData((char*)DataBuf.buf, (UINT)dwRead))
				break; 
			if (pSocket->usRcvLen != 0)
				ZxcxLogDEBUG(_T("(ReadCom(buff):[%d][%s])"), pSocket->usRcvLen, pSocket->sRcvBuf);
			else
				continue;


			if (pSocket->SocketGetWaitLen(&iPacketlen))														// GET WAIT PACK LEN
			{
				memset(bPacket, 0x00, sizeof(bPacket));
				ZxcxLogINFO(_T("(ReadSocket(buff):[%d][%s])"), pSocket->usRcvLen, pSocket->sRcvBuf);

				if(pSocket->SocketGetRcvPacket((char*)bPacket, iPacketlen))											// CHECK PACK DATA
				{
					pSocket->bWrited = FALSE;
					memcpy(g_szRecvBuff, bPacket, iPacketlen);
					g_nRecvLen = iPacketlen;
					SetEvent(g_hEvent);		//发送信号
					iPacketlen = 0;
					memset(pSocket->sRcvBuf, 0x00, sizeof(pSocket->sRcvBuf));
					memset(DataBuf.buf, 0x00, sizeof(DataBuf.buf));
				}
			}
			else if(iPacketlen == -1)
			{
				iPacketlen = 0;
				memset(pSocket->sRcvBuf, 0x00, sizeof(pSocket->sRcvBuf));
				pSocket->usRcvLen = 0;
			}

		} while (dwRead);
	}

	pSocket->m_hThreadWatch = NULL;
	return TRUE;
}

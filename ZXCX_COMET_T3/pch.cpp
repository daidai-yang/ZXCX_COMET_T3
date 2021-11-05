// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
HWND					g_hMsgWnd;
HINSTANCE				g_hInstance;
CString					g_strSubVersion;
CZxcxLog*				g_pComet_t3Logger;

BOOL					g_bIsOpen;
CSocket*				g_pSocketThread;
HANDLE					g_hEvent;
BYTE					g_ProcCmd;
CString					g_ip;
int						g_nPort;

int						g_nSendLen;
int						g_nRecvLen;
char					g_szSendBuff[SENDRECV_BUFFER_LEN];
char					g_szRecvBuff[SENDRECV_BUFFER_LEN];

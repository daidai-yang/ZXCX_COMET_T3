#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H



extern HWND					g_hMsgWnd;
extern HINSTANCE			g_hInstance;
extern CString				g_strSubVersion;
extern CZxcxLog*			g_pComet_t3Logger;

extern BOOL					g_bIsOpen;
extern CSocket*				g_pSocketThread;
extern HANDLE				g_hEvent;
extern BYTE					g_ProcCmd;
extern CString				g_ip;
extern int					g_nPort;

extern int					g_nSendLen;
extern int					g_nRecvLen;
extern char					g_szSendBuff[SENDRECV_BUFFER_LEN];
extern char					g_szRecvBuff[SENDRECV_BUFFER_LEN];


#endif
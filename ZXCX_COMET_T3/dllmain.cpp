// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		g_hInstance = hModule;

		g_pComet_t3Logger = new CZxcxLog((BYTE*)"ZXCX_COMET_T3");
		ZxcxLogINFO("(====================ZXCX_COMET_T3 DLL START V1.0.0.1 2021-09-16====================)");

		char	tempPath[MAX_PATH] = { 0 };
		GetModuleFileName(g_hInstance, tempPath, MAX_PATH);

		g_strSubVersion = GetFileVersion(tempPath);

		InitializeDll();
	}
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		if (g_pSocketThread != NULL)
		{
			g_pSocketThread->CloseSocket();
			ResetEvent(g_hEvent);
			CloseHandle(g_hEvent);
			delete g_pSocketThread;
			g_pSocketThread = NULL;
		}
		ZxcxLogINFO("DLL_PROCESS_DETACH");
		if (g_pComet_t3Logger != NULL)
		{
			delete g_pComet_t3Logger;
			g_pComet_t3Logger = NULL;
		}
        break;
    }
    return TRUE;
}

int SendRecvData(long lWaitTime)
{
	int		nRetryCount = 0, nCycTime = 50, i = 0;
	DWORD	dwReturn = 0;
	MSG		msg;

	g_pSocketThread->InitBuffer();
	ResetEvent(g_hEvent);

	do
	{
		i++;
		dwReturn = g_pSocketThread->SendData(g_szSendBuff, g_nSendLen);
		ZxcxLogINFO(_T("(SendData : g_szSendBuff:[%s], g_nSendLen:[%d])"), MakeUnPack(g_szSendBuff, g_nSendLen), dwReturn);
		if (dwReturn <= 0)
		{
			g_pSocketThread->m_bIsConnected = FALSE;
			return DT_ERROR_SENDSOCKET;
		}
		nRetryCount = lWaitTime / nCycTime;

		do {
			nRetryCount--;

			dwReturn = WaitForSingleObject(g_hEvent, nCycTime); // wait for recv data event
			if (dwReturn == WAIT_OBJECT_0)
			{
				ZxcxLogINFO(_T("(g_szRecvBuff:[%s], g_nRecvLen:[%d])"), g_szRecvBuff, g_nRecvLen);
				return DT_SUCCESS;
			}

			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		} while (nRetryCount);
	} while (i < 3);

	return DT_ERROR_WAITSOCKET;
}

void InitializeSRBuffer()
{
	g_nSendLen = 0;
	g_nRecvLen = 0;
	memset(g_szSendBuff, 0x00, sizeof(g_szSendBuff));
	memset(g_szRecvBuff, 0x00, sizeof(g_szRecvBuff));
}
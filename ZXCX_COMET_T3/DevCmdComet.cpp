#include "pch.h"

int WINAPI MakeCmdPack(BYTE btCmd, char* Data, int nDataLen)
{
	int		nIndex = 0;

	g_ProcCmd = btCmd;
	InitializeSRBuffer();

	switch (btCmd)
	{
	case DEV_CMD_CONTST_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_CONTST, DEV_CMD_FENHAO);
		g_nSendLen = 18 + 1;
	}
	break;
	case DEV_CMD_SYSSTAT_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_SYSSTAT, DEV_CMD_FENHAO);
		g_nSendLen = 19 + 1;
	}
	break;
	case DEV_CMD_HVSTAT_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_HVSTAT, DEV_CMD_FENHAO);
		g_nSendLen = 18 + 1;
	}
	break;
	case DEV_CMD_GET_HIVO_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_GET_HIVO, DEV_CMD_FENHAO);
		g_nSendLen = 16 + 1;
	}
	break;
	case DEV_CMD_HIVOM_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_HIVOM, DEV_CMD_FENHAO);
		g_nSendLen = 17 + 1;
	}
	break;
	case DEV_CMD_GET_TUCU_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_GET_TUCU, DEV_CMD_FENHAO);
		g_nSendLen = 16 + 1;
	}
	break;
	case DEV_CMD_TUCUM_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_TUCUM, DEV_CMD_FENHAO);
		g_nSendLen = 17 + 1;
	}
	break;
	case DEV_CMD_GET_FOCSL_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_GET_FOCSL, DEV_CMD_FENHAO);
		g_nSendLen = 17 + 1;
	}
	break;
	case DEV_CMD_FOCSZ_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_FOCSZ, DEV_CMD_FENHAO);
		g_nSendLen = 17 + 1;
	}
	break;
	case DEV_CMD_WUPCD_CODE:
	{
		sprintf_s(g_szSendBuff, "%s%s", DEV_CMD_WUPCD, DEV_CMD_FENHAO);
		g_nSendLen = 17 + 1;
	}
	break;
	case DEV_CMD_HIVO_CODE:
	{
		//TA10S000	--|HIVO=	e3	;	
		//8			+3			+2	+1

		//求变量位的长度TA10S000''最后一位的值,需要去掉--| 长度3 再加上 分号1个长度
		int taCmdLenValue = 5 + nDataLen + 2 + 1;

		//TA10S000B--|HIVO=100e3;	
		sprintf_s(g_szSendBuff, "%s%X%s%s%s%s%s", DEV_CMD_TA, taCmdLenValue, DEV_CMD_TA__, DEV_CMD_HIVO, Data, DEV_CMD_E3, DEV_CMD_FENHAO);
		ZxcxLogINFO("DEV_CMD_HIVO_CODE = %s", g_szSendBuff);
		//TA10S000 B --| HIVO= 100 e3 ;	
		g_nSendLen = 8 + 1 + 3 + 5 + nDataLen + 2 + 1;
	}

	break;
	case DEV_CMD_TUCU_CODE:
	{
		int taCmdLenValue = 5 + nDataLen + 2 + 1;

		//TA10S000B--|TUCU=3 e-3;	
		sprintf_s(g_szSendBuff, "%s%X%s%s%s%s%s", DEV_CMD_TA, taCmdLenValue, DEV_CMD_TA__, DEV_CMD_TUCU, Data, DEV_CMD_E_3, DEV_CMD_FENHAO);
		ZxcxLogINFO("DEV_CMD_TUCU_CODE = %s", g_szSendBuff);
		//TA10S000 B --| TUCU= 3 e-3 ;	
		g_nSendLen = 8 + 1 + 3 + 5 + nDataLen + 3 + 1;
	}
	break;
	case DEV_CMD_FOCSL_CODE:
	{
		int taCmdLenValue = 6 + nDataLen + 1;

		//TA10S000B--|FOCSL=1;	
		sprintf_s(g_szSendBuff, "%s%X%s%s%s%s", DEV_CMD_TA, taCmdLenValue, DEV_CMD_TA__, DEV_CMD_FOCSL, Data, DEV_CMD_FENHAO);
		//TA10S000 B --| FOCSL= 1;	
		g_nSendLen = 8 + 1 + 3 + 6 + nDataLen + 1;
	}
	break;
	case DEV_CMD_HVEN_CODE:
	{
		int taCmdLenValue = 5 + nDataLen + 1;

		//TA10S0007--|HVEN=1;	
		sprintf_s(g_szSendBuff, "%s%X%s%s%s%s", DEV_CMD_TA, taCmdLenValue, DEV_CMD_TA__, DEV_CMD_HVEN, Data, DEV_CMD_FENHAO);
		ZxcxLogINFO("DEV_CMD_HVEN_CODE = %s", g_szSendBuff);
		//TA10S000 7 --| HVEN= 1  ;	
		g_nSendLen = 8 + 1 + 3 + 5 + nDataLen + 1;
	}
	break;
	default:
		break;
	}

	return TRUE;
}
int WINAPI ProcRecvData(CHAR* pszReturnData, int* pnReturnLen)
{
	int		nRet = DT_SUCCESS, nDataLen = 0, nIndex = 1;
	switch (g_ProcCmd)
	{
	case DEV_CMD_CONTST_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_SYSSTAT_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_HVSTAT_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_GET_HIVO_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_HIVOM_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_GET_TUCU_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_TUCUM_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_GET_FOCSL_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_FOCSZ_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_WUPCD_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_HIVO_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_TUCU_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_FOCSL_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	case DEV_CMD_HVEN_CODE:
		memcpy(pszReturnData, &g_szRecvBuff, g_nRecvLen);
		*pnReturnLen = g_nRecvLen;
		break;
	default:
		break;
	}
	return nRet;
}
int WINAPI fnDevCometOpen(CString ip, DWORD port)
{
	ZxcxLogINFO("");
	int nRet = TRUE;

	if (g_pSocketThread != NULL)
	{
		g_pSocketThread->CloseSocket();
		ResetEvent(g_hEvent);
		CloseHandle(g_hEvent);
		delete g_pSocketThread;
		g_pSocketThread = NULL;
		ZxcxLogINFO("g_pSocketThread->CloseSocket()");
	}
	g_pSocketThread = new CSocket(g_hMsgWnd);					// Create comport thread
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (g_pSocketThread->OpenSocket(ip, port))
	{
		g_pSocketThread->m_bIsConnected = TRUE;
		nRet = DT_SUCCESS;
	}

	if (nRet != DT_SUCCESS)
		ZxcxLogERROR(_T("(return : %s)"), GetRtStr(nRet));
	else
		ZxcxLogINFO(_T("(return : %s)"), GetRtStr(nRet));
	return nRet;
}
int WINAPI fnDevCometClose()
{
	ZxcxLogINFO("");
	if (g_pSocketThread != NULL)
	{
		g_pSocketThread->CloseSocket();
		ResetEvent(g_hEvent);
		CloseHandle(g_hEvent);
		delete g_pSocketThread;
		g_pSocketThread = NULL;
	}
	return DT_SUCCESS;
}
int WINAPI fnDevCOmetReset()
{

	BYTE		nRet = DT_SUCCESS;

	return nRet;
}

int WINAPI fnDevCometGetSYSStatus(char* status)
{
	ZxcxLogINFO("");
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	MakeCmdPack(DEV_CMD_SYSSTAT_CODE, NULL, NULL);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	memcpy(status, szRecvData, nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}

int WINAPI fnDevCometGetHVStatus(char* status)
{
	ZxcxLogINFO("");
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	MakeCmdPack(DEV_CMD_HVSTAT_CODE, NULL, NULL);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	memcpy(status, szRecvData, nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}

int WINAPI fnDevCometGetVersion()
{

	BYTE		nRet = DT_SUCCESS;

	return nRet;
}
int WINAPI fnDevCometOpenHV()
{
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	char tmp[2] = { 0 };
	_itoa(1, tmp, 10);

	memcpy(&szSendData[nIndex], tmp, 1);
	nIndex = 1;

	MakeCmdPack(DEV_CMD_HVEN_CODE, szSendData, nIndex);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}
int WINAPI fnDevCometCloseHV()
{
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	char tmp[2] = { 0 };
	_itoa(0, tmp, 10);

	memcpy(&szSendData[nIndex], tmp, 1);
	nIndex = 1;

	MakeCmdPack(DEV_CMD_HVEN_CODE, szSendData, nIndex);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}
int WINAPI fnDevCometCalibrate(int flg)
{

	BYTE		nRet = DT_SUCCESS;

	return nRet;
}

int WINAPI fnDevCometSetkV(char* value, int len)
{
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	memcpy(&szSendData[nIndex], value, len);
	nIndex = len;

	MakeCmdPack(DEV_CMD_HIVO_CODE, szSendData, nIndex);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}
int WINAPI fnDevCometSetmA(char* value, int len)
{
	BYTE		nRet = DT_SUCCESS;

	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	memcpy(&szSendData[nIndex], value, len);
	nIndex = len;

	MakeCmdPack(DEV_CMD_TUCU_CODE, szSendData, nIndex);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));

	return nRet;
}
int WINAPI fnDevCometSetFocsl(char* flg, int len)
{
	BYTE		nRet = DT_SUCCESS;
	CHAR	szRecvData[SENDRECV_BUFFER_LEN] = { 0 };
	CHAR	szSendData[SENDRECV_BUFFER_LEN] = { 0 };
	int		nIndex = 0;

	memcpy(&szSendData[nIndex], flg, len);
	nIndex = len;

	MakeCmdPack(DEV_CMD_FOCSL_CODE, szSendData, nIndex);

	nRet = SendRecvData();

	if (nRet == DT_SUCCESS)
		nRet = ProcRecvData(szRecvData, &nIndex);

	if (nRet == DT_SUCCESS)
		ZxcxLogINFO(_T("(return szRecvDataLen:[%d])"), nIndex);
	else
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
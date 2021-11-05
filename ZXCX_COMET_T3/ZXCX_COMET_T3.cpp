// ZXCX_COMET_T3.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"

ZXCXCOMETT3_API int fnZXCX_COMETT3_Connect(CString ip, DWORD port)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometOpen(ip, port)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_Disconnect(void)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometClose()) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_GetVersion(void)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometGetVersion()) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_Reset(void)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCOmetReset()) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_GetSYSStatus(char* status)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometGetSYSStatus(status)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_GetHVStatus(char* status)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometGetHVStatus(status)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_OpenHV(void)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometOpenHV()) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}
ZXCXCOMETT3_API int fnZXCX_COMETT3_CloseHV(void)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometCloseHV()) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}

ZXCXCOMETT3_API int fnZXCX_COMETT3_Calibrate(int flg)
{
	int nRet = DT_FAILURE;

	if ((nRet = fnDevCometCalibrate(flg)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}

ZXCXCOMETT3_API int fnZXCX_COMETT3_SetkV(char* value)
{
	int nRet = DT_FAILURE;
	int len = strlen(value);

	if ((nRet = fnDevCometSetkV(value, len)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}

ZXCXCOMETT3_API int fnZXCX_COMETT3_SetmA(char* value)
{
	int nRet = DT_FAILURE;
	int len = strlen(value);

	if ((nRet = fnDevCometSetmA(value, len)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}

ZXCXCOMETT3_API int fnZXCX_COMETT3_SetFocsl(char* value)
{
	int nRet = DT_FAILURE;
	int len = strlen(value);

	if ((nRet = fnDevCometSetFocsl(value, len)) != DT_SUCCESS)
	{
		ZxcxLogERROR(_T("(return nRet:[%s])"), GetRtStr(nRet));
		return nRet;
	}

	ZxcxLogINFO(_T("(return nRet:[%s])"), GetRtStr(nRet));
	return nRet;
}

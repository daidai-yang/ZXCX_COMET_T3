#include "pch.h"

CString WINAPI GetRtStr(BYTE code)
{
	CString strResult = _T("");
	switch (code)
	{
	case DT_SUCCESS:
		strResult = _T("DT_SUCCESS");
		break;
	case DT_CLOSEFAIL:
		strResult = _T("DT_CLOSEFAIL");
		break;
	case DT_FAILURE:
		strResult = _T("DT_FAILURE");
		break;
	case DT_ERROR_ALREADYOPEN:
		strResult = _T("DT_ERROR_ALREADYOPEN");
		break;
	case DT_ERROR_LOADLIBRARY:
		strResult = _T("DT_ERROR_LOADLIBRARY");
		break;
	case DT_ERROR_SENDSOCKET:
		strResult = _T("DT_ERROR_SENDSOCKET");
		break;
	case DT_ERROR_WAITSOCKET:
		strResult = _T("DT_ERROR_WAITSOCKET");
		break;
	default:
		strResult = _T("UNKOWN_ERROR_CODE");
		break;
	}
	return strResult;
}

USHORT GetCRCC(BYTE *p, int len)  //Snakyo CRC校验算法,p为校验数组首地址，
{                                        //len为需要校验的数据个数。
	USHORT k, crcc = 0;
	int m, n;

	for (m = 0; m < len; m++)
	{
		k = (USHORT)p[m];
		k <<= 8;

		for (n = 8; n > 0; n--)
		{
			if (((k ^ crcc) & 0x8000) != 0)
				crcc = (USHORT)((crcc << 1) ^ 0x1021);
			else
				crcc <<= 1;
			k <<= 1;
		}
	}

	return crcc;
}

int InitializeDll()
{
	ZxcxLogINFO("");
	BYTE	bRet = DT_SUCCESS;

	g_hMsgWnd = NULL;
	g_pSocketThread = NULL;
	g_hEvent = NULL;
	g_bIsOpen = FALSE;
	g_ProcCmd = NULL;

	g_ip = "192.168.177.199";
	g_nPort = 50505;

	//g_pSocketThread = new CSocketPool();

	if (bRet == DT_SUCCESS)
		ZxcxLogINFO("(return bRet:[%s])", GetRtStr(bRet));
	else
		ZxcxLogERROR("(return bRet:[%s])", GetRtStr(bRet));

	return bRet;
}

bool CheckVersionFw(char *pcVersion)
{
	bool bRet = true;
	char acFilePath[500];
	char *pcEnd = 0;

	//GetModuleFileName (m_hInstance, acFilePath, sizeof (acFilePath));
	for (pcEnd = acFilePath + lstrlen(acFilePath); *(pcEnd - 1) != '.'; pcEnd--);
	lstrcpy(pcEnd, "ini");

	if (GetFileAttributes(acFilePath) != -1)
	{
		char acVersion[50];
		long lTotal = 0;

		bRet = false;
		lTotal = GetPrivateProfileInt("fw_version", "total", 0, acFilePath);
		for (long lIdx = 1; false == bRet && lIdx <= lTotal; lIdx++)
		{
			CString str;

			str.Format("fw_%d", lIdx);
			GetPrivateProfileString("fw_version", str, "", acVersion, sizeof(acVersion), acFilePath);
			bRet = (lstrcmpi(pcVersion, acVersion) == 0);
		}
	}
	return bRet;

}

bool MatchVersionFw(char *pcVersion)
{
	bool bRet = true;
	//char acFilePath[500];
	//char *pcEnd = 0;

	////GetModuleFileName (theApp.m_hInstance, acFilePath, sizeof (acFilePath));
	//for (pcEnd = acFilePath + lstrlen(acFilePath); *(pcEnd - 1) != '.'; pcEnd--);
	//lstrcpy(pcEnd, "ini");

	//if (GetFileAttributes(acFilePath) != -1)
	//{
	//	CString str;
	//	char acVersion[50];
	//	long lCurrent = 0;

	//	lCurrent = GetPrivateProfileInt("fw_version", "current", 0, acFilePath);

	//	str.Format("fw_%d", lCurrent);
	//	GetPrivateProfileString("fw_version", str, "", acVersion, sizeof(acVersion), acFilePath);
	//	bRet = (lstrcmpi(pcVersion, acVersion) == 0);
	//}
	return bRet;
}

void CErrorInfo::SetMTC(BYTE bCode)
{
	//CString	m_strMTCData;
	//BYTE  convertCode[5];

	//memset(m_szMTC, 0x00, sizeof(m_szMTC));
	//memset(m_szMTCDesc, 0x00, sizeof(m_szMTCDesc));
	//memset(convertCode, 0x00, sizeof(convertCode));

	//MakeUnPack(&bCode, convertCode, 1);

	//m_szMTC[0] = MTC_SUB;
	//m_szMTC[1] = MTC_DEVICE;
	//m_szMTC[2] = '0';
	//m_szMTC[3] = convertCode[0];
	//m_szMTC[4] = convertCode[1];

	//m_strMTCData = MTCodeToData(bCode);
	//memcpy(m_szMTCDesc, m_strMTCData, m_strMTCData.GetLength());
}


CString CErrorInfo::MTCodeToData(int errCode)
{
	CString m_strMTCdata = _T("");
	//CString strIniFileName = _T("");
	//char szCurPath[MAX_PATH] = { 0 };
	//char szErrCode[4] = { 0 };
	//MakeUnPack(&errCode, szErrCode, 1);

	//switch (errCode)
	//{
	//case DEV_ERR_IDC_HWERROR_LOW:
	//	m_strMTCdata = _T("Device Hwerror_Low");
	//	break;
	//case DEV_ERR_IDC_RETUIN:
	//	m_strMTCdata = _T("Device Retuin Card");
	//	break;
	//case DEV_ERR_IDC_TIMEOUT:
	//	m_strMTCdata = _T("Device TimeOut");
	//	break;
	//case DEV_ERR_IDC_TYPE:
	//	m_strMTCdata = _T("Device Card Type");
	//	break;
	//case DEV_ERR_IDC_RF:
	//	m_strMTCdata = _T("Device Card Rf Fail");
	//	break;
	//case DEV_ERR_IDC_MOVE:
	//	m_strMTCdata = _T("Device Card Move Fail");
	//	break;
	//case DEV_ERR_IDC_JAM:
	//	m_strMTCdata = _T("Device Card JAM");
	//	break;
	//case DEV_ERR_IDC_MEDIA:
	//	m_strMTCdata = _T("Device Card Media");;
	//	break;
	//case DEV_ERR_IDC_RESET:
	//	m_strMTCdata = _T("Device Reset Fail");;
	//	break;
	//case DEV_ERR_IDC_STATUS:
	//	m_strMTCdata = _T("Device Status Fail");
	//	break;
	//case DEV_ERR_IDC_RFCONTROL:
	//	m_strMTCdata = _T("Device RfControl Fail");;
	//	break;
	//case DEV_ERR_IDC_SCAN:
	//	m_strMTCdata = _T("Device Scan Fail");;
	//	break;
	//case DEV_ERR_IDC_AUTHEN:
	//	m_strMTCdata = _T("Device Authen Fail");;
	//	break;
	//case DEV_ERR_IDC_CALIB:
	//	m_strMTCdata = _T("Device Calib Fail");;
	//	break;
	//case DEV_ERR_IDC_BMP2JPEG:
	//	m_strMTCdata = _T("Device BMP2JPEG Fail");;
	//	break;
	//case DEV_ERR_IDC_UPGRADER:
	//	m_strMTCdata = _T("Device Upgrader Fail");;
	//	break;
	//case DEV_ERR_IDC_SCANLEN:
	//	m_strMTCdata = _T("Device ScanLen Fail");
	//	break;
	//case DT_SUCCESS:
	//	m_strMTCdata = _T("Device Success");
	//	break;
	//case DT_CLOSEFAIL:
	//	m_strMTCdata = _T("Device Close Fail");
	//	break;
	//case DT_FAILURE:
	//	m_strMTCdata = _T("Device Send Recv Fail");
	//	break;
	//case DT_ERROR_ALREADYOPEN:
	//	m_strMTCdata = _T("Device Already Open");
	//	break;
	//case DT_ERROR_LOADLIBRARY:
	//	m_strMTCdata = _T("Device Loadlibrary Fail");
	//	break;
	//default:
	//	m_strMTCdata = _T("Unknown MTC code");
	//	break;
	//}
	return m_strMTCdata;
}
CString WINAPI GetLastSubErr(BYTE code)
{
	CString ErrorMsg = _T("");

	//g_szMTCErrorCode.SetMTC(code);
	//ErrorMsg.Format("%.200s[MTC:%.5s]", g_szMTCErrorCode.m_szMTCDesc, g_szMTCErrorCode.m_szMTC);

	return ErrorMsg;
}


CString GetFileVersion(char* strFileName)
{
	CString strVersion = "";
	DWORD dwLen = GetFileVersionInfoSize(strFileName, NULL);
	ASSERT(dwLen != 0);
	BYTE* pBlock = new BYTE[dwLen + 1];

	ZeroMemory(pBlock, dwLen + 1);
	GetFileVersionInfo(strFileName, 0, dwLen, pBlock);

	VS_FIXEDFILEINFO* pFileInfo;
	UINT uLen = 0;
	VerQueryValue(pBlock, TEXT("\\"), (void**)&pFileInfo, &uLen);

	WORD h_1 = HIWORD(pFileInfo->dwFileVersionMS);
	WORD h_2 = LOWORD(pFileInfo->dwFileVersionMS);
	WORD l_1 = HIWORD(pFileInfo->dwFileVersionLS);
	WORD l_2 = LOWORD(pFileInfo->dwFileVersionLS);
	strVersion.Format("%d.%d.%d.%d", h_1, h_2, l_1, l_2);
	delete[]pBlock;

	return strVersion;
}

CString GetInstanceFolderPath(void)
{
	CString strPath;
	//char tcFullPath[MAX_PATH];

	//GetModuleFileName(g_hInstance, tcFullPath, MAX_PATH);

	//if (0 != GetModuleFileName(g_hInstance, tcFullPath, MAX_PATH - 1))
	//{
	//	tcFullPath[MAX_PATH - 1] = '\0';
	//}

	//TCHAR* p = _tcsrchr(tcFullPath, '\\') + 1;
	//if (p)
	//{
	//	*p = '\0';
	//	strPath = tcFullPath;
	//}

	return strPath;
}

#pragma once

#ifndef DEVICECMD_H
#define DEVICECMD_H



///////////////////////////////////////////////////////////////////////
// COMET DEV COMMAND
///////////////////////////////////////////////////////////////////////
int WINAPI fnDevCometOpen(CString ip, DWORD port);
int WINAPI fnDevCometClose();
int WINAPI fnDevCOmetReset();
int WINAPI fnDevCometGetSYSStatus(char* status);
int WINAPI fnDevCometGetHVStatus(char* status);

int WINAPI fnDevCometGetVersion();
int WINAPI fnDevCometOpenHV(void);
int WINAPI fnDevCometCloseHV(void);
int WINAPI fnDevCometCalibrate(int flg);

int WINAPI fnDevCometSetkV(char* data, int len);
int WINAPI fnDevCometSetmA(char* data, int len);
int WINAPI fnDevCometSetFocsl(char* flg, int len);

int WINAPI MakeCmdPack(BYTE btCmd, char* btPM, int nDataLen);
int WINAPI ProcRecvData(CHAR* pszReturnData, int* pnReturnLen);


#endif

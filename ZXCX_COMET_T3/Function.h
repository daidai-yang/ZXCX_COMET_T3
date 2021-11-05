#pragma once

#ifndef FUNCTION_H
#define  FUNCTION_H

#include <string>
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

BOOL				CreateMsgWnd(HINSTANCE hInst, HWND *phWnd);
int					SendRecvData(long lWaitTime = TIMEOUT_RESPONSE);
void				InitializeSRBuffer();

// Util.cpp
USHORT				GetCRCC(BYTE *p, int len);
int					InitializeDll();

bool				CheckVersionFw(char *pcVersion);
bool				MatchVersionFw(char *pcVersion);

CString				GetFileVersion(char* strFileName);

CString				GetInstanceFolderPath(void);

#endif
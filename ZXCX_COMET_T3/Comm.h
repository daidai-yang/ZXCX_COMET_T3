#pragma once
#include <afx.h>
#define	STRBUFFSIZE			32768


LPCTSTR Strcpy(CString& dBuffc, void* sBuffc);
LPCTSTR Strcpy(CString& dBuffc, void* sBuffc, int slen);
int		Strlen(void* sBuffc);
int		MakePack(void* Src, void* Dest, int Slen, char OperMode = '=', int LowNibbleFlg = FALSE);
int		MakeUnPack(void* Src, void* Dest, int Slen, int AscFlg = TRUE);
int		MakeUnPack(void* Src, CString& Dest, int Slen, int AscFlg = TRUE);
CString	MakeUnPack(void* Src, int Slen, int AscFlg = TRUE);

// testZXCX_COMET_T3.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CtestZXCXCOMETT3App:
// 有关此类的实现，请参阅 testZXCX_COMET_T3.cpp
//

class CtestZXCXCOMETT3App : public CWinApp
{
public:
	CtestZXCXCOMETT3App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CtestZXCXCOMETT3App theApp;

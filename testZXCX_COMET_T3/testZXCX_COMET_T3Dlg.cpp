
// testZXCX_COMET_T3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "testZXCX_COMET_T3.h"
#include "testZXCX_COMET_T3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestZXCXCOMETT3Dlg 对话框



CtestZXCXCOMETT3Dlg::CtestZXCXCOMETT3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TESTZXCX_COMET_T3_DIALOG, pParent)
	, m_szInfo(_T(""))
	, m_port(_T("50505"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestZXCXCOMETT3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INFO, m_szInfo);
	DDX_Text(pDX, IDC_EDIT5, m_port);
}

BEGIN_MESSAGE_MAP(CtestZXCXCOMETT3Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON3, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonGetSYSStatus)
	ON_BN_CLICKED(IDC_BUTTON4, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonGetHVStatus)
	ON_BN_CLICKED(IDC_BUTTON_Setkv, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetkv)
	ON_BN_CLICKED(IDC_BUTTON_SetmA, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetma)
	ON_BN_CLICKED(IDC_BUTTON_SetFocsl, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetfocsl)
	ON_BN_CLICKED(IDC_BUTTON_OpenHV, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonOpenhv)
	ON_BN_CLICKED(IDC_BUTTON_CloseHV, &CtestZXCXCOMETT3Dlg::OnBnClickedButtonClosehv)
END_MESSAGE_MAP()


// CtestZXCXCOMETT3Dlg 消息处理程序

BOOL CtestZXCXCOMETT3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CIPAddressCtrl * ip = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1);
	ip->SetAddress(192,168,177,199);//这里是逗号分开的哦,不是点 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestZXCXCOMETT3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestZXCXCOMETT3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestZXCXCOMETT3Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(tt);
	CString ttport;
	GetDlgItem(IDC_EDIT5)->GetWindowText(ttport);

	int Ret = fnZXCX_COMETT3_Connect(tt, atoi(ttport));
	if (Ret == 0)
	{
		m_szInfo = "打开成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "打开失败！";
		UpdateData(FALSE);
	}
}


void CtestZXCXCOMETT3Dlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	int Ret = fnZXCX_COMETT3_Disconnect();
	if (Ret == 0)
	{
		m_szInfo = "关闭成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "关闭失败！";
		UpdateData(FALSE);
	}
}

void CtestZXCXCOMETT3Dlg::OnBnClickedButtonGetSYSStatus()
{
	// TODO: 在此添加控件通知处理程序代码

	char tmp[1024] = {0};
	CString status;
	int Ret = fnZXCX_COMETT3_GetSYSStatus(tmp);
	if (Ret == 0)
	{
		status.Format("%s", tmp);
		m_szInfo = "获取系统状态成功！" + status;
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "获取系统状态失败！";
		UpdateData(FALSE);
	}
}

void CtestZXCXCOMETT3Dlg::OnBnClickedButtonGetHVStatus()
{
	// TODO: 在此添加控件通知处理程序代码
	char tmp[1024] = { 0 };
	CString status;
	int Ret = fnZXCX_COMETT3_GetHVStatus(tmp);
	if (Ret == 0)
	{
		status.Format("%s", tmp);
		m_szInfo = "获取高压状态成功！" + status;
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "获取高压状态失败！";
		UpdateData(FALSE);
	}
}

void CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetkv()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	GetDlgItem(IDC_EDIT2)->GetWindowText(tt);
	int Ret = fnZXCX_COMETT3_SetkV(tt.GetBuffer(tt.GetLength() + 1));
	if (Ret == 0)
	{
		m_szInfo = "设置电压成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "设置电压失败！";
		UpdateData(FALSE);
	}
}


void CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetma()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	GetDlgItem(IDC_EDIT3)->GetWindowText(tt);
	//CString 转char*
	int Ret = fnZXCX_COMETT3_SetmA(tt.GetBuffer(tt.GetLength()+1));
	if (Ret == 0)
	{
		m_szInfo = "设置电流成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "设置电流失败！";
		UpdateData(FALSE);
	}
}


void CtestZXCXCOMETT3Dlg::OnBnClickedButtonSetfocsl()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	GetDlgItem(IDC_EDIT4)->GetWindowText(tt);
	//CString 转char*
	int Ret = fnZXCX_COMETT3_SetFocsl(tt.GetBuffer(tt.GetLength() + 1));
	if (Ret == 0)
	{
		m_szInfo = "设置焦点成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "设置焦点失败！";
		UpdateData(FALSE);
	}
}


void CtestZXCXCOMETT3Dlg::OnBnClickedButtonOpenhv()
{
	// TODO: 在此添加控件通知处理程序代码
	int Ret = fnZXCX_COMETT3_OpenHV();
	if (Ret == 0)
	{
		m_szInfo = "出束成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "出束失败！";
		UpdateData(FALSE);
	}
}


void CtestZXCXCOMETT3Dlg::OnBnClickedButtonClosehv()
{
	// TODO: 在此添加控件通知处理程序代码
	int Ret = fnZXCX_COMETT3_CloseHV();
	if (Ret == 0)
	{
		m_szInfo = "关束成功！";
		UpdateData(FALSE);
	}
	else
	{
		m_szInfo = "关束失败！";
		UpdateData(FALSE);
	}
}


// TcpClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TcpClient.h"
#include "TcpClientDlg.h"
#include "afxdialogex.h"

#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpClientDlg 对话框



CTcpClientDlg::CTcpClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TCPCLIENT_DIALOG, pParent)
	, m_szInfo(_T(""))
	, SendMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szInfo);
	DDX_Text(pDX, IDC_EDIT_SendMsg, SendMsg);
}

BEGIN_MESSAGE_MAP(CTcpClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OpenClient, &CTcpClientDlg::OnBnClickedButtonOpenclient)
	ON_BN_CLICKED(IDC_BUTTON_CloseClient, &CTcpClientDlg::OnBnClickedButtonCloseclient)
	ON_BN_CLICKED(IDC_BUTTON_SendMsg, &CTcpClientDlg::OnBnClickedButtonSendmsg)
END_MESSAGE_MAP()


// CTcpClientDlg 消息处理程序

BOOL CTcpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTcpClientDlg::OnPaint()
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
HCURSOR CTcpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD ThreadSend(CTcpClientDlg* mytcpSend)
{

	return 0;
}

DWORD ThreadRecv(CTcpClientDlg* mytcpRecv)
{
	while (1)
	{
		char buf[512] = {0};

		recv(mytcpRecv->clientSocket, buf, sizeof(buf), 0);

		if (strlen(buf) > 0)
		{
			CString tmp;
			tmp.Format(buf);
			::SetWindowText(::GetDlgItem(mytcpRecv->m_hWnd, IDC_EDIT1), tmp);
		}
	}
	return 0;
}

void CTcpClientDlg::OnBnClickedButtonOpenclient()
{
	// TODO: 在此添加控件通知处理程序代码
	//客户端
	WORD versionRequired;
	WSADATA wsaData;                            //包含系统所支持的WinStock版本信息
	versionRequired = MAKEWORD(2, 2);           //初始化版本1.1
	int err;
	//注册WinStock，返回状态
	err = WSAStartup(versionRequired, &wsaData);//协议库的版本信息
	if (!err) {                                //返回结果为0表示初始化失败{
		cout << LPSTR("客户端套接字已经打开!\n");
		m_szInfo = "客户端套接字已经打开";
		UpdateData(FALSE);

	}
	else {
		//调用WSAGetLastError()查看错误信息
		cout << ("客户端套接字打开失败：") << WSAGetLastError() << endl;
		m_szInfo = "客户端套接字打开失败";
		UpdateData(FALSE);
		//return 0;//结束
	}

	/*
	创建套接字：
	流式套接字：   SOCK_STREAM , IPPROTO_TCP
	数据报套接字:  SOCK_DGRAM  , IPPROTO_UDP
	*/

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    //创建流式套接字
	SOCKADDR_IN clientsock_in;                                          //专门针对Internet 通信域的Winsock地址结构
	clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");        //通过inet_addr结构指定套接字的主机IP地址 
	clientsock_in.sin_family = AF_INET;                                 //指定协议家族:AF_INET
	clientsock_in.sin_port = htons(3000);                               //指定将要分配给套接字的传输层端口号：6000

	//开始连接
	m_AcceptSocket = connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));
	if (m_AcceptSocket) {
		cout << "与服务端连接失败！程序将退出..." << endl;
		m_szInfo = "与服务端连接失败！程序将退出...";
		UpdateData(FALSE);
	}

	DWORD dwThreadID;
	//HANDLE m_hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadSend, this, 0, &dwThreadID);

	HANDLE m_hThreadRecv = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRecv, this, 0, &dwThreadID);
}


void CTcpClientDlg::OnBnClickedButtonCloseclient()
{
	// TODO: 在此添加控件通知处理程序代码
	//closesocket();
}


void CTcpClientDlg::OnBnClickedButtonSendmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	GetDlgItem(IDC_EDIT_SendMsg)->GetWindowText(tt);

	char tmp[512] = { 0 };
	LPSTR p = tt.GetBuffer();
	strcpy(tmp, p);
	char sendBuf[256] = { 0 };                              //发送的字节

	sprintf_s(sendBuf, "%s", tmp);    //转换函数，将二进制的ip序列转换成char数组
	//在对应的IP处并且将这行字打印到那里
	send(clientSocket, sendBuf, strlen(sendBuf) + 1, 0);
}

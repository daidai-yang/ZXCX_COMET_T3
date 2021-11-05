
// TcpServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TcpServer.h"
#include "TcpServerDlg.h"
#include "afxdialogex.h"

#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<winsock2.h>
#include<string>
#include<stdio.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpServerDlg 对话框



CTcpServerDlg::CTcpServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TCPSERVER_DIALOG, pParent)
	, m_szInfo(_T(""))
	, SendMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szInfo);
	DDX_Text(pDX, IDC_EDIT_SendMsg, SendMsg);
}

BEGIN_MESSAGE_MAP(CTcpServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_StartTCP, &CTcpServerDlg::OnBnClickedButtonStarttcp)
	ON_BN_CLICKED(IDC_BUTTON_CloseTCP, &CTcpServerDlg::OnBnClickedButtonClosetcp)
	ON_BN_CLICKED(IDC_BUTTON_SendMsg, &CTcpServerDlg::OnBnClickedButtonSendmsg)
END_MESSAGE_MAP()


// CTcpServerDlg 消息处理程序

BOOL CTcpServerDlg::OnInitDialog()
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

void CTcpServerDlg::OnPaint()
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
HCURSOR CTcpServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD ThreadServer(CTcpServerDlg* mytcpServer)
{
	while (1)
	{
		//接收客户端传来的信息
		char receiveBuf[512] = {0};

		recv(mytcpServer->serConn, receiveBuf, sizeof(receiveBuf), 0);

		if (strlen(receiveBuf) > 0)
		{
			CString tmp;
			tmp.Format(receiveBuf);
			::SetWindowText(::GetDlgItem(mytcpServer->m_hWnd, IDC_EDIT1), tmp);
			//SetEvent(mytcpServer->m_hEvent);
			mytcpServer->ServerSendMsg();
		}
	}

	return 0;
}

void CTcpServerDlg::ServerSendMsg()
{
	//ResetEvent(m_hEvent);
	CString tt;
	GetDlgItem(IDC_EDIT_SendMsg)->GetWindowText(tt);

	char tmp[512] = { 0 };
	LPSTR p = tt.GetBuffer();
	strcpy(tmp, p);
	char sendBuf[256] = { 0 };                              //发送的字节

	sprintf_s(sendBuf, "server : welcome %s to server. %s", inet_ntoa(clientsocket.sin_addr), tmp);    //转换函数，将二进制的ip序列转换成char数组
	//在对应的IP处并且将这行字打印到那里
	send(serConn, sendBuf, strlen(sendBuf) + 1, 0);
}

void CTcpServerDlg::OnBnClickedButtonStarttcp()
{
	// TODO: 在此添加控件通知处理程序代码
	//服务器端
	//创建套接字
	WORD myVersionRequest;
	WSADATA wsaData;                          //包含系统所支持的winsocket版本信息
	myVersionRequest = MAKEWORD(2, 2);        //初始化版本1.1
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);

	if (!err) {
		cout << "已经打开套接字" << endl;
		m_szInfo = "已经打开套接字";
		UpdateData(FALSE);
	}
	else {
		//进一步绑定套接字
		cout << "套接字未打开" << endl;
		m_szInfo = "套接字未打开";
		UpdateData(FALSE);
	}

	//创建可识别套接字  调用socket函数
	serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//需要绑定的参数
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ip地址
	addr.sin_port = htons(3000);//绑定端口

	//将套接字绑定到指定的网络地址
	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
	//监听连接
	listen(serSocket, 10);                               //第二个参数代表能够接受的最多的连接数

	//while (1) {

		//建立客户端的连接
		int len = sizeof(SOCKADDR);
		//等待客户端的连接
		serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);      //返回一个数字  接受函数，不是-1就是接受连接成功
		cout << "客户端" << inet_ntoa(clientsocket.sin_addr) << "已连接" << endl;             //客户端已连接
		m_szInfo = _T("客户端已连接");
		UpdateData(FALSE);

		DWORD dwThreadID;
		HANDLE m_hThreadWatch = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadServer, this, 0, &dwThreadID);
	//}


		m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}


void CTcpServerDlg::OnBnClickedButtonClosetcp()
{
	// TODO: 在此添加控件通知处理程序代码
	//closesocket(serConn);   //关闭
	WSACleanup();           //释放资源的操作
	ResetEvent(m_hEvent);
	CloseHandle(m_hEvent);
}

void CTcpServerDlg::OnBnClickedButtonSendmsg()
{
	// TODO: 在此添加控件通知处理程序代码

	CString tt;
	GetDlgItem(IDC_EDIT_SendMsg)->GetWindowText(tt);

	char tmp[512] = { 0 };
	LPSTR p  = tt.GetBuffer();
	strcpy(tmp, p);
	char sendBuf[256] = {0};                              //发送的字节
	
	sprintf_s(sendBuf, "server : welcome %s to server. %s", inet_ntoa(clientsocket.sin_addr), tmp);    //转换函数，将二进制的ip序列转换成char数组
	//在对应的IP处并且将这行字打印到那里
	send(serConn, sendBuf, strlen(sendBuf) + 1, 0);
}

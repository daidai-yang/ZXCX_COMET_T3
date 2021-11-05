
// TcpServerDlg.h: 头文件
//

#pragma once


// CTcpServerDlg 对话框
class CTcpServerDlg : public CDialog
{
// 构造
public:
	CTcpServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCPSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStarttcp();
	afx_msg void OnBnClickedButtonClosetcp();
	void ServerSendMsg();

	CString m_szInfo;
	CString SendMsg;
	afx_msg void OnBnClickedButtonSendmsg();
	SOCKET serSocket;
	SOCKET serConn;
	SOCKADDR_IN clientsocket;
	HANDLE m_hEvent;
};

DWORD ThreadServer(CTcpServerDlg* mytcpServer);

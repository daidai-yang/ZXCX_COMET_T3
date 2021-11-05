
// testZXCX_COMET_T3Dlg.h: 头文件
//

#pragma once


// CtestZXCXCOMETT3Dlg 对话框
class CtestZXCXCOMETT3Dlg : public CDialog
{
// 构造
public:
	CtestZXCXCOMETT3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTZXCX_COMET_T3_DIALOG };
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
	CString m_szInfo;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonGetSYSStatus();
	afx_msg void OnBnClickedButtonGetHVStatus();
	afx_msg void OnBnClickedButtonSetkv();
	afx_msg void OnBnClickedButtonSetma();
	afx_msg void OnBnClickedButtonSetfocsl();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButtonOpenhv();
	afx_msg void OnBnClickedButtonClosehv();
	CString m_port;
};

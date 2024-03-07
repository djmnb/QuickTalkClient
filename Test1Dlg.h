
// Test1Dlg.h: 头文件
//

#pragma once
#include "Test1.h"

#pragma comment(lib,"ws2_32.lib")

// CTest1Dlg 对话框
class CTest1Dlg : public CDialogEx
{
// 构造
public:
	CTest1Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CTest1Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST1_DIALOG };
#endif

	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//登录界面配置信息

	string Loginfile = "info.ini";
	
	string Loginfiledir = "user";

	void LoadLoginsetting();

	void SaveLoginsetting();

	int commit();

	SOCKET fd;
	//
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox UserId;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck1();
	CButton RemPwd;
	afx_msg void OnBnClickedCheck2();
	CButton AutoLogin;
	afx_msg void OnCbnSelchangeCombo2();
	CEdit Password;
};

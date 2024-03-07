#pragma once


// CDialogChat 对话框
#define UpDataMsg (WM_USER+105)

class CDialogChat : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChat)

public:
	SOCKET fd;

	mutex Lock;
	string user_name;
	string othername;
	string Msg;

	void setfd(SOCKET fd,string str) {
		this->fd = fd;
		user_name = str;
	}

	void updata() {

		PostMessage(UpDataMsg);


	}
	CDialogChat(string name, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogChat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Chat };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMfcbutton1();
	CEdit sentMessage;
	CEdit recvMessage;
	afx_msg void OnBnClickedButton2();
protected:
	afx_msg LRESULT OnUpdatamsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
};

#pragma once

#define show_chatdialog (WM_USER+123)
// CDialogMenu 对话框

class CDialogMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMenu)

public:

	CDialogMenu(string name,CWnd* pParent = nullptr);   // 标准构造函数

	unordered_map<string, CDialogChat*> mp; // 存储对话框

	SOCKET fd;//用于通信的套接字

	thread* recvmsg;//接收消息线程


	string name;

	string user_name;

	mutex Lock;//线程锁

	void setfd(SOCKET fd,string str) {
		this->fd = fd;
		recvmsg = new thread(&CDialogMenu::Awaysrecvmsg,this);

		user_name = str;
	}

	void creat_chat_window(string name);

	void Awaysrecvmsg();

	virtual ~CDialogMenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Menu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton bt123456;
	CButton bt123;
protected:
	afx_msg LRESULT OnShowChatdialog(WPARAM wParam, LPARAM lParam);
public:
	CEdit other_id;
};

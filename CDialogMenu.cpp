// CDialogMenu.cpp: 实现文件
//

#include <math.h>
#include "pch.h"
#include "Test1.h"
#include "CDialogMenu.h"
#include "afxdialogex.h"



// CDialogMenu 对话框

IMPLEMENT_DYNAMIC(CDialogMenu, CDialogEx)

CDialogMenu::CDialogMenu(string name,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Menu, pParent)
{
	this->name = name;
	
}

void CDialogMenu::creat_chat_window(string name)
{
	CDialogChat* chat;
	if (mp.find(name) == mp.end()) {


		chat = new CDialogChat(name);

		chat->othername = name;
		chat->setfd(fd,user_name);
		chat->Create(IDD_Chat);
		chat->ShowWindow(SW_SHOW);

		mp[name] = chat;

	}
	else {
		chat = mp[name];
		bool bl = chat->IsWindowVisible();
		if (bl == true)return;
		chat->ShowWindow(SW_SHOW);
	}
}

void CDialogMenu::Awaysrecvmsg()
{
	string sp = to_string(BYE);

	while (1) {

		
		char* buff = nullptr;

		if (recvMsg(fd, &buff) == -1) {

			MessageBox(L"与服务器断开连接,请退出重新登录");
			return;
		}
		
		if (string(buff) == sp) {

			delete[]buff;
			break;
		}

		PostMessage(show_chatdialog, (WPARAM)buff);




		//this_thread::yield();
	}

	
}

CDialogMenu::~CDialogMenu()
{
}

void CDialogMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, other_id);
}


BEGIN_MESSAGE_MAP(CDialogMenu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMenu::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CDialogMenu::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogMenu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogMenu::OnBnClickedButton3)
	ON_MESSAGE(show_chatdialog, &CDialogMenu::OnShowChatdialog)
END_MESSAGE_MAP()


// CDialogMenu 消息处理程序


void CDialogMenu::OnBnClickedButton1()
{
	CString info;

	other_id.GetWindowTextW(info);

	string name = _bstr_t(info).operator const char* ();

	creat_chat_window(name);
}


void CDialogMenu::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	string sp = to_string(BYE);

	
	sendMsg(fd, sp.c_str(),sp.length());

	recvmsg->join();
	closesocket(fd);


	CDialogEx::OnClose();
}


void CDialogMenu::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


BOOL CDialogMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	ShowWindow(SW_SHOW);
	// TODO:  在此添加额外的初始化
	SetWindowTextW(CString(name.c_str()));
	//MessageBox(L"输入对方账号即可聊天");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogMenu::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDialogMenu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	creat_chat_window("123");
}


void CDialogMenu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	creat_chat_window("123456");
}


afx_msg LRESULT CDialogMenu::OnShowChatdialog(WPARAM wParam, LPARAM lParam)
{

	const char* buff = (const char*)wParam;

	Json::Value root;
	string errs;
	Json::CharReaderBuilder rr;
	Json::CharReader* rd = rr.newCharReader();
	string str = buff;
	

	bool flag = rd->parse(str.c_str(), str.c_str() + str.size(), &root, &errs);
	if (!flag) {
		return 0;
	}

	string s = root["sendname"].asString();

	string msg = root["msg"].asString();

	string timem = root["date"].asString();

	CDialogChat* chat = nullptr;

	if (mp.find(s) != mp.end()) {

		chat = mp[s];
		bool  flag = chat->IsWindowVisible();

		if (!flag) {
			chat->ShowWindow(SW_SHOW);
		}
	}
	else {

		chat = new CDialogChat(s);

		//chat->SetWindowTextW(CString(s.c_str()));

		chat->othername = s;
		chat->Create(IDD_Chat);
		chat->ShowWindow(SW_SHOW);
		

		chat->setfd(fd, this->user_name);

		mp[s] = chat;
	}

	chat->Msg = str;

	

	

	chat->updata();

	delete[]buff;
	return 0;
}

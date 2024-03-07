// CDialogChat.cpp: 实现文件
//

#include "pch.h"
#include "Test1.h"
#include "CDialogChat.h"
#include "afxdialogex.h"

#if defined(GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored “-Wdeprecated-declarations”
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif



// CDialogChat 对话框

IMPLEMENT_DYNAMIC(CDialogChat, CDialogEx)

CDialogChat::CDialogChat(string name,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Chat, pParent)
{
	othername = name;
}

CDialogChat::~CDialogChat()
{
}

void CDialogChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, sentMessage);
	DDX_Control(pDX, IDC_EDIT3, recvMessage);
}


BEGIN_MESSAGE_MAP(CDialogChat, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogChat::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogChat::OnBnClickedButton2)
	ON_MESSAGE(UpDataMsg, &CDialogChat::OnUpdatamsg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDialogChat 消息处理程序


void CDialogChat::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	//CDialogEx::OnOK();
}


void CDialogChat::OnBnClickedMfcbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogChat::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取待发送消息

	
	

	CString temp;

	sentMessage.GetWindowTextW(temp);

	string  msg = _bstr_t(temp).operator const char* ();


	Json::Value root;
	root["sendname"] = user_name.c_str();
	root["recvname"] = othername.c_str();
	root["msg"] = msg.c_str();

	


	Json::FastWriter ff;
	string str;
	str = ff.write(root);
	sendMsg(fd,str.c_str(), str.length());

	Lock.lock();
	CString app;
	recvMessage.GetWindowTextW(app);
	sentMessage.SetWindowTextW(L"");

	char timet[40];
	time_t t = time(0);

	strftime(timet, sizeof(timet), "%H:%M:%S", localtime(&t));

	recvMessage.SetWindowTextW(app + CString(user_name.c_str())+"   "+ CString(timet) + "\r\n" + temp + "\r\n");

	recvMessage.LineScroll(recvMessage.GetLineCount());
	Lock.unlock();

	//GetDlgCtrl()
	GotoDlgCtrl(GetDlgItem(IDC_EDIT1));

}


afx_msg LRESULT CDialogChat::OnUpdatamsg(WPARAM wParam, LPARAM lParam)
{


	Json::Value root;
	Json::CharReader* rd;
	Json::CharReaderBuilder rr;
	rd = rr.newCharReader();
	string e;
	//fast.write(root);

	rd->parse(Msg.c_str(), Msg.c_str() + Msg.length(), &root, &e);
   

	Lock.lock();
	CString app;
	recvMessage.GetWindowTextW(app);


	recvMessage.SetWindowTextW(app  + CString(othername.c_str()) + "   "
		+ CString(root["date"].asString().c_str()) +"\r\n" +CString(root["msg"].asString().c_str()) + "\r\n");
	recvMessage.LineScroll(recvMessage.GetLineCount());

	Lock.unlock();

	return 0;
}


void CDialogChat::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->ShowWindow(SW_HIDE);
	//CDialogEx::OnClose();
}


BOOL CDialogChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(CString(othername.c_str()));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// Test1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Test1.h"
#include "Test1Dlg.h"
#include "afxdialogex.h"
#include "RegistDialogt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest1Dlg 对话框



CTest1Dlg::CTest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST1_DIALOG, pParent)
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WSADATA data;

	WSAStartup(MAKEWORD(2, 2), &data);

	

}

CTest1Dlg::~CTest1Dlg()
{
	WSACleanup();
}

void CTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, UserId);
	DDX_Control(pDX, IDC_CHECK1, RemPwd);
	DDX_Control(pDX, IDC_CHECK2, AutoLogin);
	DDX_Control(pDX, IDC_EDIT2, Password);
}

void CTest1Dlg::LoadLoginsetting()
{
	ifstream out(Loginfiledir +"/" +Loginfile);

	if (!out.is_open())return;


	string name;
	out >> name;

	//加载账号
	UserId.SetWindowTextW(CString(name.c_str()));

	//加载密码
	out >> name;
	Password.SetWindowTextW(CString(name.c_str()));

	//加载选项
	bool flag;
    
	out >> flag;
	RemPwd.SetCheck(flag);

	out >> flag;
	AutoLogin.SetCheck(flag);

	out.close();



}

void CTest1Dlg::SaveLoginsetting()
{
	ofstream out(Loginfiledir +"/"+ Loginfile);

	if (!out.is_open()) {
		string str = string("mkdir ") + Loginfiledir;
		system(str.c_str());

		out.open(Loginfiledir + "/" + Loginfile);
		if (!out.is_open())return;
	}

	

	CString str1;

	string str;

	UserId.GetWindowTextW(str1);
	

	str = _bstr_t(str1).operator const char* ();
	
	out << str<<" ";

	Password.GetWindowTextW(str1);

	str = _bstr_t(str1).operator const char* ();
	out << str<< " ";

	bool flag;

	flag = RemPwd.GetCheck();
    out << flag << " ";

	flag = AutoLogin.GetCheck();
	out << flag << " ";

	out.close();
}

int CTest1Dlg::commit()
{
	

	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	sockaddr_in addr;

	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, ipaddr, &addr.sin_addr.S_un.S_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10007);

	int flag = connect(fd, (sockaddr*)&addr, sizeof(addr));

	if (flag < 0) {
		MessageBox(L"连接服务器失败,请检查网络状态", L"错误");
		closesocket(fd);
		return -1;
	}
	
	string t = to_string(LOGIN);
	sendMsg(fd, t.c_str(), t.length());

	CString temp;

	UserId.GetWindowTextW(temp);

	string id = _bstr_t(temp).operator const char* ();
	
	user_name = string(id);

	
	sendMsg(fd, id.data(), id.length());

	Password.GetWindowTextW(temp);

	string pwd = _bstr_t(temp).operator const char* ();

	user_passwd = string(pwd);

	sendMsg(fd, pwd.data(), pwd.length());

	char* buff = nullptr;
	recvMsg(fd, (char**)&buff);

	

	if (buff == nullptr) {
		closesocket(fd);
		return -1;
	}
	flag = string(buff) == string("1");
	delete[]buff;

	return flag;
}

BEGIN_MESSAGE_MAP(CTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTest1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CTest1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTest1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &CTest1Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTest1Dlg::OnBnClickedCheck2)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTest1Dlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CTest1Dlg 消息处理程序

BOOL CTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//RemPwd.SetCheck(true);
	//RemPwd.set
	//Password.SetWindowTextW(L"12345");

	LoadLoginsetting();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//登录账号所用函数
void CTest1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	

	//判断账号密码是否正确，向服务器端请求
	SaveLoginsetting();

	int n = commit();

	//MessageBox(CString(user_name.c_str()));
	if (n == 1) {
		MessageBox(L"登录成功");

		CDialogEx::OnOK();

		CDialogMenu menu(user_name);
		
		
		menu.setfd(fd,user_name);

		//menu.SetWindowTextW(CString(user_name.c_str()));

		menu.DoModal();

	}
	else if(n==0){
		MessageBox(L"账号或者密码错误");
		
	}
	//MessageBox(L"hello");

	//更新登录页面的选项
	
	//CDialogEx::OnOK();
}


//注册账号所用函数
void CTest1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	RegistDialogt box;

	box.DoModal();
}



//忘记密码所用函数

void CTest1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	MessageBox(L"此功能暂时还未开放");

}


void CTest1Dlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTest1Dlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTest1Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"hello");
}

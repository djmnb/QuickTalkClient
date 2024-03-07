// RegistDialogt.cpp: 实现文件
//

#include "pch.h"
#include "Test1.h"
#include "RegistDialogt.h"
#include "afxdialogex.h"
#include "DataTran.h"

// RegistDialogt 对话框

IMPLEMENT_DYNAMIC(RegistDialogt, CDialogEx)

RegistDialogt::RegistDialogt(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST1_DIALOG1, pParent)
	, registname(0)
	, registpasswd(_T(""))
{

	//  registname = 0;
}

RegistDialogt::~RegistDialogt()
{

}

void RegistDialogt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, registname);
	DDX_Text(pDX, IDC_EDIT2, registpasswd);
	DDV_MaxChars(pDX, registpasswd, 15);
}


BEGIN_MESSAGE_MAP(RegistDialogt, CDialogEx)
	ON_BN_CLICKED(IDOK, &RegistDialogt::OnBnClickedOk)
END_MESSAGE_MAP()


// RegistDialogt 消息处理程序


void RegistDialogt::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

		UpdateData(true);

		if (registname == 0 ) {
			MessageBox(L"请输入账号");
			return;
		}
		else if (registpasswd.GetLength() <= 0) {
			MessageBox(L"请输入密码");
			return;
		}
		

		

		SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


		sockaddr_in addr;
		inet_pton(AF_INET, ipaddr, &addr.sin_addr.S_un.S_addr);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(10007);

		int flag = connect(fd, (sockaddr*)&addr, sizeof(addr));

		if (flag < 0) {
			MessageBox(L"连接服务器失败,请检查网络状态", L"错误");
			closesocket(fd);
			return ;
		}

		string t = to_string(REGIST);
		sendMsg(fd, t.c_str(), t.length());

		string name = to_string(registname);
		string passwd = _bstr_t(registpasswd).operator const char* ();

		sendMsg(fd, name.c_str(), name.length());
		sendMsg(fd, passwd.c_str(), passwd.length());

		char* buff = nullptr;

		if (recvMsg(fd, &buff) == -1) {

			MessageBox(L"服务器异常");
			closesocket(fd);
			return;
		}

		closesocket(fd);

		if (string(buff) == string("1")) {
			MessageBox(L"注册成功");
			CDialogEx::OnOK();
		}
		else {
			MessageBox(L"此账号已经存在");
		}
}

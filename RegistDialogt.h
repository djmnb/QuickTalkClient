#pragma once


// RegistDialogt 对话框

class RegistDialogt : public CDialogEx
{
	DECLARE_DYNAMIC(RegistDialogt)

public:
	RegistDialogt(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RegistDialogt();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST1_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	long registname;
	int registname;
	CString registpasswd;
	afx_msg void OnBnClickedOk();
};

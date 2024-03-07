
// Test1.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include<iostream>
#include <Windows.h>
#include <WinSock2.h>
#include<fstream>
#include<thread>
#include<string>

#include<unordered_map>
#include<mutex>
#include"DataTran.h"
#include"CDialogChat.h" 
#include "CDialogMenu.h"



//static const char* ipaddr = "123.57.212.102";
static const char* ipaddr = "127.0.0.1";

using namespace std;




// CTest1App:
// 有关此类的实现，请参阅 Test1.cpp
//

class CTest1App : public CWinApp
{
public:
	CTest1App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTest1App theApp;

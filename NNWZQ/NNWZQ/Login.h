#pragma once


// CLogin 对话框
#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedBtnRegist();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnQuit();

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_objEditLoginName;
	CEdit m_objEditLoginPassword;
};

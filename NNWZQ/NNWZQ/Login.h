#pragma once


// CLogin �Ի���
#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

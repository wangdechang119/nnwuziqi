// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "NNWZQ.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN_NAME, m_objEditLoginName);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PASSWORD, m_objEditLoginPassword);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_REGIST, &CLogin::OnBnClickedBtnRegist)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CLogin::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CLogin::OnBnClickedBtnQuit)
END_MESSAGE_MAP()


// CLogin 消息处理程序
BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_objEditLoginName.SetLimitText(32);
	m_objEditLoginPassword.SetLimitText(32);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogin::OnOK()
{
	OnBnClickedBtnLogin();
}

void CLogin::OnBnClickedBtnRegist()
{
	// TODO: 在此添加控件通知处理程序代码
	char strURL[1024] = { 0 };
	sprintf(strURL, "http://www.gnxxkj.com/app/wuziqi/register.php");
	CString wstrURL(strURL);
	ShellExecute(0, NULL, wstrURL, NULL, NULL, SW_NORMAL); //在外部打开网页
}

void CLogin::OnBnClickedBtnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName, strPsw;
	m_objEditLoginName.GetWindowText(strName);
	m_objEditLoginPassword.GetWindowText(strPsw);
	strName.Trim();
	strPsw.Trim();
	if (strName.IsEmpty() || strName.Find(_T("&")) >= 0 || strName.Find(_T("=")) >= 0 || strName.Find(_T("+")) >= 0)
	{
		MessageBox(_T("用户名错误"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (strPsw.IsEmpty() || strPsw.Find(_T("&")) >= 0 || strPsw.Find(_T("=")) >= 0 || strPsw.Find(_T("+")) >= 0)
	{
		MessageBox(_T("密码错误"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	char cstrName[255] = { 0 };
	char cstrPsw[255] = { 0 };
	int nLen = 0;
	nLen = WideCharToMultiByte(CP_ACP, 0, strName, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strName, -1, cstrName, nLen, NULL, NULL);
	nLen = WideCharToMultiByte(CP_ACP, 0, strPsw, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strPsw, -1, cstrPsw, nLen, NULL, NULL);
	if (!Login(cstrName, cstrPsw))
	{
		MessageBox(_T("用户名或密码错误，请在网络畅通的情况下重新输入"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	CDialog::OnOK();
}


void CLogin::OnBnClickedBtnQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
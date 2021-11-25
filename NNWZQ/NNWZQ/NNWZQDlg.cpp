
// NNWZQDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NNWZQ.h"
#include "NNWZQDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include <mmsystem.h>		//导入声音头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNNWZQDlg 对话框

#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")



CNNWZQDlg::CNNWZQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NNWZQ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNNWZQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOARD, m_objBoard);
}

BEGIN_MESSAGE_MAP(CNNWZQDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CNNWZQDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_START, &CNNWZQDlg::OnBnClickedBtnStart)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CNNWZQDlg 消息处理程序

BOOL CNNWZQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_bLogged = false;
	if (!InitFromModelFile("model.mod"))	//使用模型文件初始化
		InitWithoutModelFile(15, 15, 5);	//初始化棋盘大小为15x15，五连子获胜（即五子棋）

	m_bStarted = false;
	m_bHumanPlay = false;
	Show();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNNWZQDlg::OnPaint()
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

		Show();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNNWZQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNNWZQDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SaveModel("model.mod"))		//保存当前已经学习出的模型，供后续初始化使用，以便不断学习进化
		AfxMessageBox(_T("模型已成功保存"));
}


void CNNWZQDlg::Show()
{
	CRect rect;
	CRect rc;
	GetClientRect(&rect);
	CWnd* pBtn = GetDlgItem(IDC_BTN_START);
	if (pBtn != NULL)
		pBtn->GetClientRect(&rc);

	rect.right -= rc.right*1.5;
	CWnd* pBoard = GetDlgItem(IDC_BOARD);
	if (pBoard != NULL)
		pBoard->MoveWindow(&rect);

	DrawBoard(&m_objBoard);
	DrawPieces(&m_objBoard);
}

bool CNNWZQDlg::Login()
{
	return true;
}

void CNNWZQDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bLogged)
	{
		CLogin objLogin;
		if (objLogin.DoModal() != IDOK)
		{
			MessageBox(_T("请先登录"), _T("温馨提醒"));
			return;
		}
		m_bLogged = true;
	}

	StartNewGame();
	Invalidate(TRUE);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(true);

	m_bStarted = true;
	if (!SetPieceByAIAndShow(&m_objBoard))
	{
		AfxMessageBox(_T("积分不足或网络问题，请确保网络畅通且积分充足（若是积分不足，充值后可继续本次对局）"));
	}
	else 
	{
		m_bHumanPlay = true;
	}
}

void CNNWZQDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	m_objBoard.GetClientRect(&rect);
	if (rect.PtInRect(point))
	{
		if (!m_bStarted)
		{
			MessageBox(_T("请先点击开始新游戏"), _T("温馨提示"), MB_OK | MB_ICONHAND);
		}
		else if (m_bHumanPlay)
		{
			if (SetPieceWithGUI(&m_objBoard, point.x, point.y))
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(), SND_RESOURCE | SND_ASYNC);
				m_bHumanPlay = false;
				if (IsGameOver())
				{
					m_bStarted = false;
					switch (GetWinner())
					{
					case -1:
						MessageBox(_T("很遗憾，您输了"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
						break;
					case 1:
						MessageBox(_T("恭喜，您赢了"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
						break;
					default:	//0
						AfxMessageBox(_T("平局"));
						break;
					}
				}
				else 
				{
					Sleep(500);
					if (!SetPieceByAIAndShow(&m_objBoard))
					{
						AfxMessageBox(_T("积分不足或网络问题，请确保网络畅通且积分充足（若是积分不足，充值后可继续本次对局）"));
					}
					else 
					{
						PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(), SND_RESOURCE | SND_ASYNC);
						m_bHumanPlay = true;
					}
				}
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

BOOL CNNWZQDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint pos;
	GetCursorPos(&pos);		//在整个屏幕上的坐标
	CRect rc;
	GetDlgItem(IDC_BOARD)->GetWindowRect(&rc);	//在整个屏幕上的坐标
	if (rc.PtInRect(pos))
	{
		if (m_bStarted && m_bHumanPlay)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));	//设置成手状，也可在OnMouseMove()中调用
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		return TRUE;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


// NNWZQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NNWZQ.h"
#include "NNWZQDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include <mmsystem.h>		//��������ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNNWZQDlg �Ի���

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


// CNNWZQDlg ��Ϣ�������

BOOL CNNWZQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_bLogged = false;
	if (!InitFromModelFile("model.mod"))	//ʹ��ģ���ļ���ʼ��
		InitWithoutModelFile(15, 15, 5);	//��ʼ�����̴�СΪ15x15�������ӻ�ʤ���������壩

	m_bStarted = false;
	m_bHumanPlay = false;
	Show();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNNWZQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		Show();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNNWZQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNNWZQDlg::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (SaveModel("model.mod"))		//���浱ǰ�Ѿ�ѧϰ����ģ�ͣ���������ʼ��ʹ�ã��Ա㲻��ѧϰ����
		AfxMessageBox(_T("ģ���ѳɹ�����"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_bLogged)
	{
		CLogin objLogin;
		if (objLogin.DoModal() != IDOK)
		{
			MessageBox(_T("���ȵ�¼"), _T("��ܰ����"));
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
		AfxMessageBox(_T("���ֲ�����������⣬��ȷ�����糩ͨ�һ��ֳ��㣨���ǻ��ֲ��㣬��ֵ��ɼ������ζԾ֣�"));
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
			MessageBox(_T("���ȵ����ʼ����Ϸ"), _T("��ܰ��ʾ"), MB_OK | MB_ICONHAND);
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
						MessageBox(_T("���ź���������"), _T("��ܰ��ʾ"), MB_OK | MB_ICONINFORMATION);
						break;
					case 1:
						MessageBox(_T("��ϲ����Ӯ��"), _T("��ܰ��ʾ"), MB_OK | MB_ICONINFORMATION);
						break;
					default:	//0
						AfxMessageBox(_T("ƽ��"));
						break;
					}
				}
				else 
				{
					Sleep(500);
					if (!SetPieceByAIAndShow(&m_objBoard))
					{
						AfxMessageBox(_T("���ֲ�����������⣬��ȷ�����糩ͨ�һ��ֳ��㣨���ǻ��ֲ��㣬��ֵ��ɼ������ζԾ֣�"));
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
	GetCursorPos(&pos);		//��������Ļ�ϵ�����
	CRect rc;
	GetDlgItem(IDC_BOARD)->GetWindowRect(&rc);	//��������Ļ�ϵ�����
	if (rc.PtInRect(pos))
	{
		if (m_bStarted && m_bHumanPlay)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));	//���ó���״��Ҳ����OnMouseMove()�е���
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		return TRUE;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

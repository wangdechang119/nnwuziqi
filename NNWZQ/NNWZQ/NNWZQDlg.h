
// NNWZQDlg.h : 头文件
//

#pragma once


// CNNWZQDlg 对话框
class CNNWZQDlg : public CDialogEx
{
// 构造
public:
	CNNWZQDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NNWZQ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()

public:
	void Show();
	bool Login();

public:
	CStatic m_objBoard;		//画图控件
	bool m_bLogged;		//是否已登录

	bool m_bStarted;	//游戏是否已经开始
	bool m_bHumanPlay;	//是否该人/挑战者落子
};

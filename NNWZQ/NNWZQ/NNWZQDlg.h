
// NNWZQDlg.h : ͷ�ļ�
//

#pragma once


// CNNWZQDlg �Ի���
class CNNWZQDlg : public CDialogEx
{
// ����
public:
	CNNWZQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NNWZQ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CStatic m_objBoard;		//��ͼ�ؼ�
	bool m_bLogged;		//�Ƿ��ѵ�¼

	bool m_bStarted;	//��Ϸ�Ƿ��Ѿ���ʼ
	bool m_bHumanPlay;	//�Ƿ����/��ս������
};

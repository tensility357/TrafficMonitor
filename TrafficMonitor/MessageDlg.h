#pragma once
#include "afxwin.h"

// CMessageDlg �Ի���

class CMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageDlg();

	void SetWindowTitle(LPCTSTR str);
	void SetInfoText(LPCTSTR str);
	void SetMessageText(LPCTSTR str);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAGE_DIALOG };
#endif

protected:
	CEdit m_message_edit;
	CSize m_min_size;		//���ڵ���С��С
	CStatic m_info_static;

	CString m_title;
	CString m_info;
	CString m_message;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

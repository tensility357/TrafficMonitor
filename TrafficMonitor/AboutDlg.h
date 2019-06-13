#pragma once
#include "DonateDlg.h"
#include "LinkStatic.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������

protected:
	CPictureStatic m_about_img;		//���ڶԻ����е�ͼƬ
	CLinkStatic m_mail;				//����ϵ���ߡ�������
	CLinkStatic m_acknowledgement;	//����л��������
	CLinkStatic m_github;			//��GitHub��������
	CLinkStatic m_donate;			//��������������
	CToolTipCtrl m_tool_tip;			//���ָ��ʱ�Ĺ�����ʾ
	CLinkStatic m_translaotr_static;

	//��������
	//DPI�趨Ϊ100%ʱ�Ĵ�С
	const int m_width{ theApp.DPI(305) };
	const int m_height{ theApp.DPI(174) };
	const int m_pic_height{ theApp.DPI(65) };
	//DPI�趨����100%ʱ�Ĵ�С
	const int m_width2{ theApp.DPI(319) };
	const int m_height2{ theApp.DPI(164) };
	const int m_pic_height2{ theApp.DPI(61) };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString GetDonateList();		//����Դ�ļ����ؾ�����Ա����

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//	afx_msg void OnStnClickedStaticDonate();
protected:
	afx_msg LRESULT OnLinkClicked(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
};

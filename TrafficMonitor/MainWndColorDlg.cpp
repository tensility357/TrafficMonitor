// MainWndColorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "MainWndColorDlg.h"
#include "afxdialogex.h"
#include "CMFCColorDialogEx.h"


// CMainWndColorDlg �Ի���

IMPLEMENT_DYNAMIC(CMainWndColorDlg, CDialog)

CMainWndColorDlg::CMainWndColorDlg(COLORREF colors[MAIN_WND_COLOR_NUM], CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAIN_COLOR_DIALOG, pParent)
{
	for (int i{}; i < MAIN_WND_COLOR_NUM; i++)
		m_colors[i] = colors[i];
}

CMainWndColorDlg::~CMainWndColorDlg()
{
}

void CMainWndColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UP_STATIC, m_statics[0]);
	DDX_Control(pDX, IDC_DOWN_STATIC, m_statics[1]);
	DDX_Control(pDX, IDC_CPU_STATIC, m_statics[2]);
	DDX_Control(pDX, IDC_MEMORY_STATIC, m_statics[3]);
}


BEGIN_MESSAGE_MAP(CMainWndColorDlg, CDialog)
	ON_MESSAGE(WM_STATIC_CLICKED, &CMainWndColorDlg::OnStaticClicked)
END_MESSAGE_MAP()


// CMainWndColorDlg ��Ϣ�������


BOOL CMainWndColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i{}; i < MAIN_WND_COLOR_NUM; i++)
	{
		m_statics[i].SetFillColor(m_colors[i]);
		m_statics[i].SetLinkCursor();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


afx_msg LRESULT CMainWndColorDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	int item_id = ::GetDlgCtrlID(((CWnd*)wParam)->m_hWnd);
	int index{};
	switch (item_id)
	{
	case IDC_UP_STATIC:
		index = 0;
		break;
	case IDC_DOWN_STATIC:
		index = 1;
		break;
	case IDC_CPU_STATIC:
		index = 2;
		break;
	case IDC_MEMORY_STATIC:
		index = 3;
		break;
	default:
		return 0;
	}

	CMFCColorDialogEx colorDlg(m_colors[index], 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_colors[index] = colorDlg.GetColor();
		m_statics[index].SetFillColor(m_colors[index]);
	}
	return 0;
}

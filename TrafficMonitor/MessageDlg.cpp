// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessageDlg.h"


// CMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CMessageDlg, CDialog)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MESSAGE_DIALOG, pParent)
{

}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::SetWindowTitle(LPCTSTR str)
{
	m_title = str;
}

void CMessageDlg::SetInfoText(LPCTSTR str)
{
	m_info = str;
}

void CMessageDlg::SetMessageText(LPCTSTR str)
{
	m_message = str;
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HELP_EDIT, m_message_edit);
	DDX_Control(pDX, IDC_INFO_STATIC, m_info_static);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CMessageDlg ��Ϣ�������


BOOL CMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);		// ����Сͼ��

	//��ȡ��ʼʱ���ڵĴ�С
	CRect rect;
	GetWindowRect(rect);
	m_min_size.cx = rect.Width();
	m_min_size.cy = rect.Height();

	SetWindowText(m_title);
	m_info_static.SetWindowText(m_info);
	m_message_edit.SetWindowText(m_message);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMessageDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ƴ�����С��С
	lpMMI->ptMinTrackSize.x = m_min_size.cx;		//������С���
	lpMMI->ptMinTrackSize.y = m_min_size.cy;		//������С�߶�

	CDialog::OnGetMinMaxInfo(lpMMI);
}

// OptionsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "OptionsDlg.h"
#include "afxdialogex.h"


// COptionsDlg �Ի���

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)

COptionsDlg::COptionsDlg(int tab, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTIONS_DIALOG, pParent), m_tab_selected{ tab }
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
END_MESSAGE_MAP()


// COptionsDlg ��Ϣ�������


BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(CCommon::LoadText(IDS_TITLE_OPTION));

	//�����ӶԻ���
	m_tab1_dlg.Create(IDD_MAIN_WND_SETTINGS_DIALOG, &m_tab);
	m_tab2_dlg.Create(IDD_TASKBAR_SETTINGS_DIALOG, &m_tab);
	m_tab3_dlg.Create(IDD_GENERAL_SETTINGS_DIALOG, &m_tab);

	//��ӶԻ���
	m_tab.AddWindow(&m_tab1_dlg, CCommon::LoadText(IDS_MAIN_WINDOW_SETTINGS));
	m_tab.AddWindow(&m_tab2_dlg, CCommon::LoadText(IDS_TASKBAR_WINDOW_SETTINGS));
	m_tab.AddWindow(&m_tab3_dlg, CCommon::LoadText(IDS_GENERAL_SETTINGS));

	//����Ĭ��ѡ�еı�ǩ
	m_tab.SetCurTab(m_tab_selected);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void COptionsDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_tab1_dlg.OnOK();
	m_tab2_dlg.OnOK();
	m_tab3_dlg.OnOK();

	CDialog::OnOK();
}

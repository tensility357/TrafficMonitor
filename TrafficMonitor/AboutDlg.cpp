#include "stdafx.h"
#include "TrafficMonitor.h"
#include "AboutDlg.h"
#include "MessageDlg.h"

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_STN_CLICKED(IDC_STATIC_DONATE, &CAboutDlg::OnStnClickedStaticDonate)
	ON_MESSAGE(WM_LINK_CLICKED, &CAboutDlg::OnLinkClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ABOUT, m_about_img);
	DDX_Control(pDX, IDC_STATIC_MAIL, m_mail);
	DDX_Control(pDX, IDC_STATIC_ACKNOWLEDGEMENT, m_acknowledgement);
	DDX_Control(pDX, IDC_STATIC_GITHUB, m_github);
	DDX_Control(pDX, IDC_STATIC_DONATE, m_donate);
	DDX_Control(pDX, IDC_TRANSLATOR_STATIC, m_translaotr_static);
}

CString CAboutDlg::GetDonateList()
{
	CString donate_list;
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_ACKNOWLEDGEMENT_TEXT), _T("TEXT"));
	if (hRes != NULL)
	{
		HGLOBAL hglobal = LoadResource(NULL, hRes);
		if (hglobal != NULL)
			donate_list.Format(_T("%s"), (LPVOID)hglobal);
	}
	return donate_list;
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(CCommon::LoadText(IDS_TITLE_ABOUT));
	CRect window_rect{};
	if (theApp.DPI(100) < 125)
	{
		window_rect.right = m_width;
		window_rect.bottom = m_height;
		AdjustWindowRectEx(window_rect, GetStyle(), FALSE, GetExStyle());		//���ͻ�����Сת���ɴ��ڴ�С
		SetWindowPos(nullptr, 0, 0, window_rect.Width(), window_rect.Height(), SWP_NOZORDER | SWP_NOMOVE);
		m_about_img.SetWindowPos(nullptr, 0, 0, m_width, m_pic_height, SWP_NOZORDER | SWP_NOMOVE);
		m_about_img.SetPicture(IDB_ABOUT_BACKGROUND);
	}
	else
	{
		window_rect.right = m_width2;
		window_rect.bottom = m_height2;
		AdjustWindowRectEx(window_rect, GetStyle(), FALSE, GetExStyle());		//���ͻ�����Сת���ɴ��ڴ�С
		SetWindowPos(nullptr, 0, 0, window_rect.Width(), window_rect.Height(), SWP_NOZORDER | SWP_NOMOVE);
		m_about_img.SetWindowPos(nullptr, 0, 0, m_width2, m_pic_height2, SWP_NOZORDER | SWP_NOMOVE);
		m_about_img.SetPicture(IDB_ABOUT_BACKGROUND_HD);
	}
	m_mail.SetURL(_T("mailto:zhongyang219@hotmail.com"));	//���ó�����
															//m_check_update.SetURL(_T("http://pan.baidu.com/s/1c1LkPQ4"));
	m_github.SetURL(_T("https://github.com/zhongyang219/TrafficMonitor"));
	m_donate.SetLinkIsURL(false);
	m_acknowledgement.SetLinkIsURL(false);

	//���ð汾��Ϣ
	CString version_info;
	GetDlgItemText(IDC_STATIC_VERSION, version_info);
	version_info.Replace(_T("<version>"), VERSION);

#ifdef COMPILE_FOR_WINXP
	version_info += _T(" (For WinXP)");
#endif // COMPILE_FOR_WINXP

#ifdef _M_X64
	version_info += _T(" (x64)");
#endif

#ifdef _DEBUG
	version_info += _T(" (Debug)");
#endif

	SetDlgItemText(IDC_STATIC_VERSION, version_info);

	//��������������
	CString temp_str;
	GetDlgItemText(IDC_STATIC_COPYRIGHT, temp_str);
	temp_str.Replace(_T("<compile_date>"), COMPILE_DATE);
	SetDlgItemText(IDC_STATIC_COPYRIGHT, temp_str);

	m_tool_tip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX);
	m_tool_tip.AddTool(&m_mail, CCommon::LoadText(IDS_SEND_EMAIL_TO_ATHOUR, _T("\r\nmailto:zhongyang219@hotmail.com")));
	//m_tool_tip.AddTool(&m_check_update, _T("���ٶ��������Ӳ鿴�Ƿ��и���\r\nhttp://pan.baidu.com/s/1c1LkPQ4"));
	m_tool_tip.AddTool(&m_github, CCommon::LoadText(IDS_GOTO_GITHUB, _T("\r\nhttps://github.com/zhongyang219/TrafficMonitor")));
	m_tool_tip.AddTool(&m_donate, CCommon::LoadText(IDS_DONATE_ATHOUR));
	m_tool_tip.SetDelayTime(300);	//�����ӳ�
	m_tool_tip.SetMaxTipWidth(800);

	//���÷�������Ϣ
	int language_code;
	language_code = _ttoi(CCommon::LoadText(IDS_LANGUAGE_CODE));
	if (language_code == 1 || language_code == 2)		//�����Ǽ������ĺ�Ӣ��ʱ����ʾ��������Ϣ
		m_translaotr_static.ShowWindow(SW_HIDE);
	if (language_code == 3)		//��ʾ�������ķ����ߵ���Ϣ
	{
		m_translaotr_static.SetURL(_T("http://mkvq.blogspot.com/"));
		m_tool_tip.AddTool(&m_translaotr_static, CCommon::LoadText(IDS_CONTACT_TRANSLATOR, _T("\r\nhttp://mkvq.blogspot.com/")));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
		m_tool_tip.RelayEvent(pMsg);

	//if (pMsg->message == WM_KEYDOWN)
	//{
	//	if ((GetKeyState(VK_CONTROL) & 0x80) && (GetKeyState(VK_SHIFT) & 0x8000) && pMsg->wParam == 'Z')
	//	{
	//		//���Գ������
	//		CString* pStr = nullptr;
	//		int a = pStr->GetLength();
	//		printf("%d", a);
	//	}
	//}

	return CDialog::PreTranslateMessage(pMsg);
}

//void CAboutDlg::OnStnClickedStaticDonate()
//{
//	CDonateDlg donateDlg;
//	donateDlg.DoModal();
//}

afx_msg LRESULT CAboutDlg::OnLinkClicked(WPARAM wParam, LPARAM lParam)
{
	CWnd* pCtrl = (CWnd*)wParam;
	if (pCtrl == &m_donate)
	{
		CDonateDlg donateDlg;
		donateDlg.DoModal();
	}
	else if (pCtrl == &m_acknowledgement)
	{
		CString strContent = GetDonateList();
		strContent += _T("\r\n");
		strContent += CCommon::LoadText(IDS_ACKNOWLEDGEMENT_EXPLAIN);
		CMessageDlg dlg;
		dlg.SetWindowTitle(CCommon::LoadText(IDS_TITLE_ACKNOWLEDGEMENT));
		dlg.SetInfoText(CCommon::LoadText(IDS_THANKS_DONORS));
		dlg.SetMessageText(strContent);
		dlg.DoModal();
	}

	return 0;
}


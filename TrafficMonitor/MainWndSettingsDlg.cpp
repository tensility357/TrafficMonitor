// MainWndSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "MainWndSettingsDlg.h"
#include "afxdialogex.h"
#include "CMFCColorDialogEx.h"

// CMainWndSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CMainWndSettingsDlg, CTabDlg)

CMainWndSettingsDlg::CMainWndSettingsDlg(CWnd* pParent /*=NULL*/)
	: CTabDlg(IDD_MAIN_WND_SETTINGS_DIALOG, pParent)
{

}

CMainWndSettingsDlg::~CMainWndSettingsDlg()
{
}

void CMainWndSettingsDlg::DrawStaticColor()
{
	//CCommon::FillStaticColor(m_color_static, m_data.text_color);
	if (m_data.specify_each_item_color)
	{
		m_color_static.SetColorNum(MAIN_WND_COLOR_NUM);
		for(int i{}; i<MAIN_WND_COLOR_NUM; i++)
			m_color_static.SetFillColor(i, m_data.text_colors[i]);
		m_color_static.Invalidate();
	}
	else
	{
		m_color_static.SetFillColor(m_data.text_colors[0]);
	}
}

void CMainWndSettingsDlg::IniUnitCombo()
{
	m_unit_combo.ResetContent();
	m_unit_combo.AddString(CCommon::LoadText(IDS_AUTO));
	if (m_data.unit_byte)
	{
		m_unit_combo.AddString(CCommon::LoadText(IDS_FIXED_AS, _T(" KB/s")));
		m_unit_combo.AddString(CCommon::LoadText(IDS_FIXED_AS, _T(" MB/s")));
	}
	else
	{
		m_unit_combo.AddString(CCommon::LoadText(IDS_FIXED_AS, _T(" Kb/s")));
		m_unit_combo.AddString(CCommon::LoadText(IDS_FIXED_AS, _T(" Mb/s")));
	}
	m_unit_combo.SetCurSel(static_cast<int>(m_data.speed_unit));
}

void CMainWndSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC, m_color_static);
	CTabDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HIDE_UNIT_CHECK, m_hide_unit_chk);
	DDX_Control(pDX, IDC_UNIT_COMBO, m_unit_combo);
	DDX_Control(pDX, IDC_FONT_SIZE_EDIT, m_font_size_edit);
	DDX_Control(pDX, IDC_DOUBLE_CLICK_COMBO, m_double_click_combo);
}


BEGIN_MESSAGE_MAP(CMainWndSettingsDlg, CTabDlg)
	ON_EN_CHANGE(IDC_UPLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeUploadEdit)
	ON_EN_CHANGE(IDC_DOWNLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeDownloadEdit)
	ON_EN_CHANGE(IDC_CPU_EDIT, &CMainWndSettingsDlg::OnEnChangeCpuEdit)
	ON_EN_CHANGE(IDC_MEMORY_EDIT, &CMainWndSettingsDlg::OnEnChangeMemoryEdit)
	//ON_BN_CLICKED(IDC_SET_COLOR_BUTTON1, &CMainWndSettingsDlg::OnBnClickedSetColorButton1)
	ON_BN_CLICKED(IDC_SET_DEFAULT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetDefaultButton)
	ON_BN_CLICKED(IDC_SET_FONT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetFontButton)
	ON_BN_CLICKED(IDC_SWITCH_UP_DOWN_CHECK, &CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck)
	ON_BN_CLICKED(IDC_FULLSCREEN_HIDE_CHECK, &CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck)
	ON_BN_CLICKED(IDC_SPEED_SHORT_MODE_CHECK2, &CMainWndSettingsDlg::OnBnClickedSpeedShortModeCheck2)
	ON_CBN_SELCHANGE(IDC_UNIT_COMBO, &CMainWndSettingsDlg::OnCbnSelchangeUnitCombo)
	ON_BN_CLICKED(IDC_HIDE_UNIT_CHECK, &CMainWndSettingsDlg::OnBnClickedHideUnitCheck)
	ON_BN_CLICKED(IDC_HIDE_PERCENTAGE_CHECK, &CMainWndSettingsDlg::OnBnClickedHidePercentageCheck)
	ON_MESSAGE(WM_STATIC_CLICKED, &CMainWndSettingsDlg::OnStaticClicked)
	ON_BN_CLICKED(IDC_SPECIFY_EACH_ITEM_COLOR_CHECK, &CMainWndSettingsDlg::OnBnClickedSpecifyEachItemColorCheck)
	ON_CBN_SELCHANGE(IDC_DOUBLE_CLICK_COMBO, &CMainWndSettingsDlg::OnCbnSelchangeDoubleClickCombo)
	ON_BN_CLICKED(IDC_SEPARATE_VALUE_UNIT_CHECK, &CMainWndSettingsDlg::OnBnClickedSeparateValueUnitCheck)
	ON_BN_CLICKED(IDC_UNIT_BYTE_RADIO, &CMainWndSettingsDlg::OnBnClickedUnitByteRadio)
	ON_BN_CLICKED(IDC_UNIT_BIT_RADIO, &CMainWndSettingsDlg::OnBnClickedUnitBitRadio)
END_MESSAGE_MAP()


// CMainWndSettingsDlg ��Ϣ�������


BOOL CMainWndSettingsDlg::OnInitDialog()
{
	CTabDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ�����ؼ�״̬
	SetDlgItemText(IDC_FONT_NAME_EDIT, m_data.font.name);
	//wchar_t buff[16];
	//swprintf_s(buff, L"%d", m_data.font_size);
	//SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);
	m_font_size_edit.SetRange(5, 72);
	m_font_size_edit.SetValue(m_data.font.size);

	SetDlgItemText(IDC_UPLOAD_EDIT, m_data.disp_str.up.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_data.disp_str.down.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_data.disp_str.cpu.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_data.disp_str.memory.c_str());

	((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->SetCheck(m_data.swap_up_down);
	((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->SetCheck(m_data.hide_main_wnd_when_fullscreen);
	((CButton*)GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2))->SetCheck(m_data.speed_short_mode);
	((CButton*)GetDlgItem(IDC_SEPARATE_VALUE_UNIT_CHECK))->SetCheck(m_data.separate_value_unit_with_space);

	m_color_static.SetLinkCursor();
	DrawStaticColor();

	m_toolTip.Create(this);
	m_toolTip.SetMaxTipWidth(theApp.DPI(300));
	m_toolTip.AddTool(GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2), CCommon::LoadText(IDS_SPEED_SHORT_MODE_TIP));

	if (m_data.unit_byte)
		((CButton*)GetDlgItem(IDC_UNIT_BYTE_RADIO))->SetCheck(TRUE);
	else
		((CButton*)GetDlgItem(IDC_UNIT_BIT_RADIO))->SetCheck(TRUE);

	IniUnitCombo();

	m_hide_unit_chk.SetCheck(m_data.hide_unit);
	if (m_data.speed_unit == SpeedUnit::AUTO)
	{
		m_hide_unit_chk.SetCheck(FALSE);
		m_data.hide_unit = false;
		m_hide_unit_chk.EnableWindow(FALSE);
	}
	((CButton*)GetDlgItem(IDC_HIDE_PERCENTAGE_CHECK))->SetCheck(m_data.hide_percent);

	if (m_text_disable)
	{
		GetDlgItem(IDC_UPLOAD_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOWNLOAD_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CPU_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEMORY_EDIT)->EnableWindow(FALSE);
		m_data.swap_up_down = false;
		((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->SetCheck(FALSE);
		GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK)->EnableWindow(FALSE);
		GetDlgItem(IDC_SET_DEFAULT_BUTTON)->EnableWindow(FALSE);
	}

	((CButton*)GetDlgItem(IDC_SPECIFY_EACH_ITEM_COLOR_CHECK))->SetCheck(m_data.specify_each_item_color);

	m_double_click_combo.AddString(CCommon::LoadText(IDS_OPEN_CONNECTION_DETIAL));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_OPEN_HISTORICAL_TRAFFIC));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_SHOW_HIDE_MORE_INFO));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_OPEN_OPTION_SETTINGS));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_OPEN_TASK_MANAGER));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_CHANGE_SKIN));
	m_double_click_combo.AddString(CCommon::LoadText(IDS_NONE));
	m_double_click_combo.SetCurSel(static_cast<int>(m_data.double_click_action));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMainWndSettingsDlg::OnEnChangeUploadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CTabDlg::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_UPLOAD_EDIT, tmp);
	m_data.disp_str.up = tmp;
}


void CMainWndSettingsDlg::OnEnChangeDownloadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CTabDlg::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_DOWNLOAD_EDIT, tmp);
	m_data.disp_str.down = tmp;
}


void CMainWndSettingsDlg::OnEnChangeCpuEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CTabDlg::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_CPU_EDIT, tmp);
	m_data.disp_str.cpu = tmp;
}


void CMainWndSettingsDlg::OnEnChangeMemoryEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CTabDlg::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_MEMORY_EDIT, tmp);
	m_data.disp_str.memory = tmp;
}


void CMainWndSettingsDlg::OnBnClickedSetDefaultButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.disp_str.up = CCommon::LoadText(IDS_UPLOAD_DISP, _T(": "));
	m_data.disp_str.down = CCommon::LoadText(IDS_DOWNLOAD_DISP, _T(": "));
	m_data.disp_str.cpu = L"CPU: ";
	m_data.disp_str.memory = CCommon::LoadText(IDS_MEMORY_DISP, _T(": "));
	SetDlgItemText(IDC_UPLOAD_EDIT, m_data.disp_str.up.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_data.disp_str.down.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_data.disp_str.cpu.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_data.disp_str.memory.c_str());
}


void CMainWndSettingsDlg::OnBnClickedSetFontButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LOGFONT lf{};
	lf.lfHeight = FONTSIZE_TO_LFHEIGHT(m_data.font.size);
	lf.lfWeight = (m_data.font.bold ? FW_BOLD : FW_NORMAL);
	lf.lfItalic = m_data.font.italic;
	lf.lfUnderline = m_data.font.underline;
	lf.lfStrikeOut = m_data.font.strike_out;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	//wcsncpy_s(lf.lfFaceName, m_data.font.name.GetString(), 32);
	CCommon::WStringCopy(lf.lfFaceName, 32, m_data.font.name.GetString());
	CCommon::NormalizeFont(lf);
	CFontDialog fontDlg(&lf);	//��������Ի��򣬳�ʼѡ������Ϊ֮ǰ����
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���
	{
		//��ȡ������Ϣ
		m_data.font.name = fontDlg.GetFaceName();
		m_data.font.size = fontDlg.GetSize() / 10;
		m_data.font.bold = (fontDlg.IsBold() != FALSE);
		m_data.font.italic = (fontDlg.IsItalic() != FALSE);
		m_data.font.underline = (fontDlg.IsUnderline() != FALSE);
		m_data.font.strike_out = (fontDlg.IsStrikeOut() != FALSE);
		//��������Ϣ��ʾ����
		SetDlgItemText(IDC_FONT_NAME_EDIT, m_data.font.name);
		wchar_t buff[16];
		swprintf_s(buff, L"%d", m_data.font.size);
		SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);
	}
}


void CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.swap_up_down = (((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.hide_main_wnd_when_fullscreen = (((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedSpeedShortModeCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.speed_short_mode = (((CButton*)GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnCbnSelchangeUnitCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.speed_unit = static_cast<SpeedUnit>(m_unit_combo.GetCurSel());
	if (m_data.speed_unit == SpeedUnit::AUTO)
	{
		m_hide_unit_chk.SetCheck(FALSE);
		m_data.hide_unit = false;
		m_hide_unit_chk.EnableWindow(FALSE);
	}
	else
	{
		m_hide_unit_chk.EnableWindow(TRUE);
	}
}


void CMainWndSettingsDlg::OnBnClickedHideUnitCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.hide_unit = (m_hide_unit_chk.GetCheck() != 0);
}


BOOL CMainWndSettingsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
		m_toolTip.RelayEvent(pMsg);

	return CTabDlg::PreTranslateMessage(pMsg);
}


void CMainWndSettingsDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ȡ��������
	int font_size;
	font_size = m_font_size_edit.GetValue();
	if (font_size > MAX_FONT_SIZE || font_size < MIN_FONT_SIZE)
	{
		CString info;
		info.Format(CCommon::LoadText(IDS_FONT_SIZE_WARNING), MIN_FONT_SIZE, MAX_FONT_SIZE);
		MessageBox(info, NULL, MB_OK | MB_ICONWARNING);
	}
	else
	{
		m_data.font.size = font_size;
	}
	GetDlgItemText(IDC_FONT_NAME_EDIT, m_data.font.name);

	CTabDlg::OnOK();
}


void CMainWndSettingsDlg::OnBnClickedHidePercentageCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.hide_percent = (((CButton*)GetDlgItem(IDC_HIDE_PERCENTAGE_CHECK))->GetCheck() != 0);
}


afx_msg LRESULT CMainWndSettingsDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	switch (::GetDlgCtrlID(((CWnd*)wParam)->m_hWnd))
	{
	case IDC_TEXT_COLOR_STATIC:
	{
		//�����ı���ɫ
		if (m_data.specify_each_item_color)
		{
			CMainWndColorDlg colorDlg(m_data.text_colors);
			if (colorDlg.DoModal() == IDOK)
			{
				for (int i{}; i < MAIN_WND_COLOR_NUM; i++)
					m_data.text_colors[i] = colorDlg.GetColors()[i];
				DrawStaticColor();
			}
		}
		else
		{
			CMFCColorDialogEx colorDlg(m_data.text_colors[0], 0, this);
			if (colorDlg.DoModal() == IDOK)
			{
				m_data.text_colors[0] = colorDlg.GetColor();
				DrawStaticColor();
			}
		}
		break;
	}
	default:
		break;
	}
	return 0;
}


void CMainWndSettingsDlg::OnBnClickedSpecifyEachItemColorCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.specify_each_item_color = (((CButton*)GetDlgItem(IDC_SPECIFY_EACH_ITEM_COLOR_CHECK))->GetCheck() != 0);
	DrawStaticColor();
}


void CMainWndSettingsDlg::OnCbnSelchangeDoubleClickCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.double_click_action = static_cast<DoubleClickAction>(m_double_click_combo.GetCurSel());
}


void CMainWndSettingsDlg::OnBnClickedSeparateValueUnitCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.separate_value_unit_with_space = (((CButton*)GetDlgItem(IDC_SEPARATE_VALUE_UNIT_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedUnitByteRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.unit_byte = true;
	IniUnitCombo();
}


void CMainWndSettingsDlg::OnBnClickedUnitBitRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.unit_byte = false;
	IniUnitCombo();
}

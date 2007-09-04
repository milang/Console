#include "stdafx.h"
#include "resource.h"

#include "DlgSettingsBehavior.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

DlgSettingsBehavior::DlgSettingsBehavior(CComPtr<IXMLDOMElement>& pOptionsRoot)
: DlgSettingsBase(pOptionsRoot)
{
	IDD = IDD_SETTINGS_BEHAVIOR;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsBehavior::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_behaviorSettings.Load(m_pOptionsRoot);

	m_nCopyOnSelect	= m_behaviorSettings.copyPasteSettings.bCopyOnSelect ? 1 : 0;
	m_nClearOnCopy	= m_behaviorSettings.copyPasteSettings.bClearOnCopy ? 1 : 0;
	m_nNoWrap		= m_behaviorSettings.copyPasteSettings.bNoWrap ? 1 : 0;
	m_nTrimSpaces	= m_behaviorSettings.copyPasteSettings.bTrimSpaces ? 1 : 0;
	m_nCopyNewlineChar= static_cast<int>(m_behaviorSettings.copyPasteSettings.copyNewlineChar);

	m_nScrollPageType= m_behaviorSettings.scrollSettings.dwPageScrollRows ? 1 : 0;

	CUpDownCtrl	spin;
	UDACCEL		udAccel;

	spin.Attach(GetDlgItem(IDC_SPIN_SCROLL_PAGE_ROWS));
	spin.SetRange(1, 500);
	udAccel.nSec = 2;
	udAccel.nInc = 1;
	spin.SetAccel(1, &udAccel);
	spin.Detach();

	EnableScrollControls();
	
	DoDataExchange(DDX_LOAD);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsBehavior::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (wID == IDOK)
	{
		DoDataExchange(DDX_SAVE);

		m_behaviorSettings.copyPasteSettings.bCopyOnSelect	= (m_nCopyOnSelect > 0);
		m_behaviorSettings.copyPasteSettings.bClearOnCopy	= (m_nClearOnCopy > 0);
		m_behaviorSettings.copyPasteSettings.bNoWrap		= (m_nNoWrap > 0);
		m_behaviorSettings.copyPasteSettings.bTrimSpaces	= (m_nTrimSpaces > 0);
		m_behaviorSettings.copyPasteSettings.copyNewlineChar= static_cast<CopyNewlineChar>(m_nCopyNewlineChar);

		if (m_nScrollPageType == 0) m_behaviorSettings.scrollSettings.dwPageScrollRows = 0;

		BehaviorSettings& behaviorSettings = g_settingsHandler->GetBehaviorSettings();

		behaviorSettings = m_behaviorSettings;
		m_behaviorSettings.Save(m_pOptionsRoot);
	}

	DestroyWindow();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsBehavior::OnClickedScrollType(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	EnableScrollControls();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsBehavior::EnableScrollControls()
{
	GetDlgItem(IDC_SCROLL_PAGE_ROWS).EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_SCROLL_PAGE_ROWS).EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_ROWS).EnableWindow(FALSE);

	if (m_nScrollPageType > 0)
	{
		GetDlgItem(IDC_SCROLL_PAGE_ROWS).EnableWindow();
		GetDlgItem(IDC_SPIN_SCROLL_PAGE_ROWS).EnableWindow();
		GetDlgItem(IDC_STATIC_ROWS).EnableWindow();
	}
}

//////////////////////////////////////////////////////////////////////////////




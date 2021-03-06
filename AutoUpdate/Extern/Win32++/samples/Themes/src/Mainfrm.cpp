////////////////////////////////////////////////////
// Mainfrm.cpp

#include "stdafx.h"
#include "mainfrm.h"
#include "resource.h"


// Definitions for the CMainFrame class
CMainFrame::CMainFrame() : m_nColor(IDM_BLUE), m_UseThemes(TRUE), m_UseBandColors(TRUE), m_UseFlatStyle(FALSE),
							m_KeepBandsLeft(TRUE), m_LockMenuBand(TRUE), m_UseRoundBorders(TRUE),
                            m_UseShortBands(TRUE), m_UseLines(FALSE), m_ShowArrows(TRUE), m_ShowCards(TRUE)
{
	// Constructor for CMainFrame. Its called after CFrame's constructor

	//Set m_View as the view window of the frame
	SetView(m_View);

	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
	LoadRegistrySettings(_T("Win32++\\Themes Sample"));
}

CMainFrame::~CMainFrame()
{
	// Destructor for CMainFrame.
}

void CMainFrame::AddCombo()
{
	// We'll be placing the ComboBoxEx control over the 'File Save' toolbar button
	int nComboWidth = 120;
	CToolBar* pTB = GetToolBar();
	if (pTB->CommandToIndex(IDM_FILE_SAVE) < 0) return;

	pTB->SetButtonStyle(IDM_FILE_SAVE, TBSTYLE_SEP);	// Convert the button to a separator
	pTB->SetButtonWidth(IDM_FILE_SAVE, nComboWidth);

	// Determine the size and position of the ComboBox
	int nIndex = pTB->CommandToIndex(IDM_FILE_SAVE);
	CRect rc = pTB->GetItemRect(nIndex);

	// Create and position the ComboboxEx window
	m_ComboBoxEx.Create(pTB);
	m_ComboBoxEx.SetWindowPos(NULL, rc, SWP_NOACTIVATE);

	// Set ComboBox Height
	m_ComboBoxEx.SendMessage(CB_SETITEMHEIGHT, (WPARAM)-1, (LPARAM)rc.Height()-6);

	m_ComboBoxEx.AddItems();
	RecalcLayout();
}

void CMainFrame::ChooseColor(UINT nColor)
{
	m_nColor = nColor;

	switch (nColor)
	{
	case IDM_MODERN:
		{
			SetReBarColors( RGB(225, 230, 255), RGB(240, 242, 250), RGB(248, 248, 248), RGB(180, 200, 230) );

			StatusBarTheme sbt = {TRUE, RGB(225, 230, 255), RGB(240, 242, 250)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(180, 250, 255), RGB(140, 190, 255), RGB(150, 220, 255), RGB(80, 100, 255), RGB(127, 127, 255)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(180, 250, 255), RGB(140, 190, 255), RGB(240, 250, 255), RGB(120, 170, 220), RGB(127, 127, 255)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_BLUE:	// ICY_BLUE Theme
		{
			SetReBarColors( RGB(150,190,245), RGB(196,215,250), RGB(220,230,250), RGB( 70,130,220) );

			StatusBarTheme sbt = {TRUE, RGB(150,190,245), RGB(196,215,250)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(255, 230, 190), RGB(255, 190, 100), RGB(255, 140, 40), RGB(255, 180, 80), RGB(128, 128, 255)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(255, 230, 190), RGB(255, 190, 100), RGB(150,190,245), RGB(220,230,250), RGB(128, 128, 200)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_GREY:	// Grey Theme
		{
			SetReBarColors( RGB(210, 210, 200), RGB(238, 236, 224), RGB(248, 247, 243), RGB(195, 195, 172) );

			StatusBarTheme sbt = {TRUE, RGB(210, 210, 200), RGB(238, 236, 224)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(192, 210, 238), RGB(192, 210, 238), RGB(152, 181, 226), RGB(152, 181, 226), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(196, 215, 250), RGB( 120, 180, 220), RGB(210, 210, 200), RGB(248, 247, 243), RGB(128, 128, 200)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_OLIVE:
		{
			SetReBarColors( RGB(160, 180, 80), RGB(180, 200, 100), RGB(200, 220, 120), RGB(80, 159, 78) );

			StatusBarTheme sbt = {TRUE, RGB(160, 180, 80), RGB(180, 200, 100)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(255, 230, 190), RGB(255, 190, 100), RGB(255, 140, 40), RGB(255, 180, 80), RGB(128, 128, 255)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(255, 200, 190), RGB(255, 210, 90), RGB(255, 230, 190), RGB(230, 160, 190), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_GOLD:
		{
			SetReBarColors( RGB(230, 180, 0), RGB(240, 210, 90), RGB(255, 240, 150), RGB(180, 140, 50) );

			StatusBarTheme sbt = {TRUE, RGB(230, 180, 0), RGB(240, 210, 90)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(192, 210, 238), RGB(192, 210, 238), RGB(152, 181, 226), RGB(152, 181, 226), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(196, 215, 250), RGB( 120, 180, 220), RGB(240, 210, 90), RGB(255, 240, 150), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_OCHRE:
		{
			SetReBarColors( RGB(248, 132, 12), RGB(248, 198, 10), RGB(248, 210, 20), RGB(248, 141, 6) );

			StatusBarTheme sbt = {TRUE, RGB(248, 132, 12), RGB(248, 198, 10)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(192, 210, 238), RGB(192, 210, 238), RGB(152, 181, 226), RGB(152, 181, 226), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(196, 215, 250), RGB( 120, 180, 220), RGB(150,190,245), RGB(220,230,250), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_PINK:
		{
			SetReBarColors( RGB(255, 130, 190), RGB(250, 205, 235), RGB(250, 205, 235), RGB(255, 120, 170) );

			StatusBarTheme sbt = {TRUE, RGB(255, 130, 190), RGB(250, 205, 235)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(192, 210, 238), RGB(192, 210, 238), RGB(248, 147, 220), RGB(248, 153, 179), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(196, 215, 250), RGB( 120, 180, 220), RGB(255, 130, 190), RGB(250, 205, 235), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_MAUVE:
		{
			SetReBarColors( RGB(210, 128, 155), RGB(230, 160, 190), RGB(230, 158, 188), RGB(110, 100, 125) );

			StatusBarTheme sbt = {TRUE, RGB(210, 128, 155), RGB(230, 160, 190)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(192, 210, 238), RGB(192, 210, 238), RGB(152, 181, 226), RGB(152, 181, 226), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(196, 215, 250), RGB( 120, 180, 220), RGB(150,190,245), RGB(220,230,250), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	case IDM_BLACK:
		{
			SetReBarColors( RGB(128, 138 ,176), RGB(98, 108 ,136), RGB(77, 87, 97), RGB(7, 17, 27) );

			StatusBarTheme sbt = {TRUE, RGB(128, 138 ,176), RGB(98, 108 ,136)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(49, 106, 197), RGB(64,177,230), RGB(27,65, 160), RGB(64,177,230), RGB(49, 106, 197)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(84,197,240), RGB(89, 136, 217), RGB(59, 126, 197), RGB(94,187,230), RGB(128, 128, 128)};
			SetMenuTheme(&mt);
		}
		break;
	default:
		{
			m_nColor = IDM_MODERN;
			SetReBarColors( RGB(225, 230, 255), RGB(240, 242, 250), RGB(248, 248, 248), RGB(180, 200, 230) );

			StatusBarTheme sbt = {TRUE, RGB(225, 230, 255), RGB(240, 242, 250)};
			SetStatusBarTheme (&sbt);

			ToolBarTheme tbt = {TRUE, RGB(180, 250, 255), RGB(140, 190, 255), RGB(150, 220, 255), RGB(80, 100, 255), RGB(127, 127, 255)};
			SetToolBarTheme(&tbt);

			MenuTheme mt = {TRUE, RGB(180, 250, 255), RGB(140, 190, 255), RGB(240, 250, 255), RGB(120, 170, 220), RGB(127, 127, 255)};
			SetMenuTheme(&mt);
		}
		break;
	}

	// Check the appropriate menu item
	int nFileItem = GetMenuItemPos(GetFrameMenu(), _T("Theme"));
	if (nFileItem >= 0)
	{
		CMenu* pThemeMenu = GetFrameMenu()->GetSubMenu(nFileItem);
		pThemeMenu->CheckMenuRadioItem(IDM_BLUE, IDM_MODERN, nColor, 0);
	}

	RecalcLayout();
}

DWORD CMainFrame::GetRegDwordFromOpenKey(HKEY hKey, LPCTSTR pName)
{
  DWORD   dwType;
  DWORD   dwCount = sizeof(DWORD);
  DWORD   dwValue = 0;
  if (ERROR_SUCCESS == RegQueryValueEx(hKey, pName, NULL, &dwType, (LPBYTE)&dwValue, &dwCount))
	  return dwValue;
  else
	  return 0;
}

BOOL CMainFrame::LoadRegistrySettings(LPCTSTR szKeyName)
{
	CFrame::LoadRegistrySettings(szKeyName);

	HKEY hKey;
	CString strKey = _T("Software\\");
	strKey += szKeyName;
	strKey += (_T("\\Theme Settings"));

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, strKey, 0, KEY_READ, &hKey))
	{
		m_nColor = GetRegDwordFromOpenKey(hKey, _T("ColorStyle"));
		m_UseThemes = GetRegDwordFromOpenKey(hKey, _T("UseThemes")) & 1;
		m_UseBandColors = GetRegDwordFromOpenKey(hKey, _T("UseBandColors")) & 1;
		m_UseFlatStyle = GetRegDwordFromOpenKey(hKey, _T("UseFlatStyle")) & 1;
		m_KeepBandsLeft = GetRegDwordFromOpenKey(hKey, _T("PutBandsLeft")) & 1;
		m_LockMenuBand = GetRegDwordFromOpenKey(hKey, _T("LockMenuBand")) & 1;
		m_UseRoundBorders = GetRegDwordFromOpenKey(hKey, _T("UseRoundBorders")) & 1;
		m_UseShortBands = GetRegDwordFromOpenKey(hKey, _T("UseShortBands")) & 1;
		m_UseLines = GetRegDwordFromOpenKey(hKey, _T("UseLines")) & 1;
		m_ShowArrows = GetRegDwordFromOpenKey(hKey, _T("ShowArrows")) & 1;
		m_ShowCards = GetRegDwordFromOpenKey(hKey, _T("ShowCards")) & 1;
		int nBands = GetRegDwordFromOpenKey(hKey, _T("NumBands"));

		// Retrieve the band styles and IDs
		for (int i = 0; i < nBands; ++i)
		{
			TCHAR szSubKey[16];
			wsprintf(szSubKey, _T("Band ID %d\0"), i+1);
			UINT nID = GetRegDwordFromOpenKey(hKey, szSubKey);
			m_vBandIDs.push_back(nID);

			wsprintf(szSubKey, _T("Band Style %d\0"), i+1);
			UINT nStyle = GetRegDwordFromOpenKey(hKey, szSubKey);
			m_vBandStyles.push_back(nStyle);

			wsprintf(szSubKey, _T("Band Size %d\0"), i+1);
			UINT nSize = GetRegDwordFromOpenKey(hKey, szSubKey);
			m_vBandSizes.push_back(nSize);
		}

		RegCloseKey(hKey);
	}
	else
	{
		// Choose reasonable default values
		m_nColor = IDM_OLIVE;
		m_UseThemes = TRUE;
		m_UseBandColors = TRUE;
		m_UseFlatStyle = FALSE;
		m_KeepBandsLeft = TRUE;
		m_LockMenuBand = TRUE;
		m_UseRoundBorders = TRUE;
		m_UseShortBands = TRUE;
		m_UseLines = FALSE;;
		m_ShowArrows = TRUE;
		m_ShowCards = TRUE;
	}

	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// OnCommand responds to menu and and toolbar input

	UNREFERENCED_PARAMETER(lParam);

	switch(LOWORD(wParam))
	{
	case IDM_FILE_EXIT:		 OnFileExit();				return TRUE;
	case IDM_MODERN:		 ChooseColor(IDM_MODERN);	return TRUE;
	case IDM_BLUE:			 ChooseColor(IDM_BLUE);		return TRUE;
	case IDM_GREY:			 ChooseColor(IDM_GREY);		return TRUE;
	case IDM_OLIVE:			 ChooseColor(IDM_OLIVE);	return TRUE;
	case IDM_OCHRE:			 ChooseColor(IDM_OCHRE);	return TRUE;
	case IDM_MAUVE:			 ChooseColor(IDM_MAUVE);	return TRUE;
	case IDM_PINK:			 ChooseColor(IDM_PINK);		return TRUE;
	case IDM_GOLD:			 ChooseColor(IDM_GOLD);		return TRUE;
	case IDM_BLACK:			 ChooseColor(IDM_BLACK);	return TRUE;
	case IDM_USE_THEMES:	 OnUseThemes();				return TRUE;
	case IDM_BAND_COLORS:	 OnBandColors();			return TRUE;
	case IDM_FLAT_STYLE:	 OnFlatStyle();				return TRUE;
	case IDM_LEFT_BANDS:	 OnLeftBands();				return TRUE;
	case IDM_LOCK_MENUBAR:	 OnLockMenuBar();			return TRUE;
	case IDM_ROUND_BORDERS:	 OnRoundBorders();			return TRUE;
	case IDM_SHORT_BANDS:	 OnShortBands();			return TRUE;
	case IDM_USE_LINES:		 OnUseLines();				return TRUE;
	case IDM_VIEW_ARROWS:	 OnViewArrows();			return TRUE;
	case IDM_VIEW_CARDS:	 OnViewCards();				return TRUE;
	case IDW_VIEW_STATUSBAR: OnViewStatusBar();			return TRUE;
	case IDW_VIEW_TOOLBAR:	 OnViewToolBar();			return TRUE;
	case IDM_HELP_ABOUT:	 OnHelp();					return TRUE;
	}

	return FALSE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT pcs)
{
	// OnCreate controls the way the frame is created.
	// Overriding CFrame::Oncreate is optional.
	// The default for the following variables is TRUE

	// m_UseIndicatorStatus = FALSE;	// Don't show keyboard indicators in the StatusBar
	// m_UseMenuStatus = FALSE;			// Don't show menu descriptions in the StatusBar
	// m_UseReBar = FALSE;				// Don't use a ReBar
	// m_UseThemes = FALSE;				// Don't use themes
	// m_UseToolBar = FALSE;			// Don't use a ToolBar

	// call the base class function
	CFrame::OnCreate(pcs);

	if (IsReBarSupported())
	{
		//Set our theme colors
		ChooseColor(m_nColor);
		
		// Set the band styles and positions
		for (int i = 0; i < GetReBar()->GetBandCount(); ++i)
		{
			if (i < (int)m_vBandStyles.size())
			{
				// Move the band to the correct position
				int iFrom = GetReBar()->IDToIndex(m_vBandIDs[i]);
				GetReBar()->MoveBand(iFrom, i);

				// Set the band's style
				REBARBANDINFO rbbi;
				ZeroMemory(&rbbi, sizeof(REBARBANDINFO));
				rbbi.fMask = RBBIM_STYLE;
				rbbi.fStyle = m_vBandStyles[i];
				GetReBar()->SetBandInfo(i, rbbi);
			}
		
			if (i < (int)m_vBandSizes.size())
			{
				// Set the band's size
				REBARBANDINFO rbbi;
				ZeroMemory(&rbbi, sizeof(REBARBANDINFO));
				rbbi.fMask = RBBIM_SIZE;
				rbbi.cx = m_vBandSizes[i];
				GetReBar()->SetBandInfo(i, rbbi);
			}

		}
	
		// Set the MenuBar's position and gripper
		int nBand = GetReBar()->GetBand(GetMenuBar()->GetHwnd());
		GetReBar()->ShowGripper(nBand, !m_LockMenuBand);
		if (m_LockMenuBand)
			GetReBar()->MoveBand(nBand, 0);

		ShowArrows(m_ShowArrows);
		ShowCards(m_ShowCards);
	}
	else
		MessageBox(_T("Some Theme features are not supported on this Operating System"), _T("Warning"), MB_ICONWARNING);

	return 0;
}

void CMainFrame::OnFileExit()
{
	// Issue a close request to the frame
	PostMessage(WM_CLOSE);
}

void CMainFrame::OnInitialUpdate()
{
	// The frame is now created.
	// Place any additional startup code here.

	TRACE("Frame created\n");
}

LRESULT CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam)
{
	// Process notification messages sent by child windows
//	switch(((LPNMHDR)lParam)->code)
//	{
 		//Add case statments for each notification message here
//	}

	// Pass any unhandled messages on for default processing
	return CFrame::OnNotify(wParam, lParam);
}

void CMainFrame::OnUseThemes()
{
	if (IsReBarSupported())
	{
		m_UseThemes = !m_UseThemes;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->UseThemes = m_UseThemes;
		SetReBarTheme(pRBT);
		int nBand = GetReBar()->GetBand(GetMenuBar()->GetHwnd());
		GetReBar()->ShowGripper(nBand, !m_UseThemes);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}

void CMainFrame::OnBandColors()
{
	if (IsReBarSupported())
	{
		m_UseBandColors = !m_UseBandColors;
		ChooseColor(m_nColor);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}
void CMainFrame::OnFlatStyle()
{
	if (IsReBarSupported())
	{
		m_UseFlatStyle = !m_UseFlatStyle;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->FlatStyle = m_UseFlatStyle;
		SetReBarTheme(pRBT);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}
void CMainFrame::OnLeftBands()
{
	if (IsReBarSupported())
	{
		m_KeepBandsLeft = !m_KeepBandsLeft;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->BandsLeft = m_KeepBandsLeft;
		SetReBarTheme(pRBT);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}

void CMainFrame::OnLockMenuBar()
{
	if (IsReBarSupported())
	{
		m_LockMenuBand = !m_LockMenuBand;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->LockMenuBand = m_LockMenuBand;
		SetReBarTheme(pRBT);
		GetReBar()->MoveBand(GetReBar()->GetBand(GetMenuBar()->GetHwnd()), 0);	// Move the MenuBar to band 0
		GetReBar()->ShowGripper(GetReBar()->GetBand(GetMenuBar()->GetHwnd()), !m_LockMenuBand);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}

void CMainFrame::OnMenuUpdate(UINT nID)
// Called just before the menu is displayed
{
	// Update the check buttons before displaying the menu
	switch(nID)
	{
	case IDM_USE_THEMES:
		GetFrameMenu()->CheckMenuItem(nID, m_UseThemes? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_BAND_COLORS:
		GetFrameMenu()->CheckMenuItem(nID, m_UseBandColors? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_FLAT_STYLE:
		GetFrameMenu()->CheckMenuItem(nID, m_UseFlatStyle? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_LEFT_BANDS:
		GetFrameMenu()->CheckMenuItem(nID, m_KeepBandsLeft? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_LOCK_MENUBAR:
		GetFrameMenu()->CheckMenuItem(nID, m_LockMenuBand? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_ROUND_BORDERS:
		GetFrameMenu()->CheckMenuItem(nID, m_UseRoundBorders? MF_CHECKED : MF_UNCHECKED);
		break;	
	case IDM_SHORT_BANDS:
		GetFrameMenu()->CheckMenuItem(nID, m_UseShortBands? MF_CHECKED : MF_UNCHECKED);
		break;	
	case IDM_USE_LINES:
		GetFrameMenu()->CheckMenuItem(nID, m_UseLines? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_VIEW_ARROWS:
		GetFrameMenu()->CheckMenuItem(nID, m_ShowArrows? MF_CHECKED : MF_UNCHECKED);
		break;
	case IDM_VIEW_CARDS:
		GetFrameMenu()->CheckMenuItem(nID, m_ShowCards? MF_CHECKED : MF_UNCHECKED);
		break;
	}

	if ((nID >= IDM_BLUE) && (nID <= IDM_MODERN))
		GetFrameMenu()->CheckMenuItem(nID, (nID == m_nColor)? MF_CHECKED : MF_UNCHECKED);

	// Call the base class member function
	CFrame::OnMenuUpdate(nID);
}

void CMainFrame::OnRoundBorders()
{
	if (IsReBarSupported())
	{
		m_UseRoundBorders = !m_UseRoundBorders;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->RoundBorders = m_UseRoundBorders;
		SetReBarTheme(pRBT);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}
void CMainFrame::OnShortBands()
{
	if (IsReBarSupported())
	{
		m_UseShortBands = !m_UseShortBands;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->ShortBands = m_UseShortBands;
		SetReBarTheme(pRBT);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}
void CMainFrame::OnUseLines()
{
	if (IsReBarSupported())
	{
		m_UseLines = !m_UseLines;
		ReBarTheme* pRBT = GetReBarTheme();
		pRBT->UseLines = m_UseLines;
		SetReBarTheme(pRBT);

		GetReBar()->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
		RecalcLayout();
	}
}

void CMainFrame::OnViewArrows()
{
	if (IsReBarSupported())
	{
		m_ShowArrows = !m_ShowArrows;
		ShowArrows(m_ShowArrows);
	}
}

void CMainFrame::OnViewCards()
{
	if (IsReBarSupported())
	{
		m_ShowCards = !m_ShowCards;
		ShowCards(m_ShowCards);
	}
}

BOOL CMainFrame::SaveRegistrySettings()
{
	if (IsReBarSupported())
	{
		CFrame::SaveRegistrySettings();

		HKEY hKey;
		CString strKeyName = GetRegistryKeyName();
		CString strKey = _T("Software\\");
		strKey += strKeyName + (_T("\\Theme Settings"));
		int nBands = GetReBar()->GetBandCount();

		RegCreateKeyEx(HKEY_CURRENT_USER, strKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

		// Save the theme settings
		RegSetValueEx(hKey, _T("ColorStyle"), 0, REG_DWORD, (LPBYTE)&m_nColor, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseThemes"), 0, REG_DWORD, (LPBYTE)&m_UseThemes, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseBandColors"), 0, REG_DWORD, (LPBYTE)&m_UseBandColors, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseFlatStyle"), 0, REG_DWORD, (LPBYTE)&m_UseFlatStyle, sizeof(DWORD));
		RegSetValueEx(hKey, _T("PutBandsLeft"), 0, REG_DWORD, (LPBYTE)&m_KeepBandsLeft, sizeof(DWORD));
		RegSetValueEx(hKey, _T("LockMenuBand"), 0, REG_DWORD, (LPBYTE)&m_LockMenuBand, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseRoundBorders"), 0, REG_DWORD, (LPBYTE)&m_UseRoundBorders, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseShortBands"), 0, REG_DWORD, (LPBYTE)&m_UseShortBands, sizeof(DWORD));
		RegSetValueEx(hKey, _T("UseLines"), 0, REG_DWORD, (LPBYTE)&m_UseLines, sizeof(DWORD));
		RegSetValueEx(hKey, _T("ShowArrows"), 0, REG_DWORD, (LPBYTE)&m_ShowArrows, sizeof(DWORD));
		RegSetValueEx(hKey, _T("ShowCards"), 0, REG_DWORD, (LPBYTE)&m_ShowCards, sizeof(DWORD));
		RegSetValueEx(hKey, _T("NumBands"), 0, REG_DWORD, (LPBYTE)&nBands, sizeof(DWORD));

		// Save the rebar band settings
		REBARBANDINFO rbbi;
		ZeroMemory(&rbbi, sizeof(REBARBANDINFO));
		rbbi.fMask = RBBIM_ID|RBBIM_STYLE|RBBIM_SIZE;

		for (int i = 0; i < nBands; i++)
		{
			GetReBar()->GetBandInfo(i, rbbi);
			UINT nID = rbbi.wID;
			UINT nStyle = rbbi.fStyle;
			UINT nSize = rbbi.cx;

			TCHAR szSubKey[16];
			wsprintf(szSubKey, _T("Band ID %d\0"), i+1);
			RegSetValueEx(hKey, szSubKey, 0, REG_DWORD, (LPBYTE)&nID, sizeof(DWORD));
			wsprintf(szSubKey, _T("Band Style %d\0"), i+1);
			RegSetValueEx(hKey, szSubKey, 0, REG_DWORD, (LPBYTE)&nStyle, sizeof(DWORD));
			wsprintf(szSubKey, _T("Band Size %d\0"), i+1);
			RegSetValueEx(hKey, szSubKey, 0, REG_DWORD, (LPBYTE)&nSize, sizeof(DWORD));
		}

		RegCloseKey(hKey);
	}

	return TRUE;
}


void CMainFrame::SetReBarColors(COLORREF clrBkGnd1, COLORREF clrBkGnd2, COLORREF clrBand1, COLORREF clrBand2)
{
	if (IsReBarSupported())
	{
		ReBarTheme rt;
		ZeroMemory(&rt, sizeof(ReBarTheme));
		rt.UseThemes = m_UseThemes;
		rt.clrBkgnd1 = clrBkGnd1;
		rt.clrBkgnd2 = clrBkGnd2;
		rt.clrBand1  = clrBand1;
		rt.clrBand2  = clrBand2;
		rt.FlatStyle = m_UseFlatStyle;
		rt.BandsLeft = m_KeepBandsLeft;
		rt.LockMenuBand = m_LockMenuBand;
		rt.RoundBorders = m_UseRoundBorders;
		rt.ShortBands = m_UseShortBands;
		rt.UseLines = m_UseLines;

		if (!m_UseBandColors)
		{
			rt.clrBand1 = 0;
			rt.clrBand2 = 0;
		}

		SetReBarTheme(&rt);
	}
}

void CMainFrame::SetupToolBar()
{
	// Set the Resource IDs for the first toolbar buttons
	AddToolBarButton( IDM_FILE_NEW   );
	AddToolBarButton( IDM_FILE_OPEN  );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_FILE_SAVE  );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_EDIT_CUT   );
	AddToolBarButton( IDM_EDIT_COPY  );
	AddToolBarButton( IDM_EDIT_PASTE );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_FILE_PRINT );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_HELP_ABOUT );

	// Set the three image lists for the first toolbar
	SetToolBarImages(RGB(255, 0, 255), IDB_TOOLBAR_NORM, IDB_TOOLBAR_HOT, IDB_TOOLBAR_DIS);

	// Add the two other toolbars if we can use rebars (Need Win95 and IE 4 or better)
	if (IsReBarSupported())
	{
		// Add the Arrows toolbar
		AddToolBarBand(&m_Arrows, 0, IDC_ARROWS);
		m_Arrows.AddButton(IDM_ARROW_LEFT);
		m_Arrows.AddButton(IDM_ARROW_RIGHT);

		// Add the Cards toolbar
		AddToolBarBand(&m_Cards, 0, IDB_CARDS);
		m_Cards.AddButton(IDM_CARD_CLUB);
		m_Cards.AddButton(IDM_CARD_DIAMOND);
		m_Cards.AddButton(IDM_CARD_HEART);
		m_Cards.AddButton(IDM_CARD_SPADE);
		
		// Set the button images
		SetTBImageList(&m_Arrows, &m_ArrowImages, IDB_ARROWS, RGB(255,0,255));
		SetTBImageList(&m_Cards, &m_CardImages, IDB_CARDS, RGB(255,0,255));
	}

	AddCombo();
}

void CMainFrame::ShowArrows(BOOL bShow)
{
	if (IsReBarSupported())
	{
		GetReBar()->SendMessage(RB_SHOWBAND, GetReBar()->GetBand(m_Arrows), bShow);

		if (GetReBarTheme()->UseThemes && GetReBarTheme()->BandsLeft)
			GetReBar()->MoveBandsLeft();
	}
}

void CMainFrame::ShowCards(BOOL bShow)
{
	if (IsReBarSupported())
	{
		GetReBar()->SendMessage(RB_SHOWBAND, GetReBar()->GetBand(m_Cards), bShow);

		if (GetReBarTheme()->UseThemes && GetReBarTheme()->BandsLeft)
			GetReBar()->MoveBandsLeft();
	}
}

LRESULT CMainFrame::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	switch (uMsg)
//	{
//		Add case statements for each messages to be handled here
//	}

//	pass unhandled messages on for default processing
	return WndProcDefault(uMsg, wParam, lParam);
}



void DoWindowTabView(DWORD dwNewView, BOOL bFirst)
{
  DWORD dwOldView=moCur.dwTabOptionsMDI;
  DWORD dwStyle;
  int nCommand=0;

  if (dwNewView & TAB_VIEW_TOP)
  {
    nCommand=IDM_WINDOW_TABVIEW_TOP;
    dwNewView=TAB_VIEW_TOP;
  }
  else if (dwNewView & TAB_VIEW_BOTTOM)
  {
    nCommand=IDM_WINDOW_TABVIEW_BOTTOM;
    dwNewView=TAB_VIEW_BOTTOM;
  }
  else if (dwNewView & TAB_VIEW_NONE)
  {
    nCommand=IDM_WINDOW_TABVIEW_NONE;
    dwNewView=TAB_VIEW_NONE;
  }
  if (dwOldView & TAB_VIEW_TOP)
    dwOldView=TAB_VIEW_TOP;
  else if (dwOldView & TAB_VIEW_BOTTOM)
    dwOldView=TAB_VIEW_BOTTOM;
  else if (dwOldView & TAB_VIEW_NONE)
    dwOldView=TAB_VIEW_NONE;
  CheckMenuRadioItem(hMainMenu, IDM_WINDOW_TABVIEW_TOP, IDM_WINDOW_TABVIEW_NONE, nCommand, MF_BYCOMMAND);
  EnableMenuItem(hMainMenu, IDM_WINDOW_TABTYPE_STANDARD, !(dwNewView & TAB_VIEW_NONE)?MF_ENABLED:MF_GRAYED);
  EnableMenuItem(hMainMenu, IDM_WINDOW_TABTYPE_BUTTONS, !(dwNewView & TAB_VIEW_NONE)?MF_ENABLED:MF_GRAYED);
  if (!bOldComctl32) EnableMenuItem(hMainMenu, IDM_WINDOW_TABTYPE_FLATBUTTONS, !(dwNewView & TAB_VIEW_NONE)?MF_ENABLED:MF_GRAYED);

  if (bFirst != TRUE && dwNewView == dwOldView) return;
  moCur.dwTabOptionsMDI=moCur.dwTabOptionsMDI & ~TAB_VIEW_TOP & ~TAB_VIEW_BOTTOM & ~TAB_VIEW_NONE;
  moCur.dwTabOptionsMDI|=dwNewView;

  if (moCur.dwTabOptionsMDI & TAB_VIEW_TOP)
  {
    dwStyle=(DWORD)GetWindowLongPtrWide(hTab, GWL_STYLE);
    SetWindowLongPtrWide(hTab, GWL_STYLE, dwStyle & ~TCS_BOTTOM);
  }
  else if (moCur.dwTabOptionsMDI & TAB_VIEW_BOTTOM)
  {
    dwStyle=(DWORD)GetWindowLongPtrWide(hTab, GWL_STYLE);
    SetWindowLongPtrWide(hTab, GWL_STYLE, dwStyle|TCS_BOTTOM);
  }
  ShowWindow(hTab, !(moCur.dwTabOptionsMDI & TAB_VIEW_NONE)?SW_SHOW:SW_HIDE);
  UpdateSize();
}

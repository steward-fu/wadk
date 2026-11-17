BOOL DoEditDeleteFirstCharW(HWND hWnd)
{
  AECHARRANGE crRange;
  wchar_t *wszRange;
  INT_PTR nRangeLen;
  INT_PTR a;
  INT_PTR b;
  int nFirstLine=0;
  BOOL bDelete;
  BOOL bCaretAtStart=FALSE;

  if (IsReadOnly(hWnd))
    return FALSE;
  if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))
    bCaretAtStart=TRUE;
  crRange.ciMin=crCurSel.ciMin;
  crRange.ciMax=crCurSel.ciMax;

  if (nRangeLen=ExGetRangeTextW(hWnd, &crRange.ciMin, &crRange.ciMax, -1, &wszRange, AELB_ASIS, TRUE))
  {
    bDelete=TRUE;
    a=0, b=0;

    while (b < nRangeLen)
    {
      while (wszRange[b] == '\r' || wszRange[b] == '\n')
      {
        bDelete=TRUE;
        wszRange[a++]=wszRange[b++];
      }
      if (bDelete)
      {
        bDelete=FALSE;
        b++;
      }
      else wszRange[a++]=wszRange[b++];
    }
    wszRange[a]='\0';

    //Save scroll
    nFirstLine=SaveLineScroll(hWnd);

    ReplaceSelW(hWnd, wszRange, a, AELB_ASINPUT, AEREPT_COLUMNASIS|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);
    SetSel(hWnd, &crRange, AESELT_COLUMNASIS|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);

    //Restore scroll
    RestoreLineScroll(hWnd, nFirstLine);

    FreeText(wszRange);
    return TRUE;
  }
  SendMessage(hWnd, WM_KEYDOWN, VK_BACK, 0);
  SendMessage(hWnd, WM_KEYUP, VK_BACK, 0);
  return FALSE;
}

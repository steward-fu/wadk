BOOL DoEditDeleteTrailingWhitespacesW(HWND hWnd)
{
  AECHARRANGE crRange;
  AECHARINDEX ciInitialCaret=ciCurCaret;
  wchar_t *wszRange;
  INT_PTR nRangeLen;
  INT_PTR nNewRangeLen;
  wchar_t *wpRead;
  wchar_t *wpWrite;
  wchar_t *wpMaxRead;
  int nFirstLine=0;
  BOOL bSelection;
  BOOL bCaretAtStart=FALSE;
  BOOL bResult=FALSE;

  if (IsReadOnly(hWnd))
    return FALSE;
  if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))
    bCaretAtStart=TRUE;

  //Save scroll
  nFirstLine=SaveLineScroll(hWnd);

  if (!AEC_IndexCompare(&crCurSel.ciMin, &crCurSel.ciMax))
  {
    SendMessage(hWnd, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&crRange.ciMin);
    SendMessage(hWnd, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&crRange.ciMax);
    bSelection=FALSE;
  }
  else
  {
    crRange.ciMin=crCurSel.ciMin;
    crRange.ciMax=crCurSel.ciMax;
    bSelection=TRUE;
  }

  if (nRangeLen=ExGetRangeTextW(hWnd, &crRange.ciMin, &crRange.ciMax, -1, &wszRange, AELB_ASIS, TRUE))
  {
    wpMaxRead=wszRange + nRangeLen;

    for (wpWrite=wszRange, wpRead=wszRange; wpRead < wpMaxRead; *wpWrite++=*wpRead++)
    {
      if (*wpRead == '\r' || *wpRead == '\n')
      {
        while (--wpWrite >= wszRange && (*wpWrite == '\t' || *wpWrite == ' '));
        ++wpWrite;
      }
    }
    while (--wpWrite >= wszRange && (*wpWrite == '\t' || *wpWrite == ' '));
    ++wpWrite;
    *wpWrite=L'\0';
    nNewRangeLen=wpWrite - wszRange;

    if (nRangeLen != nNewRangeLen)
    {
      if (!bSelection)
        SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, &crRange.ciMax);

      ReplaceSelW(hWnd, wszRange, nNewRangeLen, AELB_ASINPUT, AEREPT_COLUMNASIS|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);

      //Update selection
      if (!bSelection)
      {
        SendMessage(hWnd, AEM_INDEXUPDATE, 0, (LPARAM)&ciInitialCaret);
        crRange.ciMin=ciInitialCaret;
        crRange.ciMax=ciInitialCaret;
      }
      SetSel(hWnd, &crRange, AESELT_COLUMNASIS|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);
      bResult=TRUE;
    }
    FreeText(wszRange);
  }

  //Restore scroll
  RestoreLineScroll(hWnd, nFirstLine);

  return bResult;
}

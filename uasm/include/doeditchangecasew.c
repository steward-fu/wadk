BOOL DoEditChangeCaseW(HWND hWnd, int nCase)
{
  AECHARRANGE crRange;
  AECHARINDEX ciInitialCaret=ciCurCaret;
  wchar_t *wszRange;
  wchar_t *wpStart;
  wchar_t *wpEnd;
  int nFirstLine=0;
  INT_PTR nRangeLen;
  INT_PTR i;
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
    wpStart=wszRange;
    wpEnd=wpStart + nRangeLen;

    if (nCase == UPPERCASE)
    {
      for (i=0; i < nRangeLen; ++i)
        wszRange[i]=WideCharUpper(wszRange[i]);
    }
    else if (nCase == LOWERCASE)
    {
      for (i=0; i < nRangeLen; ++i)
        wszRange[i]=WideCharLower(wszRange[i]);
    }
    else if (nCase == SENTENCECASE)
    {
      while (wpStart < wpEnd)
      {
        while (wpStart < wpEnd && (AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart) || AKD_wcschr(STR_SENTENCE_DELIMITERSW, *wpStart)))
        {
          ++wpStart;
        }
        if (wpStart < wpEnd)
        {
          *wpStart=WideCharUpper(*wpStart);
          ++wpStart;
        }
        while (wpStart < wpEnd && !AKD_wcschr(STR_SENTENCE_DELIMITERSW, *wpStart))
        {
          *wpStart=WideCharLower(*wpStart);
          ++wpStart;
        }
      }
    }
    else if (nCase == TITLECASE)
    {
      while (wpStart < wpEnd)
      {
        while (wpStart < wpEnd && AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart))
        {
          ++wpStart;
        }
        if (wpStart < wpEnd)
        {
          *wpStart=WideCharUpper(*wpStart);
          ++wpStart;
        }
        while (wpStart < wpEnd && !AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart))
        {
          *wpStart=WideCharLower(*wpStart);
          ++wpStart;
        }
      }
    }
    else if (nCase == INVERTCASE)
    {
      while (wpStart < wpEnd)
      {
        if (WideCharLower(*wpStart) == *wpStart)
        {
          *wpStart=WideCharUpper(*wpStart);
          ++wpStart;
        }
        else
        {
          *wpStart=WideCharLower(*wpStart);
          ++wpStart;
        }
      }
    }

    if (!bSelection)
      SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, &crRange.ciMax);

    ReplaceSelW(hWnd, wszRange, -1, AELB_ASINPUT, AEREPT_COLUMNASIS|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);

    //Update selection
    if (!bSelection)
    {
      SendMessage(hWnd, AEM_INDEXUPDATE, 0, (LPARAM)&ciInitialCaret);
      crRange.ciMin=ciInitialCaret;
      crRange.ciMax=ciInitialCaret;
    }
    SetSel(hWnd, &crRange, AESELT_COLUMNASIS|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);

    FreeText(wszRange);
    bResult=TRUE;
  }

  //Restore scroll
  RestoreLineScroll(hWnd, nFirstLine);

  return bResult;
}

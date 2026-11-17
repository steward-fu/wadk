BOOL DoEditInsertStringInSelectionW(HWND hWnd, int nAction, const wchar_t *wpString)
{
  AECHARRANGE crRange;
  AETEXTRANGEW tr;
  wchar_t *wszRange=NULL;
  INT_PTR nRangeLen;
  INT_PTR nStringLenAll;
  INT_PTR nBufferLen;
  int nStringLen;
  int nStringBytes;
  int nFirstLine=0;
  INT_PTR a=0;
  INT_PTR b=0;
  INT_PTR i;
  BOOL bColumnSel;
  BOOL bCaretAtStart=FALSE;
  BOOL bResult=FALSE;

  if (!(nAction & STRSEL_CHECK) && IsReadOnly(hWnd))
    return FALSE;
  if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))
    bCaretAtStart=TRUE;
  crRange.ciMin=crCurSel.ciMin;
  crRange.ciMax=crCurSel.ciMax;

  if (crRange.ciMin.nLine != crRange.ciMax.nLine)
  {
    if (nAction & STRSEL_CHECK) return TRUE;

    if (!(bColumnSel=(BOOL)SendMessage(hWnd, AEM_GETCOLUMNSEL, 0, 0)))
    {
      SendMessage(hWnd, AEM_GETINDEX, AEGI_WRAPLINEBEGIN, (LPARAM)&crRange.ciMin);
      if (!AEC_IsFirstCharInLine(&crRange.ciMax))
      {
        SendMessage(hWnd, AEM_GETINDEX, AEGI_WRAPLINEEND, (LPARAM)&crRange.ciMax);
        //SendMessage(hWnd, AEM_GETINDEX, AEGI_NEXTLINE, (LPARAM)&crRange.ciMax);
      }
    }

    if (nRangeLen=IndexSubtract(hWnd, &crRange.ciMax, &crRange.ciMin, AELB_ASIS, bColumnSel))
    {
      nStringLen=(int)xstrlenW(wpString);
      nStringBytes=nStringLen * sizeof(wchar_t);

      //Save scroll
      nFirstLine=SaveLineScroll(hWnd);

      if (!bColumnSel)
        SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, NULL);

      if (nAction & STRSEL_INSERT)
      {
        nStringLenAll=(crRange.ciMax.nLine - crRange.ciMin.nLine + 1) * nStringLen;
        nBufferLen=nRangeLen + nStringLenAll;

        if (wszRange=AllocWideStr(nBufferLen + 1))
        {
          tr.cr.ciMin=crRange.ciMin;
          tr.cr.ciMax=crRange.ciMax;
          tr.bColumnSel=bColumnSel;
          tr.pBuffer=wszRange + nStringLenAll;
          tr.dwBufferMax=(UINT_PTR)-1;
          tr.nNewLine=AELB_ASIS;
          tr.bFillSpaces=TRUE;
          SendMessage(hWnd, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr);
          b=nStringLenAll;

          xmemcpy(wszRange, wpString, nStringBytes);
          a=nStringLen;

          while (b < nBufferLen)
          {
            if (wszRange[b] == '\r' && wszRange[b + 1] == '\r' && wszRange[b + 2] == '\n')
            {
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\r' && wszRange[b + 1] == '\n')
            {
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\r')
            {
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\n')
            {
              wszRange[a++]=wszRange[b++];
            }
            else
            {
              wszRange[a++]=wszRange[b++];
              continue;
            }

            if (b < nBufferLen || bColumnSel)
            {
              xmemcpy(wszRange + a, wpString, nStringBytes);
              a+=nStringLen;
            }
          }
          wszRange[a]='\0';
          bResult=TRUE;
        }
      }
      else if (nAction & STRSEL_DELETE)
      {
        if (wszRange=AllocWideStr(nRangeLen + 1))
        {
          tr.cr.ciMin=crRange.ciMin;
          tr.cr.ciMax=crRange.ciMax;
          tr.bColumnSel=bColumnSel;
          tr.pBuffer=wszRange;
          tr.dwBufferMax=(UINT_PTR)-1;
          tr.nNewLine=AELB_ASIS;
          tr.bFillSpaces=TRUE;
          SendMessage(hWnd, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr);

          if (nAction & STRSEL_TAB)
          {
            if (wszRange[b] == '\t')
              ++b;
            else
              for (i=0; i < lpFrameCurrent->nTabStopSize && wszRange[b] == ' '; ++i, ++b);
          }
          else if (nAction & STRSEL_SPACE)
          {
            if (wszRange[b] == ' ' || wszRange[b] == '\t')
              ++b;
          }
          else if (nAction & STRSEL_COMENT)
          {
			      if (wszRange[b] == ';'|| wszRange[b] == '\t')
              ++b;
          }
          else
          {
            if (!xmemcmp(wszRange + b, wpString, nStringBytes))
              b+=nStringLen;
          }

          while (b < nRangeLen)
          {
            if (wszRange[b] == '\r' && wszRange[b + 1] == '\r' && wszRange[b + 2] == '\n')
            {
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\r' && wszRange[b + 1] == '\n')
            {
              wszRange[a++]=wszRange[b++];
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\r')
            {
              wszRange[a++]=wszRange[b++];
            }
            else if (wszRange[b] == '\n')
            {
              wszRange[a++]=wszRange[b++];
            }
            else
            {
              wszRange[a++]=wszRange[b++];
              continue;
            }

            if (b < nRangeLen)
            {
              if (nAction & STRSEL_TAB)
              {
                if (wszRange[b] == '\t')
                  ++b;
                else
                  for (i=0; i < lpFrameCurrent->nTabStopSize && wszRange[b] == ' '; ++i, ++b);
              }
              else if (nAction & STRSEL_SPACE)
              {
                if (wszRange[b] == ' ' || wszRange[b] == '\t')
                  ++b;
              }
              else
              {
                if (!xmemcmp(wszRange + b, wpString, nStringBytes))
                  b+=nStringLen;
              }
            }
          }
          wszRange[a]='\0';
          bResult=TRUE;
        }
      }

      if (bResult)
      {
        ReplaceSelW(hWnd, wszRange, a, AELB_ASINPUT, (bColumnSel?AEREPT_COLUMNON:0)|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);
        SetSel(hWnd, &crRange, (bColumnSel?AESELT_COLUMNON:0)|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);
      }

      //Restore scroll
      RestoreLineScroll(hWnd, nFirstLine);

      FreeWideStr(wszRange);
      return bResult;
    }
  }
  if (nAction & STRSEL_CHECK) return FALSE;

  return TRUE;
}
    jmp aexit
    mov eax,TRUE
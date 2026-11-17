DoEditChangeCaseW PROC FRAME USES rbx rbp rdi rsi r12 r13 r14 r15 hWnd:HWND,nCase:SDWORD
local crRange         :AECHARRANGE 
local ciInitialCaret  :AECHARINDEX ;=ciCurCaret
local wszRange        :PTR wchar_t 
local bResult         :BOOL      ;=FALSE
local bCaretAtStart   :BOOL
local bSelection      :BOOL 
  ;//wchar_t *wpStart r12
  ;//wchar_t *wpEnd r13
  ;//int nFirstLine=0 edi
  ;//INT_PTR nRangeLen r15
  ;//INT_PTR i rbp
  
  xor edi,edi 
  mov bCaretAtStart,edi
  mov bResult,edi
  mov r14,rcx
  mov rbx,lpFrameCurrent
  cpyi2i ciInitialCaret,ciCurCaret
  .if (dwinvoke(IsReadOnly,rcx))
    xor eax,eax
    jmp aexit
  .endif
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR ciCurCaret))
    mov bCaretAtStart,TRUE
  .endif
  ;//Save scroll
  mov edi,dwinvoke(SaveLineScroll,r14)
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR crCurSel.ciMax))
    invoke SendMessage,r14,AEM_GETINDEX,AEGI_FIRSTCHAR,ADDR crRange.ciMin
    invoke SendMessage,r14,AEM_GETINDEX,AEGI_LASTCHAR,ADDR crRange.ciMax
    mov bSelection,FALSE
  .else
    cpyi2i crRange.ciMin,crCurSel.ciMin
    cpyi2i crRange.ciMax,crCurSel.ciMax
    mov bSelection,TRUE
  .endif
  mov r15,qwinvoke(ExGetRangeTextW,r14,ADDR crRange.ciMin,ADDR crRange.ciMax,-1,ADDR wszRange,AELB_ASIS,TRUE)
  .if (r15)
    mov r12,wszRange
    mov rsi,r12
    lea r13,[r12+r15*2]
    .if (nCase == UPPERCASE)
      .for (rbp=0 ¦ rbp < r15 ¦ rbp++)
        invoke WideCharUpper,WPTR[rsi+rbp*2]
        mov [rsi+rbp*2],ax
      .endfor
    .elseif (nCase == LOWERCASE)
      .for (rbp=0 ¦ rbp < r15 ¦ rbp++)
        invoke WideCharLower,WPTR[rsi+rbp*2]
        mov [rsi+rbp*2],ax
      .endfor
    .elseif (nCase == SENTENCECASE)
      .while (r12 < r13)
      	.while (r12 < r13)
          .if (qwinvoke(AKD_wcschr,ADDR[rbx].FRAMEDATA.wszWordDelimiters,WPTR[r12]))
            add r12,2
          .elseif (qwinvoke(AKD_wcschr,ADDR STR_SENTENCE_DELIMITERSW,WPTR[r12]))
            add r12,2
          .else
            .break
          .endif
        .endw
        .if (r12 < r13)
          invoke WideCharUpper,WPTR[r12]
          mov [r12],ax
          add r12,2
        .endif
        .while (r12 < r13 && !qwinvoke(AKD_wcschr,ADDR STR_SENTENCE_DELIMITERSW,WPTR[r12]))
          invoke WideCharLower,WPTR[r12]
          mov [r12],ax
          add r12,2
        .endw
      .endw
    .elseif (nCase == TITLECASE)
      .while (r12 < r13)
        .while (r12 < r13 && qwinvoke(AKD_wcschr,ADDR[rbx].FRAMEDATA.wszWordDelimiters,WPTR[r12]))
          add r12,2
        .endw
        .if (r12 < r13)
          invoke WideCharUpper,WPTR[r12]
          mov [r12],ax
          add r12,2
        .endif
        .while (r12 < r13 && !qwinvoke(AKD_wcschr,ADDR[rbx].FRAMEDATA.wszWordDelimiters,WPTR[r12]))
          invoke WideCharLower,WPTR[r12]
          mov [r12],ax
          add r12,2
        .endw
      .endw
    .elseif (nCase == INVERTCASE)
      .while (r12 < r13)
        invoke WideCharLower,WPTR[r12]
        .if (ax == WPTR[r12])
          invoke WideCharUpper,WPTR[r12]
          mov [r12],ax
          add r12,2
        .else
          invoke WideCharLower,WPTR[r12]
          mov [r12],ax
          add r12,2
        .endif
      .endw
    .endif
    .if (!bSelection)
      invoke SetSel,r14,ADDR crRange,AESELT_LOCKSCROLL,ADDR crRange.ciMax
    .endif
    invoke ReplaceSelW,r14,wszRange,-1,AELB_ASINPUT,AEREPT_COLUMNASIS or AEREPT_LOCKSCROLL,ADDR crRange.ciMin,ADDR crRange.ciMax
    ;//Update selection
    .if (!bSelection)
      invoke SendMessage,r14,AEM_INDEXUPDATE,0,ADDR ciInitialCaret
      cpyi2i crRange.ciMin,ciInitialCaret
      cpyi2i crRange.ciMax,ciInitialCaret
    .endif
    .if (bCaretAtStart)
      lea r9,crRange.ciMin
    .else 
      lea r9,crRange.ciMax
    .endif
    invoke SetSel,r14,ADDR crRange,AESELT_COLUMNASIS or AESELT_LOCKSCROLL,r9
    invoke FreeText,wszRange
    mov bResult,TRUE
  .endif
  ;//Restore scroll
  invoke RestoreLineScroll,r14,edi
  mov eax,bResult
aexit:
  ret
DoEditChangeCaseW ENDP

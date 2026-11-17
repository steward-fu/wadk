DoEditInsertStringInSelectionW PROC FRAME USES rbx rbp rdi rsi r12 r13 r14 r15 hWnd:HWND,nAction:SDWORD,wpString:PTR wchar_t 
local crRange      :AECHARRANGE 
local tr           :AETEXTRANGEW 
local nRangeLen    :INT_PTR 
local nStringLenAll:INT_PTR 
local nBufferLen   :INT_PTR 
local nFirstLine   :SDWORD      ;=0  
local bColumnSel   :BOOL    
local bCaretAtStart:BOOL          ;=FALSE
local bResult      :BOOL          ;=FALSE
  ;//wchar_t *wszRange=NULL       rsi
  ;int nStringLen   rbx
  ;int nStringBytes rbp
  
  ;INT_PTR a=0 r12
  ;INT_PTR b=0 r13
  mov r15,lpFrameCurrent
  mov r14,rcx
  mov rdi,r8
  xor esi,esi
  mov nFirstLine,esi
  mov r12,rsi
  mov r13,rsi
  .if (!(nAction & STRSEL_CHECK) && dwinvoke(IsReadOnly,r14))
    xor eax,eax
    jmp aexit
  .endif
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR ciCurCaret))
    mov bCaretAtStart,TRUE
  .endif
  cpyi2i crRange.ciMin,crCurSel.ciMin
  cpyi2i crRange.ciMax,crCurSel.ciMax
  mov eax,crRange.ciMin.nLine
  .if (eax != crRange.ciMax.nLine)
    .if (nAction & STRSEL_CHECK)
      jmp aexit
      mov eax,TRUE
    .endif
    mov bColumnSel,dwinvoke(SendMessage,r14, AEM_GETCOLUMNSEL,0,0)
    .if (!eax)
      invoke SendMessage,r14, AEM_GETINDEX, AEGI_WRAPLINEBEGIN,ADDR crRange.ciMin
      .if (!dwinvoke(AEC_IsFirstCharInLine,ADDR crRange.ciMax))
        invoke SendMessage,r14, AEM_GETINDEX, AEGI_WRAPLINEEND,ADDR crRange.ciMax
      .endif
    .endif
    mov nRangeLen,qwinvoke(IndexSubtract,r14,ADDR crRange.ciMax,ADDR crRange.ciMin,AELB_ASIS,bColumnSel)
    .if (eax)
      mov rbx,qwinvoke(xstrlenW,rdi)
      shl eax,1
      movsxd rbp,eax
      ;//Save scroll
      mov nFirstLine,dwinvoke(SaveLineScroll,r14)
      .if (!bColumnSel)
        invoke SetSel,r14,ADDR crRange,AESELT_LOCKSCROLL,NULL
      .endif
      .if (nAction & STRSEL_INSERT)
        mov eax,crRange.ciMax.nLine
        sub eax,crRange.ciMin.nLine
        inc eax
        imul eax,ebx
        cdqe
        mov nStringLenAll,rax
        mov nBufferLen,qwar(nRangeLen,nStringLenAll)
        mov rcx,nBufferLen
        inc rcx
        mov rsi,qwinvoke(AllocWideStr,rcx)
        .if (rsi)
          cpyi2i tr.cr.ciMin,crRange.ciMin
          cpyi2i tr.cr.ciMax,crRange.ciMax
          mdw tr.bColumnSel,bColumnSel
          mov tr.pBuffer,qwar(rsi,nStringLenAll) 
          mov tr.dwBufferMax,-1
          mov tr.nNewLine,AELB_ASIS
          mov tr.bFillSpaces,TRUE
          invoke SendMessage,r14,AEM_GETTEXTRANGEW,0,ADDR tr
          mov r13,nStringLenAll
          invoke xmemcpy,rsi,rdi,rbp
          mov r12,rbx
          .while (r13 < nBufferLen)
            .if (WPTR[rsi+r13*2] == 13 && WPTR[rsi+r13*2+2] == 13 && WPTR[rsi+r13*2+4] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              mov ax,[rsi+r13*2+2]
              mov [rsi+r12*2+2],ax
              mov ax,[rsi+r13*2+4]
              mov [rsi+r12*2+4],ax
              add r12,3
              add r13,3
            .elseif (WPTR[rsi+r13*2] == 13 && WPTR[rsi+r13*2+2] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              mov ax,[rsi+r13*2+2]
              mov [rsi+r12*2+2],ax
              add r12,2
              add r13,2
            .elseif (WPTR[rsi+r13*2] == 13)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
            .elseif (WPTR[rsi+r13*2] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
            .else
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
              .continue
            .endif
            .if (r13 < nBufferLen || bColumnSel)
              invoke xmemcpy,ADDR[rsi+r12*2],rdi,rbp
              add r12,rbx
            .endif
          .endw
          mov WPTR[rsi+r12*2],0
          mov bResult,TRUE
        .endif
      .elseif (nAction & STRSEL_DELETE)
        mov rcx,nRangeLen
        inc rcx
        mov rsi,qwinvoke(AllocWideStr,rcx)
        .if (rsi)
          cpyi2i tr.cr.ciMin,crRange.ciMin
          cpyi2i tr.cr.ciMax,crRange.ciMax
          mdw tr.bColumnSel,bColumnSel
          mov tr.pBuffer,rsi
          mov tr.dwBufferMax,-1
          mov tr.nNewLine,AELB_ASIS
          mov tr.bFillSpaces,TRUE
          invoke SendMessage,r14,AEM_GETTEXTRANGEW,0,ADDR tr
          .if (nAction & STRSEL_TAB)
            .if (WPTR[rsi+r13*2] == 9)
              inc r13
            .else
              .for (eax=0 ¦ eax < [r15].FRAMEDATA.nTabStopSize && WORD PTR[rsi+r13*2] == 32 ¦ eax++,r13++)
              .endfor
            .endif
          .elseif (nAction & STRSEL_SPACE)
            .if (WPTR[rsi+r13*2] == 32 || WPTR[rsi+r13*2] == 9)
              inc r13
            .endif
          .elseif (nAction & STRSEL_COMENT)
			      .if (WPTR[rsi+r13*2] == 3bh || WPTR[rsi+r13*2] == 9)
              inc r13
            .endif
          .else
            .if (!dwinvoke(xmemcmp,ADDR[rsi+r13*2],rdi,rbp))
              add r13,rbx
            .endif
          .endif

          .while (r13 < nRangeLen)
            .if (WPTR[rsi+r13*2] == 13 && WPTR[rsi+r13*2+2] == 13 && WPTR[rsi+r13*2+4] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              mov ax,[rsi+r13*2+2]
              mov [rsi+r12*2+2],ax
              mov ax,[rsi+r13*2+4]
              mov [rsi+r12*2+4],ax
              add r12,3
              add r13,3
            .elseif (WPTR[rsi+r13*2] == 13 && WPTR[rsi+r13*2+2] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              mov ax,[rsi+r13*2+2]
              mov [rsi+r12*2+2],ax
              add r12,2
              add r13,2
              .elseif(WPTR[rsi + r13 * 2] == 13)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
              .elseif (WPTR[rsi + r13 * 2] == 10)
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
            .else
              mov ax,[rsi+r13*2]
              mov [rsi+r12*2],ax
              inc r12
              inc r13
              .continue
            .endif
            .if (r13 < nRangeLen)
              .if (nAction & STRSEL_TAB)
                .if (WPTR[rsi+r13*2] == 9)
                  inc r13
                .else
                  .for (eax=0 ¦ eax < [r15].FRAMEDATA.nTabStopSize && WORD PTR[rsi+r13*2] == 32 ¦ eax++,r13++)
                  .endfor
                .endif
              .elseif (nAction & STRSEL_SPACE)
                .if (WPTR[rsi+r13*2] == 32 || WPTR[rsi+r13*2] == 9)
                  inc r13
                .endif
              .else
                .if (!dwinvoke(xmemcmp,ADDR[rsi+r13*2],rdi,rbp))
                  add r13,rbx
                .endif
              .endif
            .endif
          .endw
          mov WPTR[rsi+r12*2],0
          mov bResult,TRUE
        .endif
      .endif
      .if (bResult)
         xor eax,eax
         .if (bColumnSel)
           mov eax,AEREPT_COLUMNON
         .endif
         or eax,AEREPT_LOCKSCROLL
        invoke ReplaceSelW,r14,rsi,r12,AELB_ASINPUT,eax,ADDR crRange.ciMin,ADDR crRange.ciMax
         xor r8d,r8d
         .if (bColumnSel)
           mov r8d,AESELT_COLUMNON
         .endif  
         or r8d,AESELT_LOCKSCROLL
        .if (bCaretAtStart)
          lea r9,crRange.ciMin
        .else
          lea r9,crRange.ciMax
        .endif
        invoke SetSel,r14,ADDR crRange,r8d,r9
      .endif
      ;//Restore scroll
      invoke RestoreLineScroll,r14,nFirstLine
      invoke FreeWideStr,rsi
      mov eax,bResult
      jmp aexit
    .endif
  .endif
  .if (nAction & STRSEL_CHECK)
    xor eax,eax
    jmp aexit
  .endif
  mov eax,TRUE
aexit:
  ret
DoEditInsertStringInSelectionW ENDP

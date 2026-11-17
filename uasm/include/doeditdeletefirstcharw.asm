DoEditDeleteFirstCharW PROC FRAME USES rbx rbp rdi rsi r12 r13 r14 r15 hWnd:HWND
local crRange    :AECHARRANGE 
local wszRange   :PTR wchar_t 
;//local nRangeLen  :INT_PTR r15
;//local nFirstLine :SDWORD   edi   ;=0
;//bDelete          :BOOL     ebx
;//bCaretAtStart    :BOOL     ebp   ;=FALSE
  ;//INT_PTR a
  ;//INT_PTR b
  
  xor edi,edi
  mov ebp,edi
  mov r14,rcx
  mov r12,rdi
  mov r13,rdi
  .if (dwinvoke(IsReadOnly,r14))
    xor eax,eax
    jmp aexit
  .endif
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR ciCurCaret))
    mov ebp,TRUE
  .endif
  cpyi2i crRange.ciMin,crCurSel.ciMin
  cpyi2i crRange.ciMax,crCurSel.ciMax
  mov r15,qwinvoke(ExGetRangeTextW,r14,ADDR crRange.ciMin,ADDR crRange.ciMax,-1,ADDR wszRange,AELB_ASIS,TRUE)
  mov rsi,wszRange
  .if (rax)
    mov ebx,TRUE
    .while (r13 < r15)
      .while (WPTR[rsi+r13*2] == 13 || WPTR[rsi+r13*2] == 10)
        mov ebx,TRUE
        mov ax,[rsi+r13*2]
        mov [rsi+r12*2],ax
        inc r12
        inc r13
      .endw
      .if (ebx)
        mov ebx,FALSE
        inc r13
      .else 
        mov ax,[rsi+r13*2]
        mov [rsi+r12*2],ax
        inc r12
        inc r13
      .endif
    .endw
    mov WPTR[rsi+r12*2],0
    ;//Save scroll
    mov edi,dwinvoke(SaveLineScroll,r14)
    invoke ReplaceSelW,r14,rsi,r12,AELB_ASINPUT,AEREPT_COLUMNASIS or AEREPT_LOCKSCROLL,ADDR crRange.ciMin,ADDR crRange.ciMax
    .if (ebp)
      lea r9,crRange.ciMin
    .else
      lea r9,crRange.ciMax
    .endif
    invoke SetSel,r14,ADDR crRange,AESELT_COLUMNASIS or AESELT_LOCKSCROLL,r9
    ;//Restore scroll
    invoke RestoreLineScroll,r14,edi
    invoke FreeText,rsi
    mov eax,TRUE
    jmp aexit
  .endif
  invoke SendMessage,r14,WM_KEYDOWN,VK_BACK,0
  invoke SendMessage,r14,WM_KEYUP,VK_BACK,0
  xor eax,eax
aexit:
  ret
DoEditDeleteFirstCharW ENDP

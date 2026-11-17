DoEditDeleteTrailingWhitespacesW PROC FRAME USES rbx rbp rdi rsi r12 r13 r14 r15 hWnd:HWND 
local crRange         :AECHARRANGE 
local ciInitialCaret  :AECHARINDEX   ;//=ciCurCaret
local wszRange        :PTR wchar_t 
local bResult         :BOOL             ;=FALSE

;//  INT_PTR nRangeLen r15
  ;//INT_PTR nNewRangeLen
  ;//wchar_t *wpRead r12
  ;//wchar_t *wpWrite r13
  ;//wchar_t *wpMaxRead
  ;//int nFirstLine=0  edi
  ;//BOOL bSelection
  ;//BOOL bCaretAtStart=FALSE
  cpyi2i ciInitialCaret,ciCurCaret
  xor ebp,ebp
  mov bResult,ebp
  mov rdi,rbp
  mov r14,rcx
  .if (dwinvoke(IsReadOnly,r14))
    xor eax,eax
    jmp aexit
  .endif
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR ciCurCaret))
    mov ebp,TRUE
  .endif
  ;//Save scroll
  mov edi,dwinvoke(SaveLineScroll,r14)
  .if (!dwinvoke(AEC_IndexCompare,ADDR crCurSel.ciMin,ADDR crCurSel.ciMax))
    invoke SendMessage,r14,AEM_GETINDEX,AEGI_FIRSTCHAR,ADDR crRange.ciMin
    invoke SendMessage,r14,AEM_GETINDEX,AEGI_LASTCHAR,ADDR crRange.ciMax
    mov ebx,FALSE
  .else
    cpyi2i crRange.ciMin,crCurSel.ciMin
    cpyi2i crRange.ciMax,crCurSel.ciMax
    mov ebx,TRUE
  .endif
  mov r15,qwinvoke(ExGetRangeTextW,r14,ADDR crRange.ciMin,ADDR crRange.ciMax,-1,ADDR wszRange,AELB_ASIS,TRUE)
  .if (r15)
      mov r15,qwar(wszRange,r15)
    .for (r13=wszRange,r12=r13 ¦ r12 < r15 ¦ ax=[r12],[r13]=ax,r12+=2,r13+=2)
      .if (WPTR[r12] == 13 || WPTR[r12] == 10)
        .for(¦¦)  
      	  sub	r13, 2
      	  .break .if (r13 >= wszRange)
      	  movzx	eax, WORD PTR [r13]
      	  .break .if (eax != 9 || eax != 32)
      	.endfor 
        add r13,2
      .endif
    .endfor
    .for(¦¦)  
  	  sub	r13, 2
  	  .break .if (r13 >= wszRange)
  	  movzx	eax, WORD PTR [r13]
  	  .break .if (eax != 9 || eax != 32)
  	.endfor 
    add r13,2
    mov WPTR[r13],0
    mov rax,r13
    sub rax,wszRange
    sar rax,1
    mov rsi,rax
    .if (r15 != rsi)
      .if (!ebx)
        invoke SetSel,r14,ADDR crRange,AESELT_LOCKSCROLL,ADDR crRange.ciMax
      .endif
      invoke ReplaceSelW,r14,wszRange,rsi,AELB_ASINPUT,AEREPT_COLUMNASIS or AEREPT_LOCKSCROLL,ADDR crRange.ciMin,ADDR crRange.ciMax
      ;//Update selection
      .if (!ebx)
        invoke SendMessage,r14,AEM_INDEXUPDATE,0,ADDR ciInitialCaret
        cpyi2i crRange.ciMin,ciInitialCaret
        cpyi2i crRange.ciMax,ciInitialCaret
      .endif
      .if (ebp)
        lea r9,crRange.ciMin
      .else 
        lea r9,crRange.ciMax
      .endif
      invoke SetSel,r14,ADDR crRange,AESELT_COLUMNASIS or AESELT_LOCKSCROLL,r9
      mov bResult,TRUE
    .endif
    invoke FreeText,wszRange
  .endif
  ;//Restore scroll
  invoke RestoreLineScroll,r14,edi
  mov eax,bResult
aexit:
  ret
DoEditDeleteTrailingWhitespacesW ENDP

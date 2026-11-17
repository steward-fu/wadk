DoWindowTabView PROC FRAME USES rbx rbp rdi rsi r12 dwNewView:DWORD,bFirst:BOOL
  ;//DWORD dwOldView=moCur.dwTabOptionsMDI;esi
  ;//DWORD dwStyle;edi
  ;int nCommand=0;ebx
  mov ebx,ecx
  xor ebp,ebp
  mov esi,moCur.dwTabOptionsMDI
  .if (ebx & TAB_VIEW_TOP)
    mov ebp,IDM_WINDOW_TABVIEW_TOP
    mov ebx,TAB_VIEW_TOP
  .elseif (ebx & TAB_VIEW_BOTTOM)
    mov ebp,IDM_WINDOW_TABVIEW_BOTTOM
    mov ebx,TAB_VIEW_BOTTOM
  .elseif (ebx & TAB_VIEW_NONE)
    mov ebp,IDM_WINDOW_TABVIEW_NONE
    mov ebx,TAB_VIEW_NONE
  .endif
  .if (esi & TAB_VIEW_TOP)
    mov esi,TAB_VIEW_TOP
  .elseif (esi & TAB_VIEW_BOTTOM)
    mov esi,TAB_VIEW_BOTTOM
  .elseif (esi & TAB_VIEW_NONE)
    mov esi,TAB_VIEW_NONE
  .endif
  invoke CheckMenuRadioItem,hMainMenu,IDM_WINDOW_TABVIEW_TOP,IDM_WINDOW_TABVIEW_NONE,ebp,MF_BYCOMMAND
  .if (!(ebx & TAB_VIEW_NONE))
    mov r12d,MF_ENABLED
  .else  
    mov r12d,MF_GRAYED
  .endif
  invoke EnableMenuItem,hMainMenu,IDM_WINDOW_TABTYPE_STANDARD,r12d
  invoke EnableMenuItem,hMainMenu,IDM_WINDOW_TABTYPE_BUTTONS,r12d
  .if (!bOldComctl32)
    invoke EnableMenuItem,hMainMenu,IDM_WINDOW_TABTYPE_FLATBUTTONS,r12d
  .endif
  .if (bFirst != TRUE && ebx == esi) 
    jmp aexit
  .endif
  mov eax,moCur.dwTabOptionsMDI
  and	eax,-3
  and	eax,-5
  and	eax,-2
  mov moCur.dwTabOptionsMDI,eax
  or moCur.dwTabOptionsMDI,ebx
  .if (moCur.dwTabOptionsMDI & TAB_VIEW_TOP)
    mov edi,dwinvoke(GetWindowLongPtrWide,hTab,GWL_STYLE)
    mov r8d,edi
    and r8d,-3
    invoke SetWindowLongPtrWide,hTab,GWL_STYLE,r8d
  .elseif (moCur.dwTabOptionsMDI & TAB_VIEW_BOTTOM)
    mov edi,dwinvoke(GetWindowLongPtrWide,hTab,GWL_STYLE)
    mov r8d,edi
    or r8d,TCS_BOTTOM
    invoke SetWindowLongPtrWide,hTab,GWL_STYLE,r8d
  .endif
  .if(!(moCur.dwTabOptionsMDI & TAB_VIEW_NONE))
     mov edx,SW_SHOW
  .else   
    mov edx,SW_HIDE
  .endif
  invoke ShowWindow,hTab,edx
  invoke UpdateSize
aexit:
  ret
DoWindowTabView ENDP

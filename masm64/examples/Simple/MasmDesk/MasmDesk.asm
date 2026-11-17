; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc

    StartID equ <32768>         ; equate for lowest menu item start ID

    .data?
      hInstance dq ?
      hWnd      dq ?
      hIcon     dq ?
      hCursor   dq ?
      sWid      dq ?
      sHgt      dq ?
      hBrush    dq ?
      hMenu     dq ?
      uArray    dq ?            ; GLOBAL array handle for menu items content

    .data
      classname db "MASM64_Desktop",0
      caption db "Invisible",0

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

entry_point proc

  ; ---------------------------------------
  ; this is here so that the first call to
  ; GlobalFree has something to de-allocate
  ; ---------------------------------------
    mov uArray, alloc(1024)        

    mov hInstance, rv(GetModuleHandle,0)
    mov hIcon,     rv(LoadIcon,hInstance,10)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hBrush,    rv(CreateSolidBrush,00C4C4C4h)

    call main

    invoke ExitProcess,0

    ret

entry_point endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

main proc

    LOCAL wc      :WNDCLASSEX
    LOCAL lft     :QWORD
    LOCAL top     :QWORD
    LOCAL wid     :QWORD
    LOCAL hgt     :QWORD
    LOCAL .r15    :QWORD
    LOCAL buffer[260]:BYTE
    LOCAL pbuf    :QWORD

    mov wc.cbSize,         SIZEOF WNDCLASSEX
    mov wc.style,          CS_BYTEALIGNCLIENT or CS_BYTEALIGNWINDOW
    mov wc.lpfnWndProc,    ptr$(WndProc)
    mov wc.cbClsExtra,     0
    mov wc.cbWndExtra,     0
    mrm wc.hInstance,      hInstance
    mrm wc.hIcon,          hIcon
    mrm wc.hCursor,        hCursor
    mrm wc.hbrBackground,  hBrush
    mov wc.lpszMenuName,   0
    mov wc.lpszClassName,  ptr$(classname)
    mrm wc.hIconSm,        hIcon

    invoke RegisterClassEx,ADDR wc

    invoke CreateWindowEx,WS_EX_LEFT, \
                          ADDR classname,ADDR caption, \
                          WS_POPUP or WS_VISIBLE,\
                          0,0,sWid,sHgt,0,0,hInstance,0
    mov hWnd, rax

    invoke ShowWindow,hWnd,SW_SHOWMAXIMIZED
    invoke SetWindowPos,hWnd,HWND_BOTTOM,0,0,0,0,SWP_NOSIZE

    mov pbuf,ptr$(buffer)
    invoke GetAppPath,pbuf
    invoke szCatStr,pbuf,"menuini.txt"

    .if rv(exist,pbuf) {} 0
      invoke LoadINI,pbuf,1
    .endif

    call msgloop

    ret

main endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

msgloop proc

    LOCAL msg    :MSG
    LOCAL pmsg   :QWORD

    mov pmsg, ptr$(msg)                     ; get the msg structure address
    jmp gmsg                                ; jump directly to GetMessage()

  mloop:
    invoke TranslateMessage,pmsg
    invoke DispatchMessage,pmsg
  gmsg:
    test rax, rv(GetMessage,pmsg,0,0,0)     ; loop until GetMessage returns zero
    jnz mloop

    ret

msgloop endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

WndProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL dfbuff[260]:BYTE
    LOCAL hDC      :QWORD
    LOCAL Ps       :PAINTSTRUCT

    LOCAL pbuf1 :QWORD
    LOCAL pbuf2 :QWORD

    LOCAL buff1[260]:BYTE
    LOCAL buff2[512]:BYTE

    LOCAL .r14  :QWORD
    LOCAL .r15  :QWORD

    .switch uMsg
      .case WM_COMMAND
      ; ----------------------
      ; resource menu commands
      ; ----------------------
        .switch wParam
          .case 200
            invoke WinExec,"explorer.exe",SW_SHOW
          .case 201
            invoke WinExec,"cmd.exe",SW_SHOW
          .case 202
            invoke WinExec,"control.exe",SW_SHOW
          .case 203
            invoke WinExec,"taskmgr.exe",SW_SHOW
          .case 220
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL
          .case 300
            invoke MsgboxI,0, \
                   "Wickedly Crafted In Microsoft Assembler (MASM)", \
                   "About MASM64 Desktop",MB_OK,10
        .endsw

        ; -----------------------------------
        ; code to call custom menu procedures
        ; range = StartID to StartID + 16384
        ; -----------------------------------
          mov rax, StartID
          .if wParam }= rax
            add rax, 16384
            .if wParam { rax
              invoke process_user_menu,wParam
            .endif
          .endif
        ; -----------------------------------

      .case WM_PAINT
        mov hDC, rv(BeginPaint,hWin,ADDR Ps)
        invoke PaintDesktop,hDC
        invoke EndPaint,hWin,ADDR Ps

      .case WM_SETFOCUS
        invoke SetWindowPos,hWin,HWND_BOTTOM,0,0,0,0,SWP_NOSIZE

      .case WM_CREATE
        invoke LoadMenu,hInstance,100
        mov hMenu, rax
        invoke SetMenu,hWin,hMenu
        .return 0

      .case WM_CLOSE
        invoke SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        invoke PostQuitMessage,NULL

    .endsw

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

LoadINI proc pFileName:QWORD,startpos:QWORD

  ; ////////////////////////////////////////////////
  ;
  ; pFileName is the address of the file name string
  ; startpos is the position on the main menu bar
  ;     AFTER the resource section fixed menu items
  ;
  ; \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    LOCAL pMem  :QWORD
    LOCAL lcnt  :QWORD
    LOCAL .r13  :QWORD
    LOCAL .r14  :QWORD
    LOCAL .r15  :QWORD
    LOCAL strv  :QWORD
    LOCAL pArray:QWORD

    LOCAL pstr1 :QWORD
    LOCAL pstr2 :QWORD
    LOCAL buff1[256]:BYTE
    LOCAL buff2[512]:BYTE
    LOCAL bptr  :QWORD
    LOCAL pchr[4]:BYTE

    LOCAL mnu1  :QWORD
    LOCAL cntr  :QWORD
    LOCAL mStart:QWORD
    LOCAL hFlag :QWORD

    mov .r13, r13
    mov .r14, r14
    mov .r15, r15

    mov pstr1, ptr$(buff1)
    mov pstr2, ptr$(buff2)
    mov bptr,  ptr$(pchr)                                   ; pointer to leading byte

    mov rax, startpos                                       ; copy startpos into cntr
    mov cntr, rax
    mov mStart, StartID
    mov hFlag, 0

    mov pMem, loadfile(pFileName)                           ; load the INI file
    mov lcnt, rv(ltok,pMem,ADDR pArray)                     ; tokenize the INI file

    invoke GlobalFree,uArray                                ; release array memory before re-allocating
    mov uArray, rv(fixed_array,lcnt,512)                    ; this array holds the user strings

    mov r13, lcnt
    mov r14, pArray
    mov r15, uArray

  ; ***********************************************************************

  @@:
    mov strv, rv(split_line,QWORD PTR [r14],pstr1,pstr2)
    invoke szLeft,QWORD PTR [r14],bptr,1                    ; get 1st character

    .if strv } 0                                            ; if no comma then line = heading, separator or error
    ; ------------------------
    ;  write user entry here
    ; ------------------------
      .if hFlag {} 0
        invoke AppendMenu,mnu1,MF_STRING,mStart,pstr1       ; the MENU string
        add mStart, 1

        ; ***********************************************
        invoke szCopy,pstr2,QWORD PTR [r15]                 ; write USER string to array
        add r15, 8
        ; ***********************************************

      .else
        invoke MessageBox,0,"You must have a heading first","Menu Error",MB_OK
      .endif
    ; ------------------------
      jmp nxt1

    .else
      test rv(szCmp,bptr,"["), rax
      jz opt1

    ; ------------------
    ; write heading here
    ; ------------------
      mov mnu1, rv(CreatePopupMenu)
      invoke AppendMenu,hMenu,MF_BYPOSITION or MF_STRING or MF_POPUP,mnu1,0
      invoke szRemove,QWORD PTR [r14],QWORD PTR [r14],"["
      invoke szRemove,QWORD PTR [r14],QWORD PTR [r14],"]"
      invoke InsertMenu,hMenu,cntr,MF_BYPOSITION or MF_POPUP,mnu1,QWORD PTR [r14]
      add cntr, 1
      mov hFlag, 1
    ; ------------------
      jmp nxt1

    opt1:
      test rv(szCmp,bptr,"-"), rax
      jz opt2

    ; --------------------
    ; write separator here
    ; --------------------
      invoke AppendMenu,mnu1,MF_SEPARATOR,mnu1,0
    ; --------------------
      jmp nxt1

    opt2:
    ; --------------------------
    ; display error message here
    ; --------------------------
      invoke MessageBox,hWnd,"Missing comma in entry","Menu Error",MB_OK
    ; --------------------------
      jmp nxt1

    .endif

  nxt1:
    add r14, 8
    sub r13, 1
    jnz @B

  ; ***********************************************************************

    invoke DrawMenuBar,hWnd

    mfree pMem                                              ; release file memory
    mfree pArray                                            ; release array memory

    mov r13, .r13
    mov r14, .r14
    mov r15, .r15

    ret

LoadINI endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

split_line proc ptrstr:QWORD,pstr1:QWORD,pstr2:QWORD
  ; ------------------------------------------------------
  ; split ptrstr into pstr1 and pstr2 from either side of
  ; comma separator returns zero if no comma separator
  ; ------------------------------------------------------
    LOCAL cpos   :QWORD

    invoke StrStr,ptrstr,","            ; get the comma position in ptrstr
    mov cpos, rax                       ; StrStr returns either an OFFSET or 0 on no match
    test rax, rax                       ; test if return value is zero
    jnz @F
    ret                                 ; return zero on no comma
  @@:

    mov rax, ptrstr                     ; load address into RAX
    sub cpos, rax                       ; sub address from OFFSET to get length
    invoke szLeft,ptrstr,pstr1,cpos     ; read left side string into pstr1
    mov rax, cpos                       ; move cpos into RAX
    add ptrstr, rax                     ; add cpos to source string
    add ptrstr, 1                       ; add 1 to pass the ","
    invoke szCopy,ptrstr,pstr2          ; copy balance to 2nd buffer

    ret

split_line endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

process_user_menu proc wParam:QWORD

  ; |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
  ;
  ; wParam  : is passed directly from the WM_COMMAND in the "WndProc"
  ; uArray  : is a global array handle for an array of user defined content
  ; StartID : is an equate for the lowest menu item number
  ;
  ; |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    LOCAL .r15  :QWORD
    LOCAL .r14  :QWORD

    mov .r14, r14                       ; preserve r14
    mov .r15, r15                       ; preserve r15

    mov r15, uArray                     ; load array address into r15           <** global array handle

    mov r14, wParam                     ; load wParam into r14
    sub r14, StartID                    ; sub menu start number from wParam     <** user defined equate

  ; /////////////////////////////////////////////////////////////////////

    invoke run_menu_choice,QWORD PTR [r15+r14*8]

  ; \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    mov r15, .r15                       ; restore r15
    mov r14, .r14                       ; restore r14

    ret

process_user_menu endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

run_menu_choice proc pcmd:QWORD

    LOCAL extp  :QWORD                  ; pointer
    LOCAL extb[16]:BYTE                 ; buffer

    mov extp, ptr$(extb)                ; load buffer address into pointer
    invoke szRight,pcmd,extp,4          ; get last 4 characters
    invoke szLower,extp,extp            ; convert to lower case

    cmp rv(szCmp,extp,".hlp"), 0
    je @F
    invoke ShellExecute,hWnd,"open",pcmd,0,0,SW_SHOW
    ret
  @@:

    cmp rv(szCmp,extp,".chm"), 0
    je @F
    invoke ShellExecute,hWnd,"open",pcmd,0,0,SW_SHOW
    ret
  @@:

    cmp rv(szCmp,extp,".pdf"), 0
    je @F
    invoke ShellExecute,hWnd,"open",pcmd,0,0,SW_SHOW
    ret
  @@:

    invoke WinExec,pcmd,1               ; default to WinExec

    ret

run_menu_choice endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end
























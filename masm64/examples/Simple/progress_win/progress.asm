; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc

    PBM_SETRANGE    equ WM_USER+1
    PBM_SETPOS      equ WM_USER+2

    .data?
      hInstance dq ?
      hWnd      dq ?
      hIcon     dq ?
      hCursor   dq ?
      sWid      dq ?
      sHgt      dq ?
      hBrush    dq ?
      hProgress dq ?
      hButn1    dq ?
      cntr      dq ?
      tmID      dq ?
      hFont     dq ?
      pbar      dd ?

    .data
      classname db "template_class",0
      caption db "Progress Bar/Timer Demo",0

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

STACKFRAME 112, 256

entry_point proc

    GdiPlusBegin                    ; initialise GDIPlus

    mov hInstance, rv(GetModuleHandle,0)
    mov hIcon,     rv(LoadIcon,hInstance,10)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hBrush,    rv(CreateSolidBrush,00C4C4C4h)

    call main

    GdiPlusEnd                      ; GdiPlus cleanup

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

    mov wid, function(getpercent,sWid,45)   ; 65% screen width
    mov hgt, function(getpercent,sHgt,45)   ; 65% screen height

    invoke aspect_ratio,hgt,45              ; height + 45%
    cmp wid, rax                            ; if wid > rax
    jle @F
    mov wid, rax                            ; set wid to rax
  @@:
    mov rax, sWid                           ; calculate offset from left side
    sub rax, wid
    shr rax, 1
    mov lft, rax

    mov rax, sHgt                           ; calculate offset from top edge
    sub rax, hgt
    shr rax, 1
    mov top, rax

  ; ---------------------------------
  ; centre window at calculated sizes
  ; ---------------------------------
    invoke CreateWindowEx,WS_EX_LEFT or WS_EX_ACCEPTFILES, \
                          ADDR classname,ADDR caption, \
                          WS_OVERLAPPEDWINDOW or WS_VISIBLE,\
                          lft,top,wid,hgt,0,0,hInstance,0
    mov hWnd, rax

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
    LOCAL rct   :RECT

    .switch uMsg
      .case WM_COMMAND
        .switch wParam
          .case 200
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL
          .case 300
            invoke MsgboxI,hWin, \
                   "Generic 64 bit Template written with ML64.EXE", \
                   "About Generic Template",MB_OK,10

        ; -------------------------------------
        ; start the timer from the button click.
        ; -------------------------------------
          .case 400
          ; --------------------------------------------
          ; set the range of the progress bar (0 to 500)
          ; --------------------------------------------
            mov r11w, 500
            rol r11d, 16
            mov r11w, 0
            invoke SendMessage,hProgress,PBM_SETRANGE,0,r11d

            mov pbar, 0                             ; zero the location variable

            mov cntr, 0                             ; zero the counter
            invoke SetTimer,hWin,1,1,0              ; start the timer
            mov tmID, rax                           ; save timer ID in global

        .endsw

      .case WM_TIMER
            invoke SetWindowText,hWin,str$(cntr)
            add cntr, 1                             ; increment the counter

        ; ----------------------------------------
        ; increment the progress bar by 1 each
        ; instance of the timer message being sent
        ; ----------------------------------------
            add pbar, 1
            invoke SendMessage,hProgress,PBM_SETPOS,pbar,0

        ; --------------------------------------------------------
        ; shut down the timer when the count reaches preset number
        ; --------------------------------------------------------
            cmp cntr, 500                           ; test "cntr" against termination value
            jbe @F
            invoke KillTimer, hWin, tmID            ; terminate the timer
          @@:

      .case WM_CREATE
        mov hProgress, rv(progress_bar1,hInstance,hWin,20,20,600,20)
        mov hButn1, rv(button,hInstance,hWin,"Just Do It",20,20,150,22,400)
        mov hFont, GetFontHandle("Arial",16,600)
        invoke SendMessage,hButn1,WM_SETFONT,hFont,TRUE
        invoke LoadMenu,hInstance,100
        invoke SetMenu,hWin,rax
        .return 0

      .case WM_SIZE
        invoke GetClientRect,hWin,ADDR rct              ; get the client area size
      ; -------------------------------------
      ; space progress bar 20 pixel from left
      ; right and bottom of client area at 20
      ; pixels in height.
      ; -------------------------------------

        sspace equ <20>
        dspace equ <sspace+sspace>

        mov rct.left, sspace
        sub rct.right, dspace
        mrmd rct.top, rct.bottom
        sub rct.top, dspace
        mov rct.bottom, sspace

        invoke MoveWindow,hProgress,rct.left,rct.top,rct.right,rct.bottom,TRUE

      .case WM_DROPFILES
        invoke DragQueryFile,wParam,0,ADDR dfbuff,260
        invoke MsgboxI,hWin,ADDR dfbuff,"Drop File Name",MB_OK,10

      .case WM_CLOSE
        invoke DeleteObject,hFont
        invoke SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        invoke PostQuitMessage,NULL

    .endsw

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

progress_bar1 proc instance:QWORD,parent:QWORD,
                   lft:QWORD,top:QWORD,wid:QWORD,hgt:QWORD

    invoke CreateWindowEx,WS_EX_LEFT,"msctls_progress32", \
                          0,WS_VISIBLE or WS_CHILD or WS_BORDER,\
                          lft,top,wid,hgt,parent,0,instance,0
    ret

progress_bar1 endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end

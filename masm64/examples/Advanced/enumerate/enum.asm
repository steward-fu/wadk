; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc

    .data?
      hInstance dq ?
      hWnd      dq ?
      hIcon     dq ?
      hCursor   dq ?
      sWid      dq ?
      sHgt      dq ?
      hBrush    dq ?
      hButn1    dq ?
      hButn2    dq ?
      hButn3    dq ?
      hButn4    dq ?
      hButn5    dq ?
      bFont     dq ?
      lFont     dq ?
      hList     dq ?
      lpListProc dq ?

    backcolor equ <00333333h>

    .data
      classname db "MASM_Enumeration_Class",0
      caption db "Current Process Enumeration",0

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

entry_point proc

    GdiPlusBegin                    ; initialise GDIPlus

    mov hInstance, rv(GetModuleHandle,0)
    mov hIcon,     rv(LoadImage,hInstance,10,IMAGE_ICON,48,48,LR_LOADTRANSPARENT)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hBrush,    rv(CreateSolidBrush,005F5F5Fh)       ; background brush colour
    mov bFont,     GetFontHandle("Arial",15,400)        ; button font
    mov lFont,     GetFontHandle("FixedSys",9,400)      ; list box font

    call main

    invoke DeleteObject,bFont
    invoke DeleteObject,lFont

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

    mov wid, rv(getpercent,sWid,65)         ; 65% screen width
    mov hgt, rv(getpercent,sHgt,65)         ; 65% screen height

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

    invoke EnumWindows,ptr$(EnmProc),0

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

    LOCAL rct   :RECT

    .switch uMsg
      .case WM_COMMAND
        .switch wParam
          .case 600
            invoke SendMessage,hList,LB_RESETCONTENT,0,0            ; clear list
            invoke EnumWindows,ptr$(EnmProc),0                      ; reload list with current processes

          .case 601
            invoke SetFocus,hList
            .if rv(SendMessage,hList,LB_GETCURSEL,0,0) == LB_ERR    ; if nothing selected
              invoke SendMessage,hList,LB_SETCURSEL,0,0             ; set selection to 1st item
            .endif
            invoke SendMessage,hList,WM_LBUTTONDBLCLK,0,0           ; simulate dbl click on item

          .case 602
          about:
            .data
              msgtxt db "A 64 bit Portable Executable Application",13,10
                     db "Wickedly Crafted In Microsoft Assembler (MASM)",0
            .code
            invoke MsgboxI,hWin,ptr$(msgtxt)," About Process Enumeration",MB_OK,10

          .case 603
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL

        .endsw

      .case WM_CREATE
        mov hButn1, rv(button,hInstance,hWin,"Refresh",5,5,95,22,600)
        mov hButn2, rv(button,hInstance,hWin,"Display",105,5,95,22,601)
        mov hButn3, rv(button,hInstance,hWin,"About",205,5,95,22,602)
        mov hButn4, rv(button,hInstance,hWin,"Close",305,5,95,22,603)

        invoke SendMessage,hButn1,WM_SETFONT,bFont,TRUE
        invoke SendMessage,hButn2,WM_SETFONT,bFont,TRUE
        invoke SendMessage,hButn3,WM_SETFONT,bFont,TRUE
        invoke SendMessage,hButn4,WM_SETFONT,bFont,TRUE

      ; ---------------------------------
      ; create a list box and subclass it
      ; ---------------------------------
        mov hList, rv(listbox,hWin,hInstance,0,0,30,200,200,750)
        invoke SetWindowLongPtr,hList,GWL_WNDPROC,ADDR ListProc
        mov lpListProc, rax

        .return 0

      .case WM_CTLCOLORDLG                          ; dialog colour
        rcall CreateSolidBrush,backcolor
        ret

      .case WM_CTLCOLORSTATIC                       ; static controls
        rcall SetBkColor,wParam,backcolor
        rcall SetTextColor,wParam,00FFFFFFh
        rcall CreateSolidBrush,backcolor
        ret

      .case WM_CTLCOLOREDIT                         ; edit controls
        rcall SetBkColor,wParam,001111111h
        rcall SetTextColor,wParam,000000FFh
        rcall CreateSolidBrush,00111111h
        ret

      .case WM_CTLCOLORLISTBOX                      ; list box controls
        rcall SetBkColor,wParam,00222222h
        rcall SetTextColor,wParam,00DDDDDDh
        rcall CreateSolidBrush,00222222h
        ret

      .case WM_CTLCOLORBTN                          ; button border
        rcall CreateSolidBrush,backcolor
        ret

      .case WM_SIZE
        invoke GetClientRect,hWin,ADDR rct
        sub rct.bottom, 32
        invoke MoveWindow,hList,0,32,rct.right,rct.bottom,TRUE

      .case WM_SETFOCUS
        invoke SetFocus,hList

      .case WM_CLOSE
        invoke SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        invoke PostQuitMessage,NULL

    .endsw

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

listbox proc hparent:QWORD,instance:QWORD,text:QWORD, \
        topx:QWORD,topy:QWORD,wid:QWORD,hgt:QWORD,idnum:QWORD

    LOCAL lHandle :QWORD

    invoke CreateWindowEx,WS_EX_LEFT,"LISTBOX",text, \
                          WS_CHILD or WS_VISIBLE or LBS_HASSTRINGS or WS_VSCROLL or \
                          LBS_NOINTEGRALHEIGHT or LBS_DISABLENOSCROLL, \
                          topx,topy,wid,hgt,hparent,idnum,instance,0
    mov lHandle, rax
    invoke SendMessage,lHandle,WM_SETFONT,lFont,TRUE
    mov rax, lHandle

    ret

listbox endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

ListProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL csel  :QWORD
    LOCAL ptxt1 :QWORD
    LOCAL ptxt2 :QWORD

    LOCAL buffer1[1024]:BYTE
    LOCAL buffer2[1024]:BYTE

  ; -----------------------------
  ; Process control messages here
  ; -----------------------------

    .if uMsg == WM_LBUTTONDBLCLK
    process:
      mov ptxt1, ptr$(buffer1)
      mov ptxt2, ptr$(buffer2)
      mov csel, rv(SendMessage,hWin,LB_GETCURSEL,0,0)
      invoke SendMessage,hWin,LB_GETTEXT,csel,ptxt1

    ; ---------------------
    ; remove spaces padding
    ; ---------------------
      invoke szMono,ptxt1

    ; ------------------------------------------
    ; use alternate buffers for text replacement
    ; ------------------------------------------
      invoke szRep,ptxt1,ptxt2,"Class = ",chr$(13,10,"Class = ")
      invoke szRep,ptxt2,ptxt1,"Title = ",chr$(13,10,"Title = ")

      invoke MsgboxI,hWin,ptxt1,"Window Properties",MB_OK,10

    .elseif uMsg == WM_CHAR
      .switch wParam
        .case 13
          jmp process
      .endsw

    .endif

    invoke CallWindowProc,lpListProc,hWin,uMsg,wParam,lParam

    ret

ListProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

EnmProc proc eHandle:QWORD,lbHandle:QWORD

    LOCAL pbuf  :QWORD
    LOCAL pcls  :QWORD
    LOCAL ptxt  :QWORD
    LOCAL tlen  :QWORD
    LOCAL Buffer[1024]:BYTE
    LOCAL clName[128]:BYTE
    LOCAL tbuf[512]:BYTE

    LOCAL bwnd[64]:BYTE
    LOCAL bcls[128]:BYTE
    LOCAL bttl[256]:BYTE
    LOCAL wnd$  :QWORD
    LOCAL cls$  :QWORD
    LOCAL ttl$  :QWORD

    mov pbuf, ptr$(Buffer)
    mov pcls, ptr$(clName)
    mov ptxt, ptr$(tbuf)

    invoke GetClassName,eHandle,pcls,128
    mov tlen, rv(GetWindowText,eHandle,ptxt,512)

    mov wnd$, ptr$(bwnd)
    mov cls$, ptr$(bcls)
    mov ttl$, ptr$(bttl)

  ; ---------------------------------------------------------------------------
  ; the spaces in quotes are padding to allow the data to align in the display
  ; the "szLeft" proc reads the text + padding to produce consistent width text
  ; ---------------------------------------------------------------------------
    mcat wnd$," Handle = ",str$(eHandle),"                        "                   ; appended spaces for padding
    rcall szLeft,wnd$,wnd$,18

    mcat cls$," Class = ",pcls,"                                                    " ; appended spaces for padding
    rcall szLeft,cls$,cls$,52

    .if tlen == 0
      mcat pbuf,wnd$,cls$
    .else
      mcat pbuf,wnd$,cls$," Title = ",ptxt
    .endif

    invoke SendMessage,hList,LB_ADDSTRING,0,pbuf

  nxt:
    mov rax, eHandle
    ret

EnmProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end

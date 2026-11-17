; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc
    include jpgtool.inc

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

entry_point proc

    mov hInstance, rvcall(GetModuleHandle,0)

  ; ---------------
  ; randomise stack
  ; ---------------
    rcall seed_rrand,rv(get_unique_seed)        ; get a unique seed
    rcall rrand,1,16                            ; get a random number vetween 1 & 16
    shl rax, 6                                  ; mul by 64
    alignup rax, 16                             ; align it up to next 16 byte boundary
    sub rsp, rax                                ; subtract it from rsp
  ; ---------------

    GdiPlusBegin                    ; initialise GDIPlus

    mov hCursor,   rvcall(LoadCursor,0,IDC_ARROW)
    mov sWid,      rvcall(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rvcall(GetSystemMetrics,SM_CYSCREEN)
    mov hFont1,    GetFontHandle("Tahoma",18,600)
    mov hFont2,    GetFontHandle("Tahoma",26,600)
    mov tbBmp,     rv(ResImageLoad,20)
    mov tbTile,    rv(LoadImage,hInstance,30,IMAGE_BITMAP,sWid,rbht,LR_DEFAULTCOLOR)
    pix equ <64>
    mov hIcon,     rv(LoadImage,hInstance,10,IMAGE_ICON,pix,pix,LR_DEFAULTCOLOR)

  ; -----------------------------------------------------
  ; calculate the maxmum width based off the screen width
  ; -----------------------------------------------------

    mrm defwid, sWid                ; load the screen width
    cvtsi2sd xmm2, defwid           ; convert to XMM floating point
    mulsd xmm2, AFL8(0.70)          ; multiply by constant
    cvtsd2si rax, xmm2              ; convert back to integer
    mov defwid, rax                 ; write rax back to original integer

  ; -----------------------------------------------------

    call main

    GdiPlusEnd                      ; GdiPlus cleanup

    .exit

entry_point endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

main proc

    LOCAL wc      :WNDCLASSEX
    LOCAL lft     :QWORD
    LOCAL top     :QWORD
    LOCAL wid     :QWORD
    LOCAL hgt     :QWORD
    LOCAL pFile   :QWORD
    LOCAL hBrush  :QWORD
    LOCAL pbuf    :QWORD
    LOCAL buffer[128]:BYTE

    mov hBrush, rvcall(CreateSolidBrush,00444444h)

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

    rcall RegisterClassEx,ptr$(wc)

    swd equ <70>
    mov wid, rvcall(getpercent,sWid,swd)            ; % screen width
    mov hgt, rvcall(getpercent,sHgt,swd)            ; % screen height

    rcall aspect_ratio,hgt,50                       ; height + 50%
    cmp wid, rax                                    ; if wid > rax
    jle @F
    mov wid, rax                                    ; set wid to rax
  @@:
    mov rax, sWid                                   ; calculate offset from left side
    sub rax, wid
    shr rax, 1
    mov lft, rax

    mov rax, sHgt                                   ; calculate offset from top edge
    sub rax, hgt
    shr rax, 1
    mov top, rax

    invoke CreateWindowEx,WS_EX_LEFT or WS_EX_ACCEPTFILES, \
                          ADDR classname,ADDR caption, \
                          WS_OVERLAPPEDWINDOW or WS_VISIBLE,\
                          lft,top,wid,hgt,0,0,hInstance,0
    mov hWnd, rax

    mov hStatus, rvcall(StatusBar,hWnd)
    rcall SendMessage,hWnd,WM_SIZE,0,0
    rcall SendMessage,hStatus,SB_SETTEXT,0," No File Loaded"

    rcall szCopy,ptr$(caption),ptitle               ; store a copy of the start title in ptitle

    call msgloop

    ret

main endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

msgloop proc

    LOCAL msg    :MSG
    LOCAL pmsg   :QWORD

    mov pmsg, ptr$(msg)                                 ; get the msg structure address
    jmp gmsg                                            ; jump directly to GetMessage()

  mloop:
    .switch msg.message

  ; ||||||||||||||||||||||||||||||||||||||||||||||||||||

    .switch msg.message

      .case WM_KEYUP
        .switch msg.wParam
          .case VK_F1
            rcall SendMessage,hWnd,WM_COMMAND,54,0      ; About

        .endsw

  ; ////////////////////////////////////////////////////

        IfRepeatKey VK_MENU                             ; bypass all on ALT key
        je ByPass3

  ; ----------------------------------------------------

        IfRepeatKey VK_SHIFT                            ; bypass if SHIFT key
        je ByPass1
        IfRepeatKey VK_CONTROL                          ; allow CONTROL key
        jne ByPass1

      .switch msg.wParam
        .case VK_O
          rcall SendMessage,hWnd,WM_COMMAND,50,0        ; open file
        .case VK_S
          rcall SendMessage,hWnd,WM_COMMAND,51,0        ; save file
        .case VK_C
          rcall SendMessage,hWnd,WM_COMMAND,52,0        ; screen capture
        .case VK_P
          rcall SendMessage,hWnd,WM_COMMAND,53,0        ; paste file
        .case VK_W
          rcall SendMessage,hWnd,WM_COMMAND,55,0        ; set capture flag
        .case VK_Q
          rcall SendMessage,hWnd,WM_COMMAND,56,0        ; exit
      .endsw
 
        ByPass1:

  ; ----------------------------------------------------

        IfRepeatKey VK_SHIFT                            ; allow SHIFT key
        jne ByPass2
        IfRepeatKey VK_CONTROL                          ; bypass CONTROL key
        je ByPass2

      .switch msg.wParam
        .case VK_INSERT                                 ; shift + insert = paste
          rcall SendMessage,hWnd,WM_COMMAND,53,0 
      .endsw
        ByPass2:

  ; ----------------------------------------------------

        ByPass3:

  ; \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    .endsw

  ; ||||||||||||||||||||||||||||||||||||||||||||||||||||

    rcall TranslateMessage,pmsg
    rcall DispatchMessage,pmsg
  gmsg:
    test rax, rvcall(GetMessage,pmsg,0,0,0)             ; loop until GetMessage returns zero
    jnz mloop

    ret

msgloop endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

WndProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    USING r12,r13,r14,r15

    LOCAL dfbuff[260]:BYTE
    LOCAL sbh   :DWORD
    LOCAL rct   :RECT
    LOCAL pfn   :QWORD
    LOCAL hDC   :QWORD
    LOCAL ps    :PAINTSTRUCT
    LOCAL xWin  :QWORD
    LOCAL pbuf  :QWORD
    LOCAL buff[260]:BYTE
    LOCAL trct  :RECT
    LOCAL pRct  :QWORD

    .switch uMsg
      .case WM_COMMAND
        .switch wParam

          .case 50
            fileload:                                   ; jmp back here if no loaded file
            rcall load_disk_image,hWin,defwid

        ; -----------------------------------------------

          .case 51
            .If oFlag eq 0
              rcall no_file_loaded,hWin
              jmp fileload
            .EndIf
            rcall save_JPG_image,hWin                   ; save JPG file

        ; -----------------------------------------------

          .case 52                                      ; capture full screen
            rcall ShowWindow,hWin,SW_HIDE               ; hide this window
            rcall ScreenCapture                         ; capture screen
            mov hBitmap, rax                            ; get bitmap handle
            rcall ShowWindow,hWin,SW_SHOW               ; show it after capture
            rcall paste_image,hWin,defwid               ; display and scale image
            rcall SetWindowText,hWin, \
                " Full Screen Capture"                  ; display caption on title bar
            rcall szCopy," Full Screen Capture",ptitle  ; preserve caption into ptitle

        ; -----------------------------------------------

          .case 53
            rcall paste_clipboard_image,hWin            ; just paste image

        ; -----------------------------------------------

          .case 54
            invoke DialogBoxParam,hInstance, \
                   1500,hWin,ADDR About,hIcon           ; the modesty about box

        ; -----------------------------------------------

          .case 55
            mov capflag, 1                              ; set the capture flag
            rcall DestroyWindow,hImgBox
            mov hImgBox, rvcall(bitmap_image,hInstance,hWin,10,50)

            rcall GetClientRect,hWin,ptr$(rct)
            mov hDC, rvcall(GetDC,hWin)
            invoke DrawText,hDC, \
                 " Click in client area and drag to required window then release the mouse button ",\
                   -1,ptr$(rct),DT_SINGLELINE or DT_VCENTER or DT_CENTER
            rcall ReleaseDC,hWin,hDC

        ; -----------------------------------------------

          .case 56
            rcall SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL

        ; -----------------------------------------------

          .case 500
            rcall paste_clipboard_image,hWin            ; paste capture image

            rcall CloseClipboard
            rcall EmptyClipboard                        ; close and empty clipboard

            rcall SetWindowText,hWin," Window Capture"
            rcall szCopy," Window Capture",ptitle       ; preserve file name into ptitle

        ; -----------------------------------------------

        .endsw

      .case WM_SIZE
        invoke MoveWindow,hStatus,0,0,0,0,TRUE
 ;         rcall GetClientRect,hStatus,ptr$(rct)           ; get the height of the status bar
 ;         mrmd sbh, rct.bottom
 ;         rcall GetClientRect,hWin,ptr$(rct)              ; get the client area size
 ;         mov eax, rct.bottom
 ;         sub eax, rbht                                   ; subtract the rebar height
 ;         sub eax, sbh                                    ; subtract the status bar height
 ;         mov rct.bottom, eax                             ; write it back to structure member

      .case WM_NOTIFY
        mov r11, lParam
        mov rdx, (NMHDR PTR [r11]).hwndFrom
        .if rdx == hToolTips
          .switch wParam
            .case 50
              rcall SetWindowText,hWin," Open An Image File    Ctl+O"
            .case 51
              rcall SetWindowText,hWin," Save Loaded Image As JPG    Ctl+S"
            .case 52
              rcall SetWindowText,hWin," Capture Full Screen    Ctl+C"
            .case 53
              rcall SetWindowText,hWin," Paste Image From Clipboard    Ctl+P"
            .case 54
              rcall SetWindowText,hWin," About JpgTool    F1"
            .case 55
              rcall SetWindowText,hWin," Enable Window Capture    Ctrl+W"
            .case 56
              rcall SetWindowText,hWin," Exit JpgTool    Ctl+Q"

          .endsw
        .else
          rcall SetWindowText,hWin,ptitle                   ; restore the original title
        .endif

      .case WM_CREATE
        mov hRebar,   rvcall(rebar,hInstance,hWin,rbht)     ; create the rebar control
        mov hToolBar, rvcall(addband,hInstance,hRebar)      ; add the toolbar band to it
        mov hImgBox,  rvcall(bitmap_image,hInstance,hWin,10,50)

        mov capflag, 0                                      ; zero the capture flag
        .return 0

    ; ------------------------------------------------------

      .case WM_LBUTTONDOWN

        .If capflag eq 1

        rcall GetWindowRect,hWin,ptr$(wRct)
        rcall SetCapture,hWin

        mrmd rleft, wRct.left
        mrmd rtop, wRct.top
        mrmd rright, wRct.right
        mrmd rbottom, wRct.bottom

        invoke MoveWindow,hWin,-10000,-10000,100,100,TRUE

        .EndIf

    ; ------------------------------------------------------

      .case WM_LBUTTONUP

        .If capflag eq 1

        SaveRegs

        rcall GetCursorPos,ptr$(pt)
        mov xWin, rvcall(WindowFromPoint,pt)
        rcall SetForegroundWindow,xWin

        ; invoke SetWindowPos,xWin,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE or SWP_NOMOVE

        rcall OpenClipboard,0
        rcall EmptyClipboard
        rcall CloseClipboard

        rcall SleepEx,10,0

        KeyDown VK_CONTROL
        KeyDown VK_MENU
        KeyDown VK_SNAPSHOT

        rcall SleepEx,10,0

        KeyUp VK_SNAPSHOT
        KeyUp VK_MENU
        KeyUp VK_CONTROL

        ; invoke SetWindowPos,xWin,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE or SWP_NOMOVE

        mov r12d, rright                                ; calculate width
        sub r12d, rleft
        mov r13d, rbottom                               ; calculate height
        sub r13d, rtop

        invoke MoveWindow,hWin,rleft,rtop,r12d,r13d,TRUE
        rcall SetForegroundWindow,hWin
        rcall paste_clipboard_image,hWin

        rcall SetWindowText,hWin," Captured Window"
        rcall szCopy," Captured Window",ptitle          ; preserve file name into ptitle

        rcall ReleaseCapture
        mov capflag, 0                                  ; clear the capture flag

        RestoreRegs

        .EndIf

    ; ------------------------------------------------------

      .case WM_PAINT
        mov hDC, rvcall(BeginPaint,hWin,ptr$(ps))
          .If oFlag eq 0
            invoke DrawIconEx,hDC,50,70,hIcon,64,64,0,0,DI_NORMAL   ; only draw if no file loaded
          .EndIf
        rcall EndPaint,hWin,ptr$(ps)

      .case WM_CLOSE
        rcall SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        rcall PostQuitMessage,NULL

    .endsw

    rcall DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

no_file_loaded proc hWin:QWORD

    invoke MsgboxI,hWin, \
         "You must open an image file first"," No File Loaded",MB_OK,10
    ret

no_file_loaded endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

FixExtension proc pname:QWORD,extt:QWORD
  ; ---------------------------------------
  ; append correct extension if its missing
  ; note that the buffer address is reused
  ; ---------------------------------------
    LOCAL pbuf  :QWORD
    LOCAL pst1  :QWORD
    LOCAL str1[32]:BYTE

    .data?
      Buff@@$$@@ db 260 dup (?)             ; buffer with mangled name
    .code

    mov pst1, ptr$(str1)                    ; get both pointers
    mov pbuf, ptr$(Buff@@$$@@)

    rcall szCopy,pname,pbuf                 ; copy file name to Buff@@$$@@
    rcall szRight,pbuf,pst1,4               ; copy the right 4 characters into pst1

    mov pst1, lcase$(pst1)                  ; convert both strings to lower case
    mov extt, lcase$(extt)
    rcall szCmp,pst1,extt                   ; test if they are the same
    test rax, rax                           ; test result for zero
    jnz @F
    rcall szCatStr,pbuf,extt                ; append extension if 0
  @@:
    mov rax, pbuf                           ; return address of buffer
    ret

FixExtension endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

paste_clipboard_image proc hWin:QWORD

    LOCAL wBMP  :QWORD
    LOCAL hBMP  :QWORD
    LOCAL hFile :QWORD
    LOCAL outp  :QWORD                              ; pointer for text buffer
    LOCAL obuf[64]:BYTE                             ; text buffer

    LOCAL pbuf  :QWORD
    LOCAL buff[260]:BYTE
    LOCAL nwrt  :QWORD

    mov nwrt, 0

    rcall OpenClipboard,hWin
    mov hBitmap, rvcall(GetClipboardData,CF_BITMAP)

    .If rax eq 0
      rcall SetForegroundWindow,hWin

    .data
      txtmsg@ db "The window capture did not succeed.",13,10,13,10
              db "If an application prevents a successfuly screen capture "
              db "you can bypass the restriction by setting JpgTool.exe as",13,10,13,10
              db "          Run As Administrator",13,10,13,10
              db "This is done from the desktop properties dialog under "
              db "'Advanced' to obtain the necessary privilege level.",0
       pTxt@@ dq txtmsg@
    .code

      rcall MessageBox,hWin,pTxt@@,"Sorry, Capture failed ....",MB_ICONINFORMATION or MB_SYSTEMMODAL
      mov nwrt, 1
    .EndIf

    rcall CloseClipboard

    .If nwrt eq 1
      ret
    .EndIf

    rcall paste_image,hWin,defwid

    rcall GetBmpSize,hBitmap
    mov wBMP, rax                                   ; bitmap width
    mov hBMP, rcx                                   ; bitmap height

    mov outp, ptr$(obuf)                            ; get pointer to text buffer
    mcat outp," File Is Loaded At : ", \
                str$(wBMP)," x ", \
                str$(hBMP)," Pixels"                ; combine the strings

    rcall SendMessage,hStatus,SB_SETTEXT,0,outp     ; display string on status bar
    rcall SetWindowText,hWin," Pasted Image"        ; display file name on title bar
    rcall szCopy," Pasted Image",ptitle             ; preserve file name into ptitle

    ret

paste_clipboard_image endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

paste_image proc hWin:QWORD,iwid:QWORD

    LOCAL hFile :QWORD
    LOCAL hImg  :QWORD
    LOCAL wBMP  :QWORD
    LOCAL hBMP  :QWORD
    LOCAL ihgt  :QWORD                              ; image height

    LOCAL pttl  :QWORD
    LOCAL tbuf[260]:BYTE

    .If oFlag ne 0                                  ; if a previous image was loaded
      rcall DeleteObject,hBitmap                    ; delete previous bitmap
    .EndIf

    mov oFlag, 1                                    ; set the file loaded flag

    rcall SetWindowText,hWin,"Loading ...."         ; display loading for long loads

    invoke CopyImage,hBitmap,IMAGE_BITMAP, \
                     0,0,LR_COPYRETURNORG           ; make copy of original BMP
    mov hImg, rax

    rcall GetBmpSize,hImg
    mov wBMP, rax                                   ; bitmap width
    mov hBMP, rcx                                   ; bitmap height

    mov oWid, rax
    mov oHgt, rcx

    mov rax, iwid
    cmp wBMP, rax
    jge @F

    rcall getpercent,sHgt,80
    cmp hBMP, rax
    jb nxt
    jmp @F

  nxt:
    mrm iwid, wBMP
    mrm ihgt, hBMP
    jmp icopy

  @@:
    cvtsi2sd xmm0, wBMP                             ; convert width to floating point
    cvtsi2sd xmm1, hBMP                             ; convert height to floating point

    .If wBMP ge hBMP
      cvtsi2sd xmm2, iwid                           ; convert reference width to floating point
      divsd xmm0, xmm1                              ; calculate aspect ratio
      divsd xmm2, xmm0                              ; divide reference width by aspect ratio
      cvtsd2si rax, xmm2                            ; convert back to integer for height
      mov ihgt, rax                                 ; store as QWORD
    .EndIf

    .If hBMP gt wBMP
      divsd xmm0, xmm1                              ; calculate aspect ratio
      cvtsi2sd xmm2, sHgt                           ; the screen height
      mulsd xmm2, AFL8(0.6)                         ; multiply by 0.6
      cvtsd2si rax, xmm2
      mov ihgt, rax                                 ; convert back to integer for height
      mulsd xmm2, xmm0
      cvtsd2si rax, xmm2
      mov iwid, rax                                 ; convert back to integer for width
    .EndIf

  icopy:

    invoke CopyImage,hImg,IMAGE_BITMAP, \
                     iwid,ihgt,LR_COPYDELETEORG     ; resize and delete copy
    mov hImg, rax

    rcall SendMessage,hImgBox,STM_SETIMAGE, \
          IMAGE_BITMAP,hImg                         ; write image to static control

  bye:
    ret

paste_image endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

keydown proc vkkey:QWORD

    invoke keybd_event,vkkey,1,0,0
    invoke SleepEx,16,0
    ret

keydown endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

keyup proc vkkey:QWORD

    rcall keybd_event,vkkey,1,KEYEVENTF_KEYUP,0
    invoke SleepEx,16,0
    ret

keyup endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end


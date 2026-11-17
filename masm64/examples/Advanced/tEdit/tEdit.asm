; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

comment # ---------------------------------{ APP MAP }-------------------------------------

                       masm64rt.inc
                            |
        tEdit.inc  ---- tEdit.asm --- rsrc.rc --- dlgs.rc
                            |
        about.asm - fileio.asm - richedit.asm - search.asm - toolbar.asm - algorithms.asm

        --------------------------------------------------------------------------------- #

; *************************** EQUATES *******************************

  ; -------------------------------------------------------------
  ; equates for controlling the toolbar button size and placement
  ; -------------------------------------------------------------
    rbht     equ <58>           ; rebar height in pixels
    tbbW     equ <48>           ; toolbar button width in pixels
    tbbH     equ <48>           ; toolbar button height in pixels
    vpad     equ <12>           ; vertical button padding in pixels
    hpad     equ  <4>           ; horizontal button padding in pixels
    lind     equ <10>           ; left side initial indent in pixels

  ; --------------------------------------------------
  ; equates to control the text and background colours
  ; --------------------------------------------------
    txt_colour equ <00EEEEEEh>
    bak_colour equ <00333333h>

    tabsize equ <4>             ; set the tab size

; *******************************************************************

    include tEdit.inc

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

 entry_point proc

    GdiPlusBegin                    ; initialise GDIPlus

    mov hInstance, rv(GetModuleHandle,0)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hIcon,     rv(LoadImage,hInstance,10,IMAGE_ICON,48,48,LR_LOADTRANSPARENT)
    mov hCopy,     rv(LoadImage,hInstance,40,IMAGE_ICON,48,48,LR_LOADTRANSPARENT)
    mov hBitmap,   rv(ResImageLoad,20)
    mov tbTile,    rv(LoadImage,hInstance,30,IMAGE_BITMAP,sWid,rbht,LR_DEFAULTCOLOR)

    mov PM_LOADDONE, rv(RegisterWindowMessage,"LoadFileThread")
    mov PM_SAVEDONE, rv(RegisterWindowMessage,"SaveFileThread")

    mov ldThread, rv(CreateThread,0,0,ADDR LoadFileThread,0,CREATE_SUSPENDED,ADDR tID1)
    mov svThread, rv(CreateThread,0,0,ADDR SaveFileThread,0,CREATE_SUSPENDED,ADDR tID2)

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
    LOCAL cFile   :QWORD
    LOCAL buffer[128]:BYTE
    LOCAL pbuf    :QWORD

    rcall GetAppPath,pBase                  ; get the application path

    mov wc.cbSize,         SIZEOF WNDCLASSEX
    mov wc.style,          CS_BYTEALIGNCLIENT or CS_BYTEALIGNWINDOW
    mov wc.lpfnWndProc,    ptr$(WndProc)
    mov wc.cbClsExtra,     0
    mov wc.cbWndExtra,     0
    mrm wc.hInstance,      hInstance
    mrm wc.hIcon,          hIcon
    mrm wc.hCursor,        hCursor
    mrm wc.hbrBackground,  0
    mov wc.lpszMenuName,   0
    mov wc.lpszClassName,  ptr$(classname)
    mrm wc.hIconSm,        hIcon

    invoke RegisterClassEx,ADDR wc

    mov wid, rvcall(getpercent,sWid,65)     ; 65% screen width
    mov hgt, rvcall(getpercent,sHgt,65)     ; 65% screen height

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

 ;     mov dFont, rv(font_handle,"segoe ui",18,600)   ; font for dialog text
 ; 
 ;     rcall szCopy,"Untitled",ptitle
 ; 
 ;     invoke LoadLibrary,"riched20.dll"
 ;     mov hEdit, rv(rich_edit,hWnd,hInstance)
 ; 
 ;     mov hFont, rv(font_handle,"consolas",20,500)   ; Editor font
 ; 
 ;     invoke SendMessage,hEdit,WM_SETFONT,hFont,TRUE
 ; 
 ;     invoke SendMessage,hWnd,WM_SIZE,0,0
 ;     invoke SetFocus,hEdit
 ; 
 ;     invoke set_edit_colours
 ; 
 ;     mov hStatus, rv(StatusBar,hWnd)
 ;     invoke SendMessage,hWnd,WM_SIZE,0,0
 ; 
 ;     rcall AnimateWindow,hWnd,500,AW_ACTIVATE or AW_BLEND

  ; --------------------------------------
  ; load file from command line if present
  ; --------------------------------------

    call cmd_tail                   ; get command tail
    mov cFile, rax                  ; store rax in variable
    cmp BYTE PTR [rax], 0           ; test if its empty
    je rfout                        ; bypass loading file if empty

    invoke exist,cFile              ; check if file exists
    test rax, rax
    jnz @F

    mov pbuf,ptr$(buffer)
    mcat pbuf,"Command line file '",cFile,"' cannot be found."
    invoke MsgboxI,hWnd,pbuf,"Whoops",MB_OK,10
    jmp rfout

  @@:
    invoke file_read,hEdit,cFile

  rfout:
    mfree cFile                     ; release the memory from cmd_tail

  ; --------------------------------------

    ;; rcall AnimateWindow,hWnd,800,AW_BLEND

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
      .case WM_KEYDOWN
        .switch msg.wParam
        ; ---------------------------------------------

          .case VK_TAB
            rcall tab_replace,hEdit,tabsize
            jmp gmsg

        ; ---------------------------------------------

          .case VK_LEFT
            .if rvcall(indent_select) ~= 0              ; if text is selected
              rcall SendMessage,hWnd,WM_COMMAND,136,0
              jmp gmsg                                  ; allow no further processing
              .endif

          .case VK_RIGHT
            .if rvcall(indent_select) ~= 0              ; if text is selected
              rcall SendMessage,hWnd,WM_COMMAND,135,0
              jmp gmsg                                  ; allow no further processing
            .endif

        ; ---------------------------------------------

        .endsw

      .case WM_KEYUP
        ; -----------------
        ; single press keys
        ; -----------------
        .switch msg.wParam
          .case VK_F1
            invoke SendMessage,hWnd,WM_COMMAND,300,0    ; help / about menu
          .case VK_F2
            invoke SendMessage,hWnd,WM_COMMAND,250,0    ; search dialog
          .case VK_F3
            invoke SendMessage,hWnd,WM_COMMAND,260,0    ; replace dialog

        .endsw
        ; -----------------

          IfRepeatKey VK_SHIFT                          ; bypass if SHIFT key
          je nokey1
          IfRepeatKey VK_CONTROL                        ; allow CONTROL key
          jne nokey1
          IfRepeatKey VK_MENU                           ; bypass on ALT key
          je nokey1

        ; -----------------------------------
        ; CONTROL + virtual key for file menu
        ; -----------------------------------
        .switch msg.wParam
          .case VK_N
            invoke SendMessage,hWnd,WM_COMMAND,101,0    ; new
          .case VK_W
            invoke SendMessage,hWnd,WM_COMMAND,106,0    ; new window
          .case VK_O
            invoke SendMessage,hWnd,WM_COMMAND,102,0    ; open
          .case VK_S
            invoke SendMessage,hWnd,WM_COMMAND,103,0    ; save
          .case VK_E
            invoke SendMessage,hWnd,WM_COMMAND,104,0    ; save as
          .case VK_Q
            invoke SendMessage,hWnd,WM_COMMAND,125,0    ; close
          .case VK_D
            invoke SendMessage,hWnd,WM_COMMAND,610,0    ; date
          .case VK_T
            invoke SendMessage,hWnd,WM_COMMAND,611,0    ; time
          .case VK_A
            invoke SendMessage,hWnd,WM_COMMAND,612,0    ; select all
          .case VK_L
            invoke SendMessage,hWnd,WM_COMMAND,700,0    ; lower case
          .case VK_U
            invoke SendMessage,hWnd,WM_COMMAND,701,0    ; upper case
        .endsw
        ; -----------------------------------
      nokey1:

    .endsw

    invoke TranslateMessage,pmsg
    invoke DispatchMessage,pmsg
  gmsg:
    test rax, rv(GetMessage,pmsg,0,0,0)                 ; loop until GetMessage returns zero
    jnz mloop

    ret

 msgloop endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

 WndProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL dfbuff[260]:BYTE
    LOCAL sbh   :DWORD
    LOCAL rct   :RECT
    LOCAL pfn   :QWORD
    LOCAL sbuff[260]:BYTE
    LOCAL pbuff :QWORD

    .switch uMsg
      .case WM_COMMAND
        .switch wParam
          .case 50
            jmp new_file
          .case 51
            jmp open_dlg
          .case 52
            jmp save_dlg
          .case 53
            jmp edit_cut
          .case 54
            jmp edit_copy
          .case 55
            jmp edit_paste
          .case 56
            jmp edit_undo
          .case 57
            jmp edit_redo
          .case 58
            jmp search_find
          .case 59
            jmp text_replace
          .case 60
            jmp cmd_prompt
          .case 61
            jmp new_window
          .case 62
            jmp app_about
          .case 63
            jmp app_close

          .case 101
            new_file:
            rcall confirmation,hWin,hEdit
            cmp rax, 1
            jz @F
            rcall SetWindowText,hEdit,0
            rcall SendMessage,hStatus,SB_SETTEXT,0,0
            rcall szCopy,"Untitled",ptitle
          @@:

          .case 102
            open_dlg:
            rcall confirmation,hWin,hEdit
            cmp rax, 1
            jz @F
            invoke open_file_dialog,hWin,hInstance,"Open File",chr$("*.*",0,0)
            mov pFile, rax
            cmp BYTE PTR [rax], 0
            je @F
            rcall ResumeThread,ldThread                             ; resume thread
            rcall szCopy,pFile,ptitle
          @@:

          .case 103
            save_dlg:
            rcall GetWindowText,hWin,pFile,260
            rcall szCmp,pFile,"Untitled"
            test rax, rax
            jnz save_as
            rcall ResumeThread,svThread
            rcall szCopy,pFile,ptitle
            rcall SendMessage,hEdit,EM_SETMODIFY,FALSE,0

          .case 104
            save_as:
            invoke save_file_dialog,hWin,hInstance,"Save File As ...",chr$("*.*",0,0)
            mov pFile, rax
            cmp BYTE PTR [rax], 0
            je @F
            rcall ResumeThread,svThread
            rcall szCopy,pFile,ptitle
            rcall SendMessage,hEdit,EM_SETMODIFY,FALSE,0
          @@:

          .case 105
          cmd_prompt:
            exec "cmd.exe"

          .case 106
          new_window:
            mcat pBase,"tEdit.exe"
            exec pBase

          .case 125
            app_close:
            rcall SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL

          .case 135
            rcall right_indent

          .case 136
            rcall left_indent

        ; ------------------
        ; edit menu commands
        ; ------------------
          .case 200
            edit_undo:
            rcall SendMessage,hEdit,WM_UNDO,0,0
          .case 201
            edit_redo:
            rcall SendMessage,hEdit,EM_REDO,0,0
          .case 202
            edit_cut:
            rcall SendMessage,hEdit,WM_CUT,0,0
          .case 203
            edit_copy:
            rcall SendMessage,hEdit,WM_COPY,0,0
          .case 204
            edit_paste:
            rcall SendMessage,hEdit,EM_PASTESPECIAL,CF_TEXT,NULL
          .case 205
            edit_clear:
            rcall SendMessage,hEdit,WM_CLEAR,0,0

        ; -----------
        ; search menu
        ; -----------
          .case 250
            search_find:
          ; --------------------------------------
          ; only allow 1 instance of search dialog
          ; --------------------------------------
            .if ssrch == 0
              mov ssrch, 1
              invoke CreateDialogParam,hInstance,1000,hWin,ADDR find_text,0
            .endif

          .case 260
            text_replace:
          ; ---------------------------------------
          ; only allow 1 instance of replace dialog
          ; ---------------------------------------
            .if ssrch == 0
              mov ssrch, 1
              invoke CreateDialogParam,hInstance,2000,hWin,ADDR replace_text,0
            .endif

          .case 300
            app_about:
            invoke DialogBoxParam,hInstance,100,hWin,ADDR AboutDlg,0

          .case 301
            .data
                @@@tmsg db "Block indent is done by selecting lines of text by dragging",13,10
                        db "the mouse down the left side selection bar then using either",13,10
                        db "the left arrow key to reduce indent or the right arrow key to",13,10
                        db "increase indent.",13,10,13,10
                        db "You can change the case of selected text by using the options",13,10
                        db "on the Selection Menu.",0
                p@@@txt dq @@@tmsg
            .code

            invoke MsgboxI,hWin,p@@@txt," Selection Help",MB_OK,10

          .case 610
            mov pbuff, ptr$(sbuff)
            invoke GetDateFormat,LOCALE_USER_DEFAULT,DATE_LONGDATE,NULL,NULL,pbuff,260
            invoke SendMessage,hEdit,EM_REPLACESEL,TRUE,pbuff

          .case 611
            mov pbuff, ptr$(sbuff)
            invoke GetTimeFormat,LOCALE_USER_DEFAULT,NULL,NULL,NULL,pbuff,260
            invoke SendMessage,hEdit,EM_REPLACESEL,TRUE,pbuff

          .case 612
            rcall select_all,hEdit

          .case 700
            rcall is_selected
            test rax, rax
            jnz @F
            ret
          @@:
            rcall set_lcase                             ; lower case

          .case 701
            rcall is_selected
            test rax, rax
            jnz @F
            ret
          @@:
            rcall set_ucase                             ; upper case

        .endsw

      .case PM_LOADDONE
        mov pbuff, ptr$(sbuff)
        mov pfn, rvcall(GetWindowTextLength,hEdit)
        mcat pbuff," File opened at ",str$(pfn)," bytes"
        invoke SendMessage,hStatus,SB_SETTEXT,0,pbuff

      .case PM_SAVEDONE
        mov pbuff, ptr$(sbuff)
        mov pfn, rvcall(GetWindowTextLength,hEdit)
        mcat pbuff," File saved at ",str$(pfn)," bytes"
        invoke SendMessage,hStatus,SB_SETTEXT,0,pbuff

      .case WM_SIZE
        invoke MoveWindow,hStatus,0,0,0,0,TRUE
        invoke GetClientRect,hStatus,ADDR rct           ; get the height of the status bar
        mrmd sbh, rct.bottom
        invoke GetClientRect,hWin,ADDR rct              ; get the client area size
        mov eax, rct.bottom
        sub eax, rbht                                   ; subtract the rebar height
        sub eax, sbh                                    ; subtract the status bar height
        mov rct.bottom, eax                             ; write it back to structure member

      ; -------------------------------------------
      ; size the client window into the client area
      ; -------------------------------------------
        invoke MoveWindow,hEdit,0,rbht,rct.right,rct.bottom,TRUE

      .case WM_CREATE
        mov hRebar,   rv(rebar,hInstance,hWin,rbht)     ; create the rebar control
        mov hToolBar, rv(addband,hInstance,hRebar)      ; add the toolbar band to it
        rcall LoadMenu,hInstance,100
        rcall SetMenu,hWin,rax

        mov dFont, rv(font_handle,"segoe ui",18,600)    ; font for dialog text
        rcall szCopy,"Untitled",ptitle
        invoke LoadLibrary,"riched20.dll"

        mov hEdit, rv(rich_edit,hWin,hInstance)
        invoke SendMessage,hWin,WM_SIZE,0,0
        invoke set_edit_colours
        mov hFont, rv(font_handle,"consolas",20,500)    ; Editor font
        invoke SendMessage,hEdit,WM_SETFONT,hFont,TRUE
        mov hStatus, rv(StatusBar,hWin)
        invoke SendMessage,hWin,WM_SIZE,0,0

        ; rcall AnimateWindow,hWin,100,AW_SLIDE or AW_VER_NEGATIVE

        invoke SetFocus,hEdit

        .return 0

      .case WM_NOTIFY
        mov r11, lParam
        mov rdx, (NMHDR PTR [r11]).hwndFrom

        .if rdx == hToolTips
          .switch wParam
            .case 50
              invoke SetWindowText,hWin,"New File"
            .case 51
              invoke SetWindowText,hWin,"Open File"
            .case 52
              invoke SetWindowText,hWin,"Save File"
            .case 53
              invoke SetWindowText,hWin,"Clipboard Cut"
            .case 54
              invoke SetWindowText,hWin,"Clipboard Copy"
            .case 55
              invoke SetWindowText,hWin,"Clipboard Paste"
            .case 56
              invoke SetWindowText,hWin,"Undo Last Change"
            .case 57
              invoke SetWindowText,hWin,"Redo Last Change"
            .case 58
              invoke SetWindowText,hWin,"Find Text"
            .case 59
              invoke SetWindowText,hWin,"Replace Text"
            .case 60
              invoke SetWindowText,hWin,"Command Prompt"
            .case 61
              invoke SetWindowText,hWin,"New Window"
            .case 62
              invoke SetWindowText,hWin,"About"
            .case 63
              invoke SetWindowText,hWin,"Exit Application"
          .endsw
        .else
          invoke SetWindowText,hWin,ptitle
        .endif

      .case WM_SETFOCUS
        invoke SetFocus,hEdit

      .case WM_DROPFILES
        mov pfn, ptr$(dfbuff)
        rcall DragQueryFile,wParam,0,pfn,260
        rcall file_read,hEdit,pfn
        rcall SetWindowText,hWin,pfn

      .case WM_CLOSE
        rcall confirmation,hWin,hEdit
        rcall CloseHandle,ldThread
        rcall CloseHandle,svThread
        rcall SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        rcall PostQuitMessage,NULL

    .endsw

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

 WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

    include \masm64\include64\masm64rt.inc
    include include.inc

  ; -------------------------------------------------------------
  ; equates for controlling the toolbar button size and placement
  ; -------------------------------------------------------------
    rbht     equ <44>                                   ; rebar height in pixels
    tbbW     equ <32>                                   ; toolbar button width in pixels
    tbbH     equ <32>                                   ; toolbar button height in pixels
    vpad     equ <14>                                   ; vertical button padding in pixels
    hpad     equ  <8>                                   ; horizontal button padding in pixels
    lind     equ <10>                                   ; left side initial indent in pixels

  ; --------------------------------------------------
  ; equates to control the text and background colours
  ; --------------------------------------------------
    txt_colour equ <00EEEEEEh>
    bak_colour equ <00111111h>

    .data
      indent dq 1                                       ; auto indent is enabled = 1, disables = 0
      useDLL dq 1                                       ; DLL enabled = 1, disabled = 0

      wHelp  db "k:\masm64\help\win32.hlp",0            ; winhelp path
      phpth  dq wHelp                                   ; path pointer

    .code

  ; -------------------------------------------------
  ; included source code must be in the .code section
  ; -------------------------------------------------
    include riched.asm                                  ; the rich edit and support code
    include findrepl.asm                                ; the find and replace code
    include about.asm                                   ; the about box dialog code
    include toolbar.asm                                 ; the toolbar, status bar and rebar code
    include indent.asm                                  ; auto indent code

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

 entry_point proc

    GdiPlusBegin                                        ; initialise GDIPlus

    mov PM_PATH, rvcall(RegisterWindowMessage,"Return_App64_Path")

    rcall CreateMMF,"MASM64 Path Data",1024*256,ptr$(hMMF),ptr$(pMMF)

    mov hInstance, rv(GetModuleHandle,0)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hIcon,     rv(LoadImage,hInstance,10,IMAGE_ICON,48,48,LR_LOADTRANSPARENT)
    mov hBitmap,   rv(ResImageLoad,20)
    mov tbTile,    rv(LoadImage,hInstance,30,IMAGE_BITMAP,sWid,rbht,LR_DEFAULTCOLOR)

  ; --------------------
  ; dialog brush colours
  ; --------------------
    mov hBrush, rvcall(CreateSolidBrush,00222222h)      ; create the dialog background brush
    mov bBordr, rvcall(CreateSolidBrush,00222222h)      ; create the button border colour
    mov eColor, rvcall(CreateSolidBrush,00111111h)      ; create the Edit window back colour
    mov lColor, rvcall(CreateSolidBrush,00333333h)      ; create the list and combo back colour

    mov pPath, rv(GetAppPath,ADDR pBuffer)              ; get the editor path for later use

    call main

    GdiPlusEnd                                          ; GdiPlus cleanup

    rcall CloseMMF,pMMF,hMMF                            ; close the memory mapped file

    .exit                                               ; main exit point

    ret

 entry_point endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

 main proc

    LOCAL wc      :WNDCLASSEX
    LOCAL lft     :QWORD
    LOCAL top     :QWORD
    LOCAL wid     :QWORD
    LOCAL hgt     :QWORD
    LOCAL pFile   :QWORD
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
    mrm wc.hbrBackground,  0
    mov wc.lpszMenuName,   0
    mov wc.lpszClassName,  ptr$(classname)
    mrm wc.hIconSm,        hIcon

    rcall RegisterClassEx,ptr$(wc)

    mov wid, rvcall(getpercent,sWid,65)     ; 65% screen width
    mov hgt, rvcall(getpercent,sHgt,65)     ; 65% screen height

    rcall aspect_ratio,hgt,45               ; height + 45%
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

    rcall LoadLibrary,"riched20.dll"
    mov hEdit, rvcall(rich_edit,hWnd,hInstance)

    rcall SendMessage,hWnd,WM_SIZE,0,0
    rcall SetFocus,hEdit

    rcall set_edit_colours

    mov hStatus, rvcall(StatusBar,hWnd)
    rcall SendMessage,hWnd,WM_SIZE,0,0

  ; --------------------------------------
  ; load file from command line if present
  ; --------------------------------------

    call cmd_tail                   ; get command tail
    mov pFile, rax                  ; store rax in variable
    cmp BYTE PTR [rax], 0           ; test if its empty
    je rfout                        ; bypass loading file if empty

  ; -----------------------------------
    rcall szRemove,pFile,pFile,chr$(34)     ; strip quotes, added for old OS versions
  ; -----------------------------------     ; and non US Windows versions

    rcall exist,pFile               ; check if file exists
    test rax, rax
    jnz @F

    mov pbuf,ptr$(buffer)
    mcat pbuf,"Command line file '",pFile,"' cannot be found."
    invoke MsgboxI,hWnd,pbuf,"Whoops",MB_OK,10
    jmp rfout

  @@:
    rcall file_read,hEdit,pFile

  rfout:
    mfree pFile                     ; release the memory from cmd_tail

  ; --------------------------------------

  ; ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    .if useDLL == 1

    mov pbuf, ptr$(buffer)                                              ; get pointer to buffer
    mcat pbuf, pPath,"cplugin.dll"                                      ; append DLL name to path

    .if rvcall(exist,pbuf) ~= 0
      .data?
        cplugin dq ?
        piInterface dq ?
      .code
      mov cplugin, rvcall(LoadLibrary,pbuf)                             ; load the DLL if it exists
      mov piInterface, rvcall(GetProcAddress,cplugin,"piInterface")     ; get the procedure address
      invoke piInterface,hWnd,hMenu,hEdit,hToolBar,hStatus              ; call the DLL procedure
    .endif

    .endif

  ; ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    call msgloop

    ret

 main endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

 msgloop proc

    LOCAL msg    :MSG
    LOCAL pmsg   :QWORD
    LOCAL cr     :CHARRANGE

    mov pmsg, ptr$(msg)                                 ; get the msg structure address
    jmp gmsg                                            ; jump directly to GetMessage()

  mloop:
    .switch msg.message

      .case WM_KEYDOWN
        .switch msg.wParam
          .case VK_RETURN
            .if indent == 1
              call autoindent                           ; call autoindent from VK_RETURN (enter) key
            .endif

          .case VK_LEFT
            IfRepeatKey VK_CONTROL                      ; allow CONTROL key
            jne @F
            rcall SendMessage,hEdit,EM_EXGETSEL,0,ptr$(cr)
            mov eax, cr.cpMax
            cmp cr.cpMin, eax
            je @F
            call sub_indent
            jmp gmsg
          @@:

          .case VK_RIGHT
            IfRepeatKey VK_CONTROL                      ; allow CONTROL key
            jne @F
            rcall SendMessage,hEdit,EM_EXGETSEL,0,ptr$(cr)
            mov eax, cr.cpMax
            cmp cr.cpMin, eax
            je @F
            call add_indent
            jmp gmsg
          @@:

        .endsw

      .case WM_KEYUP
        ; -----------------
        ; single press keys
        ; -----------------
        .switch msg.wParam
          .case VK_F1
            rcall SendMessage,hEdit,WM_LBUTTONDBLCLK,0,0    ; help / menu
            rcall SendMessage,hWnd,WM_COMMAND,400,0

          .case VK_F2
            rcall SendMessage,hWnd,WM_COMMAND,250,0    ; search dialog
          .case VK_F3
            rcall SendMessage,hWnd,WM_COMMAND,260,0    ; replace dialog

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
            rcall SendMessage,hWnd,WM_COMMAND,101,0     ; new
          .case VK_O
            rcall SendMessage,hWnd,WM_COMMAND,102,0     ; open
          .case VK_S
            rcall SendMessage,hWnd,WM_COMMAND,103,0     ; save
          .case VK_T
            rcall SendMessage,hWnd,WM_COMMAND,104,0     ; save as
          .case VK_I
            rcall SendMessage,hWnd,WM_COMMAND,105,0     ; new instance
          .case VK_P
            rcall SendMessage,hWnd,WM_COMMAND,106,0     ; command prompt
          .case VK_M
            rcall SendMessage,hWnd,WM_COMMAND,107,0     ; merge text
          .case VK_Q
            rcall SendMessage,hWnd,WM_COMMAND,125,0     ; close
        .endsw
        ; ---------------------
      nokey1:

    .endsw

    rcall TranslateMessage,pmsg
    rcall DispatchMessage,pmsg
  gmsg:
    test rax, rvcall(GetMessage,pmsg,0,0,0)                 ; loop until GetMessage returns zero
    jnz mloop

    ret

 msgloop endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

WndProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL dfbuff[260]:BYTE
    LOCAL sbh   :DWORD
    LOCAL rct   :RECT
    LOCAL pfn   :QWORD
    LOCAL sbuff[260]:BYTE
    LOCAL pbuff :QWORD
    LOCAL cr    :CHARRANGE
    LOCAL pBuf  :QWORD
    LOCAL buff[1024]:BYTE
    LOCAL pName :QWORD
    LOCAL ExtDLL:QWORD
    LOCAL pibuff[260]:BYTE                                  ; plugin dir path
    LOCAL pibuf  :QWORD                                     ; its pointer


    .switch uMsg
      .case WM_CREATE
        mov hRebar,   rvcall(rebar,hInstance,hWin,rbht)     ; create the rebar control
        mov hToolBar, rvcall(addband,hInstance,hRebar)      ; add the toolbar band to it
        rcall LoadMenu,hInstance,100
        mov hMenu, rax
        rcall SetMenu,hWin,hMenu
        .return 0


      .case PM_PATH                         ; general purpose private message
        .switch wParam
          .case 0                           ; case 0 is the SCRIPT ENGINE
            chdir pMMF                      ; change to directory for new project
            jmp open_dlg                    ; open file dialog in that directory
        .endsw


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
            jmp new_instance
          .case 61
            jmp cmd_prompt
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
            rcall SetWindowText,hWin,"Untitled"
            rcall SendMessage,hStatus,SB_SETTEXT,0,0
            @@:

          .case 102
            open_dlg:
            rcall confirmation,hWin,hEdit
            cmp rax, 1
            jz @F
            invoke open_file_dialog,hWin,hInstance,"Open File",chr$("*.*",0,0)
            mov pfn, rax
            cmp BYTE PTR [rax], 0
            je @F
            rcall file_read,hEdit,pfn
            rcall SetWindowText,hWin,pfn

            mov pbuff, ptr$(sbuff)
            rcall GetWindowTextLength,hEdit
            mcat pbuff," File Opened At ",str$(rax)," Bytes"
            rcall SendMessage,hStatus,SB_SETTEXT,1,pbuff            ; display open size on status bar
          @@:

          .case 103
            save_dlg:
            mov pbuff, ptr$(sbuff)
            rcall GetWindowText,hWin,pbuff,260
            rcall szCmp,pbuff,"Untitled"
            test rax, rax
            jnz save_as
            rcall file_write,hEdit,pbuff
            rcall SetWindowText,hWin,pbuff
            rcall SendMessage,hEdit,EM_SETMODIFY,FALSE,0

            mov pbuff, ptr$(sbuff)
            rcall GetWindowTextLength,hEdit
            mcat pbuff," File Saved At ",str$(rax)," Bytes"
            rcall SendMessage,hStatus,SB_SETTEXT,1,pbuff            ; display open size on status bar

          .case 104
            save_as:
            invoke save_file_dialog,hWin,hInstance,"Save File As ...",chr$("*.*",0,0)
            mov pfn, rax
            cmp BYTE PTR [rax], 0
            je @F
            rcall file_write,hEdit,pfn
            rcall SetWindowText,hWin,pfn
            rcall SendMessage,hEdit,EM_SETMODIFY,FALSE,0

            mov pbuff, ptr$(sbuff)
            rcall GetWindowTextLength,hEdit
            mcat pbuff," File Saved At ",str$(rax)," Bytes"
            rcall SendMessage,hStatus,SB_SETTEXT,1,pbuff            ; display open size on status bar
          @@:

          .case 105
            new_instance:
            mov pBuf, ptr$(buff)
            rcall GetModuleFileName,0,pBuf,260                      ; start a new instance
            exec pBuf

          .case 106
            cmd_prompt:
            exec "cmd.exe"                                          ; command prompt

          .case 107
            rcall merge_text,hWin,hEdit

          .case 125
            app_close:
            rcall SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL

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
        ; --------------------
        ; plus or minus indent
        ; --------------------
          .case 500
          more_indent:
            rcall SendMessage,hEdit,EM_EXGETSEL,0,ptr$(cr)
            mov eax, cr.cpMax
            cmp cr.cpMin, eax                           ; if cr.cpMin & cr.cpMax equal
            je @F                                       ; bypass more indent
            call add_indent
          @@:

          .case 501
          less_indent:
            rcall SendMessage,hEdit,EM_EXGETSEL,0,ptr$(cr)
            mov eax, cr.cpMax
            cmp cr.cpMin, eax                           ; if cr.cpMin & cr.cpMax equal
            je @F                                       ; bypass less indent
            call sub_indent
          @@:
        ; --------------------

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

        ; |||||||||||||||||||||||||||||||||||||||||||||||
        ; -------------------------
        ; Run external applications
        ; -------------------------
          .case 275
            mov pBuf, ptr$(buff)                        ; get pointer to 260 byte buffer
            mcat pBuf,pPath,"se64.exe"                  ; add file name to path
            exec pBuf

          .case 276
            exec "makeit.bat"

          .case 277
            mov pBuf, ptr$(buff)                        ; get pointer to 260 byte buffer
            rcall GetWindowText,hWin,pBuf,260           ; get title bar string
            mov pName, lcase$(pBuf)
            mov rax, rep$(pName,pName,".asm",".exe")    ; run assembled exe from source code name
            exec pName

          .case 350
            mov pBuf, ptr$(buff)                        ; get pointer to 260 byte buffer
            mcat pBuf,pPath,"cpicker.exe"               ; add file name to path
            exec pBuf

          .case 351
            mov pBuf, ptr$(buff)                        ; get pointer to 260 byte buffer
            mcat pBuf,pPath,"getcolor.exe"              ; add file name to path
            exec pBuf

        ; -----------------------------------------------
        ; with source browser qetb.exe, put the directory
        ; name after the exe name to open that directory
        ; -----------------------------------------------
          .case 352
            mov pBuf, ptr$(buff)                        ; get pointer to 260 byte buffer
            mcat pBuf,pPath,"qetb.exe scripts"          ; add file name to path
            exec pBuf

        ; |||||||||||||||||||||||||||||||||||||||||||||||


          ; \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
          ; Call an external CodeEdit plugin DLL
          ; /////////////////////////////////////////////
          .case 353

            mov pBuf, ptr$(buff)
            rcall GetCurrentDirectory,260,pBuf                              ; get the current directory

            mov pibuf, ptr$(pibuff)                                         ; pointer to plugin buffer
            mcat pibuf, pPath,"ceplugins"                                   ; append dir name to path
            chdir pibuf                                                     ; change dir to 'ceplugins'

            invoke open_file_dialog,hWin,hInstance,"Open CodeEdit Plugin DLL",chr$("DLL Files",0,"*.DLL",0,0)
            mov pfn, rax
            cmp BYTE PTR [rax], 0                                           ; if cancel pressed
            je @F                                                           ; jump over load DLL code

            mov ExtDLL, rvcall(LoadLibrary,pfn)
            mov piInterface, rvcall(GetProcAddress,ExtDLL,"piInterface")    ; get the procedure address

            .if piInterface == 0
              invoke MessageBox,hWin,"The 'piInterface' export is not found in the selected DLL", \
                     "This DLL is not a CodeEdit plugin",MB_OK
              jmp @F
            .endif

            rcall SetCurrentDirectory,pBuf                                  ; restore current directory
            invoke piInterface,hWnd,hMenu,hEdit,hToolBar,hStatus            ; call the DLL procedure
          @@:

            rcall FreeLibrary,ExtDLL
            rcall SetCurrentDirectory,pBuf                                  ; duplicated if DLL error

          ; /////////////////////////////////////////////

          .case 300
            app_about:
            invoke DialogBoxParam,hInstance,100,hWin,ADDR AboutDlg,0

          .case 301
          ; --------------------------------------
          ; load winhelp without specifying a word
          ; --------------------------------------
            invoke WinHelp,hWnd,phpth,HELP_CONTENTS,0

          .case 400                                     ; F1 Help called from message loop
            F1_help:
            mov pBuf, ptr$(buff)                        ; 1024 byte LOCAL buffer
            rcall SendMessage,hEdit,EM_GETSELTEXT,0,pBuf; get the selected word
            .if len(pBuf) ~= 0                          ; if its not zero (0) length
            .data
              hlpmsg db "This is a place holder to process the selected "
                     db "word after pressing the F1 key.",13,10,13,10
                     db "REFERENCE : Located at WM_COMMAND ID 400.",13,10,0
              pHmsg  dq hlpmsg
            .code

            ; --------------------------------------------
            ; the following code assumes that win32.hlp is
            ; in the '\masm64\help\win32.hlp' directory.
            ; --------------------------------------------
              invoke WinHelp,hWnd,phpth,HELP_PARTIALKEY,pBuf

            .endif

        .endsw

      .case WM_SIZE
        invoke MoveWindow,hStatus,0,0,0,0,TRUE
        rcall GetClientRect,hStatus,ptr$(rct)           ; get the height of the status bar
        mrmd sbh, rct.bottom
        rcall GetClientRect,hWin,ptr$(rct)              ; get the client area size
        mov eax, rct.bottom
        sub eax, rbht                                   ; subtract the rebar height
        sub eax, sbh                                    ; subtract the status bar height
        mov rct.bottom, eax                             ; write it back to structure member

      ; -------------------------------------------
      ; size the client window into the client area
      ; -------------------------------------------
        invoke MoveWindow,hEdit,0,rbht,rct.right,rct.bottom,TRUE

      .case WM_SETFOCUS
        rcall SetFocus,hEdit

      .case WM_DROPFILES
        mov pfn, ptr$(dfbuff)
        rcall DragQueryFile,wParam,0,pfn,260
        rcall file_read,hEdit,pfn
        rcall SetWindowText,hWin,pfn

      .case WM_CLOSE
        rcall confirmation,hWin,hEdit
        rcall DestroyWindow,hWnd                        ; cuts the exit lag from the DLL
        rcall FreeLibrary,cplugin
        rcall SendMessage,hWin,WM_DESTROY,0,0

      .case WM_DESTROY
        rcall PostQuitMessage,NULL

    .endsw

    rcall DefWindowProc,hWin,uMsg,wParam,lParam

    ret

 WndProc endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

 confirmation proc parent:QWORD,edit:QWORD

  ; ------------------------------------------------------
  ; return values
  ; 0 = proceed with following operation, new or open file
  ; 1 = cancel following operation
  ; ------------------------------------------------------
    LOCAL nbuff[260]:BYTE
    LOCAL pbuff :QWORD

    rcall SendMessage,edit,EM_GETMODIFY,0,0
    test rax, rax       ; test if EM_GETMODIFY = 0
    jnz continue        ; jump forward if edit control modified
    ret                 ; if unmodified, exit with RAX = 0

  continue:
    invoke MsgboxI,parent,"File is not saved, save it now ?","Confirmation",MB_YESNOCANCEL,10

    .switch rax
      .case IDYES
        mov pbuff, ptr$(nbuff)
        rcall GetWindowText,parent,pbuff,260
        rcall szCmp,pbuff,"Untitled"
        test rax, rax
        jnz @F
        rcall file_write,edit,pbuff
        rcall SetWindowText,parent,pbuff
        rcall SendMessage,edit,EM_SETMODIFY,FALSE,0
        xor rax, rax
        ret
      @@:
        invoke save_file_dialog,parent,hInstance,"Save File As ...",chr$("*.*",0,0)
        mov pbuff, rax
        cmp BYTE PTR [rax], 0
        je @F
        rcall file_write,edit,pbuff
        rcall SetWindowText,parent,pbuff
        rcall SendMessage,edit,EM_SETMODIFY,FALSE,0
        xor rax, rax
        ret
      @@:
      .case IDNO
        xor rax, rax
        ret
      .case IDCANCEL
        mov rax, 1
        ret
    .endsw

    ret

 confirmation endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

 merge_text proc hWin:QWORD,edit:QWORD

    LOCAL buffer[260]:BYTE
    LOCAL pbuff :QWORD
    LOCAL pmem  :QWORD
    LOCAL lmem  :QWORD

    mov pbuff, ptr$(buffer)
    invoke open_file_dialog,hWin,hInstance,"Merge File At Current Location ....",chr$("*.*",0,0)
    mov pbuff, rax
    cmp BYTE PTR [rax], 0                               ; test if cancel was pressed
    je quit                                             ; exit proc if YES

    invoke load_file,pbuff                              ; load file to merge into memory
    mov pmem, rax
    mov lmem, rcx

    invoke SendMessage,edit,EM_REPLACESEL,TRUE,pmem     ; replace current selection with loaded file

    mfree pmem                                          ; free memory from load_file

  ; ------------
  ; reuse buffer
  ; ------------
    mov pbuff, ptr$(buffer)
    mcat pbuff,"Text merged at ",str$(lmem)," bytes"

    invoke SendMessage,hStatus,SB_SETTEXT,3,pbuff
    mov rax, 1
    ret

  quit:
    xor rax, rax
    ret

 merge_text endp

; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

NOSTACKFRAME

char_fill proc

  ; rcx = memory address
  ; rdx = byte count
  ; r8  = char

    sub rcx, 1
  @@:
    add rcx, 1
    mov BYTE PTR [rcx], r8b
    sub rdx, 1
    jnz @B

    add rcx, 1
    mov BYTE PTR [rcx], 0       ; zero terminate fill

    ret

char_fill endp

STACKFRAME


; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

    end


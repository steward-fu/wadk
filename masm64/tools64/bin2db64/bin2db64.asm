; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc
    include bin2db64.inc

  ; -------------------------------------------------------------
  ; equates for controlling the toolbar button size and placement
  ; -------------------------------------------------------------
    rbht     equ <60>           ; rebar height in pixels
    tbbW     equ <48>           ; toolbar button width in pixels
    tbbH     equ <48>           ; toolbar button height in pixels
    vpad     equ <12>           ; vertical button padding in pixels
    hpad     equ  <8>           ; horizontal button padding in pixels
    lind     equ <10>           ; left side initial indent in pixels

  ; --------------------------------------------------
  ; equates to control the text and background colours
  ; --------------------------------------------------
    txt_colour equ <00EEEEEEh>
    bak_colour equ <00111111h>

    .data?
      hInstance dq ?
      hWnd      dq ?
      hIcon     dq ?
      hCursor   dq ?
      sWid      dq ?
      sHgt      dq ?
      hBitmap   dq ?
      tbTile    dq ?
      hRebar    dq ?
      hToolBar  dq ?
      hStatus   dq ?
      hEdit     dq ?
      hToolTips dq ?

    .data
      classname db "bintodb64_class",0
      caption db "Convert Binary File To DB Format",0

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

entry_point proc

    GdiPlusBegin                    ; initialise GDIPlus

    mov hInstance, rv(GetModuleHandle,0)
    mov hCursor,   rv(LoadCursor,0,IDC_ARROW)
    mov sWid,      rv(GetSystemMetrics,SM_CXSCREEN)
    mov sHgt,      rv(GetSystemMetrics,SM_CYSCREEN)
    mov hIcon,     rv(LoadImage,hInstance,10,IMAGE_ICON,48,48,LR_LOADTRANSPARENT)
    mov hBitmap,   rv(ResImageLoad,20)
    mov tbTile,    rv(LoadImage,hInstance,30,IMAGE_BITMAP,sWid,rbht,LR_DEFAULTCOLOR)

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
    LOCAL pFile   :QWORD
    LOCAL buffer[128]:BYTE
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

    invoke RegisterClassEx,ADDR wc

    mov wid, function(getpercent,sWid,65)   ; 65% screen width
    mov hgt, function(getpercent,sHgt,65)   ; 65% screen height

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

    invoke LoadLibrary,"riched20.dll"
    mov hEdit, rv(rich_edit,hWnd,hInstance)
    invoke SendMessage,hWnd,WM_SIZE,0,0
    invoke SetFocus,hEdit

    invoke set_edit_colours

    mov hStatus, rv(StatusBar,hWnd)
    invoke SendMessage,hWnd,WM_SIZE,0,0

  ; --------------------------------------
  ; load file from command line if present
  ; --------------------------------------

    call cmd_tail                   ; get command tail
    mov pFile, rax                  ; store rax in variable
    cmp BYTE PTR [rax], 0           ; test if its empty
    je rfout                        ; bypass loading file if empty

    invoke exist,pFile              ; check if file exists
    test rax, rax
    jnz @F

    mov pbuf,ptr$(buffer)
    mcat pbuf,"Command line file '",pFile,"' cannot be found."
    invoke MsgboxI,hWnd,pbuf,"Whoops",MB_OK,10
    jmp rfout

  @@:

    invoke convert_file,pFile       ; load file and convert to DB format

  rfout:
    mfree pFile                     ; release the memory from cmd_tail

  ; --------------------------------------

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
    .switch msg.message
      .case WM_KEYUP
        .switch msg.wParam
          .case VK_F1
            invoke SendMessage,hWnd,WM_COMMAND,300,0
        .endsw
    .endsw
    invoke TranslateMessage,pmsg
    invoke DispatchMessage,pmsg
  gmsg:
    test rax, rv(GetMessage,pmsg,0,0,0)     ; loop until GetMessage returns zero
    jnz mloop

    ret

msgloop endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

stackframe_default equ <96>
STACKFRAME

WndProc proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL dfbuff[260]:BYTE
    LOCAL sbh   :DWORD
    LOCAL rct   :RECT
    LOCAL pfn   :QWORD
    LOCAL fptr  :QWORD
    LOCAL flen  :QWORD
    LOCAL pmem  :QWORD
    LOCAL olen  :QWORD
    LOCAL gpbuff[260]:BYTE
    LOCAL tPtr  :QWORD
    LOCAL cr    :CHARRANGE

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
            .if rv(GetWindowTextLength,hEdit) == 0
              jmp @F
            .endif
            call copy_all
            .return 0
          @@:

          .case 54
            jmp app_about
          .case 55
            jmp app_close

          .case 101
            new_file:
            fn SetWindowText,hEdit,0
            invoke SendMessage,hStatus,SB_SETTEXT,0,0
            .return 0

          .case 102
            open_dlg:
            invoke open_file_dialog,hWin,hInstance,"Open File",chr$("*.*",0,0)
            mov pfn, rax
            cmp BYTE PTR [rax], 0
            je @F

            invoke convert_file,pfn       ; load file and convert to DB format
            .return 0

          @@:

          .case 103
            save_dlg:
            invoke save_file_dialog,hWin,hInstance,"Save File As ...",chr$("*.*",0,0)
            mov pfn, rax
            cmp BYTE PTR [rax], 0
            je @F
            invoke file_write,hEdit,pfn
            mov flen, rv(GetWindowTextLength,hEdit)
            mov tPtr, ptr$(gpbuff)
            mcat tPtr," File Saved at ",str$(flen)," bytes"
            invoke SendMessage,hStatus,SB_SETTEXT,0,tPtr
            .return 0
          @@:

          .case 125
            app_close:
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL

          .case 300
            app_about:
            invoke DialogBoxParam,hInstance,100,hWin,ADDR AboutDlg,0
            .return 0

        .endsw

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
        .return 0

      .case WM_CREATE
        mov hRebar,   rv(rebar,hInstance,hWin,rbht)     ; create the rebar control
        mov hToolBar, rv(addband,hInstance,hRebar)      ; add the toolbar band to it
        invoke LoadMenu,hInstance,100
        invoke SetMenu,hWin,rax
        .return 0

      .case WM_NOTIFY
        mov r11, lParam
        mov rdx, (NMHDR PTR [r11]).hwndFrom

        .if rdx == hToolTips
          .switch wParam
            .case 50
              fn SetWindowText,hWin,"Clear Edit Window"
            .case 51
              fn SetWindowText,hWin,"Open File To Convert"
            .case 52
              fn SetWindowText,hWin,"Save Result To Disk"
            .case 53
              fn SetWindowText,hWin,"Select And Copy All"
            .case 54
              fn SetWindowText,hWin,"Help / About"
            .case 55
              fn SetWindowText,hWin,"Close Application"
          .endsw
        .else
          fn SetWindowText,hWin,ADDR caption
        .endif

      .case WM_SETFOCUS
        invoke SetFocus,hEdit
        .return 0

      .case WM_DROPFILES
        mov pfn, ptr$(dfbuff)
        invoke DragQueryFile,wParam,0,pfn,260
        invoke convert_file,pfn       ; load file and convert to DB format
        .return 0

      .case WM_CLOSE
        invoke SendMessage,hWin,WM_DESTROY,0,0
        .return 0

      .case WM_DESTROY
        invoke PostQuitMessage,NULL

    .endsw

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

TBcreate proc parent:DWORD

  ; -----------------------------
  ; run to toolbar creation macro
  ; -----------------------------
    ToolbarInit tbbW, tbbH, parent

  ; -----------------------------------
  ; Add toolbar buttons and spaces here
  ; arg1 bmpID (zero based)
  ; arg2 cmdID (1st is 50)
  ; -----------------------------------
    ; TBspace
    TBbutton  0,  50
    TBbutton  1,  51
    TBbutton  2,  52
    ; TBspace
    TBbutton  3,  53
    ; TBspace
    TBbutton  4,  54
    TBbutton  5,  55
    ; TBspace
  ; -----------------------------------

    mov rax, tbhandl

    ret

TBcreate endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

rich_edit proc hParent:QWORD,instance:QWORD

    LOCAL pEdit  :QWORD
    LOCAL hFont  :QWORD
    LOCAL styl   :QWORD

  ; ---------------------------
  ; create the richedit control
  ; ---------------------------
    mov styl, WS_VISIBLE or WS_CHILDWINDOW or WS_CLIPSIBLINGS or \
              ES_MULTILINE or WS_VSCROLL or WS_HSCROLL or ES_AUTOHSCROLL or \
              ES_AUTOVSCROLL or ES_NOHIDESEL or ES_DISABLENOSCROLL

    invoke CreateWindowEx,WS_EX_LEFT,"RichEdit20a", \         ; WS_EX_STATICEDGE
             0,styl,0,0,200,100,hParent,111,instance,0

    mov pEdit, rax
  ; ---------------------------

    invoke SendMessage,pEdit,EM_EXLIMITTEXT,0,1000000000
    invoke SendMessage,pEdit,EM_SETOPTIONS,ECOOP_XOR,ECO_SELECTIONBAR

    mov hFont, rv(font_handle,"fixedsys",9,600)   ; library procedure
    invoke SendMessage,pEdit,WM_SETFONT,hFont,TRUE

    mov ecx, 10
    mov edx, 5
    mov ax, dx
    rol eax, 16
    mov ax, cx
    invoke SendMessage,pEdit,EM_SETMARGINS,EC_LEFTMARGIN or EC_RIGHTMARGIN,eax

    invoke SendMessage,pEdit,EM_SETTEXTMODE,TM_PLAINTEXT or \
                             TM_MULTILEVELUNDO or TM_MULTICODEPAGE, 0
    mov rax, pEdit

    ret

rich_edit endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

StatusBar proc hParent:QWORD

    LOCAL handl :QWORD
    LOCAL sbParts[4] :DWORD
    LOCAL r12reg :QWORD

    mov r12reg, r12

    mov handl, rv(CreateStatusWindow,WS_CHILD or WS_VISIBLE or SBS_SIZEGRIP,NULL,hParent,200)

  ; --------------------------------------------
  ; set the width of each part, -1 for last part
  ; --------------------------------------------

    lea r12, sbParts

    mov DWORD PTR [r12+0], 250
    mov DWORD PTR [r12+4], 500
    mov DWORD PTR [r12+8], 800
    mov DWORD PTR [r12+12],-1

    invoke SendMessage,handl,SB_SETPARTS,4,ADDR sbParts

    mov r12, r12reg
    mov rax, handl

    ret

StatusBar endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

  MEMORYSTATUSEX STRUCT QWORD
    dwLength dd ?
    dwMemoryLoad dd ?
    ullTotalPhys dq ?
    ullAvailPhys dq ?
    ullTotalPageFile dq ?
    ullAvailPageFile dq ?
    ullTotalVirtual dq ?
    ullAvailVirtual dq ?
    ullAvailExtendedVirtual dq ?
  MEMORYSTATUSEX ENDS

    SYSTEM_INFOx STRUCT QWORD
        UNION
        dwOemId dd ?
          STRUCT
            wProcessorArchitecture dw ?
            wReserved dw ?
          ENDS
        ENDS
      dwPageSize dd ?
      lpMinimumApplicationAddress dq ?
      lpMaximumApplicationAddress dq ?
      dwActiveProcessorMask dq ?
      dwNumberOfProcessors dd ?
      dwProcessorType dd ?
      dwAllocationGranularity dd ?
      wProcessorLevel dw ?
      wProcessorRevision dw ?
    SYSTEM_INFOx ENDS

AboutDlg proc hWin:QWORD,uMsg:QWORD,wParam:QWORD,lParam:QWORD

    LOCAL hStatic :QWORD
    LOCAL hButn   :QWORD
    LOCAL hText   :QWORD
    LOCAL osInf   :QWORD
    LOCAL wickd   :QWORD
    LOCAL rct     :RECT
    LOCAL buffer[1024]:BYTE
    LOCAL pbuff   :QWORD
    LOCAL vbuffr[64]:BYTE
    LOCAL vendor  :QWORD
    LOCAL cpubuf[128]:BYTE
    LOCAL cpustr  :QWORD
    LOCAL mstat   :QWORD
    LOCAL astat   :QWORD
    LOCAL mse     :MEMORYSTATUSEX
    LOCAL syi     :SYSTEM_INFOx
    LOCAL lpp     :QWORD

    .switch uMsg
      .case WM_INITDIALOG
        mov hStatic, rv(GetDlgItem,hWin,101)
        mov hButn,   rv(GetDlgItem,hWin,102)
        mov hText,   rv(GetDlgItem,hWin,103)
        mov osInf,   rv(GetDlgItem,hWin,104)
        mov wickd,   rv(GetDlgItem,hWin,105)

      .data
        tmsg db "Bin2db64 (c) Copyright The MASM64 SDK 1998 - 2022",13,10
             db "Steve Hutchesson <hutch@movsd.com> All Rights Reserved.",13,10
             db "A Tool To Convert Binary Files To DB Format.",13,10,13,10
             db "The operating system reports...",0

        tail db "A 64 bit Portable Executable Application.",13,10
             db "Wickedly Crafted In Microsoft Assembler (MASM).",0
      .code

        invoke SetWindowText,hWin," About Bin2db64"

        mov pbuff, ptr$(buffer)
        mcat pbuff,ADDR tmsg
        invoke SetWindowText,hText,pbuff

        mov vendor, ptr$(vbuffr)
        invoke Get_Vendor,vendor

        mov cpustr, ptr$(cpubuf)
        invoke get_cpu_id_string,cpustr

        mov mse.dwLength, SIZEOF MEMORYSTATUSEX                 ; initialise length
        invoke GlobalMemoryStatusEx,ADDR mse                    ; call API

        mov mstat, rv(intdiv,mse.ullTotalPhys,1024*1024)
        mov astat, rv(intdiv,mse.ullAvailPhys,1024*1024)

        mov pbuff, ptr$(buffer)

        invoke GetSystemInfo,ADDR syi

        xor rax, rax
        mov eax, syi.dwNumberOfProcessors
        mov lpp, rax

        mcat pbuff,"Your processor is ",vendor,lf, \
             cpustr,lf, \
             str$(lpp)," logical processors present.",lf, \
             "Physical memory    ",str$(mstat)," megabytes.",lf, \
             "Available memory   ",str$(astat)," megabytes.",lf,lf

        invoke SetWindowText,osInf,pbuff
        invoke SetWindowText,wickd,ADDR tail

      ; -------------------------------------
      ; load the icon into the static control
      ; -------------------------------------
        invoke SendMessage,hStatic,STM_SETIMAGE,IMAGE_ICON,hIcon

      ; ---------------------------
      ; set the icon for the dialog
      ; ---------------------------
        invoke SendMessage,hWin,WM_SETICON,1,hIcon
        mov rax, TRUE
        ret

      .case WM_COMMAND
        .switch wParam
          .case 102                     ; the OK button
            jmp exit_dialog
        .endsw

      .case WM_CLOSE
        exit_dialog:
        invoke EndDialog,hWin,0         ; exit from system menu
    .endsw

    xor rax, rax
    ret

AboutDlg endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

rebar proc instance:QWORD,hParent:QWORD,htrebar:QWORD

    LOCAL hrbar :QWORD

    fn CreateWindowEx,WS_EX_LEFT,"ReBarWindow32",NULL, \
                      WS_VISIBLE or WS_CHILD or \
                      WS_CLIPCHILDREN or WS_CLIPSIBLINGS or \
                      RBS_VARHEIGHT or CCS_NOPARENTALIGN or CCS_NODIVIDER, \
                      -2,0,sWid,htrebar,hParent,NULL,instance,NULL
    mov hrbar, rax

    invoke ShowWindow,hrbar,SW_SHOW
    invoke UpdateWindow,hrbar

    mov rax, hrbar

    ret

rebar endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

addband proc instance:QWORD,hrbar:QWORD

    LOCAL tbhandl   :QWORD
    LOCAL rbbi      :REBARBANDINFO

    mov tbhandl, rv(TBcreate,hrbar)

    mov rbbi.cbSize,      sizeof REBARBANDINFO
    mov rbbi.fMask,       RBBIM_ID or RBBIM_STYLE or \
                          RBBIM_BACKGROUND or RBBIM_CHILDSIZE or RBBIM_CHILD
    mov rbbi.wID,         125
    mov rbbi.fStyle,      RBBS_FIXEDBMP
    mrm rbbi.hbmBack,     tbTile
    mov rbbi.cxMinChild,  0
    mrmd rbbi.cyMinChild, rbht
    mrm rbbi.hwndChild,   tbhandl

    invoke SendMessage,hrbar,RB_INSERTBAND,0,ADDR rbbi

    mov rax, tbhandl

    ret

addband endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

set_text_colour proc Edit:DWORD,txtcolour:DWORD

    .data?
      align 16
      cfm2 CHARFORMAT2 <?>
    .code

    mov cfm2.cbSize,            SIZEOF CHARFORMAT2
    mov cfm2.dwMask,            CFM_COLOR
    mov cfm2.dwEffects,         0
    mov cfm2.yHeight,           0
    mov cfm2.yOffset,           0
    mrmd cfm2.crTextColor,      txtcolour
    mov cfm2.bCharSet,          0
    mov cfm2.bPitchAndFamily,   0
    mov cfm2.szFaceName,        0
    mov cfm2.wWeight,           0
    mov cfm2.sSpacing,          0
    mov cfm2.crBackColor,       0
    mov cfm2.lcid,              0
    mov cfm2.dwReserved,        0
    mov cfm2.sStyle,            0
    mov cfm2.wKerning,          0
    mov cfm2.bUnderlineType,    0
    mov cfm2.bAnimation,        0
    mov cfm2.bRevAuthor,        0

    invoke PostMessage,Edit,EM_SETCHARFORMAT,SCF_ALL,ADDR cfm2

    ret

set_text_colour endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

set_edit_colours proc

    invoke SendMessage,hEdit,EM_SETBKGNDCOLOR,0,bak_colour
    invoke set_text_colour,hEdit,txt_colour

    ret

set_edit_colours endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

copy_all proc

    LOCAL cr :CHARRANGE

    mov cr.cpMin, 0
    mov cr.cpMax, -1

    invoke SendMessage,hEdit,EM_EXSETSEL,0,ADDR cr
    invoke SendMessage,hEdit,WM_COPY,0,0

    ret

copy_all endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

convert_file proc ptrfn:QWORD

    LOCAL pmem :QWORD
    LOCAL fptr :QWORD
    LOCAL flen :QWORD
    LOCAL olen :QWORD
    LOCAL tPtr :QWORD
    LOCAL cr   :CHARRANGE
    LOCAL gpbuff[260]:BYTE

    mov fptr, rv(load_file,ptrfn)
    mov olen, rcx
    lea rcx, [rcx+rcx*4]
    mov flen, rcx
    mov pmem, alloc(flen)

    invoke ascii_dump,fptr,pmem,olen
    invoke dbcompact,pmem

    mov tPtr, ptr$(gpbuff)
    mcat tPtr,"; Original file ",ptrfn," at ",str$(olen)," bytes",lf,lf

    invoke SetWindowText,hEdit,tPtr
    invoke SendMessage,hEdit,WM_KEYDOWN,VK_END,0
    invoke SendMessage,hEdit,WM_KEYDOWN,VK_DOWN,0
    invoke SendMessage,hEdit,EM_REPLACESEL,TRUE,pmem
    mov cr.cpMin, 0
    mov cr.cpMax, 0
    invoke SendMessage,hEdit,EM_EXSETSEL,0,ADDR cr

    mov flen, rv(GetWindowTextLength,hEdit)
    mov tPtr, ptr$(gpbuff)
    mcat tPtr," Converted File Is ",str$(flen)," Bytes In Length"
    invoke SendMessage,hStatus,SB_SETTEXT,0,tPtr

    mfree pmem
    mfree fptr

    ret

convert_file endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end


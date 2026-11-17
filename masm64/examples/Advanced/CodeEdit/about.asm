; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

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

    ; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

      .data
        tmsg db "Win 64 Code Editor © Copyright 2022",13,10
             db "The MASM64 SDK All Rights Reserved.",13,10
             db "A small footprint pure ASCII code editor.",13,10,13,10
             db "The operating system reports...",0

        tail db "A 64 bit Portable Executable Application.",13,10
             db "Wickedly Crafted In Microsoft Assembler <MASM>",0
      .code

        invoke SetWindowText,hWin," About CodeEdit"

    ; «»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»«»

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

      .case WM_CTLCOLORDLG
        mov rax, hBrush
        ret

      .case WM_CTLCOLORBTN
        mov rax, bBordr
        ret

      .case WM_CTLCOLORSTATIC                                       ; static controls
        rcall SetBkColor,wParam,00222222h
        rcall SetTextColor,wParam,00FFFFFFh
        mov rax, hBrush
        ret

      .case WM_CTLCOLOREDIT                                         ; edit controls
        rcall SetBkColor,wParam,00111111h
        rcall SetTextColor,wParam,00FFFFFFh
        mov rax, eColor
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

; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

; ==================================================================================================
; Title:      Demo08_Main.inc
; Author:     G. Friedrich
; Version:    C.1.0
; Purpose:    ObjAsm DlgApp demo application.
; Notes:      Version C.1.0, September 2021
;               - First release.
; ==================================================================================================


; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Object:     Application
; Purpose:    Main application dialog.

Object Application,, DlgApp
  RedefineMethod    CtlsSet
  RedefineMethod    Init

  VirtualEvent      OnCommand,          WM_COMMAND
  VirtualEvent      OnCtlColorStatic,   WM_CTLCOLORSTATIC
ObjectEnd


.code
; ==================================================================================================
;    Demo08 implementation
; ==================================================================================================

IDC_STC_MESSAGE equ 1001
CStr Message, CRLF, "Hello", CRLF, CRLF, \
              "This is a dialog that acts", CRLF, \
              "as the main application window.", CRLF, \
              "Press 'OK' or the close button to", CRLF, \
              "exit the application."

; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Method:     Application.CtlsSet
; Purpose:    Set dialog controls.
; Arguments:  None.
; Return:     Nothing.

Method Application.CtlsSet
  SetObject xcx
  invoke SetDlgItemText, [xcx].hWnd, IDC_STC_MESSAGE, addr Message
MethodEnd

; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Method:     Application.Init
; Purpose:    Initialize the application object.
; Arguments:  None.
; Return:     Nothing.

Method Application.Init, uses xsi
  SetObject xsi
  ACall xsi.Init
  invoke CreateDialogParam, hInstance, IDD_DLG_MAIN, 0, $MethodAddr(DlgApp.WndProc), xsi
MethodEnd

; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Method:     Application.OnCtlColorStatic
; Purpose:    Event procedure for WM_CTLCOLORSTATIC message.
; Arguments:  Arg1: First message parameter.
;             Arg2: Second message parameter.
; Return:     xax = handle to a brush that the system uses to paint the background.

Method Application.OnCtlColorStatic,, wParam:WPARAM, lParam:LPARAM
  local HC:HIGHCONTRAST

  mov HC.cbSize, sizeof HIGHCONTRAST
  invoke SystemParametersInfo, SPI_GETHIGHCONTRAST, 0, addr HC, FALSE
  .ifBitSet HC.dwFlags, HCF_HIGHCONTRASTON
    xor eax, eax
  .else
    invoke GetStockObject, WHITE_BRUSH
  .endif
MethodEnd

; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Method:     Application.OnCommand
; Purpose:    Event procedure for WM_COMMAND message.
; Arguments:  Arg1: First message parameter.
;             Arg2: Second message parameter.
; Return:     eax = If an application processes this message, it should return zero.

Method Application.OnCommand, uses xsi, wParam:WPARAM, lParam:LPARAM
  SetObject xsi
  mov xax, wParam
  .if ax == IDOK
    OCall xsi.CtlsGet
    invoke DestroyWindow, [xsi].hWnd
    xor eax, eax                                        ;Return zero
  .elseif ax == IDCANCEL
    invoke DestroyWindow, [xsi].hWnd
    xor eax, eax                                        ;Return zero
  .else
    xor eax, eax
    inc eax
  .endif
MethodEnd

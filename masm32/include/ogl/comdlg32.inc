;*  COMDLG32.LIB prototypes for MASM
;* (C)hardCode | http://bizarrecreations.webjump.com

include WinExtra\unicode.def

IFNDEF __COMDLG32PROTOS__
__COMDLG32PROTOS__=1

_XDEF ChooseColor,<:DWORD>

_XDEF ChooseFont,<:DWORD>

CommDlgExtendedError PROTO

_XDEF FindText,<:DWORD>

FormatCharDlgProc PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF GetFileTitle,<:DWORD,:DWORD,:DWORD>

_XDEF GetOpenFileName,<:DWORD>

_XDEF GetSaveFileName,<:DWORD>

LoadAlterBitmap PROTO :DWORD,:DWORD,:DWORD

_XDEF PageSetupDlg,<:DWORD>

_XDEF PrintDlg,<:DWORD>

_XDEF ReplaceText,<:DWORD>

WantArrows PROTO :DWORD,:DWORD,:DWORD,:DWORD

dwLBSubclass PROTO :DWORD,:DWORD,:DWORD,:DWORD

dwOKSubclass PROTO :DWORD,:DWORD,:DWORD,:DWORD

ENDIF ;__COMDLG32PROTOS__

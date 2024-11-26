; ==================================================================================================
; Title:      BStrLength.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  BStrLength
; Purpose:    Determine the length of a BStr not including the ZTC.
; Arguments:  Arg1: -> Source BStr.
; Return:     eax = Length of the string in characters.

OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

align ALIGN_CODE
BStrLength proc pBStr:POINTER
  mov ecx, [esp + 4]                                    ;ecx -> BStr
  mov eax, DWORD ptr [ecx - 4]                          ;Get the byte length DWORD
  shr eax, 1                                            ;Character count
  ret 4
BStrLength endp

OPTION PROLOGUE:PrologueDef
OPTION EPILOGUE:EpilogueDef

end

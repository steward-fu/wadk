; ==================================================================================================
; Title:      StrCLengthW.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  StrCLengthW
; Purpose:    Get the character count of the source WIDE string with length limitation.
; Arguments:  Arg1: -> Source WIDE string.
;             Arg3: Maximal character count.
; Return:     eax = Limited character count.

OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

align ALIGN_CODE
StrCLengthW proc pStringW:POINTER, dMaxChars:DWORD
  push edi
  mov ecx, [esp + 12]                                   ;ecx = dMaxChars
  mov edi, [esp + 8]                                    ;edi -> StringW
  inc ecx
  mov edx, ecx
  xor ax, ax
  repne scasw
  not ecx
  lea eax, [ecx + edx]
  pop edi
  ret 8
StrCLengthW endp

OPTION PROLOGUE:PrologueDef
OPTION EPILOGUE:EpilogueDef

end

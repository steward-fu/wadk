; ==================================================================================================
; Title:      StrCompA.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  StrCompA
; Purpose:    Compare 2 ANSI strings with case sensitivity.
; Arguments:  Arg1: -> ANSI string 1.
;             Arg2: -> ANSI string 2.
; Return:     If string 1 < string 2, then eax < 0.
;             If string 1 = string 2, then eax = 0.
;             If string 1 > string 2, then eax > 0.

OPTION PROC:NONE
align ALIGN_CODE
StrCompA proc pStr1:POINTER, pStr2:POINTER
  xor r8, r8
  xor eax, eax
@@:
  mov al, [rcx + r8]
  test al, al
  jz @F
  cmp al, [rdx + r8]
  jnz @F
  inc r8
  jmp @B
@@:
  movzx ecx, CHRA ptr [rdx + r8]
  sub eax, ecx
  ret
StrCompA endp
OPTION PROC:DEFAULT

end

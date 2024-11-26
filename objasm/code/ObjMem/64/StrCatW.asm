; ==================================================================================================
; Title:      StrCatW.asm
; Author:     G. Friedrich
; Version:    C.1.1
; Notes:      Version C.1.0, October 2017
;               - First release.
;             Version C.1.1, July 2022
;               - Return value added.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  StrCatW
; Purpose:    Concatenate 2 WIDE strings.
; Arguments:  Arg1: Destrination WIDE string.
;             Arg2: Source WIDE string.
; Return:     Nothing.

align ALIGN_CODE
StrCatW proc pDstStrW:POINTER, pSrcStrW:POINTER
  invoke StrEndW, rcx                                   ;pDstStrW
  invoke StrCopyW, rax, pSrcStrW
  sub rax, sizeof(CHRW)                                 ;Sizeof ZTC
  ret
StrCatW endp

end

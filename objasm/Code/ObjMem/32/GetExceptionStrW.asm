; ==================================================================================================
; Title:      GetExceptionStrW.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  GetExceptionStrW
; Purpose:    Translate an exception code to a WIDE string.
; Arguments:  Arg1: Exception code.
; Return:     eax -> WIDE string.

OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

align ALIGN_CODE
GetExceptionStrW proc dExceptionCode:DWORD
  mov eax, [esp + 4]                                    ;dExceptionCode
  cmp eax, 0C0000005h                                   ;EXCEPTION_ACCESS_VIOLATION
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_ACCESS_VIOLATION")
  ret 4
@@:
  cmp eax, 0C000008Ch                                   ;EXCEPTION_ARRAY_BOUNDS_EXCEEDED
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_ARRAY_BOUNDS_EXCEEDED")
  ret 4
@@:
  cmp eax, 080000003h                                   ;EXCEPTION_BREAKPOINT
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_BREAKPOINT")
  ret 4
@@:
  cmp eax, 080000002h                                   ;EXCEPTION_DATATYPE_MISALIGNMENT
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_DATATYPE_MISALIGNMENT")
  ret 4
@@:
  cmp eax, 0C000008Dh                                   ;EXCEPTION_FLT_DENORMAL_OPERAND
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_DENORMAL_OPERAND")
  ret 4
@@:
  cmp eax, 0C000008Eh                                   ;EXCEPTION_FLT_DIVIDE_BY_ZERO
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_DIVIDE_BY_ZERO")
  ret 4
@@:
  cmp eax, 0C000008Fh                                   ;EXCEPTION_FLT_INEXACT_RESULT
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_INEXACT_RESULT")
  ret 4
@@:
  cmp eax, 0C0000090h                                   ;EXCEPTION_FLT_INVALID_OPERATION
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_INVALID_OPERATION")
  ret 4
@@:
  cmp eax, 0C0000091h                                   ;EXCEPTION_FLT_OVERFLOW
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_OVERFLOW")
  ret 4
@@:
  cmp eax, 0C0000092h                                   ;EXCEPTION_FLT_STACK_CHECK
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_STACK_CHECK")
  ret 4
@@:
  cmp eax, 0C0000093h                                   ;EXCEPTION_FLT_UNDERFLOW
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_FLT_UNDERFLOW")
  ret 4
@@:
  cmp eax, 0C000001Dh                                   ;EXCEPTION_ILLEGAL_INSTRUCTION
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_ILLEGAL_INSTRUCTION")
  ret 4
@@:
  cmp eax, 0C0000006h                                   ;EXCEPTION_IN_PAGE_ERROR
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_IN_PAGE_ERROR")
  ret 4
@@:
  cmp eax, 0C0000094h                                   ;EXCEPTION_INT_DIVIDE_BY_ZERO
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_INT_DIVIDE_BY_ZERO")
  ret 4
@@:
  cmp eax, 0C0000095h                                   ;EXCEPTION_INT_OVERFLOW
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_INT_OVERFLOW")
  ret 4
@@:
  cmp eax, 080000004h                                   ;EXCEPTION_SINGLE_STEP
  jne @F
  mov eax, $OfsCStrW("EXCEPTION_SINGLE_STEP")
  ret 4
@@:
  mov eax, $OfsCStrW("UNKNOWN_EXCEPTION")
  ret 4
GetExceptionStrW endp

OPTION PROLOGUE:PrologueDef
OPTION EPILOGUE:EpilogueDef

end

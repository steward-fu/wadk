; ==================================================================================================
; Title:      ComGetErrStrW.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, August 2022
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
TARGET_STR_TYPE = STR_TYPE_WIDE
% include &ObjMemPath&ObjMemUefi.cop

ProcName textequ <ComGetErrStrW>

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  ComGetErrStrW
; Purpose:    Return a description WIDE string from a COM error code.
; Arguments:  Arg1: COM error code.
; Return:     eax -> Error string.

% include &ObjMemPath&Common\\ComGetErrStr_TX.inc

end

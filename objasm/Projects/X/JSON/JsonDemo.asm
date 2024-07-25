; ==================================================================================================
; Title:      JsonDemo.asm
; Author:     G. Friedrich
; Version:    1.0.0
; Purpose:    ObjAsm JSON Application.
; Notes:      Version 1.0.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\Code\Macros\Model.inc
SysSetup OOP, WIN64, WIDE_STRING, DEBUG(WND)

% includelib &LibPath&Windows\shell32.lib
% includelib &LibPath&Windows\shlwapi.lib
% include &MacPath&LDLL.inc

;Load or build the following objects
MakeObjects Primer, Stream, DiskStream, WinPrimer
MakeObjects Button, Hyperlink
MakeObjects Window, Dialog, DialogModal, DialogAbout
MakeObjects WinApp, SdiApp
MakeObjects Json

include JsonDemo_Globals.inc
include JsonDemo_Main.inc

.code
start proc
  SysInit

  DbgClearAll
  OCall $ObjTmpl(JsonDemoApp)::JsonDemoApp.Init
  OCall $ObjTmpl(JsonDemoApp)::JsonDemoApp.Run
  OCall $ObjTmpl(JsonDemoApp)::JsonDemoApp.Done

  SysDone
  invoke ExitProcess, 0
start endp

end

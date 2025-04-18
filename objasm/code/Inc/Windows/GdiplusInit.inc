;Include file created by h2incX, Version C.01.00, 30/03/2019 18:59
;(C) 2018-today by Biterider, 2005-2009 by Japheth
;Source file: 'D:\ObjAsm\Projects\32\h2IncX\header\GdiplusInit.h', last modified: 22/10/2018 20:35
;Creation parameters: 

ifndef _GDIPLUSINIT_H
  _GDIPLUSINIT_H equ <>
  include winapifamily.inc
  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    if _MSC_VER ge 1200
    endif
    DebugEventLevel typedef SDWORD
    DebugEventLevelFatal equ 0
    DebugEventLevelWarning equ 1
    
    TYPE_DebugEventProc typedef proto WIN_STD_CALL_CONV :DebugEventLevel, :ptr CHAR
    DebugEventProc typedef ptr TYPE_DebugEventProc
    TYPE_NotificationHookProc typedef proto WIN_STD_CALL_CONV :ptr ULONG_PTR
    NotificationHookProc typedef ptr TYPE_NotificationHookProc
    TYPE_NotificationUnhookProc typedef proto WIN_STD_CALL_CONV :ULONG_PTR
    NotificationUnhookProc typedef ptr TYPE_NotificationUnhookProc
    GdiplusStartupInput struct
      GdiplusVersion UINT32 ?
      DebugEventCallback DebugEventProc ?
      SuppressBackgroundThread BOOL ?
      SuppressExternalCodecs BOOL ?
    GdiplusStartupInput ends
;    GdiplusStartupInput typedef proto :DebugEventProc, :BOOL, :BOOL
    if (GDIPVER ge 0110h)
      GdiplusStartupInputEx struct
        GdiplusStartupInput <>
        StartupParameters INT_ ?
        GdiplusStartupInputEx typedef proto :INT_, :DebugEventProc, :BOOL, :BOOL
        GdiplusStartupParams typedef SDWORD
        GdiplusStartupDefault equ 0
        GdiplusStartupNoSetRound equ 1
        GdiplusStartupSetPSValue equ 2
        GdiplusStartupTransparencyMask equ 0FF000000h
      GdiplusStartupInputEx ends
    endif
    GdiplusStartupOutput_ struct
      NotificationHook NotificationHookProc ?
      NotificationUnhook NotificationUnhookProc ?
    GdiplusStartupOutput_ ends
    GdiplusStartup proto WIN_STD_CALL_CONV :ptr ULONG_PTR, :ptr GdiplusStartupInput, :ptr GdiplusStartupOutput
    GdiplusShutdown proto WIN_STD_CALL_CONV :ULONG_PTR
    if _MSC_VER ge 1200
    endif
  endif
endif
 
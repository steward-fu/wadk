;Include file created by h2incX, Version C.01.00, 30/03/2019 18:59
;(C) 2018-today by Biterider, 2005-2009 by Japheth
;Source file: 'D:\ObjAsm\Projects\32\h2IncX\header\GdiplusGraphics.h', last modified: 22/10/2018 20:35
;Creation parameters: 

ifndef _GDIPLUSGRAPHICS_H
  _GDIPLUSGRAPHICS_H equ <>
  include winapifamily.inc
  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    if _MSC_VER ge 1200
      if _MSC_VER ge 1400
      endif
    endif
;    Graphics struct
;      ;public:
;       GdiplusBase <>
;      if (GDIPVER ge 0110h)
;      endif
;      if (GDIPVER ge 0110h)
;      endif
;    Graphics ends
;    GetBounds proto WIN_STD_CALL_CONV :ptr RectF, :ptr Matrix, :ptr Pen
;    if_ proto WIN_STD_CALL_CONV :matrix
;    if_ proto WIN_STD_CALL_CONV :pen
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :bounds, :nativeMatrix, :nativePen
;    GetBounds proto WIN_STD_CALL_CONV :ptr Rect, :ptr Matrix, :ptr Pen
;    if_ proto WIN_STD_CALL_CONV :matrix
;    if_ proto WIN_STD_CALL_CONV :pen
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :bounds, :nativeMatrix, :nativePen
;    IsVisible proto WIN_STD_CALL_CONV :REAL, :REAL, :ptr Graphics
;    if_ proto WIN_STD_CALL_CONV :g
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :x, :y, :nativeGraphics, :ptr booln
;    IsVisible proto WIN_STD_CALL_CONV :INT_, :INT_, :ptr Graphics
;    if_ proto WIN_STD_CALL_CONV :g
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :x, :y, :nativeGraphics, :ptr booln
;    IsOutlineVisible proto WIN_STD_CALL_CONV :REAL, :REAL, :ptr Pen, :ptr Graphics
;    if_ proto WIN_STD_CALL_CONV :g
;    if_ proto WIN_STD_CALL_CONV :pen
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :x, :y, :nativePen, :nativeGraphics, :ptr booln
;    IsOutlineVisible proto WIN_STD_CALL_CONV :INT_, :INT_, :ptr Pen, :ptr Graphics
;    if_ proto WIN_STD_CALL_CONV :g
;    if_ proto WIN_STD_CALL_CONV :pen
;    SetStatus proto WIN_STD_CALL_CONV :DllExports, :x, :y, :nativePen, :nativeGraphics, :ptr booln
;    if _MSC_VER ge 1200
;    endif
  endif
endif
 
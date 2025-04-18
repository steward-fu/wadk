;Include file created by h2incX, Version C.01.00, 30/03/2019 18:59
;(C) 2018-today by Biterider, 2005-2009 by Japheth
;Source file: 'D:\ObjAsm\Projects\32\h2IncX\header\GdiPlus.h', last modified: 22/10/2018 20:35
;Creation parameters: 

ifndef _GDIPLUS_H
  _GDIPLUS_H equ <>
  include winapifamily.inc
  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    INT16 typedef SWORD
    UINT16 typedef WORD
    ifndef GDIPVER
      GDIPVER equ 0100h
    endif
    include pshpack8.inc
    include GdiplusMem.inc
    include GdiplusBase.inc
    include GdiplusEnums.inc
    include GdiplusTypes.inc
    include GdiplusInit.inc
    include GdiplusPixelFormats.inc
    include GdiplusColor.inc
    include GdiplusMetaHeader.inc
    include GdiplusImaging.inc
    include GdiplusColorMatrix.inc
    if (GDIPVER ge 0110h)
      include GdiplusEffects.inc
    endif
    include GdiplusGpStubs.inc
    include GdiplusHeaders.inc
    include GdiplusFlat.inc
    include GdiplusImageAttributes.inc
    include GdiplusMatrix.inc
    include GdiplusBrush.inc
    include GdiplusPen.inc
    include GdiplusStringFormat.inc
    include GdiplusPath.inc
    include GdiplusLineCaps.inc
    include GdiplusGraphics.inc
    include GdiplusMetafile.inc
    include GdiplusCachedBitmap.inc
    include GdiplusRegion.inc
    include GdiplusFontCollection.inc
    include GdiplusFontFamily.inc
    include GdiplusFont.inc
    include GdiplusBitmap.inc
    include GdiplusImageCodec.inc
    include poppack.inc
  endif
endif
 
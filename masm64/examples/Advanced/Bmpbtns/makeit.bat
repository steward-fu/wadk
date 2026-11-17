@echo off

set appname=bmpbtns

del %appname%.obj
del %appname%.exe

\masm64\bin64\porc64.exe rsrc.rc

\masm64\bin64\ml64.exe /c /nologo %appname%.asm

\masm64\bin64\Polink.exe /SUBSYSTEM:WINDOWS /ENTRY:entry_point /nologo /LARGEADDRESSAWARE %appname%.obj rsrc.res

dir %appname%.*

pause

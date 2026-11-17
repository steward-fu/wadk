@echo off

set appname=SysProperties

if exist %1.obj del %appname%.obj
if exist %1.exe del %appname%.exe

\masm64\bin64\rc.exe rsrc.rc

\masm64\bin64\ml64.exe /c /nologo %appname%.asm

\masm64\bin64\link.exe /SUBSYSTEM:WINDOWS /ENTRY:entry_point /LARGEADDRESSAWARE %appname%.obj rsrc.res

dir %appname%.*

pause

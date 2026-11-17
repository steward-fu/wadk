@echo off

set appname=ShellEx

if exist %appname%.obj del %appname%.obj
if exist %appname%.exe del %appname%.exe

\masm64\bin64\ml64.exe /c %appname%.asm

\masm64\bin64\polink.exe /SUBSYSTEM:WINDOWS /MACHINE:X64 /ENTRY:entry_point /nologo /LARGEADDRESSAWARE %appname%.obj

dir %appname%.*

pause

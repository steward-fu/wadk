@echo off

set appname=reptst

if exist %appname%.obj del %appname%.obj
if exist %appname%.exe del %appname%.exe

\masm64\bin64\ml64.exe /c %appname%.asm

\masm64\bin64\polink.exe /SUBSYSTEM:CONSOLE /MACHINE:X64 /ENTRY:entry_point /nologo /LARGEADDRESSAWARE %appname%.obj

dir %appname%.*

pause

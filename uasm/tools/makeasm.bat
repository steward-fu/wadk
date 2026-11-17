@echo off

jwasm -c -coff -Fl -I..\Include -D_DLL %1.asm 
rem use msvcrt.lib, the dynamic C runtime lib of VC
polink %1.obj /Opt:NoWin98 /SUBSYSTEM:console /LIBPATH:..\Lib msvcrt.lib kernel32.lib user32.lib /MAP

rem jwasm -c -coff -Fl -I..\Include %1.asm
rem use libc32s.lib, a simple, VC compatible static C runtime lib
rem link %1.obj /LIBPATH:..\Lib /SUBSYSTEM:console libc32s.lib kernel32.lib user32.lib /MAP

rem use libc.lib, the static C runtime lib of VC
rem link %1.obj /SUBSYSTEM:console /LIBPATH:..\Lib libc.lib kernel32.lib user32.lib /MAP


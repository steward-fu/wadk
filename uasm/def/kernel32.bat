@echo off

rem create KERNEL32.LIB

polib /DEF:winbase.def /DEF:wincon.def /DEF:winnls.def /DEF:tlhelp32.def /OUT:..\Lib\KERNEL32.LIB
rem def2lib winbase.def

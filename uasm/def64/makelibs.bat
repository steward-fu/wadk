@echo off
rem creates all Win64 libraries for which .DEF files are supplied
mkdir ..\Lib64
polib /DEF:advapi32.def /MACHINE:X64 /OUT:..\Lib64\ADVAPI32.LIB
polib /DEF:comctl32.def /MACHINE:X64 /OUT:..\Lib64\COMCTL32.LIB
polib /DEF:comdlg32.def /MACHINE:X64 /OUT:..\Lib64\COMDLG32.LIB
polib /DEF:dbgeng.def   /MACHINE:X64 /OUT:..\Lib64\DBGENG.LIB
polib /DEF:gdi32.def    /MACHINE:X64 /OUT:..\Lib64\GDI32.LIB
polib /DEF:kernel32.def /MACHINE:X64 /OUT:..\Lib64\KERNEL32.LIB
polib /DEF:msvcrt.def   /MACHINE:X64 /OUT:..\Lib64\MSVCRT.LIB
polib /DEF:ole32.def    /MACHINE:X64 /OUT:..\Lib64\OLE32.LIB
polib /DEF:oleaut32.def /MACHINE:X64 /OUT:..\Lib64\OLEAUT32.LIB
polib /DEF:shell32.def  /MACHINE:X64 /OUT:..\Lib64\SHELL32.LIB
polib /DEF:shlwapi.def  /MACHINE:X64 /OUT:..\Lib64\SHLWAPI.LIB
polib /DEF:user32.def   /MACHINE:X64 /OUT:..\Lib64\USER32.LIB
polib /DEF:ws2_32.def   /MACHINE:X64 /OUT:..\Lib64\WS2_32.LIB
polib /DEF:wsock32.def  /MACHINE:X64 /OUT:..\Lib64\WSOCK32.LIB

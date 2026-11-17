@echo off

set appname=Ucase

del %appname%.obj
del %appname%.exe

\masm64\bin64\ml64.exe /c /nologo %appname%.asm

\masm64\bin64\Polink.exe /SUBSYSTEM:WINDOWS /ENTRY:PluginEntryPoint /DLL /DEF:deffile.def /nologo /LARGEADDRESSAWARE %appname%.obj rsrc.res

del %appname%.obj
del %appname%.exp
dir %appname%.*
copy %appname%.dll ..\..

pause

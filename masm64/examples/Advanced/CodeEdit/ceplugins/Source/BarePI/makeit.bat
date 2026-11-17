@echo off

set appname=testbare

del %appname%.obj
del %appname%.exe

\masm64\bin64\porc64.exe rsrc.rc

\masm64\bin64\ml64.exe /c /nologo %appname%.asm

:: -------------------------
:: with or without resources
:: -------------------------
\masm64\bin64\Polink.exe /SUBSYSTEM:WINDOWS /ENTRY:PluginEntryPoint /DLL /DEF:deffile.def /nologo /LARGEADDRESSAWARE %appname%.obj

:: \masm64\bin64\Polink.exe /SUBSYSTEM:WINDOWS /ENTRY:PluginEntryPoint /DLL /DEF:deffile.def /nologo /LARGEADDRESSAWARE %appname%.obj rsrc.res

del %appname%.obj
del %appname%.exp

dir %appname%.*

copy %appname%.dll ..\..

pause

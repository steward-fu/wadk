@echo off
set appname=cplugin
if exist %1.obj del %appname%.obj
if exist %1.exe del %appname%.dll


\masm64\bin64\rc.exe rsrc.rc


\masm64\bin64\ml64 /c %appname%.asm
\masm64\bin64\link /SUBSYSTEM:WINDOWS /entry:PluginEntryPoint /DLL /DEF:%appname%.def %appname%.obj rsrc.res
del %appname%.obj
del %appname%.exp
dir %appname%.*
copy cplugin.dll ..
pause

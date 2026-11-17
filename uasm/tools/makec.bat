@echo off
rem cl -c -Zp %1.c
cl -c -MD %1.c
link %1.obj /SUBSYSTEM:console msvcrt.lib kernel32.lib user32.lib /MAP /OPT:NOWIN98 /NOD

@echo off
rem create NTOSKRNL.LIB
rem note: this library contains FASTCALL entries (requires a polib version > 5)
polib /DEF:NTOSKRNL.def /OUT:..\Lib\NTOSKRNL.LIB

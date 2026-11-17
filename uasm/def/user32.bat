@echo off

rem create USER32.LIB

polib /DEF:winuser.def /OUT:..\Lib\USER32.LIB

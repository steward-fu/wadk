@echo off

rem create ADVAPI32.LIB

polib /DEF:advapi32.def /DEF:winreg.def /DEF:winsvc.def /DEF:aclapi.def /OUT:..\Lib\ADVAPI32.LIB

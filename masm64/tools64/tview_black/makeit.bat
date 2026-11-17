@echo off

set appname=tview

del %appname%.obj
del %appname%.exe

@echo.
@echo ------------------------------------------------------------------
@echo Ignore the warnings, they follow from merging a number of sections.
@echo ------------------------------------------------------------------
@echo.

\masm64\bin64\porc64.exe rsrc.rc

\masm64\bin64\ml64.exe /c /nologo %appname%.asm

\masm64\bin64\Polink.exe /SUBSYSTEM:WINDOWS /MERGE:.rsrc=.data /MERGE:.data=.text /ENTRY:entry_point /nologo /LARGEADDRESSAWARE %appname%.obj rsrc.res

dir %appname%.*

pause
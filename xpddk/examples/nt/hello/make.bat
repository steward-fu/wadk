"c:\xpddk\bin\x86\cl.exe" -nologo -I"c:\xpddk\inc\wxp" -I"c:\xpddk\inc\ddk\wxp" -I"c:\xpddk\inc\crt" -D_X86_=1 /c /Zel /Gz main.c

"c:\xpddk\bin\x86\link.exe" -INCREMENTAL:NO -driver -base:0x10000 -entry:DriverEntry -subsystem:native "c:\xpddk\lib\wxp\i386\ntoskrnl.lib" "c:\xpddk\lib\wxp\i386\csq.lib" -out:main.sys main.obj

if exist app.c (
    "c:\xpddk\bin\x86\cl.exe" -nologo -I"c:\xpddk\inc\wxp" -I"c:\xpddk\inc\wxp" -I"c:\xpddk\inc\crt" -D_X86_ -DWIN32_LEAN_AND_MEAN=1 /c /Zel /Gz app.c

    "c:\xpddk\bin\x86\link.exe" -incremental:no -debug:full -debugtype:cv -entry:mainCRTStartup -subsystem:console "c:\xpddk\lib\wxp\i386\msvcrt.lib" "c:\xpddk\lib\wxp\i386\advapi32.lib" "c:\xpddk\lib\wxp\i386\kernel32.lib" -out:app.exe app.obj
)

"c:\xpddk\bin\x86\cl.exe" -nologo -I"c:\xpddk\inc\wxp" -I"c:\xpddk\inc\ddk\wxp" -I"c:\xpddk\inc\ddk\wdm\wxp" -I"c:\xpddk\inc\crt" -I"c:\numega\driverworks\include" -I"c:\numega\driverworks\source" -D_X86_=1 -DNTVERSION='WDM' /c /Zel /Gz main.cpp

"c:\xpddk\bin\x86\link.exe" -driver -base:0x10000 -entry:DriverEntry@8 -subsystem:native,5.01 "c:\xpddk\lib\wxp\i386\wdm.lib" "c:\xpddk\lib\wxp\i386\ntoskrnl.lib" "c:\xpddk\lib\wxp\i386\csq.lib" "c:\numega\driverworks\lib\i386\checked\vdw_wdm.lib" -out:main.sys main.obj

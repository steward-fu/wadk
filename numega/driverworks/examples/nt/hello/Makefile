all:
	myx86 "c:\\xpddk\\bin\\x86\\cl.exe" -I"c:\\xpddk\\inc\\wxp" -I"c:\\xpddk\\inc\\ddk\\wxp" -I"c:\\xpddk\\inc\\ddk\\wdm\\wxp" -I"c:\\xpddk\\inc\\crt" -I"c:\\numega\\driverworks\\include" -I"c:\\numega\\driverworks\\source" -D_X86_=1 -DNTVERSION=\'WDM\' -DDBG=1 /c /Zel /Gz main.cpp
	lld-link /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no /opt/wadk/xpddk/lib/wxp/i386/ntoskrnl.lib /opt/wadk/numega/driverworks/lib/i386/checked/vdw_wdm.lib main.obj /out:main.sys
	python3 fix.py main.sys

run:
	genisoimage -R -J -l -follow -o cdrom.iso * /opt/wadk/tools/sc.exe
	myqemu winxp

clean:
	rm -rf cdrom.iso *.obj *.pdb main.sys

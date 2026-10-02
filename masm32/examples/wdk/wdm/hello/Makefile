all:
	myx86 "c:\masm32\bin\ml.exe" /c /coff /Cp /Zi /Zd main.asm
	lld-link main.obj /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no /opt/wadk/masm32/lib/wxp/i386/ntoskrnl.lib /out:main.sys
	python3 fix.py main.sys

run:
	genisoimage -o cdrom.iso * run.bat /opt/wadk/tools/devcon.exe
	myqemu winxp

clean:
	rm -rf main.sys main.obj main.pdb app.obj app.pdb app.exe main.err cdrom.iso

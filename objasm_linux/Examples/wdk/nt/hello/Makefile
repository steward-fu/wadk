all:
	uasm -coff -c -q -less -nomlib -FwNUL -Zi -Zd main.asm
	myx86 "c:\masm32\bin\link.exe" main.o /driver /base:0x10000 /subsystem:native /entry:DriverEntry "c:\masm32\lib\wxp\i386\ntoskrnl.lib" /out:main.sys

run:
	genisoimage -o cdrom.iso autorun.inf main.sys run.bat /opt/wadk/tools/sc.exe
	myqemu win2k

clean:
	rm -rf main.sys main.o cdrom.iso

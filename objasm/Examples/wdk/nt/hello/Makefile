all:
	uasm -coff -c -q -less -nomlib -FwNUL -Zi -Zd main.asm
	lld-link main.o /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no "/opt/wadk/masm32/lib/wxp/i386/ntoskrnl.lib" /out:main.sys
	python3 fix.py main.sys

run:
	genisoimage -R -J -o cdrom.iso autorun.inf main.sys run.bat /opt/wadk/tools/sc.exe
	myqemu win2k

clean:
	rm -rf main.sys main.o cdrom.iso

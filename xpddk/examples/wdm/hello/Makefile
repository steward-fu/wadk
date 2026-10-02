all:
	clang -target i686-pc-windows-msvc -I/opt/wadk/xpddk/inc/wxp -I/opt/wadk/xpddk/inc/ddk/wxp -I/opt/wadk/xpddk/inc/ddk/wdm/wxp -I/opt/wadk/xpddk/inc/crt -D_X86_ -Xclang -fdefault-calling-conv=stdcall -c main.c
	lld-link main.o /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no "/opt/wadk/masm32/lib/wxp/i386/ntoskrnl.lib" /out:main.sys
	python3 fix.py main.sys

run:
	genisoimage -R -J -o cdrom.iso autorun.inf main.sys main.inf run.bat /opt/wadk/tools/devcon.exe
	myqemu winxp

clean:
	rm -rf main.sys main.o cdrom.iso

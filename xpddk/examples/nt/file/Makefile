all:
	clang --target=i686-pc-windows-msvc -fno-builtin -mrtd -I/opt/wadk/xpddk/inc/wxp -I/opt/wadk/xpddk/inc/ddk/wxp -I/opt/wadk/xpddk/inc/crt -D_X86_=1 -c main.c -w
	lld-link main.o /demangle:no /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no /opt/wadk/xpddk/lib/wxp/i386/ntoskrnl.lib /opt/wadk/xpddk/lib/wxp/i386/wdm.lib /out:main.sys
	python3 fix.py main.sys

test:
	clang --target=i686-pc-windows-msvc -I/opt/wadk/xpddk/inc/wxp -I/opt/wadk/xpddk/inc/ddk/wxp -I/opt/wadk/xpddk/inc/crt -D_X86_=1 -c main.c -w
run:

	genisoimage -o cdrom.iso * /opt/wadk/tools/sc.exe
	myqemu winxp

clean:
	rm -rf main.sys main.obj main.o main.pdb app.obj app.pdb app.exe cdrom.iso

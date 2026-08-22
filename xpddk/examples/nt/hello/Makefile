all:
	clang --target=i686-pc-windows-msvc -fno-builtin -mrtd -I/opt/wadk/xpddk/inc/wxp -I/opt/wadk/xpddk/inc/ddk/wxp -I/opt/wadk/xpddk/inc/crt -D_X86_=1 -D_CLANG_=1 -c main.c -w
	lld-link main.o /driver /base:0x10000 /subsystem:native /entry:DriverEntry /safeseh:no /opt/wadk/xpddk/lib/wxp/i386/ntoskrnl.lib /out:main.sys
	python3 fix.py main.sys

run:
	genisoimage -R -J -l -follow -o cdrom.iso * /opt/wadk/tools/sc.exe
	myqemu win2k

clean:
	rm -rf main.sys main.obj main.o main.pdb app.obj app.o app.pdb app.exe cdrom.iso

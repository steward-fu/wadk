CFLAGS += -target i686-pc-windows-msvc
CFLAGS += -D_X86_
CFLAGS += -Xclang
CFLAGS += -fdefault-calling-conv=stdcall
CFLAGS += -I/opt/wadk/xpddk/inc/wxp
CFLAGS += -I/opt/wadk/xpddk/inc/ddk/wxp
CFLAGS += -I/opt/wadk/xpddk/inc/ddk/wdm/wxp
CFLAGS += -I/opt/wadk/xpddk/inc/crt

LDFLAGS += /driver
LDFLAGS += /base:0x10000
LDFLAGS += /subsystem:native
LDFLAGS += /entry:DriverEntry
LDFLAGS += /safeseh:no
LDFLAGS += /opt/wadk/masm32/lib/wxp/i386/ntoskrnl.lib

all:
	clang $(CFLAGS) -c main.c
	lld-link main.o $(LDFLAGS) /out:main.sys
	python3 fix.py main.sys

app:
	i686-w64-mingw32-gcc app.c -o app.exe

run:
	genisoimage -R -J -o cdrom.iso * /opt/wadk/tools/devcon.exe
	myqemu winxp

clean:
	rm -rf main.sys main.o app.exe cdrom.iso

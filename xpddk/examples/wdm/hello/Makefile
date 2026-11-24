TARGET  = main

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
LDFLAGS += /out:${TARGET}.sys
LDFLAGS += /opt/wadk/xpddk/lib/wxp/i386/ntoskrnl.lib

all:
	clang $(CFLAGS) -c ${TARGET}.c
	lld-link ${TARGET}.o $(LDFLAGS)
	python3 fix.py ${TARGET}.sys

run:
	genisoimage -R -J -o cdrom.iso * /opt/wadk/tools/devcon.exe
	myqemu winxp

clean:
	rm -rf ${TARGET}.sys ${TARGET}.o cdrom.iso

all:
	myx86 "c:\wdf\bin\x86\x86\cl.exe" -nologo -I"c:\wdf\inc\wdf\kmdf\1.9" -I"c:\wdf\inc\ddk" -I"c:\wdf\inc\crt" -I"c:\wdf\inc\api" -D_X86_ /c /Zl /Gz /DKMDF_MAJOR_VERSION=1 /DKMDF_MINOR_VERSION=9 /DKMDF_MAJOR_VERSION_STRING=01 /DKMDF_MINOR_VERSION_STRING=009 main.c
	lld-link main.obj /driver /base:0x10000 /subsystem:native /entry:FxDriverEntry@8 /safeseh:no /opt/wadk/wdf/lib/win7/i386/bufferoverflowk.lib /opt/wadk/wdf/lib/win7/i386/ntoskrnl.lib /opt/wadk/wdf/lib/win7/i386/hal.lib /opt/wadk/wdf/lib/win7/i386/wmilib.lib /opt/wadk/wdf/lib/win7/i386/netio.lib /opt/wadk/wdf/lib/win7/i386/uuid.lib /opt/wadk/wdf/lib/wdf/kmdf/i386/1.9/wdfldr.lib /opt/wadk/wdf/lib/wdf/kmdf/i386/1.9/wdfdriverentry.lib /out:main.sys
	python3 fix.py main.sys
	gcc server.c -o server

run:
	./server 127.0.0.1 9999 &
	genisoimage -o cdrom.iso * /opt/wadk/tools/devcon.exe
	myqemu win7

clean:
	rm -rf main.sys main.obj main.pdb app.obj app.pdb app.exe cdrom.iso server

all:
	uasm -coff -c -q -less -nomlib -FwNUL -Zi -Zd main.asm
	myx86 "c:\masm32\bin\link.exe" main.o /driver /base:0x10000 /subsystem:native /entry:DriverEntry "c:\masm32\lib\wxp\i386\ntoskrnl.lib" /out:main.sys

app:
	myx86 "c:\masm32\bin\ml.exe" /c /coff /Cp /Zi /Zd app.asm
	myx86 "c:\masm32\bin\link.exe" /subsystem:console /version:4.0 /incremental:no /out:app.exe app.obj

run:
	genisoimage -o cdrom.iso autorun.inf main.inf main.sys app.exe run.bat
	myqemu winxp

clean:
	rm -rf main.sys main.o app.obj app.exe cdrom.iso

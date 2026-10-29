TARGET = lesson01

all:
	myx86 "c:\masm32\bin\ml.exe" /c /coff $(TARGET).asm
	myx86 "c:\masm32\bin\link.exe" /SUBSYSTEM:WINDOWS /MACHINE:X86 $(TARGET).obj opengl32.lib glu32.lib gdi32.lib user32.lib kernel32.lib /OUT:$(TARGET).exe

run:
	myx86 $(TARGET).exe

clean:
	rm -rf $(TARGET).exe $(TARGET).obj

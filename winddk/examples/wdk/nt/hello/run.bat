call start /B c:\dbgview.exe
copy e:\main.sys c:\main.sys

c:\sleep.exe 10

for /l %%x in (1, 1, 3) do (
sc create MyDriver binPath= "c:\main.sys" type= "kernel" start= "demand" error= "normal" Displayname= "MyDriver"
sc start MyDriver

c:\sleep.exe 3

sc stop MyDriver
sc delete MyDriver
)

pause

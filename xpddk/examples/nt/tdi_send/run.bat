sc create MyDriver binPath= "d:\main.sys" type= "kernel" start= "demand" error= "normal" Displayname= "MyDriver"
sc start MyDriver
sc stop MyDriver
sc delete MyDriver

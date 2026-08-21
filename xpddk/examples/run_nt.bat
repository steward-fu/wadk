sc create MyDriver binPath= "e:\main.sys" type= "kernel" start= "demand" error= "normal" Displayname= "MyDriver"
sc start MyDriver
sc stop MyDriver
sc delete MyDriver

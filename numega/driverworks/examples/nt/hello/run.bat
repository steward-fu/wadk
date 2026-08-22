sc create MyDriver binPath= "e:\main.sys" type= "kernel" start= "demand" error= "normal" Displayname= "MyDriver"
sc start MyDriver
sleep 3
sc stop MyDriver
sc delete MyDriver

@echo off
set path=d:\msvc10\bin\x86_amd64;d:\msvc10\bin;%path%
set include=d:\msvc10\include;d:\mssdk2009\include
cl -c -Fo%164.obj %1.c
link %164.obj /SUBSYSTEM:console /libpath:d:\msvc10\lib\amd64 /libpath:d:\mssdk2009\lib\x64 /MAP

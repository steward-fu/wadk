rem windres --preprocessor fprcp -v -i my.rc -o my.res
fpc -va  OPT="-gl -Xs -WC" -Twin32 -Pi386 -FE.\exe\ wcetemu.pp >i386-win32.log
pause


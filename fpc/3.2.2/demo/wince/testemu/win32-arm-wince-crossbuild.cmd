rem windres --preprocessor fprcp -v -i my.rc -o my.res
fpc -va  OPT="-gl -Xs -WC" -Twince -Parm -XParm-wince-pe- -FDd:\rscdx\reflaz\pp\binarmwince -FE.\exe\ wcetrun.pp >arm-wince.log
pause


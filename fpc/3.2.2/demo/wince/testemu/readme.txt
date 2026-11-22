TOOLS FOR RUNNING TEST SUITE FOR ARM-WINCE
==========================================


standard way for using test suite is native, rshd, sshd or equivalent runing on the target system,
nothing was available on wince except telnetd from ms samples. both xp telnet client and putty/plink
have been unsuccessugflly tested with this telenetd (also connection was randomly done)
no doubt that these 2 programs wcetrun and wcetemu will be deprecated when a reliable rshd is running on 
arm-wince targets and full pascal written ! they'll became only RAPI demo programs.

wcetemu.exe : do the following things
-----------
1. copy via the RAPI anytest.exe cross compiled exe program on the targ arm-wince system.
2. run via the RAPI the following commad line : 'wcetrun mytest.exe'
3. loop trying to delete mytest.exe file until delete can be done ie. test finished (waitforsingleobject is not available via the rapi)
4. read a small file containing the exitcode from target system

building : see win32-i386-win32-build.cmd

wcetrun.exe : do the following things
-----------
1.run the exefile passed as parameter
2.wait the program finished
3.get exitcode and write a small file containing it

building : see win32-arm-wince-crossbuild.cmd
           binutils for arm-wince will be required (cf wince wiki)

environment
-----------

* tested on an XScale and under arm emulator both running PPC2003SE (wince4.21) 
* console program should be installed, tested with PocketCMD/PocketConsole (cf wince wiki)
* ActiveSync is required for the RAPI, tested with v4.1
* host PC windowsXP SP2



for running the testsuite :

make TEST_FPC=ppcrossarm TEST_CPU_TARGET=arm TEST_OS_TARGET=wince TEST_OPT="-XParm-wince-pe- -WC" TEST_REMOTEPATH=\fpctests EMULATOR=MyDisc:\My\Path\to\wcetemu.exe 

see also fpsrc\tests\readme.txt


Any comment (improvement) can be sent to : fpc-devel@lists.freepascal.org or orinaudo@gmail.com


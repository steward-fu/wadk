
 A. About WinInc

   WinInc is a set of assembly include files in Masm-syntax to create Win32
   and Win64 applications and dlls. Furthermore, there are module definition 
   files supplied to create the standard Win32 and Win64 import libraries.

   Some samples in the SAMPLES directory illustrate how to use WinInc.


 B. Requirements

   a) Win32

   Assemblers which are able to digest the WinInc include files are

    - MASM
    - JWASM (http://www.japheth.de/JWasm.html)
    - POASM (partially)

   which gives a quite large range of possible tool chains for Windows
   development in MASM-like assembly:

   - include files:   WinInc
   - assembler:       UASM,    MS MASM  or  POASM
   - linker:          (J)WLINK,MS LINK  or  POLINK
   - resource comp:   WRC,     MS RC    or  PORC
   - librarian [opt]: WLIB,    MS LIB   or  POLIB

   WLINK, WRC and WLIB are included in Open Watcom. POASM, POLINK, PORC
   and POLIB are included in PellesC. Both Open Watcom and PellesC are
   free. JWLINK is a port of Open Watcom's WLINK, that supports 64-bit
   Windows binaries.

   b) Win64

   For Win64 development, the set of tools is significantly smaller,
   because:
   - OW tools WLINK, WLIB and WRC won't work for 64bit.
   - 64-bit Masm (ML64.EXE) has severe limitations.

   The MS and Pelles tools "know" 64-bit, but one must ensure not to
   use too old versions of these tools. The MS tools must have reached
   version number 7 at least, the Pelles tools must be version 5 or
   higher. JWasm must be v2.0 or higher.


 C. Installation

   When creating binaries for Windows the link step will require import
   libraries to resolve the references to the Windows API. One may just use
   the libraries included in the MS PSDK, then the following steps can be
   skipped.

   a) Create Standard Windows Import Libs

   The standard Windows libraries are so-called import libraries. Import
   libraries contain just references to the dlls where the functions are
   to be found. Some tools can create those libraries from simple text files.
   WLib - included in Open Watcom - is able to do it, and also POLIB -
   included in Pelles C. While WLib needs the text to be in a unique format,
   POLIB is able to understand so-called module-definition files ( file 
   extension .DEF ). That's why WinInc uses POLIB to create the most common
   Windows libraries.

   For Win32, run MAKELIBS.BAT in directory DEF.
   For Win64, run MAKELIBS.BAT in directory DEF64.

   b) Create UUID.LIB

   Regretably not all Windows libraries are just import libraries which can 
   be created by POLIB. Some contain static code. One of those - which is
   crucial for COM - is UUID.LIB. The file UUID.LIB contained in Lib subdir
   is not a fully functional version of this lib. It is created by tool
   UUID\mkguids.exe and contains just the very minimum of GUIDs. If you need
   additional GUIDs in your binary, either get a version of UUID.LIB from
   other sources (PSDK for example) or add the missing GUIDS to file
   UUID\uuid and rerun UUID\makeuuid.bat.

   Thanks to Vortex and his LIB2DEF utility, which has been used to
   create the .DEF files!


 D. License

  All files contained in WinInc are Public Domain. The 'copyright'
  string in the include files refers to tool h2incx, not to the 
  include files themselves.

  Japheth


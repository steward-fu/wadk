!IF 0

Copyright (c) Microsoft Corporation

Module Name:

    i386mk.inc

Abstract:

        This module contains the x86 specific build controls.  It is included
        by makefile.def.

Revision History:

!ENDIF

#
# x86 option control
#
UMBASE=$(UMBASE:*=i386)
UMLIBS=$(UMLIBS:*=i386)
NTRES=$(NTRES:*=i386)
UMRES=$(UMRES:*=i386)
UMOBJS=$(UMOBJS:*=i386)
CRTLIBS=$(CRTLIBS:*=i386)
LINKLIBS=$(LINKLIBS:*=i386)
GDI_DRIVER_LIBS=$(GDI_DRIVER_LIBS:*=i386)
DLLBASE=$(DLLBASE:*=i386)
DLLDEF=$(DLLDEF:*=i386)
MACHINE_TARGETLIBS=$(MACHINE_TARGETLIBS:*=i386)
!ifdef USE_MSHTML_PDB_RULES
MACHINE_TARGETLIBS=$(MACHINE_TARGETLIBS:????????=*)
!endif
TARGET=$(TARGET:*=i386)
DYNLINK_LIB=$(DYNLINK_LIB:*=i386)
TARGETEXEFILES=$(TARGETEXEFILES:*=i386)
TARGETLIBFILES=$(TARGETLIBFILES:*=i386)
TARGETOBJFILES=$(TARGETOBJFILES:*=i386)
UMOBJFILES=$(UMOBJFILES:*=i386)
UMEXEFILES=$(UMEXEFILES:*=i386)
HEADERFILE=$(HEADERFILE:*=i386)
HEADEROBJNAME=$(HEADEROBJNAME:*=i386)
HEADEROBJ=$(HEADEROBJ:*=i386)
PRECOMPILED=$(PRECOMPILED:*=i386)
PRECOMPILED_CXX=$(PRECOMPILED_CXX:*=i386)
PRECOMPILED_TARGET=$(PRECOMPILED_TARGET:*=i386)
MFC_STATIC_LIB=$(MFC_STATIC_LIB:*=i386)
CRT_LIB_PATH=$(CRT_LIB_PATH:*=i386)
SDK_LIB_PATH=$(SDK_LIB_PATH:*=i386)
DDK_LIB_PATH=$(DDK_LIB_PATH:*=i386)
IFSKIT_LIB_PATH=$(IFSKIT_LIB_PATH:*=i386)
HALKIT_LIB_PATH=$(HALKIT_LIB_PATH:*=i386)
ORDER=$(ORDER:*=i386)
OBJLIBFILES=$(OBJLIBFILES:*=i386)
MISCFILES=$(MISCFILES) $(I386_MISCFILES)
!if defined(I386_DRIVER_INFS)
DRIVER_INFS=$(DRIVER_INFS) $(I386_DRIVER_INFS)
!endif
!if defined(I386_MANIFESTED_INFS)
MANIFESTED_INFS=$(MANIFESTED_INFS) $(I386_MANIFESTED_INFS)
!endif
!if defined(I386_PRINTER_INFS)
PRINTER_INFS=$(PRINTER_INFS) $(I386_PRINTER_INFS)
!endif
!if defined(I386_MANIFESTED_PRINTER_INFS)
MANIFESTED_PRINTER_INFS=$(MANIFESTED_PRINTER_INFS) $(I386_MANIFESTED_PRINTER_INFS)
!endif
!if defined(I386_NON_PNP_INFS)
NON_PNP_INFS=$(NON_PNP_INFS) $(I386_NON_PNP_INFS)
!endif
!if defined(I386_NON_PNP_SIGN_INFS)
NON_PNP_SIGN_INFS=$(NON_PNP_SIGN_INFS) $(I386_NON_PNP_SIGN_INFS)
!endif
!if defined(I386_LOC_DRIVER_INFS)
LOC_DRIVER_INFS=$(LOC_DRIVER_INFS) $(I386_LOC_DRIVER_INFS)
!endif
!if defined(I386_LOC_MANIFESTED_INFS)
LOC_MANIFESTED_INFS=$(LOC_MANIFESTED_INFS) $(I386_LOC_MANIFESTED_INFS)
!endif
!if defined(I386_LOC_PRINTER_INFS)
LOC_PRINTER_INFS=$(LOC_PRINTER_INFS) $(I386_LOC_PRINTER_INFS)
!endif
!if defined(I386_LOC_MANIFESTED_PRINTER_INFS)
LOC_MANIFESTED_PRINTER_INFS=$(LOC_MANIFESTED_PRINTER_INFS) $(I386_LOC_MANIFESTED_PRINTER_INFS)
!endif
!if defined(I386_LOC_NON_PNP_INFS)
LOC_NON_PNP_INFS=$(LOC_NON_PNP_INFS) $(I386_LOC_NON_PNP_INFS)
!endif
!if defined(I386_LOC_NON_PNP_SIGN_INFS)
LOC_NON_PNP_SIGN_INFS=$(LOC_NON_PNP_SIGN_INFS) $(I386_LOC_NON_PNP_SIGN_INFS)
!endif
SOURCES=$(SOURCES) $(I386_SOURCES)

ATL_STATIC_LIBS = $(ATL_STATIC_LIBS) $(ATL_LIB_PATH)\atlthunk.lib

!IF "$(TARGETTYPE)"=="GDI_DRIVER" || \
    "$(TARGETTYPE)"=="MINIPORT"
#
#Drivers don't link with link libs.
#
MACHINE_TARGETLIBS=$(SDK_LIB_PATH)\int64.lib $(MACHINE_TARGETLIBS)
!ELSE
!IF defined(USE_NTDLL) || defined (USE_NOLIBS)
MACHINE_TARGETLIBS=$(SDK_LIB_PATH)\int64.lib $(MACHINE_TARGETLIBS)
!ENDIF
!ENDIF

!ifdef NTTARGETFILES
NTTARGETFILES=$(NTTARGETFILES:*=i386)
!endif
!ifdef NTTARGETFILE0
NTTARGETFILE0=$(NTTARGETFILE0:*=i386)
!endif
!ifdef NTTARGETFILE1
NTTARGETFILE1=$(NTTARGETFILE1:*=i386)
!endif

!ifdef PROJECT_LIB_PATH
PROJECT_LIB_PATH=$(PROJECT_LIB_PATH:*=i386)
!endif

!IF "$(DLLENTRY)" != "/noentry" && "$(DLLENTRY)" != "-noentry"
!   IF "$(DLLENTRY:@12=)" == "$(DLLENTRY)"
DLLENTRY=$(DLLENTRY)@12
!   ENDIF
!ENDIF

!IFDEF STD_CALL_ENTRY
UMENTRY=$(UMENTRY)@4
!ENDIF

ENTRY_SUFFIX=@8
GDI_ENTRY_SUFFIX=@12

DEFAULT_STACKRESERVE=0x40000
DEFAULT_STACKCOMMIT=0x2000

!IFDEF 386_WARNING_LEVEL
MSC_WARNING_LEVEL=$(386_WARNING_LEVEL)
!ENDIF

MSC_WARNING_LEVEL=$(MSC_WARNING_LEVEL) $(COMPILER_WX_SWITCH)

!ifdef 386_PERFFLAGS
PERFFLAGS = $(386_PERFFLAGS)
!endif

# Set MSC_OPTIMIZATION.
# Order of precedence:
#   Platform specific override
#   Environment variable
#   System Default

!ifdef 386_OPTIMIZATION
MSC_OPTIMIZATION=$(386_OPTIMIZATION)
!elseif !defined(MSC_OPTIMIZATION)
MSC_OPTIMIZATION=$(DEFAULT_MSC_OPT)
!endif

LINK_TIME_CODE_GENERATION_MSC_FLAG=
!if defined(LINK_TIME_CODE_GENERATION) && !defined(FORCENATIVEOBJECT)
# Some objects must be built native, so turn off GL for those
LINK_TIME_CODE_GENERATION_MSC_FLAG=/GL
!endif

DBGFLAGS=$(DBGFLAGS) $(MSC_OPTIMIZATION) $(LINK_TIME_CODE_GENERATION_MSC_FLAG)

!IFDEF 386_CPPFLAGS
MSC_CPPFLAGS=$(386_CPPFLAGS)
!ENDIF

!ifdef NTCPPFLAGS
!error NTCPPFLAGS is deprecated.
!endif

!ifdef NO_STRING_POOLING
STRING_POOLING =
!else
!ifdef NO_READONLY_STRINGS
STRING_POOLING = /Gf
!else
STRING_POOLING = /GF
!endif
!endif

!ifdef USE_NATIVE_EH
! if "$(USE_NATIVE_EH)" == "ASYNC"
EH_FLAGS=/EHa
! else
!  if "$(USE_NATIVE_EH)" == "CTHROW"
EH_FLAGS=/EHsc-
!  else
EH_FLAGS=/EHsc
!  endif
! endif
!else
EH_FLAGS=/EHs-c-
!endif

!if defined(USE_RTTI) || (defined(MANAGED_CXX) && "$(URT_VER)" != "1.1")
RTTI_FLAGS=/GR
!else
RTTI_FLAGS=/GR-
!endif

# On by default
!if "$(BUFFER_OVERFLOW_CHECKS)" == ""
BUFFER_OVERFLOW_CHECKS=1
!endif

# Turn off for the select few
!if ("$(DRIVERTYPE)" == "VXD") || \
    (("$(TARGETTYPE)" == "MINIPORT") && ($(_NT_TARGET_VERSION) < 0x502)) || \
    (("$(TARGETTYPE)" == "DYNLINK") && defined(RESOURCE_ONLY_DLL)) || \
    "$(BUFFER_OVERFLOW_CHECKS)" == "0"
!undef BUFFER_OVERFLOW_CHECKS
!endif

!if defined(BUFFER_OVERFLOW_CHECKS)
# verify it's one of the chosen few - 1, NTDLL or compile only - all others are wrong.
! if "$(BUFFER_OVERFLOW_CHECKS)" != "1" && \
     "$(BUFFER_OVERFLOW_CHECKS)" != "NTDLL" && \
     "$(BUFFER_OVERFLOW_CHECKS)" != "COMPILE_ONLY" && \
     "$(BUFFER_OVERFLOW_CHECKS)" != "LINK_ONLY"
!  error INVALID BUFFER_OVERFLOW_CHECKS value "$(BUFFER_OVERFLOW_CHECKS)" in $(MAKEDIR)
! endif
! if "$(BUFFER_OVERFLOW_CHECKS)" == "LINK_ONLY"
BO_FLAGS=/GS-
BUFFER_OVERFLOW_CHECKS=1
! else
BO_FLAGS=/GS
! endif
! if "$(BUFFER_OVERFLOW_CHECKS)" == "1"
!  if "$(TARGETTYPE)" == "DRIVER" || \
      "$(TARGETTYPE)" == "EXPORT_DRIVER" || \
      "$(TARGETTYPE)" == "DRIVER_LIBRARY" || \
      "$(TARGETTYPE)" == "MINIPORT" 
BO_LIB=$(SDK_LIB_PATH)\BufferOverflowK.lib
DRIVER_ENTRY=GsDriverEntry
!  elseif "$(TARGETTYPE)" == "GDI_DRIVER"
BO_LIB=$(SDK_LIB_PATH)\BufferOverflowGDI.lib
GDI_DRIVER_ENTRY=GsDrvEnableDriver
!  elseif "$(TARGETTYPE)" == "DYNLINK"
!   if !(("$(UMTYPE)"== "nt") || ("$(UMTYPE)"=="ntss"))
!    if ("$(DLLENTRY)" == "/noentry" || "$(DLLENTRY)" == "-noentry")
!     if defined(USE_MSVCRT) || defined(USE_LIBCMT)
DLLENTRY=-entry:_DllMainCRTStartup@12
!     else
DLLENTRY=-entry:_DllMainCRTStartupForGS@12
!     endif
!    endif
!    if !defined(USE_MSVCRT) && !defined(USE_LIBCMT)
BO_LIB=$(SDK_LIB_PATH)\BufferOverflowU.lib
!    endif
!   endif
!  else	# TARGETTYPE == PROGRAM/LIBRARY/NOTARGET with special build rules
!   if ("$(UMTYPE)"== "nt") || ("$(UMTYPE)"=="ntss")
!    if defined(NTKERNEL)
BO_LIB=$(SDK_LIB_PATH)\BufferOverflowK.lib
!    else
BO_LIB=$(SDK_LIB_PATH)\BufferOverflow.lib
!    endif
!   else
!    if !defined(USE_MSVCRT) && !defined(USE_LIBCMT)
BO_LIB=$(SDK_LIB_PATH)\BufferOverflowU.lib
!    endif
!   endif
!  endif
! elseif "$(BUFFER_OVERFLOW_CHECKS)" == "NTDLL"
BO_LIB=$(SDK_LIB_PATH)\BufferOverflow.lib
!  if ("$(TARGETTYPE)" == "DYNLINK") && \
      ("$(DLLENTRY)" == "/noentry" || "$(DLLENTRY)" == "-noentry") && \
      ("$(TARGETNAME)" != "ntdll")
DLLENTRY=-entry:_DllMainCRTStartupForGS@12
!  endif
! endif
!endif  # Overflow checks

!ifndef X86_CPU_OPTIMIZATION
X86_CPU_OPTIMIZATION=/G6
!endif

# Undocumented switch definitions
ERATTA_FLAGS=

# Hotpatch support
ERATTA_FLAGS=$(ERATTA_FLAGS) /hotpatch
LINKER_FLAGS=$(LINKER_FLAGS) /functionpadmin:5
!ifndef NO_SAFESEH
LINKER_FLAGS=$(LINKER_FLAGS) /safeseh
!endif


!if defined(386_STRUCT_PACKING)
MSC_STRUCT_PACKING=$(386_STRUCT_PACKING)
!elseif !defined(MSC_STRUCT_PACKING)
MSC_STRUCT_PACKING=/Zp8
!endif

# Due to different compilers in the nt tree (older VC++ as well intel compiler)
# interpreting the /Zc:wchar_t- switch as /Zc /Z: /Zw /Zc /Zh /Za ...
# creating a variable to disable /Zc:wchar_t- for the problematic directory
!ifndef NO_WCHAR_T
COMPILER_WCHAR_T=/Zc:wchar_t-
!else
COMPILER_WCHAR_T=
!endif

# Another wchar_t fix, don't want to use any wchar_t flags
# if it's managed and version 1.1 code.
!if "$(URT_VER)" == "1.1" && defined(MANAGED_CXX)
COMPILER_WCHAR_T=
!endif

STDFLAGS= /c $(COMPILER_WCHAR_T) /Zl $(MSC_STRUCT_PACKING) /Gy /Gm- $(CBSTRING) $(MSC_WARNING_LEVEL) $(MSC_CALL_TYPE) \
          $(ERATTA_FLAGS) $(EH_FLAGS) \
          $(RTTI_FLAGS) $(STRING_POOLING) $(BO_FLAGS)

!IF "$(MCPP_TYPE)" == "pure" || "$(MCPP_TYPE)" == "safe"
MSC_CALL_TYPE=
MSC_CALL_DEFINE=
!ELSE
!IF "$(386_STDCALL)" == "0"
MSC_CALL_TYPE=/Gd
MSC_CALL_DEFINE=
!ELSE
!   IF "$(386_STDCALL)" == "2"
MSC_CALL_TYPE=/Gr
MSC_CALL_DEFINE=
!   ELSE
MSC_CALL_TYPE=/Gz
MSC_CALL_DEFINE=/DSTD_CALL
!   ENDIF
!ENDIF
!ENDIF

!IF $(FREEBUILD)
ASM_DBG_DEFINES=/DDBG=0
!ENDIF

TARGET_DBG_DEFINES= $(TARGET_DBG_DEFINES) /DFPO=0
DBGFLAGS=$(DBGFLAGS) /Oy-

DBGFLAGS=$(DBGFLAGS) /Zi
386_ADBGFLAGS=$(386_ADBGFLAGS) /Zi

!if !defined(USE_PDB_TO_COMPILE) || "$(USE_PDB_TO_COMPILE)" == "0" # { {
DBGFLAGS=$(DBGFLAGS:/Zi=/Z7)
DBGFLAGS=$(DBGFLAGS:-Zi=/Z7)
!else # } {
USER_C_FLAGS=$(USER_C_FLAGS:/Z7=/Zi)
USER_C_FLAGS=$(USER_C_FLAGS:-Z7=/Zi)
! ifndef USE_MSHTML_PDB_RULES # { {
!  if "$(TARGETTYPE)" == "LIBRARY" # { {
DBGFLAGS=$(DBGFLAGS) /Fd$(TARGETPATH)\$(TARGET_DIRECTORY)\$(TARGETNAME).pdb
!  else # } {
DBGFLAGS=$(DBGFLAGS) /Fd$(OBJ_PATH)\$O^\
!  endif # } }
! else # } {
!  ifndef TARGETPDB # { {
TARGETPDB=$(TARGETNAME)
!  endif # } }
DBGFLAGS=$(DBGFLAGS) /Fd$(OBJ_PATH)\$O\$(TARGETPDB).pdb
! endif # } }
!endif # } }

!ifndef NO_BROWSER_INFO
! ifdef BROWSER_INFO
DBGFLAGS=$(DBGFLAGS) /FR$(OBJ_PATH)\$O^\
! endif
!endif

#
# 386 option control
#

!IF "$(HALTYPE)" == ""
HALDEF=
!ELSE
HALDEF=/D$(HALTYPE)=1
!ENDIF

STD_DEFINES= /D_X86_=1 /Di386=1 $(HALDEF) $(MSC_CALL_DEFINE) $(STD_DEFINES)

CDEFINES=$(STD_DEFINES) $(TARGET_DBG_DEFINES) \
              $(LIBC_DEFINES) $(C_DEFINES) $(NET_C_DEFINES) $(MFC_DEFINES)
CFLAGS=$(386_FLAGS) $(NT386FLAGS) $(STDFLAGS) $(DBGFLAGS) $(PERFFLAGS) $(USER_C_FLAGS) /wd4603 /wd4627

!if "$(URT_VER)" != "1.1"
CFLAGS=$(CFLAGS) /typedil-
!endif

386_ASMFLAGS=$(386_ADBGFLAGS) $(STD_DEFINES) $(ASM_DBG_DEFINES)\
              $(TARGET_DBG_DEFINES) $(ASM_DEFINES)

386_CDEFINES=$(CDEFINES)
386_CFLAGS=$(CFLAGS)

!if defined(SUBSTITUTE_386_CC_MANAGED) && defined(MANAGED_CXX)
CC_NAME=$(SUBSTITUTE_386_CC_MANAGED) 
!elseif defined(SUBSTITUTE_386_CC) && !defined(MANAGED_CXX)
CC_NAME=$(SUBSTITUTE_386_CC) 
!elseif !defined(CC_NAME)
CC_NAME=cl
!endif

C_COMPILER_NAME     = $(CC_NAME)
CXX_COMPILER_NAME   = $(CC_NAME)
C_PREPROCESSOR_NAME = $(CC_NAME)

!ifndef 386_ASSEMBLER_NAME
386_ASSEMBLER_NAME  = ml /safeseh
!endif

GLOBAL_C_FLAGS = /Ii386 /I. $(INCPATH1) $(CDEFINES) $(CFLAGS)

GLOBAL_C_FLAGS=$(CRT_BUILD_FLAGS) $(GLOBAL_C_FLAGS)

NP_COMPILER_FLAGS = $(GLOBAL_C_FLAGS) $(COMPILER_WARNINGS)

CXX_COMPILER_FLAGS_NOPCH = $(NP_COMPILER_FLAGS) $(MSC_CPPFLAGS) $(NTCPPFLAGS) $(MANAGED_CXX_FLAGS)
C_COMPILER_FLAGS_NOPCH = $(NP_COMPILER_FLAGS)
C_COMPILER_FLAGS = $(C_COMPILER_FLAGS_NOPCH) $(PRECOMPILED)
CXX_COMPILER_FLAGS = $(CXX_COMPILER_FLAGS_NOPCH) $(PRECOMPILED_CXX)
C_PREPROCESSOR_FLAGS = $(GLOBAL_C_FLAGS) /EP /Tc

C_PREPROCESSOR = $(C_PREPROCESSOR_NAME) $(C_PREPROCESSOR_FLAGS)
C_COMPILER     = $(C_COMPILER_NAME) $(C_COMPILER_FLAGS)
NP_C_COMPILER  = $(C_COMPILER_NAME) $(NP_COMPILER_FLAGS)
CXX_COMPILER   = $(CXX_COMPILER_NAME) $(CXX_COMPILER_FLAGS)

!if defined(NOMASMCOMPATIBILITY)
386_ASSEMBLER=$(386_ASSEMBLER_NAME) /c /coff /Cx /nologo /Ii386\ /I. $(INCPATH1) $(386_ASMFLAGS)
!else
386_ASSEMBLER=$(386_ASSEMBLER_NAME) /c /coff /Cx /nologo /Ii386\ /I. $(INCPATH1) /Zm $(386_ASMFLAGS)
!endif

ECHO_MSG=$(C_COMPILER) $<
ECHO_MSG_P=$(NP_C_COMPILER) $**
ECHO_CXX_MSG=$(CXX_COMPILER) $<

ECHO_PRECOMPILED_MSG1=$(C_COMPILER_NAME) $(C_COMPILER_FLAGS) /Yl$(TARGETNAME) /Yc$(?F) $(HEADERFILE) \
               $(HEADEROBJ) $(PRECOMPILED_FLAG) $(PRECOMPILED_SOURCEFILE)
	
ECHO_PRECOMPILED_MSG2=$(C_COMPILER_NAME) $(C_COMPILER_FLAGS) /Yl$(TARGETNAME) /Yc$(?F) $(HEADERFILE) \
               $(HEADEROBJ) $(PRECOMPILED_FLAG)

{}.c{}.asm:
    $(C_COMPILER_NAME) @<< /Fa $<
$(C_COMPILER_FLAGS: =
)
$(C_COMPILER_FLAGS:##= )
<<NOKEEP

{..\i386}.asm{}.lst:
    $(386_ASSEMBLER) /Fl$@ /Fo$@.obj $<

{i386}.asm{}.lst:
    $(386_ASSEMBLER) /Fl$@ /Fo$@.obj $<

{..\i386}.asm{$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

{$O}.asm{$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

{i386}.asm{$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

{..\i386}.asm{$(OBJ_PATH)\$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

{$(OBJ_PATH)\$O}.asm{$(OBJ_PATH)\$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

{i386}.asm{$(OBJ_PATH)\$O}.obj:
    $(386_ASSEMBLER) /Fo$@ $<

!IF "$(NTDEBUGTYPE)" == "windbg" || "$(NTDEBUGTYPE)" == "both"
NTKERNEL_LINK_OPTIONS=/entry:KiSystemStartup@4
!ELSE
NTKERNEL_LINK_OPTIONS=/base:0x80100000 /entry:KiSystemStartup@4
!ENDIF

!if "$(TARGETTYPE)" != "DRIVER"         && \
    "$(TARGETTYPE)" != "DRIVER_LIBRARY" && \
    "$(TARGETTYPE)" != "EXPORT_DRIVER"  && \
    "$(TARGETTYPE)" != "HAL"            && \
    "$(TARGETTYPE)" != "GDI_DRIVER"     && \
    "$(TARGETTYPE)" != "MINIPORT"
! if $(_NT_TOOLS_VERSION) >= 0x800 && \
     (!defined(NTKERNEL)) && \
     ("$(UMTYPE)" != "posix")
!  ifdef NO_NXCOMPAT
LINKER_FLAGS=$(LINKER_FLAGS) /nxcompat:no
MANAGED_NXCOMPAT_CMD=
!  else
LINKER_FLAGS=$(LINKER_FLAGS) /nxcompat
#MANAGED_NXCOMPAT_CMD=link /edit /nologo /nxcompat $@
MANAGED_NXCOMPAT_CMD=
!  endif
! endif
!endif

# SEH support for libs built with an older compiler
!ifdef _NT_TARGET_VERSION
!    if $(_NT_TARGET_VERSION) < 0x600 && $(_NT_TOOLS_VERSION) >= 0x700
TARGETLIBS=$(TARGETLIBS) $(DDK_LIB_PATH)\sehupd.lib
!    endif
!endif

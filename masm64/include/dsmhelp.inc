extern __imp_AddEquation:PANYARGS
AddEquation TEXTEQU <__imp_AddEquation>
extern __imp_AddEquationEx:PANYARGS
AddEquationEx TEXTEQU <__imp_AddEquationEx>
extern __imp_AddNumbers:PANYARGS
AddNumbers TEXTEQU <__imp_AddNumbers>
extern __imp_AndNumbers:PANYARGS
AndNumbers TEXTEQU <__imp_AndNumbers>
extern __imp_Assemble:PANYARGS
Assemble TEXTEQU <__imp_Assemble>
extern __imp_AssembleEx:PANYARGS
AssembleEx TEXTEQU <__imp_AssembleEx>
extern __imp_AssignDataBase:PANYARGS
AssignDataBase TEXTEQU <__imp_AssignDataBase>
extern __imp_AssignDataBaseByHandle:PANYARGS
AssignDataBaseByHandle TEXTEQU <__imp_AssignDataBaseByHandle>
extern __imp_CmpNumbers:PANYARGS
CmpNumbers TEXTEQU <__imp_CmpNumbers>
extern __imp_DelEquation:PANYARGS
DelEquation TEXTEQU <__imp_DelEquation>
extern __imp_Disassemble:PANYARGS
Disassemble TEXTEQU <__imp_Disassemble>
extern __imp_DivNumbers:PANYARGS
DivNumbers TEXTEQU <__imp_DivNumbers>
extern __imp_DsmVersion:PANYARGS
DsmVersion TEXTEQU <__imp_DsmVersion>
extern __imp_EvalExpr128:PANYARGS
EvalExpr128 TEXTEQU <__imp_EvalExpr128>
extern __imp_EvalExpr256:PANYARGS
EvalExpr256 TEXTEQU <__imp_EvalExpr256>
extern __imp_FreeInstr:PANYARGS
FreeInstr TEXTEQU <__imp_FreeInstr>
extern __imp_GetControlFlags:PANYARGS
GetControlFlags TEXTEQU <__imp_GetControlFlags>
extern __imp_GetExceptTextNote:PANYARGS
GetExceptTextNote TEXTEQU <__imp_GetExceptTextNote>
extern __imp_GetExceptions:PANYARGS
GetExceptions TEXTEQU <__imp_GetExceptions>
extern __imp_GetInterruptProps:PANYARGS
GetInterruptProps TEXTEQU <__imp_GetInterruptProps>
extern __imp_GetLatency:PANYARGS
GetLatency TEXTEQU <__imp_GetLatency>
extern __imp_GetMediaExceptionProps:PANYARGS
GetMediaExceptionProps TEXTEQU <__imp_GetMediaExceptionProps>
extern __imp_GetPfxMeaning:PANYARGS
GetPfxMeaning TEXTEQU <__imp_GetPfxMeaning>
extern __imp_GetX87ExceptionProps:PANYARGS
GetX87ExceptionProps TEXTEQU <__imp_GetX87ExceptionProps>
extern __imp_InitInstr:PANYARGS
InitInstr TEXTEQU <__imp_InitInstr>
extern __imp_InitInstrEx:PANYARGS
InitInstrEx TEXTEQU <__imp_InitInstrEx>
extern __imp_InstrDasm:PANYARGS
InstrDasm TEXTEQU <__imp_InstrDasm>
extern __imp_InstrEF:PANYARGS
InstrEF TEXTEQU <__imp_InstrEF>
extern __imp_IntToStr:PANYARGS
IntToStr TEXTEQU <__imp_IntToStr>
extern __imp_IsDFCondition:PANYARGS
IsDFCondition TEXTEQU <__imp_IsDFCondition>
extern __imp_JoinMnemonic:PANYARGS
JoinMnemonic TEXTEQU <__imp_JoinMnemonic>
extern __imp_LastInstrLength:PANYARGS
LastInstrLength TEXTEQU <__imp_LastInstrLength>
extern __imp_LatToStr:PANYARGS
LatToStr TEXTEQU <__imp_LatToStr>
extern __imp_MulNumbers:PANYARGS
MulNumbers TEXTEQU <__imp_MulNumbers>
extern __imp_NegateNumber:PANYARGS
NegateNumber TEXTEQU <__imp_NegateNumber>
extern __imp_NotNumber:PANYARGS
NotNumber TEXTEQU <__imp_NotNumber>
extern __imp_OrNumbers:PANYARGS
OrNumbers TEXTEQU <__imp_OrNumbers>
extern __imp_ParseSource:PANYARGS
ParseSource TEXTEQU <__imp_ParseSource>
extern __imp_ParseSourceEx:PANYARGS
ParseSourceEx TEXTEQU <__imp_ParseSourceEx>
extern __imp_ReinitInstr:PANYARGS
ReinitInstr TEXTEQU <__imp_ReinitInstr>
extern __imp_SelectValidLabelOrNumber:PANYARGS
SelectValidLabelOrNumber TEXTEQU <__imp_SelectValidLabelOrNumber>
extern __imp_SetArch:PANYARGS
SetArch TEXTEQU <__imp_SetArch>
extern __imp_SetBMI1:PANYARGS
SetBMI1 TEXTEQU <__imp_SetBMI1>
extern __imp_SetCPointer:PANYARGS
SetCPointer TEXTEQU <__imp_SetCPointer>
extern __imp_SetCPointerEx:PANYARGS
SetCPointerEx TEXTEQU <__imp_SetCPointerEx>
extern __imp_SetControlFlags:PANYARGS
SetControlFlags TEXTEQU <__imp_SetControlFlags>
extern __imp_SetLoadall:PANYARGS
SetLoadall TEXTEQU <__imp_SetLoadall>
extern __imp_SetLzcnt:PANYARGS
SetLzcnt TEXTEQU <__imp_SetLzcnt>
extern __imp_SetMode:PANYARGS
SetMode TEXTEQU <__imp_SetMode>
extern __imp_SetPopCs:PANYARGS
SetPopCs TEXTEQU <__imp_SetPopCs>
extern __imp_ShlNumber:PANYARGS
ShlNumber TEXTEQU <__imp_ShlNumber>
extern __imp_ShrNumber:PANYARGS
ShrNumber TEXTEQU <__imp_ShrNumber>
extern __imp_SrcAssemble:PANYARGS
SrcAssemble TEXTEQU <__imp_SrcAssemble>
extern __imp_StrToInt:PANYARGS
StrToInt TEXTEQU <__imp_StrToInt>
extern __imp_SubNumbers:PANYARGS
SubNumbers TEXTEQU <__imp_SubNumbers>
extern __imp_XorNumbers:PANYARGS
XorNumbers TEXTEQU <__imp_XorNumbers>

SymCallbackProto TYPEDEF PROTO lpVoid:LPVOID,IntVal:PVOID,dwFlags:DWORD,UndefinedSymbol:LPSTR,SymLength:PULONG
SYM_CALLBACK TYPEDEF PTR SymCallbackProto
Expression struc
	ExprLine		LPSTR ?
	ExprLength		DWORD 0
	NestingLevel	DWORD 0
	SymCallback		SYM_CALLBACK 0
	lpVoid			LPVOID 0
Expression ends
PEXPRESSION TYPEDEF PTR Expression
EF STRUC
	ID		BYTE ?	;21
	VIP		BYTE ?	;20
	VIF		BYTE ?	;19
	AC		BYTE ?	;18
	VM		BYTE ?	;17
	RF		BYTE ?	;16
	NT		BYTE ?	;14
	IOPL	BYTE ?	;13-12
	_OF		BYTE ?	;11
	_DF		BYTE ?	;10
	_IF		BYTE ?	;9
	TF		BYTE ?	;8
	SF		BYTE ?	;7
	ZF		BYTE ?	;6
	AF		BYTE ?	;4
	PF		BYTE ?	;2
	CF		BYTE ?	;0
EF ENDS
x87c struc
	C0	BYTE ?
	C1	BYTE ?
	C2	BYTE ?
	C3	BYTE ?
	dC0	BYTE ?
	dC1	BYTE ?
	dC2	BYTE ?
	dC3	BYTE ?
x87c ends
NA equ 0
_0 equ 1
_1 equ 2
U equ 3
_Mod equ 4
TMod equ 5
_Pop equ 6
TPop equ 7
Tst equ 8
lAH equ 9
VMS0 equ 10
VMIN equ 11
VMEN equ 12
;x87 conditions descriptions
lmem equ 1   ;Loaded from memory.
_rng equ 2
;0 Source operand was in range.
;1 Source operand was out of range.
_ovs equ 3
;0 No stack overflow.
;1 x87 stack overflow, if an x87 register stack fault was detected.
v0q equ 4
;0 x87 stack underflow, if an x87 register stack fault was detected.
;M Set equal to the value of bit 0 of the quotient, if there was no fault.
v1q equ 5 ;Set equal to the value of bit 1 of the quotient.
v2q equ 6 ;Set equal to the value of bit 2 of the quotient.
fpri equ 7
;0 FPREM generated the partial remainder.
;1 The source operands differed by more than a factor of 264, so the result
;is incomplete.
rnup equ 8
;0 x87 stack underflow, if an x87 register stack fault was detected.
;0 Result was rounded down, if a precision exception was detected.
;1 Result was rounded up, if a precision exception was detected.
fexm equ 9
;0 0 0 0 +unsupported format
;0 0 0 1 +NaN
;0 0 1 0 –unsupported format
;0 0 1 1 –NaN
;0 1 0 0 +normal
;0 1 0 1 +infinity
;0 1 1 0 –normal
;0 1 1 1 –infinity
;1 0 0 0 +0
;1 0 0 1 +empty
;1 0 1 0 –0
;1 0 1 1 –empty
;1 1 0 0 +denormal
;1 1 1 0 –denormal
_ous equ 10
;0 x87 stack underflow, if an x87 register stack fault was detected.
;1 x87 stack overflow, if an x87 register stack fault was detected.
cmp0 equ 11
;0 0 0 0 ST(0) > source
;0 0 0 1 ST(0) < source
;1 0 0 0 ST(0) = source
;1 1 0 1 Operands were unordered
ex00 equ 12
;0 No precision exception occurred.
;0 x87 stack underflow, if an x87 register stack fault was detected.
;0 Result was rounded down, if a precision exception was detected.
;1 Result was rounded up, if a precision exception was detected.
ex01 equ 13
;1 x87 stack overflow, if an x87 register stack fault was detected.
;0 If no other flags are set.
ex02 equ 14
;0 x87 stack underflow, if an x87 register stack fault was detected.
;1 x87 stack overflow, if an x87 register stack fault was detected.
;0 No x87 stack fault.
ex03 equ 15
;0 x87 stack underflow, if an x87 register stack fault was detected.
;1 x87 stack overflow, if an x87 register stack fault was detected.
;0 Result was rounded down, if a precision exception was detected.
;1 Result was rounded up, if a precision exception was detected.

MaxInstrLen equ 15
curr_id=MaxInstrLen+1
enum        VERBOSE_PFX,INVALID_INSTRUCTION,   INVALID_OPERAND,   OPCODE_OUT_RANGE
enum   UNKNOWN_MNEMONIC,           ASM_DUMP,  NOT_ALLOWED_LOCK,    NOT_ALLOWED_REP
enum  NOT_ALLOWED_REPXX,       TOO_LONG_STR,     TOO_MANY_ARGS,INSUFFICIENT_BUFFER
enum    INVALID_IN_LM16,TOO_LARGE_ALTER_NUM,MODE_CHANGED_TO_16, MODE_CHANGED_TO_32
enum MODE_CHANGED_TO_64,BASE_CHANGED_BY_ORG,     ASM_DIRECTIVE,        ASM_DUMP_IB
enum         ASM_OPTION,       ASM_EQUATION,       VSIB_ADDR16,          VSIB_MODE
enum          VSIB_RMEM,     VSIB_SAME_REGS
FULL_OPCSIZE equ 32
STD_MNEM_SIZE equ 32
STD_OPERMNEM_SIZE	equ 256
ALTM_STR_SIZE		equ 128
;IsHeapStr
curr_id=0
enf  MNEM_HEAP,OPER1_HEAP,OPER2_HEAP,   OPER3_HEAP
enf OPER4_HEAP,OPER5_HEAP, MO_RANGES,ANALYSES_HEAP
;InitInstrEx dwFlags
curr_id=8
enf SINGLE_DASM
;DsmCtrl
curr_id=0
enf MODRM_RANGES_PRESENT,ANALYSES_PRESENT,  OMIT_SHORT,OMIT_TYPE_SPEC
enf     OMIT_DEFAULT_SEG,        INDEX_BP
curr_id=9
enf        OMIT_NEAR_PTR,        LOADALLS,   RJ_OFFSET,        POP_CS,     CALCENG,JUST_DIRECTIVE
enf        JCC_SHORT_OPT,   JCC_SHORT_U15,    COFF_GEN
curr_id=26
enf FWAIT_APART,FULL_STR_MNEM,OFFSET_FLOAT,SKIP_DASM,ARCH_INTEL64,ARCH_AMD64
PLAIN_DASM		equ (MNEM_HEAP or OPER1_HEAP or OPER2_HEAP or OPER3_HEAP or OPER4_HEAP or OPER5_HEAP or RJ_OFFSET)
ANALYSES_AREA	equ (PLAIN_DASM or SINGLE_DASM)
STD_INSTR		equ (PLAIN_DASM or MO_RANGES)
EXT_INSTR		equ (STD_INSTR or ANALYSES_HEAP or CALCENG)

AltmBytes struc
	TotalBytes		BYTE ?
	AlterOpcNum		BYTE ?
	OptAddr			BYTE ?
	PfxPerm			BYTE ?
	WasteBitFields	BYTE ?
	WastePfx		BYTE 14 dup(?)
					BYTE 5 dup(?)
AltmBytes ends
PALTM_BYTES TYPEDEF PTR AltmBytes
moRange struc
	HighAddr	DWORD ?
	LowAddr		DWORD ?
moRange ends
moRanges struc
	CntRange	ULONG ?
	rng			moRange {}
moRanges ends
pmoRanges TYPEDEF PTR moRanges 
Features struc
	Note		BYTE ?
	exNote		BYTE ?
	MnemOrd		WORD ?
	FirstOper	BYTE ?
	SecondOper	BYTE ?
	ThirdOper	BYTE ?
	FourthOper	BYTE ?
	FifthOper   BYTE ?
	iSet		BYTE ?
Features ends
HANALYSES TYPEDEF PTR Analyses
HINB TYPEDEF PTR inbase
inbase struc
	hBase				HANDLE ?  ;+0
	RootInd				ULONG64 ? ;+8
	EquatesInd			ULONG64 ? ;+10h
	TextEqInd			ULONG64 ? ;+18h
	MacroEqsInd			ULONG64 ? ;+20h
	Next				HINB ?    ;+28h
inbase ends
PINCPATH	TYPEDEF PTR incpath
incpath struc
	Path		LPSTR ?
	Next		PINCPATH ?
incpath ends
REL_DATA struc
	NumOfSym	BYTE ?
				BYTE ?,?,?,?,?,?,?
	SymID		ULONG64 255 dup(?)
REL_DATA ends
PREL_DATA TYPEDEF PTR REL_DATA
Instruction struc
	MajorVersa		BYTE ?	;out +  0h
	MinorVersa		BYTE ?
	OpcNum			BYTE ?
	OpcTotal		BYTE ?
	DsmCtrl			DWORD ?	;in +04h
	CodePtr			PVOID ?	;in/out + 08h
	NextPtr			PVOID ? ;in/out + 10h
	AlterBase		QWORD ? ;in/out + 18h
	MnemOperType	LPSTR ? ;out + 20h
	Mnemonic		LPSTR ? ;out + 28h
	Oper1Mnemonic	LPSTR ? ;+ 30h
	Oper2Mnemonic	LPSTR ? ;+ 38h
	Oper3Mnemonic	LPSTR ? ;+ 40h
	Oper4Mnemonic	LPSTR ? ;+ 48h
	Oper5Mnemonic	LPSTR ? ;+ 50h
	RemnCode		ULONG64 ?	;in/out	;+ 58h
	ModrmOffsets	PVOID ?		;+ 60h
	hAnalyses		HANALYSES ?	;+ 68h
	Mode			BYTE ?		;in + 70h
	IsHeapStr		BYTE ?		;+ 71h
	FullOpcode		BYTE FULL_OPCSIZE dup(?)	;+ 72h
	;Legacy prefixes
	SegOver			BYTE ? ;out	+ 92h
	RepPfx			BYTE ? ;out	+ 93h
	PfxCnt			BYTE ? ;out	+ 94h
	;REX prefix
	union
		RexPfx			BYTE ? ;out	+ 95h
		XopRex			BYTE ?
		VexRex			BYTE ?
	ends
	union
		XopSec			BYTE ?	;+ 96h
		VexSec			BYTE ?
	ends
	DefaultAddrSize	BYTE ? ;out	+ 97h
	;ModRM
	mode			BYTE ? ;out	+ 98h
	reg				BYTE ? ;out	+ 99h
	rmem			BYTE ? ;out	+ 9Ah
	;SIB
	Scale			BYTE ? ;out	+ 9Bh
	Index			BYTE ? ;out	+ 9Ch
	Base			BYTE ? ;out	+ 9Dh
	ModRmAddress	BYTE 32 dup(?)	;+ 9Eh
	DefaultOperSize	WORD ?	;out	+0BEh
	iFlags			PVOID ?	;out	+0C0h
	x87Condition	x87c <>	;out	+0C8h
	union
		mOffset			DWORD ?	;out	+0D0h
		AddrBias		DWORD ? ;out	+0D0h
	ends
	iMxcsr			DWORD ?	;out	+0D4h
	DataSegMnem		DWORD ? ;out	+0D8h
	Status			DWORD ?	;out	+0DCh
	InstrLen		DWORD ?  ;out	+0E0h
	Opflags			DWORD ? ;out	+0E4h
	union
		OpFeatures		Features <>	;out	+0E8h
		oft				Features <>
	ends
	OptAddr			BYTE ?		;out	+0F2h
	Filler			BYTE ? ;+0F3h
	Opflags2		DWORD ? ;out	+0F4h
	hInb				HINB ? ;+0F8h
	hCalc				HANDLE ?  ;in     +100h
	EvalFlags			DWORD ? ;in     +108h
	AlterOpc11			BYTE ? ;out	+10Ch
	AlterOpcxx			BYTE ? ;out	+10Dh
	OpcNum2				BYTE ? ;out	+10Eh
	OpcTotal2			BYTE ? ;out	+10Fh
	EquatesInd			ULONG64 ? ;in     +110h
	union
		RipOffset		LPSTR ?	;out	+118h
		JAddrOffset		LPSTR ?
	ends
	JccPfxFiller			BYTE ?
							BYTE ?,?,?,?,?,?,?
	fn1_eax			DWORD ? ;+128h
	fn1_ebx			DWORD ? ;+12Ch
	fn1_ecx			DWORD ? ;+130h
	fn1_edx			DWORD ? ;+134h
	fn7_eax			DWORD ? ;+138h
	fn7_ebx			DWORD ? ;+13Ch
	fn7_ecx			DWORD ? ;+140h
	fn7_edx			DWORD ? ;+144h
	fn80000001_eax			DWORD ? ;+148h
	fn80000001_ebx			DWORD ? ;+14Ch
	fn80000001_ecx			DWORD ? ;+150h
	fn80000001_edx			DWORD ? ;+154h
	InitialCodePtr			PVOID ? ;+158h
	InitialCodeSize			ULONG64 ? ;+160h
	RelData				PREL_DATA ?	;+168h
Instruction ends	;170h-bytes
Inn TYPEDEF Instruction
HINSTR TYPEDEF PTR Instruction
Analyses struc
	Analyzand		HINSTR ?
	AnalysesArea	HINSTR ?
	AltmMnemonic	CHAR ALTM_STR_SIZE dup(?)
	AlterOpc		BYTE ?
	PfxPerm			BYTE ?
	WastePfx		BYTE 14 dup(?)
	WasteBitFields	BYTE ?
	LegacyCnt		BYTE ?
					BYTE 6 dup(?)
Analyses ends
curr_id=0
enf IS_TEXT,REDEFINE_NUM,REDEFINE_TEXT,REDEFINE_MACRO_EQ,IS_MACRO_EQ,IS_EQU_NUM
;Modes
curr_id=0
enum    LONG_MODE,LEGACY_MODE32,LEGACY_MODE16
;Opcodes flags
curr_id=0
enf           OPER66OVER,   ADDR67OVER,   LOCK_PFX,           MODRM
enf             SIB_BYTE,      MOFFSET,   RIP_ADDR,  ERASE_SECOND_N
enf JADDR16_BUT_NOT_LM16, MOD11_OPCODE,     PFX_F3,           JADDR
enf            OPER2_MEM,   REG_OPCODE,RMEM_OPCODE,   F2F366_OPCODE
enf          F2F3_OPCODE,WASTE_PFX_SET,    FLAG_0F,OPSZ_NOT_INFERRS
enf              CS_D_NA,      FLAG_38,    FLAG_3A,    CPL3_ALLOWED
enf              VEX_PFX,      XOP_PFX,       VSIB,       OPER1_MEM
enf            OPER3_MEM,    OPER4_MEM,   SVEX_PFX
;Opcodes2 flags
curr_id=16
enf        XACQUIRE_FLAG,  XRELEASE_FLAG
enf          DOLLAR_FLAG,CONST_REDEFINED
curr_id=0
enf REQ_TYPE,I_CPL3,A_USES,S_USES,O_USES,RE2_USES,R66_ANNIH
enf RB_USES,RR_USES,RW_USES,RE_USES,L_MBZ,M256_INT,OP5_PRES,VSIBA,LIG
;dwFlags
curr_id=0
enf    OFFSETS_COL,   HEX_COL,   RIP_ADDRS,REL_ADDRS
enf             CR,NOT_TABBED,          LF, ALT_MNEM
enf REL_FFFF_ADDRS, DB_STRING,ADDR_COMPACT
CR_LF				equ (CR or LF or ALT_MNEM)
STD_MNEM			equ (CR_LF or OFFSETS_COL or HEX_COL or ALT_MNEM or ADDR_COMPACT)
RIP_REL				equ (RIP_ADDRS or REL_ADDRS or CR_LF or ALT_MNEM)
STD_CLEAR_MNEM		equ (NOT_TABBED or ALT_MNEM)
RIP_REL_LF			equ (RIP_ADDRS or REL_ADDRS or LF or ALT_MNEM)
RIP_REL_FFFF		equ (RIP_ADDRS or REL_ADDRS or CR_LF or ALT_MNEM or REL_FFFF_ADDRS)

curr_id=0
enum     None
enum      m2z,      Ub,       Ib,        Iz,      Ubm,       Sb,           Uw,          _CL
enum       Iv,      Id
enum  Mb_Rd_q,   Mw_Rv,     M2ps,      Ed_q,      Wsd,       Yh
enum       Ed,     Wss,       Md,        Ww,       Wq,       Mq,        Mw_Rd,         Gd_q
enum    vGd_q,     Wdq,      Vpd,        Wb,       Wd,      Mdq,          Mpd,         W2ps
enum      Vps,     Vss,      Vsd,      iVpb,     iVpw,     iVpd,         iVpq
enum      Yps,     Ypd,      Yss,       Ysd,     iYpb,     iYpw,         iYpd,         iYpq
enum     vVps,    vVpd,     vVss,      vVsd,    viVpb,    viVpw,        viVpd,        viVpq
enum     vYps,    vYpd,     vYss,      vYsd,    viYpb,    viYpw,        viYpd,        viYpq
enum     VRps,    VRpd,      VRq,      VRdq,     iWpb,     iWpw,         iWpd,         iWpq
enum     mYps,    mYpd,    imYpb,     imYpw,    imYpd,    imYpq
enum     bVps,    bVpd,     bVss,      bVsd,    biVpb,    biVpw,        biVpd,        biVpq
enum     bYps,    bYpd,     bYss,      bYsd,    biYpb,    biYpw,        biYpd,        biYpq
enum     YRdq,      Mh,      Mss,       Msd,      Mps,     LMps,         YRps,         LMpd
enum     LMdq,     Mqq,    __Mod,       Mqd,     YRpd,     V2ps,        iVRpw,         iVpo
enum      mYh,    iWpo,       Vq,       Vdq,     Vd_q,      Wps,          Wpd,           Vd
enum    iVRpd,   iVRpb,    iVRpq,     iYRpb,    iYRpw,    iYRpd,        iYRpq,        iW2pd
enum     Whps,   W4hps,     W8pb,      W4pb,     W2pb,     W4pw,         W2pw
enum       Pd,      Pq,     iPpb,      iQpb,     iPpw,     iQpw,         iPpd,         iQpd
enum    iP4pb,   iQ4pb,    iP2pw,     iQ2pw,      iPd,      iQd
enum       Eb,      Ew,       Ev,       _Eq,       Gb,       Gw,           Gd,           Gv          
enum    iPRpd,   iPRpb,    iPRpw,      iYpo
enum     Pd_q,      Qq,      PRq,  mem80dec,  m32real,  m64real,    mem80real
enum   m16int,  m32int,   m64int,       m16
enum        M,      Ma,       Mp,        Mb
enum       Mw,      Mv,       Ms,    Mq_Mdq,  Mw_Rd_q
enum     Md_q,      Rv,     Rd_q,     Mb_Rd,       Sw
enum     Td_q
enum     Cd_q,    Dd_q,     _st0,      _st1,     _st2,     _st3,         _st4,         _st5
enum     _st6,    _st7, env14_28, env94_108,     vmcb,      Gzv,     UnkModRM
enum       Ob,      Ov,       Ap
enum      _Jb,      Yb,       Xb,        Yz,       Xz,       Yv,           Xv,       rAX_r8
enum   rCX_r9, rDX_r10,  rBX_r11,   rSP_r12,  rBP_r13,  rSI_r14,      rDI_r15,       AL_r8b
enum   CL_r9b, DL_r10b,  BL_r11b,   AH_r12b,  CH_r13b,  DH_r14b,      BH_r15b,         _rAX
enum     _eAX,    _eCX,     _eDX,      _eBX,     _eSP,     _eBP,         _eSI,         _eDI
enum      _AL,     _AX,      _DX,       _ES,      _CS,      _SS,          _DS,          _FS
enum      _GS,     One,       xb,       _Jz,     _eax,     _ecx

MIN_MODRM equ Mb_Rd_q
MAX_MODRM equ UnkModRM

idm macro String:VARARG
LOCAL ParmLen1,DefStr
%	FOR parm,<String>
		DefStr CATSTR <id_&parm>,< equ >,@CatStr(%MnemCnt)
		%DefStr
		MnemCnt=MnemCnt+1
	ENDM
endm
MnemCnt=0
;MnemonicsIds
idm add,push,pop,or,adc,sbb,and,daa								;  0,  1,  2,  3,  4,  5,  6,  7
idm sub,das,xor,aaa,cmp,aas,inc,dec								;  8,  9, 10, 11, 12, 13, 14, 15
idm pushad,pusha,popad,popa,bound,movsxd,arpl,imul     			; 16, 17, 18, 19, 20, 21, 22, 23
idm insb,insd,insw,outsb,outsd,outsw,jo,jno						; 24, 25, 26, 27, 28, 29, 30, 31
idm jb,jnb,jz,jnz,jbe,ja,js,jns									; 32, 33, 34, 35, 36, 37, 38, 39
idm jp,jnp,jl,jnl,jle,jg,test,xchg								; 40, 41, 42, 43, 44, 45, 46, 47
idm mov,lea,nop,pause,cdqe,cwde,cbw,cqo							; 48, 49, 50, 51, 52, 53, 54, 55
idm cdq,cwd,call,wait,pushfq,pushfd,pushf,popfq					; 56, 57, 58, 59, 60, 61, 62, 63
idm popfd,popf,sahf,lahf,movsb,movsq,movsd,movsw				; 64, 65, 66, 67, 68, 69, 70, 71
idm cmpsb,cmpsq,cmpsd,cmpsw,stosb,stosq,stosd,stosw				; 72, 73, 74, 75, 76, 77, 78, 79
idm lodsb,lodsq,lodsd,lodsw,scasb,scasq,scasd,scasw				; 80, 81, 82, 83, 84, 85, 86, 87
idm retn,les,lds,enter,leave,retf,int3,int						; 88, 89, 90, 91, 92, 93, 94, 95
idm into,iretq,iretd,iret,aam,aad,salc,xlat						; 96, 97, 98, 99,100,101,102,103
idm loopz,loopzd,loopzw,jrcxz,jecxz,jcxz,in,out					;104,105,106,107,108,109,110,111
idm jmp,int1,hlt,cmc,clc,stc,cli,sti							;112,113,114,115,116,117,118,119
idm cld,std,movs,rol,ror,rcl,rcr,shl							;120,121,122,123,124,125,126,127
idm shr,sal,sar,not,neg,mul,div,idiv							;128,129,130,131,132,133,134,135
idm sldt,str,lldt,ltr,verr,verw,sgdt,sidt						;136,137,138,139,140,141,142,143
idm lgdt,lidt,smsw,lmsw,invlpg,swapgs,rdtscp,vmrun				;144,145,146,147,148,149,150,151
idm vmmcall,vmload,vmsave,stgi,clgi,skinit,invlpga,monitor		;152,153,154,155,156,157,158,159
idm mwait,lfence,mfence,sfence,bt,bts,btr,btc					;160,161,162,163,164,165,166,167
idm cmpxchg16b,cmpxchg8b,psrlw,psraw,psllw,psrld,psrad,pslld	;168,169,170,171,172,173,174,175
idm psrlq,psllq,psrldq,pslldq,fxsave64,fxsave,ldmxcsr,stmxcsr	;176,177,178,179,180,181,182,183
idm clflush,prefetchnta,prefetcht0,prefetcht1,prefetcht2,extrq,prefetch,lar	;184,185,186,187,188,189,190,191
idm lsl,syscall,clts,sysenter,invd,wbinvd,ud2,femms				;192,193,194,195,196,197,198,199
idm movups,movss,movupd,movlps,movhlps,movsldup,movlpd,movddup	;200,201,202,203,204,205,206,207
idm unpcklps,unpcklpd,unpckhps,unpckhpd,movhps,movlhps,movshdup,movhpd ;208,209,210,211,212,213,214,215
idm movaps,movapd,cvtpi2ps,cvtsi2ss,cvtpi2pd,cvtsi2sd,movntps,movntss  ;216,217,218,219,220,221,222,223
idm movntpd,movntsd,cvttps2pi,cvttss2si,cvttpd2pi,cvttsd2si,cvtps2pi,cvtss2si	;224,225,226,227,228,229,230,231
idm cvtpd2pi,cvtsd2si,ucomiss,ucomisd,comiss,comisd,rdtsc,wrmsr		;232,233,234,235,236,237,238,239
idm rdmsr,rdpmc,sysexitq,sysexit,cmovo,cmovno,cmovb,cmovnb		;240,241,242,243,244,245,246,247
idm cmovz,cmovnz,cmovbe,cmova,cmovs,cmovns,cmovp,cmovnp			;248,249,250,251,252,253,254,255
idm cmovl,cmovnl,cmovle,cmovg,movmskps,movmskpd,sqrtps,sqrtss	;256,257,258,259,260,261,262,263
idm sqrtpd,sqrtsd,rsqrtps,rsqrtss,rcpps,rcpss,andps,andpd		;264,265,266,267,268,269,270,271
idm andnps,andnpd,orps,orpd,xorps,xorpd,addps,addss				;272,273,274,275,276,277,278,279
idm addpd,addsd,mulps,mulss,mulpd,mulsd,cvtps2pd,cvtss2sd		;280,281,282,283,284,285,286,287
idm cvtpd2ps,cvtsd2ss,cvtdq2ps,cvttps2dq,cvtps2dq,subps,subss,subpd	;288,289,290,291,292,293,294,295
idm subsd,minps,minss,minpd,minsd,divps,divss,divpd				;296,297,298,299,300,301,302,303
idm divsd,maxps,maxss,maxpd,maxsd,punpcklbw,punpcklwd,punpckldq		;304,305,306,307,308,309,310,311
idm packsswb,pcmpgtb,pcmpgtw,pcmpgtd,packuswb,punpckhbw,punpckhwd,punpckhdq	;312,313,314,315,316,317,318,319
idm packssdw,punpcklqdq,punpckhqdq,movd,movq,movdqu,movdqa,pshufw	;320,321,322,323,324,325,326,327
idm pshufhw,pshufd,pshuflw,pcmpeqb,pcmpeqw,pcmpeqd,emms,insertq		;328,329,330,331,332,333,334,335
idm haddpd,haddps,hsubpd,hsubps,seto,setno,setb,setnb 				;336,337,338,339,340,341,342,343
idm setz,setnz,setbe,seta,sets,setns,setp,setnp						;344,345,346,347,348,349,350,351
idm setl,setnl,setle,setg,cpuid,shld,rsm,shrd						;352,353,354,355,356,357,358,359
idm cmpxchg,lss,lfs,lgs,movzx,popcnt,bsf,bsr						;360,361,362,363,364,365,366,367
idm lzcnt,movsx,xadd,cmpps,cmpss,cmppd,movnti,pinsrw				;368,369,370,371,372,373,374,375
idm pextrw,shufps,shufpd,bswap,addsubpd,addsubps,paddq,pmullw		;376,377,378,379,380,381,382,383
idm movq2dq,movdq2q,pmovmskb,psubusb,psubusw,pminub,pand,paddusb	;384,385,386,387,388,389,390,391
idm paddusw,pmaxub,pandn,pavgb,pavgw,pmulhuw,pmulhw,cvtdq2pd		;392,393,394,395,396,397,398,399
idm cvttpd2dq,cvtpd2dq,movntq,movntdq,psubsb,psubsw,pminsw,por		;400,401,402,403,404,405,406,407
idm paddsb,paddsw,pmaxsw,pxor,lddqu,pmuludq,pmaddwd,psadbw			;408,409,410,411,412,413,414,415
idm maskmovq,maskmovdqu,psubb,psubw,psubd,psubq,paddb,paddw			;416,417,418,419,420,421,422,423
idm paddd,pfcmpge,pfmin,pfrcp,pfrsqrt,pfcmpgt,pfmax,pfrcpit1		;424,425,426,427,428,429,430,431
idm pfrsqit1,pfcmpeq,pfmul,pfrcpit2,pmulhrw,pi2fw,pi2fd,pf2iw		;432,433,434,435,436,437,438,439
idm pf2id,pfnacc,pfpnacc,pfsub,pfadd,pfsubr,pfacc,pswapd			;440,441,442,443,444,445,446,447
idm pavgusb,fadd,fmul,fcom,fcomp,fsub,fsubr,fdiv					;448,449,450,451,452,453,454,455
idm fdivr,fld,fst,fstp,fldenv,fldcw,fnstenv,fstenv					;456,457,458,459,460,461,462,463
idm fnstcw,fstcw,fxch,fnop,fchs,fld1,f2xm1,fprem					;464,465,466,467,468,469,470,471
idm fabs,fldl2t,fyl2x,fyl2xp1,fldl2e,fptan,fsqrt,fldpi				;472,473,474,475,476,477,478,479
idm fpatan,fsincos,ftst,fldlg2,fxtract,frndint,fxam,fldln2			;480,481,482,483,484,485,486,487
idm fprem1,fscale,fldz,fdecstp,fsin,fincstp,fcos,fiadd				;488,489,490,491,492,493,494,495
idm fimul,ficom,ficomp,fisub,fisubr,fidiv,fidivr,fcmovb				;496,497,498,499,500,501,502,503
idm fcmove,fcmovbe,fcmovu,fucompp,fild,fisttp,fist,fistp			;504,505,506,507,508,509,510,511
idm fcmovnb,fcmovne,fcmovnbe,fcmovnu,fucomi,fcomi,fnclex,fclex		;512,513,514,515,516,517,518,519
idm fninit,finit,frstor,fnsave,fsave,fnstsw,fstsw,ffree				;520,521,522,523,524,525,526,527
idm fucom,fucomp,faddp,fmulp,fsubrp,fsubp,fdivrp,fdivp				;528,529,530,531,532,533,534,535
idm fcompp,fbld,fbstp,fucomip,fcomip,ins,scas,outs					;536,537,538,539,540,541,542,543
idm loopnz,loopnzd,loopnzw,loop,loopd,loopw,cmps,xlatb				;544,545,546,547,548,549,550,551
idm prefetchw,lods,stos,getsec,retnw,retnd,enterw,enterd			;552,553,554,555,556,557,558,559
idm leavew,leaved,vmread,vmwrite,vmcall,vmlaunch,vmresume,vmxoff	;560,561,562,563,564,565,566,567
idm vmptrld,vmptrst,vmclear,vmxon,invept,invvpid,xgetbv,xsetbv		;568,569,570,571,572,573,574,575
idm xsave64,xsave,xrstor64,xrstor,pshufb,phaddw,phaddd,phaddsw		;576,577,578,579,580,581,582,583
idm pmaddubsw,phsubw,phsubd,phsubsw,psignb,psignw,psignd,pmulhrsw	;584,585,586,587,588,589,590,591
idm pblendvb,blendvps,blendvpd,ptest,pabsb,pabsw,pabsd,pmovsxbw		;592,593,594,595,596,597,598,599
idm pmovsxbd,pmovsxbq,pmovsxwd,pmovsxwq,pmovsxdq,pmuldq,pcmpeqq,movntdqa	;600,601,602,603,604,605,606,607
idm packusdw,pmovzxbw,pmovzxbd,pmovzxbq,pmovzxwd,pmovzxwq,pmovzxdq,pcmpgtq	;608,609,610,611,612,613,614,615
idm pminsb,pminsd,pminuw,pminud,pmaxsb,pmaxsd,pmaxuw,pmaxud					;616,617,618,619,620,621,622,623
idm pmulld,phminposuw,aesimc,aesenc,aesenclast,aesdec,aesdeclast,movbe		;624,625,626,627,628,629,630,631
idm crc32,roundps,roundpd,blendps,blendpd,pblendw,aeskeygenassist,dpps		;632,633,634,635,636,637,638,639
idm dppd,mpsadbw,pclmulqdq,pcmpestrm,pcmpestri,pcmpistrm,pcmpistri,roundss	;640,641,642,643,644,645,646,647
idm roundsd,palignr,pextrb,pextrq,pextrd,extractps,pinsrb,insertps			;648,649,650,651,652,653,654,655
idm pinsrq,pinsrd,cmpeqpd,cmpltpd,cmplepd,cmpunordpd,cmpneqpd,cmpnltpd		;656,657,658,659,660,661,662,663
idm cmpnlepd,cmpordpd,cmpeqps,cmpltps,cmpleps,cmpunordps,cmpneqps,cmpnltps  ;664,665,666,667,668,669,670,671
idm cmpnleps,cmpordps,cmpeqss,cmpltss,cmpless,cmpunordss,cmpneqss,cmpnltss	;672,673,674,675,676,677,678,679
idm cmpnless,cmpordss,cmpeqsd,cmpltsd,cmplesd,cmpunordsd,cmpneqsd,cmpnltsd	;680,681,682,683,684,685,686,687
idm cmpnlesd,cmpordsd,fxrstor64,fxrstor,jmpe,retfw,retfd,retfq				;688,689,690,691,692,693,694,695
idm vfmaddss,vfmaddsubpd,vfmaddsubps,vfmsubaddpd,vfmsubaddps,vfmsubpd,vfmsubps,vfmsubsd	;696,697,698,699,700,701,702,703
idm vfmsubss,vfnmaddpd,vfnmaddps,vfnmaddsd,vfnmaddss,vfnmsubpd,vfnmsubps,vfnmsubsd		;704,705,706,707,708,709,710,711
idm vfnmsubss,vpermil2pd,vpermil2ps,vfmaddpd,vfmaddps,vfmaddsd,vfrczpd,vfrczps			;712,713,714,715,716,717,718,719
idm vfrczss,vfrczsd,vpcmov,vpcomb,vpcomltb,vpcomleb,vpcomgtb,vpcomgeb					;720,721,722,723,724,725,726,727
idm vpcomeqb,vpcomneqb,vpcomfalseb,vpcomtrueb,vpcomd,vpcomltd,vpcomled,vpcomgtd			;728,729,730,731,732,733,734,735
idm vpcomged,vpcomeqd,vpcomneqd,vpcomfalsed,vpcomtrued,vpcomq,vpcomltq,vpcomleq			;736,737,738,739,740,741,742,743
idm vpcomgtq,vpcomgeq,vpcomeqq,vpcomneqq,vpcomfalseq,vpcomtrueq,vpcomub,vpcomltub		;744,745,746,747,748,749,750,751
idm vpcomleub,vpcomgtub,vpcomgeub,vpcomequb,vpcomnequb,vpcomfalseub,vpcomtrueub,vpcomud	;752,753,754,755,756,757,758,759
idm vpcomltud,vpcomleud,vpcomgtud,vpcomgeud,vpcomequd,vpcomnequd,vpcomfalseud,vpcomtrueud	;760,761,762,763,764,765,766,767
idm vpcomuq,vpcomltuq,vpcomleuq,vpcomgtuq,vpcomgeuq,vpcomequq,vpcomnequq,vpcomfalseuq	;768,769,770,771,772,773,774,775
idm vpcomtrueuq,vpcomuw,vpcomltuw,vpcomleuw,vpcomgtuw,vpcomgeuw,vpcomequw,vpcomnequw	;776,777,778,779,780,781,782,783
idm vpcomfalseuw,vpcomtrueuw,vpcomw,vpcomltw,vpcomlew,vpcomgtw,vpcomgew,vpcomeqw		;784,785,786,787,788,789,790,791
idm vpcomneqw,vpcomfalsew,vpcomtruew,vphaddbw,vphaddbd,vphaddbq,vphadddq,vphaddubw		;792,793,794,795,796,797,798,799
idm vphaddubd,vphaddubq,vphaddudq,vphadduwd,vphadduwq,vphaddwd,vphaddwq,vphsubbw		;800,801,802,803,804,805,806,807
idm vphsubdq,vphsubwd,vpmacsdd,vpmacsdqh,vpmacsdql,vpmacssdd,vpmacssdqh,vpmacssdql		;808,809,810,811,812,813,814,815
idm vpmacsswd,vpmacssww,vpmacswd,vpmacsww,vpmadcsswd,vpmadcswd,vpperm,vprotb			;816,817,818,819,820,821,822,823
idm vprotd,vprotq,vprotw,vpshab,vpshad,vpshaq,vpshaw,vpshlb								;824,825,826,827,828,829,830,831
idm vpshld,vpshlq,vpshlw,call64,jmp64,vaddpd,vaddps,vaddsd								;832,833,834,835,836,837,838,839
idm vaddss,vaddsubpd,vaddsubps,vaesenc,vaesenclast,vaesdec,vaesdeclast,vaesimc			;840,841,842,843,844,845,846,847
idm vaeskeygenassist,vandpd,vandps,vandnpd,vandnps,vblendpd,vblendps,vblendvpd			;848,849,850,851,852,853,854,855
idm vblendvps,vbroadcastss,vbroadcastsd,vbroadcastf128,vcmppd,vcmpps,vcmpsd,vcmpss		;856,857,858,859,860,861,862,863
idm vcomisd,vcomiss,vcvtdq2pd,vcvtdq2ps,vcvtpd2dq,vcvtpd2ps,vcvtps2dq,vcvtps2pd			;864,865,866,867,868,869,870,871
idm vcvtsd2si,vcvtsd2ss,vcvtsi2sd,vcvtsi2ss,vcvtss2sd,vcvtss2si,vcvttpd2dq,vcvttps2dq	;872,873,874,875,876,877,878,879
idm vcvttsd2si,vcvttss2si,vdivpd,vdivps,vdivsd,vdivss,vdppd,vdpps						;880,881,882,883,884,885,886,887
idm vextractf128,vextractps,vhaddpd,vhaddps,vhsubpd,vhsubps,vinsertf128,vinsertps		;888,889,890,891,892,893,894,895
idm vlddqu,vldmxcsr,vmaskmovdqu,vmaskmovps,vmaskmovpd,vmaxpd,vmaxps,vmaxsd				;896,897,898,899,900,901,902,903
idm vmaxss,vminpd,vminps,vminsd,vminss,vmovapd,vmovaps,vmovq							;904,905,906,907,908,909,910,911
idm vmovd,vmovddup,vmovdqa,vmovdqu,vmovlps,vmovhlps,vmovhps,vmovlhps					;912,913,914,915,916,917,918,919
idm vmovlpd,vmovhpd,vmovmskpd,vmovmskps,vmovntdq,vmovntdqa,vmovntpd,vmovntps			;920,921,922,923,924,925,926,927
idm vmovsd,vmovshdup,vmovsldup,vmovss,vmovupd,vmovups,vmpsadbw,vmulpd					;928,929,930,931,932,933,934,935
idm vmulps,vmulsd,vmulss,vorpd,vorps,vpabsb,vpabsw,vpabsd								;936,937,938,939,940,941,942,943
idm vpacksswb,vpackssdw,vpackuswb,vpackusdw,vpaddb,vpaddw,vpaddd,vpaddq					;944,945,946,947,948,949,950,951
idm vpaddsb,vpaddsw,vpaddusb,vpaddusw,vpalignr,vpand,vpandn,vpavgb						;952,953,954,955,956,957,958,959
idm vpavgw,vpblendvb,vpblendw,vpclmulqdq,vpcmpestri,vpcmpestrm,vpcmpistri,vpcmpistrm		;960,961,962,963,964,965,966,967
idm vpcmpeqb,vpcmpeqw,vpcmpeqd,vpcmpeqq,vpcmpgtb,vpcmpgtw,vpcmpgtd,vpcmpgtq			;968,969,970,971,972,973,974,975
idm vpermilpd,vpermilps,vperm2f128,vpextrb,vpextrw,vphaddw,vphaddd,vphaddsw			;976,977,978,979,980,981,982,983
idm vphminposuw,vphsubw,vphsubd,vphsubsw,vpinsrb,vpinsrw,vpinsrq,vpinsrd			;984,985,986,987,988,989,990,991
idm vpmaddwd,vpmaddubsw,vpmaxsb,vpmaxsw,vpmaxsd,vpmaxub,vpmaxuw,vpmaxud				;992,993,994,995,996,997,998,999
idm vpminsb,vpminsw,vpminsd,vpminub,vpminuw,vpminud,vpmovmskb,vpmovsxbw				;1000,1001,1002,1003,1004,1005,1006,1007
idm vpmovsxbd,vpmovzxbw,vpmovzxbd,vpmulhuw,vpmulhrsw,vpmulhw,vpmullw,vpmulld		;1008,1009,1010,1011,1012,1013,1014,1015	
idm vpmuludq,vpmuldq,vpor,vpsadbw,vpshufb,vpshufd,vpshufhw,vpshuflw					;1016,1017,1018,1019,1020,1021,1022,1023
idm vpsignb,vpsignw,vpsignd,vpslldq,vpsrldq,vpsllw,vpslld,vpsraw					;1024,1025,1026,1027,1028,1029,1030,1031
idm vpsrad,vpsrlw,vpsrld,vptest,vtestps,vtestpd,vpsubb,vpsubw						;1032,1033,1034,1035,1036,1037,1038,1039
idm vpsubd,vpsubq,vpsubsb,vpsubsw,vpsubusb,vpsubusw,vpunpckhbw,vpunpckhwd			;1040,1041,1042,1043,1044,1045,1046,1047
idm vpunpckhdq,vpunpckhqdq,vpunpcklbw,vpunpcklwd,vpunpckldq,vpunpcklqdq,vpxor,vrcpps	;1048,1049,1050,1051,1052,1053,1054,1055
idm vrcpss,vrsqrtps,vrsqrtss,vroundpd,vroundps,vroundsd,vroundss,vshufpd				;1056,1057,1058,1059,1060,1061,1062,1063
idm vshufps,vsqrtpd,vsqrtps,vsqrtsd,vsqrtss,vstmxcsr,vsubpd,vsubps						;1064,1065,1066,1067,1068,1069,1070,1071
idm vsubsd,vsubss,vucomisd,vucomiss,vunpckhpd,vunpckhps,vunpcklpd,vunpcklps				;1072,1073,1074,1075,1076,1077,1078,1079
idm vxorpd,vxorps,vzeroall,vzeroupper,vfmadd132pd,vfmadd132ps,vfmadd213pd,vfmadd213ps	;1080,1081,1082,1083,1084,1085,1086,1087
idm vfmadd231pd,vfmadd231ps,vfmadd132sd,vfmadd132ss,vfmadd213sd,vfmadd213ss,vfmadd231sd,vfmadd231ss	;1088,1089,1090,1091,1092,1093,1094,1095
idm vfmaddsub132pd,vfmaddsub132ps,vfmaddsub213pd,vfmaddsub213ps,vfmaddsub231pd,vfmaddsub231ps,vfmsubadd132pd,vfmsubadd132ps	;1096,1097,1098,1099,1100,1101,1102,1103	
idm vfmsubadd213pd,vfmsubadd213ps,vfmsubadd231pd,vfmsubadd231ps,vfmsub132pd,vfmsub132ps,vfmsub213pd,vfmsub213ps	;1104,1105,1106,1107,1108,1109,1110,1111	
idm vfmsub231pd,vfmsub231ps,vfmsub132sd,vfmsub132ss,vfmsub213sd,vfmsub213ss,vfmsub231sd,vfmsub231ss			;1112,1113,1114,1115,1116,1117,1118,1119
idm vfnmadd132pd,vfnmadd132ps,vfnmadd213pd,vfnmadd213ps,vfnmadd231pd,vfnmadd231ps,vfnmadd132sd,vfnmadd132ss	;1120,1121,1122,1123,1124,1125,1126,1127
idm vfnmadd213sd,vfnmadd213ss,vfnmadd231sd,vfnmadd231ss,vfnmsub132pd,vfnmsub132ps,vfnmsub213pd,vfnmsub213ps	;1128,1129,1130,1131,1132,1133,1134,1135
idm vfnmsub231pd,vfnmsub231ps,vfnmsub132sd,vfnmsub132ss,vfnmsub213sd,vfnmsub213ss,vfnmsub231sd,vfnmsub231ss	;1136,1137,1138,1139,1140,1141,1142,1143
idm vcmpeqpd,vcmpltpd,vcmplepd,vcmpunordpd,vcmpneqpd,vcmpnltpd,vcmpnlepd,vcmpordpd								;1144,1145,1146,1147,1148,1149,1150,1151
idm vcmpeq_uqpd,vcmpnge_uspd,vcmpngt_uspd,vcmpfalse_oqpd,vcmpneq_oqpd,vcmpge_ospd,vcmpgt_ospd,vcmptrue_uqpd		;1152,1153,1154,1155,1156,1157,1158,1159	
idm vcmpeq_ospd,vcmplt_oqpd,vcmple_oqpd,vcmpunord_spd,vcmpneq_uspd,vcmpnlt_uqpd,vcmpnle_uqpd,vcmpord_spd		;1160,1161,1162,1163,1164,1165,1166,1167	
idm vcmpeq_uspd,vcmpnge_uqpd,vcmpngt_uqpd,vcmpfalse_ospd,vcmpneq_ospd,vcmpge_oqpd,vcmpgt_oqpd,vcmptrue_uspd		;1168,1169,1170,1171,1172,1173,1174,1175
idm vcmpeqps,vcmpltps,vcmpleps,vcmpunordps,vcmpneqps,vcmpnltps,vcmpnleps,vcmpordps								;1176,1177,1178,1179,1180,1181,1182,1183
idm vcmpeq_uqps,vcmpnge_usps,vcmpngt_usps,vcmpfalse_oqps,vcmpneq_oqps,vcmpge_osps,vcmpgt_osps,vcmptrue_uqps		;1184,1185,1186,1187,1188,1189,1190,1191
idm vcmpeq_osps,vcmplt_oqps,vcmple_oqps,vcmpunord_sps,vcmpneq_usps,vcmpnlt_uqps,vcmpnle_uqps,vcmpord_sps		;1192,1193,1194,1195,1196,1197,1198,1199
idm vcmpeq_usps,vcmpnge_uqps,vcmpngt_uqps,vcmpfalse_osps,vcmpneq_osps,vcmpge_oqps,vcmpgt_oqps,vcmptrue_usps		;1200,1201,1202,1203,1204,1205,1206,1207
idm vcmpeqsd,vcmpltsd,vcmplesd,vcmpunordsd,vcmpneqsd,vcmpnltsd,vcmpnlesd,vcmpordsd								;1208,1209,1210,1211,1212,1213,1214,1215
idm vcmpeq_uqsd,vcmpnge_ussd,vcmpngt_ussd,vcmpfalse_oqsd,vcmpneq_oqsd,vcmpge_ossd,vcmpgt_ossd,vcmptrue_uqsd		;1216,1217,1218,1219,1220,1221,1222,1223
idm vcmpeq_ossd,vcmplt_oqsd,vcmple_oqsd,vcmpunord_ssd,vcmpneq_ussd,vcmpnlt_uqsd,vcmpnle_uqsd,vcmpord_ssd		;1224,1225,1226,1227,1228,1229,1230,1231
idm vcmpeq_ussd,vcmpnge_uqsd,vcmpngt_uqsd,vcmpfalse_ossd,vcmpneq_ossd,vcmpge_oqsd,vcmpgt_oqsd,vcmptrue_ussd		;1232,1233,1234,1235,1236,1237,1238,1239
idm vcmpeqss,vcmpltss,vcmpless,vcmpunordss,vcmpneqss,vcmpnltss,vcmpnless,vcmpordss								;1240,1241,1242,1243,1244,1245,1246,1247
idm vcmpeq_uqss,vcmpnge_usss,vcmpngt_usss,vcmpfalse_oqss,vcmpneq_oqss,vcmpge_osss,vcmpgt_osss,vcmptrue_uqss		;1248,1249,1250,1251,1252,1253,1254,1255	
idm vcmpeq_osss,vcmplt_oqss,vcmple_oqss,vcmpunord_sss,vcmpneq_usss,vcmpnlt_uqss,vcmpnle_uqss,vcmpord_sss		;1256,1257,1258,1259,1260,1261,1262,1263
idm vcmpeq_usss,vcmpnge_uqss,vcmpngt_uqss,vcmpfalse_osss,vcmpneq_osss,vcmpge_oqss,vcmpgt_oqss,vcmptrue_usss		;1264,1265,1266,1267,1268,1269,1270,1271
idm vpclmullqlqdq,vpclmulhqlqdq,vpclmullqhdq,vpclmulhqhdq,pclmullqlqdq,pclmulhqlqdq,pclmullqhdq,pclmulhqhdq		;1272,1273,1274,1275,1276,1277,1278,1279
idm ffreep,fneni,feni,fndisi,fdisi,fnsetpm,fsetpm,frstpm						;1280,1281,1282,1283,1284,1285,1286,1287
idm fsaved,fsavew,fnsaved,fnsavew,frstord,frstorw,fldenvd,fldenvw				;1288,1289,1290,1291,1292,1293,1294,1295
idm fstenvd,fstenvw,fnstenvd,fnstenvw,vpsllq,vpsrlq,vpmovzxbq,vpmovzxdq			;1296,1297,1298,1299,1300,1301,1302,1302
idm vpmovzxwd,vpmovzxwq,vpmovsxbq,vpmovsxdq,vpmovsxwd,vpmovsxwq,vpextrq,vpextrd	;1304,1305,1306,1307,1308,1309,1310,1311
idm xsaveopt64,xsaveopt,sysretq,sysret,loadall286,loadall386,rdfsbase,rdgsbase	;1312,1313,1314,1315,1316,1317,1318,1319
idm rdrand,wrfsbase,wrgsbase,vcvtph2ps,vcvtps2ph,andn,bextr,blsi			;1320,1321,1322,1323,1324,1325,1326,1327
idm blsmsk,blsr,bzhi,mulx,pdep,pext,rorx,sarx								;1328,1329,1330,1331,1332,1333,1334,1335
idm shlx,shrx,tzcnt,invpcid,vpblendd,vpbroadcastb,vpbroadcastw,vpbroadcastd	;1336,1337,1338,1339,1340,1341,1342,1343
idm vpbroadcastq,vbroadcasti128,vpmaskmovq,vpmaskmovd,vpsllvq,vpsllvd,vpsravd,vpsrlvq	;1344,1345,1346,1347,1348,1349,1350,1351
idm vpsrlvd,vpermps,vpermd,vinserti128,vextracti128,vperm2i128,vpermpd,vpermq			;1352,1353,1354,1355,1356,1357,1358,1359
idm vgatherdpd,vgatherdps,vgatherqpd,vgatherqps,vpgatherdq,vpgatherdd,vpgatherqq,vpgatherqd	;1360,1361,1362,1363,1364,1365,1366,1367
idm blcfill,blci,blcic,blcmsk,blcs,blsfill,blsic,t1mskc		;1368,1369,1370,1371,1372,1373,1374,1375
idm tzmsk,llwpcb,lwpins,lwpval,slwpcb,xabort,xbegin,xend	;1376,1377,1378,1379,1380,1381,1382,1383
idm xtest,vmfunc,clac,stac,adcx,adox,rdseed	;1384,1385,1386,1387,1388,1389,1390
SizeOfImm3DNow equ 24
;Notes
curr_id=1
enum       UD64,  UD16_32, DIFF64_OPC,    WaitPfx,     x87,  MNEM16_DIFF,  MNEM16_DFUD64, TwoPDepBut66
enum TwoPDepend,    NOW3D,   MNEM_DIF, MNEM67_DIF,  FGROUP,    PfxDepend,   FGROUP_MOD11
enum     RegAvx,    wm_ch,     modmsd,       WMBZ,  sg_opc,       wm_chf,             W1

curr_id=1
enum  no32op,  j32no, framel,op_lock, op_rep,rep_n_e,CSdNA
enum m1l_avx, xop2op, xop3op, xop4op,nrev3op,nrev4op

curr_id=0
enum        ilwp
enum      ibasic, icmpxchgxb,    icmovcc,i3dprefetch,   iclflush,     imovbe,     icrc32,  iprefetch
enum   ilongmode, ipclmulqdq,       iaes, ixsaverstr, i64sysctrl,       itsc,    irdtscp,   irdwrmsr
enum isyscallret, ienterexit,       isvm,   isysctrl,  iisysctrl,       isse, issemmxext, issemmxbsc
enum     issemmx,  issebasic,ifxsaverstr,      isse2,   isse2mmx, ibasicsse2,isse2mmxext, isse2basic
enum       isse3,   isse3mmx,   isse3fpu,     issse3,issse3mmxex,     isse4a,     isse41,  isse41bsc
enum      isse42,       immx,    immxx87,  immxbasic,       ix87, ix87cmovcc,    ix87mmx,     i3dnow
enum   i3dnowx87,  i3dnowext,       ivmx,      ifma4,       ixop,       iavx,    iaesavx,      if16c
enum       ifma3,      ibmi1,      ibmi2,      iavx2,    iaclmul,  ifsgsbase,    irdrand,       itbm
enum       irtm,    ihle_rtm
SIGNED_INT		equ 1 shl 0
PLUS_SIGN		equ 1 shl 1
RADIX_LETTER	equ 1 shl 2
FIRST_CIPHER	equ 1 shl 3
STD_HEX			equ (FIRST_CIPHER or RADIX_LETTER)
STD_BIN			equ RADIX_LETTER
STD_OCT			equ RADIX_LETTER
STD_DEC			equ 0
SIGNED_HEX			equ (FIRST_CIPHER or RADIX_LETTER or SIGNED_INT)
SIGNED_BIN			equ (SIGNED_INT or RADIX_LETTER)
SIGNED_OCT			equ (SIGNED_INT or RADIX_LETTER)
SIGNED_DEC			equ SIGNED_INT
UPPER_CHAR equ 0DFh
DEFAULT_RADIX equ 1 shl 0
STD_MASM_NUM	equ (DEFAULT_RADIX or FIRST_CIPHER)
MUST_BE_POSITIVE_OR_ZERO	equ 1
DIVIDE_BY_ZERO				equ 2
MUST_BEGINS_BY_CIPHER		equ 3
OWORD_SIZE	equ 1 shl 8
HWORD_SIZE	equ 1 shl 9
DHWORD_SIZE	equ 1 shl 10
QHWORD_SIZE	equ 1 shl 11
INDIRECT_SHIFT_COUNT	equ 1 shl 12
ERASE_MASM_QUOTES		equ 1 shl 13
STD_MASM_NUM_128	equ (STD_MASM_NUM or OWORD_SIZE)
STD_MASM_NUM_256	equ (STD_MASM_NUM or HWORD_SIZE)
SIGNED_128			equ (SIGNED_INT or OWORD_SIZE)
SIGNED_256			equ (SIGNED_INT or HWORD_SIZE)
;Ïåðåñòàíîâêè ïðåôèêñîâ
pfx_lock  equ 0  ;- 0F0h
pfx_66    equ 1  ;- 66h
pfx_67    equ 2  ;- 67h
pfx_seg   equ 3  ;- 64h,65h (2Eh,3Eh,26h,36h)
pfx_f2_f3 equ 4  ;- 0F2h,0F3h
curr_id=0
enum c_ss0000,c_gp0001,c_gp0002,c_gp0003,c_pf0004,c_ac0005,c_np0006,c_ss0007
enum c_gp0008,c_gp0009,c_gp0010,c_gp0011,c_gp0012,c_gp0013,c_gp0014,c_ss0015
enum c_br0016,c_gp0017,c_ss0018,c_gp0019,c_ud0020,c_gp0021,c_gp0022,c_gp0023
enum c_gp0024,c_ss0025,c_gp0026,c_ud0027,c_ud0028,c_gp0029,c_gp0030,c_gp0031
enum c_gp0032,c_gp0033,c_gp0034,c_gp0035,c_db0036,c_ud0037,c_ud0038,c_gp0039
enum c_ts0040,c_ts0041,c_ts0042,c_ts0043,c_ts0044,c_ts0045,c_ts0046,c_np0047
enum c_ss0048,c_ss0049,c_gp0050,c_gp0051,c_gp0052,c_gp0053,c_gp0054,c_gp0055
enum c_gp0056,c_gp0057,c_gp0058,c_gp0059,c_gp0060,c_gp0061,c_nm0062,c_mf0063
enum c_gp0064,c_gp0065,c_ud0066,c_ud0067,c_ud0068,c_ud0069,c_nm0070,c_ud0071
enum c_xf0072,c_xf0073,c_xf0074,c_gp0075,c_gp0076,c_gp0077,c_ud0078,c_ud0079
enum c_ud0080,c_gp0081,c_gp0082,c_gp0083,c_gp0084,c_gp0085,c_gp0086,c_gp0087
enum c_gp0088,c_gp0089,c_gp0090,c_gp0091,c_gp0092,c_gp0093,c_gp0094,c_gp0095
enum c_gp0096,c_gp0097,c_gp0098,c_gp0099,c_gp0100,c_gp0101,c_gp0102,c_gp0103
enum c_np0104,c_ss0105,c_gp0106,c_gp0107,c_gp0108,c_gp0109,c_gp0110,c_gp0111
enum c_gp0112,c_gp0113,c_gp0114,c_gp0115,c_gp0116,c_np0117,c_gp0118,c_gp0119
enum c_gp0120,c_gp0121,c_gp0122,c_gp0123,c_gp0124,c_gp0125,c_gp0126,c_gp0127
enum c_of0128,c_bp0129,c_ts0130,c_ss0131,c_db0132,c_gp0133,c_de0134,c_gp0135
enum c_gp0136,c_gp0137,c_de0138,c_de0139,c_ud0140,c_np0141,c_gp0142,c_gp0143
enum c_gp0144,c_gp0145,c_gp0146,c_np0147,c_gp0148,c_gp0149,c_gp0150,c_gp0151
enum c_ud0152,c_gp0153,c_ud0154,c_ud0155,c_ud0156,c_gp0157,c_gp0158,c_ud0159
enum c_ud0160,c_gp0161,c_gp0162,c_ud0163,c_ud0164,c_ud0165,c_gp0166,c_gp0167
enum c_ud0168,c_ud0169,c_ud0170,c_ud0171,c_ud0172,c_gp0173,c_gp0174,c_ac0175
enum c_ud0176,c_ud0177,c_gp0178,c_ud0179,c_gp0180,c_ud0181,c_ud0182,c_gp0183
enum c_ud0184,c_ud0185,c_ud0186,c_ud0187,c_ud0188,c_ud0189,c_xf0190,c_xf0191
enum c_xf0192,c_ud0193,c_gp0194,c_gp0195,c_gp0196,c_ud0197,c_ud0198,c_gp0199
enum c_gp0200,c_ud0201,c_gp0202,c_gp0203,c_ud0204,c_xf0205,c_xf0206,c_xf0207
enum c_xf0208,c_xf0209,c_xf0210,c_xf0211,c_xf0212,c_xf0213,c_xf0214,c_xf0215
enum c_xf0216,c_xf0217,c_ud0218,c_ud0219,c_ud0220,c_mf0221,c_mf0222,c_mf0223
enum c_mf0224,c_mf0225,c_mf0226,c_mf0227,c_mf0228,c_mf0229,c_mf0230,c_mf0231
enum c_mf0232,c_mf0233,c_mf0234,c_mf0235,c_mf0236,c_mf0237,c_mf0238,c_mf0239
enum c_mf0240,c_mf0241,c_mf0242,c_mf0243,c_mf0244,c_mf0245,c_mf0246,c_mf0247
enum c_mf0248,c_mf0249,c_mf0250,c_mf0251,c_ud0252,c_mf0253,c_mf0254,c_mf0255
enum c_mf0256,c_ud0257,c_ud0258,c_gp0259,c_pf0260,c_ss0261,c_ud0262,c_gp0263
enum c_ss0264,c_gp0265,c_gp0266,c_gp0267,c_gp0268,c_gp0269,c_pf0270,c_ss0271
enum c_ss0272,c_ss0273,c_ud0274,c_gp0275,c_ss0276,c_ss0277,c_gp0278,c_gp0279
enum c_pf0280,c_ss0281,c_ss0282,c_gp0283,c_gp0284,c_gp0285,c_pf0286,c_gp0287
enum c_gp0288,c_ud0289,c_gp0290,c_gp0291,c_ud0292,c_ud0293,c_ss0294,c_ss0295
enum c_gp0296,c_ud0297,c_ud0298,c_ud0299,c_ud0300,c_gp0301,c_gp0302,c_gp0303
enum c_nm0304,c_ss0305,c_ss0306,c_gp0307,c_gp0308,c_gp0309,c_gp0310,c_pf0311
enum c_gp0312,c_gp0313,c_gp0314,c_ud0315,c_ud0316,c_ud0317,c_nm0318,c_ss0319
enum c_gp0320,c_gp0321,c_pf0322,c_ac0323,c_gp0324,c_gp0325,c_ud0326,c_gp0327
enum c_gp0328,c_gp0329,c_ud0330,c_gp0331,c_ud0332,c_xf0333,c_xf0334,c_xf0335
enum c_xf0336,c_ud0337,c_ud0338,c_gp0339,c_xf0340,c_ud0341,c_ac0342,c_ac0343
enum c_ud0344,c_ud0345,c_ud0346,c_ud0347,c_ud0348,c_ud0349,c_ud0350,c_ud0351
enum c_nm0352,c_ss0353,c_gp0354,c_pf0355,c_ac0356,c_ud0357,c_ud0358,c_ud0359
enum c_ud0360,c_gp0361,c_ud0362,c_ud0363,c_ss0364,c_ss0365,c_gp0366,c_pf0367
enum c_ac0368,c_ud0369,c_ud0370,c_ud0371,c_ud0372,c_gp0373,c_gp0374,c_gp0375
enum c_gp0376,c_gp0377,c_pf0378,c_ss0379,c_ud0380,c_ud0381,c_pf0382,c_pf0383
enum c_pf0384,c_ud0385,c_gp0386,c_gp0387,c_pf0388,c_pf0389,c_ud0390,c_ud0391
enum c_gp0392,c_gp0393,c_gp0394,c_gp0395,c_ud0396,c_ud0397,c_ud0398,c_ss0399
enum c_ud0400,c_ud0401,c_ud0402,c_ud0403,c_ud0404,c_ss0405,c_ss0406,c_gp0407
enum c_gp0408,c_gp0409,c_pf0410,c_ac0411
ExceptionPtr struc
	Vector		BYTE ?
	Flags		BYTE ?
	NoteIndex	WORD ?
ExceptionPtr ends
Exceptions struc
	eCount		WORD ?
	VectorsList ExceptionPtr<>
Exceptions ends
PEXCEPTS TYPEDEF PTR Exceptions
E_REAL equ (1 shl 3)
E_8086 equ (1 shl 4)
E_PR86 equ (1 shl 5)
E_COMP equ (1 shl 6)
E_PR64 equ (1 shl 7)
E_PROT equ (E_PR86 or E_PR64 or E_COMP)
E_ALL  equ (E_REAL or E_8086 or E_PROT)
E_VPRT equ (E_8086 or E_PROT)
E_RORV equ (E_REAL or E_8086)
E_NVRT equ (E_REAL or E_PROT)
E_NORL equ (E_PROT or E_8086)
E_PR32 equ (E_COMP or E_PR86)
E_X86C equ (E_REAL or E_8086 or E_PR32)
;Interrupts and Exceptions
ExceptProps struc
	Interrupt	BYTE ?
	Mnemonic	CHAR 4 dup(?)
	Cause		BYTE ?
	Flags		WORD ?
ExceptProps ends
curr_id=0
enum E_DIVIDE_BY_ZERO_ERROR,E_DEBUG,E_NON_MASKABLE_INT,E_BREAKPOINT,E_OVERFLOW	;0,1,2,3,4
enum E_BOUND_RANGE,E_INVALID_OPCODE,E_DEVICE_NOT_AVAILABLE,E_DOUBLE_FAULT		;5,6,7,8
enum E_COPROCESSOR_SEG_OVER,E_INVALID_TSS,E_SEGMENT_NOT_PRESENT,E_STACK			;9,10,11,12
enum E_GENERAL_PROTECTION,E_PAGE_FAULT,E_RESERVED,E_X87_EXCEPT_PENDING			;13,14,15,16
enum E_ALIGNMENT_CHECK,E_MACHINE_CHECK,E_SIMD_FLOATING_POINT					;17,18,19
curr_id=30
enum E_SECURITY_EXCEPTION														;30
curr_id=32
enum E_EXTERNAL_INTS															;32
curr_id=0
enum C_DIV_IDIV_INSTRUCTIONS,C_INSTR_OR_DATA_ACCESS,C_EXTERNAL_NMI_SIGNAL,C_INT3_INSTR	;0,1,2,3
enum C_INTO_INSTR,C_BOUND_INSTR,C_INVALID_INSTRS,C_X87_INSTRUCTIONS,C_INT_DURING_AN_INT	;4,5,6,7,8
enum C_RESERVED,C_TSS_ACCESS_AND_SWITCH,C_ACCESS_THROUGH_AN_LSD,C_SS_LOADS_AND_SS_REFS	;9,10,11,12
enum C_MEM_ACCESS_AND_PCHECK,C_PAGING_MEM_ACCESS										;13,14
curr_id=16
enum C_X87_AND_MEDIA64_INSTR,C_MEM_ACCESS,C_MODEL_SPECIFIC,C_MEDIA128_INSTR				;16,17,18,19
curr_id=30
enum C_SECURE_EVENT_IN_HOST																;30
curr_id=32
enum C_EXT_INT_SIGNAL																	;32
SRC_SOFTWARE	equ (1 shl 3)
SRC_INTERNAL	equ (1 shl 4)
SRC_EXTERNAL	equ (1 shl 5)
TYPE_FAULT		equ (1 shl 6)
TYPE_TRAP		equ (1 shl 7)
TYPE_ABORT		equ (1 shl 8)
PRECISE			equ (1 shl 9)
NOT_PRECISE		equ (1 shl 10)
CLASS_CONTRIBUTORY	equ (1 shl 11)
CLASS_BENIGN		equ (1 shl 12)
GENS_BY_GEN_INSTRS	equ (1 shl 13)
RESERVED_VECTOR		equ (1 shl 14)
MediaException struc
	Exception		BYTE ?
	Mnemonic		CHAR 3 dup(?)
	AltMnemonic		CHAR 3 dup(?)
	Flags			BYTE ?
MediaException ends
IEEE754				equ (1 shl 3)
NAN_HIGH_PRIORITY	equ (1 shl 4)
curr_id=0
enum XF_INVALID_OPERATION,XF_DENORMALIZED_OPERATION,XF_ZERO_DIVIDED
enum XF_OVERFLOW,XF_UNDERFLOW,XF_PRECISION
X87Exception struc
	Exception		BYTE ?
	Mnemonic		CHAR 3 dup(?)
	AltMnemonic		CHAR 3 dup(?)
	Flags			BYTE ?
X87Exception ends
curr_id=0
enum MF_INVALID_OPERATION,MF_DENORMALIZED_OPERATION,MF_ZERO_DIVIDED
enum MF_OVERFLOW,MF_UNDERFLOW,MF_PRECISION,MF_STACK_FAULT


;Instruction Latencies
;Flags
LAT_IMM		equ (1 shl 0)
LAT_RNG		equ (1 shl 1)
LNOTE11		equ (1 shl 2)	;4 The latency listed is the absolute minimum, 
							;while average latencies may be higher and are a function of internal
							;pipeline conditions.
LAT_COND	equ (1 shl 3)
LAT_UNV		equ (1 shl 4)
LAT_FRACT	equ (1 shl 5)
LNOTE1		equ (1 shl 6)	;Static timing assumes a predicted branch.
LNOTE2		equ (1 shl 7)	;Store operation also updates ESP—the new 
							;register value is available one clock earlier 
							;than the specified latency.
LNOTE3		equ (1 shl 8)	;The clock count, regardless of the number of 
							;shifts or rotates, as determined by CL or imm8.
LNOTE4		equ (1 shl 9)	;LEA instructions have a latency of 1 when there 
							;are two source operands (as in the case of the base + index
							;form LEA EAX, [EDX+EDI]). Forms with a scale or more 
							;than two source operands will have a latency of 2 (LEA
							;EAX, [EBX+EBX*8]).
LNOTE5		equ (1 shl 10)	;These instructions have an effective latency as shown. 
							;They map to internal NOPs that can be issued at a rate of
							;three per cycle but do not occupy execution resources.
LNOTE6		equ (1 shl 11)	;The latency of repeated string instructions can be found 
							;in “Latency of Repeated String Instructions” on page 167.
LNOTE7		equ (1 shl 12)	;For the PREFETCH and PREFETCHW instructions, the mem8 
							;value refers to an address in the 64-byte line to be prefetched.
LNOTE8		equ (1 shl 13)	;These instructions have an effective latency as shown. However, 
							;these instructions generate an internal NOP
							;with a latency of two cycles but no related 
							;dependencies. These internal NOPs can be executed at a rate of
							;three per cycle and can use any of the three execution resources.
OPS16		equ (1 shl 14)
OPS32		equ (1 shl 15)
OPS64		equ (1 shl 16)
LNOTE10		equ (1 shl 17)	;The 8-clock latency is only visible to younger stores that need 
							;to do an external write. The 2-clock latency is
							;visible to the other stores and instructions.
LNOTE12		equ (1 shl 18)	;For the PREFETCHNTA/T0/T1/T2 instructions, the mem8 value
							;refers to an address in the 64-byte line to be prefetched.
TWO_0F		equ (1 shl 19)
RA2C		equ (1 shl 20)	;Repeat after 2 cyles.
RA4C		equ (1 shl 21)	;Repeat after 4 cyles.
BF_EX1_PIPE	equ (1 shl 22)	;If branch fused, op to EX1, else op to EX0 | EX1.
LNOTE15		equ (1 shl 23)	;This is the execution latency for the instruction. 
							;The time to complete the external write depends on the memory
							;speed and the hardware implementation.
LNOTE14		equ (1 shl 24)	;The low half of the result is available one cycle earlier than listed.
MODE64		equ (1 shl 25)
ADDR16		equ (1 shl 26)
ADDR32		equ (1 shl 27)
LNOTE13		equ (1 shl 28)	;The high half of the result is available one cycle earlier than listed.
LNOTE9		equ (1 shl 29)	;First op to AG0 | AG1, Second to EX0 | EX1.
NORES		equ (LNOTE5)	;No resources mapped.
LNOTE16		equ (1 shl 30)	;The three latency numbers represent the latency values 
							;for precision control settings of single precision, double
							;precision, and extended precision, respectively.
J32NOF		equ (1 shl 31)
;ModrmType
MODREGREG	equ (1 shl 0)
MODREGMEM	equ (1 shl 1)
LNOTE17		equ (1 shl 2)	;2. These instructions have an effective latency as shown.
							;However, these instructions generate an internal NOP
							;with a latency of two cycles but no related dependencies. 
							;These internal NOPs can be executed at a rate of
							;three per cycle and can use any of the three execution resources.
LNOTE18		equ (1 shl 3)	;3. This is a VectorPath decoded operation that uses one execution pipe (one ROP).
LNOTE19		equ (1 shl 4)	;4. There is additional latency associated with this instruction. 
							;“e” represents the difference between the exponents
							;of the divisor and the dividend. If “s” is the number 
							;of normalization shifts performed on the result, then
							;n = (s+1)/2 where (0 <= n <= 32).
LNOTE20		equ (1 shl 5)	;5. The latency provided for this operation is the best-case latency.
MBL			equ (1 shl 6)
VEX_SEC66	equ (1 shl 7)
;Pipes
EX0_PIPE	equ (1 shl 0)
EX1_PIPE	equ (1 shl 1)
AG0_PIPE	equ (1 shl 2)
AG1_PIPE	equ (1 shl 3)
P0_PIPE		equ (1 shl 4)
P1_PIPE		equ (1 shl 5)
P2_PIPE		equ (1 shl 6)
P3_PIPE		equ (1 shl 7)
UNV_PIPE	equ (1 shl 8)
MAL_PIPE	equ (1 shl 9)
XBR_PIPE	equ (1 shl 10)
FMA_PIPE	equ (1 shl 11)
MC_PIPE		equ (1 shl 12)
CVT_PIPE	equ (1 shl 13)
MMA_PIPE	equ (1 shl 14)
STO_PIPE	equ (1 shl 15)
FADD_PIPE	equ (1 shl 16)
FMUL_PIPE	equ (1 shl 17)
FSTORE_PIPE	equ (1 shl 18)
NONE_PIPE	equ (1 shl 19)
EX0_EX1		equ (EX0_PIPE or EX1_PIPE)
AG0_AG1		equ (AG0_PIPE or AG1_PIPE)
EX_AG01		equ (EX0_EX1 or AG0_AG1)
FADD_FMUL	equ (FADD_PIPE or FMUL_PIPE)
FADD_MUL_ST	equ (FADD_FMUL or FSTORE_PIPE)
XBR_P1		equ (XBR_PIPE or P1_PIPE)
MAL_P2_P3	equ (MAL_PIPE or P2_PIPE or P3_PIPE)
CVT_P0		equ (CVT_PIPE or P0_PIPE)
STO_P3		equ (STO_PIPE or P3_PIPE)
FMA_P0_P1	equ (FMA_PIPE or P0_PIPE or P1_PIPE)
MMA_P0		equ (MMA_PIPE or P0_PIPE)
FMA_P0		equ (FMA_PIPE or P0_PIPE)
XBR_P1_FMA_P0		equ (XBR_P1 or FMA_P0)
FMA_P0_P1_STO_P3	equ (FMA_P0_P1 or STO_P3)
XBR_P1_CVT_P0		equ (XBR_P1 or CVT_P0)
CVT_P0_STO_P3		equ (CVT_P0 or STO_P3)
XBR_P1_STO_P3		equ (XBR_P1 or STO_P3)
MAL_P2_P3_XBR_P1	equ (MAL_P2_P3 or XBR_P1)
CVT_P0_FMA_P0_P1	equ (FMA_P0_P1 or CVT_P0)
;DecodeType
DEC_1P	equ (1 shl 0)
DEC_2P	equ (1 shl 1)
DEC_VC	equ (1 shl 2)
DEC_MC	equ (1 shl 3)
ltn struc
	FirstPfx	BYTE ?
	FirstByte	BYTE ?
	SecondByte	BYTE ?
	ModrmType	BYTE ?
	Pipes		DWORD ?
	DecodeType	WORD ?
	Latency		QWORD ?
	Latency2	QWORD ?
	Throughput	WORD ?
	Flags		DWORD ?
ltn ends
PLTN TYPEDEF PTR ltn
LAT_ATHLON		equ (1 shl 0)
LAT_BULLDOZER	equ (1 shl 1)
PCNTX TYPEDEF PTR cntx
ReadContext TYPEDEF PROTO Cntx:PVOID,lpDest:PVOID,__size:ULONG64,Selector:WORD,MemOffset:QWORD,dwFlags:DWORD
PREAD_CONTEXT TYPEDEF PTR ReadContext
cntx struc
	ReadMemCallback	PREAD_CONTEXT ?
	Context			PCONTEXT ?
	lpVoid			PVOID ?
cntx ends
curr_id=1
enum ch_cpl,callgate

LPEF TYPEDEF PTR EF
LPExceptProps TYPEDEF PTR ExceptProps
LPMediaException TYPEDEF PTR MediaException
LPX87Exception TYPEDEF PTR X87Exception
lpx87c TYPEDEF PTR lpx87c
;register encoding
;The registers available in all modes.
;32-bit GPRs
GPR_EAX equ 0
GPR_EBX equ 3
GPR_ECX equ 1
GPR_EDX equ 2
GPR_ESI equ 6
GPR_EDI equ 7
GPR_EBP equ 5
GPR_ESP equ 4
;16-bit GPRs
GPR_AX equ 0
GPR_BX equ 3
GPR_CX equ 1
GPR_DX equ 2
GPR_SI equ 6
GPR_DI equ 7
GPR_BP equ 5
GPR_SP equ 4
;8-bit GPRs
GPR_AL equ 0
GPR_BL equ 3
GPR_CL equ 1
GPR_DL equ 2
;Not addressable when a REX prefix is used.
GPR_AH equ 4
GPR_BH equ 7
GPR_CH equ 5
GPR_DH equ 6
;The registers accessible in 64-bit mode.
;64-bit GPRs
GPR_RAX equ 0
GPR_RBX equ 3
GPR_RCX equ 1
GPR_RDX equ 2
GPR_RSI equ 6
GPR_RDI equ 7
GPR_RBP equ 5
GPR_RSP equ 4
GPR_R8 equ 8
GPR_R9 equ 9
GPR_R10 equ 10
GPR_R11 equ 11
GPR_R12 equ 12
GPR_R13 equ 13
GPR_R14 equ 14
GPR_R15 equ 15
;32-bit GPRs
GPR_R8d equ 8
GPR_R9d equ 9
GPR_R10d equ 10
GPR_R11d equ 11
GPR_R12d equ 12
GPR_R13d equ 13
GPR_R14d equ 14
GPR_R15d equ 15
;16-bit GPRs
GPR_R8w equ 8
GPR_R9w equ 9
GPR_R10w equ 10
GPR_R11w equ 11
GPR_R12w equ 12
GPR_R13w equ 13
GPR_R14w equ 14
GPR_R15w equ 15
;8-bit GPRs
GPR_R8b equ 8
GPR_R9b equ 9
GPR_R10b equ 10
GPR_R11b equ 11
GPR_R12b equ 12
GPR_R13b equ 13
GPR_R14b equ 14
GPR_R15b equ 15
;Only addressable when a REX prefix is used.
GPR_SIL equ 6
GPR_DIL equ 7
GPR_BPL equ 5
GPR_SPL equ 4

ID_ES equ 0
ID_CS equ 1
ID_SS equ 2
ID_DS equ 3
ID_FS equ 4
ID_GS equ 5
MIN_ASM_PASSES	equ 2
STD_MAX_PASSES	equ 30
ipr struc
	hBase		HANDLE ?	;00h
	hInstr		HINSTR ?	;08h
	incp		PINCPATH ?	;10h
	root_ind	ULONG64 ?	;18h
	src_ind		ULONG64 ?	;20h
	err_ind		ULONG64 ?	;28h
	pm_ind		ULONG64 ?	;30h
	msi			ULONG64 ?	;38h
	hKern		HMODULE ?	;40h
	hNt			HMODULE ?	;48h
	hDsmh		HMODULE ?	;50h
	hDsmb		HMODULE ?	;58h
	GetMH		PVOID ?		;60h
	GetPA		PVOID ?		;68h
	HeapAlloc	PVOID ?		;70h
	HeapReAlloc PVOID ?		;78h
	hHeap		HANDLE ?	;80h
	CreateFile	PVOID ?		;88h
	ReadFile	PVOID ?		;90h
	WriteFile	PVOID ?		;98h
	CloseHandle	PVOID ?		;0A0h
	ProcessEquations	ULONG64 ?	;0A8h
	GetComma	PVOID ?		;0B0h
	IntToStr	PVOID ?		;0B8h
	HeapFree	PVOID ?		;0C0h
	IsQwordReg	PVOID ?		;0C8h
	IsDwordReg	PVOID ?		;0D0h
	IsWordReg	PVOID ?		;0D8h
	IsByteReg	PVOID ?		;0E0h
	EvalExpr128	PVOID ?		;0E8h
	EvalExpr256	PVOID ?		;0F0h
	SetDefaultOperType	PVOID ?	;0F8h
	SkipComment	PVOID ?		;100h
	TrimComment	PVOID ?		;108h
	LoadLib		PVOID ?		;110h
	ProcessTextEqs	PVOID ?	;118h
	DsmCtrl		DWORD ?		;120h
	Mode		BYTE ?		;124h
	Filler		BYTE ?		;125h
	wFlags		WORD ?		;126h
	AlterBase	QWORD ?		;128h
	fs_ind		ULONG64 ?	;130h
	GetSharedFunc	PVOID ?	;138h
	GetTextEqValue	PVOID ?	;140h
	SelValidLN		PVOID ?	;148h
ipr ends
PINCPARSE	TYPEDEF PTR ipr
curr_id=0
enf P_MACRO,F_SHARED
curr_id=0
enf   NOT_ALLOWED,INDEFINITE_MEANING
enf       STD_LOCK,        TPR_ACCESS,   STD_REPNE,    STD_REP,  STD_REPE,    OPC_MOD,  OPC_MOD66,  REP_NOP
enf   STD_XACQUIRE,      STD_XRELEASE,  STD_OPSIZE,  STD_ASIZE,  STD_CX_W,    STD_SEG,   DS_ANNIH
enf     STD_LOCK_F,      TPR_ACCESS_F, STD_REPNE_F,  STD_REP_F,STD_REPE_F,  OPC_MOD_F,OPC_MOD66_F,REP_NOP_F
enf STD_XACQUIRE_F,    STD_XRELEASE_F,STD_OPSIZE_F,STD_ASIZE_F,STD_CX_W_F,  STD_SEG_F,   SS_ANNIH

STD_CX_WA_F	equ (STD_ASIZE_F or STD_CX_W_F)
STD_CX_WA	equ (STD_ASIZE or STD_CX_W)

M_F0_F		equ (STD_LOCK_F or TPR_ACCESS_F)
M_F2F3_F	equ (STD_REPNE_F or STD_REP_F or STD_REPE_F or OPC_MOD_F or REP_NOP_F or STD_XACQUIRE_F or STD_XRELEASE_F)
M_66_F		equ (STD_OPSIZE_F or OPC_MOD66_F)
M_67_F		equ (STD_ASIZE_F or STD_CX_W_F)
M_SEG_F		equ STD_SEG_F
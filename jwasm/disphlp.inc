
;;--------------------------------------------------------------------
;;--- helper macros for IDispatch
;;---
;;--- PLEASE NOTE: you are not forced to use or understand the
;;--- macros inside this file. There exist some different degrees of
;;--- COM support which you may use or not. A brief overview follows:
;;---
;;--- 1. use the COMView generated standard includes, but
;;---    define your own helper macros (BEGIN_INTERFACE, STDMETHOD,...)
;;---
;;--- 2. + use the base include files supplied (OBJBASE.INC, UNKNWN.INC,
;;---    OAIDL.INC). With that you may call vtable methods with macro vf() 
;;---
;;--- 3. + use COMView generated "dispatch helper" includes, but define
;;---    your own macros DEFINE_DISPMETHOD,... so you dont need DISPHLP.INC.
;;---
;;--- 4. + use include file DISPHLP.INC and use macros dm() for calling 
;;---    dispatchonly methods and place macro DEFINE_INVOKEHELPER in your code.
;;---
;;--- 5. + use event support from DISPHLP.INC, that is 
;;---    define event tables with BEGIN_EVENTS, DEFINE_DISPEVENT and
;;---    END_EVENT + place DEFINE_EVENTHELPER somewhere in your code.
;;--------------------------------------------------------------------

;;--------------------------------------------------------------------
;;--- calling IDispatch::Invoke support macros:
;;--- dm()					: calls method of dispatch interface
;;--- GETTYPEFROMVT vt:req	: used internally
;;--- GETSIZEFROMVT vt:req	: used internally
;;--- DEFINE_DISPMETHOD		: defines helper textequates for a dispatch method
;;--- DEFINE_INVOKEHELPER	: defines InvokeHelper proc for dispatch calls
;;--------------------------------------------------------------------

;;--------------------------------------------------------------------
;;--- Event support
;;--- macros to simplify implementing event sinks:
;;--- BEGIN_EVENTS
;;--- END_EVENTS
;;--- DEFINE_DISPEVENT
;;--- DEFINE_EVENTHELPER
;;--- macros to simplify fireing events:
;;--- DEFINE_FIREEVENTHELPER
;;--- FIREEVENT
;;--------------------------------------------------------------------

;;--------------------------------------------------------------------
;;--- other macros:
;;--- dmx() - may replace dm() macro
;;--- DEFINEEXECUTEINVOKE - helpers for dmx()
;;--------------------------------------------------------------------

ifndef NO_DEFINE_DUMMY_PROCS 
NO_DEFINE_DUMMY_PROCS = 0		;that's used by macro DEFINE_DISPMETHOD
endif

;-------------------------------------------------------------------
; dm() calls a method/property of an dispatchonly interface
; which means to call IDispatch::Invoke finally. Since that function
; requires some type translation of arguments, a helper proc
; InvokeHelper is called which does that work. For this job
; InvokeHelper needs some metadata which every call will have
; to supply. This metadata is defined here, so just data of
; methods called by the program will be defined. The correspondant
; string equates however are defined by macro DEFINE_DISPMETHOD.
;-------------------------------------------------------------------
; About the metadata: it will be located in section _TEXT$03,
; so at the end it will settle down behind the other code
;-------------------------------------------------------------------
; usage: "invoke dm(pInterface,Interface,Function)<,arguments>"
;-------------------------------------------------------------------
	
dm macro this:req, interface, func:req
ifndef &interface&_&func&MDData
_TEXT$03	segment dword public 'CODE'
&interface&_&func&MDData label byte
	dd &interface&_&func&DispId
	dw &interface&_&func&MD
_TEXT$03	ends
extern DEFINE_INVOKEHELPER_is_missing:abs
endif
;;	mov edx, offset &interface&_&func&MDData
	exitm <&interface&_&func&, addr &interface&_&func&MDData, this>
	endm


;;----------------------------------------------------------------------
;; GETTYPEFROMVT: thats to define parameter string of a proc 
;; Since we have only the VT_xxx types available, we must translate
;; them to types MASM will understand.
;; Theres no need for special handling of the 1, 2 or 4 byte sizes
;; Just ensure the 8 (VT_R8, VT_CY and VT_DATE) and 16 (VT_VARIANT) byte
;; sizes are taken care of.    
;;----------------------------------------------------------------------

GETTYPEFROMVT macro vt:req
if ((vt) AND VT_BYREF)
  if LOW(vt) eq VT_VARIANT
	exitm <ptr VARIANT>
  elseif LOW(vt) eq VT_BOOL
	exitm <ptr BOOL>
  elseif LOW(vt) eq VT_BSTR
	exitm <ptr BSTR>
  elseif LOW(vt) eq VT_I4
	exitm <ptr SDWORD>
  elseif LOW(vt) eq VT_DISPATCH
	exitm <ptr LPDISPATCH>
  else
	exitm <PTR>
  endif
elseif (vt) eq VT_I4
	exitm <SDWORD>
elseif (vt) eq VT_VARIANT
	exitm <VARIANT>
elseif (vt) eq VT_R8
	exitm <REAL8>
elseif (vt) eq VT_CY
	exitm <QWORD>
elseif (vt) eq VT_DATE
	exitm <QWORD>
elseif (vt) eq VT_BSTR
	exitm <BSTR>
elseif (vt) eq VT_BOOL
	exitm <BOOL>
elseif (vt) eq VT_DISPATCH
	exitm <LPDISPATCH>
else
	exitm <DWORD>
endif
	endm


;;----------------------------------------------------------------------
;; GETSIZEFROMVT: returns size of a VT_xxx type.
;; here the 1 and 2 byte sizes need special handling since
;; the size may be used for a copy operation
;;----------------------------------------------------------------------

GETSIZEFROMVT macro vt:req
ifidni <vt>,<VT_VARIANT>
	exitm <16>
elseifidni <vt>,<VT_R8>
	exitm <8>
elseifidni <vt>,<VT_CY>
	exitm <8>
elseifidni <vt>,<VT_DATE>
	exitm <8>
elseifidni <vt>,<VT_I2>
	exitm <2>
elseifidni <vt>,<VT_UI2>
	exitm <2>
elseifidni <vt>,<VT_BOOL>
	exitm <2>
elseifidni <vt>,<VT_I1>
	exitm <1>
elseifidni <vt>,<VT_UI1>
	exitm <1>
else
	exitm <4>
endif
	endm

;;----------------------------------------------------------------------
;; DEFINE_DISPMETHOD: this macro defines some text equates, no code or data.
;; the real code or data will be defined by macro dm(), on a per function
;; base. The data is used by InvokeHelper to assemble an IDispatch::Invoke call.
;;
;; Now what's done here? 
;; 1. do a (dummy) PROC definition with all parameters
;; 2. define a metadata textequate which describes what to do for InvokeHelper.
;; 3. define a dispid textequate
;;----------------------------------------------------------------------
;; the locals are:
;; i = number of arguments
;; parm = holds one argument at a time
;; ??ArgString: argument string, i.e. <arg1:DWORD, arg2:VARIANT,arg3:ptr VARIANT>
;; ??ArgType: argument types: <VT_UI4, V_VARIANT>
;; ??RetSize: return parameter size, i.e <4> or <0>
;; ??RetString: return parameter string, i.e <pRet: ptr VARIANT> or <>
;; ??RetType: return parameter type, i.e <VT_UI4> or <0>
;;----------------------------------------------------------------------
;; the globals are:
;; &interface&_&method&DispId:	DispId of this method/property
;; &interface&_&method&MD:		metadata string of this method/property
;; &interface&_&method&Type:	function type of this method/property (for dmx())
;; &interface&_&method&Args:	argument string of this method/property
;;----------------------------------------------------------------------
;; To increase compile speed there exist 2 equates,
;; NO_DEFINE_DUMMY_PROCS and DEFINE_PUBLIC_DUMMY_PROCS.
;; To use any of them is useful only with very large includes, where
;; compile speed becomes an issue.
;; Setting NO_DEFINE_DUMMY_PROCS to 1 will prohibit DEFINE_DISPMETHOD
;; from defining dummy procs and define prototypes instead, which will
;; increase compile speed. (The dummy procs have a length of zero and
;; just exist to fool MASM so the invoke type checking will work.)
;; But the linker now won't find these symbols. So to resolve these
;; references you'll need to make another source file where to set
;; DEFINE_PUBLIC_DUMMY_PROCS = 1. With that switch on dummy procs
;; are generated and made public.
;;----------------------------------------------------------------------

;;--- defining less locals speeds up compile time

DEFINE_DISPMETHOD macro interface, method:req, dispid:req, functype:req, rettype, args:VARARG
local i, parm
;;local i, parm, ??ArgString, ??ArgType, ??RetSize, ??RetString, ??RetType

??ArgString textequ <>
??ArgType textequ <>
i = 1
for parm,<args>
??ArgType CatStr ??ArgType,%parm,<,>
??ArgString CatStr ??ArgString,<, arg>,%i,<:>,<GETTYPEFROMVT(parm)>
i = i + 1
    endm

i = i - 1

ifnb <rettype>
??RetString textequ <, pRet:ptr GETTYPEFROMVT(rettype)>
??RetType	textequ %rettype
??RetSize	textequ <GETSIZEFROMVT(rettype)>
else
??RetString	textequ <>
??RetType	textequ <0>
??RetSize	textequ <0>
endif

&interface&_&method&DispId	equ <dispid>
&interface&_&method&Type	textequ %DISPATCH_&functype&
&interface&_&method&MD		CatStr %i,<,>,??ArgType,??RetType,<,>,%DISPATCH_&functype&,<,>,??RetSize
&interface&_&method&Args	CatStr <th:LPDISPATCH>,??ArgString,??RetString

if NO_DEFINE_DUMMY_PROCS gt 0
&interface&_&method proto :ptr,:LPDISPATCH ??ArgString ??RetString
else
_TEXT$02	segment dword public 'CODE'
ifdef DEFINE_PUBLIC_DUMMY_PROCS
&interface&_&method proc public pMD:ptr, pDisp:LPDISPATCH ??ArgString ??RetString
else
&interface&_&method proc pMD:ptr, pDisp:LPDISPATCH ??ArgString ??RetString
endif
&interface&_&method endp
_TEXT$02	ends
endif

	endm


;;----------------------------------------------------------------------
;; DEFINE_INVOKEHELPER: this macro defines proc InvokeHelper
;; its in a macro so COMView can define it with one line
;; and it can be changed without changing COMVIEW
;;----------------------------------------------------------------------
;; what should be kept in mind: this proc is to reside in section 
;; _TEXT$02$1. The dummy procs defined by DEFINE_DISPMETHOD will
;; reside in section _TEXT$02, so they will come before InvokeHelper
;; Thats important, without that properly defined the code will crash!
;;----------------------------------------------------------------------
;; InvokeHelper is used in conjunction with macro dm()
;;----------------------------------------------------------------------

DEFINE_INVOKEHELPER macro
local ??pMetaData, ??pDispatch, ??Arg1

ifndef INVOKEHELPER_DEFINED

INVOKEHELPER_DEFINED equ 1

_TEXT$02$1	segment dword public 'CODE'

;----------------------------------------------------------------------
; stubepilogue: now the only purpose is to clean up stack 
; inside InvokeHelper proc. So its a local macro now
;----------------------------------------------------------------------

stubepilogue macro procname,flag,parmbyte,localbyte,reglist,userparms
	for r,reglist
		pop r
	endm
	mov		ecx,[ebp+4]
	mov		ebp,[ebp+0]
	mov		esp, edx
	jmp		ecx
	endm
	
	OPTION EPILOGUE: stubepilogue

;;--- InvokeHelper first parameter is a ptr to metadata:
;;--- metadata struct
;;---	dispid DWORD ?		;member ID
;;---	numargs WORD ?		;number of arguments
;;---	argtype WORD [numargs] dup (?) ;types of arguments
;;---	rettype WORD ?		;type of return
;;---	functype WORD ? 	;DISPATCH_METHOD, DISPATCH_PROPERTYGET, ...
;;---	size of ret:WORD ?	;size in bytes of return argument
;;--- metadata ends
;;
;; ebp is:	[ebp+00]=old ebp
;;			[ebp+04]=return addr 
;;			[ebp+08]=ptr metadata
;;			[ebp+12]=pDispatch
;;			[ebp+16]=1. argument

??pMetaData	textequ <[ebp+08]>
??pDispatch	textequ <[ebp+12]>
??Arg1		textequ <[ebp+16]>

InvokeHelper proc c uses ebx esi edi

local pRet:DWORD
local dwESP:DWORD
local dwOrgESP:DWORD
local dwPropPutId:DWORD
local DispParams:DISPPARAMS

public DEFINE_INVOKEHELPER_is_missing	;make sure InvokeHelper will be included
DEFINE_INVOKEHELPER_is_missing	equ 0

	mov dwESP, esp
	mov esi, ??pMetaData
	lea edx, ??Arg1
;;------------------------------- 1. get DISPID
	lodsd
	mov ebx, eax
;;------------------------------- 2. assemble the VARIANT argument array	
;;-------------------------------    copy data from pArgs
	lodsw
	movzx eax, ax	
	mov ecx, eax
	mov DispParams.cArgs, eax
	.while (ecx)
		sub esp, sizeof VARIANT
		lodsw 
		mov [esp].VARIANT.vt, ax
		xchg edx, esi
		lea edi, [esp+8]
		.if (ax & VT_BYREF)
			movsd
		.elseif (ax == VT_VARIANT)
			sub edi, 8
			movsd
			movsd
			movsd
			movsd
		.elseif (ax == VT_R8 || ax == VT_DATE || ax == VT_CY)
			movsd
			movsd
		.else
;;------------------------------- handle all parameters with size 1, 2 or 4 here
			movsd
		.endif
		xchg esi, edx
		dec ecx
	.endw
	mov DispParams.rgvarg, esp

;;------------------------------- 3. setup a return parameter if required

	lodsw						; get type of ret (HIWORD(eax) is cleared)
	.if (eax)
		sub esp, sizeof VARIANT
		mov edi, esp
		mov [esp].VARIANT.vt, ax
		mov ecx,[edx]
		mov pRet, ecx
		add edx, 4
	.else
		xor edi, edi
	.endif
	mov dwOrgESP, edx
;;------------------------------- 4. get method type, set named argument

	lodsw
	mov ecx, eax
	.if ((ecx == DISPATCH_PROPERTYPUT) || (ecx == DISPATCH_PROPERTYPUTREF))
		mov dwPropPutId, DISPID_PROPERTYPUT
		lea eax, dwPropPutId
		mov DispParams.rgdispidNamedArgs, eax
		mov DispParams.cNamedArgs, 1
	.else
		mov DispParams.cNamedArgs, 0
	.endif



;;------------------------------- 5. call IDispatch::Invoke

	invoke vf(??pDispatch, IDispatch, Invoke_), ebx, addr IID_NULL,\
		LOCALE_SYSTEM_DEFAULT, ecx, addr DispParams, edi, NULL, NULL

;;------------------------------- the variant array isnt cleared!!!


	.if (eax == S_OK && edi)
;;------------------------------- 6. copy returned data to ret param
;;-------------------------------    don't change EAX here
		movzx ecx, word ptr [esi];get size of ret
		mov esi, edi
		mov edi,pRet
;;------------------------------- if its a VARIANT, copy all 16 bytes
		.if (ecx <= 8)
;;------------------------------- else copy 8,4,2 or 1 bytes 
			add esi,8
		.endif
		mov dl,cl
		shr ecx, 2
		rep movsd
		mov cl,dl
		and cl, 3
		rep movsb
	.endif
;;------------------------------- 7. restore ESP (thats needed!)
	mov esp, dwESP
	mov edx, dwOrgESP
	ret
InvokeHelper endp

_TEXT$02$1	ends

	OPTION EPILOGUE: epiloguedef

endif

	endm

;---------------------------------------------------------------------
;--- BEGIN_EVENTS
;--- defines start of an event tab
;--- such a tab consists of entries containing 2 DWORDS,
;--- which is the metadata ptr defined from macro DEFINE_DISPMETHOD
;--- and the address of the event handling proc
;--------------------------------------------------------------------

BEGIN_EVENTS macro name
??Interface equ <name>
&name&_EventTab	label dword
	endm

;--------------------------------------------------------------------
;--- END_EVENTS
;--- marks end of an event tab
;--------------------------------------------------------------------

END_EVENTS macro
	dd -1
??Interface equ <>
	endm

;--------------------------------------------------------------------
;--- DEFINE_DISPEVENT
;--- defines 1 entry in an Event tab
;--- the prototypes defined here provide for parameter checking
;--------------------------------------------------------------------

DEFINE_DISPEVENT macro method:req, eventproc, xInterface

ifnb <xInterface>

ifndef <xInterface&_&method&MDData>
_TEXT$03	segment dword public 'CODE'
&xInterface&_&method&MDData label byte
	dd &xInterface&_&method&DispId
	dw &xInterface&_&method&MD
_TEXT$03	ends
endif

%	dd xInterface&_&method&MDData

ifnb <eventproc>
	dd eventproc
%eventproc proto &xInterface&_&method&Args
else
%	dd _&xInterface&_&method&
%_&xInterface&_&method& proto &xInterface&_&method&Args
endif

else

ifndef <??Interface&_&method&MDData>
_TEXT$03	segment dword public 'CODE'
%&??Interface&_&method&MDData label byte
%	dd &??Interface&_&method&DispId
%	dw &??Interface&_&method&MD
_TEXT$03	ends
endif

%	dd ??Interface&_&method&MDData

ifnb <eventproc>
	dd eventproc
%eventproc proto &??Interface&_&method&Args
else
%	dd _&??Interface&_&method&
%_&??Interface&_&method& proto &??Interface&_&method&Args
endif

endif

	endm

;--------------------------------------------------------------------
;--- DEFINE_FIREEVENTHELPER
;--- this macro defines a helper proc called by macro FIREEVENT.
;--- please note that for these helper procs to work
;--- connection points must implement method EnumConnections!
;--------------------------------------------------------------------

ifndef FIREEVENTHELPER_INCLUDED

DEFINE_FIREEVENTHELPER macro

FIREEVENTHELPER_INCLUDED equ 1

		.code

;--------------------------------------------------------------------------
;--- send an event to all connected sinks of an ConnectionPoint
;--------------------------------------------------------------------------

DispatchEvent proc public pConnectionPoint: LPCONNECTIONPOINT, dwDispId:DWORD,
				dwType:DWORD, pDispParams:ptr DISPPARAMS, pRet:ptr VARIANT

local	pEnumConnections:LPENUMCONNECTIONS
local	pDispatch:LPDISPATCH
local	rc:dword

    mov rc, E_FAIL
	.if (pConnectionPoint)
		invoke vf(pConnectionPoint, IConnectionPoint, EnumConnections), addr pEnumConnections
		.if (eax == S_OK)
			.while (1)
				invoke vf(pEnumConnections, IEnumConnections, Next), 1, addr pDispatch, NULL
				.break .if (eax != S_OK)
				invoke vf(pDispatch, IDispatch, Invoke_),\
					dwDispId, addr IID_NULL, LOCALE_USER_DEFAULT,\
					dwType, pDispParams, pRet, NULL, NULL
                mov rc, eax
				invoke vf(pDispatch, IDispatch, Release)
			.endw
			invoke vf(pEnumConnections, IEnumConnections, Release)
		.endif
	.endif
    mov eax, rc
	ret

DispatchEvent endp


FireEvent proc c public uses ebx esi edi pMetaData:ptr, pConnectionPoint:LPCONNECTIONPOINT, parms:VARARG

local	dwESP:DWORD
local	pRet:DWORD
local	dwPropPutId:DWORD
local	DispParams:DISPPARAMS

	mov dwESP, esp
	mov esi, pMetaData	
	lea edx, parms
;;------------------------------- 1. get DISPID
	lodsd
	mov ebx, eax
;;------------------------------- 2. assemble the VARIANT argument array	
;;-------------------------------    copy data from pArgs
	lodsw
	movzx eax, ax	
	mov ecx, eax
	mov DispParams.cArgs, eax
	.while (ecx)
		sub esp, sizeof VARIANT
		lodsw 
		mov [esp].VARIANT.vt, ax
		xchg edx, esi
		lea edi, [esp+8]
		.if (ax & VT_BYREF)
			movsd
		.elseif (ax == VT_VARIANT)
			sub edi, 8
			movsd
			movsd
			movsd
			movsd
		.elseif (ax == VT_R8 || ax == VT_DATE || ax == VT_CY)
			movsd
			movsd
		.else
;;------------------------------- handle all parameters with size 1, 2 or 4 here
			movsd
		.endif
		xchg esi, edx
		dec ecx
	.endw
	mov DispParams.rgvarg, esp

;;------------------------------- 3. setup a return parameter if required

	lodsw						; get type of ret (HIWORD(eax) is cleared)
	.if (eax)
		sub esp, sizeof VARIANT
		mov edi, esp
		mov [esp].VARIANT.vt, ax
		mov ecx,[edx]
		mov pRet, ecx
		add edx, 4
	.else
		xor edi, edi
	.endif
;;------------------------------- 4. get method type, set named argument

	lodsw
	mov ecx, eax
	.if ((ecx == DISPATCH_PROPERTYPUT) || (ecx == DISPATCH_PROPERTYPUTREF))
		mov dwPropPutId, DISPID_PROPERTYPUT
		lea eax, dwPropPutId
		mov DispParams.rgdispidNamedArgs, eax
		mov DispParams.cNamedArgs, 1
	.else
		mov DispParams.cNamedArgs, 0
	.endif



;;------------------------------- 5. call DispatchEvent
;;------------------------------- ebx=DISPID
;;------------------------------- ecx=method type
;;------------------------------- edi=ptr RetArg:VARIANT

	invoke DispatchEvent, pConnectionPoint, ebx, ecx, addr DispParams, edi

;;------------------------------- 5a. remember, the variant array isnt cleared!

	.if (eax == S_OK && edi)
;;------------------------------- 6. copy returned data to ret param
;;-------------------------------    don't change EAX here
		movzx ecx, word ptr [esi];get size of ret
		mov esi, edi
		mov edi,pRet
;;------------------------------- if its a VARIANT, copy all 16 bytes
		.if (ecx <= 8)
;;------------------------------- else copy 8,4,2 or 1 bytes 
			add esi,8
		.endif
		mov dl,cl
		shr ecx, 2
		rep movsd
		mov cl,dl
		and cl, 3
		rep movsb
	.endif
;;------------------------------- 7. restore ESP (thats needed!)
	mov esp, dwESP
	ret

FireEvent endp

	endm

endif

;--------------------------------------------------------------------------
;--- FIREEVENT: fires an event
;--- used by servers to notify client of an event (dispinterface)
;--- macro DEFINE_FIREEVENTHELPER has to be included into the source
;--------------------------------------------------------------------------

FIREEVENT macro this:req, interface, func
ifndef &interface&_&func&MDData
_TEXT$03	segment dword public 'CODE'
&interface&_&func&MDData label byte
	dd &interface&_&func&DispId
	dw &interface&_&func&MD
_TEXT$03	ends
endif
	exitm <FireEvent, addr &interface&_&func&MDData, this>
	endm


;--------------------------------------------------------------------
;--- DEFINE_EVENTHELPER:
;--- this macro defines a IDispatch interface for event handling
;--- it is rather large.
;--------------------------------------------------------------------


DEFINE_EVENTHELPER	macro 
local DispatchVtbl

;--- the CEvents structure (should not be accessed from outside)

CEvents		struct
_IDispatch	IDispatch	<>
ObjRefCount	DWORD		?
pThis		LPVOID		?	;the "this" ptr from Create@CEvents
pCP			LPUNKNOWN	?	;the connection point we are connected with
dwCookie	DWORD		?	;the cookie we get from ::Advise
pEventTab	LPDWORD		?	;the event tab from Connect@CEvents
EventIID	IID			<>	;the source IID from Connect@CEvents
CEvents		ends

__this	textequ <ebx>
_this	textequ <[__this].CEvents>

	MEMBER _IDispatch, ObjRefCount, pThis, pCP, dwCookie, pEventTab, EventIID

	.const

DispatchVtbl	IDispatchVtbl {\
		QueryInterface@CEvents, AddRef@CEvents, Release@CEvents,\
		GetTypeInfoCount@CEvents, GetTypeInfo@CEvents,\
		GetIDsOfNames@CEvents, Invoke@CEvents}

	.code

Disconnect@CEvents	proto :ptr CEvents
AddRef@CEvents		proto :ptr CEvents

;--------------------------------------------------------------------
;--- constructor. The pUnknown parameter may be NULL. The event procs
;---   will receive it at (first) LPDISPATCH parameter
;--------------------------------------------------------------------

Create@CEvents	proc uses __this pThis:LPVOID

	invoke LocalAlloc, LMEM_FIXED, sizeof CEvents
	.if (!eax)
		ret
	.endif
	mov __this, eax
	mov m__IDispatch.lpVtbl, offset DispatchVtbl
	mov m_ObjRefCount, 1
	mov eax, pThis
	.if (!eax)
		mov eax, __this
	.endif
	mov m_pThis, eax
;;--------------------- dont assume it is a COM object
;;	.if (eax)
;;		invoke vf(eax, IUnknown, AddRef)
;;	.endif
	mov m_pCP, NULL
	mov m_dwCookie, 0
	mov m_pEventTab, NULL
	return __this

Create@CEvents	endp

;--------------------------------------------------------------------
;--- destructor
;--------------------------------------------------------------------

Destroy@CEvents	proc uses __this this_:ptr CEvents
    mov __this,this_
	.if (m_pCP)
		.if (m_dwCookie)
			invoke Disconnect@CEvents, __this
		.endif
		invoke vf(m_pCP, IUnknown, Release)
		mov m_pCP, NULL
	.endif
;;	.if (m_pUnknown)
;;		invoke vf(m_pUnknown, IUnknown, Release)
;;		mov m_pUnknown, NULL
;;	.endif
	invoke LocalFree, this_
	ret
Destroy@CEvents	endp


QueryInterface@CEvents proc uses __this esi edi this_:ptr CEvents, riid:ptr IID, ppReturn:ptr ptr

if 0; ifdef _DEBUG
local	wszIID[40]:word
local	szKey[128]:byte
local	dwSize:DWORD
local	hKey:HANDLE
endif

    mov __this,this_

	mov eax, S_OK
	mov	esi, offset IID_IUnknown	;is it IUnknown?
	mov edx, riid
	mov edi, edx
	mov ecx, 4
	repz cmpsd
	jz	Found
	mov	esi, offset IID_IDispatch	;is it IDispatch?
	mov edi, edx
	mov cl, 4
	repz cmpsd
	jz	Found
	lea	esi, m_EventIID				;or is it the one we are created for?
	mov edi, edx
	mov cl, 4
	repz cmpsd
	jz	Found
	xor edx, edx
	mov eax, E_NOINTERFACE
	jmp exit
Found:
	invoke AddRef@CEvents, __this
	mov edx, __this
	mov eax, S_OK
exit:
	mov ecx, ppReturn
	mov [ecx], edx

if 0; ifdef _DEBUG
;--------------------- print the name of the interface we have just been queried
    push eax
	invoke StringFromGUID2,riid, addr wszIID, LENGTHOF wszIID
	invoke wsprintf, addr szKey, CStr("Interface\%S"),addr wszIID
	invoke RegOpenKeyEx, HKEY_CLASSES_ROOT, addr szKey, 0, KEY_READ, addr hKey 
	.if (eax == ERROR_SUCCESS)
		mov dwSize, sizeof szKey
		invoke RegQueryValueEx,hKey,CStr(""),NULL,NULL,addr szKey,addr dwSize
		invoke RegCloseKey, hKey
	.else
		mov szKey,0
	.endif
    pop eax
	DebugOut "CEvents::QueryInterface(%S[%s])=%X", addr wszIID, addr szKey, eax
endif
	ret

QueryInterface@CEvents endp


AddRef@CEvents proc uses __this this_:ptr CEvents

	mov __this,this_
	inc m_ObjRefCount

;	DebugOut "CEvents::AddRef Count=%u", m_ObjRefCount

	mov eax, m_ObjRefCount
	ret

AddRef@CEvents endp


Release@CEvents proc uses __this this_:ptr CEvents

	mov __this,this_
	dec m_ObjRefCount

;	DebugOut "CEvents::Release Count=%u", m_ObjRefCount

	mov eax, m_ObjRefCount
	.if (eax == 0)
		invoke Destroy@CEvents, __this
		xor eax,eax
	.endif
	ret

Release@CEvents endp

;--------------------------------------------------------------------
;--- define IConnectionPoint + IConnectionPointContainer
;--- in case ocidl.inc is not included
;--------------------------------------------------------------------

ifndef IConnectionPointVtbl
externdef stdcall IID_IConnectionPoint:IID
BEGIN_INTERFACE IConnectionPoint, IUnknown
	STDMETHOD		GetConnectionInterface	,:ptr IID
	STDMETHOD		GetConnectionPointContainer	,:ptr ptr
	STDMETHOD		Advise				,:ptr IUnknown,:ptr dword
	STDMETHOD		Unadvise			,:dword
	STDMETHOD		EnumConnections		,:ptr ptr
END_INTERFACE
endif

ifndef IConnectionPointContainerVtbl
externdef stdcall IID_IConnectionPointContainer:IID
BEGIN_INTERFACE IConnectionPointContainer, IUnknown
	STDMETHOD		EnumConnectionPoints,:ptr ptr
	STDMETHOD		FindConnectionPoint	,:ptr IID,:ptr ptr IConnectionPoint
END_INTERFACE
endif

;--------------------------------------------------------------------
;--- this IDispatch interface is for events only
;--- so the caller has the typeinfo and should not expect
;--- to get it from us.
;--------------------------------------------------------------------

GetTypeInfoCount@CEvents proc this_:ptr CEvents, pctinfo:ptr DWORD
    return E_NOTIMPL
GetTypeInfoCount@CEvents endp

GetTypeInfo@CEvents proc this_:ptr CEvents, iTInfo:DWORD, lcid:LCID, ppTInfo:ptr LPTYPEINFO
    return E_NOTIMPL
GetTypeInfo@CEvents endp

GetIDsOfNames@CEvents proc this_:ptr CEvents, riid:ptr IID, rgszNames:DWORD, cNames:DWORD, lcid:LCID, rgDispId:ptr DISPID
    return DISP_E_UNKNOWNINTERFACE
GetIDsOfNames@CEvents endp

;--------------------------------------------------------------------
;--- IDispatch::Invoke here is were all events come in first
;--------------------------------------------------------------------

Invoke@CEvents proc uses esi edi __this this_:ptr CEvents, dispIdMember:DISPID, riid:ptr IID,
		lcid:LCID, wFlags:DWORD, pDispParams:ptr DISPPARAMS,
		pVarResult:ptr VARIANT, pExcepInfo:DWORD, puArgErr:ptr DWORD

local dwESP:DWORD
local dwNumArgs:DWORD
local varTemp:VARIANT
local dwArgErr:DWORD

    mov __this,this_

if 0;ifdef _DEBUG
	DebugOut "CEvents::Invoke(%X,%X,%X,%X,%X,%X,%X,%X)", dispIdMember,\
		riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr
	mov eax,pDispParams
	assume eax:ptr DISPPARAMS
	.if (eax)
		DebugOut "  DispParams={%X,%X,%X,%X}", [eax].rgvarg,\
			[eax].rgdispidNamedArgs, [eax].cArgs, [eax].cNamedArgs
	.endif
	mov eax,pVarResult
	assume eax:ptr VARIANT
	.if (eax)
		movzx ecx,[eax].vt
		DebugOut "  VarResult={%X,%X}", ecx,[eax].lVal
	.endif
	assume eax:nothing
endif

;--------------------------------------------------------------------
;--- now scan if an event proc is defined for the DISP-ID
;--------------------------------------------------------------------

	mov ecx, m_pEventTab
	mov eax, dispIdMember
	.while (dword ptr [ecx] != -1)
		mov esi,[ecx]
		.if (eax == [esi])
			mov dwESP, esp
			add esi, sizeof DWORD
			lodsw						;number of arguments
			movzx eax, ax
			mov dwNumArgs, eax
			mov ax,[esi+eax*2]
			.if (ax)
				mov eax, pVarResult
				.if (eax)
					push [eax+8]
				.else
					push 0
				.endif
			.endif
			mov edi, dwNumArgs
			mov edx, pDispParams
			mov edx, [edx].DISPPARAMS.rgvarg
			.while (edi)
				mov ax, [esi+edi*2-2]
				.if (ax == VT_VARIANT)
					push dword ptr [edx+12]
					push dword ptr [edx+08]
					push dword ptr [edx+04]
					push dword ptr [edx+00]
				.elseif ((ax == VT_R8) || (ax == VT_DATE) || (ax == VT_CY))
					push dword ptr [edx+12]
					push dword ptr [edx+08]
				.else
					push dword ptr [edx+08]
				.endif
				dec edi
				add edx, sizeof VARIANT
			.endw
			push m_pThis
			call dword ptr [ecx+4]			;call the event proc
			jmp exit
		.endif
		add ecx, 2 * sizeof DWORD
	.endw
	mov eax, DISP_E_MEMBERNOTFOUND
exit:
	ret

Invoke@CEvents endp


;--------------------------------------------------------------------
;--- Connect@CEvents: the main routine called from outside
;--- this will establish a connection.
;--- parameters are:
;---  this_: thats our object we get with Create@CEvents()
;---  pUnknown: thats an IUnknown ptr from our client which we will ask
;---       for connections
;---  pIID: thats the interface we are interested in
;---  pEventTab: thats an eventtab we have declared with macros BEGIN_EVENTS ...
;--------------------------------------------------------------------

Connect@CEvents	proc uses __this esi edi this_:ptr CEvents, pUnknown:LPUNKNOWN, pIID:ptr IID, pEventTab:LPVOID

local	pCPContainer:ptr IConnectionPointContainer

	mov __this,this_

	.if (m_pCP == NULL)
		invoke vf(pUnknown, IUnknown, QueryInterface), addr IID_IConnectionPointContainer, addr pCPContainer
		.if (eax == S_OK)
			invoke vf(pCPContainer, IConnectionPointContainer, FindConnectionPoint), pIID, addr m_pCP
			.if (eax == S_OK)
				mov esi, pIID
				lea edi, m_EventIID
				movsd
				movsd
				movsd
				movsd
				mov ecx, pEventTab
				mov m_pEventTab, ecx
			.endif
			push eax
			invoke vf(pCPContainer, IUnknown, Release)
			pop eax
		.endif
	.endif

	.if (m_pCP)
		invoke vf(m_pCP, IConnectionPoint, Advise), __this, addr m_dwCookie
	.endif
	ret
Connect@CEvents	endp

;--------------------------------------------------------------------
;--- Disconnect@CEvents: no more events will come in
;--------------------------------------------------------------------

Disconnect@CEvents	proc uses __this this_:ptr CEvents

	mov __this,this_
	.if (m_pCP && m_dwCookie)
		invoke vf(m_pCP, IConnectionPoint, Unadvise), m_dwCookie
		mov m_dwCookie, 0
	.endif
	ret
Disconnect@CEvents	endp

__this	textequ <>
_this	textequ <>

	endm		; end of macro DEFINE_EVENTHELPER


;----------------------------------------------------------------
;--- end of event support macros
;----------------------------------------------------------------


;----------------------------------------------------------------
;--- Here 2 macros are defined, dmx() and DEFINE_EXECUTEINVOKE.
;--- These provides another - optional - way to call methods from 
;--- dispatchonly interfaces. Under some circumstances these
;--- macros may offer slight benefits compared to using macro dm().

;----------------------------------------------------------------
;--- macro dmx() simplifies usage of ExecuteInvoke (see below)
;--- since one doesnt have to remember DISPID and function type
;--- of the method/property
;---
;--- example how to get cell(1,1) of current worksheet in excel:
;---
;--- 1. prepare for execution (will populate VARIANT array varArray)
;--- PrepareInvoke(addr varArray, 2, VT_I4, 1, VT_I4, 1)
;---
;--- 2. execute IDispatch::Invoke
;--- dmx(pObject, Range, get_Item), VT_DISPATCH, addr pResult, addr varArray
;---
;--- pResult may hold a VT_DISPATCH object now on success.
;----------------------------------------------------------------

dmx macro this:req, interface, func:req
	exitm <ExecuteInvoke, this, &interface&_&func&DispId, &interface&_&func&Type>
	endm

;------------------------------------------------------------------
; DEFINE_EXECUTEINVOKE defines procs PrepareInvoke & ExecuteInvoke
; if you want to use these procs (or macro dmx()) you will have to
; place this macro in your code.
;------------------------------------------------------------------

DEFINE_EXECUTEINVOKE macro

ifndef EXECUTEINVOKE_DEFINED

EXECUTEINVOKE_DEFINED equ 1

PrepareInvoke PROTO C :ptr VARIANT, :DWORD, :VARARG

ExecuteInvoke PROTO  pDispatch:LPDISPATCH, dwId:DWORD, dwFlag:DWORD,
		w_oVT_TYPE:WORD, pResult:ptr, :ptr VARIANT

	.code

PrepareInvoke PROC C USES esi edi pVariant:ptr VARIANT, cNum:DWORD, args:VARARG

;------------------------------------------------------------------
;--- PrepareInvoke
;--- 
;--- pVariant may be NULL, in which case an array of VARIANTS is
;--- allocated. If the function returns NULL, a memory error has occured.
;--- So to avoid fiddling around with error checking and forgetting
;--- to free memory I would suggest not to use this feature and
;--- supply some space for PrepareInvoke. Just use some locally 
;--- defined VARIANT variables.
;--- In case of success eax holds ptr to start of the VARIANT array
;--- 
;--- IMPORTANT: the VARIANT array for PrepareInvoke must be 1 item
;--- larger than the number of arguments supplied, since last entry
;--- will be filled with VT_EMPTY type to indicate "end of array".
;--- 
;--- Usage:
;--- PrepareInvoke(addr varArray, 2, VT_I4, 1, VT_I4, 1)
;---                              !  !		!  !	  + ...
;---                              !  !		!  + type 2. argument	
;---                              !  !		+ value 1. argument
;---                              !  + type 1. argument
;---                              + number of arguments 
;------------------------------------------------------------------

	mov edi, pVariant
	.if (!edi)
		mov eax, cNum
		inc eax
		mov ecx, sizeof VARIANT
		mul ecx
		invoke LocalAlloc, LMEM_FIXED, eax
		.if (!eax)
			jmp exit
		.endif
		mov edi, eax
		mov pVariant, eax
	.endif
	
	mov ecx, cNum
	mov eax, sizeof VARIANT					;; let edi point to end of array
	mul ecx									;; since arguments should be
	add edi, eax							;; reversed

	mov [edi].VARIANT.vt, VT_EMPTY			;; mark end of array
	lea esi, args							;; Get the arguments pointer

	.while (ecx)
		sub edi, sizeof VARIANT
		lodsd								
		mov [edi].VARIANT.vt,ax				;; copy type
		mov dx,ax
		lodsd								;; copy value
		.if (dx == VT_VARIANT)
			stosd
			movsd
			movsd
			movsd
			sub edi, 16
		.elseif (dx == VT_R8 || dx == VT_DATE || dx == VT_CY)
			mov dword ptr [edi].VARIANT.dblVal+0, eax
			lodsd
			mov dword ptr [edi].VARIANT.dblVal+4, eax
		.else
			mov [edi].VARIANT.lVal, eax
		.endif
		dec ecx
	.endw

	mov eax, pVariant						;; Return the starting pointer to the memory
exit:
	ret
PrepareInvoke ENDP


;--------------------------------------------------------------------------------------------+
; ExecuteInvoke
;
; Use this to call DISPATCHABLE interfaces by means of LATE Binding.
; Instead of calling ExecuteInvoke directly you can use macro dmx()
; which avoids having to remember DISPID & function type
;
;    The params are:
;        pDispatch   :LPDISPATCH  --   Disp Interface pointer
;        dwId        :DWORD       --   Disp. Unique ID of prop/meth
;        dwFlag      :DWORD       --   Either:
;                                         DISPATCH_PROPERTYPUT
;                                         DISPATCH_PROPERTYGET
;                                         DISPATCH_PROPERTYPUTREF
;                                         DISPATCH_METHOD
;        woVT_TYPE   :WORD        --   Return VT_TYPE to expect (Set NULL if not used)
;        lpResult    :DWORD       --   Address to store return  (Set NULL if not used)
;        pVariants   :ptr VARIANT --   Pointer to VARIANT array, possibly created by
;                                      PrepareInvoke.
;
; By NaN (c) 2002 + Japheth.
;--------------------------------------------------------------------------------------------+
ExecuteInvoke PROC uses edi esi pDispatch: LPDISPATCH, dwId:DWORD, dwFlag:DWORD,
				w_oVT_TYPE:WORD, pResult:ptr, pVariants:ptr VARIANT

local dwPropPutId:DWORD
LOCAL iErr:DWORD
local pVarRet:ptr VARIANT
local dispparams:DISPPARAMS
local varReturn:VARIANT

	mov esi, pVariants
	mov dispparams.rgvarg, esi
	mov ecx, 0
	.while ([esi].VARIANT.vt != VT_EMPTY)
		inc ecx
		add esi, sizeof VARIANT
	.endw
	mov dispparams.cArgs, ecx

    mov eax, dwFlag
	.if(( eax == DISPATCH_PROPERTYPUT ) || ( eax == DISPATCH_PROPERTYPUTREF) )
		mov dispparams.cNamedArgs, 1			  ;; Indicate 1 named argument
		mov dwPropPutId, DISPID_PROPERTYPUT 	  ;; Indicate 'get' property call
		lea eax, dwPropPutId					  ;; get the address to this indication
		mov dispparams.rgdispidNamedArgs, eax	  ;; Set the named agrument pointer
	.else
		mov dispparams.cNamedArgs, 0			  ;; Indicate 0 named argument
		mov dispparams.rgdispidNamedArgs, NULL	  ;; Set the named agrument pointer
	.endif

	.if (pResult)
		lea eax, varReturn
		mov pVarRet, eax
		mov ax, w_oVT_TYPE
		mov varReturn.vt, ax
	.else
		mov pVarRet, NULL
	.endif
		
	mov iErr, 0

	invoke vf(pDispatch, IDispatch, Invoke_), dwId, addr IID_NULL, LOCALE_SYSTEM_DEFAULT,\
			dwFlag, addr dispparams, pVarRet, NULL, addr iErr
	  
	.if ((eax == S_OK) && pVarRet)
		movzx eax, w_oVT_TYPE
		lea esi, varReturn
;----------------------- Modify the Return to what we asked for
		invoke VariantChangeType, esi, esi, NULL, eax
		mov edi, pResult
		mov ax, w_oVT_TYPE
		.if (ax == VT_VARIANT)
			movsd
			movsd
			movsd
			movsd
		.else
			lea esi,[esi.VARIANT.lVal]
			.if (( ax == VT_R8 ) || (ax  == VT_CY ) || (ax == VT_DATE))
				movsd
				movsd
			.elseif ((ax == VT_UI2) || (ax == VT_I2))
				movsw
			.elseif ((ax == VT_UI1) || (ax == VT_I1))
				movsb
			.else
				movsd
			.endif
		.endif
		mov eax, S_OK
	.endif
	mov edx, iErr				;; Set EDX to any error returned
	ret

ExecuteInvoke ENDP

endif

	endm


;;--- end of file

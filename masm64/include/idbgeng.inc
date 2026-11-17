externdef IID_IDebugAdvanced:GUID
externdef IID_IDebugAdvanced2:GUID
externdef IID_IDebugAdvanced3:GUID
externdef IID_IDebugBreakpoint:GUID
externdef IID_IDebugBreakpoint2:GUID
externdef IID_IDebugClient:GUID
externdef IID_IDebugClient2:GUID
externdef IID_IDebugClient3:GUID
externdef IID_IDebugClient4:GUID
externdef IID_IDebugClient5:GUID
externdef IID_IDebugControl:GUID
externdef IID_IDebugControl2:GUID
externdef IID_IDebugControl3:GUID
externdef IID_IDebugControl4:GUID
externdef IID_IDebugDataSpaces:GUID
externdef IID_IDebugDataSpaces2:GUID
externdef IID_IDebugDataSpaces3:GUID
externdef IID_IDebugDataSpaces4:GUID
externdef IID_IDebugEventCallbacks:GUID
externdef IID_IDebugEventCallbacksWide:GUID
externdef IID_IDebugInputCallbacks:GUID
externdef IID_IDebugOutputCallbacks:GUID
externdef IID_IDebugOutputCallbacksWide:GUID
externdef IID_IDebugOutputCallbacks2:GUID
externdef IID_IDebugRegisters:GUID
externdef IID_IDebugRegisters2:GUID
externdef IID_IDebugSymbolGroup:GUID
externdef IID_IDebugSymbolGroup2:GUID
externdef IID_IDebugSymbols:GUID
externdef IID_IDebugSymbols2:GUID
externdef IID_IDebugSymbols3:GUID
externdef IID_IDebugSystemObjects:GUID
externdef IID_IDebugSystemObjects2:GUID
externdef IID_IDebugSystemObjects3:GUID
externdef IID_IDebugSystemObjects4:GUID
DEBUG_READ_USER_MINIDUMP_STREAM STRUC
	StreamType	ULONG ?
	Flags		ULONG ?
	_Offset		ULONG64 ?
	Buffer		PVOID ?
	BufferSize	ULONG ?
	BufferUsed	ULONG ?
DEBUG_READ_USER_MINIDUMP_STREAM ENDS
PDEBUG_READ_USER_MINIDUMP_STREAM TYPEDEF PTR DEBUG_READ_USER_MINIDUMP_STREAM
DEBUG_GET_TEXT_COMPLETIONS_NO_DOT_COMMANDS			equ 1
DEBUG_GET_TEXT_COMPLETIONS_NO_EXTENSION_COMMANDS	equ 2
DEBUG_GET_TEXT_COMPLETIONS_NO_SYMBOLS				equ 4
DEBUG_GET_TEXT_COMPLETIONS_IN STRUC
	Flags			ULONG ?
	MatchCountLimit	ULONG ?
	Reserved		ULONG64 3 dup(?)
DEBUG_GET_TEXT_COMPLETIONS_IN ENDS
PDEBUG_GET_TEXT_COMPLETIONS_IN TYPEDEF PTR DEBUG_GET_TEXT_COMPLETIONS_IN
DEBUG_GET_TEXT_COMPLETIONS_IS_DOT_COMMAND			equ 1
DEBUG_GET_TEXT_COMPLETIONS_IS_EXTENSION_COMMAND		equ 2
DEBUG_GET_TEXT_COMPLETIONS_IS_SYMBOL				equ 4
DEBUG_GET_TEXT_COMPLETIONS_OUT STRUC
	Flags			ULONG ?
	ReplaceIndex	ULONG ?
	MatchCount		ULONG ?
	Reserved1		ULONG ?
	Reserved2		ULONG64 2 dup(?)
DEBUG_GET_TEXT_COMPLETIONS_OUT ENDS
PDEBUG_GET_TEXT_COMPLETIONS_OUT TYPEDEF PTR DEBUG_GET_TEXT_COMPLETIONS_OUT
DEBUG_CACHED_SYMBOL_INFO STRUC
	ModBase	ULONG64 ?
	Arg1	ULONG64 ?
	Arg2	ULONG64 ?
	Id		ULONG ?
	Arg3	ULONG ?
DEBUG_CACHED_SYMBOL_INFO ENDS
PDEBUG_CACHED_SYMBOL_INFO TYPEDEF PTR DEBUG_CACHED_SYMBOL_INFO
DEBUG_REQUEST_SOURCE_PATH_HAS_SOURCE_SERVER				equ 0
DEBUG_REQUEST_TARGET_EXCEPTION_CONTEXT					equ 1
DEBUG_REQUEST_TARGET_EXCEPTION_THREAD					equ 2
DEBUG_REQUEST_TARGET_EXCEPTION_RECORD					equ 3
DEBUG_REQUEST_GET_ADDITIONAL_CREATE_OPTIONS				equ 4
DEBUG_REQUEST_SET_ADDITIONAL_CREATE_OPTIONS				equ 5
DEBUG_REQUEST_GET_WIN32_MAJOR_MINOR_VERSIONS			equ 6
DEBUG_REQUEST_READ_USER_MINIDUMP_STREAM					equ 7
DEBUG_REQUEST_TARGET_CAN_DETACH							equ 8
DEBUG_REQUEST_SET_LOCAL_IMPLICIT_COMMAND_LINE			equ 9
DEBUG_REQUEST_GET_CAPTURED_EVENT_CODE_OFFSET			equ 10
DEBUG_REQUEST_READ_CAPTURED_EVENT_CODE_STREAM			equ 11
DEBUG_REQUEST_EXT_TYPED_DATA_ANSI						equ 12
DEBUG_REQUEST_GET_EXTENSION_SEARCH_PATH_WIDE			equ 13
DEBUG_REQUEST_GET_TEXT_COMPLETIONS_WIDE					equ 14
DEBUG_REQUEST_GET_CACHED_SYMBOL_INFO					equ 15
DEBUG_REQUEST_ADD_CACHED_SYMBOL_INFO					equ 16
DEBUG_REQUEST_REMOVE_CACHED_SYMBOL_INFO					equ 17
DEBUG_REQUEST_GET_TEXT_COMPLETIONS_ANSI					equ 18
DEBUG_REQUEST_CURRENT_OUTPUT_CALLBACKS_ARE_DML_AWARE	equ 19
DEBUG_REQUEST_GET_OFFSET_UNWIND_INFORMATION				equ 20
DEBUG_REQUEST_GET_DUMP_HEADER							equ 21
DEBUG_REQUEST_SET_DUMP_HEADER							equ 22
DEBUG_REQUEST_MIDORI									equ 23
DEBUG_REQUEST_PROCESS_DESCRIPTORS						equ 24
DEBUG_REQUEST_MISC_INFORMATION							equ 25
DEBUG_REQUEST_OPEN_PROCESS_TOKEN						equ 26
DEBUG_REQUEST_OPEN_THREAD_TOKEN							equ 27
DEBUG_REQUEST_DUPLICATE_TOKEN							equ 28
DEBUG_REQUEST_QUERY_INFO_TOKEN							equ 29
DEBUG_REQUEST_CLOSE_TOKEN								equ 30
DEBUG_SRCFILE_SYMBOL_TOKEN								equ 0
DEBUG_SRCFILE_SYMBOL_TOKEN_SOURCE_COMMAND_WIDE			equ 1
DEBUG_SYMINFO_BREAKPOINT_SOURCE_LINE					equ 0
DEBUG_SYMINFO_IMAGEHLP_MODULEW64						equ 1
DEBUG_SYMINFO_GET_SYMBOL_NAME_BY_OFFSET_AND_TAG_WIDE	equ 2
DEBUG_SYMINFO_GET_MODULE_SYMBOL_NAMES_AND_OFFSETS		equ 3
DEBUG_SYSOBJINFO_THREAD_BASIC_INFORMATION				equ 0
DEBUG_SYSOBJINFO_THREAD_NAME_WIDE						equ 1
DEBUG_SYSOBJINFO_CURRENT_PROCESS_COOKIE					equ 2
DEBUG_TBINFO_EXIT_STATUS								equ 1
DEBUG_TBINFO_PRIORITY_CLASS								equ 2
DEBUG_TBINFO_PRIORITY									equ 4
DEBUG_TBINFO_TIMES										equ 8
DEBUG_TBINFO_START_OFFSET								equ 16
DEBUG_TBINFO_AFFINITY									equ 32
DEBUG_TBINFO_ALL										equ 3Fh
DEBUG_THREAD_BASIC_INFORMATION STRUC
	Valid			ULONG ?
	ExitStatus		ULONG ?
	PriorityClass	ULONG ?
	Priority		ULONG ?
	CreateTime		ULONG64 ?
	ExitTime		ULONG64 ?
	KernelTime		ULONG64 ?
	UserTime		ULONG64 ?
	StartOffset		ULONG64 ?
	Affinity		ULONG64 ?
DEBUG_THREAD_BASIC_INFORMATION ENDS
PDEBUG_THREAD_BASIC_INFORMATION TYPEDEF PTR DEBUG_THREAD_BASIC_INFORMATION
IDebugAdvanced STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetThreadContext			PANYARGS ?
	SetThreadContext			PANYARGS ?
	Request						PANYARGS ?
	GetSourceFileInformation	PANYARGS ?
	FindSourceFileAndToken		PANYARGS ?
	GetSymbolInformation		PANYARGS ?
	GetSystemObjectInformation	PANYARGS ?
	GetSourceFileInformationWide	PANYARGS ?	;IDebugAdvanced3
	FindSourceFileAndTokenWide	PANYARGS ?
	GetSymbolInformationWide	PANYARGS ?
IDebugAdvanced ENDS
PDEBUG_ADVANCED TYPEDEF PTR IDebugAdvanced
PDADV TYPEDEF PTR PDEBUG_ADVANCED
DEBUG_BREAKPOINT_CODE		equ 0
DEBUG_BREAKPOINT_DATA		equ 1
DEBUG_BREAKPOINT_TIME		equ 2
DEBUG_BREAKPOINT_GO_ONLY	equ 1
DEBUG_BREAKPOINT_DEFERRED	equ 2
DEBUG_BREAKPOINT_ENABLED	equ 4
DEBUG_BREAKPOINT_ADDER_ONLY	equ 8
DEBUG_BREAKPOINT_ONE_SHOT	equ 16
DEBUG_BREAK_READ			equ 1
DEBUG_BREAK_WRITE			equ 2
DEBUG_BREAK_EXECUTE			equ 4
DEBUG_BREAK_IO				equ 8
DEBUG_BREAKPOINT_PARAMETERS STRUC
	_Offset					ULONG64 ?
	Id						ULONG ?
	BreakType				ULONG ?
	ProcType				ULONG ?
	Flags					ULONG ?
	DataSize				ULONG ?
	DataAccessType			ULONG ?
	PassCount				ULONG ?
	CurrentPassCount		ULONG ?
	MatchThread				ULONG ?
	CommandSize				ULONG ?
	OffsetExpressionSize	ULONG ?
DEBUG_BREAKPOINT_PARAMETERS ENDS
PDEBUG_BREAKPOINT_PARAMETERS TYPEDEF PTR DEBUG_BREAKPOINT_PARAMETERS
IDebugBreakpoint STRUC
	QueryInterface				QUERYPROC ?	;+0
	Addref						ADDPROC   ?	;+8
	Release						RELEASEPROC ?	;+10h
	GetId						PANYARGS ?		;+18h
	GetType						PANYARGS ?		;+20h
	GetAdder					PANYARGS ?		;+28h
	GetFlags					PANYARGS ?		;+30h
	AddFlags					PANYARGS ?		;+38h
	RemoveFlags					PANYARGS ?		;+40h
	SetFlags					PANYARGS ?		;+48h
	GetOffset					PANYARGS ?		;+50h
	SetOffset					PANYARGS ?
	GetDataParameters			PANYARGS ?	;—¬Œ…—“¬¿ Œ—“¿ÕŒ¬Œ¬ Õ¿ œ¿Ãﬂ“‹
	SetDataParameters			PANYARGS ?
	GetPassCount				PANYARGS ?
	SetPassCount				PANYARGS ?
	GetCurrentPassCount			PANYARGS ?
	GetMatchThreadId			PANYARGS ?
	SetMatchThreadId			PANYARGS ?
	GetCommand					PANYARGS ?
	SetCommand					PANYARGS ?
	GetOffsetExpression			PANYARGS ?
	SetOffsetExpression			PANYARGS ?
	GetParameters				PANYARGS ?
	GetCommandWide				PANYARGS ?	;IDebugBreakpoint2
	SetCommandWide				PANYARGS ?
	GetOffsetExpressionWide		PANYARGS ?
	SetOffsetExpressionWide		PANYARGS ?
IDebugBreakpoint ENDS
PDEBUG_BREAKPOINT TYPEDEF PTR IDebugBreakpoint
PDBREAK TYPEDEF PTR PDEBUG_BREAKPOINT
DEBUG_ATTACH_KERNEL_CONNECTION	equ 0
DEBUG_ATTACH_LOCAL_KERNEL		equ 1
DEBUG_ATTACH_EXDI_DRIVER		equ 2
DEBUG_ATTACH_INSTALL_DRIVER		equ 4
DEBUG_GET_PROC_DEFAULT			equ 0
DEBUG_GET_PROC_FULL_MATCH		equ 1
DEBUG_GET_PROC_ONLY_MATCH		equ 2
DEBUG_GET_PROC_SERVICE_NAME		equ 4
DEBUG_PROC_DESC_DEFAULT			equ 0
DEBUG_PROC_DESC_NO_PATHS		equ 1
DEBUG_PROC_DESC_NO_SERVICES		equ 2
DEBUG_PROC_DESC_NO_MTS_PACKAGES	equ 4
DEBUG_PROC_DESC_NO_COMMAND_LINE	equ 8
DEBUG_PROC_DESC_NO_SESSION_ID	equ 16
DEBUG_PROC_DESC_NO_USER_NAME	equ 32
DEBUG_ATTACH_DEFAULT					equ 0
DEBUG_ATTACH_NONINVASIVE				equ 1
DEBUG_ATTACH_EXISTING					equ 2
DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND		equ 4
DEBUG_ATTACH_INVASIVE_NO_INITIAL_BREAK	equ 8
DEBUG_ATTACH_INVASIVE_RESUME_PROCESS	equ 16
DEBUG_ATTACH_NONINVASIVE_ALLOW_PARTIAL	equ 32
DEBUG_CREATE_PROCESS_NO_DEBUG_HEAP		equ CREATE_UNICODE_ENVIRONMENT
DEBUG_CREATE_PROCESS_THROUGH_RTL		equ STACK_SIZE_PARAM_IS_A_RESERVATION
DEBUG_ECREATE_PROCESS_DEFAULT					equ 0
DEBUG_ECREATE_PROCESS_INHERIT_HANDLES			equ 1
DEBUG_ECREATE_PROCESS_USE_VERIFIER_FLAGS		equ 2
DEBUG_ECREATE_PROCESS_USE_IMPLICIT_COMMAND_LINE	equ 4
DEBUG_CREATE_PROCESS_OPTIONS STRUC
	CreateFlags		ULONG ?
	EngCreateFlags	ULONG ?
	VerifierFlags	ULONG ?
	Reserved		ULONG ?
DEBUG_CREATE_PROCESS_OPTIONS ENDS
PDEBUG_CREATE_PROCESS_OPTIONS TYPEDEF PTR DEBUG_CREATE_PROCESS_OPTIONS
DEBUG_PROCESS_DETACH_ON_EXIT		equ 1
DEBUG_PROCESS_ONLY_THIS_PROCESS		equ 2
DEBUG_CONNECT_SESSION_DEFAULT		equ 0
DEBUG_CONNECT_SESSION_NO_VERSION	equ 1
DEBUG_CONNECT_SESSION_NO_ANNOUNCE	equ 2
DEBUG_SERVERS_DEBUGGER				equ 1
DEBUG_SERVERS_PROCESS				equ 2
DEBUG_SERVERS_ALL					equ 3
DEBUG_END_PASSIVE					equ 0
DEBUG_END_ACTIVE_TERMINATE			equ 1
DEBUG_END_ACTIVE_DETACH				equ 2
DEBUG_END_REENTRANT					equ 3
DEBUG_END_DISCONNECT				equ 4
DEBUG_OUTPUT_NORMAL					equ 1
DEBUG_OUTPUT_ERROR					equ 2
DEBUG_OUTPUT_WARNING				equ 4
DEBUG_OUTPUT_VERBOSE				equ 8
DEBUG_OUTPUT_PROMPT					equ 10h
DEBUG_OUTPUT_PROMPT_REGISTERS		equ 20h
DEBUG_OUTPUT_EXTENSION_WARNING		equ 40h
DEBUG_OUTPUT_DEBUGGEE				equ 80h
DEBUG_OUTPUT_DEBUGGEE_PROMPT		equ 100h
DEBUG_OUTPUT_SYMBOLS				equ 200h
DEBUG_OUTPUT_ALL					equ 3FFh
DEBUG_IOUTPUT_KD_PROTOCOL			equ 80000000h
DEBUG_IOUTPUT_REMOTING				equ 40000000h
DEBUG_IOUTPUT_BREAKPOINT			equ 20000000h
DEBUG_IOUTPUT_EVENT					equ 10000000h
DEBUG_IOUTPUT_ADDR_TRANSLATE		equ 8000000h
DEBUG_OUTPUT_IDENTITY_DEFAULT		equ 0
DEBUG_FORMAT_DEFAULT								equ 0
DEBUG_FORMAT_CAB_SECONDARY_ALL_IMAGES				equ 10000000h
DEBUG_FORMAT_WRITE_CAB								equ 20000000h
DEBUG_FORMAT_CAB_SECONDARY_FILES					equ 40000000h
DEBUG_FORMAT_NO_OVERWRITE							equ 80000000h
DEBUG_FORMAT_USER_SMALL_FULL_MEMORY					equ 1
DEBUG_FORMAT_USER_SMALL_HANDLE_DATA					equ 2
DEBUG_FORMAT_USER_SMALL_UNLOADED_MODULES			equ 4
DEBUG_FORMAT_USER_SMALL_INDIRECT_MEMORY				equ 8
DEBUG_FORMAT_USER_SMALL_DATA_SEGMENTS				equ 10h
DEBUG_FORMAT_USER_SMALL_FILTER_MEMORY				equ 20h
DEBUG_FORMAT_USER_SMALL_FILTER_PATHS				equ 40h
DEBUG_FORMAT_USER_SMALL_PROCESS_THREAD_DATA			equ 80h
DEBUG_FORMAT_USER_SMALL_PRIVATE_READ_WRITE_MEMORY	equ 100h
DEBUG_FORMAT_USER_SMALL_NO_OPTIONAL_DATA			equ 200h
DEBUG_FORMAT_USER_SMALL_FULL_MEMORY_INFO			equ 400h
DEBUG_FORMAT_USER_SMALL_THREAD_INFO					equ 800h
DEBUG_FORMAT_USER_SMALL_CODE_SEGMENTS				equ 1000h
DEBUG_FORMAT_USER_SMALL_NO_AUXILIARY_STATE			equ 2000h
DEBUG_FORMAT_USER_SMALL_FULL_AUXILIARY_STATE		equ 4000h
DEBUG_FORMAT_USER_SMALL_IGNORE_INACCESSIBLE_MEM		equ 8000000h
DEBUG_DUMP_FILE_BASE								equ 0FFFFFFFFh
DEBUG_DUMP_FILE_PAGE_FILE_DUMP						equ 0
DEBUG_DUMP_FILE_LOAD_FAILED_INDEX	equ 0FFFFFFFFh
DEBUG_DUMP_FILE_ORIGINAL_CAB_INDEX	equ 0FFFFFFFEh
IDebugClient STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	AttachKernel				PANYARGS ?	;¬€¡Œ– “»œ¿ —Œ≈ƒ»Õ≈Õ»ﬂ
	GetKernelConnectionOptions	PANYARGS ?
	SetKernelConnectionOptions	PANYARGS ?	;Õ¿—“–Œ… ¿ œ¿–¿Ã≈“–Œ¬ —Œ≈ƒ»Õ≈Õ»ﬂ
	StartProcessServer			PANYARGS ?	;”ƒ¿À®ÕÕ€… «¿œ”—  œ–Œ÷≈——Œ¬
	ConnectProcessServer		PANYARGS ?
	DisconnectProcessServer		PANYARGS ?
	GetRunningProcessSystemIds	PANYARGS ?	;œ≈–≈◊»—À≈Õ»≈ » œŒÀ”◊≈Õ»≈ —¬Œ…—“¬ ƒŒ—“”œÕ€’ œ–Œ÷≈——Œ¬
	GetRunningProcessSystemIdByExecutableName	PANYARGS ?
	GetRunningProcessDescription				PANYARGS ?
	AttachProcess				PANYARGS ?	;œŒƒ Àﬁ◊≈Õ»≈   œŒÀ‹«Œ¬¿“≈À‹— »Ã œ–Œ÷≈——¿Ã
	CreateProcess				PANYARGS ?	;«¿œ”—  ÕŒ¬Œ√Œ œ–Œ÷≈——¿ ƒÀﬂ Œ“À¿ƒ »
	CreateProcessAndAttach		PANYARGS ?
	GetProcessOptions			PANYARGS ?	;”œ–¿¬À≈Õ»≈  ŒÕ“–ŒÀ‹Õ€Ã» ‘À¿√¿Ã» œ–Œ÷≈——¿
	AddProcessOptions			PANYARGS ?
	RemoveProcessOptions		PANYARGS ?
	SetProcessOptions			PANYARGS ?
	OpenDumpFile				PANYARGS ?	;”œ–¿¬À≈Õ»≈ ‘¿…À¿Ã» ƒ¿Ãœ¿
	WriteDumpFile				PANYARGS ?
	ConnectSession				PANYARGS ?	;√Œ“Œ¬ÕŒ—“‹  À»≈Õ“¿ œ–»Õ»Ã¿“‹ ”◊¿—“»≈ ¬ —≈——»»
	StartServer					PANYARGS ?	;œ–»Õﬂ“»≈ ”ƒ¿À®ÕÕ€’ —Œ≈ƒ»Õ≈Õ»…
	OutputServers				PANYARGS ?	;œŒÀ”◊≈Õ»≈ —œ»— ¿ «¿œ”Ÿ≈ÕÕ€’ —À”∆¡
	TerminateProcesses			PANYARGS ?	;«¿¬≈–ÿ≈Õ»≈ ¬—≈’ œ–Œ÷≈——Œ¬ »« —œ»— ¿ Œ“À¿ƒ◊» ¿
	DetachProcesses				PANYARGS ?	;Œ“ Àﬁ◊≈Õ»≈ Œ“À¿ƒ◊» ¿ Œ“ ¬—≈’ œ–Œ÷≈——Œ¬
	EndSession					PANYARGS ?	;«¿¬≈–ÿ≈Õ»≈ —≈——»»
	GetExitCode					PANYARGS ?	; Œƒ «¿¬≈–ÿ≈Õ»ﬂ œ–Œ÷≈——¿
	DispatchCallbacks			PANYARGS ?	;œ≈–≈ƒ¿◊¿ »Õ‘Œ–Ã¿÷»» Œ —Œ¡€“»ﬂ’  À»≈Õ“— »Ã ‘”Õ ÷»ﬂÃ
	ExitDispatch				PANYARGS ?
	CreateClient				PANYARGS ?	;CO«ƒ¿Õ»≈ ÕŒ¬Œ√Œ  À»≈Õ“— Œ√Œ Œ¡⁄≈ “¿ ƒÀﬂ “–›ƒ¿
	GetInputCallbacks			PANYARGS ?
	SetInputCallbacks			PANYARGS ?
	GetOutputCallbacks			PANYARGS ?	;”œ–¿¬À≈Õ»≈  À»≈Õ“— »Ã» »Õ“≈–‘≈…—¿Ã»
	SetOutputCallbacks			PANYARGS ?
	GetOutputMask				PANYARGS ?
	SetOutputMask				PANYARGS ?
	GetOtherOutputMask			PANYARGS ?
	SetOtherOutputMask			PANYARGS ?
	GetOutputWidth				PANYARGS ?
	SetOutputWidth				PANYARGS ?
	GetOutputLinePrefix			PANYARGS ?	;Ã≈“Œƒ€ ”œ–¿¬À≈Õ»ﬂ ¬€¬ŒƒŒÃ »Õ‘Œ–Ã¿÷»»
	SetOutputLinePrefix			PANYARGS ?
	GetIdentity					PANYARGS ?	;œŒÀ”◊≈Õ»≈ »Õ‘Œ–Ã¿÷»» Œ  À»≈Õ“≈
	OutputControl				PANYARGS ?
	GetEventCallbacks			PANYARGS ?	;”œ–¬À≈Õ»≈  À»≈“— »Ã» ‘”Õ ÷»ﬂÃ» Œ¡–¿¡Œ“ » —Œ¡€“»…
	SetEventCallbacks			PANYARGS ?
	FlushCallbacks				PANYARGS ?
	WriteDumpFile2				PANYARGS ?	;”œ–¿¬À≈Õ»≈ ‘¿…À¿Ã» ƒ¿Ãœ¿ IDebugClient2
	AddDumpInformationFile		PANYARGS ?
	EndProcessServer			PANYARGS ?	;”œ–¿¬À≈Õ»≈ —≈–¬≈–ŒÃ
	WaitForProcessServerEnd		PANYARGS ?
	IsKernelDebuggerEnabled		PANYARGS ?
	TerminateCurrentProcess		PANYARGS ?
	AbandonCurrentProcess		PANYARGS ?
	GetRunningProcessSystemIdByExecutableNameWide	PANYARGS ?	;IDebugClient3
	GetRunningProcessDescriptionWide	PANYARGS ?
	CreateProcessWide					PANYARGS ?
	CreateProcessAndAttachWide			PANYARGS ?
	OpenDumpFileWide					PANYARGS ?	;IDebugClient4
	WriteDumpFileWide					PANYARGS ?
	AddDumpInformationFileWide			PANYARGS ?
	GetNumberDumpFiles					PANYARGS ?
	GetDumpFile							PANYARGS ?
	GetDumpFileWide						PANYARGS ?
	AttachKernelWide					PANYARGS ?	;IDebugClient5
	GetKernelConnectionOptionsWide		PANYARGS ?
	SetKernelConnectionOptionsWide		PANYARGS ?
	StartProcessServerWide				PANYARGS ?
	ConnectProcessServerWide			PANYARGS ?
	StartServerWide						PANYARGS ?
	OutputServersWide					PANYARGS ?
	GetOutputCallbacksWide				PANYARGS ?
	SetOutputCallbacksWide				PANYARGS ?
	GetOutputLinePrefixWide				PANYARGS ?
	SetOutputLinePrefixWide				PANYARGS ?
	GetIdentityWide						PANYARGS ?
	OutputIdentityWide					PANYARGS ?
	GetEventCallbacksWide				PANYARGS ?
	SetEventCallbacksWide				PANYARGS ?
	CreateProcess2						PANYARGS ?
	CreateProcess2Wide					PANYARGS ?
	CreateProcessAndAttach2				PANYARGS ?
	CreateProcessAndAttach2Wide			PANYARGS ?
	PushOutputLinePrefix				PANYARGS ?
	PushOutputLinePrefixWide			PANYARGS ?
	PopOutputLinePrefix					PANYARGS ?
	GetNumberInputCallbacks				PANYARGS ?
    GetNumberOutputCallbacks			PANYARGS ?
    GetNumberEventCallbacks				PANYARGS ?
    GetQuitLockString					PANYARGS ?
    SetQuitLockString					PANYARGS ?
    GetQuitLockStringWide				PANYARGS ?
    SetQuitLockStringWide				PANYARGS ?
IDebugClient ENDS
PDEBUG_CLIENT	TYPEDEF PTR IDebugClient
PDCLIENT TYPEDEF PTR PDEBUG_CLIENT
DEBUG_STATUS_NO_CHANGE				equ 0
DEBUG_STATUS_GO						equ 1
DEBUG_STATUS_GO_HANDLED				equ 2
DEBUG_STATUS_GO_NOT_HANDLED			equ 3
DEBUG_STATUS_STEP_OVER				equ 4
DEBUG_STATUS_STEP_INTO				equ 5
DEBUG_STATUS_BREAK					equ 6
DEBUG_STATUS_NO_DEBUGGEE			equ 7
DEBUG_STATUS_STEP_BRANCH			equ 8
DEBUG_STATUS_IGNORE_EVENT			equ 9
DEBUG_STATUS_RESTART_REQUESTED		equ 10
DEBUG_STATUS_REVERSE_GO				equ 11
DEBUG_STATUS_REVERSE_STEP_BRANCH	equ 12
DEBUG_STATUS_REVERSE_STEP_OVER		equ 13
DEBUG_STATUS_REVERSE_STEP_INTO		equ 14
DEBUG_STATUS_MASK					equ 15
DEBUG_STATUS_INSIDE_WAIT			equ 100000000h
DEBUG_STATUS_WAIT_TIMEOUT			equ 200000000h
DEBUG_OUTCTL_THIS_CLIENT			equ 0
DEBUG_OUTCTL_ALL_CLIENTS			equ 1
DEBUG_OUTCTL_ALL_OTHER_CLIENTS		equ 2
DEBUG_OUTCTL_IGNORE					equ 3
DEBUG_OUTCTL_LOG_ONLY				equ 4
DEBUG_OUTCTL_SEND_MASK				equ 7
DEBUG_OUTCTL_NOT_LOGGED				equ 8
DEBUG_OUTCTL_OVERRIDE_MASK			equ 10h
DEBUG_OUTCTL_DML					equ 20h
DEBUG_OUTCTL_AMBIENT_DML			equ 0FFFFFFFEh
DEBUG_OUTCTL_AMBIENT_TEXT			equ 0FFFFFFFFh
DEBUG_OUTCTL_AMBIENT				equ DEBUG_OUTCTL_AMBIENT_TEXT
DEBUG_INTERRUPT_ACTIVE				equ 0
DEBUG_INTERRUPT_PASSIVE				equ 1
DEBUG_INTERRUPT_EXIT				equ 2
DEBUG_CURRENT_DEFAULT				equ 15
DEBUG_CURRENT_SYMBOL				equ 1
DEBUG_CURRENT_DISASM				equ 2
DEBUG_CURRENT_REGISTERS				equ 4
DEBUG_CURRENT_SOURCE_LINE			equ 8
DEBUG_DISASM_EFFECTIVE_ADDRESS				equ 1
DEBUG_DISASM_MATCHING_SYMBOLS				equ 2
DEBUG_DISASM_SOURCE_LINE_NUMBER				equ 4
DEBUG_DISASM_SOURCE_FILE_NAME				equ 8
DEBUG_LEVEL_SOURCE							equ 0
DEBUG_LEVEL_ASSEMBLY						equ 1
DEBUG_ENGOPT_IGNORE_DBGHELP_VERSION			equ 1
DEBUG_ENGOPT_IGNORE_EXTENSION_VERSIONS		equ 2
DEBUG_ENGOPT_ALLOW_NETWORK_PATHS			equ 4
DEBUG_ENGOPT_DISALLOW_NETWORK_PATHS			equ 8
DEBUG_ENGOPT_NETWORK_PATHS					equ (4 or 8)
DEBUG_ENGOPT_IGNORE_LOADER_EXCEPTIONS		equ 10h
DEBUG_ENGOPT_INITIAL_BREAK					equ 20h
DEBUG_ENGOPT_INITIAL_MODULE_BREAK			equ 40h
DEBUG_ENGOPT_FINAL_BREAK					equ 80h
DEBUG_ENGOPT_NO_EXECUTE_REPEAT				equ 100h
DEBUG_ENGOPT_FAIL_INCOMPLETE_INFORMATION	equ 200h
DEBUG_ENGOPT_ALLOW_READ_ONLY_BREAKPOINTS	equ 400h
DEBUG_ENGOPT_SYNCHRONIZE_BREAKPOINTS		equ 800h
DEBUG_ENGOPT_DISALLOW_SHELL_COMMANDS		equ 1000h
DEBUG_ENGOPT_KD_QUIET_MODE					equ 2000h
DEBUG_ENGOPT_DISABLE_MANAGED_SUPPORT		equ 4000h
DEBUG_ENGOPT_DISABLE_MODULE_SYMBOL_LOAD		equ 8000h
DEBUG_ENGOPT_DISABLE_EXECUTION_COMMANDS		equ 10000h
DEBUG_ENGOPT_DISALLOW_IMAGE_FILE_MAPPING	equ 20000h
DEBUG_ENGOPT_PREFER_DML						equ 40000h
DEBUG_ENGOPT_ALL							equ 7FFFFh
DEBUG_ANY_ID								equ 0FFFFFFFFh
DEBUG_STACK_FRAME STRUC
	InstructionOffset	ULONG64 ?
	ReturnOffset		ULONG64 ?
	FrameOffset			ULONG64 ?
	StackOffset			ULONG64 ?
	FuncTableEntry		ULONG64 ?
	Params				ULONG64 4 dup(?)
	Reserved			ULONG64 6 dup(?)
	Virtual				BOOL ?
	FrameNumber			ULONG ?
DEBUG_STACK_FRAME ENDS
PDEBUG_STACK_FRAME TYPEDEF PTR DEBUG_STACK_FRAME
DEBUG_STACK_ARGUMENTS				equ 1
DEBUG_STACK_FUNCTION_INFO			equ 2
DEBUG_STACK_SOURCE_LINE				equ 4
DEBUG_STACK_FRAME_ADDRESSES			equ 8
DEBUG_STACK_COLUMN_NAMES			equ 10h
DEBUG_STACK_NONVOLATILE_REGISTERS	equ 20h
DEBUG_STACK_FRAME_NUMBERS			equ 40h
DEBUG_STACK_PARAMETERS				equ 80h
DEBUG_STACK_FRAME_ADDRESSES_RA_ONLY	equ 100h
DEBUG_STACK_FRAME_MEMORY_USAGE		equ 200h
DEBUG_STACK_PARAMETERS_NEWLINE		equ 400h
DEBUG_STACK_DML						equ 800h
DEBUG_STACK_FRAME_OFFSETS			equ 1000h
DEBUG_CLASS_UNINITIALIZED			equ 0
DEBUG_CLASS_KERNEL					equ 1
DEBUG_CLASS_USER_WINDOWS			equ 2
DEBUG_CLASS_IMAGE_FILE				equ 3
DEBUG_DUMP_SMALL					equ 1024
DEBUG_DUMP_DEFAULT					equ 1025
DEBUG_DUMP_FULL						equ 1026
DEBUG_DUMP_IMAGE_FILE				equ 1027
DEBUG_DUMP_TRACE_LOG				equ 1028
DEBUG_DUMP_WINDOWS_CE				equ 1029
DEBUG_KERNEL_CONNECTION				equ 0
DEBUG_KERNEL_LOCAL					equ 1
DEBUG_KERNEL_EXDI_DRIVER			equ 2
DEBUG_KERNEL_IDNA					equ 3
DEBUG_KERNEL_INSTALL_DRIVER			equ 4
DEBUG_KERNEL_SMALL_DUMP				equ DEBUG_DUMP_SMALL
DEBUG_KERNEL_DUMP					equ DEBUG_DUMP_DEFAULT
DEBUG_KERNEL_FULL_DUMP				equ DEBUG_DUMP_FULL
DEBUG_KERNEL_TRACE_LOG				equ DEBUG_DUMP_TRACE_LOG
DEBUG_USER_WINDOWS_PROCESS			equ 0
DEBUG_USER_WINDOWS_PROCESS_SERVER	equ 1
DEBUG_USER_WINDOWS_IDNA				equ 2
DEBUG_USER_WINDOWS_SMALL_DUMP		equ DEBUG_DUMP_SMALL
DEBUG_USER_WINDOWS_DUMP				equ DEBUG_DUMP_DEFAULT
DEBUG_USER_WINDOWS_DUMP_WINDOWS_CE	equ DEBUG_DUMP_WINDOWS_CE
DEBUG_EXTENSION_AT_ENGINE			equ 0
DEBUG_EXECUTE_DEFAULT				equ 0
DEBUG_EXECUTE_ECHO					equ 1
DEBUG_EXECUTE_NOT_LOGGED			equ 2
DEBUG_EXECUTE_NO_REPEAT				equ 4
DEBUG_FILTER_CREATE_THREAD			equ 0
DEBUG_FILTER_EXIT_THREAD			equ 1
DEBUG_FILTER_CREATE_PROCESS			equ 2
DEBUG_FILTER_EXIT_PROCESS			equ 3
DEBUG_FILTER_LOAD_MODULE			equ 4
DEBUG_FILTER_UNLOAD_MODULE			equ 5
DEBUG_FILTER_SYSTEM_ERROR			equ 6
DEBUG_FILTER_INITIAL_BREAKPOINT		equ 7
DEBUG_FILTER_INITIAL_MODULE_LOAD	equ 8
DEBUG_FILTER_DEBUGGEE_OUTPUT		equ 9
DEBUG_FILTER_BREAK					equ 0
DEBUG_FILTER_SECOND_CHANCE_BREAK	equ 1
DEBUG_FILTER_OUTPUT					equ 2
DEBUG_FILTER_IGNORE					equ 3
DEBUG_FILTER_REMOVE					equ 4
DEBUG_FILTER_GO_HANDLED				equ 0
DEBUG_FILTER_GO_NOT_HANDLED			equ 1
DEBUG_SPECIFIC_FILTER_PARAMETERS STRUC
	ExecutionOption	ULONG ?
	ContinueOption	ULONG ?
	TextSize		ULONG ?
	CommandSize		ULONG ?
	ArgumentSize	ULONG ?
DEBUG_SPECIFIC_FILTER_PARAMETERS ENDS
PDEBUG_SPECIFIC_FILTER_PARAMETERS TYPEDEF PTR DEBUG_SPECIFIC_FILTER_PARAMETERS
DEBUG_EXCEPTION_FILTER_PARAMETERS STRUC
	ExecutionOption		ULONG ?
	ContinueOption		ULONG ?
	TextSize			ULONG ?
	CommandSize			ULONG ?
	SecondCommandSize	ULONG ?
	ExceptionCode		ULONG ?
DEBUG_EXCEPTION_FILTER_PARAMETERS ENDS
PDEBUG_EXCEPTION_FILTER_PARAMETERS TYPEDEF PTR DEBUG_EXCEPTION_FILTER_PARAMETERS
DEBUG_WAIT_DEFAULT	equ 0
DEBUG_LAST_EVENT_INFO_BREAKPOINT STRUC
	Id	ULONG ?
DEBUG_LAST_EVENT_INFO_BREAKPOINT ENDS
PDEBUG_LAST_EVENT_INFO_BREAKPOINT TYPEDEF PTR DEBUG_LAST_EVENT_INFO_BREAKPOINT
DEBUG_LAST_EVENT_INFO_EXCEPTION STRUC
	ExceptionRecord		EXCEPTION_RECORD<>
	FirstChance			ULONG ?
DEBUG_LAST_EVENT_INFO_EXCEPTION ENDS
PDEBUG_LAST_EVENT_INFO_EXCEPTION TYPEDEF PTR DEBUG_LAST_EVENT_INFO_EXCEPTION
DEBUG_LAST_EVENT_INFO_EXIT_THREAD STRUC
	ExitCode	ULONG ?
DEBUG_LAST_EVENT_INFO_EXIT_THREAD ENDS
PDEBUG_LAST_EVENT_INFO_EXIT_THREAD TYPEDEF PTR DEBUG_LAST_EVENT_INFO_EXIT_THREAD
DEBUG_LAST_EVENT_INFO_EXIT_PROCESS STRUC
	ExitCode	ULONG ?
DEBUG_LAST_EVENT_INFO_EXIT_PROCESS ENDS
PDEBUG_LAST_EVENT_INFO_EXIT_PROCESS TYPEDEF PTR DEBUG_LAST_EVENT_INFO_EXIT_PROCESS
DEBUG_LAST_EVENT_INFO_LOAD_MODULE STRUC
	Base	ULONG64 ?
DEBUG_LAST_EVENT_INFO_LOAD_MODULE ENDS
PDEBUG_LAST_EVENT_INFO_LOAD_MODULE TYPEDEF PTR DEBUG_LAST_EVENT_INFO_LOAD_MODULE
DEBUG_LAST_EVENT_INFO_UNLOAD_MODULE STRUC
	Base	ULONG64 ?
DEBUG_LAST_EVENT_INFO_UNLOAD_MODULE ENDS
PDEBUG_LAST_EVENT_INFO_UNLOAD_MODULE TYPEDEF PTR DEBUG_LAST_EVENT_INFO_UNLOAD_MODULE
DEBUG_LAST_EVENT_INFO_SYSTEM_ERROR STRUC
	Error	ULONG ?
	Level	ULONG ?
DEBUG_LAST_EVENT_INFO_SYSTEM_ERROR ENDS
PDEBUG_LAST_EVENT_INFO_SYSTEM_ERROR TYPEDEF PTR DEBUG_LAST_EVENT_INFO_SYSTEM_ERROR
DEBUG_VALUE_INVALID		equ 0
DEBUG_VALUE_INT8		equ 1
DEBUG_VALUE_INT16		equ 2
DEBUG_VALUE_INT32		equ 3
DEBUG_VALUE_INT64		equ 4
DEBUG_VALUE_FLOAT32		equ 5
DEBUG_VALUE_FLOAT64		equ 6
DEBUG_VALUE_FLOAT80		equ 7
DEBUG_VALUE_FLOAT82		equ 8
DEBUG_VALUE_FLOAT128	equ 9
DEBUG_VALUE_VECTOR64	equ 10
DEBUG_VALUE_VECTOR128	equ 11
DEBUG_VALUE_TYPES		equ 12
I64RARTS32 STRUC
     LowPart	ULONG ?
     HighPart	ULONG ?
I64RARTS32 ENDS
F128PARTS64 STRUC
	LowPart		ULONG64 ?
	HighPart		LONG64 ?
F128PARTS64 ENDS
DEBUG_VALUE STRUC
	UNION
    	I8	UCHAR ?
    	I16	USHORT ?
		I32	ULONG ?
        STRUC
        	I64	ULONG64 ?
        	Nat	BOOL ?
        ENDS
    	F32			REAL4 ?
        F64			REAL8 ?
		F80Bytes	BYTE 10 dup(?)
        F82Bytes	UCHAR 11 dup(?)
		F128Bytes	UCHAR 16 dup(?)
    	VI8			UCHAR 16 dup(?)
    	VI16		USHORT 8 dup(?)
    	VI32		ULONG 4 dup(?)
    	VI64		ULONG64 2 dup(?)
		VF32		REAL4 4 dup(?)
		VF64		REAL8 2 dup(?)
		I64Rarts32	I64RARTS32<>
		F128Parts64	F128PARTS64<>
		RawBytes	UCHAR 24 dup(?)
	ENDS
	TailOfRawBytes	ULONG ?
	_Type			ULONG ?
DEBUG_VALUE ENDS
PDEBUG_VALUE TYPEDEF PTR DEBUG_VALUE
IDebugControl STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetInterrupt				PANYARGS ?	;œ–Œ¬≈– ¿ œŒÀ‹«Œ¬¿“≈À‹— »’ œ–≈–€¬¿Õ»…, Õ¿œ–»Ã≈– CTRL+C
	SetInterrupt				PANYARGS ?	;–≈√»—“–¿÷»ﬂ » ”œ–¿¬À≈Õ»≈ œŒÀ‹«Œ¬¿“≈À‹— »Ã» œ–≈–€¬¿Õ»ﬂÃ»
	GetInterruptTimeout			PANYARGS ?
	SetInterruptTimeout			PANYARGS ?
	GetLogFile					PANYARGS ?
	OpenLogFile					PANYARGS ?	;”œ–¿¬À≈Õ»≈ ‘¿…ÀŒÃ ∆”–Õ¿À¿
	CloseLogFile				PANYARGS ?
	GetLogMask					PANYARGS ?
	SetLogMask					PANYARGS ?
	Input						PANYARGS ?	;¬¬Œƒ  À»≈Õ“¿
	ReturnInput					PANYARGS ?
	Output						PANYARGS ?	;¬€¬Œƒ
	OutputVaList				PANYARGS ?
	ControlledOutput			PANYARGS ?	;”œ–¿¬À≈Õ»≈ ¬€¬ŒƒŒÃ
	ControlledOutputVaList		PANYARGS ?
	OutputPrompt				PANYARGS ?
	OutputPromptVaList			PANYARGS ?
	GetPromptText				PANYARGS ?
	OutputCurrentState			PANYARGS ?
	OutputVersionInformation	PANYARGS ?
	GetNotifyEventHandle		PANYARGS ?	;”¬≈ƒŒÃÀ≈Õ»≈ Œ —Œ¡€“»ﬂ’
	SetNotifyEventHandle		PANYARGS ?
	Assemble					PANYARGS ?	;ƒ»«/¿——≈Ã¡À»–Œ¬¿Õ»≈
	Disassemble					PANYARGS ?
	GetDisassembleEffectiveOffset	PANYARGS ?
	OutputDisassembly			PANYARGS ?
	OutputDisassemblyLines		PANYARGS ?
	GetNearInstruction			PANYARGS ?
	GetStackTrace				PANYARGS ?
	GetReturnOffset				PANYARGS ?	;“–¿—»–Œ¬¿Õ»≈ —“› ¿
	OutputStackTrace			PANYARGS ?
	GetDebuggeeType				PANYARGS ?	;œŒÀ”◊≈Õ»≈ ƒŒœŒÀÕ»“≈À‹ÕŒ… »Õ‘Œ–Ã¿÷»»
	GetActualProcessorType		PANYARGS ?
	GetExecutingProcessorType	PANYARGS ?
	GetNumberPossibleExecutingProcessorTypes	PANYARGS ?
	GetPossibleExecutingProcessorTypes			PANYARGS ?
	GetNumberProcessors			PANYARGS ?
	GetSystemVersion			PANYARGS ?
	GetPageSize					PANYARGS ?
	IsPointer64Bit				PANYARGS ?
	ReadBugCheckData			PANYARGS ?
	GetNumberSupportedProcessorTypes	PANYARGS ?
	GetSupportedProcessorTypes	PANYARGS ?
	GetProcessorTypeNames		PANYARGS ?	;Õ¿«¬¿Õ»≈ œ–Œ÷≈——Œ–¿
	GetEffectiveProcessorType	PANYARGS ?
	SetEffectiveProcessorType	PANYARGS ?
	GetExecutionStatus			PANYARGS ?
	SetExecutionStatus			PANYARGS ?
	GetCodeLevel				PANYARGS ?
	SetCodeLevel				PANYARGS ?
	GetEngineOptions			PANYARGS ?
	AddEngineOptions			PANYARGS ?
	RemoveEngineOptions			PANYARGS ?
	SetEngineOptions			PANYARGS ?
	GetSystemErrorControl		PANYARGS ?
	SetSystemErrorControl		PANYARGS ?
	GetTextMacro				PANYARGS ?	;”œ–¿¬À≈Õ»≈ “≈ —“Œ¬€Ã» Ã¿ –Œ—¿Ã»
	SetTextMacro				PANYARGS ?
	GetRadix					PANYARGS ?
	SetRadix					PANYARGS ?
	Evaluate					PANYARGS ?
	CoerceValue					PANYARGS ?	;”œ–¿¬À≈Õ»≈ œ≈–≈Ã≈ÕÕ€Ã»
	CoerceValues				PANYARGS ?
	Execute						PANYARGS ?	;¬€œŒÀÕ≈Õ»≈ “≈ —“Œ¬€’  ŒÃÃ¿Õƒ
	ExecuteCommandFile			PANYARGS ?
	GetNumberBreakpoints		PANYARGS ?	;”œ–¿¬À≈Õ»≈ “Œ◊ ¿Ã» Œ—“¿ÕŒ¬¿
	GetBreakpointByIndex		PANYARGS ?
	GetBreakpointById			PANYARGS ?
	GetBreakpointParameters		PANYARGS ?
	AddBreakpoint				PANYARGS ?
	RemoveBreakpoint			PANYARGS ?
	AddExtension				PANYARGS ?	;”œ–¿¬À≈Õ»≈ ¡»¡À»Œ“≈ ¿Ã» –¿—ÿ»–≈Õ»ﬂ
	RemoveExtension				PANYARGS ?
	GetExtensionByPath			PANYARGS ?
	CallExtension				PANYARGS ?
	GetExtensionFunction		PANYARGS ?
	GetWindbgExtensionApis32	PANYARGS ?
	GetWindbgExtensionApis64	PANYARGS ?
	GetNumberEventFilters		PANYARGS ?	;”œ–¿¬À≈Õ»≈ ‘»À‹“–¿Ã» —Œ¡€“»…
	GetEventFilterText			PANYARGS ?
	GetEventFilterCommand		PANYARGS ?
	SetEventFilterCommand		PANYARGS ?
	GetSpecificFilterParameters	PANYARGS ?
	SetSpecificFilterParameters	PANYARGS ?
	GetSpecificFilterArgument	PANYARGS ?
	SetSpecificFilterArgument	PANYARGS ?
	GetExceptionFilterParameters	PANYARGS ?
	SetExceptionFilterParameters	PANYARGS ?
	GetExceptionFilterSecondCommand	PANYARGS ?
	SetExceptionFilterSecondCommand	PANYARGS ?
	WaitForEvent					PANYARGS ?	;÷» À œŒÀ”◊≈Õ»ﬂ ”¬≈ƒŒÃÀ≈Õ»… Œ —Œ¡€“»ﬂ’
	GetLastEventInformation			PANYARGS ?
	GetCurrentTimeDate				PANYARGS ?	;IDebugControl2
	GetCurrentSystemUpTime			PANYARGS ?
	FormatFlags						PANYARGS ?
	GetDumpFormatFlags				PANYARGS ?
	GetNumberTextReplacements		PANYARGS ?
	GetTextReplacement				PANYARGS ?
	SetTextReplacement				PANYARGS ?
	RemoveTextReplacements			PANYARGS ?
	OutputTextReplacements			PANYARGS ?
	GetAssemblyOptions				PANYARGS ?	;IDebugControl3 Œœ÷»» ƒÀﬂ ƒ»«/¿——≈Ã¡À»–Œ¬¿Õ»ﬂ
    AddAssemblyOptions				PANYARGS ?
    RemoveAssemblyOptions			PANYARGS ?
    SetAssemblyOptions				PANYARGS ?
    GetExpressionSyntax				PANYARGS ?
    SetExpressionSyntax				PANYARGS ?
    SetExpressionSyntaxByName		PANYARGS ?
    GetNumberExpressionSyntaxes		PANYARGS ?
    GetExpressionSyntaxNames		PANYARGS ?
    GetNumberEvents					PANYARGS ?
    GetEventIndexDescription		PANYARGS ?
    GetCurrentEventIndex			PANYARGS ?
    SetNextEventIndex				PANYARGS ?
	GetLogFileWide					PANYARGS ?	;IDebugControl4
	OpenLogFileWide					PANYARGS ?
	InputWide						PANYARGS ?
	ReturnInputWide					PANYARGS ?
	OutputWide						PANYARGS ?
	OutputVaListWide				PANYARGS ?
	ControlledOutputWide			PANYARGS ?
	ControlledOutputVaListWide		PANYARGS ?
	OutputPromptWide				PANYARGS ?
	OutputPromptVaListWide			PANYARGS ?
	GetPromptTextWide				PANYARGS ?
	AssembleWide					PANYARGS ?
	DisassembleWide					PANYARGS ?
	GetProcessorTypeNamesWide		PANYARGS ?
	GetTextMacroWide				PANYARGS ?
	SetTextMacroWide				PANYARGS ?
	EvaluateWide					PANYARGS ?
	ExecuteWide						PANYARGS ?
	ExecuteCommandFileWide			PANYARGS ?
	GetBreakpointByIndex2			PANYARGS ?
    GetBreakpointById2				PANYARGS ?
    AddBreakpoint2					PANYARGS ?
    RemoveBreakpoint2				PANYARGS ?
    AddExtensionWide				PANYARGS ?
    GetExtensionByPathWide			PANYARGS ?
    CallExtensionWide				PANYARGS ?
    GetExtensionFunctionWide		PANYARGS ?
    GetEventFilterTextWide			PANYARGS ?
    GetEventFilterCommandWide		PANYARGS ?
    SetEventFilterCommandWide		PANYARGS ?
    GetSpecificFilterArgumentWide	PANYARGS ?
    SetSpecificFilterArgumentWide	PANYARGS ?
    GetExceptionFilterSecondCommandWide	PANYARGS ?
    SetExceptionFilterSecondCommandWide	PANYARGS ?
    GetLastEventInformationWide		PANYARGS ?
    GetTextReplacementWide			PANYARGS ?
    SetTextReplacementWide			PANYARGS ?
    SetExpressionSyntaxByNameWide	PANYARGS ?
    GetExpressionSyntaxNamesWide	PANYARGS ?
    GetEventIndexDescriptionWide	PANYARGS ?
    GetLogFile2						PANYARGS ?
    OpenLogFile2					PANYARGS ?
    GetLogFile2Wide					PANYARGS ?
    OpenLogFile2Wide				PANYARGS ?
    GetSystemVersionValues			PANYARGS ?
    GetSystemVersionString			PANYARGS ?
    GetSystemVersionStringWide		PANYARGS ?
    GetContextStackTrace			PANYARGS ?
    OutputContextStackTrace			PANYARGS ?
    GetStoredEventInformation		PANYARGS ?
    GetManagedStatus				PANYARGS ?
    GetManagedStatusWide			PANYARGS ?
    ResetManagedStatus				PANYARGS ?
IDebugControl ENDS
PDEBUG_CONTROL TYPEDEF PTR IDebugControl
PDCTRL TYPEDEF PTR PDEBUG_CONTROL
DEBUG_OUT_TEXT_REPL_DEFAULT			equ 0
DEBUG_ASMOPT_DEFAULT				equ 0
DEBUG_ASMOPT_VERBOSE				equ 1
DEBUG_ASMOPT_NO_CODE_BYTES			equ 2
DEBUG_ASMOPT_IGNORE_OUTPUT_WIDTH	equ 4
DEBUG_ASMOPT_SOURCE_LINE_NUMBER		equ 8
DEBUG_EXPR_MASM						equ 0
DEBUG_EXPR_CPLUSPLUS				equ 1
DEBUG_EINDEX_NAME					equ 0
DEBUG_EINDEX_FROM_START				equ 0
DEBUG_EINDEX_FROM_END				equ 1
DEBUG_EINDEX_FROM_CURRENT			equ 2
DEBUG_LOG_DEFAULT					equ 0
DEBUG_LOG_APPEND					equ 1
DEBUG_LOG_UNICODE					equ 2
DEBUG_LOG_DML						equ 4
DEBUG_SYSVERSTR_SERVICE_PACK		equ 0
DEBUG_SYSVERSTR_BUILD				equ 1
DEBUG_MANAGED_DISABLED				equ 0
DEBUG_MANAGED_ALLOWED				equ 1
DEBUG_MANAGED_DLL_LOADED			equ 2
DEBUG_MANSTR_NONE					equ 0
DEBUG_MANSTR_LOADED_SUPPORT_DLL		equ 1
DEBUG_MANSTR_LOAD_STATUS			equ 2
DEBUG_MANRESET_DEFAULT				equ 0
DEBUG_MANRESET_LOAD_DLL				equ 1
DEBUG_DATA_SPACE_VIRTUAL			equ 0
DEBUG_DATA_SPACE_PHYSICAL			equ 1
DEBUG_DATA_SPACE_CONTROL			equ 2
DEBUG_DATA_SPACE_IO					equ 3
DEBUG_DATA_SPACE_MSR				equ 4
DEBUG_DATA_SPACE_BUS_DATA			equ 5
DEBUG_DATA_SPACE_DEBUGGER_DATA		equ 6
DEBUG_DATA_SPACE_COUNT				equ 7
DEBUG_DATA_KernBase								equ 24
DEBUG_DATA_BreakpointWithStatusAddr				equ 32
DEBUG_DATA_SavedContextAddr						equ 40
DEBUG_DATA_KiCallUserModeAddr					equ 56
DEBUG_DATA_KeUserCallbackDispatcherAddr			equ 64
DEBUG_DATA_PsLoadedModuleListAddr				equ 72
DEBUG_DATA_PsActiveProcessHeadAddr				equ 80
DEBUG_DATA_PspCidTableAddr						equ 88
DEBUG_DATA_ExpSystemResourcesListAddr			equ 96
DEBUG_DATA_ExpPagedPoolDescriptorAddr			equ 104
DEBUG_DATA_ExpNumberOfPagedPoolsAddr			equ 112
DEBUG_DATA_KeTimeIncrementAddr					equ 120
DEBUG_DATA_KeBugCheckCallbackListHeadAddr		equ 128
DEBUG_DATA_KiBugcheckDataAddr					equ 136
DEBUG_DATA_IopErrorLogListHeadAddr				equ 144
DEBUG_DATA_ObpRootDirectoryObjectAddr			equ 152
DEBUG_DATA_ObpTypeObjectTypeAddr				equ 160
DEBUG_DATA_MmSystemCacheStartAddr				equ 168
DEBUG_DATA_MmSystemCacheEndAddr					equ 176
DEBUG_DATA_MmSystemCacheWsAddr					equ 184
DEBUG_DATA_MmPfnDatabaseAddr					equ 192
DEBUG_DATA_MmSystemPtesStartAddr				equ 200
DEBUG_DATA_MmSystemPtesEndAddr					equ 208
DEBUG_DATA_MmSubsectionBaseAddr					equ 216
DEBUG_DATA_MmNumberOfPagingFilesAddr			equ 224
DEBUG_DATA_MmLowestPhysicalPageAddr				equ 232
DEBUG_DATA_MmHighestPhysicalPageAddr			equ 240
DEBUG_DATA_MmNumberOfPhysicalPagesAddr			equ 248
DEBUG_DATA_MmMaximumNonPagedPoolInBytesAddr		equ 256
DEBUG_DATA_MmNonPagedSystemStartAddr			equ 264
DEBUG_DATA_MmNonPagedPoolStartAddr				equ 272
DEBUG_DATA_MmNonPagedPoolEndAddr				equ 280
DEBUG_DATA_MmPagedPoolStartAddr					equ 288
DEBUG_DATA_MmPagedPoolEndAddr					equ 296
DEBUG_DATA_MmPagedPoolInformationAddr			equ 304
DEBUG_DATA_MmPageSize							equ 312
DEBUG_DATA_MmSizeOfPagedPoolInBytesAddr			equ 320
DEBUG_DATA_MmTotalCommitLimitAddr				equ 328
DEBUG_DATA_MmTotalCommittedPagesAddr			equ 336
DEBUG_DATA_MmSharedCommitAddr					equ 344
DEBUG_DATA_MmDriverCommitAddr					equ 352
DEBUG_DATA_MmProcessCommitAddr					equ 360
DEBUG_DATA_MmPagedPoolCommitAddr				equ 368
DEBUG_DATA_MmExtendedCommitAddr					equ 376
DEBUG_DATA_MmZeroedPageListHeadAddr				equ 384
DEBUG_DATA_MmFreePageListHeadAddr				equ 392
DEBUG_DATA_MmStandbyPageListHeadAddr			equ 400
DEBUG_DATA_MmModifiedPageListHeadAddr			equ 408
DEBUG_DATA_MmModifiedNoWritePageListHeadAddr	equ 416
DEBUG_DATA_MmAvailablePagesAddr					equ 424
DEBUG_DATA_MmResidentAvailablePagesAddr			equ 432
DEBUG_DATA_PoolTrackTableAddr					equ 440
DEBUG_DATA_NonPagedPoolDescriptorAddr			equ 448
DEBUG_DATA_MmHighestUserAddressAddr				equ 456
DEBUG_DATA_MmSystemRangeStartAddr				equ 464
DEBUG_DATA_MmUserProbeAddressAddr				equ 472
DEBUG_DATA_KdPrintCircularBufferAddr			equ 480
DEBUG_DATA_KdPrintCircularBufferEndAddr			equ 488
DEBUG_DATA_KdPrintWritePointerAddr				equ 496
DEBUG_DATA_KdPrintRolloverCountAddr				equ 504
DEBUG_DATA_MmLoadedUserImageListAddr			equ 512
DEBUG_DATA_NtBuildLabAddr						equ 520
DEBUG_DATA_KiNormalSystemCall					equ 528
DEBUG_DATA_KiProcessorBlockAddr					equ 536
DEBUG_DATA_MmUnloadedDriversAddr				equ 544
DEBUG_DATA_MmLastUnloadedDriverAddr				equ 552
DEBUG_DATA_MmTriageActionTakenAddr				equ 560
DEBUG_DATA_MmSpecialPoolTagAddr					equ 568
DEBUG_DATA_KernelVerifierAddr					equ 576
DEBUG_DATA_MmVerifierDataAddr					equ 584
DEBUG_DATA_MmAllocatedNonPagedPoolAddr			equ 592
DEBUG_DATA_MmPeakCommitmentAddr					equ 600
DEBUG_DATA_MmTotalCommitLimitMaximumAddr		equ 608
DEBUG_DATA_CmNtCSDVersionAddr					equ 616
DEBUG_DATA_MmPhysicalMemoryBlockAddr			equ 624
DEBUG_DATA_MmSessionBase						equ 632
DEBUG_DATA_MmSessionSize						equ 640
DEBUG_DATA_MmSystemParentTablePage				equ 648
DEBUG_DATA_MmVirtualTranslationBase				equ 656
DEBUG_DATA_OffsetKThreadNextProcessor			equ 664
DEBUG_DATA_OffsetKThreadTeb						equ 666
DEBUG_DATA_OffsetKThreadKernelStack				equ 668
DEBUG_DATA_OffsetKThreadInitialStack			equ 670
DEBUG_DATA_OffsetKThreadApcProcess				equ 672
DEBUG_DATA_OffsetKThreadState					equ 674
DEBUG_DATA_OffsetKThreadBStore					equ 676
DEBUG_DATA_OffsetKThreadBStoreLimit				equ 678
DEBUG_DATA_SizeEProcess							equ 680
DEBUG_DATA_OffsetEprocessPeb					equ 682
DEBUG_DATA_OffsetEprocessParentCID				equ 684
DEBUG_DATA_OffsetEprocessDirectoryTableBase		equ 686
DEBUG_DATA_SizePrcb								equ 688
DEBUG_DATA_OffsetPrcbDpcRoutine					equ 690
DEBUG_DATA_OffsetPrcbCurrentThread				equ 692
DEBUG_DATA_OffsetPrcbMhz						equ 694
DEBUG_DATA_OffsetPrcbCpuType					equ 696
DEBUG_DATA_OffsetPrcbVendorString				equ 698
DEBUG_DATA_OffsetPrcbProcessorState				equ 700
DEBUG_DATA_OffsetPrcbNumber						equ 702
DEBUG_DATA_SizeEThread							equ 704
DEBUG_DATA_KdPrintCircularBufferPtrAddr			equ 712
DEBUG_DATA_KdPrintBufferSizeAddr				equ 720
DEBUG_DATA_MmBadPagesDetected					equ 800
DEBUG_DATA_EtwpDebuggerData						equ 816
DEBUG_DATA_PaeEnabled							equ 100000
DEBUG_DATA_SharedUserData						equ 100008
DEBUG_DATA_ProductType							equ 100016
DEBUG_DATA_SuiteMask							equ 100024
DEBUG_DATA_DumpWriterStatus						equ 100032
DEBUG_DATA_DumpFormatVersion					equ 100040
DEBUG_DATA_DumpWriterVersion					equ 100048
DEBUG_DATA_DumpPowerState						equ 100056
DEBUG_DATA_DumpMmStorage						equ 100064
DEBUG_PROCESSOR_IDENTIFICATION_ALPHA STRUC
	_Type		ULONG ?
	Revision	ULONG ?
DEBUG_PROCESSOR_IDENTIFICATION_ALPHA ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_ALPHA TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_ALPHA
DEBUG_PROCESSOR_IDENTIFICATION_AMD64 STRUC
	Family			ULONG ?
	Model			ULONG ?
	Stepping		ULONG ?
	VendorString	CHAR 16 dup(?)
DEBUG_PROCESSOR_IDENTIFICATION_AMD64 ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_AMD64 TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_AMD64
DEBUG_PROCESSOR_IDENTIFICATION_IA64 STRUC
	Model			ULONG ?
	Revision		ULONG ?
	Family			ULONG ?
	ArchRev			ULONG ?
	VendorString	CHAR 16 dup(?)
DEBUG_PROCESSOR_IDENTIFICATION_IA64 ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_IA64 TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_IA64
DEBUG_PROCESSOR_IDENTIFICATION_X86 STRUC
	Family			ULONG ?
	Model			ULONG ?
	Stepping		ULONG ?
	VendorString	CHAR 16 dup(?)
DEBUG_PROCESSOR_IDENTIFICATION_X86 ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_X86 TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_X86
DEBUG_PROCESSOR_IDENTIFICATION_ARM STRUC
	_Type		ULONG ?
	Revision	ULONG ?
DEBUG_PROCESSOR_IDENTIFICATION_ARM ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_ARM TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_ARM
DEBUG_PROCESSOR_IDENTIFICATION_ALL STRUC
	Alpha	DEBUG_PROCESSOR_IDENTIFICATION_ALPHA<>
	Amd64	DEBUG_PROCESSOR_IDENTIFICATION_AMD64<>
	Ia64	DEBUG_PROCESSOR_IDENTIFICATION_IA64<>
	X86		DEBUG_PROCESSOR_IDENTIFICATION_X86<>
	Arm		DEBUG_PROCESSOR_IDENTIFICATION_ARM<>
DEBUG_PROCESSOR_IDENTIFICATION_ALL ENDS
PDEBUG_PROCESSOR_IDENTIFICATION_ALL TYPEDEF PTR DEBUG_PROCESSOR_IDENTIFICATION_ALL
DEBUG_DATA_KPCR_OFFSET						equ 0
DEBUG_DATA_KPRCB_OFFSET						equ 1
DEBUG_DATA_KTHREAD_OFFSET					equ 2
DEBUG_DATA_BASE_TRANSLATION_VIRTUAL_OFFSET	equ 3
DEBUG_DATA_PROCESSOR_IDENTIFICATION			equ 4
DEBUG_DATA_PROCESSOR_SPEED					equ 5
IDebugDataSpaces STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	ReadVirtual					PANYARGS ?
	WriteVirtual				PANYARGS ?
	SearchVirtual				PANYARGS ?
	ReadVirtualUncached			PANYARGS ?
	WriteVirtualUncached		PANYARGS ?
	ReadPointersVirtual			PANYARGS ?
	WritePointersVirtual		PANYARGS ?
	ReadPhysical				PANYARGS ?
	WritePhysical				PANYARGS ?
	ReadControl					PANYARGS ?
	WriteControl				PANYARGS ?
	ReadIo						PANYARGS ?
	WriteIo						PANYARGS ?
	ReadMsr						PANYARGS ?
	WriteMsr					PANYARGS ?
	ReadBusData					PANYARGS ?
	WriteBusData				PANYARGS ?
	CheckLowMemory				PANYARGS ?
	ReadDebuggerData			PANYARGS ?
	ReadProcessorSystemData		PANYARGS ?
	VirtualToPhysical			PANYARGS ?	;IDebugDataSpaces2.
	GetVirtualTranslationPhysicalOffsets	PANYARGS ?
	ReadHandleData				PANYARGS ?
	FillVirtual					PANYARGS ?
	FillPhysical				PANYARGS ?
	QueryVirtual				PANYARGS ?
	ReadImageNtHeaders			PANYARGS ?	;IDebugDataSpaces3.
	ReadTagged					PANYARGS ?
	StartEnumTagged				PANYARGS ?
	GetNextTagged				PANYARGS ?
	EndEnumTagged				PANYARGS ?
	GetOffsetInformation		PANYARGS ?	;IDebugDataSpaces4.
	GetNextDifferentlyValidOffsetVirtual	PANYARGS ?
	GetValidRegionVirtual		PANYARGS ?
	SearchVirtual2				PANYARGS ?
	ReadMultiByteStringVirtual	PANYARGS ?
	ReadMultiByteStringVirtualWide	PANYARGS ?
	ReadUnicodeStringVirtual		PANYARGS ?
	ReadUnicodeStringVirtualWide	PANYARGS ?
    ReadPhysical2				PANYARGS ?
    WritePhysical2				PANYARGS ?
IDebugDataSpaces ENDS
PDEBUG_DATA_SPACES TYPEDEF PTR IDebugDataSpaces
PDDSPACES TYPEDEF PTR PDEBUG_DATA_SPACES
DEBUG_HANDLE_DATA_TYPE_BASIC					equ 0
DEBUG_HANDLE_DATA_TYPE_TYPE_NAME				equ 1
DEBUG_HANDLE_DATA_TYPE_OBJECT_NAME				equ 2
DEBUG_HANDLE_DATA_TYPE_HANDLE_COUNT				equ 3
DEBUG_HANDLE_DATA_TYPE_TYPE_NAME_WIDE			equ 4
DEBUG_HANDLE_DATA_TYPE_OBJECT_NAME_WIDE			equ 5
DEBUG_HANDLE_DATA_TYPE_MINI_THREAD_1			equ 6
DEBUG_HANDLE_DATA_TYPE_MINI_MUTANT_1			equ 7
DEBUG_HANDLE_DATA_TYPE_MINI_MUTANT_2			equ 8
DEBUG_HANDLE_DATA_TYPE_PER_HANDLE_OPERATIONS	equ 9
DEBUG_HANDLE_DATA_TYPE_ALL_HANDLE_OPERATIONS	equ 10
DEBUG_HANDLE_DATA_TYPE_MINI_PROCESS_1			equ 11
DEBUG_HANDLE_DATA_TYPE_MINI_PROCESS_2			equ 12
DEBUG_HANDLE_DATA_BASIC STRUC
	TypeNameSize	ULONG ?
	ObjectNameSize	ULONG ?
	Attributes		ULONG ?
	GrantedAccess	ULONG ?
	HandleCount		ULONG ?
	PointerCount	ULONG ?
DEBUG_HANDLE_DATA_BASIC ENDS
PDEBUG_HANDLE_DATA_BASIC TYPEDEF PTR DEBUG_HANDLE_DATA_BASIC
DEBUG_OFFSINFO_VIRTUAL_SOURCE		equ 1
DEBUG_VSOURCE_INVALID				equ 0
DEBUG_VSOURCE_DEBUGGEE				equ 1
DEBUG_VSOURCE_MAPPED_IMAGE			equ 2
DEBUG_VSOURCE_DUMP_WITHOUT_MEMINFO	equ 3
DEBUG_VSEARCH_DEFAULT				equ 0
DEBUG_VSEARCH_WRITABLE_ONLY			equ 1
DEBUG_PHYSICAL_DEFAULT				equ 0
DEBUG_PHYSICAL_CACHED				equ 1
DEBUG_PHYSICAL_UNCACHED				equ 2
DEBUG_PHYSICAL_WRITE_COMBINED		equ 3
DEBUG_EVENT_BREAKPOINT				equ 1
DEBUG_EVENT_EXCEPTION				equ 2
DEBUG_EVENT_CREATE_THREAD			equ 4
DEBUG_EVENT_EXIT_THREAD				equ 8
DEBUG_EVENT_CREATE_PROCESS			equ 10h
DEBUG_EVENT_EXIT_PROCESS			equ 20h
DEBUG_EVENT_LOAD_MODULE				equ 40h
DEBUG_EVENT_UNLOAD_MODULE			equ 80h
DEBUG_EVENT_SYSTEM_ERROR			equ 100h
DEBUG_EVENT_SESSION_STATUS			equ 200h
DEBUG_EVENT_CHANGE_DEBUGGEE_STATE	equ 400h
DEBUG_EVENT_CHANGE_ENGINE_STATE		equ 800h
DEBUG_EVENT_CHANGE_SYMBOL_STATE		equ 1000h
DEBUG_SESSION_ACTIVE						equ 0
DEBUG_SESSION_END_SESSION_ACTIVE_TERMINATE	equ 1
DEBUG_SESSION_END_SESSION_ACTIVE_DETACH		equ 2
DEBUG_SESSION_END_SESSION_PASSIVE			equ 3
DEBUG_SESSION_END							equ 4
DEBUG_SESSION_REBOOT						equ 5
DEBUG_SESSION_HIBERNATE						equ 6
DEBUG_SESSION_FAILURE						equ 7
DEBUG_CDS_ALL								equ 0FFFFFFFFh
DEBUG_CDS_REGISTERS							equ 1
DEBUG_CDS_DATA								equ 2
DEBUG_CES_ALL								equ 0FFFFFFFFh
DEBUG_CES_CURRENT_THREAD					equ 1
DEBUG_CES_EFFECTIVE_PROCESSOR				equ 2
DEBUG_CES_BREAKPOINTS						equ 4
DEBUG_CES_CODE_LEVEL						equ 8
DEBUG_CES_EXECUTION_STATUS					equ 10h
DEBUG_CES_ENGINE_OPTIONS					equ 20h
DEBUG_CES_LOG_FILE							equ 40h
DEBUG_CES_RADIX								equ 80h
DEBUG_CES_EVENT_FILTERS						equ 100h
DEBUG_CES_PROCESS_OPTIONS					equ 200h
DEBUG_CES_EXTENSIONS						equ 400h
DEBUG_CES_SYSTEMS							equ 800h
DEBUG_CES_ASSEMBLY_OPTIONS					equ 1000h
DEBUG_CES_EXPRESSION_SYNTAX					equ 2000h
DEBUG_CES_TEXT_REPLACEMENTS					equ 4000h
DEBUG_CSS_ALL								equ 0FFFFFFFFh
DEBUG_CSS_LOADS								equ 1
DEBUG_CSS_UNLOADS							equ 2
DEBUG_CSS_SCOPE								equ 4
DEBUG_CSS_PATHS								equ 8
DEBUG_CSS_SYMBOL_OPTIONS					equ 10h
DEBUG_CSS_TYPE_OPTIONS						equ 20h
IDebugEventCallbacks STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetInterestMask				PANYARGS ?
	Breakpoint					PANYARGS ?
	Exception					PANYARGS ?
	CreateThread				PANYARGS ?
	ExitThread					PANYARGS ?
	CreateProcess				PANYARGS ?
	ExitProcess					PANYARGS ?
	LoadModule					PANYARGS ?
	UnloadModule				PANYARGS ?
	SystemError					PANYARGS ?
	SessionStatus				PANYARGS ?
	ChangeDebuggeeState			PANYARGS ?
	ChangeEngineState			PANYARGS ?
	ChangeSymbolState			PANYARGS ?
IDebugEventCallbacks ENDS
PDEBUG_EVENT_CALLBACKS TYPEDEF PTR IDebugEventCallbacks
PDECALLBACKS TYPEDEF PTR PDEBUG_EVENT_CALLBACKS
IDebugEventCallbacksWide STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetInterestMask				PANYARGS ?
	Breakpoint					PANYARGS ?
	Exception					PANYARGS ?
	CreateThread				PANYARGS ?
	ExitThread					PANYARGS ?
	CreateProcess				PANYARGS ?
	ExitProcess					PANYARGS ?
	LoadModule					PANYARGS ?
	UnloadModule				PANYARGS ?
	SystemError					PANYARGS ?
	SessionStatus				PANYARGS ?
	ChangeDebuggeeState			PANYARGS ?
	ChangeEngineState			PANYARGS ?
	ChangeSymbolState			PANYARGS ?
IDebugEventCallbacksWide ENDS
PDEBUG_EVENT_CALLBACKS_WIDE TYPEDEF PTR IDebugEventCallbacksWide
PDECALLBACKSW TYPEDEF PTR PDEBUG_EVENT_CALLBACKS_WIDE
IDebugInputCallbacks STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	StartInput					PANYARGS ?
	EndInput					PANYARGS ?
IDebugInputCallbacks ENDS
PDEBUG_INPUT_CALLBACKS TYPEDEF PTR IDebugInputCallbacks
PDICALLBACKS TYPEDEF PTR PDEBUG_INPUT_CALLBACKS
IDebugOutputCallbacks STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	Output						PANYARGS ?
	GetInterestMask				PANYARGS ?	;IDebugOutputCallbacks2.
	Output2						PANYARGS ?
IDebugOutputCallbacks ENDS
PDEBUG_OUTPUT_CALLBACKS TYPEDEF PTR IDebugOutputCallbacks
PDOCALLBACKS TYPEDEF PTR PDEBUG_OUTPUT_CALLBACKS
IDebugOutputCallbacksWide STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	Output						PANYARGS ?
IDebugOutputCallbacksWide ENDS
PDEBUG_OUTPUT_CALLBACKS_WIDE TYPEDEF PTR IDebugOutputCallbacksWide
PDOCALLBACKSW TYPEDEF PTR PDEBUG_OUTPUT_CALLBACKS_WIDE
DEBUG_OUTCBI_EXPLICIT_FLUSH		equ 1
DEBUG_OUTCBI_TEXT				equ 2
DEBUG_OUTCBI_DML				equ 4
DEBUG_OUTCBI_ANY_FORMAT			equ 6
DEBUG_OUTCB_TEXT				equ 0
DEBUG_OUTCB_DML					equ 1
DEBUG_OUTCB_EXPLICIT_FLUSH		equ 2
DEBUG_OUTCBF_COMBINED_EXPLICIT_FLUSH	equ 1
DEBUG_OUTCBF_DML_HAS_TAGS				equ 2
DEBUG_OUTCBF_DML_HAS_SPECIAL_CHARACTERS	equ 4
DEBUG_REGISTERS_DEFAULT					equ 0
DEBUG_REGISTERS_INT32					equ 1
DEBUG_REGISTERS_INT64					equ 2
DEBUG_REGISTERS_FLOAT					equ 4
DEBUG_REGISTERS_ALL						equ 7
DEBUG_REGISTER_SUB_REGISTER				equ 1
DEBUG_REGISTER_DESCRIPTION STRUC
	_Type			ULONG ?
	Flags			ULONG ?
	SubregMaster	ULONG ?
	SubregLength	ULONG ?
	SubregMask		ULONG64 ?
	SubregShift		ULONG ?
	Reserved0		ULONG ?
DEBUG_REGISTER_DESCRIPTION ENDS
PDEBUG_REGISTER_DESCRIPTION TYPEDEF PTR DEBUG_REGISTER_DESCRIPTION
IDebugRegisters STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetNumberRegisters			PANYARGS ?
	GetDescription				PANYARGS ?
	GetIndexByName				PANYARGS ?
	GetValue					PANYARGS ?
	SetValue					PANYARGS ?
	GetValues					PANYARGS ?
	SetValues					PANYARGS ?
	OutputRegisters				PANYARGS ?
	GetInstructionOffset		PANYARGS ?
	GetStackOffset				PANYARGS ?
	GetFrameOffset				PANYARGS ?
	GetDescriptionWide			PANYARGS ?	;IDebugRegisters2.
	GetIndexByNameWide			PANYARGS ?
	GetNumberPseudoRegisters	PANYARGS ?
	GetPseudoDescription		PANYARGS ?
	GetPseudoDescriptionWide	PANYARGS ?
	GetPseudoIndexByName		PANYARGS ?
	GetPseudoIndexByNameWide	PANYARGS ?
	GetPseudoValues				PANYARGS ?
	SetPseudoValues				PANYARGS ?
	GetValues2					PANYARGS ?
	SetValues2					PANYARGS ?
	OutputRegisters2			PANYARGS ?
	GetInstructionOffset2		PANYARGS ?
	GetStackOffset2				PANYARGS ?
	GetFrameOffset2				PANYARGS ?
IDebugRegisters ENDS
PDEBUG_REGISTERS TYPEDEF PTR IDebugRegisters
PDREG TYPEDEF PTR PDEBUG_REGISTERS
DEBUG_REGSRC_DEBUGGEE			equ 0
DEBUG_REGSRC_EXPLICIT			equ 1
DEBUG_REGSRC_FRAME				equ 2
DEBUG_OUTPUT_SYMBOLS_DEFAULT	equ 0
DEBUG_OUTPUT_SYMBOLS_NO_NAMES	equ 1
DEBUG_OUTPUT_SYMBOLS_NO_OFFSETS	equ 2
DEBUG_OUTPUT_SYMBOLS_NO_VALUES	equ 4
DEBUG_OUTPUT_SYMBOLS_NO_TYPES	equ 10h
DEBUG_OUTPUT_NAME_END			equ "**NAME**"
DEBUG_OUTPUT_OFFSET_END			equ "**OFF**"
DEBUG_OUTPUT_VALUE_END			equ "**VALUE**"
DEBUG_OUTPUT_TYPE_END			equ "**TYPE**"
DEBUG_OUTPUT_NAME_END_WIDE		equ "**NAME**"
DEBUG_OUTPUT_OFFSET_END_WIDE	equ "**OFF**"
DEBUG_OUTPUT_VALUE_END_WIDE		equ "**VALUE**"
DEBUG_OUTPUT_TYPE_END_WIDE		equ "**TYPE**"
IFDEF UNICODE
	DEBUG_OUTPUT_NAME_END_T		equ DEBUG_OUTPUT_NAME_END_WIDE
	DEBUG_OUTPUT_OFFSET_END_T	equ DEBUG_OUTPUT_OFFSET_END_WIDE
	DEBUG_OUTPUT_VALUE_END_T	equ DEBUG_OUTPUT_VALUE_END_WIDE
	DEBUG_OUTPUT_TYPE_END_T		equ DEBUG_OUTPUT_TYPE_END_WIDE
ELSE
	DEBUG_OUTPUT_NAME_END_T		equ DEBUG_OUTPUT_NAME_END
	DEBUG_OUTPUT_OFFSET_END_T	equ DEBUG_OUTPUT_OFFSET_END
	DEBUG_OUTPUT_VALUE_END_T	equ DEBUG_OUTPUT_VALUE_END
	DEBUG_OUTPUT_TYPE_END_T		equ DEBUG_OUTPUT_TYPE_END
ENDIF
DEBUG_SYMBOL_EXPANSION_LEVEL_MASK	equ 0Fh
DEBUG_SYMBOL_EXPANDED				equ 10h
DEBUG_SYMBOL_READ_ONLY				equ 20h
DEBUG_SYMBOL_IS_ARRAY				equ 40h
DEBUG_SYMBOL_IS_FLOAT				equ 80h
DEBUG_SYMBOL_IS_ARGUMENT			equ 100h
DEBUG_SYMBOL_IS_LOCAL				equ 200h
DEBUG_SYMBOL_PARAMETERS STRUC
	Module			ULONG64 ?
	TypeId			ULONG ?
	ParentSymbol	ULONG ?
	SubElements		ULONG ?
	Flags			ULONG ?
	Reserved		ULONG64 ?
DEBUG_SYMBOL_PARAMETERS ENDS
PDEBUG_SYMBOL_PARAMETERS TYPEDEF PTR DEBUG_SYMBOL_PARAMETERS
IDebugSymbolGroup STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetNumberSymbols			PANYARGS ?
	AddSymbol					PANYARGS ?
	RemoveSymbolByName			PANYARGS ?
	RemoveSymbolByIndex			PANYARGS ?
	GetSymbolName				PANYARGS ?
	GetSymbolParameters			PANYARGS ?
	ExpandSymbol				PANYARGS ?
	OutputSymbols				PANYARGS ?
	WriteSymbol					PANYARGS ?
	OutputAsType				PANYARGS ?
	AddSymbolWide				PANYARGS ?	;IDebugSymbolGroup2
	RemoveSymbolByNameWide		PANYARGS ?
	GetSymbolNameWide			PANYARGS ?
	WriteSymbolWide				PANYARGS ?
	OutputAsTypeWide			PANYARGS ?
	GetSymbolTypeName			PANYARGS ?
	GetSymbolTypeNameWide		PANYARGS ?
	GetSymbolSize				PANYARGS ?
	GetSymbolOffset				PANYARGS ?
	GetSymbolRegister			PANYARGS ?
	GetSymbolValueText			PANYARGS ?
	GetSymbolValueTextWide		PANYARGS ?
    GetSymbolEntryInformation	PANYARGS ?
IDebugSymbolGroup ENDS
PDEBUG_SYMBOL_GROUP TYPEDEF PTR IDebugSymbolGroup
PDSGROUP TYPEDEF PTR PDEBUG_SYMBOL_GROUP
DEBUG_SYMENT_IS_CODE		equ 1
DEBUG_SYMENT_IS_DATA		equ 2
DEBUG_SYMENT_IS_PARAMETER	equ 4
DEBUG_SYMENT_IS_LOCAL		equ 8
DEBUG_SYMENT_IS_MANAGED		equ 10h
DEBUG_SYMENT_IS_SYNTHETIC	equ 20h
DEBUG_SYMBOL_ENTRY STRUC
	ModuleBase	ULONG64 ?
	_Offset		ULONG64 ?
	Id			ULONG64 ?
	Arg64		ULONG64 ?
	_Size		ULONG ?
	Flags		ULONG ?
	TypeId		ULONG ?
	NameSize	ULONG ?
	Token		ULONG ?
	Tag			ULONG ?
	Arg32		ULONG ?
	Reserved	ULONG ?
DEBUG_SYMBOL_ENTRY ENDS
PDEBUG_SYMBOL_ENTRY TYPEDEF PTR DEBUG_SYMBOL_ENTRY
DEBUG_MODULE_LOADED				equ 0
DEBUG_MODULE_UNLOADED			equ 1
DEBUG_MODULE_USER_MODE			equ 2
DEBUG_MODULE_EXE_MODULE			equ 4
DEBUG_MODULE_EXPLICIT			equ 8
DEBUG_MODULE_SECONDARY			equ 10h
DEBUG_MODULE_SYNTHETIC			equ 20h
DEBUG_MODULE_SYM_BAD_CHECKSUM	equ 10000h
DEBUG_SYMTYPE_NONE		equ 0
DEBUG_SYMTYPE_COFF		equ 1
DEBUG_SYMTYPE_CODEVIEW	equ 2
DEBUG_SYMTYPE_PDB		equ 3
DEBUG_SYMTYPE_EXPORT	equ 4
DEBUG_SYMTYPE_DEFERRED	equ 5
DEBUG_SYMTYPE_SYM		equ 6
DEBUG_SYMTYPE_DIA		equ 7
DEBUG_MODULE_PARAMETERS STRUC
	Base				ULONG64 ?
	_Size				ULONG ?
	TimeDateStamp		ULONG ?
	Checksum			ULONG ?
	Flags				ULONG ?
	SymbolType			ULONG ?
	ImageNameSize		ULONG ?
	ModuleNameSize		ULONG ?
	LoadedImageNameSize	ULONG ?
	SymbolFileNameSize	ULONG ?
	MappedImageNameSize	ULONG ?
	Reserved			ULONG64 ?
DEBUG_MODULE_PARAMETERS ENDS
PDEBUG_MODULE_PARAMETERS TYPEDEF PTR DEBUG_MODULE_PARAMETERS
DEBUG_SCOPE_GROUP_ARGUMENTS		equ 1
DEBUG_SCOPE_GROUP_LOCALS		equ 2
DEBUG_SCOPE_GROUP_ALL			equ 3
DEBUG_OUTTYPE_DEFAULT			equ 0
DEBUG_OUTTYPE_NO_INDENT			equ 1
DEBUG_OUTTYPE_NO_OFFSET			equ 2
DEBUG_OUTTYPE_VERBOSE			equ 4
DEBUG_OUTTYPE_COMPACT_OUTPUT	equ 8
DEBUG_OUTTYPE_RECURSION_LEVEL MACRO Max:REQ
	EXITM <(((Max) AND 0Fh) shl 4)>
ENDM
DEBUG_OUTTYPE_ADDRESS_OF_FIELD	equ 10000h
DEBUG_OUTTYPE_ADDRESS_AT_END	equ 20000h
DEBUG_OUTTYPE_BLOCK_RECURSE		equ 200000h
DEBUG_FIND_SOURCE_DEFAULT		equ 0
DEBUG_FIND_SOURCE_FULL_PATH		equ 1
DEBUG_FIND_SOURCE_BEST_MATCH	equ 2
DEBUG_FIND_SOURCE_NO_SRCSRV		equ 4
DEBUG_FIND_SOURCE_TOKEN_LOOKUP	equ 8
DEBUG_INVALID_OFFSET		equ ((ULONG64) PTR -1)
MODULE_ORDERS_MASK			equ 0F0000000h
MODULE_ORDERS_LOADTIME		equ 10000000h
MODULE_ORDERS_MODULENAME	equ 20000000h
IDebugSymbols STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetSymbolOptions			PANYARGS ?
	AddSymbolOptions			PANYARGS ?
	RemoveSymbolOptions			PANYARGS ?
	SetSymbolOptions			PANYARGS ?
	GetNameByOffset				PANYARGS ?
	GetOffsetByName				PANYARGS ?
	GetNearNameByOffset			PANYARGS ?
	GetLineByOffset				PANYARGS ?
	GetOffsetByLine				PANYARGS ?
	GetNumberModules			PANYARGS ?
	GetModuleByIndex			PANYARGS ?
	GetModuleByModuleName		PANYARGS ?
	GetModuleByOffset			PANYARGS ?
	GetModuleNames				PANYARGS ?
	GetModuleParameters			PANYARGS ?
	GetSymbolModule				PANYARGS ?
	GetTypeName					PANYARGS ?
	GetTypeId					PANYARGS ?
	GetTypeSize					PANYARGS ?
	GetFieldOffset				PANYARGS ?
	GetSymbolTypeId				PANYARGS ?
	GetOffsetTypeId				PANYARGS ?
	ReadTypedDataVirtual		PANYARGS ?
	WriteTypedDataVirtual		PANYARGS ?
	OutputTypedDataVirtual		PANYARGS ?
	ReadTypedDataPhysical		PANYARGS ?
	WriteTypedDataPhysical		PANYARGS ?
	OutputTypedDataPhysical		PANYARGS ?
	GetScope					PANYARGS ?
	SetScope					PANYARGS ?
	ResetScope					PANYARGS ?
	GetScopeSymbolGroup			PANYARGS ?
	CreateSymbolGroup			PANYARGS ?
	StartSymbolMatch			PANYARGS ?
	GetNextSymbolMatch			PANYARGS ?
	EndSymbolMatch				PANYARGS ?
	Reload						PANYARGS ?
	GetSymbolPath				PANYARGS ?
	SetSymbolPath				PANYARGS ?
	AppendSymbolPath			PANYARGS ?
	GetImagePath				PANYARGS ?
	SetImagePath				PANYARGS ?
	AppendImagePath				PANYARGS ?
	GetSourcePath				PANYARGS ?
	GetSourcePathElement		PANYARGS ?
	SetSourcePath				PANYARGS ?
	AppendSourcePath			PANYARGS ?
	FindSourceFile				PANYARGS ?
	GetSourceFileLineOffsets	PANYARGS ?
	GetModuleVersionInformation	PANYARGS ?	;IDebugSymbols2.
	GetModuleNameString			PANYARGS ?
	GetConstantName				PANYARGS ?
	GetFieldName				PANYARGS ?
	GetTypeOptions				PANYARGS ?
	AddTypeOptions				PANYARGS ?
    RemoveTypeOptions			PANYARGS ?
    SetTypeOptions				PANYARGS ?
    GetNameByOffsetWide			PANYARGS ?	;IDebugSymbols3
    GetOffsetByNameWide			PANYARGS ?
    GetNearNameByOffsetWide		PANYARGS ?
    GetLineByOffsetWide			PANYARGS ?
    GetOffsetByLineWide			PANYARGS ?
    GetModuleByModuleNameWide	PANYARGS ?
    GetSymbolModuleWide			PANYARGS ?
    GetTypeNameWide				PANYARGS ?
	GetTypeIdWide				PANYARGS ?
	GetFieldOffsetWide			PANYARGS ?
	GetSymbolTypeIdWide			PANYARGS ?
    GetScopeSymbolGroup2		PANYARGS ?
    CreateSymbolGroup2			PANYARGS ?
    StartSymbolMatchWide		PANYARGS ?
    GetNextSymbolMatchWide		PANYARGS ?
	ReloadWide					PANYARGS ?
	GetSymbolPathWide			PANYARGS ?
	SetSymbolPathWide			PANYARGS ?
	AppendSymbolPathWide		PANYARGS ?
	GetImagePathWide			PANYARGS ?
	SetImagePathWide			PANYARGS ?
	AppendImagePathWide			PANYARGS ?
	GetSourcePathWide			PANYARGS ?
	GetSourcePathElementWide	PANYARGS ?
	SetSourcePathWide			PANYARGS ?
	AppendSourcePathWide		PANYARGS ?
	FindSourceFileWide			PANYARGS ?
	GetSourceFileLineOffsetsWide	PANYARGS ?
	GetModuleVersionInformationWide	PANYARGS ?
	GetModuleNameStringWide		PANYARGS ?
	GetConstantNameWide			PANYARGS ?
	GetFieldNameWide			PANYARGS ?
	IsManagedModule				PANYARGS ?
	GetModuleByModuleName2		PANYARGS ?
	GetModuleByModuleName2Wide	PANYARGS ?
	GetModuleByOffset2			PANYARGS ?
	AddSyntheticModule			PANYARGS ?
    AddSyntheticModuleWide		PANYARGS ?
    RemoveSyntheticModule		PANYARGS ?
    GetCurrentScopeFrameIndex	PANYARGS ?
    SetScopeFrameByIndex		PANYARGS ?
    SetScopeFromJitDebugInfo	PANYARGS ?
    SetScopeFromStoredEvent		PANYARGS ?
    OutputSymbolByOffset		PANYARGS ?
    GetFunctionEntryByOffset	PANYARGS ?
    GetFieldTypeAndOffset		PANYARGS ?
    GetFieldTypeAndOffsetWide	PANYARGS ?
    AddSyntheticSymbol			PANYARGS ?
    AddSyntheticSymbolWide		PANYARGS ?
    RemoveSyntheticSymbol		PANYARGS ?
    GetSymbolEntriesByOffset	PANYARGS ?
    GetSymbolEntriesByName		PANYARGS ?
    GetSymbolEntriesByNameWide	PANYARGS ?
    GetSymbolEntryByToken		PANYARGS ?
    GetSymbolEntryInformation	PANYARGS ?
    GetSymbolEntryString		PANYARGS ?
    GetSymbolEntryStringWide	PANYARGS ?
    GetSymbolEntryOffsetRegions	PANYARGS ?
    GetSymbolEntryBySymbolEntry	PANYARGS ?
    GetSourceEntriesByOffset	PANYARGS ?
    GetSourceEntriesByLine		PANYARGS ?
    GetSourceEntriesByLineWide	PANYARGS ?
    GetSourceEntryString		PANYARGS ?
    GetSourceEntryStringWide	PANYARGS ?
    GetSourceEntryOffsetRegions	PANYARGS ?
    GetSourceEntryBySourceEntry	PANYARGS ?
IDebugSymbols ENDS
PDEBUG_SYMBOLS TYPEDEF PTR IDebugSymbols
PDSYMBOLS TYPEDEF PTR PDEBUG_SYMBOLS
DEBUG_MODNAME_IMAGE			equ 0
DEBUG_MODNAME_MODULE		equ 1
DEBUG_MODNAME_LOADED_IMAGE	equ 2
DEBUG_MODNAME_SYMBOL_FILE	equ 3
DEBUG_MODNAME_MAPPED_IMAGE	equ 4
DEBUG_TYPEOPTS_UNICODE_DISPLAY		equ 1
DEBUG_TYPEOPTS_LONGSTATUS_DISPLAY	equ 2
DEBUG_TYPEOPTS_FORCERADIX_OUTPUT	equ 4
DEBUG_TYPEOPTS_MATCH_MAXSIZE		equ 8
DEBUG_GETMOD_DEFAULT				equ 0
DEBUG_GETMOD_NO_LOADED_MODULES		equ 1
DEBUG_GETMOD_NO_UNLOADED_MODULES	equ 2
DEBUG_ADDSYNTHMOD_DEFAULT			equ 0
DEBUG_ADDSYNTHSYM_DEFAULT			equ 0
DEBUG_OUTSYM_DEFAULT				equ 0
DEBUG_OUTSYM_FORCE_OFFSET			equ 1
DEBUG_OUTSYM_SOURCE_LINE			equ 2
DEBUG_OUTSYM_ALLOW_DISPLACEMENT		equ 4
DEBUG_GETFNENT_DEFAULT				equ 0
DEBUG_GETFNENT_RAW_ENTRY_ONLY		equ 1
DEBUG_MODULE_AND_ID STRUC
	ModuleBase	ULONG64 ?
	Id			ULONG64 ?
DEBUG_MODULE_AND_ID ENDS
PDEBUG_MODULE_AND_ID TYPEDEF PTR DEBUG_MODULE_AND_ID
DEBUG_SOURCE_IS_STATEMENT			equ 1
DEBUG_GSEL_DEFAULT					equ 0
DEBUG_GSEL_NO_SYMBOL_LOADS			equ 1
DEBUG_GSEL_ALLOW_LOWER				equ 2
DEBUG_GSEL_ALLOW_HIGHER				equ 4
DEBUG_GSEL_NEAREST_ONLY				equ 8
DEBUG_SYMBOL_SOURCE_ENTRY STRUC
	ModuleBase		ULONG64 ?
	_Offset			ULONG64 ?
	FileNameId		ULONG64 ?
	EngineInternal	ULONG64 ?
	_Size			ULONG ?
	Flags			ULONG ?
	FileNameSize	ULONG ?
	StartLine		ULONG ?
	EndLine			ULONG ?
	StartColumn		ULONG ?
	EndColumn		ULONG ?
	Reserved		ULONG ?
DEBUG_SYMBOL_SOURCE_ENTRY ENDS
PDEBUG_SYMBOL_SOURCE_ENTRY TYPEDEF PTR DEBUG_SYMBOL_SOURCE_ENTRY
IDebugSystemObjects STRUC
	QueryInterface				QUERYPROC ?
	Addref						ADDPROC   ?
	Release						RELEASEPROC ?
	GetEventThread				PANYARGS ?
	GetEventProcess				PANYARGS ?
	GetCurrentThreadId			PANYARGS ?
	SetCurrentThreadId			PANYARGS ?
	GetCurrentProcessId			PANYARGS ?
	SetCurrentProcessId			PANYARGS ?
	GetNumberThreads			PANYARGS ?
	GetTotalNumberThreads		PANYARGS ?
	GetThreadIdsByIndex			PANYARGS ?
	GetThreadIdByProcessor		PANYARGS ?
	GetCurrentThreadDataOffset	PANYARGS ?
	GetThreadIdByDataOffset		PANYARGS ?
	GetCurrentThreadTeb			PANYARGS ?
	GetThreadIdByTeb			PANYARGS ?
	GetCurrentThreadSystemId	PANYARGS ?
	GetThreadIdBySystemId		PANYARGS ?
	GetCurrentThreadHandle		PANYARGS ?
	GetThreadIdByHandle			PANYARGS ?
	GetNumberProcesses			PANYARGS ?
	GetProcessIdsByIndex		PANYARGS ?
	GetCurrentProcessDataOffset	PANYARGS ?
	GetProcessIdByDataOffset	PANYARGS ?
	GetCurrentProcessPeb		PANYARGS ?
	GetProcessIdByPeb			PANYARGS ?
	GetCurrentProcessSystemId	PANYARGS ?
	GetProcessIdBySystemId		PANYARGS ?
	GetCurrentProcessHandle		PANYARGS ?
	GetProcessIdByHandle		PANYARGS ?
	GetCurrentProcessExecutableName	PANYARGS ?
	GetCurrentProcessUpTime		PANYARGS ?	;IDebugSystemObjects2
	GetImplicitThreadDataOffset	PANYARGS ?
	SetImplicitThreadDataOffset	PANYARGS ?
	GetImplicitProcessDataOffset	PANYARGS ?
	SetImplicitProcessDataOffset	PANYARGS ?
    GetEventSystem				PANYARGS ?	;IDebugSystemObjects3.
	GetCurrentSystemId			PANYARGS ?
	SetCurrentSystemId			PANYARGS ?
	GetNumberSystems			PANYARGS ?
	GetSystemIdsByIndex			PANYARGS ?
	GetTotalNumberThreadsAndProcesses	PANYARGS ?
	GetCurrentSystemServer		PANYARGS ?
	GetSystemByServer			PANYARGS ?
    GetCurrentSystemServerName	PANYARGS ?
    GetCurrentProcessExecutableNameWide	PANYARGS ?
    GetCurrentSystemServerNameWide		PANYARGS ?
IDebugSystemObjects ENDS
PDEBUG_SYSTEM_OBJECT TYPEDEF PTR IDebugSystemObjects
PDSOBJECT TYPEDEF PTR PDEBUG_SYSTEM_OBJECT
DEBUG_COMMAND_EXCEPTION_ID		equ 0DBE00DBEh
DEBUG_CMDEX_INVALID				equ 0
DEBUG_CMDEX_ADD_EVENT_STRING	equ 1
DEBUG_CMDEX_RESET_EVENT_STRINGS	equ 2
IFNDEF DEBUG_NO_IMPLEMENTATION
	OPTION PROLOGUE:rbpFramePrologue
	OPTION EPILOGUE:rbpFrameEpilogue
	.code
	DebugCommandException proc <4> Command:ULONG,ArgSize:ULONG,Arg:PVOID
	LOCAL ExArgs[4]:PVOID
	    mov ExArgs[8*0],DEBUG_COMMAND_EXCEPTION_ID;
	    mov ExArgs[8*1],rcx
	    mov ExArgs[8*2],rdx
	    mov ExArgs[8*3],r8
	    invoke RaiseException,DBG_COMMAND_EXCEPTION,0,4,addr ExArgs
	    ret
	DebugCommandException endp
ENDIF
DEBUG_EXTENSION_VERSION MACRO Major:REQ,Minor:REQ
	EXITM<((((Major) AND 0FFFFh) SHL 16) OR ((Minor) AND 0FFFFh))>
ENDM
DEBUG_EXTINIT_HAS_COMMAND_HELP	equ 1
DEBUG_EXTENSION_INITIALIZE		TYPEDEF PROTO Version:PULONG,Flags:PULONG
PDEBUG_EXTENSION_INITIALIZE		TYPEDEF PTR DEBUG_EXTENSION_INITIALIZE
DEBUG_EXTENSION_UNINITIALIZE	TYPEDEF PROTO
PDEBUG_EXTENSION_UNINITIALIZE	TYPEDEF PTR DEBUG_EXTENSION_UNINITIALIZE
DEBUG_NOTIFY_SESSION_ACTIVE			equ 0
DEBUG_NOTIFY_SESSION_INACTIVE		equ 1
DEBUG_NOTIFY_SESSION_ACCESSIBLE		equ 2
DEBUG_NOTIFY_SESSION_INACCESSIBLE	equ 3
DEBUG_EXTENSION_NOTIFY TYPEDEF PROTO Notify:ULONG,Argument:ULONG64
DEBUG_EXTENSION_CONTINUE_SEARCH		equ HRESULT_FROM_NT(0C0000271h)
DEBUG_EXTENSION_RELOAD_EXTENSION	equ HRESULT_FROM_NT(0C00000EEh)
DEBUG_EXTENSION_CALL TYPEDEF PROTO Client:PDEBUG_CLIENT,Args:PCSTR
PDEBUG_EXTENSION_CALL TYPEDEF PTR DEBUG_EXTENSION_CALL
DEBUG_KNOWN_STRUCT_GET_NAMES				equ 1
DEBUG_KNOWN_STRUCT_GET_SINGLE_LINE_OUTPUT	equ 2
DEBUG_KNOWN_STRUCT_SUPPRESS_TYPE_NAME		equ 3
DEBUG_EXTENSION_KNOWN_STRUCT TYPEDEF PROTO Flags:ULONG,_Offset:ULONG64,\
TypeName:PSTR,Buffer:PSTR,BufferChars:PULONG
PDEBUG_ENTENSION_KNOWNSTRUCT TYPEDEF PTR DEBUG_ENTENSION_KNOWNSTRUCT
DEBUG_EXTENSION_KNOWN_STRUCT_EX TYPEDEF PROTO Client:PDEBUG_CLIENT,Flags:ULONG,_Offset:ULONG64,\
TypeName:PCSTR,Buffer:PSTR,BufferChars:PULONG
PDEBUG_EXTENSION_KNOWN_STRUCT_EX TYPEDEF PTR DEBUG_EXTENSION_KNOWN_STRUCT_EX
PDEBUG_EXTENSION_KNOWN_STRUCT TYPEDEF PDEBUG_ENTENSION_KNOWNSTRUCT
DEBUG_EXT_QVALUE_DEFAULT		equ 0
DEBUG_EXTENSION_QUERY_VALUE_NAMES TYPEDEF PROTO Client:PDEBUG_CLIENT,Flags:ULONG,\
Buffer:PWSTR,BufferChars:ULONG,BufferNeeded:PULONG
PDEBUG_EXTENSION_QUERY_VALUE_NAMES TYPEDEF PTR DEBUG_EXTENSION_QUERY_VALUE_NAMES
DEBUG_EXT_PVALUE_DEFAULT		equ 0
DEBUG_EXT_PVTYPE_IS_VALUE		equ 0
DEBUG_EXT_PVTYPE_IS_POINTER		equ 1
DEBUG_EXTENSION_PROVIDE_VALUE TYPEDEF PROTO Client:PDEBUG_CLIENT,Flags:ULONG,\
_Name:PCWSTR,_Value:PULONG64,TypeModBase:PULONG64,TypeId:PULONG,TypeFlags:PULONG
PDEBUG_EXTENSION_PROVIDE_VALUE TYPEDEF PTR DEBUG_EXTENSION_PROVIDE_VALUE
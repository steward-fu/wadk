;*   KERNEL32.LIB prototypes for MASM
;* (C)hardCode | http://bizarrecreations.webjump.com

include WinExtra\unicode.def

IFNDEF __KERN32PROTOS__
__KERN32PROTOS__=1

_XDEF AddAtom,<:DWORD>

_XDEF AddConsoleAlias,<:DWORD,:DWORD,:DWORD>

AllocConsole PROTO
AreFileApisANSI PROTO
BackupRead PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
BackupSeek PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
BackupWrite PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
BaseAttachCompleteThunk PROTO
Beep PROTO :DWORD,:DWORD

_XDEF BeginUpdateResource,<:DWORD,:DWORD>

_XDEF BuildCommDCB,<:DWORD,:DWORD>

_XDEF BuildCommDCBAndTimeouts,<:DWORD,:DWORD,:DWORD>

_XDEF CallNamedPipe,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CancelIo PROTO :DWORD
CancelWaitableTimer PROTO :DWORD
ClearCommBreak PROTO :DWORD
ClearCommError PROTO :DWORD,:DWORD,:DWORD
CloseConsoleHandle PROTO :DWORD
CloseHandle PROTO :DWORD
CloseProfileUserMapping PROTO
CmdBatNotification PROTO :DWORD

_XDEF CommConfigDialog,<:DWORD,:DWORD,:DWORD>

CompareFileTime PROTO :DWORD,:DWORD

_XDEF CompareString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

ConnectNamedPipe PROTO :DWORD,:DWORD
ConsoleMenuControl PROTO :DWORD,:DWORD,:DWORD
ContinueDebugEvent PROTO :DWORD,:DWORD,:DWORD
ConvertDefaultLocale PROTO :DWORD
ConvertThreadToFiber PROTO :DWORD

_XDEF CopyFile,<:DWORD,:DWORD,:DWORD>

_XDEF CopyFileEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreateConsoleScreenBuffer PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF CreateDirectory,<:DWORD,:DWORD>

_XDEF CreateDirectoryEx,<:DWORD,:DWORD,:DWORD>

_XDEF CreateEvent,<:DWORD,:DWORD,:DWORD,:DWORD>

CreateFiber PROTO :DWORD,:DWORD,:DWORD

_XDEF CreateFile,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CreateFileMapping,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreateIoCompletionPort PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF CreateMailslot,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CreateMutex,<:DWORD,:DWORD,:DWORD>

_XDEF CreateNamedPipe,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreatePipe PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF CreateProcess,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreateRemoteThread PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF CreateSemaphore,<:DWORD,:DWORD,:DWORD,:DWORD>

CreateTapePartition PROTO :DWORD,:DWORD,:DWORD,:DWORD
CreateThread PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateVirtualBuffer PROTO :DWORD,:DWORD,:DWORD

_XDEF CreateWaitableTimer,<:DWORD,:DWORD,:DWORD>

DebugActiveProcess PROTO :DWORD
DebugBreak PROTO

_XDEF DefineDosDevice,<:DWORD,:DWORD,:DWORD>

DeleteAtom PROTO :DWORD
DeleteCriticalSection PROTO :DWORD
DeleteFiber PROTO :DWORD

_XDEF DeleteFile,<:DWORD>

DeviceIoControl PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DisableThreadLibraryCalls PROTO :DWORD
DisconnectNamedPipe PROTO :DWORD
DosDateTimeToFileTime PROTO :DWORD,:DWORD,:DWORD
DuplicateConsoleHandle PROTO :DWORD,:DWORD,:DWORD,:DWORD
DuplicateHandle PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF EndUpdateResource,<:DWORD,:DWORD>

EnterCriticalSection PROTO :DWORD

_XDEF EnumCalendarInfo,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF EnumDateFormats,<:DWORD,:DWORD,:DWORD>

_XDEF EnumResourceLanguages,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF EnumResourceNames,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF EnumResourceTypes,<:DWORD,:DWORD,:DWORD>

_XDEF EnumSystemCodePages,<:DWORD,:DWORD>

_XDEF EnumSystemLocales,<:DWORD,:DWORD>

_XDEF EnumTimeFormats,<:DWORD,:DWORD,:DWORD>

EraseTape PROTO :DWORD,:DWORD,:DWORD
EscapeCommFunction PROTO :DWORD,:DWORD
ExitProcess PROTO :DWORD
ExitThread PROTO :DWORD
ExitVDM PROTO :DWORD,:DWORD

_XDEF ExpandEnvironmentStrings,<:DWORD,:DWORD,:DWORD>

_XDEF ExpungeConsoleCommandHistory,<:DWORD>

ExtendVirtualBuffer PROTO :DWORD,:DWORD

_XDEF FatalAppExit,<:DWORD,:DWORD>

FatalExit PROTO :DWORD
FileTimeToDosDateTime PROTO :DWORD,:DWORD,:DWORD
FileTimeToLocalFileTime PROTO :DWORD,:DWORD
FileTimeToSystemTime PROTO :DWORD,:DWORD
FillConsoleOutputAttribute PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF FillConsoleOutputCharacter,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF FindAtom,<:DWORD>

FindClose PROTO :DWORD
FindCloseChangeNotification PROTO :DWORD

_XDEF FindFirstChangeNotification,<:DWORD,:DWORD,:DWORD>

_XDEF FindFirstFile,<:DWORD,:DWORD>

_XDEF FindFirstFileEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

FindNextChangeNotification PROTO :DWORD

_XDEF FindNextFile,<:DWORD,:DWORD>

_XDEF FindResource,<:DWORD,:DWORD,:DWORD>

_XDEF FindResourceEx,<:DWORD,:DWORD,:DWORD,:DWORD>

FlushConsoleInputBuffer PROTO :DWORD
FlushFileBuffers PROTO :DWORD
FlushInstructionCache PROTO :DWORD,:DWORD,:DWORD
FlushViewOfFile PROTO :DWORD,:DWORD

_XDEF FoldString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF FormatMessage,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

FreeConsole PROTO

_XDEF FreeEnvironmentStrings,<:DWORD>

FreeLibrary PROTO :DWORD
FreeLibraryAndExitThread PROTO :DWORD,:DWORD
FreeResource PROTO :DWORD
FreeVirtualBuffer PROTO :DWORD
GenerateConsoleCtrlEvent PROTO :DWORD,:DWORD
GetACP PROTO

_XDEF GetAtomName,<:DWORD,:DWORD,:DWORD>

_XDEF GetBinaryType,<:DWORD,:DWORD>

GetCPInfo PROTO :DWORD,:DWORD
GetCommConfig PROTO :DWORD,:DWORD,:DWORD
GetCommMask PROTO :DWORD,:DWORD
GetCommModemStatus PROTO :DWORD,:DWORD
GetCommProperties PROTO :DWORD,:DWORD
GetCommState PROTO :DWORD,:DWORD
GetCommTimeouts PROTO :DWORD,:DWORD

_XDEF GetCommandLine,<>

_XDEF GetCompressedFileSize,<:DWORD,:DWORD>

_XDEF GetComputerName,<:DWORD,:DWORD>

_XDEF GetConsoleAlias,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetConsoleAliasExes,<:DWORD,:DWORD>

_XDEF GetConsoleAliasExesLength,<>

_XDEF GetConsoleAliases,<:DWORD,:DWORD,:DWORD>

_XDEF GetConsoleAliasesLength,<:DWORD>

GetConsoleCP PROTO

_XDEF GetConsoleCommandHistory,<:DWORD,:DWORD,:DWORD>

_XDEF GetConsoleCommandHistoryLength,<:DWORD>

GetConsoleCursorInfo PROTO :DWORD,:DWORD
GetConsoleDisplayMode PROTO :DWORD
GetConsoleFontInfo PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetConsoleFontSize PROTO :DWORD,:DWORD
GetConsoleHardwareState PROTO :DWORD,:DWORD,:DWORD

_XDEF GetConsoleInputExeName,<:DWORD,:DWORD>

GetConsoleInputWaitHandle PROTO

_XDEF GetConsoleKeyboardLayoutName,<:DWORD>

GetConsoleMode PROTO :DWORD,:DWORD
GetConsoleOutputCP PROTO
GetConsoleScreenBufferInfo PROTO :DWORD,:DWORD

_XDEF GetConsoleTitle,<:DWORD,:DWORD>

_XDEF GetCurrencyFormat,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetCurrentConsoleFont PROTO :DWORD,:DWORD,:DWORD

_XDEF GetCurrentDirectory,<:DWORD,:DWORD>

GetCurrentProcess PROTO
GetCurrentProcessId PROTO
GetCurrentThread PROTO
GetCurrentThreadId PROTO

_XDEF GetDateFormat,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetDefaultCommConfig,<:DWORD,:DWORD,:DWORD>

_XDEF GetDiskFreeSpace,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetDiskFreeSpaceEx,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetDriveType,<:DWORD>

_XDEF GetEnvironmentStrings,<>

_XDEF GetEnvironmentVariable,<:DWORD,:DWORD,:DWORD>

GetExitCodeProcess PROTO :DWORD,:DWORD
GetExitCodeThread PROTO :DWORD,:DWORD

_XDEF GetFileAttributes,<:DWORD>

_XDEF GetFileAttributesEx,<:DWORD,:DWORD,:DWORD>

GetFileInformationByHandle PROTO :DWORD,:DWORD
GetFileSize PROTO :DWORD,:DWORD
GetFileTime PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetFileType PROTO :DWORD

_XDEF GetFullPathName,<:DWORD,:DWORD,:DWORD,:DWORD>

GetHandleInformation PROTO :DWORD,:DWORD
GetLargestConsoleWindowSize PROTO :DWORD
GetLastError PROTO
GetLocalTime PROTO :DWORD

_XDEF GetLocaleInfo,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetLogicalDriveStrings,<:DWORD,:DWORD>

GetLogicalDrives PROTO
GetMailslotInfo PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF GetModuleFileName,<:DWORD,:DWORD,:DWORD>

_XDEF GetModuleHandle,<:DWORD>

_XDEF GetNamedPipeHandleState,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetNamedPipeInfo PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GetNextVDMCommand PROTO :DWORD

_XDEF GetNumberFormat,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetNumberOfConsoleFonts PROTO
GetNumberOfConsoleInputEvents PROTO :DWORD,:DWORD
GetNumberOfConsoleMouseButtons PROTO :DWORD
GetOEMCP PROTO
GetOverlappedResult PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetPriorityClass PROTO :DWORD

_XDEF GetPrivateProfileInt,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetPrivateProfileSection,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetPrivateProfileSectionNames,<:DWORD,:DWORD,:DWORD>

_XDEF GetPrivateProfileString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetPrivateProfileStruct,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetProcAddress PROTO :DWORD,:DWORD
GetProcessAffinityMask PROTO :DWORD,:DWORD,:DWORD
GetProcessHeap PROTO
GetProcessHeaps PROTO :DWORD,:DWORD
GetProcessPriorityBoost PROTO :DWORD,:DWORD
GetProcessShutdownParameters PROTO :DWORD,:DWORD
GetProcessTimes PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GetProcessVersion PROTO :DWORD
GetProcessWorkingSetSize PROTO :DWORD,:DWORD,:DWORD

_XDEF GetProfileInt,<:DWORD,:DWORD,:DWORD>

_XDEF GetProfileSection,<:DWORD,:DWORD,:DWORD>

_XDEF GetProfileString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetQueuedCompletionStatus PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF GetShortPathName,<:DWORD,:DWORD,:DWORD>

_XDEF GetStartupInfo,<:DWORD>

GetStdHandle PROTO :DWORD

_XDEF GetStringType,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetStringTypeEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetSystemDefaultLCID PROTO
GetSystemDefaultLangID PROTO
_XDEF GetSystemDirectory,<:DWORD,:DWORD>

GetSystemInfo PROTO :DWORD
GetSystemPowerStatus PROTO :DWORD
GetSystemTime PROTO :DWORD
GetSystemTimeAdjustment PROTO :DWORD,:DWORD,:DWORD
GetSystemTimeAsFileTime PROTO :DWORD
GetTapeParameters PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetTapePosition PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GetTapeStatus PROTO :DWORD

_XDEF GetTempFileName,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetTempPath,<:DWORD,:DWORD>

GetThreadContext PROTO :DWORD,:DWORD
GetThreadLocale PROTO
GetThreadPriority PROTO :DWORD
GetThreadPriorityBoost PROTO :DWORD,:DWORD
GetThreadSelectorEntry PROTO :DWORD,:DWORD,:DWORD
GetThreadTimes PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GetTickCount PROTO

_XDEF GetTimeFormat,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetTimeZoneInformation PROTO :DWORD
GetUserDefaultLCID PROTO
GetUserDefaultLangID PROTO
GetVDMCurrentDirectories PROTO :DWORD,:DWORD
GetVersion PROTO

_XDEF GetVersionEx,<:DWORD>

_XDEF GetVolumeInformation,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetWindowsDirectory,<:DWORD,:DWORD>

_XDEF GlobalAddAtom,<:DWORD>

GlobalAlloc PROTO :DWORD,:DWORD
GlobalCompact PROTO :DWORD
GlobalDeleteAtom PROTO :DWORD

_XDEF GlobalFindAtom,<:DWORD>

GlobalFix PROTO :DWORD
GlobalFlags PROTO :DWORD
GlobalFree PROTO :DWORD

_XDEF GlobalGetAtomName,<:DWORD,:DWORD,:DWORD>

GlobalHandle PROTO :DWORD
GlobalLock PROTO :DWORD
GlobalMemoryStatus PROTO :DWORD
GlobalReAlloc PROTO :DWORD,:DWORD,:DWORD
GlobalSize PROTO :DWORD
GlobalUnWire PROTO :DWORD
GlobalUnfix PROTO :DWORD
GlobalUnlock PROTO :DWORD
GlobalWire PROTO :DWORD
HeapAlloc PROTO :DWORD,:DWORD,:DWORD
HeapCompact PROTO :DWORD,:DWORD
HeapCreate PROTO :DWORD,:DWORD,:DWORD
HeapDestroy PROTO :DWORD
HeapExtend PROTO :DWORD,:DWORD,:DWORD,:DWORD
HeapFree PROTO :DWORD,:DWORD,:DWORD
HeapLock PROTO :DWORD
HeapReAlloc PROTO :DWORD,:DWORD,:DWORD,:DWORD
HeapSize PROTO :DWORD,:DWORD,:DWORD
HeapSummary PROTO :DWORD,:DWORD,:DWORD
HeapUnlock PROTO :DWORD
HeapUsage PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
HeapValidate PROTO :DWORD,:DWORD,:DWORD
HeapWalk PROTO :DWORD,:DWORD
InitAtomTable PROTO :DWORD
InitializeCriticalSection PROTO :DWORD
InterlockedCompareExchange PROTO :DWORD,:DWORD,:DWORD
InterlockedDecrement PROTO :DWORD
InterlockedExchange PROTO :DWORD,:DWORD
InterlockedExchangeAdd PROTO :DWORD,:DWORD
InterlockedIncrement PROTO :DWORD
InvalidateConsoleDIBits PROTO :DWORD,:DWORD
IsBadCodePtr PROTO :DWORD
IsBadHugeReadPtr PROTO :DWORD,:DWORD
IsBadHugeWritePtr PROTO :DWORD,:DWORD
IsBadReadPtr PROTO :DWORD,:DWORD

_XDEF IsBadStringPtr,<:DWORD,:DWORD>

IsBadWritePtr PROTO :DWORD,:DWORD
IsDBCSLeadByte PROTO :DWORD
IsDBCSLeadByteEx PROTO :DWORD,:DWORD
IsDebuggerPresent PROTO
IsProcessorFeaturePresent PROTO :DWORD
IsValidCodePage PROTO :DWORD
IsValidLocale PROTO :DWORD,:DWORD

_XDEF LCMapString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

LeaveCriticalSection PROTO :DWORD

_XDEF LoadLibrary,<:DWORD>

_XDEF LoadLibraryEx,<:DWORD,:DWORD,:DWORD>

LoadModule PROTO :DWORD,:DWORD
LoadResource PROTO :DWORD,:DWORD
LocalAlloc PROTO :DWORD,:DWORD
LocalCompact PROTO :DWORD
LocalFileTimeToFileTime PROTO :DWORD,:DWORD
LocalFlags PROTO :DWORD
LocalFree PROTO :DWORD
LocalHandle PROTO :DWORD
LocalLock PROTO :DWORD
LocalReAlloc PROTO :DWORD,:DWORD,:DWORD
LocalShrink PROTO :DWORD,:DWORD
LocalSize PROTO :DWORD
LocalUnlock PROTO :DWORD
LockFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
LockFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
LockResource PROTO :DWORD
MapViewOfFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MapViewOfFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF MoveFile,<:DWORD,:DWORD>

_XDEF MoveFileEx,<:DWORD,:DWORD,:DWORD>

MulDiv PROTO :DWORD,:DWORD,:DWORD
MultiByteToWideChar PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF OpenEvent,<:DWORD,:DWORD,:DWORD>

OpenFile PROTO :DWORD,:DWORD,:DWORD

_XDEF OpenFileMapping,<:DWORD,:DWORD,:DWORD>

_XDEF OpenMutex,<:DWORD,:DWORD,:DWORD>

OpenProcess PROTO :DWORD,:DWORD,:DWORD
OpenProfileUserMapping PROTO

_XDEF OpenSemaphore,<:DWORD,:DWORD,:DWORD>

_XDEF OpenWaitableTimer,<:DWORD,:DWORD,:DWORD>

_XDEF OutputDebugString,<:DWORD>

_XDEF PeekConsoleInput,<:DWORD,:DWORD,:DWORD,:DWORD>

PeekNamedPipe PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
PostQueuedCompletionStatus PROTO :DWORD,:DWORD,:DWORD,:DWORD
PrepareTape PROTO :DWORD,:DWORD,:DWORD
PulseEvent PROTO :DWORD
PurgeComm PROTO :DWORD,:DWORD

_XDEF QueryDosDevice,<:DWORD,:DWORD,:DWORD>

QueryPerformanceCounter PROTO :DWORD
QueryPerformanceFrequency PROTO :DWORD
QueryWin31IniFilesMappedToRegistry PROTO :DWORD,:DWORD,:DWORD,:DWORD
QueueUserAPC PROTO :DWORD,:DWORD,:DWORD
RaiseException PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF ReadConsole,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF ReadConsoleInput,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF ReadConsoleInputEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF ReadConsoleOutput,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

ReadConsoleOutputAttribute PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF ReadConsoleOutputCharacter,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

ReadFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ReadFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ReadProcessMemory PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
RegisterConsoleVDM PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
RegisterWaitForInputIdle PROTO :DWORD
RegisterWowBaseHandlers PROTO :DWORD
RegisterWowExec PROTO :DWORD
ReleaseMutex PROTO :DWORD
ReleaseSemaphore PROTO :DWORD,:DWORD,:DWORD

_XDEF RemoveDirectory,<:DWORD>

ResetEvent PROTO :DWORD
ResumeThread PROTO :DWORD
RtlFillMemory PROTO :DWORD,:DWORD,:DWORD
RtlMoveMemory PROTO :DWORD,:DWORD,:DWORD
RtlUnwind PROTO :DWORD,:DWORD,:DWORD,:DWORD
RtlZeroMemory PROTO :DWORD,:DWORD

_XDEF ScrollConsoleScreenBuffer,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF SearchPath,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

SetCommBreak PROTO :DWORD
SetCommConfig PROTO :DWORD,:DWORD,:DWORD
SetCommMask PROTO :DWORD,:DWORD
SetCommState PROTO :DWORD,:DWORD
SetCommTimeouts PROTO :DWORD,:DWORD

_XDEF SetComputerName,<:DWORD>

SetConsoleActiveScreenBuffer PROTO :DWORD
SetConsoleCP PROTO :DWORD
SetConsoleCommandHistoryMode PROTO :DWORD
SetConsoleCtrlHandler PROTO :DWORD,:DWORD
SetConsoleCursor PROTO :DWORD,:DWORD
SetConsoleCursorInfo PROTO :DWORD,:DWORD
SetConsoleCursorPosition PROTO :DWORD,:DWORD
SetConsoleDisplayMode PROTO :DWORD,:DWORD,:DWORD
SetConsoleFont PROTO :DWORD,:DWORD
SetConsoleHardwareState PROTO :DWORD,:DWORD,:DWORD
SetConsoleIcon PROTO :DWORD

_XDEF SetConsoleInputExeName,<:DWORD>

SetConsoleKeyShortcuts PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetConsoleMaximumWindowSize PROTO :DWORD,:DWORD
SetConsoleMenuClose PROTO :DWORD
SetConsoleMode PROTO :DWORD,:DWORD

_XDEF SetConsoleNumberOfCommands,<:DWORD,:DWORD>

SetConsoleOutputCP PROTO :DWORD
SetConsolePalette PROTO :DWORD,:DWORD,:DWORD
SetConsoleScreenBufferSize PROTO :DWORD,:DWORD
SetConsoleTextAttribute PROTO :DWORD,:DWORD

_XDEF SetConsoleTitle,<:DWORD>

SetConsoleWindowInfo PROTO :DWORD,:DWORD,:DWORD

_XDEF SetCurrentDirectory,<:DWORD>

_XDEF SetDefaultCommConfig,<:DWORD,:DWORD,:DWORD>

SetEndOfFile PROTO :DWORD

_XDEF SetEnvironmentVariable,<:DWORD,:DWORD>

SetErrorMode PROTO :DWORD
SetEvent PROTO :DWORD
SetFileApisToANSI PROTO
SetFileApisToOEM PROTO

_XDEF SetFileAttributes,<:DWORD,:DWORD>

SetFilePointer PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetFileTime PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetHandleCount PROTO :DWORD
SetHandleInformation PROTO :DWORD,:DWORD,:DWORD
SetLastConsoleEventActive PROTO
SetLastError PROTO :DWORD
SetLocalTime PROTO :DWORD

_XDEF SetLocaleInfo,<:DWORD,:DWORD,:DWORD>

SetMailslotInfo PROTO :DWORD,:DWORD
SetNamedPipeHandleState PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetPriorityClass PROTO :DWORD,:DWORD
SetProcessAffinityMask PROTO :DWORD,:DWORD
SetProcessPriorityBoost PROTO :DWORD,:DWORD
SetProcessShutdownParameters PROTO :DWORD,:DWORD
SetProcessWorkingSetSize PROTO :DWORD,:DWORD,:DWORD
SetStdHandle PROTO :DWORD,:DWORD
SetSystemPowerState PROTO :DWORD,:DWORD
SetSystemTime PROTO :DWORD
SetSystemTimeAdjustment PROTO :DWORD,:DWORD
SetTapeParameters PROTO :DWORD,:DWORD,:DWORD
SetTapePosition PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
SetThreadAffinityMask PROTO :DWORD,:DWORD
SetThreadContext PROTO :DWORD,:DWORD
SetThreadIdealProcessor PROTO :DWORD,:DWORD
SetThreadLocale PROTO :DWORD
SetThreadPriority PROTO :DWORD,:DWORD
SetThreadPriorityBoost PROTO :DWORD,:DWORD
SetTimeZoneInformation PROTO :DWORD
SetUnhandledExceptionFilter PROTO :DWORD
SetVDMCurrentDirectories PROTO :DWORD,:DWORD

_XDEF SetVolumeLabel,<:DWORD,:DWORD>

SetWaitableTimer PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
SetupComm PROTO :DWORD,:DWORD,:DWORD
ShowConsoleCursor PROTO :DWORD,:DWORD
SignalObjectAndWait PROTO :DWORD,:DWORD,:DWORD,:DWORD
SizeofResource PROTO :DWORD,:DWORD
Sleep PROTO :DWORD
SleepEx PROTO :DWORD,:DWORD
SuspendThread PROTO :DWORD
SwitchToFiber PROTO :DWORD
SwitchToThread PROTO
SystemTimeToFileTime PROTO :DWORD,:DWORD
SystemTimeToTzSpecificLocalTime PROTO :DWORD,:DWORD,:DWORD
TerminateProcess PROTO :DWORD,:DWORD
TerminateThread PROTO :DWORD,:DWORD
TlsAlloc PROTO
TlsFree PROTO :DWORD
TlsGetValue PROTO :DWORD
TlsSetValue PROTO :DWORD,:DWORD
TransactNamedPipe PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
TransmitCommChar PROTO :DWORD,:DWORD
TrimVirtualBuffer PROTO :DWORD
TryEnterCriticalSection PROTO :DWORD
UnhandledExceptionFilter PROTO :DWORD
UnlockFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
UnlockFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
UnmapViewOfFile PROTO :DWORD

_XDEF UpdateResource,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

VDMConsoleOperation PROTO :DWORD,:DWORD
VDMOperationStarted PROTO :DWORD

_XDEF VerLanguageName,<:DWORD,:DWORD,:DWORD>

VerifyConsoleIoHandle PROTO :DWORD
VirtualAlloc PROTO :DWORD,:DWORD,:DWORD,:DWORD
VirtualAllocEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
VirtualBufferExceptionHandler PROTO :DWORD,:DWORD,:DWORD
VirtualFree PROTO :DWORD,:DWORD,:DWORD
VirtualFreeEx PROTO :DWORD,:DWORD,:DWORD,:DWORD
VirtualLock PROTO :DWORD,:DWORD
VirtualProtect PROTO :DWORD,:DWORD,:DWORD,:DWORD
VirtualProtectEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
VirtualQuery PROTO :DWORD,:DWORD,:DWORD
VirtualQueryEx PROTO :DWORD,:DWORD,:DWORD,:DWORD
VirtualUnlock PROTO :DWORD,:DWORD
WaitCommEvent PROTO :DWORD,:DWORD,:DWORD
WaitForDebugEvent PROTO :DWORD,:DWORD
WaitForMultipleObjects PROTO :DWORD,:DWORD,:DWORD,:DWORD
WaitForMultipleObjectsEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
WaitForSingleObject PROTO :DWORD,:DWORD
WaitForSingleObjectEx PROTO :DWORD,:DWORD,:DWORD

_XDEF WaitNamedPipe,<:DWORD,:DWORD>

WideCharToMultiByte PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
WinExec PROTO :DWORD,:DWORD

_XDEF WriteConsole,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF WriteConsoleInput,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF WriteConsoleInputVDM,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF WriteConsoleOutput,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

WriteConsoleOutputAttribute PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF WriteConsoleOutputCharacter,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

WriteFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
WriteFileEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF WritePrivateProfileSection,<:DWORD,:DWORD,:DWORD>

_XDEF WritePrivateProfileString,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF WritePrivateProfileStruct,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

WriteProcessMemory PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF WriteProfileSection,<:DWORD,:DWORD>

_XDEF WriteProfileString,<:DWORD,:DWORD,:DWORD>

WriteTapemark PROTO :DWORD,:DWORD,:DWORD,:DWORD
_hread PROTO :DWORD,:DWORD,:DWORD
_hwrite PROTO :DWORD,:DWORD,:DWORD
_lclose PROTO :DWORD
_lcreat PROTO :DWORD,:DWORD
_llseek PROTO :DWORD,:DWORD,:DWORD
_lopen PROTO :DWORD,:DWORD
_lread PROTO :DWORD,:DWORD,:DWORD
_lwrite PROTO :DWORD,:DWORD,:DWORD

_XDEF lstrcat,<:DWORD,:DWORD>

_XDEF lstrcmp,<:DWORD,:DWORD>

_XDEF lstrcmpi,<:DWORD,:DWORD>

_XDEF lstrcpy,<:DWORD,:DWORD>

_XDEF lstrcpyn,<:DWORD,:DWORD,:DWORD>

_XDEF lstrlen,<:DWORD>


ENDIF ;__KERN32PROTOS__

{
    This unit contains the record definition for the Win32 RAPI

    Copyright (c) 2006 Free Pascal development team.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{
  rapi.h

  Changes :

  02-15-2006 : orinaudo@gmail.com,  First release
   require ActiveSync installed on the windows PC
   tested with ActiveSync 4.1

}

unit w32rapi;

{$calling stdcall}

interface

uses windows;

{* const **********************************************************************}
const
  RAPILIB = 'rapi.dll';

  CERAPI_E_ALREADYINITIALIZED = $80041001;

{* types **********************************************************************}
type
  TRapiInit = record
    cbSize:DWORD;
    heRapiInit:THandle;
    hrRapiInit:HResult;
  end;

{* functions*******************************************************************}
function CeCloseHandle(hFile: HANDLE):WINBOOL; external RAPILIB name 'CeCloseHandle';
function CeCreateFile( lpFileName:LPCWSTR; dwDesiredAccess:DWORD; dwShareMode: DWORD; lpSecurityAttributes:LPSECURITY_ATTRIBUTES; dwCreationDisposition:DWORD; dwFlagsAndAttributes:DWORD; hTemplateFile:HANDLE): HANDLE; external RAPILIB name 'CeCreateFile';
function CeCreateProcess(lpApplicationName : LPCWSTR; lpCommandLine: LPCWSTR; lpProcessAttributes: LPSECURITY_ATTRIBUTES; lpThreadAttributes:LPSECURITY_ATTRIBUTES; bInheritHandles: BOOL; dwCreationFlags: DWORD; lpEnvironment: LPVOID; lpCurrentDirectory: LPWSTR; lpStartupInfo:LPSTARTUPINFO; lpProcessInformation: LPPROCESS_INFORMATION):WINBOOL; external RAPILIB name 'CeCreateProcess';
function CeDeleteFile(lpFileName: LPCWSTR): WINBOOL; external RAPILIB name 'CeDeleteFile';
function CeGetLastError: DWORD; external RAPILIB name 'CeGetLastError';
function CeReadFile( hFile: HANDLE; lpBuffer: LPVOID; nNumberOfBytesToRead: DWORD; lpNumberOfBytesRead: LPDWORD; lpOverlapped: LPOVERLAPPED):WINBOOL; external RAPILIB name 'CeReadFile';
function CeWriteFile( hFile: HANDLE; lpBuffer: LPCVOID; nNumberOfBytesToWrite: DWORD; lpNumberOfBytesWritten: LPDWORD;  lpOverlapped: LPOVERLAPPED):WINBOOL; external RAPILIB name 'CeWriteFile';
function CeRapiGetError:Longint; external RAPILIB name 'CeRapiGetError';
function CeRapiInit:Longint; external RAPILIB name 'CeRapiInit';
function CeRapiInitEx(var RInit:TRapiInit) : LongInt; external RAPILIB name 'CeRapiInitEx';
function CeRapiUninit:Longint; external RAPILIB name 'CeRapiUninit';
function CeGetFileAttributes(lpFileName:LPCWSTR): longint; external RAPILIB name 'CeGetFileAttributes';
function CeCreateDirectory(lpPathName:LPCWSTR;lpSecurityAttributes:pointer):WINBOOL; external RAPILIB name 'CeCreateDirectory';


implementation

initialization

finalization

end.


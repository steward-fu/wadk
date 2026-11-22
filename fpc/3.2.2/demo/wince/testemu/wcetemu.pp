{
    This program is a local test runner for win32

    Copyright (c) 2006 Free Pascal development team.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{
  Changes :

  02-16-2006 : orinaudo@gmail.com,  First release

}
program wcetemu;

{$mode objfpc}

uses Sysutils, w32rapi, windows, IniFiles;


{* const **********************************************************************}

const
  SREMOTERUNPROG    = 'wcetrun.exe';
  IBLOCKBUFFERSIZE  = 256*1024;
  ISEEKWAITTEMPOMS  = 200;
  ISEEKRETRYMAX     = 180000; // 180 seconds

{* var ************************************************************************}
var
    SREMOTEEXEPATH   : widestring = '\fpctests';
    SLOCALLOGPATHFILE: string;
    flog             : Text;
    sTestExeName     : String;
    lRes,
    WaitTime         : cardinal;
    bExitCode        : Byte;
    RBLOCKBUFFER     : Array[1..IBLOCKBUFFERSIZE] of Byte;
    bFileFound       : boolean;
    CopyFileToDevice : boolean = True;
    LocalTestsRoot   : string;
    RemoteRunner     : string;

{* log ************************************************************************}
procedure log(const csString: String; Error: boolean = False);
begin
 if Error then
   writeln(csString);
 if SLOCALLOGPATHFILE = '' then exit;
 system.writeln(flog,FormatDateTime('yy-mm-dd hh:nn:ss',Now)+' : '+csString);
 system.Flush(flog);
end;

{* sub RAPI *******************************************************************}
function remotecopyto( const csSource, csTarget : String): Longint;
var wsTarget        : WideString;
    lRead,
    lWritten,res,i  : Longint;
    bError          : Boolean;
    hFileTarget     : HANDLE;
    AFileSource     : File of byte;

begin
 // open local file
 {$I-}
 AssignFile(AFileSource,csSource);
 system.FileMode := $40;
 system.Reset(AFileSource);
 {$I+}
 res:=system.ioresult;
 bError:=(res>0);
 if bError then begin
   Log('error opening local file "'+csSource+'" ioresult='+IntToStr(res), True);
   Result:=res;
   exit;
 end;
 try
   //create target file
   wsTarget:=csTarget;
   for i:=1 to 10 do begin
     hFileTarget:=CeCreateFile( PWideChar(wsTarget), GENERIC_WRITE, 0, NIL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,0);
     bError:=(hFileTarget=INVALID_HANDLE_VALUE);
     if not bError then
       break;
     Sleep(1000);
   end;
   if bError then begin
     Result:=CEGetLastError;
     Log('error creating remote file "'+csTarget+'" ce('+IntToStr(CEGetLastError)+') rapi('+IntToStr(ceRapiGetError)+')', True);
     exit;
   end;
   try
    //copy local file by block
    repeat
      {$I-}
      system.BlockRead( AFileSource, RBLOCKBUFFER, IBLOCKBUFFERSIZE, lRead);
      {$I+}
      res:=system.ioresult;
      bError:=res>0;
      if bError then begin
        Log('error readblock local file "'+csTarget+'" toread='+IntToStr(IBLOCKBUFFERSIZE)+' read='+IntToStr(lRead), True);
        Result:=res;
      end
      else begin
        bError:=not CeWriteFile( hFileTarget, @RBLOCKBUFFER,  lRead, @lWritten, nil) or (lRead<>lWritten);
        if bError then begin
          Log('error writing remote file "'+csTarget+'" ce(+'+IntToStr(CEGetLastError)+') written('+IntToStr(lWritten)+')', True);
          Result:=CEGetLastError;
        end;
      end;
     until (lRead<IBLOCKBUFFERSIZE) or (bError);
     if not bError then
       Result:=0;
   finally
     CeCloseHandle(hFileTarget);
   end;
 finally
   CloseFile(AFileSource);
 end;
end;

function remoterun( const csApplication, csCmdLine : String): Longint;
var RPI           : PROCESS_INFORMATION;

    wsCmdLine,
    wsApplication : WideString;
    bError        : boolean;
begin
  wsApplication:=csApplication;
  wsCmdLine:=csCmdLine;

  bError:=not CeCreateProcess(PWideChar(wsApplication), PWideChar(wsCmdLine),nil,nil,FALSE, 0, nil, nil, nil, @RPI );
  Log('remote run "'+csApplication+' '+csCmdLine+'" exitcode='+IntToStr(CeGetLastError)+' bError='+BoolToStr(bError));
  if bError
  then Result:=CeGetLastError
  else begin
   CeCloseHandle (RPI.hThread);
   CeCloseHandle (RPI.hProcess);
   Result:=0;
  end;

end;

function remotedelete( const csTarget : String): Longint;
var wsTarget : WideString;
    bError   : boolean;
begin
  wsTarget:=csTarget;

  bError:=not CeDeleteFile(PWideChar(wsTarget));
  Log('remote delete "'+csTarget+'" exitcode='+IntToStr(CeGetLastError)+' bError='+BoolToStr(bError));
  if bError
  then Result:=CeGetLastError
  else Result:=0;

end;

function remotereadexitcode( const csRemote : String; var vbExitCode: Byte): Longint;
var wsRemote        : WideString;
    lRead           : Longint;
    hFileRemote     : HANDLE;
    bError          : Boolean;
begin
 vbExitCode:=255;
 //create target file
   //change extention to .ext
 wsRemote:=ChangeFileExt(csRemote,'.ext');
 hFileRemote:=CeCreateFile( PWideChar(wsRemote), GENERIC_READ, 0, NIL, OPEN_EXISTING, 0, 0);
 bError:=(hFileRemote=INVALID_HANDLE_VALUE);
 if bError then begin
  Result:=CEGetLastError;
  Log('error opening remote file "'+wsRemote+'" ce('+IntToStr(CEGetLastError)+') rapi('+IntToStr(ceRapiGetError)+')', True);
 end else begin
  try
   //read remote file
   bError:=not (CeReadFile( hFileRemote, @RBLOCKBUFFER,  1, @lRead, nil) and (lRead = 1));
   if (bError) then begin
    Log('error reading remote file "'+csRemote+'" ce('+IntToStr(CEGetLastError)+') read('+IntToStr(lRead)+')', True);
    Result:=CEGetLastError;
    if Result = 0 then
      Result:=255;
   end else begin
    vbExitCode:=RBLOCKBUFFER[1];
    Log('exit code read ='+IntToStr(vbExitCode));
    Result:=0;
   end;
  finally
    CeCloseHandle(hFileRemote);
  end;
 end;
end;

function InitRapi: boolean;
var
  ri: TRapiInit;
  res: cardinal;
begin
  ri.cbSize:=sizeof(ri);
  res:=CeRapiInitEx(ri);
  if (res = S_OK) then begin
    if (WaitForSingleObject(ri.heRapiInit, 10*1000) = WAIT_OBJECT_0) then
      res:=ri.hrRapiInit
    else
      res:=cardinal(E_FAIL);
  end;
  Result:=res = S_OK;
  if not Result then begin
    CeRapiUninit;
    Log('Can''''t initialize connection to remote device.', True);
  end;
end;

{******************************************************************************}

procedure ProcessCmdLine;
var
  i: integer;
  s: string;

  function GetNextParam(HaltOnEnd: boolean): string;
  begin
    Inc(i);
    if i > ParamCount then begin
      if HaltOnEnd then begin
        writeln('Incorrect parameters.');
        Halt(2);
      end;
      Result:='';
    end
    else
      Result:=ParamStr(i);
  end;
  
var
  ini: TIniFile;
  
begin
 if ParamCount = 0 then begin
   writeln('Usage: ' + ExtractFileName(ParamStr(0)) + ' [-L <log_file>] [-R <remote_path>] <test_to_run>');
   writeln('-L - write log to <log_file>.');
   writeln('-R - path in Pocket PC device where <test_to_run> program will be copied.');
   writeln('     default path: ' + SREMOTEEXEPATH);
   Halt(1);
 end;
 
 s:=ChangeFileExt(ParamStr(0), '.ini');
 if FileExists(s) then begin
   ini:=TIniFile.Create(s);
   try
     SLOCALLOGPATHFILE:=ini.ReadString('Options', 'LogToFile', SLOCALLOGPATHFILE);
     SREMOTEEXEPATH:=ini.ReadString('Options', 'RemotePath', SREMOTEEXEPATH);
     CopyFileToDevice:=ini.ReadBool('Options', 'CopyFile', CopyFileToDevice);
     LocalTestsRoot:=ini.ReadString('Options', 'LocalTestsRoot', LocalTestsRoot);
   finally
     ini.Free;
   end;
 end;
 
 i:=0;
 while True do begin
   s:=GetNextParam(False);
   if s = '' then
     break;
   if Copy(s, 1, 2) = '-L' then
     SLOCALLOGPATHFILE:=GetNextParam(True)
   else
   if Copy(s, 1, 2) = '-R' then
     SREMOTEEXEPATH:=GetNextParam(True)
   else
     if sTestExeName = '' then
       sTestExeName:=s
     else
       begin
         writeln('Incorrect parameters.');
         Halt(2);
       end;
 end;
 SREMOTEEXEPATH:=IncludeTrailingPathDelimiter(SREMOTEEXEPATH);
 RemoteRunner:=SREMOTEEXEPATH + SREMOTERUNPROG;
 if not CopyFileToDevice and (LocalTestsRoot<>'') then begin
   s:=IncludeTrailingPathDelimiter(GetCurrentDir);
   LocalTestsRoot:=IncludeTrailingPathDelimiter(LocalTestsRoot);
   if AnsiCompareText(LocalTestsRoot, Copy(s, 1, Length(LocalTestsRoot))) = 0 then
     SREMOTEEXEPATH:=IncludeTrailingPathDelimiter(SREMOTEEXEPATH + Copy(s, Length(LocalTestsRoot)+1, MaxInt));
 end;
end;

{******************************************************************************}

begin
 ProcessCmdLine;
 if SLOCALLOGPATHFILE <> '' then begin
   system.FileMode := $42;
   system.Assign(flog,SLOCALLOGPATHFILE);
   {$I-}
   system.Append(flog);
   {$I+}
   if (system.ioresult>0) then begin
    system.Rewrite(flog);
    log('log rewrite');
   end else log('log append');
 end;

 try
   if not InitRapi then
     Halt(255);
   if CopyFileToDevice then begin
     CeCreateDirectory(PWideChar(widestring(ExcludeTrailingPathDelimiter(SREMOTEEXEPATH))), nil);
     remotedelete(ChangeFileExt(SREMOTEEXEPATH+sTestExeName, '.ext'));
     //copy file
     log('remote copy "'+sTestExeName+'" to "'+SREMOTEEXEPATH+sTestExeName+'"');
     lRes:=remotecopyto(sTestExeName, SREMOTEEXEPATH+sTestExeName);
     if lRes<>0 then
       Halt(255);  // source file not found
   end;

   while True do begin
     lRes:=remoterun(RemoteRunner,'"'+SREMOTEEXEPATH+sTestExeName+'"');
     if lRes<>0 then begin
       // check exec stub file
       if CeGetFileAttributes(PWideChar(widestring(RemoteRunner))) <> -1  then begin
         log('Unable to run "'+RemoteRunner+'"', True);
         Halt(255);
       end;
       if remotecopyto(ExtractFilePath(ParamStr(0)) + SREMOTERUNPROG, RemoteRunner) <> 0 then
         Halt(255);  // exec stub file not found
     end
     else
       break;
   end;

   // waiting for result file creation (waitforsingleobject and getexitcodprocess not available with rapi)
   log('Waiting for result file...');
   WaitTime:=GetTickCount;
   bFileFound:=False;
   repeat
     if CeGetFileAttributes(PWideChar(widestring(ChangeFileExt(SREMOTEEXEPATH+sTestExeName, '.ext')))) <> -1  then begin
       bFileFound:=True;
       break;
     end
     else
       Sleep(ISEEKWAITTEMPOMS);
   until GetTickCount - WaitTime >= ISEEKRETRYMAX;

   if bFileFound then begin
     // reading result file
     WaitTime:=GetTickCount;
     bFileFound:=False;
     repeat
       log('remote read exitcode"'+SREMOTEEXEPATH+sTestExeName+'"');
       lRes:=remotereadexitcode(SREMOTEEXEPATH+sTestExeName, bExitCode);
       bFileFound:=(lRes=0);
       if bFileFound then begin
         if CopyFileToDevice then
           remotedelete(ChangeFileExt(SREMOTEEXEPATH+sTestExeName, '.ext'));
         break;
       end;
       Sleep(ISEEKWAITTEMPOMS);
     until GetTickCount - WaitTime >= 30000;
   end;
   
   // deleting remote file
   if CopyFileToDevice then
     remotedelete(SREMOTEEXEPATH+sTestExeName);

   CeRapiUninit;
   
   if (not bFileFound) then begin
     log('* error no exitcode for "'+sTestExeName+'"', True);
     bExitCode:=255; //error code, result file not found
   end;
 finally
   if SLOCALLOGPATHFILE <> '' then begin
     log('log closed');
     Close(flog);
   end;
 end;
 
 if bExitCode>0 then
   Halt(bExitCode);
end.

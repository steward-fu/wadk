{
    This program is a remote test runner for wince

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
program wcetrun;

{$mode objfpc}
{$apptype console}

uses
  SysUtils, windows;

var wsTestExeName,
    wsTestExtName : WideString;
    RPI           : PROCESS_INFORMATION;
    RSTARTUP      : STARTUPINFO;
    bError        : boolean;
    bExitCode     : Byte;
    i,
    lExitCode     : Longint;
    FileExit      : File of byte;
begin
  if Paramcount>0 then begin
   try
     wsTestExeName:=ParamStr(1);
     writeln('wcerun - starting='+wsTestExeName);
     //create process
     FillChar(RSTARTUP,SizeOf(RSTARTUP),0);
     RSTARTUP.cb:=SizeOf(RSTARTUP);
     if CreateProcess(PWideChar(wsTestExeName), nil,nil,nil,FALSE, 0, nil, nil, @RSTARTUP, RPI ) then begin
       writeln('wcerun - waiting return');
       //wait end
       if WaitForSingleObject(RPI.hProcess, 3*60*1000) = WAIT_OBJECT_0 then begin
         writeln('wcerun - finished, get exit code');
         //get exitcode
         GetExitCodeProcess(RPI.hProcess, @lExitCode);
         writeln('wcerun - exitcode=', lExitCode);
       end
       else begin
         writeln('wcerun - process did not exit.');
         lExitCode:=255;
       end;
       CloseHandle (RPI.hThread);
       CloseHandle (RPI.hProcess);
     end
     else
       lExitCode:=255;
     //create file with exit code
     //change extension
     wsTestExtName:=ChangeFileExt(wsTestExeName,'.ext');

     if lExitCode<255 then
       bExitCode:=byte(lExitCode)
     else
       bExitCode:=255;
   except
     bExitCode:=255;
   end;
   system.assign(FileExit,wsTestExtName);
   for i:=1 to 10 do
     try
       system.rewrite(FileExit);
       break;
     except
       Sleep(1000);
     end;
   write(FileExit,bExitCode);
   system.Close(FileExit);
  end
  else
    writeln('wcterun - exiting no params');
end.

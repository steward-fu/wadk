{
    This program is part of the FPC demoes.
    Copyright (C) 2006 by Ales Katona
  
    A test for sendfile syscall that allows high speed streaming
    of files.
    The program forks to be both receiver and sender.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
program demo_sendfile;

{$mode objfpc}{$H+}

uses
  SysUtils, BaseUnix, FreeBSD, Sockets;
  
procedure Bail(const Error: Integer);
begin
  Writeln('Error: ', Error);
  Halt(1);
end;

procedure SetupSocket(var aSocket: Integer; var aAddress: TInetSockAddr;
                      const aIP: string; const aPort: Word);
begin
  aSocket:=fpSocket(AF_INET, SOCK_STREAM, 6);
  if aSocket < 0 then
    Bail(fpgeterrno);

  with aAddress do begin
    Family:=AF_INET;
    Port:=htons(aPort);
    Addr:=LongInt(StrToNetAddr(aIP));
  end;
end;

procedure Sender;
var
  aSocket, aFile: Integer;
  Sent: Int64;
  Address: TInetSockAddr;
begin
  Sleep(500); // wait so the other side can start accepting
  aFile:=fpOpen(ParamStr(1), O_RDONLY); // get the file fd
  if aFile < 0 then
    Bail(fpgeterrno);
    
  SetupSocket(aSocket, Address, '127.0.0.1', Word(StrToInt(ParamStr(3))));
    
  Write('SENDER: Connecting...');
  if fpConnect(aSocket, @Address, sizeof(Address)) = 0 then begin
    Write('SENDER: Connected.. sending.. ');
    Sent:=0;
    { send the whole file in one syscall, blocking,
       arguments: fd of file to send, socket to send to (blocking mode depends on it),
                           offset (where to begin reading/int64), count to send (0 means until EOF), 
                           "header/trailer record", bytes sent (int64), flags (1 = don't wait for IO) }
    if SendFile(aFile, aSocket, 0, 0, nil, @Sent, 0) < 0 then
      Bail(fpgeterrno);
    Writeln('SENDER: Sent: ', Sent, ' bytes.');
    fpShutDown(aSocket, 2);
    fpClose(aSocket);
  end else Bail(fpgeterrno);
  FpClose(aFile);
end;

procedure Receiver;
const
  BUFFER_SIZE = 65535;
var
  ServerSocket, ClientSocket, Received, AddressLength: Integer;
  Address: TInetSockAddr;
  aFile: file of Byte;
  Buffer: array[0..BUFFER_SIZE] of Byte;
begin
  AssignFile(aFile, ParamStr(2));
  ReWrite(aFile);
  SetupSocket(ServerSocket, Address, '0.0.0.0', Word(StrToInt(ParamStr(3))));
  
  AddressLength:=SizeOf(Address);
  if fpBind(ServerSocket, @Address, SizeOf(Address)) < 0 then
    Bail(fpgeterrno);
  if fpListen(ServerSocket, 1) < 0 then
    Bail(fpgeterrno);
    
  Write('RECEIVER: accepting... ');
  ClientSocket:=fpAccept(ServerSocket, @Address, @AddressLength);
  if ClientSocket < 0 then
    Bail(fpgeterrno);
  Write('RECEIVER: Accepted. Receiving... ');
  repeat
    Received:=fpRecv(ClientSocket, @Buffer[0], BUFFER_SIZE, 0);
    if Received < 0 then
      Bail(fpgeterrno);
    BlockWrite(aFile, Buffer[0], Received);
  until Received <= 0;
  Writeln('RECEIVER: Done.');
  CloseFile(aFile);
  fpShutDown(ClientSocket, 2);
  fpClose(ClientSocket);
  fpClose(ServerSocket);
end;

begin
  if (ParamCount = 3) and FileExists(ParamStr(1)) then begin
    if fpFork > 0 then
      Sender
    else begin
      Receiver;
    end;
  end else Writeln('Usage: ', ParamStr(0), ' <inputfile> <outputfile> <port>');
end.

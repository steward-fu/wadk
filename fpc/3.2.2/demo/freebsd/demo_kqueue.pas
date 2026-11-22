{
    This program is part of the FPC demoes.
    Copyright (C) 2006 by Ales Katona
 
    A demo that demonstrates the *BSD Kqueue call  

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

program demo_kqueue;

{$mode objfpc}{$H+}

uses
  SysUtils, BaseUnix, BSD;

var
  TheQueue, PID: Integer;
  EventRec: TKEvent;
begin
  Flush(output);
  PID:=fpFork;
  if PID > 0 then begin
    TheQueue:=KQueue;  // get a new queue, process can have more than one
    if TheQueue < 0 then
      Writeln('Error on KQueue');

    { First clear the "setter record" then set the process handle
      to the record and set it to watch for process events. If one happens
      add it to queue but clear after it's retrieved }
    FillChar(EventRec, SizeOf(EventRec), 0);
    EV_SET(@EventRec, PID, EVFILT_PROC, EV_ADD or EV_CLEAR, 0, 0, nil);

    Writeln('Waiting for child to quit...');
    { This is a combined call which saves one syscall. This call
      first SETS the event record "EventRec" as we set it above and right afterwards
      waits indefenetly until given event happens. When it does, it writes back
      to the same record the result of what happened. }
    if KEvent(TheQueue, @EventRec, 1, @EventRec, 1, nil) > 0 then // combined action
      Writeln('Child has quit')
    else
      Writeln('KEvent error');
    Writeln('Parent quitting');
  end else begin
    Writeln('Child waiting 5 seconds');
    Sleep(5000);
    Writeln('Child quitting');
  end;
end.


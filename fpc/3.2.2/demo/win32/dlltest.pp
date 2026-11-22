{
  Copyright (c) 1998 by Pierre Muller

  Win32 DLL usage example. It needs testdll.pp
}
program dlltest;

procedure p1(var S : string);
 external 'testdll' name 'P1';
procedure proc2(x:longint);
 external 'testdll' name 'Proc2';

var
   s : string;external 'testdll' name 'FPC_string';
   s2 : string;

begin
  writeln('Main: Hello!');
  s2:='Test before';
  p1(s2);
  if s2<>'New value' then
    begin
      Writeln('Error while calling P1');
      Halt(1);
    end;
  writeln('Main: ',Hinstance,' ',Hprevinst);
  writeln('Main: testdll s string = ',s);
  s:='Changed by program';
  proc2(1234);
  writeln('Main: press enter');
  readln;
end.

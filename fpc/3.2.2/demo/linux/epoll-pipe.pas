
// demonstration file for the epoll() linux specific call, by Micha
// Nelissen

program epoll_pipe;

{$mode objfpc}{$h+}

uses
  baseunix, unix, linux;

const
  NumPipes = 100;
  NumActive = 1;
  NumWrites = NumPipes;
  NumRuns = 16;

var
  gPipes: array of tfildes;
  gEvents: array of epoll_event;
  gCount, gFired, gWrites: integer;
  epoll_fd: integer;
  
function getustime: qword;
var
  tm: timeval;
begin
  fpgettimeofday(@tm, nil);
  result := tm.tv_sec * 1000000 + tm.tv_usec;
end;
  
procedure read_cb(fd, idx: integer);
var
  widx: integer;
  ch: char;
begin
  widx := idx + NumActive + 1;
  
  if fpread(fd, ch, sizeof(ch)) <> 0 then
    inc(gCount)
  else
    writeln('false read event: fd=', fd, ' idx=', idx);

  if gWrites <> 0 then
  begin
    if widx >= NumPipes then
      dec(widx, NumPipes);
    fpwrite(gPipes[widx][1], 'e', 1);
    dec(gWrites);
    inc(gFired);
  end;
end;

procedure run_once(var work: integer; var tr: qword);
var
  i, res: integer;
  ts, te: qword;
begin
  gFired := 0;
  for i := 0 to NumActive-1 do
  begin
    fpwrite(gPipes[i][1], 'e', 1);
    inc(gFired);
  end;

  gCount := 0;
  gWrites := NumWrites;
  ts := getustime;
  repeat
    res := epoll_wait(epoll_fd, @gEvents[0], NumPipes, 0);
    for i := 0 to res-1 do
      read_cb(gPipes[gEvents[i].data.u32][0], gEvents[i].data.u32);
  until gCount = gFired;
  te := getustime;

  tr := te-ts;
  work := gCount;
end;

var
  lEvent: epoll_event;
  i, work: integer;
  tr: qword;
begin
  SetLength(gEvents, NumPipes);
  SetLength(gPipes, NumPipes);
  epoll_fd := epoll_create(NumPipes);
  if epoll_fd = -1 then
  begin
    writeln('error calling epoll_create');
    halt(1);
  end;

  for i := 0 to NumPipes-1 do
  begin
    if fppipe(gPipes[i]) = -1 then
    begin
      writeln('error calling pipe');
      halt(1);
    end;
    fpfcntl(gPipes[i][0], F_SETFL, fpfcntl(gPipes[i][0], F_GETFL) or O_NONBLOCK);

    lEvent.events := EPOLLIN;
    lEvent.data.u32 := i;
    if epoll_ctl(epoll_fd, EPOLL_CTL_ADD, gPipes[i][0], @lEvent) < 0 then
    begin
      writeln('error calling epoll_ctl');
      halt(1);
    end;
  end;
  
  for i := 0 to NumRuns-1 do
  begin
    run_once(work, tr);
    if work = 0.0 then
      halt(1);
    writeln(double(tr)/double(work):10:7);
  end;
end.


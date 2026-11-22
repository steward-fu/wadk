{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2019 by Nikolay Nikolov

    Sorting Algorithms Animations Demo (in text mode)

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

program sortdemo;

{$MODE objfpc}

uses
  Video, Keyboard, SortBase, SysUtils;

var
  Arr: array of Integer;
  LastComp1, LastComp2: Integer;

procedure TextOut(X, Y: Word; const S: string);
var
  W, P, I, M: Word;
begin
  P := (X - 1) + (Y - 1) * ScreenWidth;
  M := Length(S);
  if P + M > ScreenWidth * ScreenHeight then
    M := ScreenWidth * ScreenHeight - P;
  for I := 1 to M do
    VideoBuf^[P + I - 1] := Ord(S[i]) + ($07 shl 8);
end;

procedure InitArr;
var
  I: Integer;
begin
  LastComp1 := -1;
  LastComp2 := -1;
  SetLength(Arr, ScreenHeight);
  for I := 0 to Length(Arr) - 1 do
    Arr[I] := I;
end;

procedure ShuffleArr;
const
  NumSwaps = 100;
var
  I, A1, A2, tmp: Integer;
begin
  InitArr;
  for I := 1 to NumSwaps do
  begin
    A1 := Random(Length(Arr));
    A2 := Random(Length(Arr));
    tmp := Arr[A1];
    Arr[A1] := Arr[A2];
    Arr[A2] := tmp;
  end;
end;

procedure FewUniqueArr;
var
  I: Integer;
begin
  InitArr;
  for I := 0 to Length(Arr) - 1 do
    Arr[I] := Random(4) * (Length(Arr) - 1) div 3;
end;

procedure ReversedArr;
var
  I: Integer;
begin
  LastComp1 := -1;
  LastComp2 := -1;
  SetLength(Arr, ScreenHeight);
  for I := 0 to Length(Arr) - 1 do
    Arr[I] := Length(Arr) - I - 1;
end;

procedure DrawArr;
var
  I, X: Integer;
  Attr: Byte;
begin
  for I := 0 to Length(Arr) - 1 do
  begin
    if (I = LastComp1) or (I = LastComp2) then
      Attr := $6E
    else
      Attr := $0F;
    for X := 0 to Arr[I] do
    begin
      if X >= ScreenWidth then
        break;
      VideoBuf^[I * ScreenWidth + X] := Ord('#') + (Attr shl 8);
    end;
    for X := Arr[I] + 1 to ScreenWidth - 1 do
      VideoBuf^[I * ScreenWidth + X] := Ord(' ') + ($07 shl 8);
  end;
end;

function Comparer(Item1, Item2, Context: Pointer): Integer;
begin
  Result := PInteger(Item1)^ - PInteger(Item2)^;
  LastComp1 := (Item1 - @Arr[0]) div SizeOf(Arr[0]);
  LastComp2 := (Item2 - @Arr[0]) div SizeOf(Arr[0]);
  DrawArr;
  UpdateScreen(False);
  Sleep(10);
end;

procedure Exchanger(Item1, Item2, Context: Pointer);
var
  tmp: Integer;
begin
  tmp := PInteger(Item1)^;
  PInteger(Item1)^ := PInteger(Item2)^;
  PInteger(Item2)^ := tmp;
  LastComp1 := -1;
  LastComp2 := -1;
  DrawArr;
  UpdateScreen(False);
  Sleep(10);
end;

procedure DemonstrateAlgorithm(SortingAlgorithm: PSortingAlgorithm);
begin
  SortingAlgorithm^.ItemListSorter_CustomItemExchanger_ContextComparer(
    @Arr[0], Length(Arr), SizeOf(Arr[0]), @Comparer, @Exchanger, nil);

  LastComp1 := -1;
  LastComp2 := -1;
  DrawArr;
  TextOut(50, 10, 'Done!');
  UpdateScreen(False);
end;

begin
  Randomize;

  InitVideo;
  InitKeyboard;

  repeat
    case Random(3) of
      0: ShuffleArr;
      1: ReversedArr;
      2: FewUniqueArr;
    end;
    DrawArr;
    UpdateScreen(True);

    DemonstrateAlgorithm(@QuickSort);
    Sleep(1000);
  Until True;

//  Readln;

  DoneKeyboard;
  DoneVideo;
end.

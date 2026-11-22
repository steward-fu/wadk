Program cgibmp;
{   This file is a Free Pascal example
    Copyright (C) 2001 by Marco van de Voort
        member of the Free Pascal development team.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    A CGI (page counter) in pascal, without libraries or delphi features.

    HTML query (different counter variables) not implemented yet.
    The first argument will become the variable name.

    Note, this is just meant as a demonstration of principle, and not as production 

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
}

uses strings,
     baseunix;

Const max_data = 1000;

Type
  TBMPHeadtype = packed Record  {Headers for BMP. Putting them in one record is easier}
           { bit map file header }
                         bftype: word;                   { "BM" or $4D42 }
                         bfsize: longint;                { size of file in bytes }
                         bfreserved1: word;
                         bfreserved2: word;
                         bfoffbits: longint;             { ^ where graphic data begins }
           { bit map information header }
                         bisize: longint;                { length of this header, $28 }
                         biwidth: longint;               { pixel width }
                         biheight: longint;              { pixel height }
                         biplanes: word;                 { = 1 }
                         bibitcount: word;               { color bits per pixel }
                         bicompression: longint;         { = 0 for no compression }
                         bisizeimage: longint;           { = bfsize - bfoffbits }
                         bixpelspermeter: longint;       { x pixels per meter }
                         biypelspermeter: longint;       { y pixels per meter }
                         biclrused: longint;             { \ I have never seen these }
                         biclrimportant: longint;        { / two used for anything }
         End;


        { 10 characters (character 0..9) , 12x8 dimension
            (some VGA font with four colums zeros deleted)}

Const Font : ARRAY[0..119] Of BYTE = (
                                      0,24,36,36,66,66,66,36,36,24,0,0,
                                      0,24,40,72,8,8,8,8,8,8,0,0,
                                      0,60,66,2,4,8,16,32,64,126,0,0,
                                      0,60,66,2,2,28,2,2,66,60,0,0,
                                      0,4,12,20,36,68,254,4,4,4,0,0,
                                      0,126,64,64,124,66,2,2,66,60,0,0,
                                      0,28,34,64,64,92,98,66,66,60,0,0,
                                      0,126,2,2,4,4,8,8,16,16,0,0,
                                      0,60,66,66,66,60,66,66,66,60,0,0,
                                      0,60,66,66,70,58,2,2,68,56,0,0);

Var 
    Thousands,                   {Counter digits}
    Hundreds,
    Tens,
    one     : LONGINT;
    hdr     : TBMPHeadtype;      {BMP header}
    Rows    : LONGINT;          {Generic counter, and counter for
                                 Rows of picture}
    BytePtr : ^BYTE;            {Used to output header}
    nrdata  : longint;
    p       : PChar;
    literal,
    aname   : boolean;
    F       : file;
    Count   : LONGINT;
    Dummy   : LONGINT;

Begin
  writeln(sizeof(tbmpheadtype));
  If StrComp(fpgetenv('REQUEST_METHOD'),'GET')<>0 Then
    Begin
      Writeln ('Content-type: text/html');
      Writeln;
      Writeln ('This script should be referenced with a METHOD of GET');
      halt(1);
    End;

   Writeln ('Content-type: image/bmp');
   Writeln;
  
   // one could expand this to allow more variables based on the querystring.
   p := fpgetenv('QUERY_STRING');

   Assign (f,'count');
   {$I-}
   reset(F,1);
   {$I+}
   If IORESULT<>0 Then
     Begin
       Assign(F,'count');
       rewrite(F);
       Close(F);
       Assign(F,'count');
       reset(F,1);
       Count := 0;
     End
   Else
     Begin
       Blockread(F,Count,4,Dummy);
       Seek(F,0);
     End;
    INC(Count);
    BlockWrite(F,Count,4);
    Close(F);

 {Set up BMP-header}


  FillChar(hdr,SIZEOF(tBmpheadtype),0);
  With Hdr Do
    Begin
      bftype := $4D42;                 { "BM" or $4D42 }
      bfsize := 54+8+4*12;             { size of file in bytes }
      bfreserved1 := 0;
      bfreserved2 := 0;
      bfoffbits := $3E;            { where graphic data begins }
      bisize := 40;                    { length of this header }
      biwidth := 32;                  { pixel width }
      biheight := 12;                 { pixel height }
      biplanes := 1;                   { =1 }
      bibitcount := 1;                 { color bits per pixel }
      bicompression := 0;              { =0 for no compression }
      bisizeimage := bfsize-bfoffbits;
      bixpelspermeter := 0;
      biypelspermeter := 0;
      biclrused := 0;
      biclrimportant := 0;
    End;

 {Output BMP-header to standard out}

  BytePtr := @Hdr;
  For Rows:=0 To sizeof(TBMPHeadType)-1 Do
    write(CHR(Byteptr[Rows]));

 {Output colors/palette}

  Write(#255,#255,#255,#0,#0,#0,#0,#0);

 { Split up into digits}

  Thousands := Count Div 1000;
  Count     := Count Mod 1000;
  Hundreds  := Count Div 100;
  Count     := Count Mod 100;
  Tens      := Count Div 10;
  One 	    := Count Mod 10;
  If Thousands>9 Then Thousands := 9;

 { Print bitmapdata}

  For Rows := 11 Downto 0 Do { Rows loop}
    Begin
   {Construct bitmap line}
      Write(CHR(Font[12*Thousands+Rows]));
      Write(CHR(Font[12*Hundreds+Rows]));
      Write(CHR(Font[12*Tens+Rows]));
      Write(CHR(Font[12*One+Rows]));
    End;
End.

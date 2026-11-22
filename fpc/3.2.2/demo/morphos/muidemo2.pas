{

    Creating a simple MUI custom class, using MUI and MUIHelper units
    Free Pascal for MorphOS example

    Copyright (C) 2006 by Karoly Balogh

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ ** Quick & Dirty coding, but should provide a few useful hints. ** }
{ ** Some better examples will follow. ** }

{$inline on}
{$macro on}
program muidemo2;

uses exec, amigados, intuition, mui, amigalib, utility, muihelper;

// temp hack
const
  TRAP_LIB             = $ff00;

var
  app: pObject_;
  win: pObject_;

  signals: longword;
  retval: longword;
  quitapp: boolean;

  quitbutton: pObject_;
  my_Stuff: PMUI_CustomClass;

{$warning wtf?!}
const
  MUIM_my_Toggle = $ab00f000; // wtf?

function TAG(value: pointer): longword; inline;
begin
  TAG:=longword(value);
end;

function TAG(value: pchar): longword; inline;
begin
  TAG:=longword(value);
end;

const 
  sayings: array[0..3] of PChar = (MUIX_R+'w00t...?', MUIX_L+'b00...!!11',MUIX_C+':: 0wn3d! ::',MUIX_C+'l33t h4x0r');

type pmy_Data = ^tmy_Data;
     tmy_Data = record
        curr_Saying: dword;
        saying: pObject_;
     end;


// my Subclass
// ********************************************************************
function my_New(cl: pIClass; obj: pObject_; msg: pOpSet): LongWord; cdecl;
var button: pObject_;
    saying: pObject_;
    data: pmy_Data;
begin
  DWord(obj):=DoSuperNew(cl, obj, 
      [ Child, TAG(MH_VGroup('Teh Butt0n Klass',
          [ Child, TAG(MH_Text(saying,sayings[0])),
            Child, TAG(MH_MakeButton(button,'r0x0r')),
            TAG_DONE
          ])),
      TAG_MORE, DWord(msg^.ops_AttrList)]);

  if obj <> nil then begin
    data:=INST_DATA(cl,p_Object(obj));
 
    data^.saying:=saying;
    data^.curr_Saying:=0;

    DoMethod(button, [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, TAG(obj), 1, MUIM_my_Toggle ]);
  end;

  my_New:=DWord(obj);
end;

function my_Toggle(data: pmy_Data): longword;
begin
  with data^ do begin
    inc(curr_Saying);
    if curr_Saying > 3 then curr_Saying:=0;
   
    MUIset(saying, MUIA_Text_Contents, DWord(sayings[curr_Saying]));
  end;

  my_Toggle:=0;
end;

// MCC_Dispatcher in Pascal
// evil C programmers inventing macroed API should be punished to death
// ********************************************************************

function my_DispatcherPPC: LongWord;
var
  cl : pIClass;
  obj: pObject_;
  msg: PMsg;
  tmpResult: longword;
  data: pmy_Data;
begin
  DISPATCHERARG(cl,obj,msg);
  data:=INST_DATA(cl,p_Object(obj));

  case (msg^.MethodID) of
    OM_NEW: tmpResult:=my_New(cl,obj,popSet(msg));
    MUIM_my_Toggle: tmpResult:=my_Toggle(data);
    else
      tmpResult:=DoSuperMethodA(cl,obj,msg);
  end;
  my_DispatcherPPC:=tmpResult;
end;

const
  my_Dispatcher : TEmulLibEntry = ( Trap: TRAP_LIB; Extension: 0; Func: @my_DispatcherPPC );


  
// Our cleanup procedure
// ********************************************************************
procedure Shutdown(error: string);
begin
  if (app <> nil) then MUI_DisposeObject(app);
  if (my_Stuff <> nil) then MUI_DeleteCustomClass(my_Stuff);

  if error<>'' then begin
    writeln(error);
    halt(1);
  end else begin
    halt;
  end;
end;

// main()
// ********************************************************************
begin
  InitIntuitionLibrary;
  InitMUIMasterLibrary;

  my_Stuff := MUI_CreateCustomClass(NIL, MUIC_Group, NIL, sizeof(tmy_Data), @my_Dispatcher);
  if my_Stuff = NIL then Shutdown('error: cannot create custom class.');

  // Our application object
  app := MH_Application(
         [ MUIA_Application_Title    , TAG('FPC MUI Test 2'),    // Name of our app
           MUIA_Application_Version  , TAG('1.0'),               // Our version
           MUIA_Application_Copyright, TAG('Public Domain'),     // Copyright status
           MUIA_Application_Author   , TAG('Karoly Balogh'),     // Author
           MUIA_Application_Base     , TAG('FPC_MUITEST2'),      // ENVARC prefsfilename
           SubWindow, TAG(MH_Window(win,
              [ MUIA_Window_Title , TAG('FPC MUI Test 2'),
                MUIA_Window_ID    , MAKE_ID('M','A','I','N'),  // Config ID to store window settings (position, size etc)
                WindowContents, TAG(MH_VGroup(
                   [ Child, TAG(MH_ColGroup(2, 
                        [ Child, TAG(NewObject(my_Stuff^.mcc_Class, NIL, [TAG_DONE])),
                          Child, TAG(NewObject(my_Stuff^.mcc_Class, NIL, [TAG_DONE])),
                          Child, TAG(NewObject(my_Stuff^.mcc_Class, NIL, [TAG_DONE])),
                          Child, TAG(NewObject(my_Stuff^.mcc_Class, NIL, [TAG_DONE])),
                        MUI_END])),
                     Child, TAG(MH_MakeHBar(2)),
                     Child, TAG(MH_MakeButton(quitbutton,'Teh Quit')),
                   MUI_END])),
              MUI_END])),
         MUI_END]);
  if app = nil then Shutdown('error: cannot create application.');

  {* Setting quit notifies * }
  DoMethod(win, [ MUIM_Notify, MUIA_Window_CloseRequest, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, DWord(MUIV_Application_ReturnID_Quit) ]);
  DoMethod(quitbutton, [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, DWord(MUIV_Application_ReturnID_Quit) ]);

  {* Setting MUIA_Window_Open to TRUE makes our window visible. *}
  MUIset(win, MUIA_Window_Open, MUI_TRUE);

  quitapp:=false;
  signals:=0;
  while not quitapp do begin
    retval:=DoMethod(app, [MUIM_Application_NewInput, DWord(@signals)]);
    if (retval = DWord(MUIV_Application_ReturnID_Quit)) then
       quitapp:=true;
    if (signals <> 0) then begin
      signals := Wait(signals Or SIGBREAKF_CTRL_C);
      if (signals and SIGBREAKF_CTRL_C) > 0 then
        quitapp:=true;
    end;
  end;

  Shutdown(''); 
end.

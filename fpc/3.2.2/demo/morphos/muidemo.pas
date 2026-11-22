{

    Creating a simple MUI application
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

program muidemo;

uses exec, amigados, intuition, mui, amigalib, utility;

var
  app: pObject_;
  win: pObject_;

  signals: longword;
  retval: longword;
  quitapp: boolean;

  button: array[0..3] of pObject_;
  mytext: pObject_;

begin
  InitIntuitionLibrary;
  InitMUIMasterLibrary;

  button[0]:=MUI_MakeObject(MUIO_Button, [DWord(PChar('r0x0r'))]);
  button[1]:=MUI_MakeObject(MUIO_Button, [DWord(PChar('k3wl'))]);
  button[2]:=MUI_MakeObject(MUIO_Button, [DWord(PChar('pwnz ya'))]);
  button[3]:=MUI_MakeObject(MUIO_Button, [DWord(PChar('Teh Quit'))]);

  mytext:=MUI_NewObject(MUIC_Text,
                        [ MUIA_Text_Contents, DWord(PChar('w00t...?')), TAG_DONE ]);

  win := MUI_NewObject(MUIC_Window,
                [ MUIA_Window_Title , DWord(PChar('Free Pascal MUI Test')),
                  MUIA_Window_ID    , MAKE_ID('M','A','I','N'),             // Config ID to store window settings (position, size etc)
                  MUIA_Window_RootObject  , 
                     DWord(MUI_NewObject(MUIC_Group,
                            [ MUIA_Group_Child, 
                                 DWord(MUI_NewObject(MUIC_Group,
                                        [ MUIA_Frame, MUIV_Frame_Group, MUIA_FrameTitle, DWord(PChar('Teh Buttonz!')), MUIA_Background, MUII_GroupBack,
                                          MUIA_Group_Child, DWord(button[0]),
                                          MUIA_Group_Child, DWord(button[1]),
                                          MUIA_Group_Child, DWord(button[2]),
                                          TAG_DONE
                                        ])),
                              MUIA_Group_Child,
                                 DWord(MUI_NewObject(MUIC_Group,
                                        [ MUIA_Frame, MUIV_Frame_Group, MUIA_FrameTitle, DWord(PChar('Da Zone')), MUIA_Background, MUII_GroupBack,
                                          MUIA_Group_Child, DWord(mytext),
                                          MUIA_Group_Child, DWord(button[3]),
                                          TAG_DONE
                                        ])),
                              TAG_DONE 
                            ])),
                  TAG_DONE
                ]);

  app := MUI_NewObject(MUIC_Application,
                [ MUIA_Application_Title     , DWord(PChar('Free Pascal MUI Test')),    // Name of our app
                  MUIA_Application_Version   , DWord(PChar('1.0')),                     // Our version
                  MUIA_Application_Copyright , DWord(PChar('Public Domain')),       // Copyright status
                  MUIA_Application_Author    , DWord(PChar('Karoly Balogh')),       // Author
                  MUIA_Application_Base      , DWord(PChar('FPC_MUITEST')),         // ENVARC prefsfilename
                  MUIA_Application_Window, DWord(win),
                  TAG_DONE
                ]);

  
  if app = nil then begin
     writeln('Error: cannot create application.');
     halt(1);
  end;

  DoMethod(DWord(win), [ MUIM_Notify, MUIA_Window_CloseRequest, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, DWord(MUIV_Application_ReturnID_Quit) ]);
  DoMethod(DWord(button[0]), [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, 1 ]);
  DoMethod(DWord(button[1]), [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, 2 ]);
  DoMethod(DWord(button[2]), [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, 3 ]);
  DoMethod(DWord(button[3]), [ MUIM_Notify, MUIA_Pressed, MUI_TRUE, MUIV_Notify_Application, 2, MUIM_Application_ReturnID, DWord(MUIV_Application_ReturnID_Quit) ]);

  {* Setting MUIA_Window_Open to TRUE makes our window visible. *}
  MUIset(win, MUIA_Window_Open, MUI_TRUE);

  quitapp:=false;
  signals:=0;
  while not quitapp do begin
    retval:=DoMethod(DWord(app), [MUIM_Application_NewInput, DWord(@signals)]);
    if (retval = DWord(MUIV_Application_ReturnID_Quit)) then
       quitapp:=true
    else begin
      case retval of
        1: MUIset(mytext, MUIA_Text_Contents, DWord(PChar(': button 1 r0x0r :')));
        2: MUIset(mytext, MUIA_Text_Contents, DWord(PChar(': button 2 k3wl :')));
        3: MUIset(mytext, MUIA_Text_Contents, DWord(PChar(': button 3 pwnz ya :')));
      end;
    end;
    if (signals <> 0) then begin
      signals := Wait(signals Or SIGBREAKF_CTRL_C);
      if (signals and SIGBREAKF_CTRL_C) > 0 then
        quitapp:=true;
    end;
  end;

  MUI_DisposeObject(app);
end.

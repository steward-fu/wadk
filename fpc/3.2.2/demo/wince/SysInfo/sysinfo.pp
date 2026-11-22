{WinCE API call sample : sysinfo
 show how to :
   - handle messages with loop using TObject.Dispatch
   - create form,
   - load resources (accelators/menubar)
   - show system informations using HDC

 sysinfo.rc file require .inc file for consts, if needed update #include path in this file

 changes :

 10-05-2005 : orinaudo@gmail.com
  first release
  win32(xp) cross compiled with fpc 2.1.x from today, tested on PPC arm-wince 4.21
  Tested on WM5
}

Program sysinfo;

{$APPTYPE GUI}
{$MODE DELPHI}
{$PACKRECORDS C}

Uses Strings, Windows, SysUtils, strutils, aygshell;

{$include appconst.inc}

{$R sysinfo.rc}


//*****************************************************************************
// Base Object (dispatch messages using FPC/TObject capabilities)
//*****************************************************************************
Function SysInfoMainWndProc (pMainHWnd:HWnd; piMessage : UINT; pWParam : WParam; pLParam:LParam): LResult; stdcall; forward;

type
 TMainSysInfo = Class(TObject)
  FPWClassName,
  FPWTitleName           : PWideChar;
  FAccelTable            : HACCEL;
  FMainHWnd              : HWND;
  FMenuBarHWnd           : HWND;
  FShellActivateInfo     : SHACTIVATEINFO;
  constructor Create;

  function WInit: boolean;
  function FWndProc( pMainHWnd:HWnd; piMessage : UINT; pWParam : WParam; pLParam:LParam): LResult;
  procedure DefaultHandler(var message); override;
  procedure DoCommand( var vAMessage : TMessage); message WM_COMMAND; virtual;
  procedure DoCreate( var vAMessage : TMessage); message WM_CREATE; virtual;
  procedure DoPaint( var vAMessage : TMessage); message WM_PAINT; virtual;
  procedure DoDestroy( var vAMessage : TMessage); message WM_DESTROY; virtual;
  procedure DoActivate( var vAMessage : TMessage); message WM_ACTIVATE; virtual;
  procedure DoSettingChange( var vAMessage : TMessage); message WM_SETTINGCHANGE; virtual;
 end;

//*****************************************************************************
// Global variables
//*****************************************************************************

var
  GMainSysInfo : TMainSysInfo;
  GMsg: MSG;

//*****************************************************************************

constructor TMainSysInfo.Create;
Begin
  inherited Create;
  FPWClassName:='TFormSysInfo';
  FPWTitleName:='SysInfo';
  FMainHWnd:=0;
  FMenuBarHWnd:=0;
  FAccelTable:=0;
end;

function TMainSysInfo.WInit : boolean;
var rc : RECT;
    wc : WNDCLASS;
begin
  //requirements of the Pocket PC shell, only one instance
  //If it is already running, then focus on the window
  FMainHWnd:=FindWindow( FPWClassName, FPWTitleName);
  if (FMainHWnd=0) then begin
    //register windows class
    With wc do begin
      Style := cs_hRedraw or cs_vRedraw;
      lpfnWndProc := WndProc(@SysInfoMainWndProc);
      cbClsExtra := 0;
      cbWndExtra := 0;
      hInstance := system.MainInstance;
      hIcon := LoadIcon(system.MainInstance,IDI_SYSINFO);
      hCursor := 0;
      hbrBackground := GetStockObject(WHITE_BRUSH);
      lpszMenuName := 0;
      lpszClassName := FPWClassName;
    End;
    RegisterClass(@wc);

    //create window
    FMainHWnd := CreateWindow (
                   FPWClassName, FPWTitleName, WS_VISIBLE, CW_USEDEFAULT,
                   CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT, 0,
                   0, system.MainInstance, 0);

    GetWindowRect(FMainHWnd, @rc);
    rc.bottom:= rc.bottom - 26; //26 is the menubar height
    if (FMenuBarHWnd>0)
    then MoveWindow(FMainHWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);

    ShowWindow(FMainHWnd, SW_SHOW);
    UpdateWindow(FMainHWnd);
    FAccelTable:= LoadAccelerators(System.MainInstance , MAKEINTRESOURCE(IDC_SYSINFO));
    Result:=True;
   end else begin
    SetForegroundWindow(FMainHWnd);
    Result:=False;
   end;
   //MessageBox(0,PWideChar(WideFormat('hMainInst/hMainWindow/hAccel = %d/%d/%d/ler: %d',[system.MainInstance,FMainHWnd, FAccelTable,GetLastError])),'Info', MB_OK);
end;

function TMainSysInfo.FWndProc( pMainHWnd:HWnd; piMessage : UINT; pWParam : WParam; pLParam:LParam): LResult;
var AMessage: TMessage;
begin
 //small hack, wm_create occur during creation -> createwindows function is not returned
 //so FMainHWnd still 0 and menubar need a parent !
 if (FMainHWnd=0) and (piMessage=WM_CREATE) then FMainHWnd:=pMainHWnd;

 with AMessage do begin
  msg := piMessage;
  wParam := pWParam;
  lParam := pLParam;
 end;
 Dispatch(AMessage);
 Result:=AMessage.Result;
end;

procedure TMainSysInfo.DefaultHandler(var message);
var PAMessage : PMessage;
begin
 with TMessage(message) do
  Result:=DefWindowProc(FMainHWnd, msg, wParam, lParam);
end;

procedure TMainSysInfo.DoCommand( var vAMessage : TMessage);
begin
  vAMessage.Result:=0;
  // Parse the menu selections:
  Case vAMessage.wParamlo of
    IDM_HELP_ABOUT:
      begin
        MessageBox(0,'SysInfo v1','About', MB_OK);
      end;
    IDOK:
      begin
        SendMessage(FMainHWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), FMainHWnd);
	SendMessage (FMainHWnd, WM_CLOSE, 0, 0);
      end;
    IDM_QUIT:
      begin
        DestroyWindow(FMainHWnd);
      end;
    else vAMessage.Result:=DefWindowProc(FMainHWnd, vAMessage.msg, vAMessage.WParam, vAMessage.LParam);
  end;
end;

procedure TMainSysInfo.DoCreate( var vAMessage : TMessage);
var AMenuBarInfo : SHMENUBARINFO;
begin
  vAMessage.Result:=0;
  //create MenuBar
  FillByte(AMenuBarInfo,sizeof(SHMENUBARINFO),0);
  with AMenuBarInfo do begin
    cbSize := sizeof(SHMENUBARINFO);
    dwFlags:= 0; //SHCMBF_EMPTYBAR;
    hwndParent:= FMainHWnd;
    nToolBarId:= IDR_MENUBAR;
    hInstRes:= System.MainInstance;
    nBmpId:= 0;
    cBmpImages:= 0;
    hwndMB:= 0;
    clrBk :=0;
  end;
  if SHCreateMenuBar(@AMenuBarInfo)
  then FMenuBarHWnd:=AMenuBarInfo.hwndMB
  else FMenuBarHWnd:=0;
  //MessageBox(0,PWideChar(WideFormat('menu bar hwnd = %d / %d',[FMenuBarHWnd, GetLastError])),'Info', MB_OK);

  //Initialize the shell activate info structure
  FillByte(FShellActivateInfo,sizeof(SHACTIVATEINFO),0);
  FShellActivateInfo.cbSize := sizeof(SHACTIVATEINFO);
end;

procedure TMainSysInfo.DoPaint( var vAMessage : TMessage);
var rt     : RECT;
    ps     : PAINTSTRUCT;
    AHDC   : HDC;
    wzData : WideString;
begin
   vAMessage.Result:=0;
   AHDC:= BeginPaint(FMainHWnd, @ps);
   try
    GetClientRect(FMainHWnd, @rt);
    wzData:=WideFormat('Build : %d, WinCE v : %d.%d'#13+
                       'Plateform : %d'#13+
                       'CDS Version : %s',
                       [Sysutils.WinCEBuildNumber, Sysutils.WinCEMajorVersion,
                        Sysutils.WinCEMinorVersion, SysUtils.WinCEPlatform,
                        Sysutils.WinCECSDVersion]);

    DrawText(Ahdc, PWideChar(wzData), -1, @rt, DT_LEFT);

   finally EndPaint(FMainHWnd, @ps); end;
end;

procedure TMainSysInfo.DoDestroy( var vAMessage : TMessage);
begin
  vAMessage.Result:=0;
  DestroyWindow(FMenuBarHWnd); //MenuBar Destroy
  FMenuBarHWnd:=0;
  PostQuitMessage(0);
end;

procedure TMainSysInfo.DoActivate( var vAMessage : TMessage);
begin
  with vAMessage do begin
   Result:=0;
   // Notify shell of our activate message
   SHHandleWMActivate(FMainHWnd, wParam, lParam, @FShellActivateInfo, 0); //SHA_INPUTDIALOG
  end;
end;

procedure TMainSysInfo.DoSettingChange( var vAMessage : TMessage);
begin
  with vAMessage do begin
   Result:=0;
   SHHandleWMSettingChange(FMainHWnd, wParam, lParam, @FShellActivateInfo);
  end;
end;

//*****************************************************************************
// SysInfoMainWndProc
// Process messages for the main window
//*****************************************************************************

// registerclass accept only static proc not objects methods
// lpfnWndProc := WndProc(@SysInfoMainWndProc) -> redirection to object method

Function SysInfoMainWndProc (pMainHWnd:HWnd; piMessage : UINT; pWParam : WParam; pLParam:LParam): LResult; stdcall;
begin
 Result:=GMainSysInfo.FWndProc( pMainHWnd,piMessage,pWParam,pLParam);
end;

//*****************************************************************************
// Main entry point
//*****************************************************************************
Begin
 try

  GMainSysInfo:=TMainSysInfo.Create;
  try
    if GMainSysInfo.WInit
    then While GetMessage(@GMsg,0,0,0)
         do if TranslateAccelerator(GMsg.hwnd, GMainSysInfo.FAccelTable, @GMsg)=0 then begin
             Windows.TranslateMessage(@GMsg);
             Windows.DispatchMessage(@GMsg);
            end;

  finally GMainSysInfo.Free; end;

 except
  On E:Exception do MessageBox(0,PWideChar(WideFormat('message = %s',[E.message])),'Error', MB_OK);
 end;
End.


;*   USER32.LIB prototypes for MASM
;* (C)hardCode | http://bizarrecreations.webjump.com

include WinExtra\unicode.def

IFNDEF __USER32PROTOS__
__USER32PROTOS__=1

ActivateKeyboardLayout PROTO :DWORD,:DWORD
AdjustWindowRect PROTO :DWORD,:DWORD,:DWORD
AdjustWindowRectEx PROTO :DWORD,:DWORD,:DWORD,:DWORD
AnyPopup PROTO

_XDEF AppendMenu,<:DWORD,:DWORD,:DWORD,:DWORD>

ArrangeIconicWindows PROTO :DWORD
AttachThreadInput PROTO :DWORD,:DWORD,:DWORD
BeginDeferWindowPos PROTO :DWORD
BeginPaint PROTO :DWORD,:DWORD
BringWindowToTop PROTO :DWORD

_XDEF BroadcastSystemMessage,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CallMsgFilter,<:DWORD,:DWORD>

CallNextHookEx PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF CallWindowProc,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CascadeChildWindows PROTO :DWORD,:DWORD
CascadeWindows PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ChangeClipboardChain PROTO :DWORD,:DWORD

_XDEF ChangeDisplaySettings,<:DWORD,:DWORD>

_XDEF ChangeDisplaySettingsEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF ChangeMenu,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CharLower,<:DWORD>

_XDEF CharLowerBuff,<:DWORD,:DWORD>

_XDEF CharNext,<:DWORD>

_XDEF CharNextEx,<:DWORD,:DWORD,:DWORD>

_XDEF CharPrev,<:DWORD,:DWORD>

_XDEF CharPrevEx,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CharToOem,<:DWORD,:DWORD>

_XDEF CharToOemBuff,<:DWORD,:DWORD,:DWORD>

_XDEF CharUpper,<:DWORD>

_XDEF CharUpperBuff,<:DWORD,:DWORD>

CheckDlgButton PROTO :DWORD,:DWORD,:DWORD
CheckMenuItem PROTO :DWORD,:DWORD,:DWORD
CheckMenuRadioItem PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CheckRadioButton PROTO :DWORD,:DWORD,:DWORD,:DWORD
ChildWindowFromPoint PROTO :DWORD,:DWORD,:DWORD
ChildWindowFromPointEx PROTO :DWORD,:DWORD,:DWORD,:DWORD
ClientToScreen PROTO :DWORD,:DWORD
ClipCursor PROTO :DWORD
CloseClipboard PROTO
CloseDesktop PROTO :DWORD
CloseWindow PROTO :DWORD
CloseWindowStation PROTO :DWORD

_XDEF CopyAcceleratorTable,<:DWORD,:DWORD,:DWORD>

CopyIcon PROTO :DWORD
CopyImage PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CopyRect PROTO :DWORD,:DWORD
CountClipboardFormats PROTO

_XDEF CreateAcceleratorTable,<:DWORD,:DWORD>

CreateCaret PROTO :DWORD,:DWORD,:DWORD,:DWORD
CreateCursor PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF CreateDesktop,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CreateDialogIndirectParam,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CreateDialogParam,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreateIcon PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateIconFromResource PROTO :DWORD,:DWORD,:DWORD,:DWORD
CreateIconFromResourceEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateIconIndirect PROTO :DWORD

_XDEF CreateMDIWindow,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

CreateMenu PROTO
CreatePopupMenu PROTO

_XDEF CreateWindowEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF CreateWindowStation,<:DWORD,:DWORD,:DWORD,:DWORD>

DdeAbandonTransaction PROTO :DWORD,:DWORD,:DWORD
DdeAccessData PROTO :DWORD,:DWORD
DdeAddData PROTO :DWORD,:DWORD,:DWORD,:DWORD
DdeClientTransaction PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DdeCmpStringHandles PROTO :DWORD,:DWORD
DdeConnect PROTO :DWORD,:DWORD,:DWORD,:DWORD
DdeConnectList PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DdeCreateDataHandle PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF DdeCreateStringHandle,<:DWORD,:DWORD,:DWORD>

DdeDisconnect PROTO :DWORD
DdeDisconnectList PROTO :DWORD
DdeEnableCallback PROTO :DWORD,:DWORD,:DWORD
DdeFreeDataHandle PROTO :DWORD
DdeFreeStringHandle PROTO :DWORD,:DWORD
DdeGetData PROTO :DWORD,:DWORD,:DWORD,:DWORD
DdeGetLastError PROTO :DWORD
DdeGetQualityOfService PROTO :DWORD,:DWORD,:DWORD
DdeImpersonateClient PROTO :DWORD

_XDEF DdeInitialize,<:DWORD,:DWORD,:DWORD,:DWORD>

DdeKeepStringHandle PROTO :DWORD,:DWORD
DdeNameService PROTO :DWORD,:DWORD,:DWORD,:DWORD
DdePostAdvise PROTO :DWORD,:DWORD,:DWORD
DdeQueryConvInfo PROTO :DWORD,:DWORD,:DWORD
DdeQueryNextServer PROTO :DWORD,:DWORD

_XDEF DdeQueryString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

DdeReconnect PROTO :DWORD
DdeSetQualityOfService PROTO :DWORD,:DWORD,:DWORD
DdeSetUserHandle PROTO :DWORD,:DWORD,:DWORD
DdeUnaccessData PROTO :DWORD
DdeUninitialize PROTO :DWORD

_XDEF DefDlgProc,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DefFrameProc,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DefMDIChildProc,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DefWindowProc,<:DWORD,:DWORD,:DWORD,:DWORD>

DeferWindowPos PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DeleteMenu PROTO :DWORD,:DWORD,:DWORD
DestroyAcceleratorTable PROTO :DWORD
DestroyCaret PROTO
DestroyCursor PROTO :DWORD
DestroyIcon PROTO :DWORD
DestroyMenu PROTO :DWORD
DestroyWindow PROTO :DWORD

_XDEF DialogBoxIndirectParam,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DialogBoxParam,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DispatchMessage,<:DWORD>

_XDEF DlgDirList,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DlgDirListComboBox,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DlgDirSelectComboBoxEx,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DlgDirSelectEx,<:DWORD,:DWORD,:DWORD,:DWORD>

DragDetect PROTO :DWORD,:DWORD,:DWORD
DragObject PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DrawAnimatedRects PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawCaption PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawEdge PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawFocusRect PROTO :DWORD,:DWORD
DrawFrame PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawFrameControl PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawIcon PROTO :DWORD,:DWORD,:DWORD,:DWORD
DrawIconEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DrawMenuBar PROTO :DWORD

_XDEF DrawState,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DrawText,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF DrawTextEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

EditWndProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
EmptyClipboard PROTO
EnableMenuItem PROTO :DWORD,:DWORD,:DWORD
EnableScrollBar PROTO :DWORD,:DWORD,:DWORD
EnableWindow PROTO :DWORD,:DWORD
EndDeferWindowPos PROTO :DWORD
EndDialog PROTO :DWORD,:DWORD
EndPaint PROTO :DWORD,:DWORD
EnumChildWindows PROTO :DWORD,:DWORD,:DWORD
EnumClipboardFormats PROTO :DWORD
EnumDesktopWindows PROTO :DWORD,:DWORD,:DWORD

_XDEF EnumDesktops,<:DWORD,:DWORD,:DWORD>

_XDEF EnumDisplaySettings,<:DWORD,:DWORD,:DWORD>

_XDEF EnumProps,<:DWORD,:DWORD>

_XDEF EnumPropsEx,<:DWORD,:DWORD,:DWORD>

EnumThreadWindows PROTO :DWORD,:DWORD,:DWORD

_XDEF EnumWindowStations,<:DWORD,:DWORD>

EnumWindows PROTO :DWORD,:DWORD
EqualRect PROTO :DWORD,:DWORD
ExcludeUpdateRgn PROTO :DWORD,:DWORD
ExitWindowsEx PROTO :DWORD,:DWORD
FillRect PROTO :DWORD,:DWORD,:DWORD

_XDEF FindWindow,<:DWORD,:DWORD>

_XDEF FindWindowEx,<:DWORD,:DWORD,:DWORD,:DWORD>

FlashWindow PROTO :DWORD,:DWORD
FrameRect PROTO :DWORD,:DWORD,:DWORD
FreeDDElParam PROTO :DWORD,:DWORD
GetActiveWindow PROTO
GetAsyncKeyState PROTO :DWORD
GetCapture PROTO
GetCaretBlinkTime PROTO
GetCaretPos PROTO :DWORD

_XDEF GetClassInfo,<:DWORD,:DWORD,:DWORD>

_XDEF GetClassInfoEx,<:DWORD,:DWORD,:DWORD>

_XDEF GetClassLong,<:DWORD,:DWORD>

_XDEF GetClassName,<:DWORD,:DWORD,:DWORD>

GetClassWord PROTO :DWORD,:DWORD
GetClientRect PROTO :DWORD,:DWORD
GetClipCursor PROTO :DWORD
GetClipboardData PROTO :DWORD

_XDEF GetClipboardFormatName,<:DWORD,:DWORD,:DWORD>

GetClipboardOwner PROTO
GetClipboardViewer PROTO
GetCursor PROTO
GetCursorPos PROTO :DWORD
GetDC PROTO :DWORD
GetDCEx PROTO :DWORD,:DWORD,:DWORD
GetDesktopWindow PROTO
GetDialogBaseUnits PROTO
GetDlgCtrlID PROTO :DWORD
GetDlgItem PROTO :DWORD,:DWORD
GetDlgItemInt PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF GetDlgItemText,<:DWORD,:DWORD,:DWORD,:DWORD>

GetDoubleClickTime PROTO
GetFocus PROTO
GetForegroundWindow PROTO
GetIconInfo PROTO :DWORD,:DWORD
GetInputDesktop PROTO
GetInputState PROTO
GetKBCodePage PROTO

_XDEF GetKeyNameText,<:DWORD,:DWORD,:DWORD>

GetKeyState PROTO :DWORD
GetKeyboardLayout PROTO :DWORD
GetKeyboardLayoutList PROTO :DWORD,:DWORD

_XDEF GetKeyboardLayoutName,<:DWORD>

GetKeyboardState PROTO :DWORD
GetKeyboardType PROTO :DWORD
GetLastActivePopup PROTO :DWORD
GetMenu PROTO :DWORD
GetMenuCheckMarkDimensions PROTO
GetMenuContextHelpId PROTO :DWORD
GetMenuDefaultItem PROTO :DWORD,:DWORD,:DWORD
GetMenuItemCount PROTO :DWORD
GetMenuItemID PROTO :DWORD,:DWORD

_XDEF GetMenuItemInfo,<:DWORD,:DWORD,:DWORD,:DWORD>

GetMenuItemRect PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetMenuState PROTO :DWORD,:DWORD,:DWORD

_XDEF GetMenuString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF GetMessage,<:DWORD,:DWORD,:DWORD,:DWORD>

GetMessageExtraInfo PROTO
GetMessagePos PROTO
GetMessageTime PROTO
GetNextDlgGroupItem PROTO :DWORD,:DWORD,:DWORD
GetNextDlgTabItem PROTO :DWORD,:DWORD,:DWORD
GetOpenClipboardWindow PROTO
GetParent PROTO :DWORD
GetPriorityClipboardFormat PROTO :DWORD,:DWORD
GetProcessWindowStation PROTO

_XDEF GetProp,<:DWORD,:DWORD>

GetQueueStatus PROTO :DWORD
GetScrollInfo PROTO :DWORD,:DWORD,:DWORD
GetScrollPos PROTO :DWORD,:DWORD
GetScrollRange PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetShellWindow PROTO
GetSubMenu PROTO :DWORD,:DWORD
GetSysColor PROTO :DWORD
GetSysColorBrush PROTO :DWORD
GetSystemMenu PROTO :DWORD,:DWORD
GetSystemMetrics PROTO :DWORD

_XDEF GetTabbedTextExtent,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetThreadDesktop PROTO :DWORD
GetTopWindow PROTO :DWORD
GetUpdateRect PROTO :DWORD,:DWORD,:DWORD
GetUpdateRgn PROTO :DWORD,:DWORD,:DWORD

_XDEF GetUserObjectInformation,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

GetUserObjectSecurity PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
GetWindow PROTO :DWORD,:DWORD
GetWindowContextHelpId PROTO :DWORD
GetWindowDC PROTO :DWORD

_XDEF GetWindowLong,<:DWORD,:DWORD>

GetWindowPlacement PROTO :DWORD,:DWORD
GetWindowRect PROTO :DWORD,:DWORD
GetWindowRgn PROTO :DWORD,:DWORD

_XDEF GetWindowText,<:DWORD,:DWORD,:DWORD>

_XDEF GetWindowTextLength,<:DWORD>

GetWindowThreadProcessId PROTO :DWORD,:DWORD
GetWindowWord PROTO :DWORD,:DWORD

_XDEF GrayString,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

HideCaret PROTO :DWORD
HiliteMenuItem PROTO :DWORD,:DWORD,:DWORD,:DWORD
ImpersonateDdeClientWindow PROTO :DWORD,:DWORD
InSendMessage PROTO
InflateRect PROTO :DWORD,:DWORD,:DWORD

_XDEF InsertMenu,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF InsertMenuItem,<:DWORD,:DWORD,:DWORD,:DWORD>

IntersectRect PROTO :DWORD,:DWORD,:DWORD
InvalidateRect PROTO :DWORD,:DWORD,:DWORD
InvalidateRgn PROTO :DWORD,:DWORD,:DWORD
InvertRect PROTO :DWORD,:DWORD

_XDEF IsCharAlpha,<:DWORD>

_XDEF IsCharAlphaNumeric,<:DWORD>

_XDEF IsCharLower,<:DWORD>

_XDEF IsCharUpper,<:DWORD>

IsChild PROTO :DWORD,:DWORD
IsClipboardFormatAvailable PROTO :DWORD

_XDEF IsDialogMessage,<:DWORD,:DWORD>

IsDlgButtonChecked PROTO :DWORD,:DWORD
IsIconic PROTO :DWORD
IsMenu PROTO :DWORD
IsRectEmpty PROTO :DWORD
IsWindow PROTO :DWORD
IsWindowEnabled PROTO :DWORD
IsWindowUnicode PROTO :DWORD
IsWindowVisible PROTO :DWORD
IsZoomed PROTO :DWORD
KillSystemTimer PROTO :DWORD,:DWORD
KillTimer PROTO :DWORD,:DWORD

_XDEF LoadAccelerators,<:DWORD,:DWORD>

_XDEF LoadBitmap,<:DWORD,:DWORD>

_XDEF LoadCursor,<:DWORD,:DWORD>

_XDEF LoadCursorFromFile,<:DWORD>

_XDEF LoadIcon,<:DWORD,:DWORD>

_XDEF LoadImage,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF LoadKeyboardLayout,<:DWORD,:DWORD>

_XDEF LoadMenu,<:DWORD,:DWORD>

_XDEF LoadMenuIndirect,<:DWORD>

_XDEF LoadString,<:DWORD,:DWORD,:DWORD,:DWORD>

LockWindowUpdate PROTO :DWORD
LookupIconIdFromDirectory PROTO :DWORD,:DWORD
LookupIconIdFromDirectoryEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MapDialogRect PROTO :DWORD,:DWORD

_XDEF MapVirtualKey,<:DWORD,:DWORD>

_XDEF MapVirtualKeyEx,<:DWORD,:DWORD,:DWORD>

MapWindowPoints PROTO :DWORD,:DWORD,:DWORD,:DWORD
MenuItemFromPoint PROTO :DWORD,:DWORD,:DWORD,:DWORD
MessageBeep PROTO :DWORD

_XDEF MessageBox,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF MessageBoxEx,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF MessageBoxIndirect,<:DWORD>

_XDEF ModifyMenu,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

MoveWindow PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MsgWaitForMultipleObjects PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MsgWaitForMultipleObjectsEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
OemKeyScan PROTO :DWORD

_XDEF OemToChar,<:DWORD,:DWORD>

_XDEF OemToCharBuff,<:DWORD,:DWORD,:DWORD>

OffsetRect PROTO :DWORD,:DWORD,:DWORD
OpenClipboard PROTO :DWORD

_XDEF OpenDesktop,<:DWORD,:DWORD,:DWORD,:DWORD>

OpenIcon PROTO :DWORD
OpenInputDesktop PROTO :DWORD,:DWORD,:DWORD

_XDEF OpenWindowStation,<:DWORD,:DWORD,:DWORD>

PackDDElParam PROTO :DWORD,:DWORD,:DWORD
PaintDesktop PROTO :DWORD

_XDEF PeekMessage,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF PostMessage,<:DWORD,:DWORD,:DWORD,:DWORD>

PostQuitMessage PROTO :DWORD

_XDEF PostThreadMessage,<:DWORD,:DWORD,:DWORD,:DWORD>

PtInRect PROTO :DWORD,:DWORD,:DWORD
RedrawWindow PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF RegisterClass,<:DWORD>

_XDEF RegisterClassEx,<:DWORD>

_XDEF RegisterClipboardFormat,<:DWORD>

RegisterHotKey PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF RegisterWindowMessage,<:DWORD>

ReleaseCapture PROTO
ReleaseDC PROTO :DWORD,:DWORD
RemoveMenu PROTO :DWORD,:DWORD,:DWORD

_XDEF RemoveProp,<:DWORD,:DWORD>

ReplyMessage PROTO :DWORD
ReuseDDElParam PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ScreenToClient PROTO :DWORD,:DWORD
ScrollChildren PROTO :DWORD,:DWORD,:DWORD
ScrollDC PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ScrollWindow PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ScrollWindowEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF SendDlgItemMessage,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF SendMessage,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF SendMessageCallback,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF SendMessageTimeout,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF SendNotifyMessage,<:DWORD,:DWORD,:DWORD,:DWORD>

SetActiveWindow PROTO :DWORD
SetCapture PROTO :DWORD
SetCaretBlinkTime PROTO :DWORD
SetCaretPos PROTO :DWORD,:DWORD

_XDEF SetClassLong,<:DWORD,:DWORD,:DWORD>

SetClassWord PROTO :DWORD,:DWORD,:DWORD
SetClipboardData PROTO :DWORD,:DWORD
SetClipboardViewer PROTO :DWORD
SetCursor PROTO :DWORD
SetCursorPos PROTO :DWORD,:DWORD
SetDebugErrorLevel PROTO :DWORD
SetDeskWallpaper PROTO :DWORD
SetDlgItemInt PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF SetDlgItemText,<:DWORD,:DWORD,:DWORD>

SetDoubleClickTime PROTO :DWORD
SetFocus PROTO :DWORD
SetForegroundWindow PROTO :DWORD
SetKeyboardState PROTO :DWORD
SetLastErrorEx PROTO :DWORD,:DWORD
SetMenu PROTO :DWORD,:DWORD
SetMenuContextHelpId PROTO :DWORD,:DWORD
SetMenuDefaultItem PROTO :DWORD,:DWORD,:DWORD
SetMenuItemBitmaps PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF SetMenuItemInfo,<:DWORD,:DWORD,:DWORD,:DWORD>

SetMessageExtraInfo PROTO :DWORD
SetMessageQueue PROTO :DWORD
SetParent PROTO :DWORD,:DWORD
SetProcessWindowStation PROTO :DWORD

_XDEF SetProp,<:DWORD,:DWORD,:DWORD>

SetRect PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
SetRectEmpty PROTO :DWORD
SetScrollInfo PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetScrollPos PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetScrollRange PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
SetShellWindow PROTO :DWORD
SetSysColors PROTO :DWORD,:DWORD,:DWORD
SetSystemCursor PROTO :DWORD,:DWORD
SetSystemMenu PROTO :DWORD,:DWORD
SetSystemTimer PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetThreadDesktop PROTO :DWORD
SetTimer PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF SetUserObjectInformation,<:DWORD,:DWORD,:DWORD,:DWORD>

SetUserObjectSecurity PROTO :DWORD,:DWORD,:DWORD
SetWindowContextHelpId PROTO :DWORD,:DWORD

_XDEF SetWindowLong,<:DWORD,:DWORD,:DWORD>

SetWindowPlacement PROTO :DWORD,:DWORD
SetWindowPos PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
SetWindowRgn PROTO :DWORD,:DWORD,:DWORD

_XDEF SetWindowText,<:DWORD,:DWORD>

SetWindowWord PROTO :DWORD,:DWORD,:DWORD

_XDEF SetWindowsHook,<:DWORD,:DWORD>

_XDEF SetWindowsHookEx,<:DWORD,:DWORD,:DWORD,:DWORD>

ShowCaret PROTO :DWORD
ShowCursor PROTO :DWORD
ShowOwnedPopups PROTO :DWORD,:DWORD
ShowScrollBar PROTO :DWORD,:DWORD,:DWORD
ShowWindow PROTO :DWORD,:DWORD
ShowWindowAsync PROTO :DWORD,:DWORD
SubtractRect PROTO :DWORD,:DWORD,:DWORD
SwapMouseButton PROTO :DWORD
SwitchDesktop PROTO :DWORD

_XDEF SystemParametersInfo,<:DWORD,:DWORD,:DWORD,:DWORD>

_XDEF TabbedTextOut,<:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD>

TileChildWindows PROTO :DWORD,:DWORD
TileWindows PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ToAscii PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ToAsciiEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ToUnicode PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ToUnicodeEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
TrackMouseEvent PROTO :DWORD
TrackPopupMenu PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
TrackPopupMenuEx PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF TranslateAccelerator,<:DWORD,:DWORD,:DWORD>

TranslateMDISysAccel PROTO :DWORD,:DWORD
TranslateMessage PROTO :DWORD
UnhookWindowsHook PROTO :DWORD,:DWORD
UnhookWindowsHookEx PROTO :DWORD
UnionRect PROTO :DWORD,:DWORD,:DWORD
UnloadKeyboardLayout PROTO :DWORD
UnpackDDElParam PROTO :DWORD,:DWORD,:DWORD,:DWORD

_XDEF UnregisterClass,<:DWORD,:DWORD>

UnregisterHotKey PROTO :DWORD,:DWORD
UpdateWindow PROTO :DWORD
ValidateRect PROTO :DWORD,:DWORD
ValidateRgn PROTO :DWORD,:DWORD

_XDEF VkKeyScan,<:DWORD>

_XDEF VkKeyScanEx,<:DWORD,:DWORD>

WaitForInputIdle PROTO :DWORD,:DWORD
WaitMessage PROTO

_XDEF WinHelp,<:DWORD,:DWORD,:DWORD,:DWORD>

WindowFromDC PROTO :DWORD
WindowFromPoint PROTO :DWORD,:DWORD
keybd_event PROTO :DWORD,:DWORD,:DWORD,:DWORD
mouse_event PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD

_XDEF wvsprintf,<:DWORD,:DWORD,:DWORD>

ENDIF ;__USER32PROTOS__

.global WinMain

.equiv SetWindowLong, SetWindowLongA
.equiv DispatchMessage, DispatchMessageA
.equiv GetMessage, GetMessageA
.equiv CreateWindowEx, CreateWindowExA
.equiv MessageBox, MessageBoxA
.equiv CallWindowProc, CallWindowProcA
.equiv DefWindowProc, DefWindowProcA
.equiv RegisterClass, RegisterClassA

.equiv MB_OK, 0
.equiv NULL, 0
.equiv WC_DIALOG, 0x8002
.equiv WM_DESTROY, 2
.equiv WM_CLOSE, 0x10
.equiv WS_OVERLAPPED, 0
.equiv WS_CAPTION, 0xc00000
.equiv WS_SYSMENU, 0x80000
.equiv WS_THICKFRAME, 0x40000
.equiv WS_MINIMIZEBOX, 0x20000
.equiv WS_MAXIMIZEBOX, 0x10000
.equiv WS_VISIBLE, 0x10000000
.equiv WS_EX_LEFT, 0x00000000
.equiv WS_OVERLAPPEDWINDOW, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
.equiv GWL_WNDPROC, -4

.equiv WNDCLASS.style, 0
.equiv WNDCLASS.lpfnWndProc, 4
.equiv WNDCLASS.cbClsExtra, 8
.equiv WNDCLASS.cbWndExtra, 12
.equiv WNDCLASS.hInstance, 16
.equiv WNDCLASS.hIcon, 20
.equiv WNDCLASS.hCursor, 24
.equiv WNDCLASS.hbrBackground, 28
.equiv WNDCLASS.lpszMenuName, 32
.equiv WNDCLASS.lpszClassName, 36


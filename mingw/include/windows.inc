.extern _ExitProcess@4
.extern _MessageBoxA@16

.equ MessageBox, MessageBoxA
.equ MessageBoxA, _MessageBoxA@16
.equ ExitProcess, _ExitProcess@4
.equ MB_OK, 0
.equ NULL,0


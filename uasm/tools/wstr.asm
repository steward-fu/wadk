
;--- test app for wide strings

	.386
	.model flat, stdcall
	option casemap:none

	.nolist
	.nocref
WIN32_LEAN_AND_MEAN equ 1
	include windows.inc
	include stdio.inc
	include stdlib.inc
	.list
	.cref

	.data

szFStr	db "%S",0
wstr1	dw L("first line",10,"second line",10),0

	.code

main proc c argc:dword, argv:ptr ptr sbyte

local	szText[128]:byte

	invoke wsprintf, addr szText, offset szFStr, addr wstr1
	invoke printf, addr szText
	ret

main endp

mainCRTStartup proc public
ifdef _DLL
__getmainargs proto c :dword, :dword, :dword, :dword, :dword

	sub esp, sizeof STARTUPINFO
	mov [esp].STARTUPINFO.cb, sizeof STARTUPINFO
	mov eax, esp
	push 0
	mov ebx, esp
	push 0
	mov ecx, esp
	push 0
	mov edx, esp
	invoke __getmainargs, edx, ecx, ebx, 0, eax
else
externdef c __argv:dword
externdef c __argc:dword
	push __argv
	push __argc
endif
	call main
	invoke exit, eax

mainCRTStartup endp

	END mainCRTStartup

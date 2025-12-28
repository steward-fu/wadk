;--- socket send()/recf() example

        .386
        .MODEL FLAT, stdcall
        option casemap:none

WIN32_LEAN_AND_MEAN equ 1
        include windows.inc
        include winsock.inc
        include stdio.inc

;--- macro to simplify defining a string

CStr macro y:req
local sym
    .const
ifidni <y>,<"">
sym db 0
else
sym db y,0
endif
    .code
    exitm <offset sym>
    endm

        .DATA
        
sin1    SOCKADDR_IN <>

szHost  db "www.japheth.de",0
szRequest db "GET / HTTP/1.0",13,10,"Host: %s",13,10,13,10

        .DATA?
        
buffer  db 32768 dup (?)        
        
        .CODE

;--- display host name/address

disphostent proc uses esi ebx phostent:ptr hostent

        mov esi, phostent
        .if ([esi].hostent.h_name)
            invoke printf, CStr(<"gethostbyname.h_name=%s",10>), [esi].hostent.h_name
        .endif
        .if ([esi].hostent.h_aliases)
            mov ebx, [esi].hostent.h_aliases
            .while (dword ptr [ebx])
                mov eax, [ebx]
                invoke printf, CStr(<"gethostbyname.h_aliases=%s",10>), eax
                add ebx, 4
            .endw
        .endif
        movzx eax, [esi].hostent.h_addrtype
        invoke printf, CStr(<"gethostbyname.h_addrtype=%X",10>), eax
        movzx eax, [esi].hostent.h_length
        invoke printf, CStr(<"gethostbyname.h_length=%X",10>), eax
        .if ([esi].hostent.h_addr_list)
            mov ebx, [esi].hostent.h_addr_list
            .while (dword ptr [ebx])
                mov eax, [ebx]
                pushad
                movzx edx, byte ptr [eax+0]
                movzx ecx, byte ptr [eax+1]
                movzx esi, byte ptr [eax+2]
                movzx edi, byte ptr [eax+3]
                invoke printf, CStr(<"gethostbyname.h_addr_list=%u.%u.%u.%u",10>), edx, ecx, esi, edi
                popad
                add ebx, 4
            .endw
        .endif
        ret
disphostent endp

;--- display received string

displaybuffer proc uses esi pBuffer:ptr, dwLen:DWORD

        mov esi, pBuffer
        mov ecx, dwLen
        .while (ecx)
            push ecx
            lodsb
            invoke printf, CStr("%c"), eax
            pop ecx
            dec ecx
        .endw
        ret     
displaybuffer endp

;--- main() 
;--- establish a HTTP connection and read the index file

main    proc c

local   WSAData:WSADATA
local   phostent:DWORD
local   sock:SOCKET

        invoke  WSAStartup, 0101h, addr WSAData
        .if (eax)
            invoke printf, CStr(<"WSAStartup failed [%X]",10>), eax
            jmp @exit
        .endif
        movzx eax, WSAData.wVersion
        invoke printf, CStr(<"WSAStartup.wVersion: %X", 10>), eax
        movzx eax, WSAData.wHighVersion
        invoke printf, CStr(<"WSAStartup.wHighVersion: %X", 10>), eax
        invoke printf, CStr(<"WSAStartup.szDescription: %s", 10>), addr WSAData.szDescription
        invoke printf, CStr(<"WSAStartup.szSystemStatus: %s", 10>), addr WSAData.szSystemStatus
        movzx eax, WSAData.iMaxSockets
        invoke printf, CStr(<"WSAStartup.iMaxSockets: %X", 10>), eax
        movzx eax, WSAData.iMaxUdpDg
        invoke printf, CStr(<"WSAStartup.iMaxUdpDg: %X", 10>), eax
        invoke printf, CStr(<"WSAStartup.lpVendorInfo: %X", 10>), WSAData.lpVendorInfo

        mov esi, offset szHost
        invoke gethostbyname, esi
        .if (eax)
            mov phostent, eax
            invoke disphostent, eax
        .else
            invoke WSAGetLastError
            invoke printf, CStr(<"gethostbyname('%s') failed [%u]",10>), esi, eax
            jmp exit2
        .endif

        invoke socket, AF_INET, SOCK_STREAM, 0
        .if (eax == INVALID_SOCKET)
            invoke WSAGetLastError
            invoke printf, CStr(<"socket() failed [%u]",10>), eax
            jmp exit2
        .endif
        mov sock, eax
        invoke printf, CStr(<"socket()=%X",10>), sock
            
        mov sin1.sin_family, AF_INET
        invoke htons, 80                ;use the HTTP port
        mov sin1.sin_port, ax

        mov eax, phostent
        mov eax, [eax].hostent.h_addr_list
        mov ebx, [eax]
        mov cl,[ebx+0]
        mov sin1.sin_addr.S_un.S_un_b.s_b1, cl
        mov cl,[ebx+1]
        mov sin1.sin_addr.S_un.S_un_b.s_b2, cl
        mov cl,[ebx+2]
        mov sin1.sin_addr.S_un.S_un_b.s_b3, cl
        mov cl,[ebx+3]
        mov sin1.sin_addr.S_un.S_un_b.s_b4, cl
        invoke connect, sock, addr sin1, sizeof sin1
        .if (eax == SOCKET_ERROR)
            invoke WSAGetLastError
            invoke printf, CStr(<"connect() failed [%u]",10>), eax
        .else
            invoke printf, CStr(<"connect(%X)=%X",10>), sock, eax
            invoke sprintf, addr buffer, addr szRequest, addr szHost
            invoke send, sock, addr buffer, eax, 0
            .if (eax != SOCKET_ERROR)
                invoke recv, sock, addr buffer, sizeof buffer, 0
                .if (eax != SOCKET_ERROR)
                    invoke displaybuffer, addr buffer, eax
                .else
                    invoke WSAGetLastError
                    invoke printf, CStr(<"recv() failed [%X]",10>), eax
                .endif
            .else
                invoke WSAGetLastError
                invoke printf, CStr(<"send() failed [%X]",10>), eax
            .endif
            invoke shutdown, sock, 2            
            invoke printf, CStr(<"shutdown(%X)=%X",10>), sock, eax
        .endif

        invoke closesocket, sock
        invoke printf, CStr(<"closesocket(%X)=%X",10>), sock, eax
exit2:
        invoke WSACleanup
        invoke printf, CStr(<"WSACleanup()=%X",10>), eax
@exit:        
        ret
main    endp

mainCRTStartup  proc stdcall
        call    main
        invoke  ExitProcess,eax
mainCRTStartup endp

        END mainCRTStartup

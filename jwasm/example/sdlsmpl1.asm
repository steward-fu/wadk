;--- this is a SDL sample written in MASM

        .386
        .model flat, stdcall
        option casemap:none

        .nolist
        .nocref
        include windows.inc
        include sdl.inc
        .cref
        .list

CStr macro text
local szText
    .const
szText db text
    db 0
    .code
    exitm <offset szText>
    endm

        .code

main  proc c argc:dword, argv:ptr ptr SBYTE

local   display:dword
local   image:dword
local   sdlevnt:SDL_Event

        invoke OutputDebugString, CStr(<"--- calling SDL_Init",13,10>)
        invoke SDL_Init, SDL_INIT_VIDEO
        .if (eax & 80000000h)
            invoke MessageBox, 0, CStr("SDL_Init failed"), 0, MB_OK
            jmp exit
        .endif

        invoke OutputDebugString, CStr(<"--- calling SDL_SetVideoMode",13,10>)
        invoke SDL_SetVideoMode, 640, 480, 0, SDL_HWSURFACE or SDL_ASYNCBLIT or SDL_HWACCEL
        .if (!eax)
            invoke SDL_GetError
            invoke MessageBox, 0, eax, CStr("SDL_SetVideoMode failed"), MB_OK
            jmp exit
        .endif

        mov display, eax
;        mov esi, CStr(".\winnt.bmp")
        mov esi, CStr(".\setup.bmp")
        invoke OutputDebugString, CStr(<"--- calling SDL_LoadBMP",13,10>)
        invoke SDL_LoadBMP(esi)
        .if (!eax)
            invoke MessageBox, 0, CStr("Error: bitmap not found"), esi, MB_OK
            jmp exit2
        .endif
        mov image, eax
        
        invoke OutputDebugString, CStr(<"--- calling SDL_BlitSurface",13,10>)
        invoke SDL_BlitSurface, image, NULL, display, NULL
        
        invoke SDL_Flip, display
        
        invoke SDL_FreeSurface, image

        .while (1)
            invoke SDL_PollEvent, addr sdlevnt
            .if (eax)
                movzx eax, sdlevnt.type_
                .if (eax == SDL_KEYDOWN)
                    .break .if (sdlevnt.key.keysym.scancode == 1)
                .endif
            .endif
        .endw
exit2:
        invoke SDL_Quit
exit:        
        ret
main  endp

        end

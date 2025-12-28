;--- an SDL audio sample written in MASM

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

        .data

pBuff   DWORD 0
dwLen   DWORD 0
dwPos   DWORD 0
bDone   BYTE 0

        .code

audio_cb proc c pUserData:ptr, stream:ptr BYTE, len:DWORD

local   waveptr:dword

        mov ecx, pBuff
        mov eax, dwLen
        add eax, ecx
        add ecx, dwPos
        sub eax, ecx
        .if (eax > len)
            mov eax, len
        .endif
        .if (!eax)
            mov bDone,1
        .endif
        add dwPos, eax
        invoke SDL_MixAudio, stream, ecx, eax, SDL_MIX_MAXVOLUME
        ret
audio_cb endp

main  proc c argc:dword, argv:ptr ptr SBYTE

local   screen:dword
local   sdlevnt:SDL_Event
local   as1:SDL_AudioSpec

        .if (argc < 2)
            invoke printf, CStr(< "need a .WAV file as parameter",10 >)
            jmp @exit
        .endif
        mov esi, SDL_INIT_AUDIO
        invoke SDL_Init, esi
        .if (sdword ptr eax < 0)
            invoke SDL_GetError
            invoke printf, CStr("SDL_Init failed [%s]"), eax
            jmp @exit
        .endif

        mov ecx, argv
        mov esi, [ecx+4]
        mov dwLen, 0
        lea ebx, as1
        lea edi, pBuff
        lea ecx, dwLen
        invoke SDL_LoadWAV(esi, ebx, edi, ecx)
        .if (!eax)
            invoke SDL_GetError
            invoke printf, CStr(< "Error: SDL_LoadWav() failed [%s]",10 >), eax
            jmp exit2
        .endif
        mov as1.callback, offset audio_cb
        
        invoke SDL_OpenAudio, addr as1, 0
        .if (sdword ptr eax < 0)
            invoke SDL_GetError
            invoke printf, CStr(< "Error: SDL_OpenAudio() failed [%s]",10 >), eax
            jmp exit2
        .endif
        invoke SDL_PauseAudio, 0

        .while (1)
            invoke SDL_Delay, 1000
            .break .if (bDone)
            invoke SDL_PollEvent, addr sdlevnt
            .if (eax)
                movzx eax, sdlevnt.type_
                .if (eax == SDL_KEYDOWN)
                    .break .if (sdlevnt.key.keysym.scancode == 1)
                .endif
            .endif
        .endw
        invoke SDL_FreeWAV, pBuff
        invoke SDL_CloseAudio
exit2:
        invoke SDL_Quit
@exit:        
        ret
main  endp

        end
